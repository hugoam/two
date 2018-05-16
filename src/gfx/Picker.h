//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Array.h>
#include <geom/Geom.h>
#include <gfx/Generated/Forward.h>

#ifndef MUD_GENERATOR_SKIP_INCLUDES
#include <bgfx/bgfx.h>
#endif

#include <vector>
#include <functional>

namespace mud
{
#define PICKING_BUFFER_SIZE 8  // Size of the ID buffer

	struct PickQuery
	{
		PickQuery() {}
		PickQuery(uvec4 rect, Ray ray, float fov, float aspect, uint32_t mask)
			: m_rect(rect), m_center_ray(ray), m_fov(fov), m_aspect(aspect), m_mask(mask)
		{}

		uvec4 m_rect = uvec4(0U);
		Ray m_center_ray = {};
		float m_fov = 0.f;
		float m_aspect = 0.f;
		uint32_t m_mask = UINT32_MAX;

		uint32_t m_readback_ready = UINT32_MAX;

		std::function<void(Item*)> m_callback;
		std::function<void(array<Item*>)> m_multi_callback;

		operator bool() const { return m_rect != uvec4(0U); }
	};

	class MUD_GFX_EXPORT Picker
	{
	public:
		Picker(GfxSystem& system, FrameBuffer& target);
		~Picker();

		void process(Render& render, PickQuery& query);

		FrameBuffer& m_target;
		uvec2 m_size;

		PickQuery m_query;

		bgfx::ProgramHandle m_program;
		bgfx::UniformHandle u_picking_id;

		bgfx::TextureHandle m_readback_texture;
		bgfx::FrameBufferHandle m_fbo;
		bgfx::TextureHandle m_fbo_texture;

		std::vector<uint32_t> m_data;
	};
}
