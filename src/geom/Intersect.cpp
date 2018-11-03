//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.geom;
#else
#include <math/Clamp.h>
#include <math/Axes.h>
#include <geom/Types.h>
#include <geom/Intersect.h>
#include <geom/Shapes.h>
#include <geom/Geom.h>
#include <geom/Aabb.h>
#endif

namespace mud
{
	// using std::clamp;

	const float c_cmp_epsilon = 0.00001f;
	const float c_cmp_epsilon2 = c_cmp_epsilon * c_cmp_epsilon;

	float ray_aabb_intersection_dist(const vec3& bmin, const vec3& bmax, const Ray& ray)
	{
		const vec3 t1 = (bmin - ray.m_start) * ray.m_inv_dir;
		const vec3 t2 = (bmax - ray.m_start) * ray.m_inv_dir;

		float tmin = max(max(min(t1.x, t2.x), min(t1.y, t2.y)), min(t1.z, t2.z));
		float tmax = min(min(max(t1.x, t2.x), max(t1.y, t2.y)), max(t1.z, t2.z));

		return tmax >= tmin ? tmin : 0.f;
	}

	bool ray_aabb_intersection(const vec3& bmin, const vec3& bmax, const Ray& ray)
	{
		return ray_aabb_intersection_dist(bmin, bmax, ray) > 0.f;
	}

	bool ray_aabb_intersection(const vec3& bmin, const vec3& bmax, const Ray& ray, vec3& result)
	{
		float dist = ray_aabb_intersection_dist(bmin, bmax, ray);
		if(dist > 0.f)
			result = ray.m_start + ray.m_dir * dist;
		return dist > 0.f;
	}

	bool segment_triangle_intersection(const vec3& sp, const vec3& sq, const vec3& a, const vec3& b, const vec3& c, float& t)
	{
		vec3 ab = b - a;
		vec3 ac = c - a;
		vec3 qp = sp - sq;

		// Compute triangle normal. Can be precalculated or cached if
		// intersecting multiple segments against the same triangle
		vec3 norm = cross(ab, ac);

		// Compute denominator d. If d <= 0, segment is parallel to or points
		// away from triangle, so exit early
		float d = dot(qp, norm);
		if(d <= 0.0f) return false;

		// Compute intersection t value of pq with plane of triangle. A ray
		// intersects iff 0 <= t. Segment intersects iff 0 <= t <= 1. Delay
		// dividing by d until intersection has been found to pierce triangle
		vec3 ap = sp - a;
		t = dot(ap, norm);
		if(t < 0.0f) return false;
		if(t > d) return false; // For segment; exclude this code line for a ray test

								// Compute barycentric coordinate components and test if within bounds
		vec3 e = cross(qp, ap);
		float v = dot(ac, e);
		if(v < 0.0f || v > d) return false;
		float w = -dot(ab, e);
		if(w < 0.0f || v + w > d) return false;

		// Segment/ray intersects triangle. Perform delayed division
		t /= d;

		return true;
	}

	bool segment_aabb_intersection(const vec3& sp, const vec3& sq, const vec3& amin, const vec3& amax, float& tmin, float& tmax)
	{
		static const float EPS = 1e-6f;

		vec3 d = sq - sp;
		tmin = 0.0;
		tmax = 1.0f;

		for(int i = 0; i < 3; i++)
		{
			if(fabsf(d[i]) < EPS)
			{
				if(sp[i] < amin[i] || sp[i] > amax[i])
					return false;
			}
			else
			{
				const float ood = 1.0f / d[i];
				float t1 = (amin[i] - sp[i]) * ood;
				float t2 = (amax[i] - sp[i]) * ood;
				if(t1 > t2) std::swap(t1, t2);
				if(t1 > tmin) tmin = t1;
				if(t2 < tmax) tmax = t2;
				if(tmin > tmax) return false;
			}
		}

		return true;
	}

