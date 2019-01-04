//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <infra/Array.h>
#include <infra/Bitset.h>
#include <geom/Geom.h>
#endif
#include <gfx/Forward.h>
#include <gfx/Buffer.h>
#include <gfx/FrustumCluster.h>

#if defined MUD_UNIFORM_BLOCKS
#include <gfx/Uniform.h>
#endif

#ifndef MUD_CPP_20
#include <vector>
#include <array>
#include <bitset>
#endif

#include <bgfx/bgfx.h>

//#define USE_STD_BITSET

namespace mud
{
	constexpr size_t CONFIG_MAX_LIGHT_COUNT = 256;
	constexpr size_t CONFIG_MAX_LIGHT_INDEX = CONFIG_MAX_LIGHT_COUNT - 1;

	constexpr size_t CONFIG_FROXEL_SLICE_COUNT = 16;

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
	static constexpr size_t FROXEL_BUFFER_ENTRY_COUNT_MAX = 8192;

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

		// This depends on the maximum number of lights (currently 255),and can't be more than 16 bits.
		static_assert(CONFIG_MAX_LIGHT_INDEX <= std::numeric_limits<uint16_t>::max(), "can't have more than 65536 lights");
		using RecordBufferType = std::conditional_t<CONFIG_MAX_LIGHT_INDEX <= std::numeric_limits<uint8_t>::max(), uint8_t, uint16_t>;

		// this is chosen so froxelizePointAndSpotLight() vectorizes 4 froxel tests / spotlight
		// with 256 lights this implies 8 jobs (256 / 32) for froxelization.
		using LightGroupType = uint32_t;

	//private:
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

		// The first entry always encodes the type of light, i.e. point/spot
		using FroxelThreadData = std::array<LightGroupType, FROXEL_BUFFER_ENTRY_COUNT_MAX + 1>;

		bool update();
		void update_viewport();
		void update_projection();

		void froxelize_assign_records_compress(size_t num_lights);

		void light_bounds(const mat4& projection, const Froxelizer::LightParams& light, uvec3& lo, uvec3& hi) const;
		void froxelize_light(FroxelThreadData& froxelThread, size_t bit, const mat4& projection, const LightParams& light) const;
		void froxelize_light_group(const Camera& camera, array<Light*> lights, size_t offset, size_t stride);

		GfxSystem& m_gfx_system;

		ClusteredFrustum m_frustum;

		template <class T>
		struct Buffer
		{
			Buffer(GpuBuffer::Element element, size_t row_size, size_t row_count) : m_buffer(element, row_size, row_count) {}
			GpuBuffer m_buffer;
			std::vector<T> m_data;
			const bgfx::Memory* m_memory;
		};

		std::vector<FroxelThreadData> m_froxel_sharded_data;  // 256 KiB w/ 256 lights
		std::vector<LightRecord> m_light_records;             // 256 KiB w/ 256 lights

		Buffer<FroxelEntry> m_froxels;			//  32 KiB w/ 8192 froxels
		Buffer<RecordBufferType> m_records;		//  64 KiB // max 32 KiB  (actual: resolution dependant)

		std::vector<Frustum> m_debug_clusters;

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
