//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#include <bx/allocator.h>
#include <bx/math.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <geom/Aabb.h>
#include <geom/Intersect.h>
#include <gfx/Froxel.h>
#include <gfx/Camera.h>
#include <gfx/Viewport.h>
#include <gfx/Light.h>
#include <gfx/Scene.h>
#include <gfx/Renderer.h>
#include <gfx/GfxSystem.h>
#endif

#include <cstddef>
#include <cstdint>

#if defined WIN32
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

namespace mud
{
	static constexpr bool SUPPORTS_NON_SQUARE_FROXELS = false;
	static constexpr bool SUPPORTS_REMAPPED_FROXELS = false;

	// The Froxel buffer is set to FROXEL_BUFFER_WIDTH x n
	// With n limited by the supported texture dimension, which is guaranteed to be at least 2048
	// in all version of GLES.

	// Make sure this matches the same constants in shading_lit.fs
	constexpr size_t FROXEL_BUFFER_WIDTH_SHIFT = 6u;
	constexpr size_t FROXEL_BUFFER_WIDTH = 1u << FROXEL_BUFFER_WIDTH_SHIFT;
	constexpr size_t FROXEL_BUFFER_WIDTH_MASK = FROXEL_BUFFER_WIDTH - 1u;
	constexpr size_t FROXEL_BUFFER_HEIGHT = (FROXEL_BUFFER_ENTRY_COUNT_MAX + FROXEL_BUFFER_WIDTH_MASK) / FROXEL_BUFFER_WIDTH;

	constexpr size_t RECORD_BUFFER_WIDTH_SHIFT = 5u;
	constexpr size_t RECORD_BUFFER_WIDTH = 1u << RECORD_BUFFER_WIDTH_SHIFT;
	constexpr size_t RECORD_BUFFER_WIDTH_MASK = RECORD_BUFFER_WIDTH - 1u;

	constexpr size_t RECORD_BUFFER_HEIGHT = 2048;
	constexpr size_t RECORD_BUFFER_ENTRY_COUNT = RECORD_BUFFER_WIDTH * RECORD_BUFFER_HEIGHT; // 64K

	// number of lights processed by one group (e.g. 32)
	static constexpr size_t LIGHT_PER_GROUP = sizeof(Froxelizer::LightGroupType) * 8;

	// number of groups (i.e. jobs) to use for froxelization (e.g. 8)
	static constexpr size_t GROUP_COUNT = (CONFIG_MAX_LIGHT_COUNT + LIGHT_PER_GROUP - 1) / LIGHT_PER_GROUP;


	// record buffer cannot be larger than 65K entries because we're using uint16_t to store indices
	// so its maximum size is 128 KiB
	static_assert(RECORD_BUFFER_ENTRY_COUNT <= 65536, "RecordBuffer cannot be larger than 65536 entries");

	inline GpuBuffer::ElementType record_type() { return std::is_same<Froxelizer::RecordBufferType, uint8_t>::value ? GpuBuffer::ElementType::UINT8 : GpuBuffer::ElementType::UINT16; }

	// clustered shading refs
	// http://www.humus.name/Articles/PracticalClusteredShading.pdf
	// http://www.cse.chalmers.se/~uffe/clustered_shading_preprint.pdf

	Froxelizer::Froxelizer()
		: m_froxels({ GpuBuffer::ElementType::UINT16, 2 }, FROXEL_BUFFER_WIDTH, FROXEL_BUFFER_HEIGHT)
		, m_records({ record_type(), 1 }, RECORD_BUFFER_WIDTH, RECORD_BUFFER_HEIGHT)
	{
		m_uniform.createUniforms();
	}

	Froxelizer::~Froxelizer()
	{
		// destroy m_records_buffer
		// destroy m_froxel_buffer
	}

	bool Froxelizer::update(const Viewport& viewport, const mat4& projection, float near, float far)
	{
		[[unlikely]] if(m_viewport != &viewport || m_viewport->m_rect != viewport.m_rect)
			m_dirty |= VIEWPORT_CHANGED;
		[[unlikely]] if(m_projection != projection)
			m_dirty |= PROJECTION_CHANGED;

		//if(all(less(abs(m_projection), glm::vec3(EPSILON))))

		m_viewport = &viewport;
		m_projection = projection;
		m_near = near;
		UNUSED(far);

		bool uniformsNeedUpdating = false;

		[[unlikely]] if(m_dirty)
			uniformsNeedUpdating = update();

		return uniformsNeedUpdating;
	}

