//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#include <bx/allocator.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <stl/bitset.h>
#include <stl/swap.h>
#include <stl/span.h>
#include <stl/array.h>
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

#include <stl/stddef.h>
#include <stdint.h>
#include <cstring>
#include <cstdio>
#include <limits>

#if defined WIN32
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

//#define USE_STD_BITSET

#include <stl/vector.hpp>

namespace mud
{
	// This depends on the maximum number of lights (currently 255),and can't be more than 16 bits.
	static_assert(CONFIG_MAX_LIGHT_INDEX <= UINT16_MAX, "can't have more than 65536 lights");
	using RecordBufferType = std::conditional_t<CONFIG_MAX_LIGHT_INDEX <= UINT8_MAX, uint8_t, uint16_t>;

	// this is chosen so clusterizePointAndSpotLight() vectorizes 4 cluster tests / spotlight
	// with 256 lights this implies 8 jobs (256 / 32) for clusterization.

	using LightGroupType = uint32_t;

	// The first entry always encodes the type of light, i.e. point/spot
	using FroxelThreadData = array<LightGroupType, CLUSTER_BUFFER_ENTRY_COUNT_MAX + 1>;

	static constexpr bool SUPPORTS_REMAPPED_CLUSTERS = false;

	// The Froxel buffer is set to CLUSTER_BUFFER_WIDTH x n
	// With n limited by the supported texture dimension, which is guaranteed to be at least 2048
	// in all version of GLES.

	// Make sure this matches the same constants in shading_lit.fs
	constexpr uint32_t CLUSTER_BUFFER_WIDTH_SHIFT = 6u;
	constexpr uint32_t CLUSTER_BUFFER_WIDTH = 1u << CLUSTER_BUFFER_WIDTH_SHIFT;
	constexpr uint32_t CLUSTER_BUFFER_WIDTH_MASK = CLUSTER_BUFFER_WIDTH - 1u;
	constexpr uint32_t CLUSTER_BUFFER_HEIGHT = (CLUSTER_BUFFER_ENTRY_COUNT_MAX + CLUSTER_BUFFER_WIDTH_MASK) / CLUSTER_BUFFER_WIDTH;

	constexpr uint32_t RECORD_BUFFER_WIDTH_SHIFT = 5u;
	constexpr uint32_t RECORD_BUFFER_WIDTH = 1u << RECORD_BUFFER_WIDTH_SHIFT;
	constexpr uint32_t RECORD_BUFFER_WIDTH_MASK = RECORD_BUFFER_WIDTH - 1u;

	constexpr uint32_t RECORD_BUFFER_HEIGHT = 2048;
	constexpr uint32_t RECORD_BUFFER_ENTRY_COUNT = RECORD_BUFFER_WIDTH * RECORD_BUFFER_HEIGHT; // 64K

	// number of lights processed by one group (e.g. 32)
	static constexpr uint32_t LIGHT_PER_GROUP = sizeof(LightGroupType) * 8;

	// number of groups (i.e. jobs) to use for clusterization (e.g. 8)
	static constexpr uint32_t GROUP_COUNT = (CONFIG_MAX_LIGHT_COUNT + LIGHT_PER_GROUP - 1) / LIGHT_PER_GROUP;


	// record buffer cannot be larger than 65K entries because we're using uint16_t to store indices
	// so its maximum size is 128 KiB
	static_assert(RECORD_BUFFER_ENTRY_COUNT <= 65536, "RecordBuffer cannot be larger than 65536 entries");

	inline GpuBuffer::ElementType record_type() { return std::is_same<RecordBufferType, uint8_t>::value ? GpuBuffer::ElementType::UINT8 : GpuBuffer::ElementType::UINT16; }

	// clustered shading refs
	// http://www.humus.name/Articles/PracticalClusteredShading.pdf
	// http://www.cse.chalmers.se/~uffe/clustered_shading_preprint.pdf

	struct LightRecord
	{
#ifndef USE_STD_BITSET
		using Lights = bitset<uint64_t, (CONFIG_MAX_LIGHT_COUNT + 63) / 64>;
#else
		using Lights = std::bitset<CONFIG_MAX_LIGHT_COUNT>;
#endif
		Lights lights;
	};

