#include <mud/geom.h>
#include <mud/math.h>
#include <mud/infra.h>
#include <mud/type.h>

#ifdef MUD_MODULES
module mud.math;
#else
#include <stl/tinystl/vector.impl.h>
#include <stl/tinystl/unordered_map.impl.h>
#endif

using namespace mud;
namespace tinystl
{
	template class MUD_GEOM_EXPORT vector<Poisson*>;
	template class MUD_GEOM_EXPORT vector<Geometry*>;
	template class MUD_GEOM_EXPORT vector<Geometry>;
	template class MUD_GEOM_EXPORT vector<Circle>;
	template class MUD_GEOM_EXPORT vector<IcoSphere>;
	template class MUD_GEOM_EXPORT vector<ProcShape>;
	template class MUD_GEOM_EXPORT vector<Distribution::Point>;
	template class MUD_GEOM_EXPORT vector<vector<Distribution::Point>>;
	template class MUD_GEOM_EXPORT vector<vector<Distribution::Point>*>;
	template class MUD_GEOM_EXPORT unordered_map<int64_t, int>;
}


#ifdef MUD_MODULES
module mud.geom;
#else
#endif

#include <stl/swap.h>

namespace mud
{
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
				if(t1 > t2) swap(t1, t2);
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
				if(t1 > t2) swap(t1, t2);
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

		if(abs(denom) <= c_cmp_epsilon)
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
		vec3 center = mulp(transform, source.m_center);
		vec3 extent = mult(abs(transform), source.m_extents);
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

#ifndef MUD_CPP_20
#include <stl/unordered_map.h>
#include <stl/map.h>
#include <cstdio>
#endif

#ifdef MUD_MODULES
module mud.geom;
#else
#endif

#include <mikktspace.h>

namespace mud
{
	inline bool operator<(const vec3& lhs, const vec3& rhs) { return all(less(lhs, rhs)); }
}

namespace mud
{
	uint32_t joints(const ivec4& j)
	{
		return uint32_t(j[0]) | uint32_t(j[1]) << 8 | uint32_t(j[2]) << 16 | uint32_t(j[3]) << 24;
	}

	inline void vec_to_array(const vec3& in, float out[]) { out[0] = in.x; out[1] = in.y; out[2] = in.z; }
	inline void vec_to_array(const vec2& in, float out[]) { out[0] = in.x; out[1] = in.y; }

	inline int quantize_unorm(float v, int N)
	{
		const float scale = float((1 << N) - 1);

		v = (v >= 0) ? v : 0;
		v = (v <= 1) ? v : 1;

		return int(v * scale + 0.5f);
	}

	inline int quantize_snorm(float v, int N)
	{
		const float scale = float((1 << (N - 1)) - 1);

		float round = (v >= 0 ? 0.5f : -0.5f);

		v = (v >= -1) ? v : -1;
		v = (v <= +1) ? v : +1;

		return int(v * scale + round);
	}

	inline unsigned short quantize_half(float v)
	{
		union { float f; unsigned int ui; } u = { v };
		unsigned int ui = u.ui;

		int s = (ui >> 16) & 0x8000;
		int em = ui & 0x7fffffff;

		/* bias exponent and round to nearest; 112 is relative exponent bias (127-15) */
		int h = (em - (112 << 23) + (1 << 12)) >> 13;

		/* underflow: flush to zero; 113 encodes exponent -14 */
		h = (em < (113 << 23)) ? 0 : h;

		/* overflow: infinity; 143 encodes exponent 16 */
		h = (em >= (143 << 23)) ? 0x7c00 : h;

		/* NaN; note that we convert all types of NaN to qNaN */
		h = (em > (255 << 23)) ? 0x7e00 : h;

		return (unsigned short)(s | h);
	}

	MeshAdapter& MeshAdapter::qposition(const vec3& p)
	{
		*m_cursor.m_qposition = half3(quantize_half(p.x), quantize_half(p.y), quantize_half(p.z));
		next(m_cursor.m_qposition);
		++m_vertex;
		return *this;
	}

	MeshAdapter& MeshAdapter::qnormal(const vec3& n)
	{
		if(m_cursor.m_qnormal)
		{
			uint8_t* packed = (uint8_t*)m_cursor.m_qnormal;
			*packed++ = uint8_t(n.x * 127.0f + 128.0f); // quantize_snorm(n.x, 8)
			*packed++ = uint8_t(n.y * 127.0f + 128.0f);
			*packed++ = uint8_t(n.z * 127.0f + 128.0f);

			next(m_cursor.m_qnormal);
		}
		return *this;
	}

	MeshAdapter& MeshAdapter::qtangent(const vec4& t)
	{
		if(m_cursor.m_qtangent)
		{
			uint8_t* packed = (uint8_t*)m_cursor.m_qtangent;
			*packed++ = uint8_t(t.x * 127.0f + 128.0f);  // quantize_snorm(t.x, 8)
			*packed++ = uint8_t(t.y * 127.0f + 128.0f);
			*packed++ = uint8_t(t.z * 127.0f + 128.0f);
			*packed++ = uint8_t(t.w * 127.0f + 128.0f);

			next(m_cursor.m_qtangent);
		}
		return *this;
	}

	MeshAdapter& MeshAdapter::quv0(const vec2& uv)
	{
		if(m_cursor.m_quv0)
		{
			m_uv0_rect.add(uv);
			*m_cursor.m_quv0 = half2(quantize_half(uv.x), quantize_half(uv.y));
			next(m_cursor.m_quv0);
		}
		return *this;
	}

	MeshAdapter& MeshAdapter::quv1(const vec2& uv)
	{
		if(m_cursor.m_quv1)
		{
			m_uv1_rect.add(uv);
			*m_cursor.m_quv1 = half2(quantize_half(uv.x), quantize_half(uv.y));
			next(m_cursor.m_quv1);
		}
		return *this;
	}

	Geometry::Geometry()
		: Shape(type<Geometry>())
		, m_vertices()
		, m_triangles()
	{}

	void Geometry::allocate(size_t vertex_count, size_t tri_count)
	{
		m_vertices.resize(vertex_count);
		m_triangles.resize(tri_count);
	}

	object<Shape> Geometry::clone() const { return oconstruct<Geometry>(*this); }

	MeshPacker::MeshPacker()
	{}

	uint32_t MeshPacker::vertex_format()
	{
		//uint32_t format = m_quantize ? VertexAttribute::QPosition : VertexAttribute::Position;
		uint32_t format = VertexAttribute::Position;
		if(!m_normals.empty())	format |= (m_quantize ? VertexAttribute::QNormal : VertexAttribute::Normal);
		if(!m_tangents.empty())	format |= (m_quantize ? VertexAttribute::QTangent : VertexAttribute::Tangent);
		if(!m_uv0s.empty())		format |= (m_quantize ? VertexAttribute::QTexCoord0 : VertexAttribute::TexCoord0);
		if(!m_uv1s.empty())		format |= (m_quantize ? VertexAttribute::QTexCoord1 : VertexAttribute::TexCoord1);
		if(!m_bones.empty())	format |= VertexAttribute::Joints;
		if(!m_weights.empty())	format |= VertexAttribute::Weights;
		return format;
	}

	void MeshPacker::bake(bool normals, bool tangents)
	{
		UNUSED(normals);

		//if(normals)
		//	this->generate_normals();

		if(tangents)
			this->generate_tangents();
	}

	void MeshPacker::pack_vertices(MeshAdapter& writer, const mat4& transform)
	{
		auto position = [&](uint32_t i) { return vec3(transform * vec4(m_positions[i], 1.f)); };
		auto normal = [&](uint32_t i) { return normalize(vec3(transform * vec4(m_normals[i], 0.f))); };
		auto tangent = [&](uint32_t i) { return vec4(vec3(transform * vec4(vec3(m_tangents[i]), 0.f)), m_tangents[i].w); };

		for(uint32_t i = 0; i < uint32_t(m_positions.size()); ++i)
		{
			writer.position(position(i));
			if(!m_normals.empty())	m_quantize ? writer.qnormal(normal(i)) : writer.normal(normal(i));
			if(!m_tangents.empty()) m_quantize ? writer.qtangent(tangent(i)) : writer.tangent(tangent(i));
			if(!m_uv0s.empty())     m_quantize ? writer.quv0(m_uv0s[i]) : writer.uv0(m_uv0s[i]);
			if(!m_uv1s.empty())		m_quantize ? writer.quv1(m_uv1s[i]) : writer.uv1(m_uv1s[i]);
			if(!m_bones.empty())	writer.joints(joints(m_bones[i]));
			if(!m_weights.empty())	writer.weights(m_weights[i]);

			if(m_indices.empty())
				writer.index(i);
		}

		for(uint32_t i = 0; i < m_indices.size(); ++i)
		{
			writer.index(m_indices[i]);
		}
	}

	void MeshPacker::generate_normals()
	{
#if 0
		map<vec3, vec3> smooth_normals;
		//std::unordered_map<vec3, vec3> smooth_normals;

		vector<int> smooth_groups;

		for(int smooth_group : smooth_groups)
		{
			for(size_t i = 0; i < m_positions.size(); i += 3)
			{
				int vert_smooth_group = 0;
				if(vert_smooth_group != smooth_group)
					continue;

				vec3 normal = Plane(m_positions[i + 0], m_positions[i + 1], m_positions[i + 2]).m_normal;

				if(smooth_group == 0)
				{
					m_normals[i + 0] = normal;
					m_normals[i + 1] = normal;
					m_normals[i + 2] = normal;
				}
				else
				{
					smooth_normals[m_positions[i + 0]] += normal;
					smooth_normals[m_positions[i + 1]] += normal;
					smooth_normals[m_positions[i + 2]] += normal;
				}
			}
		
			if(smooth_group == 0)
				continue;

			for(auto& kv : smooth_normals)
				kv.second = normalize(kv.second);

			for(size_t i = 0; i < m_positions.size(); i++)
			{
				m_normals[i] = smooth_normals[m_positions[i]];
			}

			smooth_normals.clear();
		}
#endif
	}

