

#pragma once

#include <gfx/Forward.h>
#include <gfx/Renderer.h>
#include <gfx/Viewport.h>
#include <gfx/Camera.h>
#include <gfx/Material.h>

namespace mud
{
	export_ struct MUD_GFX_EXPORT ManualRender
	{
		ManualRender(Render& render, Shading shading, FrameBuffer& fbo, const uvec4& viewport_rect);
		ManualRender(Render& render, Shading shading, FrameBuffer& fbo, const uvec4& viewport_rect, const mat4& transform, const mat4& projection, bool ortho = false);

		void render(Renderer& renderer, RenderFunc func);

		Render& m_render;
		Camera m_camera;
		Viewport m_viewport;
		Render m_sub_render;
	};
}
