//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <math/Vec.h>
#endif
#include <gfx-pbr/Forward.h>

#include <bgfx/bgfx.h>

#ifndef MUD_CPP_20
#include <vector>
#include <map>
#endif

namespace mud
{
	struct ShadowCubemap
	{
		ShadowCubemap(uint16_t size);
		bgfx::FrameBufferHandle m_fbos[6];
		bgfx::TextureHandle m_cubemap;
		uint16_t m_size;
	};

	class ShadowAtlas
	{
	public:
		ShadowAtlas(uint16_t size, std::vector<uint16_t> slices_subdiv);

		uint16_t m_size = 0;

		bgfx::TextureHandle m_depth = BGFX_INVALID_HANDLE;
		bgfx::FrameBufferHandle m_fbo = BGFX_INVALID_HANDLE;

		std::vector<ShadowCubemap> m_cubemaps;

		uvec4 light_rect(Light& light);

		uvec4 render_update(Render& render, Light& light);
		bool update_light(Light& light, uint64_t render, float coverage, uint64_t light_version);
		void remove_light(Light& light);

		ShadowCubemap& light_cubemap(Light& light, uint16_t shadow_size);

		struct Slice
		{
			Slice(uint32_t size, uint16_t subdiv, uvec4 rect);

			uint32_t m_size;
			uint16_t m_subdiv;
			uvec4 m_rect;

			struct Slot
			{
				Light* m_light;
				uvec4 m_rect;
			};

			void remove_light(Light& light);
			void add_light(Light& light);

			std::vector<Slot> m_slots;
			std::vector<Slot*> m_free_slots;
		};

		std::vector<Slice> m_slices;

		struct Index
		{
			uint8_t m_slice;
			uint16_t m_slot;
		};

		std::vector<Index> m_light_indices;
	};
}