	struct ShapeData
	{
		array<ShapeIndex> m_indices;
		array<ShapeVertex> m_vertices;
	};

	inline ShapeData& mikkt_mesh(const SMikkTSpaceContext* context) { return *static_cast<ShapeData*>(context->m_pUserData); }
	inline ShapeVertex& mikkt_vertex(const SMikkTSpaceContext* context, int face, int vert)
	{
		ShapeData& shape_data = *static_cast<ShapeData*>(context->m_pUserData);
		ShapeIndex index = shape_data.m_indices[face * 3 + vert];
		return shape_data.m_vertices[index];
	}

	void generate_mikkt_tangents(array<ShapeIndex> indices, array<ShapeVertex> vertices)
	{
		ShapeData shape_data = { indices, vertices };
		vector<ShapeVertex> verts = to_vector(vertices);

		using Context = SMikkTSpaceContext;

		SMikkTSpaceInterface intf = {};
		intf.m_getNumFaces = [](const Context* c) -> int { return int(mikkt_mesh(c).m_indices.m_count) / 3; };
		intf.m_getNumVerticesOfFace = [](const Context* c, const int face) -> int { UNUSED(c); UNUSED(face); return 3; };
		intf.m_getPosition = [](const Context* c, float pos[], const int face, const int vert) { vec_to_array(mikkt_vertex(c, face, vert).m_position, pos); };
		intf.m_getNormal = [](const Context* c, float norm[], const int face, const int vert) { vec_to_array(mikkt_vertex(c, face, vert).m_normal, norm); };
		intf.m_getTexCoord = [](const Context* c, float uv[], const int face, const int vert) { vec_to_array(mikkt_vertex(c, face, vert).m_uv0, uv); };
		
		intf.m_setTSpaceBasic = [](const SMikkTSpaceContext * c, const float tangent[], const float sign, const int face, const int vert)
		{
			ShapeVertex& vertex = mikkt_vertex(c, face, vert);
			vertex.m_tangent = { tangent[0], tangent[1], tangent[2], sign };
		};

		SMikkTSpaceContext context;
		context.m_pInterface = &intf;
		context.m_pUserData = &shape_data;

		bool success = genTangSpaceDefault(&context) != 0;
		if(!success)
			printf("WARNING: Couldn't generate mikktspace tangents\n");
	}

	inline MeshPacker& mikkt_packer(const SMikkTSpaceContext* context) { return *static_cast<MeshPacker*>(context->m_pUserData); }
	inline size_t mikkt_index(const SMikkTSpaceContext* context, int face, int vert)
	{
		return mikkt_packer(context).m_indices.size() > 0 ? mikkt_packer(context).m_indices[face * 3 + vert]
														  : face * 3 + vert;
	}

	void MeshPacker::generate_tangents()
	{
		using Context = SMikkTSpaceContext;

		m_tangents.resize(m_positions.size());

		SMikkTSpaceInterface intf = {};
		intf.m_getNumFaces = [](const Context* c) -> int { return int(mikkt_packer(c).index_count()) / 3; };
		intf.m_getNumVerticesOfFace = [](const Context* c, const int face) -> int { UNUSED(c); UNUSED(face); return 3; };
		intf.m_getPosition = [](const Context* c, float pos[], const int face, const int vert) { vec_to_array(mikkt_packer(c).m_positions[mikkt_index(c, face, vert)], pos); };
		intf.m_getNormal = [](const Context* c, float norm[], const int face, const int vert) { vec_to_array(mikkt_packer(c).m_normals[mikkt_index(c, face, vert)], norm); };
		intf.m_getTexCoord = [](const Context* c, float uv[], const int face, const int vert) { vec_to_array(mikkt_packer(c).m_uv0s[mikkt_index(c, face, vert)], uv); };
		
		intf.m_setTSpaceBasic = [](const SMikkTSpaceContext * c, const float tangent[], const float sign, const int face, const int vert)
		{
			mikkt_packer(c).m_tangents[mikkt_index(c, face, vert)] = { tangent[0], tangent[1], tangent[2], sign };
		};

		SMikkTSpaceContext context;
		context.m_pInterface = &intf;
		context.m_pUserData = this;

		bool success = genTangSpaceDefault(&context) != 0;
		if(!success)
			printf("WARNING: Couldn't generate mikktspace tangents\n");
	}
}


#ifdef MUD_MODULES
module mud.geom;
#else
#endif

namespace mud
{
	Poisson::Poisson(vec2 size, float maxRadius)
		: Distribution()
		, m_size(size)
		, m_cellSize(maxRadius / sqrt(2.f))
		, m_invCellSize(1.f / m_cellSize)
		, m_grid(size_t(ceil(m_size * m_invCellSize).x), size_t(ceil(m_size * m_invCellSize).y), 1)
	{}

	void Poisson::pushPoint(const Point& point)
	{
		size_t index = gridIndex(point);
		m_points.push_back(point);
		m_unprocessed.push_back(point);
		m_grid[index].push_back(point);
	}

	Distribution::Point Poisson::randomPointAround(const Point& point, float radius)
	{
		float distance = point.radius + radius;

		float rr = m_overlap ? random_scalar(point.radius, distance)
							 : random_scalar(distance, distance * 2.f);
		float rt = random_scalar(0.f, float(2.f * c_pi));

		float x = rr * sin(rt) + point.position.x;
		float y = rr * cos(rt) + point.position.y;

		return Point(vec3(x, y, 0.f), radius);
	}

	bool Poisson::checkSpace(const Point& point)
	{
		size_t index = gridIndex(point);
		
		auto neighbours = m_grid.neighbours(index, 2);
		neighbours.push_back(&m_grid.at(index));

		for(vector<Point>* cell : neighbours)
			for(Point& other : *cell)
			{
				float dist = m_overlap ? point.radius : point.radius + other.radius;
				if(distance(point.position, other.position) <= dist)
					return false;
			}
		
		return true;
	}

	bool Poisson::checkInside(const Point& point)
	{
		return (point.position.x < m_size.x && point.position.x  >= 0.f
			 && point.position.y < m_size.y && point.position.y >= 0.f);
	}

	size_t Poisson::gridIndex(const Point& point)
	{
		uvec3 index = uvec3(floor(point.position * m_invCellSize));
		return m_grid.index_at(index.x, index.y, 0);
	}

	bool Poisson::insertPoint(float radius)
	{
		if(m_points.empty())
		{
			if(!m_start_from_center)
				pushPoint({ vec3(random_scalar(0.f, m_size.x), random_scalar(0.f, m_size.y), 0.f), radius });
			else
				pushPoint({ vec3(0.5f, 0.5f, 0.f), radius });
			return true;
		}

		while(!m_unprocessed.empty())
		{
			uint index = random_integer(0U, uint(m_unprocessed.size()) - 1);
			Point& refpoint = m_unprocessed[index];

			for(; refpoint.visits < m_k; ++refpoint.visits)
			{
				Point point = randomPointAround(refpoint, radius);
				if(checkInside(point) && checkSpace(point))
				{
					pushPoint(point);
					return true;
				}
			}

			m_unprocessed.erase(m_unprocessed.begin() + index);
		}

		return false;
	}

	bool Poisson::addPoint(float radius, vec3& point)
	{
		bool added = this->insertPoint(radius);
		if(added)
			point = m_points.back().position;
		return added;
	}

	void Poisson::uniform(float radius)
	{
		while(this->insertPoint(radius))
			continue;
	}

	vector<vec3> Poisson::distribute(float radius)
	{
		while(insertPoint(radius))
			continue;

		vector<vec3> result;
		for(Point& point : m_points)
		{
			vec3 position = { point.position.x - m_size.x / 2.f, 0.f, point.position.y - m_size.y / 2.f };
			result.push_back(position);
		}
		return result;
	}

	vector<Circle> Poisson::distribute_circles(float radius)
	{
		vector<vec3> distribution = this->distribute(radius);
		vector<Circle> result;
		for(vec3& point : distribution)
			result.push_back({ point, radius, Axis::Y });
		return result;
	}

	vector<vec3> distribute_poisson(vec2 size, float radius)
	{
		Poisson distribution = { size, radius };
		return distribution.distribute(radius);
	}
}


#ifdef MUD_MODULES
module mud.geom;
#else
#endif

namespace mud
{
	Line::Line() : Shape(type<Line>()) {}
	Line::Line(const vec3& start, const vec3& end) : Shape(type<Line>()), m_start(start), m_end(end) {}
	object<Shape> Line::clone() const { return oconstruct<Line>(*this); }

	Rect::Rect() : Shape(type<Rect>()) {}
	Rect::Rect(const vec2& pos, const vec2& size) : Shape(type<Rect>()), m_position(pos), m_size(size) {}
	Rect::Rect(float x, float y, float w, float h) : Shape(type<Rect>()), m_position(x, y), m_size(w, h) {}
	object<Shape> Rect::clone() const { return oconstruct<Rect>(*this); }

	Quad::Quad() : Shape(type<Quad>()) {}
	Quad::Quad(const vec3& a, const vec3& b, const vec3& c, const vec3& d) : Shape(type<Quad>()), m_vertices{ a, b, c, d } {}
	object<Shape> Quad::clone() const { return oconstruct<Quad>(*this); }

	Polygon::Polygon() : Shape(type<Polygon>()) {}
	Polygon::Polygon(vector<vec3> vertices) : Shape(type<Polygon>()), m_vertices(vertices) {}
	object<Shape> Polygon::clone() const { return oconstruct<Polygon>(*this); }

	Grid2::Grid2() : Shape(type<Grid2>()) {}
	Grid2::Grid2(const vec2& size, const vec2& space) : Shape(type<Grid2>()), m_size(size), m_space(space) {}
	object<Shape> Grid2::clone() const { return oconstruct<Grid2>(*this); }