	bool Froxelizer::prepare(const Viewport& viewport, const mat4& projection, float near, float far)
	{
		bool uniformsNeedUpdating = this->update(viewport, projection, near, far);

		// froxel buffer (~32 KiB) & record buffer (~64 KiB)
		m_froxels.m_data.resize(FROXEL_BUFFER_ENTRY_COUNT_MAX);
		m_records.m_data.resize(RECORD_BUFFER_ENTRY_COUNT);

		m_light_records.resize(FROXEL_BUFFER_ENTRY_COUNT_MAX);  // light records per froxel (~256 KiB)
		m_froxel_sharded_data.resize(GROUP_COUNT);				// froxel thread data (~256 KiB)

		return uniformsNeedUpdating;
	}

	void compute_froxel_layout(uvec2* dim, uint16_t* countX, uint16_t* countY, uint16_t* countZ, uvec2 viewport)
	{
		if(SUPPORTS_NON_SQUARE_FROXELS == false)
		{
			// calculate froxel dimension from FROXEL_BUFFER_ENTRY_COUNT_MAX and viewport
			// - Start from the maximum number of froxels we can use in the x-y plane
			size_t froxelSliceCount = CONFIG_FROXEL_SLICE_COUNT;
			size_t froxelPlaneCount = FROXEL_BUFFER_ENTRY_COUNT_MAX / froxelSliceCount;
			// - compute the number of square froxels we need in width and height, rounded down
			//   solving: |  froxel_count_x * froxel_count_y == froxelPlaneCount
			//            |  froxel_count_x / froxel_count_y == width / height
			size_t froxel_count_x = size_t(bx::sqrt(froxelPlaneCount * viewport.x / viewport.y));
			size_t froxel_count_y = size_t(bx::sqrt(froxelPlaneCount * viewport.y / viewport.x));
			// - copmute the froxels dimensions, rounded up
			size_t froxelSizeX = (viewport.x + froxel_count_x - 1) / froxel_count_x;
			size_t froxelSizeY = (viewport.y + froxel_count_y - 1) / froxel_count_y;
			// - and since our froxels must be square, only keep the largest dimension
			size_t froxel_dimension = bx::max(froxelSizeX, froxelSizeY);

			// Here we recompute the froxel counts which may have changed a little due to the rounding
			// and the squareness requirement of froxels
			froxel_count_x = (viewport.x + froxel_dimension - 1) / froxel_dimension;
			froxel_count_y = (viewport.y + froxel_dimension - 1) / froxel_dimension;

			*dim = uvec2(froxel_dimension);
			*countX = uint16_t(froxel_count_x);
			*countY = uint16_t(froxel_count_y);
			*countZ = uint16_t(froxelSliceCount);
		}
		else
		{
			// TODO: don't hardcode this
			*countX = uint16_t(32);
			*countY = uint16_t(16);
			if(viewport.y > viewport.x)
				std::swap(*countX, *countY);
			*countZ = uint16_t(CONFIG_FROXEL_SLICE_COUNT);
			dim->x = (viewport.x + *countX - 1) / *countX;
			dim->y = (viewport.y + *countY - 1) / *countY;
		}
	}

	void Froxelizer::update_viewport()
	{
		uvec2 viewport = rect_size(m_viewport->m_rect);

		compute_froxel_layout(&m_froxel_dimension, &m_froxel_count_x, &m_froxel_count_y, &m_froxel_count_z, viewport);

		m_clip_to_froxel = (0.5f * vec2(viewport)) / vec2(m_froxel_dimension);

		m_inv_dimension = 1.0f / vec2(m_froxel_dimension);

		// froxel count must fit on 16 bits
		m_froxel_count = uint16_t(m_froxel_count_x * m_froxel_count_y * m_froxel_count_z);

		m_distances_z.resize(m_froxel_count_z + 1);
		m_planes_x.resize(m_froxel_count_x + 1);
		m_planes_y.resize(m_froxel_count_y + 1);
		m_bounding_spheres.resize(m_froxel_count);

		m_distances_z[0] = 0.0f;
		const float linearizer = std::log2(m_light_far / m_light_near) / float(m_froxel_count_z - 1);

		for(ssize_t i = 1, n = m_froxel_count_z; i <= n; i++)
			m_distances_z[i] = m_light_far * std::exp2f(float(i - n) * linearizer);
		
		// for the inverse-transformation (view-space z to z-slice)
		m_linearizer = 1 / linearizer;
		m_light_far_log2 = std::log2(m_light_far);

		m_params_z = { 0, 0, -m_linearizer, m_froxel_count_z };
		if(SUPPORTS_REMAPPED_FROXELS)
		{
			m_params_f.x = uint32_t(m_froxel_count_z);
			m_params_f.y = uint32_t(m_froxel_count_x * m_froxel_count_z);
			m_params_f.z = 1;
		}
		else
		{
			m_params_f.x = 1;
			m_params_f.y = uint32_t(m_froxel_count_x);
			m_params_f.z = uint32_t(m_froxel_count_x * m_froxel_count_y);
		}
	}

