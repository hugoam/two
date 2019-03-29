//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/vector.h>
#include <stl/map.h>
#include <math/Vec.h>
#endif
#include <gfx/Texture.h>
#include <gfx/RenderTarget.h>
#include <gfx-pbr/Forward.h>

#include <bgfx/bgfx.h>

namespace mud
{
	class ShadowAtlas
	{
	public:
		ShadowAtlas() {}
		ShadowAtlas(uint16_t size, vector<uint16_t> slices_subdiv);

		uint16_t m_size = 0;
		uvec2 m_rect_size;

		Texture m_color;
		Texture m_depth;
		FrameBuffer m_fbo;

		struct Slot
		{
			uint16_t m_index;
			Light* m_light;
			uvec4 m_rect;
		};

		struct Slice;

		Slice& light_slice(Light& light);
		Slot& light_slot(Light& light);

		uvec4 render_update(Render& render, Light& light);
		bool update_light(Light& light, uint64_t render, float coverage, uint64_t light_version);
		void remove_light(Light& light, bool block = false);

		struct Slice
		{
			Slice() {}
			Slice(uint8_t index, uint16_t size, uint16_t subdiv, uvec4 rect);

			uint8_t m_index;
			uint16_t m_size;
			uint16_t m_subdiv;
			uvec4 m_rect;

			uint16_t m_slot_size;
			vector<Slot> m_slots;

			vector<Slot*> m_free_slots;
			vector<Slot*> m_free_blocks;
		};

		vector<Slice> m_slices;

		struct Index { uint8_t slice; uint16_t slot; };
	};
}
