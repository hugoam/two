//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef MUD_CPP_20
#include <assert.h> // <cassert>
#include <stdint.h> // <cstdint>
#include <float.h> // <cfloat>
import std.core;
import std.memory;
#endif

#ifdef MUD_MODULES
module mud.gfx-pbr;
#else
#include <obj/Vector.h>
#include <gfx/Renderer.h>
#include <gfx/Node3.h>
#include <gfx-pbr/ReflectionAtlas.h>
#include <gfx-pbr/Reflection.h>
#endif

#include <bx/math.h>

namespace mud
{
	ReflectionAtlas::ReflectionAtlas(uint16_t size, uint16_t subdiv)
		: m_size(size)
		, m_subdiv(subdiv)
	{
#if 0 // @todo: crashes in D3D11
		bgfx::TextureFormat::Enum color_format = bgfx::TextureFormat::RGBA16F;

		if(!bgfx::isTextureValid(0, true, 1, color_format, GFX_TEXTURE_CLAMP))
			color_format = bgfx::TextureFormat::RGB10A2;

		m_color = bgfx::createTextureCube(size, true, 1, color_format, GFX_TEXTURE_CLAMP);

		for(int i = 0; i < 6; i++)
		{
			bgfx::Attachment attachment = { m_color, 0, uint16_t(i) };
			m_fbo[i] = bgfx::createFrameBuffer(1, &attachment, true);
			// clear it ? 
		}

		m_slots.reserve(subdiv * subdiv);
		for(uint x = 0; x < subdiv; ++x)
			for(uint y = 0; y < subdiv; ++y)
			{
				uint subdiv_size = m_size / m_subdiv;
				uvec4 slot_urect = { x * subdiv_size, y * subdiv_size, subdiv_size, subdiv_size };
				vec4 slot_rect = vec4(slot_urect) / float(m_size);
				m_slots.push_back({ m_slots.size(), nullptr, slot_urect, slot_rect, 0 });
			}
#endif
	}

	ReflectionAtlas::~ReflectionAtlas()
	{
		for(int i = 0; i < 6; i++)
			bgfx::destroy(m_fbo[i]);
		bgfx::destroy(m_color);
	}

	vec4 ReflectionAtlas::probe_rect(ReflectionProbe& probe)
	{
		return m_slots[probe.m_atlas_index].m_rect;
	}

	uvec4 ReflectionAtlas::render_update(Render& render, ReflectionProbe& probe)
	{
		UNUSED(render);
		if(probe.m_atlas_index)
			return m_slots[probe.m_atlas_index].m_urect;

		Slot& slot = *vector_pop(m_free_slots);
		slot.m_probe = &probe;
		probe.m_atlas_index = slot.m_index;
		return slot.m_urect;
	}
}