	void Froxelizer::update_projection()
	{
		// clip-space dimensions
		const vec2 froxel_clip_size = (2.0f * vec2(m_froxel_dimension)) / rect_size(m_viewport->m_rect);
		const mat4 inv_projection = inverse(m_projection);

		auto to_view_space = [](const mat4& inv_projection, vec4 p0, vec4 p1)
		{
			p0 = inv_projection * p0;
			p1 = inv_projection * p1;
			return vec4(normalize(cross(vec3(p1), vec3(p0))), 0.f);
		};

		for(size_t i = 0, n = m_froxel_count_x; i <= n; ++i)
		{
			float x = (i * froxel_clip_size.x) - 1.0f;
			vec4 p0 = { x, -1, -1, 1 };
			vec4 p1 = { x,  1, -1, 1 };
			m_planes_x[i] = to_view_space(inv_projection, p0, p1);
		}

		for(size_t i = 0, n = m_froxel_count_y; i <= n; ++i)
		{
			float y = (i * froxel_clip_size.y) - 1.0f;
			vec4 p0 = { -1, y, -1, 1 };
			vec4 p1 = {  1, y, -1, 1 };
			m_planes_y[i] = to_view_space(inv_projection, p0, p1);
		}

		// 3-planes intersection:
		//      -d0.(n1 x n2) - d1.(n2 x n0) - d2.(n0 x n1)
		// P = ---------------------------------------------
		//                      n0.(n1 x n2)

		// use stack memory here, it's only 16 KiB max
		assert(m_froxel_count_x <= 2048);
		typename std::aligned_storage<sizeof(vec2), alignof(vec2)>::type stack[2048];
		vec2* const minMaxX = reinterpret_cast<vec2*>(stack);

		for(size_t iz = 0, fi = 0, nz = m_froxel_count_z; iz < nz; ++iz)
		{
			vec4 planes[6];
			vec3 minp;
			vec3 maxp;

			// near/far planes for all froxels at iz
			planes[4] = vec4{ 0, 0, 1, m_distances_z[iz + 0] };
			planes[5] = -vec4{ 0, 0, 1, m_distances_z[iz + 1] };

			// min/max for z is calculated trivially because near/far planes are parallel to
			// the camera.
			minp.z = -m_distances_z[iz + 1];
			maxp.z = -m_distances_z[iz];
			assert(minp.z < maxp.z);
			
			for(size_t ix = 0; ix < m_froxel_count_x; ++ix)
			{
				// left, right planes for all froxels at ix
				planes[0] = m_planes_x[ix];
				planes[1] = -m_planes_x[ix + 1];
				minp.x = std::numeric_limits<float>::max();
				maxp.x = std::numeric_limits<float>::lowest();
				// min/max for x is calculated by intersecting the near/far and left/right planes
				for(size_t c = 0; c < 4; ++c)
				{
					vec4 const& p0 = planes[0 + (c & 1)];    // {x,0,z,0}
					vec4 const& p2 = planes[4 + (c >> 1)];    // {0,0,+/-1,d}
					float px = (p2.z * p2.w * p0.z) / p0.x;
					minp.x = bx::min(minp.x, px);
					maxp.x = bx::max(maxp.x, px);
				}
				assert(minp.x < maxp.x);
				minMaxX[ix] = vec2{ minp.x, maxp.x };
			}

			for(size_t iy = 0; iy < m_froxel_count_y; ++iy)
			{
				// bottom, top planes for all froxels at iy
				planes[2] = m_planes_y[iy];
				planes[3] = -m_planes_y[iy + 1];
				minp.y = std::numeric_limits<float>::max();
				maxp.y = std::numeric_limits<float>::lowest();
				// min/max for y is calculated by intersecting the near/far and bottom/top planes
				for(size_t c = 0; c < 4; ++c)
				{
					vec4 const& p1 = planes[2 + (c & 1)];    // {0,y,z,0}
					vec4 const& p2 = planes[4 + (c >> 1)];    // {0,0,+/-1,d}
					float py = (p2.z * p2.w * p1.z) / p1.y;
					minp.y = bx::min(minp.y, py);
					maxp.y = bx::max(maxp.y, py);
				}
				assert(minp.y < maxp.y);

				for(size_t ix = 0, nx = m_froxel_count_x; ix < nx; ++ix) 
				{
					// note: clang vectorizes this loop!
					assert(froxel_index(ix, iy, iz) == fi);
					minp.x = minMaxX[ix][0];
					maxp.x = minMaxX[ix][1];
					m_bounding_spheres[fi++] = { (maxp + minp) * 0.5f, length((maxp - minp) * 0.5f) };
				}
			}
		}

		//    linearizer = log2(zLightFar / zLightNear) / (zcount - 1)
		//    vz = -exp2((i - zcount) * linearizer) * zLightFar
		// => i = log2(zLightFar / -vz) / -linearizer + zcount

		float Pz = m_projection[2][2];
		float Pw = m_projection[3][2];
		if(m_projection[2][3] != 0)
		{
			// perspective projection
			// (clip) cz = Pz*vz+Pw, cw=-vz
			// (ndc)  nz = -Pz-Pw/vz
			// (win)  fz = -Pz*0.5+0.5 - Pw*0.5/vz
			// ->  = vz = -Pw / (2*fz + Pz-1)
			// i = log2(zLightFar*(2*fz + Pz-1) / Pw) / -linearizer + zcount
			m_params_z[0] = 2.0f * m_light_far / Pw;
			m_params_z[1] = m_light_far * (Pz - 1.0f) / Pw;
		}
		else
		{
			// orthographic projection
			// (clip) cz = Pz*vz+Pw, cw=1
			// (ndc)  nz = Pz*vz+Pw
			// (win)  fz = Pz*vz*0.5 + Pw*0.5+0.5
			// ->  = vz = (2*fz - Pw-1)/Pz
			// i = log2(-vz / zLightFar) / linearizer + zcount
			// i = log2((-2*fz + Pw + 1)/(Pz*zLightFar)) / linearizer + zcount

			m_params_z[0] = -2.0f / (Pz * m_light_far);
			m_params_z[1] = (1.0f + Pw) / (Pz * m_light_far);
			m_params_z[2] = m_linearizer;
		}

		if(m_debug_clusters.size() > 0)
			this->compute_froxels();
	}