	struct LightParams
	{
		LightParams(vec3 position, float cosSqr, vec3 axis, float invSin, float radius) : position(position), cosSqr(cosSqr), axis(axis), invSin(invSin), radius(radius) {}
		vec3 position;
		float cosSqr;
		vec3 axis;
		float invSin = std::numeric_limits<float>::infinity(); // this must be initialized to indicate this is a point light
		float radius; // radius is not used in the hot loop, so leave it at the end
	};

	struct FroxelUniform
	{
		void createUniforms()
		{
			s_light_records  = bgfx::createUniform("s_light_records",  bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View);
			s_light_clusters = bgfx::createUniform("s_light_clusters", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View);

			u_cluster_p0 = bgfx::createUniform("u_cluster_p0", bgfx::UniformType::Vec4, 1U, bgfx::UniformFreq::View);
			u_cluster_f = bgfx::createUniform("u_cluster_f", bgfx::UniformType::Vec4, 1U, bgfx::UniformFreq::View);
			u_cluster_z = bgfx::createUniform("u_cluster_z", bgfx::UniformType::Vec4, 1U, bgfx::UniformFreq::View);
		}

		bgfx::UniformHandle s_light_records;
		bgfx::UniformHandle s_light_clusters;

		bgfx::UniformHandle u_cluster_p0;
		bgfx::UniformHandle u_cluster_f;
		bgfx::UniformHandle u_cluster_z;
	};

	struct Froxelizer::Impl
	{
		Impl()
			: m_clusters({ GpuBuffer::ElementType::UINT16, 2 }, CLUSTER_BUFFER_WIDTH, CLUSTER_BUFFER_HEIGHT)
			, m_records({ record_type(), 1 }, RECORD_BUFFER_WIDTH, RECORD_BUFFER_HEIGHT)
		{
			m_uniform.createUniforms();
		}

		template <class T>
		struct Buffer
		{
			Buffer(GpuBuffer::Element element, uint32_t row_size, uint32_t row_count) : m_buffer(element, row_size, row_count) {}
			GpuBuffer m_buffer;
			vector<T> m_data;
			const bgfx::Memory* m_memory;
		};

		vector<FroxelThreadData> m_cluster_sharded_data;  // 256 KiB w/ 256 lights
		vector<LightRecord> m_light_records;             // 256 KiB w/ 256 lights

		Buffer<FroxelEntry> m_clusters;			//  32 KiB w/ 8192 clusters
		Buffer<RecordBufferType> m_records;		//  64 KiB // max 32 KiB  (actual: resolution dependant)

		FroxelUniform m_uniform;
	};

	void clusterize_light(ClusteredFrustum& frustum, FroxelThreadData& clusterThread, uint32_t bit, const mat4& projection, float near, const LightParams& light, float light_far);

	Froxelizer::Froxelizer(GfxSystem& gfx)
		: m_gfx(gfx)
		, m_impl(construct<Impl>())
	{
		UNUSED(RECORD_BUFFER_WIDTH_MASK);
	}

	Froxelizer::~Froxelizer()
	{}

	uint32_t Froxelizer::record(uint32_t cluster) { return m_impl->m_clusters.m_data[cluster].offset; }
	uint32_t Froxelizer::count(uint32_t record, int type) { return m_impl->m_clusters.m_data[record].count[type]; }
	uint32_t Froxelizer::light(uint32_t record) { return m_impl->m_records.m_data[record]; }

	bool Froxelizer::update(const uvec4& rect, const mat4& projection, float near, float far)
	{
		if(m_viewport != rect) //[[unlikely]]
			m_dirty |= uint8_t(Dirty::Viewport);
		if(m_proj != projection) //[[unlikely]]
			m_dirty |= uint8_t(Dirty::Projection);

		//if(all(less(abs(m_proj), vec3(EPSILON))))

		m_viewport = rect;
		m_proj = projection;
		m_near = near;
		m_light_far = far;

		bool uniformsNeedUpdating = false;

		if(m_dirty) // [[unlikely]] 
			uniformsNeedUpdating = update();

		return uniformsNeedUpdating;
	}

