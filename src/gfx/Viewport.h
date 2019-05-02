//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <stl/function.h>
#include <math/Vec.h>
#include <math/Colour.h>
#include <ecs/Entity.h>
#endif
#include <gfx/Forward.h>
#include <gfx/Renderer.h>
#include <gfx/Culling.h>
#include <gfx/Froxel.h>

namespace two
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

	export_ extern TWO_GFX_EXPORT GridECS* g_viewer_ecs;

	export_ class refl_ TWO_GFX_EXPORT Viewport : public OEntt
	{
	public:
		constr_ Viewport() {}
		constr_ Viewport(Camera& camera, Scene& scene, const vec4& rect = vec4(0.f), bool scissor = false);
		~Viewport();

		Viewport(Viewport&& other) = default;
		Viewport& operator=(Viewport&& other) = default;

		attr_ Camera* m_camera;
		attr_ Scene* m_scene;

		attr_ uint16_t m_index = 0;
		attr_ bool m_autorender = true;
		attr_ vec4 m_rect = vec4(0.f);
		attr_ bool m_scissor = false;
		attr_ Colour m_clear_colour = Colour::Black;
		attr_ Shading m_shading = Shading::Shaded;
		attr_ Lighting m_lighting = Lighting::Clustered;
		attr_ bool m_clustered = false;
		attr_ bool m_to_gamma = false;

		using RenderTask = function<void(Render&)>;
		vector<RenderTask> m_tasks;
		
		unique<Culler> m_culler;

		unique<Froxelizer> m_clusters;

		void pass(const Pass& pass);

		meth_ void cull(Render& render);
		meth_ void render(Render& render);

		meth_ void set_clustered(GfxSystem& gfx);

		Ray ray(const vec2& pos);
		vec3 raycast(const Plane& plane, const vec2& pos);
	};
}
