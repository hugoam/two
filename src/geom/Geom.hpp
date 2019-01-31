//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <math/Vec.hpp>
#endif
#include <geom/Forward.h>
#include <geom/Geom.h>

namespace mud
{
	inline float distance(const Plane& plane, const vec3& p)
	{
		return dot(plane.m_normal, p) - plane.m_distance;
	}

	inline vec3 project(const Plane& plane, const vec3& p)
	{
		return p - plane.m_normal * distance(plane, p);
	}	// Implementation

	inline Plane::Plane(const vec3& normal, float distance)
		: m_normal(normal), m_distance(distance)
	{}

	inline Plane::Plane(float a, float b, float c, float d)
		: m_normal(a, b, c), m_distance(d)
	{}

	inline Plane::Plane(const vec3& point, const vec3& normal)
		: m_normal(normal), m_distance(dot(normal, point))
	{}

	inline Plane::Plane(const vec3& p1, const vec3& p2, const vec3& p3, Clockwise dir)
		: m_normal(normalize(dir == CLOCKWISE ? cross(p1 - p3, p1 - p2)
											  : cross(p1 - p2, p1 - p3)))
		, m_distance(dot(m_normal, p1))
	{}

	inline Plane normalize(const Plane& plane)
	{
		float l = length(plane.m_normal);
		if(l == 0)
			return { Zero3, 0.f };
		return { plane.m_normal / l, plane.m_distance / l };
	}

	inline Ray to_ray(const vec3& pos, const vec3& dir, float distance) { return { pos, pos + dir * distance, dir, 1.f / dir }; };
	inline Segment to_segment(const Ray& ray) { return { ray.m_start, ray.m_end }; }

	inline Plane6::Plane6() {}
	inline Plane6::Plane6(Plane right, Plane left, Plane up, Plane down, Plane near, Plane far) : m_right(right), m_left(left), m_up(up), m_down(down), m_near(near), m_far(far) {}

	inline Point8::Point8() {}
	inline Point8::Point8(vec3 a, vec3 b, vec3 c, vec3 d, vec3 e, vec3 f, vec3 g, vec3 h) : m_a(a), m_b(b), m_c(c), m_d(d), m_e(e), m_f(f), m_g(g), m_h(h) {}
}
