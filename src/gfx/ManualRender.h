

#pragma once

#include <gfx/Generated/Forward.h>
#include <gfx/Renderer.h>
#include <gfx/Viewport.h>
#include <gfx/Camera.h>
#include <gfx/Material.h>

namespace mud
{
	struct ManualRender
	{
		ManualRender(Render& render, bgfx::FrameBufferHandle fbo, const uvec4& viewport_rect);
		ManualRender(Render& render, bgfx::FrameBufferHandle fbo, const uvec4& viewport_rect, const mat4& transform, const mat4& projection);

		void cull(Plane6* input_planes = nullptr);
		void render();

		Render& m_render;
		Camera m_camera;
		Viewport m_viewport;
		Render m_shadow_render;
	};
}
