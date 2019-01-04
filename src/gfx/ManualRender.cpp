//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

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
#include <gfx/Frustum.h>
#endif

namespace mud
{
	ManualRender::ManualRender(Render& render, Shading shading, bgfx::FrameBufferHandle fbo, const uvec4& viewport_rect)
		: m_render(render)
		, m_camera()
		, m_viewport(m_camera, render.m_scene, viewport_rect)
		, m_sub_render(shading, m_viewport, fbo, render.m_frame)
	{
		m_sub_render.m_shot->m_lights = m_render.m_shot->m_lights;
	}

	ManualRender::ManualRender(Render& render, Shading shading, bgfx::FrameBufferHandle fbo, const uvec4& viewport_rect, const mat4& transform, const mat4& projection, bool ortho)
		: m_render(render)
		, m_camera(transform, projection, ortho)
		, m_viewport(m_camera, render.m_scene, viewport_rect)
		, m_sub_render(shading, m_viewport, fbo, render.m_frame)
	{
		m_sub_render.m_shot->m_lights = m_render.m_shot->m_lights;
	}

	void ManualRender::render(Renderer& renderer)
	{
		renderer.render(m_sub_render);
		m_render.m_pass_index = m_sub_render.m_pass_index;
	}
}
