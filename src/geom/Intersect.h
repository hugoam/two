//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <math/Vec.h>
#include <math/VecOps.h>
#endif
#include <geom/Forward.h>

namespace mud
{
	export_ MUD_GEOM_EXPORT vec3 circumcenter(const vec3& a, const vec3& b, const vec3& c);

	export_ MUD_GEOM_EXPORT bool segment_triangle_intersection(const vec3& sp, const vec3& sq, const vec3& a, const vec3& b, const vec3& c, float& t);
	export_ MUD_GEOM_EXPORT bool segment_aabb_intersection(const vec3& sp, const vec3& sq, const vec3& amin, const vec3& amax, float& tmin, float& tmax);
	export_ MUD_GEOM_EXPORT bool segment_aabb_intersection_2d(const vec2& p, const vec2& q, const vec2& bmin, const vec2& bmax);

	export_ MUD_GEOM_EXPORT bool ray_aabb_intersection(const vec3& min, const vec3& max, const Ray& R);
	export_ MUD_GEOM_EXPORT bool ray_aabb_intersection(const vec3& min, const vec3& max, const Ray& R, vec3& result);
	export_ MUD_GEOM_EXPORT bool line_circle_intersection(const vec3& l0, const vec3& l1, const vec3& c0, float r, vec3& r0, vec3& r1);
	export_ MUD_GEOM_EXPORT bool circle_circle_intersection(const vec3& c0, float r0, const vec3& c1, float r1, vec3& p1, vec3& p2);
	export_ MUD_GEOM_EXPORT vec3 plane_segment_intersection(const Plane& P, const Segment& S);
	export_ MUD_GEOM_EXPORT vec3 plane_segment_intersection(const vec3& N, float d, const vec3& L1, const vec3& L2);
	export_ MUD_GEOM_EXPORT vec3 plane_segment_intersection(const vec3& P1, const vec3& P2, const vec3& P3, const vec3& L1, const vec3& L2);
	export_ MUD_GEOM_EXPORT vec3 plane_3_intersection(const Plane& plane0, const Plane& plane1, const Plane& plane2);
	export_ MUD_GEOM_EXPORT bool frustum_aabb_intersection(const Plane6& planes, const Aabb& aabb);
	export_ MUD_GEOM_EXPORT bool sphere_aabb_intersection(const vec3& center, float radius, const Aabb& aabb);

	export_ MUD_GEOM_EXPORT vec3 nearest_point_on_face(const Face3& face, const vec3& point);
	export_ MUD_GEOM_EXPORT vec3 nearest_point_on_line(const vec3& origin, const vec3& dir, const vec3& point);

	inline vec4 sphere_plane_intersection(const vec3& sphere_position, float sphere_radius_squared, const vec3& plane_normal, float plane_d)
	{
		const float d = dot(sphere_position, plane_normal) + plane_d;
		const float rr = sphere_radius_squared - d * d;
		return { sphere_position - plane_normal * d, rr };
	}

	// this version returns a false-positive intersection in a small area near the origin of the cone extended outward by the sphere's radius.
	inline bool sphere_cone_intersection_fast(const vec3& sphere_position, float sphere_radius_squared, const vec3& cone_position, const vec3& cone_axis, float cone_sin_inverse, float cone_cos_squared)
	{
		const vec3 u = cone_position - (sphere_radius_squared * cone_sin_inverse) * cone_axis;
		vec3 d = sphere_position - u;
		float e = dot(cone_axis, d);
		float dd = dot(d, d);
		// we do the e>0 last here to avoid a branch
		return (e * e >= dd * cone_cos_squared && e > 0);
	}

	inline bool sphere_cone_intersection(const vec3& sphere_position, float sphere_radius_squared, const vec3& cone_position, const vec3& cone_axis, float cone_sin_inverse, float cone_cos_squared)
	{
		if(sphere_cone_intersection_fast(sphere_position, sphere_radius_squared, cone_position, cone_axis, cone_sin_inverse, cone_cos_squared))
		{
			vec3 d = sphere_position - cone_position;
			float e = -dot(cone_axis, d);
			float dd = dot(d, d);
			if(e * e >= dd * (1 - cone_cos_squared) && e > 0)
				return dd <= sphere_radius_squared * sphere_radius_squared;
			return true;
		}
		return false;
	}
}