	void Froxelizer::setup()
	{
		// cluster buffer (~32 KiB) & record buffer (~64 KiB)
		m_impl->m_clusters.m_data.resize(CLUSTER_BUFFER_ENTRY_COUNT_MAX);
		m_impl->m_records.m_data.resize(RECORD_BUFFER_ENTRY_COUNT);

		m_impl->m_light_records.resize(CLUSTER_BUFFER_ENTRY_COUNT_MAX);  // light records per cluster (~256 KiB)
		m_impl->m_cluster_sharded_data.resize(GROUP_COUNT);				// cluster thread data (~256 KiB)
	}

	void Froxelizer::update_viewport()
	{
		m_frustum.m_near = m_light_near;
		m_frustum.m_far = m_light_far;

		m_frustum.resize(rect_size(vec4(m_viewport)));

		m_pz = { 0.f, 0.f, -m_frustum.m_linearizer, float(m_frustum.m_subdiv_z) };
		if(SUPPORTS_REMAPPED_CLUSTERS)
		{
			m_pf.x = uint32_t(m_frustum.m_subdiv_z);
			m_pf.y = uint32_t(m_frustum.m_subdiv_x * m_frustum.m_subdiv_z);
			m_pf.z = 1;
		}
		else
		{
			m_pf.x = 1;
			m_pf.y = uint32_t(m_frustum.m_subdiv_x);
			m_pf.z = uint32_t(m_frustum.m_subdiv_x * m_frustum.m_subdiv_y);
		}
	}

	void Froxelizer::update_projection()
	{
		m_frustum.recompute(m_proj, rect_size(vec4(m_viewport)));

		//    linearizer = log2(zLightFar / zLightNear) / (zcount - 1)
		//    vz = -exp2((i - zcount) * linearizer) * zLightFar
		// => i = log2(zLightFar / -vz) / -linearizer + zcount
		
		float Pz = m_proj[2][2];
		float Pw = m_proj[3][2];
		if(m_proj[2][3] != 0)
		{
			// perspective projection
			// (clip) cz = Pz*vz+Pw, cw=-vz
			// (ndc)  nz = -Pz-Pw/vz
			// (win)  fz = -Pz*0.5+0.5 - Pw*0.5/vz
			// ->  = vz = -Pw / (2*fz + Pz-1)
			// i = log2(zLightFar*(2*fz + Pz-1) / Pw) / -linearizer + zcount
			m_pz[0] = 2.0f * m_light_far / Pw;
			m_pz[1] = m_light_far * (Pz - 1.0f) / Pw;
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

			m_pz[0] = -2.0f / (Pz * m_light_far);
			m_pz[1] = (1.0f + Pw) / (Pz * m_light_far);
			m_pz[2] = m_frustum.m_linearizer;
		}

		if(m_debug_clusters.size() > 0)
			this->compute_clusters();
	}

	bool Froxelizer::update()
	{
		bool uniformsNeedUpdating = false;
		if(m_dirty & uint8_t(Dirty::Viewport)) // [[unlikely]] 
		{
			update_viewport();
			uniformsNeedUpdating = true;
		}

		if(m_dirty & uint8_t(Dirty::Projection) | uint8_t(Dirty::Viewport)) // [[unlikely]] 
		{
			update_projection();
			uniformsNeedUpdating = true;
		}
		assert(m_light_near >= m_near);
		m_dirty = 0;
		return uniformsNeedUpdating;
	}

	void Froxelizer::compute_clusters()
	{	
		m_debug_clusters.resize(m_frustum.m_cluster_count);

		uint32_t i = 0;

		for(uint16_t z = 0; z < m_frustum.m_subdiv_z; ++z)
		for(uint16_t y = 0; y < m_frustum.m_subdiv_y; ++y)
		for(uint16_t x = 0; x < m_frustum.m_subdiv_x; ++x)
		{
			m_debug_clusters[i++] = m_frustum.cluster_frustum(x, y, z);
		}
	}

