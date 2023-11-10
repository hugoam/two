//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <bgfx/bgfx.h>
#include <stl/vector.h>
#include <stl/map.h>
#include <math/Vec.h>
#include <gfx/Depth.h>
#include <gfx/Texture.h>
#include <gfx/RenderTarget.h>
#endif
#include <gfx-pbr/Forward.h>

namespace two
{
	class ShadowAtlas
	{
	public:
		ShadowAtlas() {}
		ShadowAtlas(uint16_t size, uint8_t num_slices);

		uint16_t m_side = 0;
		uvec2 m_size;

		const Texture& texture(DepthMethod depth_method) const
		{
			if (depth_method == DepthMethod::Depth)
				return m_depth;
			else if (depth_method == DepthMethod::DepthPacked || depth_method == DepthMethod::Distance)
				return m_color;
		}

		Texture m_color;
		Texture m_depth;
		FrameBuffer m_fbo;

		struct Block;

		struct Slot
		{
			uint16_t m_index;
			Light* m_light = nullptr;
			vec4 m_rect;
			uvec4 m_trect;
			uint32_t m_frame = 0;
			uint16_t m_block = UINT16_MAX;
		};

		struct Block
		{
			uint32_t m_slots[8];
		};

		struct Slice;

		Slice& light_slice(Light& light);
		Slot& light_slot(Light& light);

		void begin_frame(const RenderFrame& frame);
		void subdiv(Slice& slice, uint16_t subdiv);
		
		Slot& alloc(Slice& slice, bool block6 = false);
		void yield(Slice& slice, uint32_t index);

		vec4 render_update(Render& render, Light& light);
		bool update_light(Light& light, uint32_t render, float coverage, uint32_t light_version);
		void remove_light(Light& light, bool block = false);

		struct Slice
		{
			Slice() {}
			Slice(uint8_t index, const uvec2& size, const vec4& rect);

			uint8_t m_index;
			uvec2 m_size;
			vec4 m_rect;

			uint16_t m_subdiv = 0;
			uvec2 m_slot_size;
			vector<Slot> m_slots;
			vector<Block> m_blocks;

			vector<uint32_t> m_free_slots;
			vector<uint32_t> m_free_blocks;
		};

		vector<Slice> m_slices;
	};
}
