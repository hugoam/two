//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <math/Vec.h>
#include <math/Colour.h>
#endif
#include <gfx/Forward.h>

#ifndef MUD_CPP_20
#include <functional>
#endif

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
	};

	export_ enum class refl_ Shading : unsigned int
	{
		Wireframe,
		Unshaded,
		Shaded,
		Volume,
		Clear
	};

	struct RenderFilters;

	export_ class refl_ MUD_GFX_EXPORT Viewport
	{
	public:
		Viewport(Camera& camera, Scene& scene, uvec4 rect = {}, bool scissor = false);

		attr_ Camera* m_camera;
		attr_ Scene* m_scene;

		attr_ uint16_t m_index = 0;
		attr_ mut_ uvec4 m_rect = {};
		attr_ mut_ bool m_scissor = false;
		attr_ mut_ Colour m_clear_colour = Colour::Black;
		attr_ mut_ Shading m_shading = Shading::Shaded;
		/*attr_ mut_*/ RenderFilters* m_filters = nullptr;

		std::function<uvec4()> m_get_size;
		std::function<void(Render&)> m_render;

		void render_pass(cstring name, const Pass& render_pass);

		void render(Render& render);

		Ray ray(const vec2& pos);
		vec3 raycast(const Plane& plane, const vec2& pos);
	};
}
