//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <stl/vector.h>
#include <stl/span.h>
#include <geom/Geom.h>
#endif
#include <gfx/Forward.h>
#include <gfx/Buffer.h>
#include <gfx/FrustumCluster.h>

#if defined TWO_UNIFORM_BLOCKS
#include <gfx/Uniform.h>
#endif

#ifndef TWO_MODULES
namespace bgfx
{
	struct Encoder;
}
#endif

namespace two
{
	constexpr uint32_t CONFIG_MAX_LIGHT_COUNT = 256;
	constexpr uint32_t CONFIG_MAX_LIGHT_INDEX = CONFIG_MAX_LIGHT_COUNT - 1;

	constexpr uint32_t CONFIG_CLUSTER_SLICE_COUNT = 16;

	//
	// Light UBO           Froxel Record Buffer     per-cluster light list texture
	// {4 x vec4}         R_U8  {index into        RG_U16 {offset, point-count, spot-sount}
	// (spot/point            light texture}
	//
	//  +----+                     +-+                     +----+
	// 0|....| <------------+     0| |         +-----------|0221| (e.g. offset=02, 2-point, 1-spot)
	// 1|....|<--------+     \    1| |        /            |    |
	// 2:    :          \     +---2|0|<------+             |    |
	// 3:    : <-------- \--------3|3|                     :    :
	// 4:    :            +------- :1:                     :    :
	//  :    :                     : :                     :    :
	//  :    :                     | |                     |    |
	//  :    :                     | |                     |    |
	//  :    :                     +-+                     |    |
	//  :    :                  65536 max                  +----+
	//  |....|                                          h = num clusters
	//  |....|
	//  +----+
	// 256 lights max
	//

	// Max number of clusters limited by:
	// - max texture size [min 2048]
	// - chosen texture width [64]
	// - size of CPU-side indices [16 bits]
	// Also, increasing the number of clusters adds more pressure on the "record buffer" which stores
	// the light indices per cluster. The record buffer is limited to 65536 entries, so with
	// 8192 clusters, we can store 8 lights per clusters assuming they're all used. In practice, some
	// clusters are not used, so we can store more.
	static constexpr uint32_t CLUSTER_BUFFER_ENTRY_COUNT_MAX = 8192;

	class TWO_GFX_EXPORT Froxelizer
	{
	public:
		Froxelizer(GfxSystem& gfx);
		~Froxelizer();

		void setup();
		bool update(const uvec4& rect, const mat4& projection, float near, float far);

		// update Records and Froxels texture with lights data. this is thread-safe.
		void clusterize_lights(const Camera& camera, span<Light*> lights);
		void clusterize_loop(const Camera& camera, span<Light*> lights);

		// send cluster data to GPU
		void upload();
		void submit(const Pass& pass) const;
		void submit(bgfx::Encoder& encoder) const;

		void compute_clusters();

		struct FroxelEntry
		{
			FroxelEntry() {}
			FroxelEntry(uint16_t offset, uint8_t point_count, uint8_t spot_count) : offset(offset), count{ point_count, spot_count } {}
			union
			{
				uint32_t u32 = 0;
				struct
				{
					uint16_t offset;
					uint8_t count[2];
				};
			};
		};

		bool update();
		void update_viewport();
		void update_projection();

		uint32_t record(uint32_t cluster);
		uint32_t count(uint32_t cluster, int type = 0);
		uint32_t light(uint32_t record);

		void clusterize_assign_records_compress(uint32_t num_lights);

		void clusterize_light_group(const Camera& camera, span<Light*> lights, uint32_t offset, uint32_t stride);

		GfxSystem& m_gfx;

		ClusteredFrustum m_frustum;

		vector<Frustum> m_debug_clusters;

		struct Impl;
		unique<Impl> m_impl;

		mat4 m_proj;

		// needed for update()
		uvec4 m_viewport;
		vec4 m_pz = {};
		uvec3 m_pf = {};
		float m_near = 0.0f;        // camera near
		float m_light_far = 100.f;
		float m_light_near = 5.f;  // light near (first slice)

		// track if we need to update our internal state before clusterizing
		uint8_t m_dirty = 0;
		enum class Dirty {
			None = 0,
			Viewport,
			Projection
		};
	};

}