	Triangle::Triangle() : Shape(type<Triangle>()) {}
	Triangle::Triangle(const vec2& size) : Shape(type<Triangle>()), m_size(size) {}
	object<Shape> Triangle::clone() const { return oconstruct<Triangle>(*this); }

	Circle::Circle() : Shape(type<Circle>()) {}
	Circle::Circle(float radius, Axis axis) : Shape(type<Circle>()), m_radius(radius), m_axis(axis) {}
	Circle::Circle(const vec3& center, float radius, Axis axis) : Shape(type<Circle>(), center), m_radius(radius), m_axis(axis) {}
	object<Shape> Circle::clone() const { return oconstruct<Circle>(*this); }

	Torus::Torus() : Shape(type<Torus>()) {}
	Torus::Torus(float radius, float solid_radius, Axis axis) : Shape(type<Torus>()), m_radius(radius), m_solid_radius(solid_radius), m_axis(axis) {}
	Torus::Torus(const vec3& center, float radius, float solid_radius, Axis axis) : Shape(type<Torus>(), center), m_radius(radius), m_solid_radius(solid_radius), m_axis(axis) {}
	object<Shape> Torus::clone() const { return oconstruct<Torus>(*this); }

	Ring::Ring() : Shape(type<Ring>()) {}
	Ring::Ring(float radius, float min, float max) : Shape(type<Ring>()), m_radius(radius), m_min(min), m_max(max) {}
	object<Shape> Ring::clone() const { return oconstruct<Ring>(*this); }

	Ellipsis::Ellipsis() : Shape(type<Ellipsis>()) {}
	Ellipsis::Ellipsis(vec2 radius, Axis axis) : Shape(type<Ellipsis>()), m_radius(radius), m_axis(axis) {}
	object<Shape> Ellipsis::clone() const { return oconstruct<Ellipsis>(*this); }

	Arc::Arc() : Shape(type<Arc>()) {}
	Arc::Arc(float radius, float start, float end) : Shape(type<Arc>()), m_radius(radius), m_start(start), m_end(end) {}
	object<Shape> Arc::clone() const { return oconstruct<Arc>(*this); }

	ArcLine::ArcLine() : Shape(type<ArcLine>()) {}
	ArcLine::ArcLine(const vec3& start, const vec3& middle, const vec3& end) : Shape(type<ArcLine>()), m_start(start), m_middle(middle), m_end(end) {}
	ArcLine::ArcLine(const vec3& center, const vec3& start, const vec3& middle, const vec3& end) : Shape(type<ArcLine>(), center), m_start(start), m_middle(middle), m_end(end) {}
	object<Shape> ArcLine::clone() const { return oconstruct<ArcLine>(*this); }

	Cylinder::Cylinder() : Shape(type<Cylinder>()) {}
	Cylinder::Cylinder(float radius, float height, Axis axis) : Shape(type<Cylinder>()), m_radius(radius), m_height(height), m_axis(axis) {}
	object<Shape> Cylinder::clone() const { return oconstruct<Cylinder>(*this); }

	Capsule::Capsule() : Shape(type<Capsule>()) {}
	Capsule::Capsule(float radius, float height, Axis axis) : Shape(type<Capsule>()), m_radius(radius), m_height(height), m_axis(axis) {}
	object<Shape> Capsule::clone() const { return oconstruct<Capsule>(*this); }

	Cube::Cube() : Shape(type<Cube>()) {}
	Cube::Cube(const vec3& extents) : Shape(type<Cube>()), m_extents(extents) {}
	Cube::Cube(const vec3& center, const vec3& extents) : Shape(type<Cube>(), center), m_extents(extents) {}
	Cube::Cube(float side) : Shape(type<Cube>()), m_extents(side, side, side) {}
	object<Shape> Cube::clone() const { return oconstruct<Cube>(*this); }

	Box::Box() : Shape(type<Box>()), m_vertices() {}
	object<Shape> Box::clone() const { return oconstruct<Box>(*this); }

	Sphere::Sphere() : Shape(type<Sphere>()) {}
	Sphere::Sphere(float radius) : Shape(type<Sphere>()), m_radius(radius) {}
	Sphere::Sphere(const vec3& center, float radius) : Shape(type<Sphere>(), center), m_radius(radius) {}
	object<Shape> Sphere::clone() const { return oconstruct<Sphere>(*this); }

	SphereRing::SphereRing() : Shape(type<SphereRing>()) {}
	SphereRing::SphereRing(float radius, float min, float max) : Shape(type<SphereRing>()), m_radius(radius), m_min(min), m_max(max) {}
	object<Shape> SphereRing::clone() const { return oconstruct<SphereRing>(*this); }

	Spheroid::Spheroid() : Shape(type<Spheroid>()) {}
	Spheroid::Spheroid(float radius) : Shape(type<Spheroid>()), m_radius(radius), m_circleX(radius, Axis::X), m_circleY(radius, Axis::Y), m_circleZ(radius, Axis::Z) {}
	Spheroid::Spheroid(const vec3& center, float radius) : Shape(type<Spheroid>(), center), m_radius(radius), m_circleX(radius, Axis::X), m_circleY(radius, Axis::Y), m_circleZ(radius, Axis::Z) {}
	object<Shape> Spheroid::clone() const { return oconstruct<Spheroid>(*this); }

	Points::Points() : Shape(type<Points>()) {}
	Points::Points(const vector<vec3>& points) : Shape(type<Points>()), m_points(points) {}
	object<Shape> Points::clone() const { return oconstruct<Points>(*this); }

	Grid3::Grid3() : Shape(type<Grid3>()) {}
	Grid3::Grid3(const uvec2& size, const vector<vec3>& points) : Shape(type<Grid3>()), m_size(size), m_points(points) { m_points.resize(size.x * size.y); }
	object<Shape> Grid3::clone() const { return oconstruct<Grid3>(*this); }

	ConvexHull::ConvexHull() : Shape(type<ConvexHull>()) {}
	ConvexHull::ConvexHull(const vector<vec3>& vertices) : Shape(type<ConvexHull>()), m_vertices(vertices) {}
	object<Shape> ConvexHull::clone() const { return oconstruct<ConvexHull>(*this); }

	Aabb::Aabb() : Cube(Zero3), m_empty(true) {}
	Aabb::Aabb(const vec3& center, const vec3& extents) : Cube(center, extents), m_empty(false) {}
	object<Shape> Aabb::clone() const { return oconstruct<Aabb>(*this); }

	bool Aabb::intersects(const Aabb& other) const
	{
		return !(any(less(m_center + m_extents, other.m_center - other.m_extents))
			  || any(greater(m_center - m_extents, other.m_center + other.m_extents)));
	}

	void Aabb::merge(const vec3& point)
	{
		if(m_empty)
		{
			m_center = point;
			m_empty = false;
			return;
		}

		vec3 bmax = max(m_center + m_extents, point);
		vec3 bmin = min(m_center - m_extents, point);

		m_center = (bmax + bmin) * 0.5f;
		m_extents = (bmax - bmin) * 0.5f;
	}

	void Aabb::mergeSafe(const Aabb& other)
	{
		if(other.m_empty) return;
		if(m_empty) *this = other; else this->merge(other);
		m_empty = false;
	}

	void Aabb::merge(const Aabb& other)
	{
		vec3 max_bounds = max(m_center + m_extents, other.m_center + other.m_extents);
		vec3 min_bounds = min(m_center - m_extents, other.m_center - other.m_extents);

		m_center = (max_bounds + min_bounds) * 0.5f;
		m_extents = (max_bounds - min_bounds) * 0.5f;
	}

	bool Aabb::cull(const vec3& point) const
	{
		if(m_empty) return false;

		vec3 max_bounds(m_center + m_extents);
		vec3 min_bounds(m_center - m_extents);

		if(any(greater(point, max_bounds)))
			return true;
		if(any(less(point, min_bounds)))
			return true;

		return false;
	}

	bool Aabb::cull(array<vec3> points) const
	{
		for(const vec3& point : points)
			if(cull(point))
				return true;
		return false;
	}

	Aabb face_aabb(const vec3* vertices)
	{
		vec3 bmin = min(vertices[0], min(vertices[1], vertices[2]));
		vec3 bmax = max(vertices[0], max(vertices[1], vertices[2]));
		vec3 extents = (bmax - bmin) * 0.5f;
		return Aabb(bmin + extents, extents);
	}

	Aabb face_aabb(const Face3& face)
	{
		return face_aabb(face.m_vertices);
	}

	void quad_vertices(const vec2& size, const vec3& u, const vec3& v, array<vec3> vertices, const vec2& offset = Zero2)
	{
		vec3 offset3d = u * offset.x + v * offset.y;
		vec3 a = (u * size.x + v * size.y) / 2.f;
		vec3 b = (u * size.x - v * size.y) / 2.f;
		vertices[0] = a + offset3d;
		vertices[1] = b + offset3d;
		vertices[2] = -a + offset3d;
		vertices[3] = -b + offset3d;
	}

	Quad::Quad(const vec2& size, const vec3& x, const vec3& y) : Shape(type<Quad>()) { quad_vertices(size, x, y, { m_vertices, 4 }); }
	Quad::Quad(const vec2& offset, const vec2& size, const vec3& x, const vec3& y) : Shape(type<Quad>()) { quad_vertices(size, x, y, { m_vertices, 4 }, offset); }
	Quad::Quad(const vec3& center, const vec2& size, const vec3& x, const vec3& y) : Shape(type<Quad>(), center) { quad_vertices(size, x, y, { m_vertices, 4 }); }
	Quad::Quad(const vec3& center, const vec2& offset, const vec2& size, const vec3& x, const vec3& y) : Shape(type<Quad>(), center) { quad_vertices(size, x, y, { m_vertices, 4 }, offset); }
	Quad::Quad(float size, const vec3& x, const vec3& y) : Quad({ size, size }, x, y) {}
	Quad::Quad(const Rect& rect) : Quad({ rect.m_size.x, rect.m_size.y }, X3, Z3) {}