	bool Froxelizer::update()
	{
		bool uniformsNeedUpdating = false;
		[[unlikely]] if(m_dirty & VIEWPORT_CHANGED)
		{
			update_viewport();
			uniformsNeedUpdating = true;
		}

		[[unlikely]] if(m_dirty & (PROJECTION_CHANGED | VIEWPORT_CHANGED))
		{
			update_projection();
			uniformsNeedUpdating = true;
		}
		assert(m_light_near >= m_near);
		m_dirty = 0;
		return uniformsNeedUpdating;
	}

	Plane to_plane(const vec4& p) { return { vec3(p), p.w }; }

	Frustum Froxelizer::froxel_at(size_t x, size_t y, size_t z) const
	{
		assert(x < m_froxel_count_x);
		assert(y < m_froxel_count_y);
		assert(z < m_froxel_count_z);
		Frustum froxel;
		froxel.m_planes.m_left	= to_plane(m_planes_x[x]);
		froxel.m_planes.m_down	= to_plane(m_planes_y[y]);
		froxel.m_planes.m_near	= to_plane(vec4{ 0, 0, 1, -m_distances_z[z] });
		froxel.m_planes.m_right = to_plane(-m_planes_x[x + 1]);
		froxel.m_planes.m_up	= to_plane(-m_planes_y[y + 1]);
		froxel.m_planes.m_far	= to_plane(vec4{ 0, 0, 1, -m_distances_z[z + 1] });
		froxel.m_corners = frustum_corners(froxel.m_planes);
		froxel.compute();
		return froxel;
	}

	void Froxelizer::compute_froxels()
	{	
		m_debug_clusters.resize(m_froxel_count);

		size_t i = 0;

		for(size_t z = 0; z < m_froxel_count_z; ++z)
		for(size_t y = 0; y < m_froxel_count_y; ++y)
		for(size_t x = 0; x < m_froxel_count_x; ++x)
		{
			m_debug_clusters[i++] = this->froxel_at(x, y, z);
		}
	}

