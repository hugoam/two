//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/function.h>
#include <math/Vec.h>
#include <math/Colour.h>
#include <ecs/Entity.h>
#endif
#include <gfx/Forward.h>
#include <gfx/Renderer.h>
#include <gfx/Culling.h>

namespace mud
{
	using cstring = const char*;

	export_ enum class refl_ MSAA : unsigned int
	{
		Disabled,
		X2,
		X4,
		X8,
		X16,
		Count
	};

	export_ enum class refl_ Shading : unsigned int
	{
		Wireframe,
		Solid,
		Shaded,
		Volume,
		Voxels,
		Lightmap,
		Clear,

		Count
	};

	export_ extern MUD_GFX_EXPORT GridECS* g_viewer_ecs;

	export_ class refl_ MUD_GFX_EXPORT Viewport : public Entt
	{
	public:
		Viewport(Camera& camera, Scene& scene, uvec4 rect = {}, bool scissor = false);
		~Viewport();

		attr_ Camera* m_camera;
		attr_ Scene* m_scene;

		attr_ uint16_t m_index = 0;
		attr_ bool m_active = true;
		attr_ uvec4 m_rect = uvec4(0U);
		attr_ bool m_scissor = false;
		attr_ Colour m_clear_colour = Colour::Black;
		attr_ Shading m_shading = Shading::Shaded;
		attr_ Lighting m_lighting = Lighting::Clustered;

		using RenderTask = function<void(Render&)>;
		vector<RenderTask> m_tasks;
		
		Culler m_culler;

		void render_pass(cstring name, const Pass& render_pass);

		void cull(Render& render);
		void render(Render& render);

		Ray ray(const vec2& pos);
		vec3 raycast(const Plane& plane, const vec2& pos);
	};
}