	void box_vertices(const vec3& center, const vec3& extents, array<vec3> vertices)
	{
		vec3 min = center - extents;
		vec3 max = center + extents;

		vertices[0] = { min.x, min.y, max.z };
		vertices[1] = { max.x, min.y, max.z };
		vertices[2] = { max.x, max.y, max.z };
		vertices[3] = { min.x, max.y, max.z };
		vertices[4] = { max.x, min.y, min.z };
		vertices[5] = { min.x, min.y, min.z };
		vertices[6] = { min.x, max.y, min.z };
		vertices[7] = { max.x, max.y, min.z };
	}

	Box::Box(array<vec3> vertices) : Shape(type<Box>()) { array<vec3> dest = { m_vertices, 8 }; copy(dest, vertices); }
	Box::Box(const Cube& cube) : Shape(type<Box>()) { box_vertices(cube.m_center, cube.m_extents, { m_vertices, 8 }); }

	Symbol::Symbol(Colour fill, Colour outline, bool overlay, bool double_sided, SymbolDetail detail)
		: m_outline(outline)
		, m_fill(fill)
		, m_overlay(overlay)
		, m_double_sided(double_sided)
		, m_detail(detail)
	{}

	Symbol::Symbol(cstring image, float alpha)
		: Symbol()
	{
		m_image = image;
		m_fill.m_a = alpha;
	}

	Symbol::Symbol(const Image256& image, float alpha)
		: Symbol()
	{
		m_image256 = &const_cast<Image256&>(image);
		m_fill.m_a = alpha;
	}

	bool Symbol::operator==(const Symbol& other) const
	{
		UNUSED(other);
		return true;
	}

	inline vec3 distribute_sphere(float radius, float h = 2.f, float maxh = 1.f)
	{
		const float rand0 = random_scalar(0.f, 1.f) * h - maxh;
		const float rand1 = random_scalar(0.f, 1.f) * c_pi * 2.f;
		const float sqrtf1 = sqrt(1.0f - rand0 * rand0);

		return vec3{ sqrtf1 * cos(rand1), sqrtf1 * sin(rand1), rand0 } * radius;
	}

	inline vec3 distribute_spherical(float radius, float min, float max)
	{
		const float maxh = max * 2.0f - 1.0f;
		const float minh = min * 2.0f - 1.0f;
		return distribute_sphere(radius, maxh - minh, maxh);
	}

	inline vec3 distribute_circle(float radius)
	{
		const float angle = random_scalar(0.f, 1.f) * c_pi * 2.f;
		return vec3{ cos(angle), 0.0f, sin(angle) } * radius;
	}

	inline vec3 distribute_ring(float radius, float min = 0.f, float max = 1.f)
	{
		const float size = random_scalar(min, max);
		vec3 pos = distribute_circle(radius);
		return pos * size;
	}

	inline vec3 distribute_rect(float width = 1.f, float height = 1.f)
	{
		const float x = random_scalar(-1.f, 1.f);
		const float y = random_scalar(-1.f, 1.f);
		return { x * width, 0.f, y * height };
	}

	inline vec3 distribute_points(const vector<vec3>& points)
	{
		uint index = random_integer(0U, uint(points.size()) - 1U);
		return points[index];
	}

	RandomShapePoint::RandomShapePoint()
	{
		dispatch_branch<Sphere>(*this, +[](const Sphere& sphere) { return distribute_sphere(sphere.m_radius); });
		dispatch_branch<SphereRing>(*this, +[](const SphereRing& sphere) { return distribute_spherical(sphere.m_radius, sphere.m_min, sphere.m_max); });
		dispatch_branch<Circle>(*this, +[](const Circle& circle) { return distribute_circle(circle.m_radius); });
		dispatch_branch<Ring>(*this, +[](const Ring& ring) { return distribute_ring(ring.m_radius, ring.m_min, ring.m_max); });
		dispatch_branch<Rect>(*this, +[](const Rect& rect) { return distribute_rect(rect.m_size.x, rect.m_size.y); });
		dispatch_branch<Points>(*this, +[](const Points& points) { return distribute_points(points.m_points); });
	}

