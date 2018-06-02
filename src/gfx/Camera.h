//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Array.h>
#include <math/VecOps.h>
#include <geom/Geom.h>
#include <gfx/Generated/Forward.h>
#include <gfx/Node3.h>

namespace mud
{
	export_ enum _refl_ IsometricAngle : unsigned int
	{
		NORTH = (1 << 0),
		SOUTH = (2 << 0),
		EAST = (1 << 8),
		WEST = (2 << 8)
	};

	export_ class _refl_ MUD_GFX_EXPORT Camera
	{
	public:
		Camera(Scene* scene = nullptr);
		Camera(mat4 transform, mat4 projection);

		_attr_ Scene* m_scene = nullptr;
		_attr_ _mut_ Node3 m_node;
		_attr_ _mut_ Node3 m_target;

		_attr_ mat4 m_transform;
		_attr_ mat4 m_projection;

#if defined MUD_UNIFORM_BLOCKS
		_attr_ FrustumBlock m_frustum;
#endif
		_attr_ _mut_ float m_fov = 60.f;
		_attr_ _mut_ float m_aspect = 1.f;
		_attr_ _mut_ float m_near = 0.001f;
		_attr_ _mut_ float m_far = 100.f;

		_attr_ _mut_ bool m_orthogonal = false;
		_attr_ _mut_ float m_height = 1.f;

		_attr_ _mut_ bool m_optimize_ends = true;

		_attr_ _mut_ vec4 m_lod_offsets = { 0.1f, 0.3f, 0.6f, 0.8f };

		vec4 ortho_rect() { return { -m_height / 2.f * m_aspect, m_height / 2.f * m_aspect, -m_height / 2.f, m_height / 2.f }; };

		void update();

		void set_look_at(const vec3& eye, const vec3& target);
		void set_isometric(IsometricAngle angle, const vec3& position);

		Plane near_plane();
		Plane far_plane();

		mat4 projection(float near, float far, bool ndc = false);

		Ray ray(const vec2& offset);
	};
}