	size_t Froxelizer::findSliceZ(float z) const
	{
		// The vastly common case is that z<0, so we always do the math for this case
		// and we "undo" it below otherwise. This works because we're using fast::log2 which
		// doesn't care if given a negative number (we'd have to use abs() otherwise).

		// This whole function is now branch-less.

		int s = int((bx::log2(-z) - m_light_far_log2) * m_linearizer + m_froxel_count_z);

		// there are cases where z can be negative here, e.g.:
		// - the light is visible, but its center is behind the camera
		// - the camera's near is behind the camera (e.g. with shadowmap cameras)
		// in that case just return the first slice
		s = z < 0 ? s : 0;

		// clamp between [0, m_froxel_count_z)
		return size_t(bx::clamp(s, 0, m_froxel_count_z - 1));
	}
	
	std::pair<size_t, size_t> Froxelizer::clipToIndices(const vec2& clip) const
	{
		// clip coordinates between [-1, 1], conversion to index between [0, count[
		//  = floor((clip + 1) * ((0.5 * dimension) / froxelsize))
		//  = floor((clip + 1) * constant
		//  = floor(clip * constant + constant)
		const size_t xi = size_t(bx::clamp(int(clip.x * m_clip_to_froxel.x + m_clip_to_froxel.x), 0, m_froxel_count_x - 1));
		const size_t yi = size_t(bx::clamp(int(clip.y * m_clip_to_froxel.y + m_clip_to_froxel.y), 0, m_froxel_count_y - 1));
		return { xi, yi };
	}

	void Froxelizer::upload()
	{
		m_froxels.m_memory = bgfx::copy(m_froxels.m_data.data(), sizeof(FroxelEntry) * m_froxels.m_data.size());
		m_records.m_memory = bgfx::copy(m_records.m_data.data(), sizeof(RecordBufferType) * m_records.m_data.size());

		// send data to GPU
		m_froxels.m_buffer.commit(m_froxels.m_memory);
		m_records.m_buffer.commit(m_records.m_memory);
	}

	void Froxelizer::submit()
	{
		bgfx::setTexture(uint8_t(TextureSampler::LightRecords), m_uniform.s_light_records, m_records.m_buffer.m_texture);
		bgfx::setTexture(uint8_t(TextureSampler::Clusters), m_uniform.s_light_clusters, m_froxels.m_buffer.m_texture);

		m_uniform.upload(vec4(m_inv_dimension, rect_offset(m_viewport->m_rect)), vec4(m_params_f, 0.f), m_params_z);
	}

	void Froxelizer::froxelize_lights(const Camera& camera, array<Light*> lights)
	{
		// note: this is called asynchronously
		froxelize_loop(camera, lights);
		froxelize_assign_records_compress(lights.size());
	}

	void Froxelizer::froxelize_loop(const Camera& camera, array<Light*> lights)
	{
		//SYSTRACE_CALL();

		array<FroxelThreadData> froxelThreadData = m_froxel_sharded_data;
		memset(froxelThreadData.data(), 0, froxelThreadData.size() * sizeof(FroxelThreadData));

		auto process = [this, &froxelThreadData, lights, &camera] (size_t count, size_t offset, size_t stride)
		{
			const mat4& projection = m_projection;

			for(size_t i = offset; i < count; i += stride)
			{
				vec3 position = vec3(camera.m_transform * vec4(lights[i]->m_node.m_position, 1.f));
				vec3 direction = vec3(camera.m_transform * vec4(lights[i]->m_node.direction(), 0.f));

				float cos2 = bx::square(cos(to_radians(lights[i]->m_spot_angle)));
				float invsin = 1.f / std::sqrt(1.f - cos2);

				LightParams light = { position, cos2, direction, invsin, lights[i]->m_range };

				const size_t group = i % GROUP_COUNT;
				const size_t bit = i / GROUP_COUNT;
				assert(bit < LIGHT_PER_GROUP);

				FroxelThreadData& threadData = froxelThreadData[group];
				const bool isSpot = light.invSin != std::numeric_limits<float>::infinity();
				threadData[0] |= isSpot << bit;
				froxelize_light(threadData, bit, projection, light);
			}
		};

		for(size_t i = 0; i < GROUP_COUNT; i++)
			process(lights.size(), i, GROUP_COUNT);

		// we do 64 lights per job
		/*JobSystem& js = engine.getJobSystem();

		constexpr bool SINGLE_THREADED = false;
		if(!SINGLE_THREADED) {
			auto parent = js.createJob();
			for(size_t i = 0; i < GROUP_COUNT; i++) {
				js.run(jobs::createJob(js, parent, std::cref(process), lights.size(), i, GROUP_COUNT));
			}
			js.runAndWait(parent);
		}
		else {
			js.runAndWait(jobs::createJob(js, nullptr, std::cref(process),
				lights.size(), 0, 1)
			);
		}*/
	}

