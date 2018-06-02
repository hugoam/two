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
module mud.gfx;
#else
#include <geom/Intersect.h>
#include <gfx/ManualRender.h>
#include <gfx/GfxSystem.h>
#include <gfx/Item.h>
#include <gfx/Scene.h>
#include <gfx/Mesh.h>
#include <gfx/Model.h>
#include <gfx/Shot.h>
#include <gfx-pbr/Shadow.h>
#endif

namespace mud
{
	std::vector<Item*> frustum_cull(Render& render, const Plane6& frustum_planes, std::function<bool(Item&)> filter)
	{
		std::vector<Item*> items;
		for(Item* item : render.m_shot->m_items)
			if(!filter || filter(*item))
			{
				if(frustum_aabb_intersection(frustum_planes, item->m_aabb))
					items.push_back(item);
			}
		return items;
	}

	ManualRender::ManualRender(Render& render, bgfx::FrameBufferHandle fbo, const uvec4& viewport_rect)
		: m_render(render)
		, m_camera()
		, m_viewport(m_camera, render.m_scene, viewport_rect)
		, m_shadow_render(m_viewport, fbo, render.m_frame)
	{}

	ManualRender::ManualRender(Render& render, bgfx::FrameBufferHandle fbo, const uvec4& viewport_rect, const mat4& transform, const mat4& projection)
		: m_render(render)
		, m_camera(transform, projection)
		, m_viewport(m_camera, render.m_scene, viewport_rect)
		, m_shadow_render(m_viewport, fbo, render.m_frame)
	{}

	void ManualRender::cull(Plane6* input_planes)
	{
		Plane6 planes = input_planes ? *input_planes : frustum_planes(m_camera.m_projection, m_camera.m_transform);

		auto filter = [](Item& item) { return item.m_visible && item.m_model->m_geometry[PLAIN] && item.m_cast_shadows != ItemShadow::Off; };
		m_shadow_render.m_shot->m_items = frustum_cull(m_render, planes, filter);

		for(Item* item : m_shadow_render.m_shot->m_items)
			item->m_depth = plane_distance_to(planes.m_near, item->m_node.m_position);
	}

	void ManualRender::render()
	{
		Renderer& renderer = m_render.m_scene.m_gfx_system.renderer<ShadowRenderer>();
		renderer.render(m_shadow_render);
		m_render.m_pass_index = m_shadow_render.m_pass_index;
	}
}
