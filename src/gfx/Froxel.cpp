//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#include <bx/allocator.h>
#include <bx/math.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <jobs/Job.h>
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

	Froxelizer::Froxelizer(GfxSystem& gfx_system)
		: m_gfx_system(gfx_system)
		, m_froxels({ GpuBuffer::ElementType::UINT16, 2 }, FROXEL_BUFFER_WIDTH, FROXEL_BUFFER_HEIGHT)
		, m_records({ record_type(), 1 }, RECORD_BUFFER_WIDTH, RECORD_BUFFER_HEIGHT)
	{
		m_uniform.createUniforms();
	}

	Froxelizer::~Froxelizer()
	{}

	bool Froxelizer::update(const Viewport& viewport, const mat4& projection, float near, float far)
	{
		if(m_viewport != &viewport || m_viewport->m_rect != viewport.m_rect) //[[unlikely]]
			m_dirty |= VIEWPORT_CHANGED;
		if(m_projection != projection) //[[unlikely]]
			m_dirty |= PROJECTION_CHANGED;

		//if(all(less(abs(m_projection), glm::vec3(EPSILON))))

		m_viewport = &viewport;
		m_projection = projection;
		m_near = near;
		UNUSED(far);

		bool uniformsNeedUpdating = false;

		if(m_dirty) // [[unlikely]] 
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

	void Froxelizer::update_viewport()
	{
		m_frustum.m_near = m_light_near;
		m_frustum.m_far = m_light_far;

		m_frustum.resize(rect_size(vec4(m_viewport->m_rect)));

		m_params_z = { 0.f, 0.f, -m_frustum.m_linearizer, float(m_frustum.m_subdiv_z) };
		if(SUPPORTS_REMAPPED_FROXELS)
		{
			m_params_f.x = uint32_t(m_frustum.m_subdiv_z);
			m_params_f.y = uint32_t(m_frustum.m_subdiv_x * m_frustum.m_subdiv_z);
			m_params_f.z = 1;
		}
		else
		{
			m_params_f.x = 1;
			m_params_f.y = uint32_t(m_frustum.m_subdiv_x);
			m_params_f.z = uint32_t(m_frustum.m_subdiv_x * m_frustum.m_subdiv_y);
		}
	}

	void Froxelizer::update_projection()
	{
		m_frustum.recompute(m_projection, rect_size(vec4(m_viewport->m_rect)));

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
			m_params_z[2] = m_frustum.m_linearizer;
		}

		if(m_debug_clusters.size() > 0)
			this->compute_froxels();
	}

	bool Froxelizer::update()
	{
		bool uniformsNeedUpdating = false;
		if(m_dirty & VIEWPORT_CHANGED) // [[unlikely]] 
		{
			update_viewport();
			uniformsNeedUpdating = true;
		}

		if(m_dirty & (PROJECTION_CHANGED | VIEWPORT_CHANGED)) // [[unlikely]] 
		{
			update_projection();
			uniformsNeedUpdating = true;
		}
		assert(m_light_near >= m_near);
		m_dirty = 0;
		return uniformsNeedUpdating;
	}

	void Froxelizer::compute_froxels()
	{	
		m_debug_clusters.resize(m_frustum.m_cluster_count);

		size_t i = 0;

		for(size_t z = 0; z < m_frustum.m_subdiv_z; ++z)
		for(size_t y = 0; y < m_frustum.m_subdiv_y; ++y)
		for(size_t x = 0; x < m_frustum.m_subdiv_x; ++x)
		{
			m_debug_clusters[i++] = m_frustum.cluster_frustum(x, y, z);
		}
	}

	void Froxelizer::upload()
	{
		m_froxels.m_memory = bgfx::copy(m_froxels.m_data.data(), uint32_t(sizeof(FroxelEntry) * m_froxels.m_data.size()));
		m_records.m_memory = bgfx::copy(m_records.m_data.data(), uint32_t(sizeof(RecordBufferType) * m_records.m_data.size()));

		// send data to GPU
		m_froxels.m_buffer.commit(m_froxels.m_memory);
		m_records.m_buffer.commit(m_records.m_memory);
	}

	void Froxelizer::submit(bgfx::Encoder& encoder) const
	{
		encoder.setTexture(uint8_t(TextureSampler::LightRecords), m_uniform.s_light_records, m_records.m_buffer.m_texture);
		encoder.setTexture(uint8_t(TextureSampler::Clusters), m_uniform.s_light_clusters, m_froxels.m_buffer.m_texture);

		auto submit = [=](bgfx::Encoder& encoder, vec4 params, vec4 f, vec4 z)
		{
			encoder.setUniform(m_uniform.u_froxel_params, &params);
			encoder.setUniform(m_uniform.u_froxel_f, &f);
			encoder.setUniform(m_uniform.u_froxel_z, &z);
		};

		submit(encoder, vec4(m_frustum.m_inv_tile_size, rect_offset(vec4(m_viewport->m_rect))), vec4(vec3(m_params_f), 0.f), m_params_z);
	}

	void Froxelizer::froxelize_lights(const Camera& camera, array<Light*> lights)
	{
		// note: this is called asynchronously
		froxelize_loop(camera, lights);
		froxelize_assign_records_compress(lights.size());
	}

	void Froxelizer::froxelize_light_group(const Camera& camera, array<Light*> lights, size_t offset, size_t stride)
	{
		const mat4& projection = m_projection;

		for(size_t i = offset; i < lights.size(); i += stride)
		{
			vec3 position = vec3(camera.m_transform * vec4(lights[i]->m_node.position(), 1.f));
			vec3 direction = vec3(camera.m_transform * vec4(lights[i]->m_node.direction(), 0.f));

			float cos2 = bx::square(cos(to_radians(lights[i]->m_spot_angle)));
			float invsin = 1.f / std::sqrt(1.f - cos2);

			LightParams light = { position, cos2, direction, invsin, lights[i]->m_range };

			const size_t group = i % GROUP_COUNT;
			const size_t bit = i / GROUP_COUNT;
			assert(bit < LIGHT_PER_GROUP);

			FroxelThreadData& threadData = m_froxel_sharded_data[group];
			const bool isSpot = light.invSin != std::numeric_limits<float>::infinity();
			threadData[0] |= isSpot << bit;
			froxelize_light(threadData, bit, projection, light);
		}
	}