	void Froxelizer::froxelize_assign_records_compress(size_t num_lights)
	{
		auto inspect = [&]()
		{
			size_t i = 0;
			for(FroxelEntry& entry : m_froxels.m_data)
			{
				if(entry.count[0] > 0 || entry.count[1] > 0 && entry.offset == 0)
					printf("froxel %i has lights but offset 0\n", i);
				i++;
			}
		};

		//SYSTRACE_CALL();

		array<FroxelThreadData> froxelThreadData = m_froxel_sharded_data;

		// convert froxel data from N groups of M bits to LightRecord::bitset, so we can
		// easily compare adjacent froxels, for compaction. The conversion loops below get
		// inlined and vectorized in release builds.

		// keep these two loops separate, it helps the compiler a lot
		LightRecord::bitset spot_lights;

		using container_type = LightRecord::bitset::container_type;
		constexpr size_t r = sizeof(container_type) / sizeof(LightGroupType);

#ifndef USE_STD_BITSET
		for(size_t i = 0; i < LightRecord::bitset::WORLD_COUNT; i++)
		{
			container_type b = froxelThreadData[i * r][0];
			for(size_t k = 0; k < r; k++)
				b |= (container_type(froxelThreadData[i * r + k][0]) << (LIGHT_PER_GROUP * k));
			spot_lights.at(i) = b;
		}

		// this gets very well vectorized...
		for(size_t j = 1, jc = FROXEL_BUFFER_ENTRY_COUNT_MAX; j < jc; j++)
		{
			for(size_t i = 0; i < LightRecord::bitset::WORLD_COUNT; i++)
			{
				container_type b = froxelThreadData[i * r][j];
				for(size_t k = 0; k < r; k++)
					b |= (container_type(froxelThreadData[i * r + k][j]) << (LIGHT_PER_GROUP * k));
				m_light_records[j - 1].lights.at(i) = b;
			}
		}
#else
		for(size_t i = 0; i < CONFIG_MAX_LIGHT_COUNT; ++i)
			spot_lights[i] = froxelThreadData[i][0];

		for(size_t j = 1, jc = FROXEL_BUFFER_ENTRY_COUNT_MAX; j < jc; j++)
			for(size_t i = 0; i < CONFIG_MAX_LIGHT_COUNT; ++i)
				m_light_records[j - 1].lights[i] = froxelThreadData[i][j];
#endif

		uint16_t offset = 0;

		auto remap = [stride = size_t(m_froxel_count_x * m_froxel_count_y)](size_t i) -> size_t
		{
			if(SUPPORTS_REMAPPED_FROXELS) {
				// TODO: with the non-square froxel change these would be mask ops instead of divide.
				i = (i % stride) * CONFIG_FROXEL_SLICE_COUNT + (i / stride);
			}
			return i;
		};

		for(size_t i = 0, c = m_froxel_count; i < c;)
		{
			LightRecord b = m_light_records[i];
			if(b.lights.none())
			{
				m_froxels.m_data[remap(i++)].u32 = 0;
				continue;
			}

			// We have a limitation of 255 spot + 255 point lights per froxel.
			uint8_t point_count = (uint8_t)bx::min(size_t(255), (b.lights & ~spot_lights).count());
			uint8_t spot_count = (uint8_t)bx::min(size_t(255), (b.lights &  spot_lights).count());

			FroxelEntry entry = { offset, point_count, spot_count };

			const uint8_t light_count = entry.count[0] + entry.count[1];

			[[unlikely]] if(offset + light_count >= RECORD_BUFFER_ENTRY_COUNT)
			{
				// note: instead of dropping froxels we could look for similar records we've already
				// filed up.
				do { // this compiles to memset() when remap() is identity
					m_froxels.m_data[remap(i++)].u32 = 0;
				} while(i < c);
				goto out_of_memory;
			}

			// iterate the bitfield
			size_t first_point = offset;
			size_t first_spot = offset + entry.count[0];
			size_t point = first_point;
			size_t spot = first_spot;

//#ifndef USE_STD_BITSET
#if 0
			b.lights.for_each([&](size_t l) mutable
#else
			for(size_t l = 0; l < CONFIG_MAX_LIGHT_COUNT; ++l)
				if(b.lights[l])
#endif
			{
				// make sure to keep this code branch-less
				const bool isSpot = spot_lights[l];
				auto& i = isSpot ? spot : point;
				auto  s = isSpot ? first_spot : first_point;

				const size_t word = l / LIGHT_PER_GROUP;
				const size_t bit = l % LIGHT_PER_GROUP;
				size_t ll = (bit * GROUP_COUNT) | (word % GROUP_COUNT);
				assert(ll < num_lights);

				m_records.m_data[i] = (RecordBufferType)ll;
				// we need to "cancel" the write if we have more than 255 spot or point lights
				// (this is a limitation of the data type used to store the light counts per froxel)
				i += (i - s < 255) ? 1 : 0;

//#ifndef USE_STD_BITSET
#if 0
			});
#else
			}
#endif

			offset += light_count;

			do {
				m_froxels.m_data[remap(i++)].u32 = entry.u32;
				if(i >= c) break;

				if(m_light_records[i].lights != b.lights && i >= m_froxel_count_x)
				{
					// if this froxel record doesn't match the previous one on its left,
					// we re-try with the record above it, which saves many froxel records
					// (north of 10% in practice).
					b = m_light_records[i - m_froxel_count_x];
					entry.u32 = m_froxels.m_data[remap(i - m_froxel_count_x)].u32;
				}
			} while(m_light_records[i].lights == b.lights);

			//printf("\niteration %i\n\n", i);
			//inspect();
		}

