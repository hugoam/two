//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx-pbr/Forward.h>

namespace two
{
	export_ class refl_ TWO_GFX_PBR_EXPORT CubeTarget
	{
	public:
		constr_ CubeTarget() {}
		meth_ void create(uint32_t size);
		meth_ FrameBuffer& side(size_t i) { return m_fbos[i]; }
		FrameBuffer m_fbos[6]; // @todo reflect array members
		attr_ Texture m_cubemap;
		attr_ Texture m_depth;
		attr_ uint32_t m_size;
	};

	export_ class refl_ TWO_GFX_PBR_EXPORT CubeCamera
	{
	public:
		constr_ CubeCamera() {}
		constr_ CubeCamera(Scene& scene, float near, float far, uint32_t size);

		Camera m_cameras[6];
		Viewport m_viewports[6];

		attr_ CubeTarget m_cubemap;
		attr_ uvec2 m_size;

		meth_ Render render(GfxSystem& gfx, Render& render, SignedAxis axis);

		void render(GfxSystem& gfx, Render& render, RenderFunc renderer);
		void clear(GfxSystem& gfx, Render& render, Colour color, float depth, uint8_t stencil);
	};

	export_ class TWO_GFX_PBR_EXPORT ReflectionAtlas
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
			uint32_t m_last_update;
		};

		vector<Slot> m_slots;
		vector<Slot*> m_free_slots;
	};
}