#define MUD_THREADED

	void Froxelizer::froxelize_loop(const Camera& camera, array<Light*> lights)
	{
		memset(m_froxel_sharded_data.data(), 0, m_froxel_sharded_data.size() * sizeof(FroxelThreadData));

#ifdef MUD_THREADED
		JobSystem& js = *m_gfx_system.m_job_system;

		auto process_task = [&](size_t offset, size_t stride)
		{
			this->froxelize_light_group(camera, lights, offset, stride);
		};

		Job* parent = js.job();
		for(size_t i = 0; i < GROUP_COUNT; i++)
			js.run(job(js, parent, std::cref(process_task), i, GROUP_COUNT));
		js.complete(parent);
#else
		for(size_t i = 0; i < GROUP_COUNT; i++)
			this->froxelize_light_group(camera, lights, i, GROUP_COUNT);
#endif
	}

	void Froxelizer::froxelize_assign_records_compress(size_t num_lights)
	{
		UNUSED(num_lights);

		auto inspect = [&]()
		{
			size_t i = 0;
			for(FroxelEntry& entry : m_froxels.m_data)
			{
				if((entry.count[0] > 0 || entry.count[1] > 0) && entry.offset == 0)
					printf("froxel %i has lights but offset 0\n", int(i));
				i++;
			}
		};
		UNUSED(inspect);

		// convert froxel data from N groups of M bits to LightRecord::Lights, so we can
		// easily compare adjacent froxels, for compaction. The conversion loops below get
		// inlined and vectorized in release builds.

		// keep these two loops separate, it helps the compiler a lot
		LightRecord::Lights spot_lights;

		using container_type = LightRecord::Lights::container_type;
		constexpr size_t r = sizeof(container_type) / sizeof(LightGroupType);

		for(size_t i = 0; i < LightRecord::Lights::WORLD_COUNT; i++)
		{
			container_type b = m_froxel_sharded_data[i * r][0];
			for(size_t k = 0; k < r; k++)
				b |= (container_type(m_froxel_sharded_data[i * r + k][0]) << (LIGHT_PER_GROUP * k));
			spot_lights.at(i) = b;
		}

		// this gets very well vectorized...
		for(size_t j = 1, jc = FROXEL_BUFFER_ENTRY_COUNT_MAX; j < jc; j++)
		{
			for(size_t i = 0; i < LightRecord::Lights::WORLD_COUNT; i++)
			{
				container_type b = m_froxel_sharded_data[i * r][j];
				for(size_t k = 0; k < r; k++)
					b |= (container_type(m_froxel_sharded_data[i * r + k][j]) << (LIGHT_PER_GROUP * k));
				m_light_records[j - 1].lights.at(i) = b;
			}
		}

		uint16_t offset = 0;

		auto remap = [stride = size_t(m_frustum.m_subdiv_x * m_frustum.m_subdiv_y)](size_t i) -> size_t
		{
			if(SUPPORTS_REMAPPED_FROXELS) {
				// TODO: with the non-square froxel change these would be mask ops instead of divide.
				i = (i % stride) * CONFIG_FROXEL_SLICE_COUNT + (i / stride);
			}
			return i;
		};

		size_t num_clusters = m_frustum.m_cluster_count;
		for(size_t cluster = 0; cluster < num_clusters;)
		{
			LightRecord b = m_light_records[cluster];
			if(b.lights.none())
			{
				m_froxels.m_data[remap(cluster++)].u32 = 0;
				continue;
			}

			// We have a limitation of 255 spot + 255 point lights per froxel.
			uint8_t point_count = (uint8_t)bx::min(size_t(255), (b.lights & ~spot_lights).count());
			uint8_t spot_count = (uint8_t)bx::min(size_t(255), (b.lights &  spot_lights).count());

			FroxelEntry entry = { offset, point_count, spot_count };

			const uint8_t light_count = entry.count[0] + entry.count[1];

			if(offset + light_count >= RECORD_BUFFER_ENTRY_COUNT) //[[unlikely]]
			{
				// note: instead of dropping froxels we could look for similar records we've already
				// filed up.
				do { // this compiles to memset() when remap() is identity
					m_froxels.m_data[remap(cluster++)].u32 = 0;
				} while(cluster < num_clusters);
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
				m_froxels.m_data[remap(cluster++)].u32 = entry.u32;
				if(cluster >= num_clusters) break;

				if(m_light_records[cluster].lights != b.lights && cluster >= m_frustum.m_subdiv_x)
				{
					// if this froxel record doesn't match the previous one on its left,
					// we re-try with the record above it, which saves many froxel records
					// (north of 10% in practice).
					b = m_light_records[cluster - m_frustum.m_subdiv_x];
					entry.u32 = m_froxels.m_data[remap(cluster - m_frustum.m_subdiv_x)].u32;
				}
			} while(m_light_records[cluster].lights == b.lights);

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

		const auto imin = m_frustum.tile_index(min(xyLeftNear, xyLeftFar));
		lo = { imin.x, imin.y, m_frustum.slice(znear) };

		const auto imax = m_frustum.tile_index(max(xyRightNear, xyRightFar));
		hi = {
			imax.x + 1,   // x1 points to 1 past the last value (like end() does
			imax.y,      // y1 points to the last value
			m_frustum.slice(zfar)  // z1 points to the last value
		};
	}

	void Froxelizer::froxelize_light(FroxelThreadData& froxelThread, size_t bit, const mat4& projection, const Froxelizer::LightParams& light) const
	{
		if(light.position.z + light.radius < -m_light_far) // [[unlikely]] // z values are negative
		{
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

		const size_t zcenter = m_frustum.slice(s.z);

		for(size_t iz = lo.z; iz <= hi.z; ++iz)
		{
			vec4 cz(s);
			if(iz != zcenter) // [[unlikely]]
				cz = sphere_plane_intersection(s, (iz < zcenter) ? m_frustum.m_distances_z[iz + 1] : m_frustum.m_distances_z[iz]);

			// find x & y slices that contain the sphere's center
			// (note: this changes with the Z slices
			const vec2 clip = project(projection, vec3(cz));
			const auto center = m_frustum.tile_index(clip);

			if(cz.w > 0)
			{ // intersection of light with this plane (slice)
				for(size_t iy = lo.y; iy <= hi.y; ++iy)
				{
					vec4 cy(cz);
					if(iy != center.y) // [[unlikely]] 
					{
						vec4 const& plane = iy < center.y ? m_frustum.m_planes_y[iy + 1] : m_frustum.m_planes_y[iy];
						cy = sphere_plane_intersection(cz, plane.y, plane.z);
					}
					if(cy.w > 0)
					{ // intersection of light with this horizontal plane
						size_t bx, ex; // horizontal begin/end indices
										// find the begin index (left side)
						for(bx = lo.x; ++bx <= center.x;)
							if(sphere_plane_distance2(cy, m_frustum.m_planes_x[bx].x, m_frustum.m_planes_x[bx].z) > 0)
								break; // intersection

						// find the end index (right side), x1 is past the end
						for(ex = hi.x; --ex > center.x;)
							if(sphere_plane_distance2(cy, m_frustum.m_planes_x[ex].x, m_frustum.m_planes_x[ex].z) > 0)
								break; // intersection

						--bx;
						++ex;

						if(bx >= ex) // [[unlikely]]
							continue;

						assert(bx < m_frustum.m_subdiv_x && ex <= m_frustum.m_subdiv_x);

						// The first entry reserved for type of light, i.e. point/spot
						size_t fi = m_frustum.index(bx, iy, iz) + 1;
						if(light.invSin != std::numeric_limits<float>::infinity())
						{
							// This is a spotlight (common case)
							// this loops gets vectorized (on arm64) w/ clang
							while(bx++ != ex)
							{
								// see if this froxel intersects the cone
								bool intersect = sphere_cone_intersection(m_frustum.m_bounding_spheres[fi - 1], light.position, light.axis, light.invSin, light.cosSqr);
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
