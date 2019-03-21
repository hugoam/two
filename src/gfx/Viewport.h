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
#include <gfx/Froxel.h>

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

	export_ class refl_ MUD_GFX_EXPORT Viewport : public OEntt
	{
	public:
		Viewport() {}
		Viewport(Camera& camera, Scene& scene, uvec4 rect = uvec4(0U), bool scissor = false);
		~Viewport();

		Viewport(Viewport&& other) = default;
		Viewport& operator=(Viewport&& other) = default;

		attr_ Camera* m_camera;
		attr_ Scene* m_scene;

		attr_ uint16_t m_index = 0;
		attr_ bool m_active = true;
		attr_ uvec4 m_rect = uvec4(0U);
		attr_ bool m_scissor = false;
		attr_ Colour m_clear_colour = Colour::Black;
		attr_ Shading m_shading = Shading::Shaded;
		attr_ Lighting m_lighting = Lighting::Clustered;
		attr_ bool m_clustered = false;

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