	vector<vec3> distribute_shape(const Shape& shape, size_t count)
	{
		if(!RandomShapePoint::me().check(Ref(&shape)))
			return vector<vec3>(count, Zero3);

		vector<vec3> points(count);
		for(size_t i = 0; i < count; ++i)
			points[i] = RandomShapePoint::me().dispatch(Ref(&shape));
		return points;
	}
}

#ifdef MUD_MODULES
module mud.geom;
#else
#endif

namespace mud
{
    // Exported types
    template <> MUD_GEOM_EXPORT Type& type<mud::DrawMode>() { static Type ty("mud::DrawMode", sizeof(mud::DrawMode)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::PrimitiveType>() { static Type ty("mud::PrimitiveType", sizeof(mud::PrimitiveType)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::SymbolDetail>() { static Type ty("mud::SymbolDetail", sizeof(mud::SymbolDetail)); return ty; }
    
    template <> MUD_GEOM_EXPORT Type& type<mud::Distribution>() { static Type ty("Distribution", sizeof(mud::Distribution)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Face3>() { static Type ty("Face3", sizeof(mud::Face3)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::MeshPacker>() { static Type ty("MeshPacker", sizeof(mud::MeshPacker)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Plane>() { static Type ty("Plane", sizeof(mud::Plane)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Plane3>() { static Type ty("Plane3", sizeof(mud::Plane3)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Ray>() { static Type ty("Ray", sizeof(mud::Ray)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Segment>() { static Type ty("Segment", sizeof(mud::Segment)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Shape>() { static Type ty("Shape", sizeof(mud::Shape)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::ShapeVar>() { static Type ty("ShapeVar", sizeof(mud::ShapeVar)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Symbol>() { static Type ty("Symbol", sizeof(mud::Symbol)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Arc>() { static Type ty("Arc", type<mud::Shape>(), sizeof(mud::Arc)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::ArcLine>() { static Type ty("ArcLine", type<mud::Shape>(), sizeof(mud::ArcLine)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Capsule>() { static Type ty("Capsule", type<mud::Shape>(), sizeof(mud::Capsule)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Cube>() { static Type ty("Cube", type<mud::Shape>(), sizeof(mud::Cube)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Aabb>() { static Type ty("Aabb", type<mud::Cube>(), sizeof(mud::Aabb)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Box>() { static Type ty("Box", type<mud::Shape>(), sizeof(mud::Box)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Circle>() { static Type ty("Circle", type<mud::Shape>(), sizeof(mud::Circle)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::ConvexHull>() { static Type ty("ConvexHull", type<mud::Shape>(), sizeof(mud::ConvexHull)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Cylinder>() { static Type ty("Cylinder", type<mud::Shape>(), sizeof(mud::Cylinder)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Ellipsis>() { static Type ty("Ellipsis", type<mud::Shape>(), sizeof(mud::Ellipsis)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Geometry>() { static Type ty("Geometry", type<mud::Shape>(), sizeof(mud::Geometry)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Grid2>() { static Type ty("Grid2", type<mud::Shape>(), sizeof(mud::Grid2)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Grid3>() { static Type ty("Grid3", type<mud::Shape>(), sizeof(mud::Grid3)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Line>() { static Type ty("Line", type<mud::Shape>(), sizeof(mud::Line)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Points>() { static Type ty("Points", type<mud::Shape>(), sizeof(mud::Points)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Poisson>() { static Type ty("Poisson", type<mud::Distribution>(), sizeof(mud::Poisson)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Polygon>() { static Type ty("Polygon", type<mud::Shape>(), sizeof(mud::Polygon)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Quad>() { static Type ty("Quad", type<mud::Shape>(), sizeof(mud::Quad)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Rect>() { static Type ty("Rect", type<mud::Shape>(), sizeof(mud::Rect)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Ring>() { static Type ty("Ring", type<mud::Shape>(), sizeof(mud::Ring)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Sphere>() { static Type ty("Sphere", type<mud::Shape>(), sizeof(mud::Sphere)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::SphereRing>() { static Type ty("SphereRing", type<mud::Shape>(), sizeof(mud::SphereRing)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Spheroid>() { static Type ty("Spheroid", type<mud::Shape>(), sizeof(mud::Spheroid)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Torus>() { static Type ty("Torus", type<mud::Shape>(), sizeof(mud::Torus)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Triangle>() { static Type ty("Triangle", type<mud::Shape>(), sizeof(mud::Triangle)); return ty; }
}


#ifdef MUD_MODULES
module mud.geom;
#else
#endif

namespace mud
{
	uint16_t circle_subdiv(uint lod) { return uint16_t(6 + 12 * lod); }
	
	vec3 flip_point_axis(const vec3& point, SignedAxis axis)
	{
		if(axis == SignedAxis::PlusX || axis == SignedAxis::MinusX)
			return { point.y, point.x, point.z };
		else if(axis == SignedAxis::PlusZ || axis == SignedAxis::MinusZ)
			return { point.z, point.x, point.y };
		else
			return { point.z, point.y, point.x };
	}

	uint16_t circle_vertices(const ProcShape& shape, const vec3& position, vec2 radius, SignedAxis axis, bool lines, MeshAdapter& writer, bool outward_normals)
	{
		uint16_t subdiv = circle_subdiv(uint(shape.m_symbol.m_detail));

		float increment = 2 * c_pi / subdiv;
		float angle = 0.0f;

		for(uint16_t i = 0; i < subdiv; i++)
		{
			vec3 point = flip_point_axis({ radius.x * cos(angle), 0.f, radius.y * sin(angle) }, axis);
			writer.position(position + point)
				  .normal(outward_normals ? point : to_vec3(axis))
				  .colour(lines ? shape.m_symbol.m_outline : shape.m_symbol.m_fill);
			angle += increment;
		}

		if(!lines)
			writer.position(position)
				  .normal(to_vec3(axis))
				  .colour(lines ? shape.m_symbol.m_outline : shape.m_symbol.m_fill);

		return subdiv;
	}

	ShapeSize size_shape_lines(const ProcShape& shape, const Circle& circle)
	{
		UNUSED(circle);
		uint16_t subdiv = circle_subdiv(uint(shape.m_symbol.m_detail));
		return { subdiv, subdiv * 2 };
	}

	void draw_shape_lines(const ProcShape& shape, const Circle& circle, MeshAdapter& writer)
	{
		uint16_t subdiv = circle_vertices(shape, circle.m_center, vec2{ circle.m_radius }, to_signed_axis(circle.m_axis, true), true, writer);

		for (uint16_t i = 0; i < subdiv; i++)
			writer.line(i, i + 1 < subdiv ? i + 1 : 0);
	}

	ShapeSize size_shape_triangles(const ProcShape& shape, const Circle& circle)
	{
		UNUSED(circle);
		uint16_t subdiv = circle_subdiv(uint(shape.m_symbol.m_detail));
		return { subdiv + 1, subdiv * 3 };
	}

	void draw_shape_triangles(const ProcShape& shape, const Circle& circle, MeshAdapter& writer)
	{
		uint16_t subdiv = circle_vertices(shape, circle.m_center, vec2{ circle.m_radius }, to_signed_axis(circle.m_axis, true), false, writer);

		for (uint16_t i = 0; i < subdiv; i++)
			writer.tri(i + 1 < subdiv ? i + 1 : 0, i,  subdiv);
	}

	
	ShapeSize size_shape_lines(const ProcShape& shape, const Ellipsis& ellipsis)
	{
		UNUSED(ellipsis);
		uint16_t subdiv = circle_subdiv(uint(shape.m_symbol.m_detail));
		return { subdiv, subdiv * 2 };
	}

	void draw_shape_lines(const ProcShape& shape, const Ellipsis& ellipsis, MeshAdapter& writer)
	{
		uint16_t subdiv = circle_vertices(shape, ellipsis.m_center, ellipsis.m_radius, to_signed_axis(ellipsis.m_axis, true), true, writer);

		for (uint16_t i = 0; i < subdiv; i++)
			writer.line(i, i + 1 < subdiv ? i + 1 : 0);
	}

	ShapeSize size_shape_triangles(const ProcShape& shape, const Ellipsis& ellipsis)
	{
		UNUSED(ellipsis);
		uint16_t subdiv = circle_subdiv(uint(shape.m_symbol.m_detail));
		return { subdiv + 1, subdiv * 3 };
	}

	void draw_shape_triangles(const ProcShape& shape, const Ellipsis& ellipsis, MeshAdapter& writer)
	{
		uint16_t subdiv = circle_vertices(shape, ellipsis.m_center, ellipsis.m_radius, to_signed_axis(ellipsis.m_axis, true), false, writer);

		for (uint16_t i = 0; i < subdiv; i++)
			writer.tri(i + 1 < subdiv ? i + 1 : 0, i,  subdiv);
	}

	ShapeSize size_shape_lines(const ProcShape& shape, const ArcLine& arc)
	{
		UNUSED(arc);
		uint16_t subdiv = circle_subdiv(uint(shape.m_symbol.m_detail));
		return { subdiv, (subdiv-1) * 2 };
	}

	void draw_shape_lines(const ProcShape& shape, const ArcLine& arc, MeshAdapter& writer)
	{
		uint16_t subdiv = circle_subdiv(uint(shape.m_symbol.m_detail));

		vec3 center = circumcenter(arc.m_start, arc.m_middle, arc.m_end);
		vec3 D = arc.m_start - center;
		vec3 E = arc.m_end - center;

		vec3 N = Plane(arc.m_start, arc.m_middle, arc.m_end).m_normal;
		float theta = angle(normalize(D), normalize(E));
		float dtheta = theta / subdiv;
		vec3 B = D;

		for(size_t i = 0; i < subdiv; ++i)
		{
			vec3 dir = rotate(B, float(i) * dtheta, N);
			vec3 p = dir + center;
			writer.position(arc.m_center + p)
				  .colour(shape.m_symbol.m_outline);
		}

		for(uint16_t i = 0; i < subdiv - 1; i++)
			writer.line(i, i + 1 < subdiv ? i + 1 : 0);
	}

	ShapeSize size_shape_triangles(const ProcShape& shape, const ArcLine& arc)
	{
		UNUSED(shape); UNUSED(arc);
		return { 0, 0 };
	}

	void draw_shape_triangles(const ProcShape& shape, const ArcLine& arc, MeshAdapter& writer)
	{
		UNUSED(shape); UNUSED(arc); UNUSED(writer);
	}

	uint16_t torus_sides(uint lod) { return uint16_t(12 + 12 * lod); }
	uint16_t torus_rings(uint lod) { return uint16_t(12 + 12 * lod); }

	ShapeSize size_shape_lines(const ProcShape& shape, const Torus& torus)
	{
		UNUSED(shape); UNUSED(torus);
		return { 0, 0 };
	}

	void draw_shape_lines(const ProcShape& shape, const Torus& torus, MeshAdapter& writer)
	{
		UNUSED(shape); UNUSED(torus); UNUSED(writer);
	}

	ShapeSize size_shape_triangles(const ProcShape& shape, const Torus& torus)
	{
		UNUSED(torus);
		uint16_t sides_subdiv = torus_sides(uint(shape.m_symbol.m_detail)) + 1;
		uint16_t rings_subdiv = torus_rings(uint(shape.m_symbol.m_detail)) + 1;
		return { int(sides_subdiv * rings_subdiv), int((sides_subdiv-1) * (rings_subdiv-1) * 6) };
	}

	void draw_shape_triangles(const ProcShape& shape, const Torus& torus, MeshAdapter& writer)
	{
		uint16_t sides = torus_sides(uint(shape.m_symbol.m_detail));
		uint16_t rings = torus_rings(uint(shape.m_symbol.m_detail));

		uint16_t sides_subdiv = sides + 1;
		uint16_t rings_subdiv = rings + 1;

		float vertical_delta = c_pi * 2.0f / float(rings);
		float horizontal_delta = c_pi * 2.0f / float(sides);

		for(uint16_t v = 0; v < sides_subdiv; v++)
			for(uint16_t h = 0; h < rings_subdiv; h++)
			{
				const float theta = vertical_delta * v;
				const float phi = horizontal_delta * h;

				const float x = cos(theta) * (torus.m_radius + torus.m_solid_radius * cos(phi));
				const float y = sin(theta) * (torus.m_radius + torus.m_solid_radius * cos(phi));
				const float z = torus.m_solid_radius * sin(phi);

				vec3 point = flip_point_axis({ x, z, y }, to_signed_axis(torus.m_axis, true));

				writer.position(point)
					  .colour(shape.m_symbol.m_fill);
			}

		for(uint16_t v = 0; v < sides; v++)
			for(uint16_t h = 0; h < rings; h++)
			{
				const uint16_t lt = h + v * sides_subdiv;
				const uint16_t rt = (h + 1) + v * sides_subdiv;

				const uint16_t lb = h + (v + 1) * sides_subdiv;
				const uint16_t rb = (h + 1) + (v + 1) * sides_subdiv;

				writer.tri(lt, rt, lb);
				writer.tri(rt, rb, lb);
			}
	}
}


#ifdef MUD_MODULES
module mud.geom;
#else
#endif

namespace mud
{
	ShapeSize size_cube_corners_lines(const ProcShape& shape, const Box& box)
	{
		UNUSED(shape); UNUSED(box);
		return { 8 * 4, 8 * 3 * 2 };
	}

	void draw_cube_corners_lines(const ProcShape& shape, const Box& box, MeshAdapter& writer)
	{
		for(int i = 0; i < 8; ++i)
		{
			vec3 position = box.m_center + box.m_vertices[i];

			static const vec3 components[3] = { X3, Y3, Z3 };
			float size_factor = 0.2f;
			
			writer.position(position)
				  .colour(shape.m_symbol.m_outline);

			for(int j = 0; j < 3; ++j)
				writer.position(position - position * components[j] * size_factor)
					  .colour(shape.m_symbol.m_outline);
		}


		for(uint16_t i = 0; i < 8 * 4; i+=4)
		{
			writer.line(i, i + 1);
			writer.line(i, i + 2);
			writer.line(i, i + 3);
		}
	}

	ShapeSize size_shape_lines(const ProcShape& shape, const Box& box)
	{
		//return size_cube_corners_lines(shape, box);
		UNUSED(shape); UNUSED(box);
		return { 8, 24 };
	}

	void draw_shape_lines(const ProcShape& shape, const Box& box, MeshAdapter& writer)
	{
		//return draw_cube_corners_lines(shape, box, writer);

		for (int i = 0; i < 8; ++i)
			writer.position(box.m_center + box.m_vertices[i])
				  .colour(shape.m_symbol.m_outline);

		for (uint16_t i = 0; i < 4; ++i)
			writer.line(i, (i + 1) % 4);

		for (uint16_t i = 4; i < 8; ++i)
			writer.line(i,  i == 7 ? 4 : i + 1);

		writer.line(1, 4);
		writer.line(2, 7);
		writer.line(0, 5);
		writer.line(3, 6);
	}

#define CUBE_NORMALS 1

	ShapeSize size_shape_triangles(const ProcShape& shape, const Box& box)
	{
		UNUSED(shape); UNUSED(box);
#if CUBE_NORMALS
		return { 24, 36 };
#else
		return { 16, 36 };
#endif
	}

	void draw_cube_quad(const ProcShape& shape, const Box& box, MeshAdapter& writer, uint32_t a, uint32_t b, uint32_t c, uint32_t d)
	{
		draw_shape_triangles(shape, Quad(box.m_vertices[a], box.m_vertices[b], box.m_vertices[c], box.m_vertices[d]), writer);
		writer.m_offset += 4;
	}

	void draw_shape_triangles(const ProcShape& shape, const Box& box, MeshAdapter& writer)
	{
#if CUBE_NORMALS
		draw_cube_quad(shape, box, writer, 0, 1, 2, 3);
		draw_cube_quad(shape, box, writer, 4, 5, 6, 7);
		draw_cube_quad(shape, box, writer, 0, 3, 6, 5);
		draw_cube_quad(shape, box, writer, 4, 7, 2, 1);
		draw_cube_quad(shape, box, writer, 3, 2, 7, 6);
		draw_cube_quad(shape, box, writer, 5, 4, 1, 0);
#else
		static vec2 quadUVs[4] = { { 1.f, 1.f }, { 1.f, 0.f }, { 0.f, 0.f }, { 0.f, 1.f } };

		for (int i = 0; i < 8; ++i)
			writer.position(shape.m_position + box.m_vertices[i])
				  .colour(Colour::White)
				  .uv0(quadUVs[i%4]);

		int i = 0;
		for(int v : { 3, 2, 7, 6, 5, 4, 1, 0 })
			writer.position(shape.m_position + box.m_vertices[v])
				  .colour(Colour::White)
				  .uv0(quadUVs[i++ % 4]);

		writer.quad(0, 1, 2, 3);
		writer.quad(4, 5, 6, 7);

		writer.quad(0, 3, 6, 5);
		writer.quad(4, 7, 2, 1);

		writer.quad(8, 9, 10, 11);
		writer.quad(12, 13, 14, 15);
#endif
	}
}


#ifdef MUD_MODULES
module mud.geom;
#else
#endif

namespace mud
{
	ShapeSize size_shape_lines(const ProcShape& shape, const Cylinder& cylinder)
	{
		ShapeSize circle_size = size_shape_lines(shape, Circle(cylinder.m_radius));
		return { circle_size.vertex_count * 2, circle_size.index_count * 3 };
	}
	
	void draw_shape_lines(const ProcShape& shape, const Cylinder& cylinder, MeshAdapter& writer)
	{
		vec3 offset = cylinder.m_axis == Axis::X ? X3 * cylinder.m_height / 2.f
					: cylinder.m_axis == Axis::Y ? Y3 * cylinder.m_height / 2.f
												 : Z3 * cylinder.m_height / 2.f;

		Circle circle = { cylinder.m_radius, cylinder.m_axis };
		uint16_t subdiv = circle_vertices(shape, cylinder.m_center + offset, vec2{ circle.m_radius }, to_signed_axis(circle.m_axis, true), true, writer);
						  circle_vertices(shape, cylinder.m_center - offset, vec2{ circle.m_radius }, to_signed_axis(circle.m_axis, false), true, writer);

		for (uint16_t i = 0; i < subdiv; i++)
		{
			writer.line(i, i + 1 < subdiv ? i + 1 : 0);
			writer.line(subdiv + i, i + 1 < subdiv ? subdiv + i + 1 : subdiv);
			writer.line(i, subdiv + i);
		}
	}

	ShapeSize size_shape_triangles(const ProcShape& shape, const Cylinder& cylinder)
	{
		ShapeSize circle_size = size_shape_triangles(shape, Circle(cylinder.m_radius));
		return { circle_size.vertex_count * 4, circle_size.index_count * 4 };
	}
	
	void draw_shape_triangles(const ProcShape& shape, const Cylinder& cylinder, MeshAdapter& writer)
	{
		vec3 offset = cylinder.m_axis == Axis::X ? X3 * cylinder.m_height / 2.f
					: cylinder.m_axis == Axis::Y ? Y3 * cylinder.m_height / 2.f
												: Z3 * cylinder.m_height / 2.f;

		Circle circle = { cylinder.m_radius, cylinder.m_axis };

		uint16_t subdiv = circle_vertices(shape, cylinder.m_center - offset, vec2{ circle.m_radius }, to_signed_axis(circle.m_axis, false), false, writer);

		for(uint16_t i = 0; i < subdiv; i++)
			writer.tri(i + 1 < subdiv ? i + 1 : 0, i, subdiv);
		writer.next();

		circle_vertices(shape, cylinder.m_center + offset, vec2{ circle.m_radius }, to_signed_axis(circle.m_axis, true), false, writer);

		for(uint16_t i = 0; i < subdiv; i++)
			writer.tri(i, i + 1 < subdiv ? i + 1 : 0, subdiv);
		writer.next();

		circle_vertices(shape, cylinder.m_center - offset, vec2{ circle.m_radius }, to_signed_axis(circle.m_axis, false), false, writer, true);
		circle_vertices(shape, cylinder.m_center + offset, vec2{ circle.m_radius }, to_signed_axis(circle.m_axis, true), false, writer, true);

		for(uint16_t i = 0; i < subdiv; i++)
			writer.quad(i, i + 1 < subdiv ? i + 1 : 0, i + 1 < subdiv ? (subdiv + 1) + i + 1 : (subdiv + 1), (subdiv + 1) + i);
	}
}


#ifdef MUD_MODULES
module mud.geom;
#else
#endif

namespace mud
{
	ShapeSize size_shape_lines(const ProcShape& shape, const Geometry& geometry)
	{
		UNUSED(shape);
		return { int(geometry.m_vertices.size()), int(geometry.m_triangles.size()) * 6 };
	}

	void draw_shape_lines(const ProcShape& shape, const Geometry& geometry, MeshAdapter& writer)
	{
		for(const Vertex& vertex : geometry.m_vertices)
			writer.position(geometry.m_center + vertex.m_position)
				  .colour(shape.m_symbol.m_outline);

		for(const Tri& triangle : geometry.m_triangles)
		{
			writer.line(uint16_t(triangle.a), uint16_t(triangle.b));
			writer.line(uint16_t(triangle.b), uint16_t(triangle.c));
			writer.line(uint16_t(triangle.c), uint16_t(triangle.a));
		}
	}
	
	ShapeSize size_shape_triangles(const ProcShape& shape, const Geometry& geometry)
	{
		UNUSED(shape);
		return { int(geometry.m_vertices.size()), int(geometry.m_triangles.size()) * 3 };
	}

	void draw_shape_triangles(const ProcShape& shape, const Geometry& geometry, MeshAdapter& writer)
	{
		UNUSED(shape);
		for(const Vertex& vertex : geometry.m_vertices)
			writer.position(geometry.m_center + vertex.m_position)
				  .colour(Colour::White);

		for(const Tri& triangle : geometry.m_triangles)
			writer.tri(triangle.a, triangle.b, triangle.c);
	}
}


#ifdef MUD_MODULES
module mud.geom;
#else
#endif

namespace mud
{
	vector<IcoSphere> IcoSphere::s_levels = { 1, 2, 3 };

	IcoSphere::IcoSphere(int recursionLevel)
	{
		float t = (1.0f + sqrt(5.0f)) / 2.0f;

		vec3 vertices[] = {
			{ -1.0f,  t,  0.0f },
			{  1.0f,  t,  0.0f },
			{ -1.0f, -t,  0.0f },
			{  1.0f, -t,  0.0f },
							
			{  0.0f, -1.0f,  t },
			{  0.0f,  1.0f,  t },
			{  0.0f, -1.0f, -t },
			{  0.0f,  1.0f, -t },
							
			{  t,  0.0f, -1.0f },
			{  t,  0.0f,  1.0f },
			{ -t,  0.0f, -1.0f },
			{ -t,  0.0f,  1.0f },
		};

		for(vec3& vert : vertices)
			this->vertex(vert);

		Face faces[] = {
			{ 0, 11, 5 }, { 0, 5,  1  }, { 0,  1,  7  }, { 0,  7, 10 }, { 0, 10, 11 },
			{ 1, 5,  9 }, { 5, 11, 4  }, { 11, 10, 2  }, { 10, 7, 6  }, { 7, 1,  8  },
			{ 3, 9,  4 }, { 3, 4,  2  }, { 3,  2,  6  }, { 3,  6, 8  }, { 3, 8,  9  },
			{ 4, 9,  5 }, { 2, 4,  11 }, { 6,  2,  10 }, { 8,  6, 7  }, { 9, 8,  1  },
		};

		for(Face& face : faces)
			m_faces.push_back(face);

		Line lines[] = {
			{ 1, 0 }, { 1, 5 }, { 1, 7 }, { 1, 8  }, { 1, 9  },
			{ 2, 3 }, { 2, 4 }, { 2, 6 }, { 2, 10 }, { 2, 11 },
			{ 0, 5 }, { 5, 9 }, { 9, 8 }, { 8, 7 }, { 7, 0 },
			{ 10, 11 }, { 11, 4 }, { 4, 3 }, { 3, 6 }, { 6, 10 },

			{ 0, 11 }, { 11, 5 }, { 5, 4 }, { 4, 9 }, { 9, 3 },
			{ 3, 8 }, { 8, 6 }, { 6, 7 }, { 7, 10 }, { 10, 0 },
		};

		for(Line& line : lines)
			m_lines.push_back(line);

		for(int r = 0; r < recursionLevel; r++)
		{
			vector<Face> prevfaces = m_faces;

			m_faces.clear();
			m_lines.clear();

			for(Face& face : prevfaces)
			{
				int a = this->middle_point(face[0], face[1]);
				int b = this->middle_point(face[1], face[2]);
				int c = this->middle_point(face[2], face[0]);

				m_faces.push_back({ face[0], a, c });
				m_faces.push_back({ face[1], b, a });
				m_faces.push_back({ face[2], c, b });
				m_faces.push_back({ a, b, c });

				this->triangle(face[0], a, c);
				this->triangle(face[1], b, a);
				this->triangle(face[2], c, b);
			}
		}
	}

	void IcoSphere::triangle(int index0, int index1, int index2)
	{
		m_lines.push_back({ index0, index1 });
		m_lines.push_back({ index1, index2 });
		m_lines.push_back({ index2, index0 });
	}
	
	int IcoSphere::vertex(const vec3& vertex)
	{
		m_vertices.push_back(normalize(vertex));
		return int(m_vertices.size() - 1);
	}

	int IcoSphere::middle_point(int index0, int index1)
	{
		int64_t lo = index0 < index1 ? index0 : index1;
		int64_t hi = index0 < index1 ? index1 : index0;
		int64_t key = (lo << 32) | hi;

		if (m_middle_point_cache.find(key) != m_middle_point_cache.end())
			return m_middle_point_cache[key];

		vec3 point1 = m_vertices[index0];
		vec3 point2 = m_vertices[index1];
		vec3 middle = (point1 + point2) / 2.f;

		int index = this->vertex(middle);
		m_middle_point_cache[key] = index;
		return index;
	}
}


#ifdef MUD_MODULES
module mud.geom;
#else
#endif

namespace mud
{
	void draw_line(const vec3& start, const vec3& end, const Colour& colour, MeshAdapter& writer)
	{
		writer.position(start)
			  .colour(colour);
		writer.position(end)
			  .colour(colour);
	}

	ShapeSize size_shape_lines(const ProcShape& shape, const Line& line)
	{
		UNUSED(shape); UNUSED(line);
		return { 2, 2 };
	}

	void draw_shape_lines(const ProcShape& shape, const Line& line, MeshAdapter& writer)
	{
		draw_line(line.m_start, line.m_end, shape.m_symbol.m_outline, writer);
		writer.line(0, 1);
	}

	ShapeSize size_shape_triangles(const ProcShape& shape, const Line& line)
	{
		UNUSED(shape); UNUSED(line);
		return { 0, 0 };
	}

	void draw_shape_triangles(const ProcShape& shape, const Line& line, MeshAdapter& writer)
	{
		UNUSED(shape); UNUSED(line); UNUSED(writer);
	}

	ShapeSize size_shape_lines(const ProcShape& shape, const Grid2& grid)
	{
		UNUSED(shape);
		uint16_t lines = uint16_t(grid.m_size.x) + 1 + uint16_t(grid.m_size.y) + 1;
		return { lines * 2, lines * 2 };
	}

	void draw_shape_lines(const ProcShape& shape, const Grid2& grid, MeshAdapter& writer)
	{
		vec2 half = grid.m_size * grid.m_space / 2.f;
		vec3 origin = grid.m_center - vec3{ half.x, 0.f, half.y };

		for(size_t x = 0; x < size_t(grid.m_size.x) + 1; ++x)
			draw_line(origin + to_xz(grid.m_space * vec2(float(x), 0.f)), origin + to_xz(grid.m_space * vec2(float(x), grid.m_size.y)), shape.m_symbol.m_outline, writer);
		for(size_t y = 0; y < size_t(grid.m_size.y) + 1; ++y)
			draw_line(origin + to_xz(grid.m_space * vec2(0.f, float(y))), origin + to_xz(grid.m_space * vec2(grid.m_size.x, float(y))), shape.m_symbol.m_outline, writer);

		uint16_t lines = uint16_t(grid.m_size.x) + 1 + uint16_t(grid.m_size.y) + 1;
		for(uint16_t i = 0; i < lines; ++i)
			writer.line(i * 2, i * 2 + 1);
	}

	ShapeSize size_shape_triangles(const ProcShape& shape, const Grid2& grid)
	{
		UNUSED(shape); UNUSED(grid);
		return { 0, 0 };
	}

	void draw_shape_triangles(const ProcShape& shape, const Grid2& grid, MeshAdapter& writer)
	{
		UNUSED(shape); UNUSED(grid); UNUSED(writer);
	}
}


#ifdef MUD_MODULES
module mud.geom;
#else
#endif

namespace mud
{
	using Draw = DispatchDrawProcShape;

	ShapeSize symbol_line_size(const ProcShape& procshape)
	{
		const Shape& shape = *procshape.m_shape;
		if(Draw::me.m_size_lines.check(Ref(&shape)))
			return Draw::me.m_size_lines.dispatch(Ref(&shape), procshape);
		return { 0, 0 };
	}

	ShapeSize symbol_triangle_size(const ProcShape& procshape)
	{
		const Shape& shape = *procshape.m_shape;
		if(Draw::me.m_size_triangles.check(Ref(&shape)))
			return Draw::me.m_size_triangles.dispatch(Ref(&shape), procshape);
		return { 0, 0 };
	}

	void symbol_draw_lines(const ProcShape& procshape, MeshAdapter& writer)
	{
		const Shape& shape = *procshape.m_shape;
		if(Draw::me.m_draw_lines.check(Ref(&shape)))
			Draw::me.m_draw_lines.dispatch(Ref(&shape), procshape, writer);
	}

	void symbol_draw_triangles(const ProcShape& procshape, MeshAdapter& writer)
	{
		const Shape& shape = *procshape.m_shape;
		if(Draw::me.m_draw_triangles.check(Ref(&shape)))
			Draw::me.m_draw_triangles.dispatch(Ref(&shape), procshape, writer);
	}

	ShapeSize size_shape_lines(const ProcShape& procshape, const CompoundShape& compound)
	{
		UNUSED(procshape);
		ShapeSize result = { 0, 0 };
		for(auto& shape : compound.m_shapes)
			result.vec += symbol_line_size(shape).vec;
		return result;
	}

	void draw_shape_lines(const ProcShape& procshape, const CompoundShape& compound, MeshAdapter& writer)
	{
		UNUSED(procshape);
		for(auto& shape : compound.m_shapes)
		{
			symbol_draw_lines(shape, writer);
			writer.next();
		}
	}

	ShapeSize size_shape_triangles(const ProcShape& procshape, const CompoundShape& compound)
	{
		UNUSED(procshape);
		ShapeSize result = { 0, 0 };
		for(auto& shape : compound.m_shapes)
			result.vec += symbol_triangle_size(shape).vec;
		return result;
	}

	void draw_shape_triangles(const ProcShape& procshape, const CompoundShape& compound, MeshAdapter& writer)
	{
		UNUSED(procshape);
		for(auto& shape : compound.m_shapes)
		{
			symbol_draw_triangles(shape, writer);
			writer.next();
		}
	}

	DispatchDrawProcShape::DispatchDrawProcShape()
	{
		declare_shape<Line>(*this);
		declare_shape<ArcLine>(*this);
		declare_shape<Circle>(*this);
		declare_shape<Ellipsis>(*this);
		declare_shape<Grid2>(*this);
		declare_shape<Grid3>(*this);
		declare_shape<Quad>(*this);
		declare_shape<Rect>(*this);
		declare_shape<Triangle>(*this);

		declare_shape<Box>(*this);
		declare_shape<Cube>(*this);
		declare_shape<Aabb>(*this);
		declare_shape<Cylinder>(*this);
		declare_shape<Sphere>(*this);
		declare_shape<Torus>(*this);

		declare_shape<Geometry>(*this);

		declare_compound_shape<Spheroid>(*this);
	}
}


#ifdef MUD_MODULES
module mud.geom;
#else
#endif

//#define PK_GLITCH

namespace mud
{
	static vec2 quadUVs[4] = { { 1.f, 1.f }, { 1.f, 0.f }, { 0.f, 0.f }, { 0.f, 1.f } };

	vec3 quad_normal(const vec3& a, const vec3& b, const vec3& c, const vec3& d)
	{
		UNUSED(d);
#ifndef PK_GLITCH
		vec3 x = b - a;
		vec3 y = c - a;
		return normalize(cross(x, y));
#else
		return 1.f;
#endif
	}

	void quad_vertices(const ProcShape& shape, const vec3& center, const vec3& a, const vec3& b, const vec3& c, const vec3& d, bool fill, MeshAdapter& writer)
	{
		auto vertex = [&](const vec3& p, const vec3& n, const vec2& uv)
		{
			writer.position(center + p)
				  .colour(fill ? shape.m_symbol.m_fill : shape.m_symbol.m_outline)
				  .normal(n)
				  .uv0(uv);
		};

		vec3 normal = quad_normal(a, b, c, d);
		vertex(a, normal, quadUVs[0]);
		vertex(b, normal, quadUVs[1]);
		vertex(c, normal, quadUVs[2]);
		vertex(d, normal, quadUVs[3]);
	}

	void quad_vertices(const ProcShape& shape, const vec3& center, array<vec3> vertices, bool fill, MeshAdapter& writer)
	{
		quad_vertices(shape, center, vertices[0], vertices[1], vertices[2], vertices[3], fill, writer);
	}

	ShapeSize size_shape_lines(const ProcShape& shape, const Quad& quad)
	{
		UNUSED(shape); UNUSED(quad);
		return { 4, 8 };
	}

	void draw_shape_lines(const ProcShape& shape, const Quad& quad, MeshAdapter& writer)
	{
		quad_vertices(shape, quad.m_center, { const_cast<vec3*>(quad.m_vertices), 4 }, false, writer);
		for(uint16_t i = 0; i < 4; i++)
			writer.line(i, (i + 1) % 4);
	}

	ShapeSize size_shape_triangles(const ProcShape& shape, const Quad& quad)
	{
		UNUSED(shape); UNUSED(quad);
		return { 4, 6 };
	}

	void draw_shape_triangles(const ProcShape& shape, const Quad& quad, MeshAdapter& writer)
	{
		quad_vertices(shape, quad.m_center, { const_cast<vec3*>(quad.m_vertices), 4 }, true, writer);
		writer.quad(0, 1, 2, 3);
	}

	size_t num_rects(const Grid3& grid) { return (grid.m_size.x-1) * (grid.m_size.y-1); }

	ShapeSize size_shape_lines(const ProcShape& shape, const Grid3& grid)
	{
		UNUSED(shape);
		size_t rects = num_rects(grid);
		return { int(rects * 4), int(rects * 8) };
	}

	void draw_shape_lines(const ProcShape& shape, const Grid3& grid, MeshAdapter& writer)
	{
		// @todo: could draw it like a grid instead of per quads...
		array2d<vec3> points = { const_cast<vec3*>(grid.m_points.data()), grid.m_size.x, grid.m_size.y };

		uint32_t offset = 0;

		for(uint32_t x = 0; x < grid.m_size.x - 1; ++x)
			for(uint32_t y = 0; y < grid.m_size.y - 1; ++y)
			{
				quad_vertices(shape, grid.m_center, points.at(x, y), points.at(x + 1, y), points.at(x + 1, y + 1), points.at(x, y + 1), true, writer);
				for(uint16_t i = 0; i < 4; i++)
					writer.line(offset + i, offset + (i + 1) % 4);
			}
	}

	ShapeSize size_shape_triangles(const ProcShape& shape, const Grid3& grid)
	{
		UNUSED(shape);
		size_t rects = num_rects(grid);
		return{ int(rects * 4), int(rects * 6) };
	}

	void draw_shape_triangles(const ProcShape& shape, const Grid3& grid, MeshAdapter& writer)
	{
		array2d<vec3> points = { const_cast<vec3*>(grid.m_points.data()), grid.m_size.x, grid.m_size.y };

		uint32_t offset = 0;

		for(uint32_t x = 0; x < grid.m_size.x-1; ++x)
			for(uint32_t y = 0; y < grid.m_size.y-1; ++y)
			{
				quad_vertices(shape, grid.m_center, points.at(x, y), points.at(x+1, y), points.at(x+1, y+1), points.at(x, y+1), true, writer);
				writer.quad(offset + 0, offset + 1, offset + 2, offset + 3);
				offset += 4;
			}
	}
}


#ifdef MUD_MODULES
module mud.geom;
#else
#endif

#define ICO_SPHERE_LOD 2
//#define MUD_SPHERE_ICOSPHERE

namespace mud
{
	ShapeSize size_icosphere_lines(const ProcShape& shape, const Sphere& sphere)
	{
		UNUSED(shape); UNUSED(sphere);
		IcoSphere& icosphere = IcoSphere::s_levels[ICO_SPHERE_LOD];

		return { int(icosphere.m_vertices.size()), int(icosphere.m_lines.size()) * 2 };
	}

	void draw_icosphere_lines(const ProcShape& shape, const Sphere& sphere, MeshAdapter& writer)
	{
		IcoSphere& icosphere = IcoSphere::s_levels[ICO_SPHERE_LOD];

		for(const vec3& vertex : icosphere.m_vertices)
			writer.position(sphere.m_center + vertex * sphere.m_radius)
				  .colour(shape.m_symbol.m_outline);

		for(const IcoSphere::Line& line : icosphere.m_lines)
			writer.line(ShapeIndex(line[0]), ShapeIndex(line[1]));
	}

	ShapeSize size_icosphere_triangles(const ProcShape& shape, const Sphere& sphere)
	{
		UNUSED(shape); UNUSED(sphere);
		IcoSphere& icosphere = IcoSphere::s_levels[ICO_SPHERE_LOD];

		return { int(icosphere.m_vertices.size()), int(icosphere.m_faces.size()) * 3 };
	}

	void draw_icosphere_triangles(const ProcShape& shape, const Sphere& sphere, MeshAdapter& writer)
	{
		IcoSphere& icosphere = IcoSphere::s_levels[ICO_SPHERE_LOD];

		for(const vec3& vertex : icosphere.m_vertices)
			writer.position(sphere.m_center + vertex * sphere.m_radius)
				  .normal(normalize(vertex))
				  .colour(shape.m_symbol.m_fill);

		for(IcoSphere::Face& face : icosphere.m_faces)
			writer.tri(face[0], face[1], face[2]);
	}

	uint16_t sphere_rings(uint lod) { return uint16_t(6 + 6 * lod); }
	uint16_t sphere_sectors(uint lod) { return uint16_t(6 + 6 * lod); }

	void sphere_vertices(const vec3& center, float radius, uint16_t rings, uint16_t sectors, const Colour& colour, MeshAdapter& writer)
	{
		float const R = 1.f / (float)(rings - 1);
		float const S = 1.f / (float)(sectors - 1);
		float repeat = 1.f;

		for(uint16_t r = 0; r < rings; r++) for(uint16_t s = 0; s < sectors; s++)
		{
			float const x = cos(2 * c_pi * s * S) * sin(c_pi * r * R);
			float const y = sin(-c_pi / 2.f + c_pi * r * R);
			float const z = sin(2 * c_pi * s * S) * sin(c_pi * r * R);

			writer.position(center + vec3(x, y, z) * radius)
				  .normal({ x, y, z })
				  .uv0({ s * S * repeat, r * R * repeat })
				  .colour(colour);
		}
	}

	ShapeSize size_sphere_lines(const ProcShape& shape, const Sphere& sphere)
	{
		UNUSED(shape); UNUSED(sphere);
		uint16_t rings = sphere_rings(uint(shape.m_symbol.m_detail));
		uint16_t sectors = sphere_sectors(uint(shape.m_symbol.m_detail));

		return { int(rings * sectors), int((rings-1) * (sectors-1) * 4) };
	}

	void draw_sphere_lines(const ProcShape& shape, const Sphere& sphere, MeshAdapter& writer)
	{
		uint16_t rings = sphere_rings(uint(shape.m_symbol.m_detail));
		uint16_t sectors = sphere_sectors(uint(shape.m_symbol.m_detail));

		sphere_vertices(sphere.m_center, sphere.m_radius, rings, sectors, shape.m_symbol.m_outline, writer);

		for(uint16_t r = 0; r < rings - 1; r++) for(uint16_t s = 0; s < sectors - 1; s++)
		{
			writer.line(r * sectors + (s + 1),
					    r * sectors + s);
			writer.line((r + 1) * sectors + (s + 1),
					    r * sectors + (s + 1));
		}
	}

	ShapeSize size_sphere_triangles(const ProcShape& shape, const Sphere& sphere)
	{
		UNUSED(shape); UNUSED(sphere);
		uint16_t rings = sphere_rings(uint(shape.m_symbol.m_detail));
		uint16_t sectors = sphere_sectors(uint(shape.m_symbol.m_detail));

		return { int(rings * sectors), int((rings-1) * (sectors-1) * 6) };
	}

	void draw_sphere_triangles(const ProcShape& shape, const Sphere& sphere, MeshAdapter& writer)
	{
		uint16_t rings = sphere_rings(uint(shape.m_symbol.m_detail));
		uint16_t sectors = sphere_sectors(uint(shape.m_symbol.m_detail));

		sphere_vertices(sphere.m_center, sphere.m_radius, rings, sectors, shape.m_symbol.m_fill, writer);

		for(uint16_t r = 0; r < rings - 1; r++) for(uint16_t s = 0; s < sectors - 1; s++)
		{
			writer.quad((r + 1) * sectors + s,
					    (r + 1) * sectors + (s + 1),
					    r * sectors + (s + 1),
					    r * sectors + s);
		}
	}

	ShapeSize size_shape_lines(const ProcShape& shape, const Sphere& sphere)
	{
#ifdef MUD_SPHERE_ICOSPHERE
		return size_icosphere_lines(shape, sphere);
#else
		return size_sphere_lines(shape, sphere);
#endif
	}

	void draw_shape_lines(const ProcShape& shape, const Sphere& sphere, MeshAdapter& writer)
	{
#ifdef MUD_SPHERE_ICOSPHERE
		return draw_icosphere_lines(shape, sphere, writer);
#else
		return draw_sphere_lines(shape, sphere, writer);
#endif
	}

	ShapeSize size_shape_triangles(const ProcShape& shape, const Sphere& sphere)
	{
#ifdef MUD_SPHERE_ICOSPHERE
		return size_icosphere_triangles(shape, sphere);
#else
		return size_sphere_triangles(shape, sphere);
#endif
	}

	void draw_shape_triangles(const ProcShape& shape, const Sphere& sphere, MeshAdapter& writer)
	{
#ifdef MUD_SPHERE_ICOSPHERE
		return draw_icosphere_triangles(shape, sphere, writer);
#else
		return draw_sphere_triangles(shape, sphere, writer);
#endif
	}
}


#ifdef MUD_MODULES
module mud.geom;
#else
#endif

namespace mud
{
	CompoundShape shape_compound(const ProcShape& shape, const Spheroid& spheroid)
	{
		return { { ProcShape{ shape.m_symbol, &spheroid.m_circleX, shape.m_draw_mode },
				   ProcShape{ shape.m_symbol, &spheroid.m_circleY, shape.m_draw_mode },
				   ProcShape{ shape.m_symbol, &spheroid.m_circleZ, shape.m_draw_mode } } };
	}
}


#ifdef MUD_MODULES
module mud.geom;
#else
#endif

//#define PK_GLITCH

namespace mud
{
	void triangle_vertices(const ProcShape& shape, const Triangle& triangle, bool fill, MeshAdapter& writer)
	{
		vec3 vertices[3] = { { -triangle.m_size.x / 2.f, -triangle.m_size.y / 2.f, 0.f },
							 {  triangle.m_size.x / 2.f, -triangle.m_size.y / 2.f, 0.f },
							 {  0.f,                      triangle.m_size.y / 2.f, 0.f } };

		for(int i = 0; i < 3; i++)
			writer.position(triangle.m_center + vertices[i])
				  .colour(fill ? shape.m_symbol.m_fill : shape.m_symbol.m_outline);
	}

	ShapeSize size_shape_lines(const ProcShape& shape, const Triangle& triangle)
	{
		UNUSED(shape); UNUSED(triangle);
		return { 3, 6 };
	}

	void draw_shape_lines(const ProcShape& shape, const Triangle& triangle, MeshAdapter& writer)
	{
		triangle_vertices(shape, triangle, false, writer);
		for(uint16_t i = 0; i < 3; i++)
			writer.line(i, (i + 1) % 3);
	}

	ShapeSize size_shape_triangles(const ProcShape& shape, const Triangle& triangle)
	{
		UNUSED(shape); UNUSED(triangle);
		return { 3, 3 };
	}

	void draw_shape_triangles(const ProcShape& shape, const Triangle& triangle, MeshAdapter& writer)
	{
		triangle_vertices(shape, triangle, true, writer);
		writer.tri(0, 1, 2);
	}
}