	bool segment_aabb_intersection_2d(const vec2& p, const vec2& q, const vec2& bmin, const vec2& bmax)
	{
		static const float EPSILON = 1e-6f;

		float tmin = 0;
		float tmax = 1;
		vec2 d = q - p;

		for(int i = 0; i < 2; i++)
		{
			if(fabsf(d[i]) < EPSILON)
			{
				// Ray is parallel to slab. No hit if origin not within slab
				if(p[i] < bmin[i] || p[i] > bmax[i])
					return false;
			}
			else
			{
				// Compute intersection t value of ray with near and far plane of slab
				float ood = 1.0f / d[i];
				float t1 = (bmin[i] - p[i]) * ood;
				float t2 = (bmax[i] - p[i]) * ood;
				if(t1 > t2) std::swap(t1, t2);
				if(t1 > tmin) tmin = t1;
				if(t2 < tmax) tmax = t2;
				if(tmin > tmax) return false;
			}
		}
		return true;
	}

	bool line_circle_intersection(const vec3& l0, const vec3& l1, const vec3& c0, float r, vec3& r0, vec3& r1)
	{
		UNUSED(r1);

		vec3 d = l1 - l0; // FlowAxis vector of ray, from start to end
		vec3 f = l0 - c0; // Vector from center sphere to ray start

		float a = dot(d, d);
		float b = dot(f * 2.f, d) ;
		float c = dot(f, f) - r*r ;

		float discriminant = b*b-4*a*c;
		if(discriminant < 0)
		{
		  // no intersection
			return false;
		}
		else
		{
		  // ray didn't totally miss sphere,
		  // so there is a solution to
		  // the equation.

		  discriminant = sqrt(discriminant);

		  // either solution may be on or off the ray so need to test both
		  // t1 is always the smaller value, because BOTH discriminant and
		  // a are nonnegative.
		  float t1 = (-b - discriminant)/(2*a);
		  float t2 = (-b + discriminant)/(2*a);

		  // 3x HIT cases:
		  //          -o->             --|-->  |            |  --|->
		  // Impale(t1 hit,t2 hit), Poke(t1 hit,t2>1), ExitWound(t1<0, t2 hit), 

		  // 3x MISS cases:
		  //       ->  o                     o ->              | -> |
		  // FallShort (t1>1,t2>1), Past (t1<0,t2<0), CompletelyInside(t1<0, t2>1)

		  if( t1 >= 0 && t1 <= 1 )
		  {
			// t1 is the intersection, and it's closer than t2
			// (since t1 uses -b - discriminant)
			// Impale, Poke
			r0 = l0;
			r0 += d * t1; 
			return true;
		  }

		  // here t1 didn't intersect so we are either started
		  // inside the sphere or completely past it
		  if( t2 >= 0 && t2 <= 1 )
		  {
			// ExitWound
			r0 = l0;
			r0 += d * t2;
			return true;
		  }

		  // no intn: FallShort, Past, CompletelyInside
		  return false;
		}
	}

	bool circle_circle_intersection(	const vec3& c0, float r0,
										const vec3& c1, float r1,
										vec3& p1,
										vec3& p2	)
	{
		float a, dx, dy, d, h, rx, ry;
		float x2, y2;

		/* dx and dy are the vertical and horizontal distances between
		* the circle centers.
		*/
		dx = c1.x - c0.x;
		dy = c1.z - c0.z;

		/* Determine the straight-line distance between the centers. */
		//d = sqrt((dy*dy) + (dx*dx));
		d = hypot(dx,dy); // Suggested by Keith Briggs

		/* Check for solvability. */
		if (d > (r0 + r1))
		{
			/* no solution. circles do not intersect. */
			return false;
		}
		if (d < fabs(r0 - r1))
		{
			/* no solution. one circle is contained in the other */
			return false;
		}

		/* 'point 2' is the point where the line through the circle
		* intersection points crosses the line between the circle
		* centers.  
		*/

		/* Determine the distance from point 0 to point 2. */
		a = ((r0*r0) - (r1*r1) + (d*d)) / (2.f * d) ;

		/* Determine the coordinates of point 2. */
		x2 = c0.x + (dx * a/d);
		y2 = c0.z + (dy * a/d);

		/* Determine the distance from point 2 to either of the
		* intersection points.
		*/
		h = sqrt((r0*r0) - (a*a));

		/* Now determine the offsets of the intersection points from
		* point 2.
		*/
		rx = -dy * (h/d);
		ry = dx * (h/d);

		/* Determine the absolute intersection points. */
		p1.x = x2 + rx;
		p2.x = x2 - rx;
		p1.z = y2 + ry;
		p2.z = y2 - ry;

		return true;
	}

