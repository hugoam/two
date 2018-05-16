//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Vec.h>
#include <math/Colour.h>
#include <gfx/Generated/Forward.h>

#include <functional>

namespace mud
{
	using cstring = const char*;

	enum class _refl_ MSAA : unsigned int
	{
		Disabled,
		X2,
		X4,
		X8,
		X16,
	};

	enum class _refl_ Shading : unsigned int
	{
		Wireframe,
		Unshaded,
		Shaded
	};

	class _refl_ MUD_GFX_EXPORT Viewport
	{
	public:
		Viewport(Camera& camera, Scene& scene, uvec4 rect = {}, bool scissor = false);

		_attr_ Camera* m_camera;
		_attr_ Scene* m_scene;

		_attr_ uint16_t m_index = 0;
		_attr_ _mut_ uvec4 m_rect = {};
		_attr_ _mut_ bool m_scissor = false;
		_attr_ _mut_ Colour m_clear_colour = Colour::Black;
		_attr_ _mut_ Shading m_shading = Shading::Shaded;
		_attr_ _mut_ RenderFilters* m_filters = nullptr;

		std::function<uvec4()> m_get_size;
		std::function<void(Render&)> m_render;

		void render_pass(cstring name, const Pass& render_pass);

		void render(Render& render);

		Ray ray(const vec2& pos);
		vec3 raycast(const Plane& plane, const vec2& pos);
	};
}
