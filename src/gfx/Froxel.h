//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/vector.h>
#include <infra/Array.h>
#include <geom/Geom.h>
#endif
#include <gfx/Forward.h>
#include <gfx/Buffer.h>
#include <gfx/FrustumCluster.h>

#if defined MUD_UNIFORM_BLOCKS
#include <gfx/Uniform.h>
#endif

#include <bgfx/bgfx.h>

namespace mud
{
	constexpr uint32_t CONFIG_MAX_LIGHT_COUNT = 256;
	constexpr uint32_t CONFIG_MAX_LIGHT_INDEX = CONFIG_MAX_LIGHT_COUNT - 1;

	constexpr uint32_t CONFIG_FROXEL_SLICE_COUNT = 16;

	//
	// Light UBO           Froxel Record Buffer     per-froxel light list texture
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
	//  |....|                                          h = num froxels
	//  |....|
	//  +----+
	// 256 lights max
	//

	// Max number of froxels limited by:
	// - max texture size [min 2048]
	// - chosen texture width [64]
	// - size of CPU-side indices [16 bits]
	// Also, increasing the number of froxels adds more pressure on the "record buffer" which stores
	// the light indices per froxel. The record buffer is limited to 65536 entries, so with
	// 8192 froxels, we can store 8 lights per froxels assuming they're all used. In practice, some
	// froxels are not used, so we can store more.
	static constexpr uint32_t FROXEL_BUFFER_ENTRY_COUNT_MAX = 8192;

	export_ struct FroxelUniform
	{
		void createUniforms()
		{
			s_light_records		= bgfx::createUniform("s_light_records",	bgfx::UniformType::Int1);
			s_light_clusters	= bgfx::createUniform("s_light_clusters",	bgfx::UniformType::Int1);

			u_froxel_params = bgfx::createUniform("u_froxel_params",	bgfx::UniformType::Vec4);
			u_froxel_f		= bgfx::createUniform("u_froxel_f",			bgfx::UniformType::Vec4);
			u_froxel_z		= bgfx::createUniform("u_froxel_z",			bgfx::UniformType::Vec4);
		}

		bgfx::UniformHandle s_light_records;
		bgfx::UniformHandle s_light_clusters;

		bgfx::UniformHandle u_froxel_params;
		bgfx::UniformHandle u_froxel_f;
		bgfx::UniformHandle u_froxel_z;
	};

	class MUD_GFX_EXPORT Froxelizer
	{
	public:
		Froxelizer(GfxSystem& gfx_system);
		~Froxelizer();

		bool prepare(const Viewport& viewport, const mat4& projection, float near, float far);
		bool update(const Viewport& viewport, const mat4& projection, float near, float far);

		// update Records and Froxels texture with lights data. this is thread-safe.
		void froxelize_lights(const Camera& camera, array<Light*> lights);
		void froxelize_loop(const Camera& camera, array<Light*> lights);

		// send froxel data to GPU
		void upload();
		void submit(bgfx::Encoder& encoder) const;

		void compute_froxels();

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

		void froxelize_assign_records_compress(uint32_t num_lights);

		void froxelize_light_group(const Camera& camera, array<Light*> lights, uint32_t offset, uint32_t stride);

		GfxSystem& m_gfx_system;

		ClusteredFrustum m_frustum;

		vector<Frustum> m_debug_clusters;

		struct Impl;
		unique<Impl> m_impl;

		mat4 m_projection;

		// needed for update()
		const Viewport* m_viewport;
		vec4 m_params_z = {};
		uvec3 m_params_f = {};
		float m_near = 0.0f;        // camera near
		float m_light_far = 100.f;
		float m_light_near = 5.f;  // light near (first slice)

		// track if we need to update our internal state before froxelizing
		uint8_t m_dirty = 0;
		enum {
			VIEWPORT_CHANGED = 0x01,
			PROJECTION_CHANGED = 0x02
		};

		FroxelUniform m_uniform;
	};

}