	vec3 plane_segment_intersection(const Plane& P, const Segment& S)
	{
		return plane_segment_intersection(P.m_normal, P.m_distance, S.m_start, S.m_end);
	}

	vec3 plane_segment_intersection(const vec3& N, float d, const vec3& L1, const vec3& L2)
	{
		vec3 P = N * d;
		vec3 result = L1 + (dot(N, P - L1) / dot(N, L2 - L1)) * (L2 - L1);
		if(any(isnan(result)) || any(isinf(result)))
			return Zero3; // @todo move to optional when C++17
		return result;
	}

	vec3 plane_segment_intersection(const vec3& P1, const vec3& P2, const vec3& P3, const vec3& L1, const vec3& L2)
	{
		vec3 N = cross(P2 - P1, P3 - P1);
		vec3 result = L1 + (dot(N, P1 - L1) / dot(N, L2 - L1)) * (L2 - L1);
		if(any(isnan(result)) || any(isinf(result)))
			return Zero3; // @todo move to optional when C++17
		return result;
	}

	vec3 plane_3_intersection(const Plane& plane0, const Plane& plane1, const Plane& plane2)
	{
		vec3 normal0 = plane0.m_normal;
		vec3 normal1 = plane1.m_normal;
		vec3 normal2 = plane2.m_normal;

		float denom = dot(cross(normal0, normal1), normal2);

		if(std::abs(denom) <= c_cmp_epsilon)
			return Zero3; // @todo move to optional when C++17

		return ((cross(normal1, normal2) * plane0.m_distance) +
				(cross(normal2, normal0) * plane1.m_distance) +
				(cross(normal0, normal1) * plane2.m_distance)) / denom;
	}

	vec3 nearest_point_on_line(const vec3& origin, const vec3& dir, const vec3& point)
	{
		vec3 vec = point - origin;
		float d = dot(vec, dir);
		return origin + dir * d;
	}

	vec3 nearest_point_on_face(const Face3& face, const vec3& point)
	{
		vec3 edge0 = face.m_vertices[1] - face.m_vertices[0];
		vec3 edge1 = face.m_vertices[2] - face.m_vertices[0];
		vec3 v0 = face.m_vertices[0] - point;

		float a = dot(edge0, edge0);
		float b = dot(edge0, edge1);
		float c = dot(edge1, edge1);
		float d = dot(edge0, v0);
		float e = dot(edge1, v0);

		float det = a * c - b * b;
		float s = b * e - c * d;
		float t = b * d - a * e;

		if(s + t < det)
		{
			if(s < 0.f)
			{
				if(t < 0.f)
				{
					if(d < 0.f)
					{
						s = clamp(-d / a, 0.f, 1.f);
						t = 0.f;
					}
					else
					{
						s = 0.f;
						t = clamp(-e / c, 0.f, 1.f);
					}
				}
				else
				{
					s = 0.f;
					t = clamp(-e / c, 0.f, 1.f);
				}
			}
			else if(t < 0.f)
			{
				s = clamp(-d / a, 0.f, 1.f);
				t = 0.f;
			}
			else
			{
				float invDet = 1.f / det;
				s *= invDet;
				t *= invDet;
			}
		}
		else
		{
			if(s < 0.f)
			{
				float tmp0 = b + d;
				float tmp1 = c + e;
				if(tmp1 > tmp0)
				{
					float numer = tmp1 - tmp0;
					float denom = a - 2 * b + c;
					s = clamp(numer / denom, 0.f, 1.f);
					t = 1 - s;
				}
				else
				{
					t = clamp(-e / c, 0.f, 1.f);
					s = 0.f;
				}
			}
			else if(t < 0.f)
			{
				if(a + d > b + e)
				{
					float numer = c + e - b - d;
					float denom = a - 2 * b + c;
					s = clamp(numer / denom, 0.f, 1.f);
					t = 1 - s;
				}
				else
				{
					s = clamp(-e / c, 0.f, 1.f);
					t = 0.f;
				}
			}
			else
			{
				float numer = c + e - b - d;
				float denom = a - 2 * b + c;
				s = clamp(numer / denom, 0.f, 1.f);
				t = 1.f - s;
			}
		}

		return face.m_vertices[0] + edge0 * s + edge1 * t;
	}

