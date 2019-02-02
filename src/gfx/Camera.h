//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <infra/Array.h>
#include <infra/NonCopy.h>
#include <type/Unique.h>
#include <math/Vec.h>
#include <geom/Geom.h>
#endif
#include <gfx/Forward.h>
#include <gfx/Node3.h>

namespace mud
{
	export_ enum refl_ IsometricAngle : unsigned int
	{
		NORTH = (1 << 0),
		SOUTH = (2 << 0),
		EAST = (1 << 8),
		WEST = (2 << 8)
	};

	export_ class refl_ MUD_GFX_EXPORT Camera : public NonCopy
	{
	public:
		Camera();
		Camera(mat4 transform, mat4 projection, bool ortho = false);
		Camera(mat4 transform, float fov, float aspect, float near, float far);
		Camera(mat4 transform, vec2 rect, float near, float far);
		~Camera();

		attr_ vec3 m_eye;
		attr_ vec3 m_target;

		attr_ mat4 m_transform;
		attr_ mat4 m_projection;

#if defined MUD_UNIFORM_BLOCKS
		attr_ FrustumBlock m_frustum;
#endif
		attr_ float m_fov = 60.f;
		attr_ float m_aspect = 1.f;
		attr_ float m_near = 0.1f;
		attr_ float m_far = 100.f;

		attr_ bool m_orthographic = false;
		attr_ float m_height = 1.f;

		attr_ bool m_optimize_ends = true;
		attr_ bool m_clustered = false;

		attr_ vec4 m_lod_offsets = { 0.1f, 0.3f, 0.6f, 0.8f };

		void update();

		void set_look_at(const vec3& eye, const vec3& target);
		void set_isometric(IsometricAngle angle, const vec3& position);

		Plane near_plane() const;
		Plane far_plane() const;

		mat4 projection(float near, float far, bool ndc = false);

		Ray ray(const vec2& offset) const;

		unique<Froxelizer> m_clusters;
	};
}