	out_of_memory:
		;
	}

	static inline vec2 project(mat4 const& p, vec3 const& v)
	{
		const float vx = v[0];
		const float vy = v[1];
		const float vz = v[2];

		// We know we're using a projection matrix (which has a bunch of zeros)
		// But we need to handle asymetric frustums and orthographic projections.
		//       orthographic ------------------------+
		//  asymmetric frustum ---------+             |
		//                              v             v
		const float x = p[0].x * vx + p[2].x * vz + p[3].x;
		const float y = p[1].y * vy + p[2].y * vz + p[3].y;
		const float w = p[2].w * vz + p[3].w;

		return vec2{ x, y } * (1 / w);
	}

	inline float sphere_plane_distance2(const vec4& s, float px, float pz) { return sphere_plane_intersection(vec3(s), s.w, { px, 0.f, pz }, 0.f).w; };
	inline vec4 sphere_plane_intersection(const vec4& s, float py, float pz) { return sphere_plane_intersection(vec3(s), s.w, { 0.f, py, pz }, 0.f); };
	inline vec4 sphere_plane_intersection(const vec4& s, float pw) { return sphere_plane_intersection(vec3(s), s.w, { 0.f, 0.f, 1.f }, pw); };
	inline bool sphere_cone_intersection(const vec4& s, const vec3& cone_position, const vec3& cone_axis, float cone_sin_inverse, float cone_cos_squared) { return sphere_cone_intersection_fast(vec3(s), s.w, cone_position, cone_axis, cone_sin_inverse, cone_cos_squared); }
	
	void Froxelizer::light_bounds(const mat4& projection, const Froxelizer::LightParams& light, uvec3& lo, uvec3& hi) const
	{
		// find a reasonable bounding-box in froxel space for the sphere by projecting
		// it's (clipped) bounding-box to clip-space and converting to froxel indices.
		Aabb aabb = { light.position, vec3(light.radius) };
		const float znear = bx::min(-m_near, aabb.m_center.z + aabb.m_extents.z); // z values are negative
		const float zfar = aabb.m_center.z - aabb.m_extents.z;

		vec2 xyLeftNear		= project(projection, { vec2(aabb.m_center) - vec2(aabb.m_extents), znear });
		vec2 xyLeftFar		= project(projection, { vec2(aabb.m_center) - vec2(aabb.m_extents), zfar });
		vec2 xyRightNear	= project(projection, { vec2(aabb.m_center) + vec2(aabb.m_extents), znear });
		vec2 xyRightFar		= project(projection, { vec2(aabb.m_center) + vec2(aabb.m_extents), zfar });

		// handle inverted frustums (e.g. x or y symetries)
		if(xyLeftNear.x > xyRightNear.x)   std::swap(xyLeftNear.x, xyRightNear.x);
		if(xyLeftNear.y > xyRightNear.y)   std::swap(xyLeftNear.y, xyRightNear.y);
		if(xyLeftFar.x  > xyRightFar.x)    std::swap(xyLeftFar.x, xyRightFar.x);
		if(xyLeftFar.y  > xyRightFar.y)    std::swap(xyLeftFar.y, xyRightFar.y);

		const auto imin = clipToIndices(min(xyLeftNear, xyLeftFar));
		lo = { imin.first, imin.second, findSliceZ(znear) };

		const auto imax = clipToIndices(max(xyRightNear, xyRightFar));
		hi = {
			imax.first + 1,   // x1 points to 1 past the last value (like end() does
			imax.second,      // y1 points to the last value
			findSliceZ(zfar)  // z1 points to the last value
		};
	}

	void Froxelizer::froxelize_light(FroxelThreadData& froxelThread, size_t bit, const mat4& projection, const Froxelizer::LightParams& light) const
	{
		[[unlikely]] if(light.position.z + light.radius < -m_light_far) {    // z values are negative
																			// This light is fully behind LightFar, it doesn't light anything
																			// (we could avoid this check if we culled lights using LightFar instead of the
																			// culling camera's far plane)
			return;
		}

		// the code below works with radius^2
		const vec4 s = { light.position, light.radius * light.radius };

		uvec3 lo, hi;
		light_bounds(projection, light, lo, hi);

		assert(lo.x < hi.x);
		assert(lo.y <= hi.y);
		assert(lo.z <= hi.z);

		const size_t zcenter = findSliceZ(s.z);

		for(size_t iz = lo.z; iz <= hi.z; ++iz)
		{
			vec4 cz(s);
			[[unlikely]] if(iz != zcenter)
				cz = sphere_plane_intersection(s, (iz < zcenter) ? m_distances_z[iz + 1] : m_distances_z[iz]);

			// find x & y slices that contain the sphere's center
			// (note: this changes with the Z slices
			const vec2 clip = project(projection, vec3(cz));
			const auto indices = clipToIndices(clip);
			const size_t xcenter = indices.first;
			const size_t ycenter = indices.second;

			if(cz.w > 0)
			{ // intersection of light with this plane (slice)
				for(size_t iy = lo.y; iy <= hi.y; ++iy)
				{
					vec4 cy(cz);
					[[unlikely]] if(iy != ycenter)
					{
						vec4 const& plane = iy < ycenter ? m_planes_y[iy + 1] : m_planes_y[iy];
						cy = sphere_plane_intersection(cz, plane.y, plane.z);
					}
					if(cy.w > 0)
					{ // intersection of light with this horizontal plane
						size_t bx, ex; // horizontal begin/end indices
										// find the begin index (left side)
						for(bx = lo.x; ++bx <= xcenter; bx)
							if(sphere_plane_distance2(cy, m_planes_x[bx].x, m_planes_x[bx].z) > 0)
								break; // intersection

						// find the end index (right side), x1 is past the end
						for(ex = hi.x; --ex > xcenter; ex)
							if(sphere_plane_distance2(cy, m_planes_x[ex].x, m_planes_x[ex].z) > 0)
								break; // intersection

						--bx;
						++ex;

						[[unlikely]] if(bx >= ex)
							continue;

						assert(bx < m_froxel_count_x && ex <= m_froxel_count_x);

						// The first entry reserved for type of light, i.e. point/spot
						size_t fi = froxel_index(bx, iy, iz) + 1;
						if(light.invSin != std::numeric_limits<float>::infinity())
						{
							// This is a spotlight (common case)
							// this loops gets vectorized (on arm64) w/ clang
							while(bx++ != ex)
							{
								// see if this froxel intersects the cone
								bool intersect = sphere_cone_intersection(m_bounding_spheres[fi - 1], light.position, light.axis, light.invSin, light.cosSqr);
								froxelThread[fi++] |= LightGroupType(intersect) << bit;
							}
						}
						else
						{
							// this loops gets vectorized (on arm64) w/ clang
							while(bx++ != ex)
								froxelThread[fi++] |= LightGroupType(1) << bit;
						}
					}
				}
			}
		}
	}
}
