//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/function.h>
#include <stl/vector.h>
#include <stl/span.h>
#include <geom/Geom.h>
#endif
#include <gfx/Forward.h>

#include <bgfx/bgfx.h>

namespace mud
{
#define PICKING_BUFFER_SIZE 8  // Size of the ID buffer

	using PickCallback = function<void(Item*)>;
	using MultipickCallback = function<void(span<Item*>)>;

	export_ struct PickQuery
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

		PickCallback m_callback;
		MultipickCallback m_multi_callback;

		operator bool() const { return m_rect != uvec4(0U); }
	};

	export_ class MUD_GFX_EXPORT Picker
	{
	public:
		Picker(GfxSystem& system, FrameBuffer& target);
		~Picker();

		void pick_point(Viewport& viewport, vec2 position, PickCallback callback, uint32_t mask);
		void pick_rectangle(Viewport& viewport, vec4 rect, MultipickCallback callback, uint32_t mask);

		void process(Render& render, PickQuery& query);

		FrameBuffer& m_target;
		uvec2 m_size;

		Program& m_program;

		PickQuery m_query;

		bgfx::UniformHandle u_picking_id;

		bgfx::FrameBufferHandle m_fbo;
		bgfx::TextureHandle m_fbo_texture;

		bgfx::TextureHandle m_readback_texture = BGFX_INVALID_HANDLE;

		vector<uint32_t> m_data;
	};
}
