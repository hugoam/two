//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <gfx/Cpp20.h>
module two.gfx.pbr;

namespace two
{
	ReflectionAtlas::ReflectionAtlas(uint16_t size, uint16_t subdiv)
		: m_size(size)
		, m_subdiv(subdiv)
	{
		// TODO(hugoam) TextureSampler::ReflectionProbe collides with TextureSampler::Clusters
#if 0 // @todo: crashes in D3D11
		TextureFormat color_format = TextureFormat::RGBA16F;

		if(!bgfx::isTextureValid(0, true, 1, bgfx::TextureFormat::Enum(color_format), TEXTURE_CLAMP))
			color_format = TextureFormat::RGB10A2;

		m_color = { uvec2(uint(size)), true, color_format, BGFX_TEXTURE_RT | TEXTURE_CLAMP, true };

		for(int i = 0; i < 6; i++)
		{
			bgfx::Attachment attachment = { bgfx::Access::Write, m_color, 0, uint16_t(i), 1, BGFX_RESOLVE_AUTO_GEN_MIPS };
			m_fbo[i] = { uvec2(uint(size)), m_color, span<bgfx::Attachment>{ attachment } };
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
#if 0
		for(int i = 0; i < 6; i++)
			bgfx::destroy(m_fbo[i]);
		bgfx::destroy(m_color);
#endif
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

		Slot& slot = *pop(m_free_slots);
		slot.m_probe = &probe;
		probe.m_atlas_index = int(slot.m_index);
		return slot.m_urect;
	}
}