	void Froxelizer::upload()
	{
		m_impl->m_clusters.m_memory = bgfx::copy(m_impl->m_clusters.m_data.data(), uint32_t(sizeof(FroxelEntry) * m_impl->m_clusters.m_data.size()));
		m_impl->m_records.m_memory = bgfx::copy(m_impl->m_records.m_data.data(), uint32_t(sizeof(RecordBufferType) * m_impl->m_records.m_data.size()));

		// send data to GPU
		m_impl->m_clusters.m_buffer.commit(m_impl->m_clusters.m_memory);
		m_impl->m_records.m_buffer.commit(m_impl->m_records.m_memory);
	}

	struct refl_ GpuClusters
	{
		attr_ gpu_ vec2 inv_tile_size;
		attr_ gpu_ vec2 viewport_pos;
		attr_ gpu_ vec3 params_f;
		attr_ gpu_ vec4 params_z;
	};

	void Froxelizer::submit(const Pass& pass) const
	{
		uint32_t records = uint32_t(TextureSampler::LightRecords);
		uint32_t clusters = uint32_t(TextureSampler::Clusters);

		bgfx::setViewUniform(pass.m_index, m_impl->m_uniform.s_light_records, &records);
		bgfx::setViewUniform(pass.m_index, m_impl->m_uniform.s_light_clusters, &clusters);

		auto submit = [=](vec4 params, vec4 f, vec4 z)
		{
			bgfx::setViewUniform(pass.m_index, m_impl->m_uniform.u_cluster_p0, &params);
			bgfx::setViewUniform(pass.m_index, m_impl->m_uniform.u_cluster_f, &f);
			bgfx::setViewUniform(pass.m_index, m_impl->m_uniform.u_cluster_z, &z);
		};

		submit(vec4(m_frustum.m_inv_tile_size, rect_offset(vec4(m_viewport))), vec4(vec3(m_pf), 0.f), m_pz);
	}

	void Froxelizer::submit(bgfx::Encoder& encoder) const
	{
		encoder.setTexture(uint8_t(TextureSampler::LightRecords), m_impl->m_records.m_buffer.m_texture);
		encoder.setTexture(uint8_t(TextureSampler::Clusters), m_impl->m_clusters.m_buffer.m_texture);
	}

	void Froxelizer::clusterize_lights(const Camera& camera, span<Light*> lights)
	{
		// note: this is called asynchronously
		clusterize_loop(camera, lights);
		clusterize_assign_records_compress(uint32_t(lights.size()));
	}

	void Froxelizer::clusterize_light_group(const Camera& camera, span<Light*> lights, uint32_t offset, uint32_t stride)
	{
		const mat4& projection = m_proj;

		for(uint32_t i = offset; i < lights.size(); i += stride)
		{
			vec3 position = mulp(camera.m_view, lights[i]->m_node->position());
			vec3 direction = muln(camera.m_view, lights[i]->m_node->direction());

			float cos2 = sq(cos(to_radians(lights[i]->m_spot_angle)));
			float invsin = 1.f / std::sqrt(1.f - cos2);

			LightParams light = { position, cos2, direction, invsin, lights[i]->m_range };

			const uint32_t group = i % GROUP_COUNT;
			const uint32_t bit = i / GROUP_COUNT;
			assert(bit < LIGHT_PER_GROUP);

			FroxelThreadData& threadData = m_impl->m_cluster_sharded_data[group];
			const bool isSpot = light.invSin != std::numeric_limits<float>::infinity();
			threadData[0] |= isSpot << bit;
			clusterize_light(m_frustum, threadData, bit, projection, m_near, light, m_light_far);
		}
	}

#define MUD_THREADED

	void Froxelizer::clusterize_loop(const Camera& camera, span<Light*> lights)
	{
		memset(m_impl->m_cluster_sharded_data.data(), 0, m_impl->m_cluster_sharded_data.size() * sizeof(FroxelThreadData));

#ifdef MUD_THREADED
		JobSystem& js = *m_gfx.m_job_system;
		Job* parent = js.job();
		for(uint32_t i = 0; i < GROUP_COUNT; i++)
		{
			auto task = [=, &camera](JobSystem&, Job*) { this->clusterize_light_group(camera, lights, i, GROUP_COUNT); };
			js.run(js.job(parent, task));
		}
		js.complete(parent);
#else
		for(uint32_t i = 0; i < GROUP_COUNT; i++)
			this->clusterize_light_group(camera, lights, i, GROUP_COUNT);
#endif
	}