	Aabb transform_aabb(const Aabb& source, const mat4& transform)
	{
		vec3 center = vec3(transform * vec4{ source.m_center, 1.f });
		vec3 extent = vec3(abs(transform) * vec4 { source.m_extents, 0.f });

		return Aabb(center, extent);
	}

	Aabb translate_aabb(const Aabb& source, const vec3& offset)
	{
		Aabb result = source;
		result.m_center += offset;
		return result;
	}

	vec2 project_aabb_in_plane(const Plane& plane, const Aabb& aabb)
	{
		float length = dot(abs(plane.m_normal), aabb.m_extents);
		float dist = distance(plane, aabb.m_center);
		return { dist - length, dist + length };
	}

	bool frustum_aabb_intersection(const Plane6& planes, const Aabb& aabb)
	{
		vec3 bounds[2] = { aabb.m_center - aabb.m_extents, aabb.m_center + aabb.m_extents };

		for(uint i = 0; i < 6; ++i)
		{
			// our frustum normals are inverted somehow (normal faces outward whereas this algo needs it to be inward)
			vec3 normal = -planes[i].m_normal;

			const size_t px = size_t(normal.x > 0.0f);
			const size_t py = size_t(normal.y > 0.0f);
			const size_t pz = size_t(normal.z > 0.0f);

			vec3 pvertex = { bounds[px].x, bounds[py].y, bounds[pz].z };

			if(dot(pvertex, normal) < -planes[i].m_distance)
				return false;
		}

		return true;
	}

	inline float sqr(float a) { return a * a; }

	bool sphere_aabb_intersection(const vec3& center, float radius, const Aabb& aabb)
	{
		vec3 min = aabb.m_center - aabb.m_extents;
		vec3 max = aabb.m_center + aabb.m_extents;

		float r2 = radius * radius;
		float dmin = 0.f;

		for(vec3::length_type i = 0; i < 3; ++i)
		{
			if(center[i] < min[i]) dmin += sqr(center[i] - min[i]);
			else if(center[i] > max[i]) dmin += sqr(center[i] - max[i]);
		}

		return dmin <= r2;
	}

	// ref: https://www.ics.uci.edu/~eppstein/junkyard/circumcenter.html

	//     |                                                           |
	//     | |c-a|^2 [(b-a)x(c-a)]x(b-a) + |b-a|^2 (c-a)x[(b-a)x(c-a)] |
	//     |                                                           |
	// r = -------------------------------------------------------------,
	//                          2 | (b-a)x(c-a) |^2
	// 
	//         |c-a|^2 [(b-a)x(c-a)]x(b-a) + |b-a|^2 (c-a)x[(b-a)x(c-a)]
	// m = a + ---------------------------------------------------------.
	//                            2 | (b-a)x(c-a) |^2

	vec3 circumcenter(const vec3& a, const vec3& b, const vec3& c)
	{
		vec3 ba = b - a;
		vec3 ca = c - a;

		float balength = length2(ba);
		float calength = length2(ca);

		vec3 crossbc = cross(ba, ca);
		vec3 crossbc2 = crossbc * crossbc;

		float denominator = 0.5f / (crossbc2.x + crossbc2.y + crossbc2.z);

		auto yzx = [](const vec3& v) -> vec3 { return { v.y, v.z, v.x }; };
		auto zxy = [](const vec3& v) -> vec3 { return { v.z, v.x, v.y }; };
		
		vec3 circa = ((balength * yzx(ca) - calength * yzx(ba)) * zxy(crossbc) 
					- (balength * zxy(ca) - calength * zxy(ba)) * yzx(crossbc))
					* denominator;

		return a + circa;
	}
}
