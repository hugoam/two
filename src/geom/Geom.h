//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <math/Vec.h>
#include <math/Math.h>
#include <math/Colour.h>
#endif
#include <geom/Forward.h>

namespace mud
{
	export_ MUD_GEOM_EXPORT Aabb transform_aabb(const Aabb& source, const mat4& transform);
	export_ MUD_GEOM_EXPORT Aabb translate_aabb(const Aabb& source, const vec3& offset);
	export_ MUD_GEOM_EXPORT vec2 project_aabb_in_plane(const Plane& plane, const Aabb& aabb);

	export_ extern MUD_GEOM_EXPORT const float c_cmp_epsilon;
	export_ extern MUD_GEOM_EXPORT const float c_cmp_epsilon2;

	export_ struct refl_ Plane
	{
		attr_ vec3 m_normal;
		attr_ float m_distance;

		Plane(const vec3& normal = Zero3, float distance = 0.f);
		Plane(float a, float b, float c, float d);
		Plane(const vec3& point, const vec3& normal);
		Plane(const vec3& p1, const vec3& p2, const vec3& p3, Clockwise dir = ANTI_CLOCKWISE);
	};

	export_ struct refl_ Plane3
	{
		attr_ vec3 m_origin;
		attr_ vec3 m_a;
		attr_ vec3 m_b;
	};

	export_ struct refl_ Face3
	{
		vec3 m_vertices[3];

		Face3() {}
		Face3(const vec3& a, const vec3& b, const vec3& c) : m_vertices{ a, b, c } {}

		Face3& operator=(const Face3& other) = default; // @kludge: might be a clang modules bug ?
	};

	export_ inline float distance(const Plane& plane, const vec3& p)
	{
		return dot(plane.m_normal, p) - plane.m_distance;
	}

	export_ inline vec3 project(const Plane& plane, const vec3& p)
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

	export_ inline Plane normalize(const Plane& plane)
	{
		float l = length(plane.m_normal);
		if(l == 0)
			return { Zero3, 0.f };
		return { plane.m_normal / l, plane.m_distance / l };
	}

	export_ struct refl_ Segment
	{
		attr_ vec3 m_start;
		attr_ vec3 m_end;
	};

	export_ struct refl_ Ray
	{
		attr_ vec3 m_start;
		attr_ vec3 m_end;
		attr_ vec3 m_dir;
		attr_ vec3 m_inv_dir;
	};

	export_ func_ inline Ray to_ray(const vec3& pos, const vec3& dir, float distance = 1000.f) { return { pos, pos + dir * distance, dir, 1.f / dir }; };
	export_ func_ inline Segment to_segment(const Ray& ray) { return { ray.m_start, ray.m_end }; }

	export_ struct Plane6
	{
		Plane6() {}
		Plane6(Plane right, Plane left, Plane up, Plane down, Plane near, Plane far) : m_right(right), m_left(left), m_up(up), m_down(down), m_near(near), m_far(far) {}
		const Plane& operator[](size_t index) const { return *((Plane*)&m_right + index); }
		Plane& operator[](size_t index) { return *((Plane*)&m_right + index); }
		Plane m_right, m_left, m_up, m_down, m_near, m_far;
	};

	export_ struct Point8
	{
		Point8() {}
		Point8(vec3 a, vec3 b, vec3 c, vec3 d, vec3 e, vec3 f, vec3 g, vec3 h) : m_a(a), m_b(b), m_c(c), m_d(d), m_e(e), m_f(f), m_g(g), m_h(h) {}
		const vec3& operator[](size_t index) const { return *((vec3*)&m_a + index); }
		vec3& operator[](size_t index) { return *(&m_a + index); }
		vec3 m_a, m_b, m_c, m_d, m_e, m_f, m_g, m_h;
	};
}