	void Froxelizer::clusterize_assign_records_compress(uint32_t num_lights)
	{
		UNUSED(num_lights);

		auto inspect = [&]()
		{
			uint32_t i = 0;
			for(FroxelEntry& entry : m_impl->m_clusters.m_data)
			{
				if((entry.count[0] > 0 || entry.count[1] > 0) && entry.offset == 0)
					printf("cluster %i has lights but offset 0\n", int(i));
				i++;
			}
		};
		UNUSED(inspect);

		// convert cluster data from N groups of M bits to LightRecord::Lights, so we can
		// easily compare adjacent clusters, for compaction. The conversion loops below get
		// inlined and vectorized in release builds.

		// keep these two loops separate, it helps the compiler a lot
		LightRecord::Lights spot_lights;

		using container_type = LightRecord::Lights::container_type;
		constexpr uint32_t r = sizeof(container_type) / sizeof(LightGroupType);

		for(uint32_t i = 0; i < LightRecord::Lights::WORLD_COUNT; i++)
		{
			container_type b = m_impl->m_cluster_sharded_data[i * r][0];
			for(uint32_t k = 0; k < r; k++)
				b |= (container_type(m_impl->m_cluster_sharded_data[i * r + k][0]) << (LIGHT_PER_GROUP * k));
			spot_lights.at(i) = b;
		}

		// this gets very well vectorized...
		for(uint32_t j = 1, jc = CLUSTER_BUFFER_ENTRY_COUNT_MAX; j < jc; j++)
		{
			for(uint32_t i = 0; i < LightRecord::Lights::WORLD_COUNT; i++)
			{
				container_type b = m_impl->m_cluster_sharded_data[i * r][j];
				for(uint32_t k = 0; k < r; k++)
					b |= (container_type(m_impl->m_cluster_sharded_data[i * r + k][j]) << (LIGHT_PER_GROUP * k));
				m_impl->m_light_records[j - 1].lights.at(i) = b;
			}
		}

		uint16_t offset = 0;

		auto remap = [stride = uint32_t(m_frustum.m_subdiv_x * m_frustum.m_subdiv_y)](uint32_t i) -> uint32_t
		{
			if(SUPPORTS_REMAPPED_CLUSTERS) {
				// TODO: with the non-square cluster change these would be mask ops instead of divide.
				i = (i % stride) * CONFIG_CLUSTER_SLICE_COUNT + (i / stride);
			}
			return i;
		};

		uint32_t num_clusters = m_frustum.m_cluster_count;
		for(uint32_t cluster = 0; cluster < num_clusters;)
		{
			LightRecord b = m_impl->m_light_records[cluster];
			if(b.lights.none())
			{
				m_impl->m_clusters.m_data[remap(cluster++)].u32 = 0;
				continue;
			}

			// We have a limitation of 255 spot + 255 point lights per cluster.
			uint8_t point_count = uint8_t(min(255U, uint32_t((b.lights & ~spot_lights).count())));
			uint8_t spot_count = uint8_t(min(255U, uint32_t((b.lights &  spot_lights).count())));

			FroxelEntry entry = { offset, point_count, spot_count };

			const uint8_t light_count = entry.count[0] + entry.count[1];

			if(offset + light_count >= RECORD_BUFFER_ENTRY_COUNT) //[[unlikely]]
			{
				// note: instead of dropping clusters we could look for similar records we've already
				// filed up.
				do { // this compiles to memset() when remap() is identity
					m_impl->m_clusters.m_data[remap(cluster++)].u32 = 0;
				} while(cluster < num_clusters);
				goto out_of_memory;
			}

			// iterate the bitfield
			uint32_t first_point = offset;
			uint32_t first_spot = offset + entry.count[0];
			uint32_t point = first_point;
			uint32_t spot = first_spot;

//#ifndef USE_STD_BITSET
#if 0
			b.lights.for_each([&](uint32_t l) mutable
#else
			for(uint32_t l = 0; l < CONFIG_MAX_LIGHT_COUNT; ++l)
				if(b.lights[l])
#endif
			{
				// make sure to keep this code branch-less
				const bool isSpot = spot_lights[l];
				auto& i = isSpot ? spot : point;
				auto  s = isSpot ? first_spot : first_point;

				const uint32_t word = l / LIGHT_PER_GROUP;
				const uint32_t bit = l % LIGHT_PER_GROUP;
				uint32_t ll = (bit * GROUP_COUNT) | (word % GROUP_COUNT);
				assert(ll < num_lights);

				m_impl->m_records.m_data[i] = (RecordBufferType)ll;
				// we need to "cancel" the write if we have more than 255 spot or point lights
				// (this is a limitation of the data type used to store the light counts per cluster)
				i += (i - s < 255) ? 1 : 0;

//#ifndef USE_STD_BITSET
#if 0
			});
#else
			}
#endif

			offset += light_count;

			do {
				m_impl->m_clusters.m_data[remap(cluster++)].u32 = entry.u32;
				if(cluster >= num_clusters) break;

				if(m_impl->m_light_records[cluster].lights != b.lights && cluster >= m_frustum.m_subdiv_x)
				{
					// if this cluster record doesn't match the previous one on its left,
					// we re-try with the record above it, which saves many cluster records
					// (north of 10% in practice).
					b = m_impl->m_light_records[cluster - m_frustum.m_subdiv_x];
					entry.u32 = m_impl->m_clusters.m_data[remap(cluster - m_frustum.m_subdiv_x)].u32;
				}
			} while(m_impl->m_light_records[cluster].lights == b.lights);

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

		return vec2(x, y) * (1 / w);
	}

