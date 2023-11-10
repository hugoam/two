//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <math/Vec.h>
#include <math/Colour.h>
#endif
#include <geom/Forward.h>

namespace two
{
	export_ TWO_GEOM_EXPORT Aabb transform_aabb(const Aabb& source, const mat4& transform);
	export_ TWO_GEOM_EXPORT Aabb translate_aabb(const Aabb& source, const vec3& offset);
	export_ TWO_GEOM_EXPORT vec2 project_aabb_in_plane(const Plane& plane, const Aabb& aabb);

	export_ constexpr inline float c_cmp_epsilon = 0.00001f;
	export_ constexpr inline float c_cmp_epsilon2 = c_cmp_epsilon * c_cmp_epsilon;

	export_ struct refl_ Plane
	{
		attr_ vec3 m_normal;
		attr_ float m_distance;

		Plane(const vec3& normal = vec3(0.f), float distance = 0.f);
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

	export_ inline float distance(const Plane& plane, const vec3& p);
	export_ inline vec3 project(const Plane& plane, const vec3& p);
	export_ inline Plane operator*(const mat4& mat, const Plane& p);

	export_ inline Plane normalize(const Plane& plane);

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

	export_ func_ inline Ray to_ray(const vec3& pos, const vec3& dir, float distance = 1000.f);
	export_ func_ inline Segment to_segment(const Ray& ray);

	export_ struct Plane6
	{
		Plane6();
		Plane6(Plane right, Plane left, Plane up, Plane down, Plane near, Plane far);
		const Plane& operator[](size_t index) const { return *((Plane*)&m_right + index); }
		Plane& operator[](size_t index) { return *((Plane*)&m_right + index); }
		Plane m_right, m_left, m_up, m_down, m_near, m_far;
	};

	export_ struct Point8
	{
		Point8();
		Point8(vec3 a, vec3 b, vec3 c, vec3 d, vec3 e, vec3 f, vec3 g, vec3 h);
		const vec3& operator[](size_t index) const { return *((vec3*)&m_a + index); }
		vec3& operator[](size_t index) { return *(&m_a + index); }
		vec3 m_a, m_b, m_c, m_d, m_e, m_f, g, m_h;
	};
}
