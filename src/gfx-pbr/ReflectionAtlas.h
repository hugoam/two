//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/vector.h>
#include <math/Colour.h>
#include <math/Vec.h>
#include <gfx/Texture.h>
#include <gfx/RenderTarget.h>
#endif
#include <gfx-pbr/Forward.h>

#include <bgfx/bgfx.h>

namespace mud
{
	struct ReflectionCubemap
	{
		ReflectionCubemap() {}
		ReflectionCubemap(uint32_t size);
		FrameBuffer m_fbo[6];
		Texture m_cubemap;
		Texture m_depth;
		uint32_t m_size;
	};

	class ReflectionAtlas
	{
	public:
		ReflectionAtlas(uint16_t size, uint16_t subdiv);
		~ReflectionAtlas();

		uint16_t m_size = 0;
		uint16_t m_subdiv = 0;

		FrameBuffer m_fbo[6];
		Texture m_color;

		vec4 probe_rect(ReflectionProbe& probe);
		uvec4 render_update(Render& render, ReflectionProbe& probe);

		struct Slot
		{
			size_t m_index;
			ReflectionProbe* m_probe;
			uvec4 m_urect;
			vec4 m_rect;
			uint64_t m_last_update;
		};

		vector<Slot> m_slots;
		vector<Slot*> m_free_slots;
	};
}