	inline float sphere_plane_distance2(const vec4& s, float px, float pz)
	{
		return sphere_plane_intersection(vec3(s), s.w, { px, 0.f, pz }, 0.f).w;
	}
	
	inline vec4 sphere_plane_intersection(const vec4& s, float py, float pz)
	{
		return sphere_plane_intersection(vec3(s), s.w, { 0.f, py, pz }, 0.f);
	}
	
	inline vec4 sphere_plane_intersection(const vec4& s, float pw)
	{
		return sphere_plane_intersection(vec3(s), s.w, { 0.f, 0.f, 1.f }, pw);
	}

	inline bool sphere_cone_intersection(const vec4& s, const vec3& cone_position, const vec3& cone_axis, float cone_sin_inverse, float cone_cos_squared)
	{
		return sphere_cone_intersection_fast(vec3(s), s.w, cone_position, cone_axis, cone_sin_inverse, cone_cos_squared);
	}
	
	void light_bounds(ClusteredFrustum& frustum, const mat4& projection, float near, const LightParams& light, uvec3& lo, uvec3& hi)
	{
		// find a reasonable bounding-box in cluster space for the sphere by projecting
		// it's (clipped) bounding-box to clip-space and converting to cluster indices.
		Aabb aabb = { light.position, vec3(light.radius) };
		const float znear = bx::min(-near, aabb.m_center.z + aabb.m_extents.z); // z values are negative
		const float zfar = aabb.m_center.z - aabb.m_extents.z;

		vec2 xyLeftNear		= project(projection, { vec2(aabb.m_center) - vec2(aabb.m_extents), znear });
		vec2 xyLeftFar		= project(projection, { vec2(aabb.m_center) - vec2(aabb.m_extents), zfar });
		vec2 xyRightNear	= project(projection, { vec2(aabb.m_center) + vec2(aabb.m_extents), znear });
		vec2 xyRightFar		= project(projection, { vec2(aabb.m_center) + vec2(aabb.m_extents), zfar });

		// handle inverted frustums (e.g. x or y symetries)
		if(xyLeftNear.x > xyRightNear.x)   swap(xyLeftNear.x, xyRightNear.x);
		if(xyLeftNear.y > xyRightNear.y)   swap(xyLeftNear.y, xyRightNear.y);
		if(xyLeftFar.x  > xyRightFar.x)    swap(xyLeftFar.x, xyRightFar.x);
		if(xyLeftFar.y  > xyRightFar.y)    swap(xyLeftFar.y, xyRightFar.y);

		const auto imin = frustum.tile_index(min(xyLeftNear, xyLeftFar));
		lo = { imin.x, imin.y, frustum.slice(znear) };

		const auto imax = frustum.tile_index(max(xyRightNear, xyRightFar));
		hi = {
			imax.x + 1,   // x1 points to 1 past the last value (like end() does
			imax.y,      // y1 points to the last value
			frustum.slice(zfar)  // z1 points to the last value
		};
	}

	void clusterize_light(ClusteredFrustum& frustum, FroxelThreadData& clusterThread, uint32_t bit, const mat4& projection, float near, const LightParams& light, float light_far)
	{
		if(light.position.z + light.radius < -light_far) // [[unlikely]] // z values are negative
		{
			// This light is fully behind LightFar, it doesn't light anything
			// (we could avoid this check if we culled lights using LightFar instead of the
			// culling camera's far plane)
			return;
		}

		// the code below works with radius^2
		const vec4 s = { light.position, light.radius * light.radius };

		uvec3 lo, hi;
		light_bounds(frustum, projection, near, light, lo, hi);

		assert(lo.x < hi.x);
		assert(lo.y <= hi.y);
		assert(lo.z <= hi.z);

		const uint32_t zcenter = frustum.slice(s.z);

		for(uint32_t iz = lo.z; iz <= hi.z; ++iz)
		{
			vec4 cz(s);
			if(iz != zcenter) // [[unlikely]]
				cz = sphere_plane_intersection(s, (iz < zcenter) ? frustum.m_distances_z[iz + 1] : frustum.m_distances_z[iz]);

			// find x & y slices that contain the sphere's center
			// (note: this changes with the Z slices
			const vec2 clip = project(projection, vec3(cz));
			const auto center = frustum.tile_index(clip);

			if(cz.w > 0)
			{ // intersection of light with this plane (slice)
				for(uint32_t iy = lo.y; iy <= hi.y; ++iy)
				{
					vec4 cy(cz);
					if(iy != center.y) // [[unlikely]] 
					{
						vec4 const& plane = iy < center.y ? frustum.m_planes_y[iy + 1] : frustum.m_planes_y[iy];
						cy = sphere_plane_intersection(cz, plane.y, plane.z);
					}
					if(cy.w > 0)
					{ // intersection of light with this horizontal plane
						uint32_t bx, ex; // horizontal begin/end indices
										// find the begin index (left side)
						for(bx = lo.x; ++bx <= center.x;)
							if(sphere_plane_distance2(cy, frustum.m_planes_x[bx].x, frustum.m_planes_x[bx].z) > 0)
								break; // intersection

						// find the end index (right side), x1 is past the end
						for(ex = hi.x; --ex > center.x;)
							if(sphere_plane_distance2(cy, frustum.m_planes_x[ex].x, frustum.m_planes_x[ex].z) > 0)
								break; // intersection

						--bx;
						++ex;

						if(bx >= ex) // [[unlikely]]
							continue;

						assert(bx < frustum.m_subdiv_x && ex <= frustum.m_subdiv_x);

						// The first entry reserved for type of light, i.e. point/spot
						uint16_t fi = frustum.index(bx, iy, iz) + 1;
						if(light.invSin != std::numeric_limits<float>::infinity())
						{
							// This is a spotlight (common case)
							// this loops gets vectorized (on arm64) w/ clang
							while(bx++ != ex)
							{
								// see if this cluster intersects the cone
								bool intersect = sphere_cone_intersection(frustum.m_bounding_spheres[fi - 1], light.position, light.axis, light.invSin, light.cosSqr);
								clusterThread[fi++] |= LightGroupType(intersect) << bit;
							}
						}
						else
						{
							// this loops gets vectorized (on arm64) w/ clang
							while(bx++ != ex)
								clusterThread[fi++] |= LightGroupType(1) << bit;
						}
					}
				}
			}
		}
	}
}
