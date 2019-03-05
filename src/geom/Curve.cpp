//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef MUD_MODULES
module mud.geom;
#else
#include <stl/string.h>
#include <stl/algorithm.h>
#include <stl/memory.h>
#include <math/Vec.hpp>
#include <math/Interp.h>
#include <geom/Curve.h>
#include <geom/Geom.h>
#endif

#include <cfloat>

namespace mud
{
	Curve3Sampler::Curve3Sampler(Curve3& curve)
		: m_curve(curve)
	{}

	vec3 Curve3Sampler::point(float u) const
	{
		float t = this->at(u);
		return m_curve.point(t);
	}

	vec3 Curve3Sampler::tangent(float u) const
	{
		float t = this->at(u);
		return m_curve.tangent(t);
	}
	float Curve3Sampler::at(float u) const
	{
		vector<float> lengths = m_curve.lengths();
		return this->at_distance(u * m_lengths.back());
	}

	vector<vec3> Curve3Sampler::points(size_t subdiv) const
	{
		vector<float> lengths = m_curve.lengths(subdiv);
		vector<vec3> points = {};
		for(size_t d = 0; d <= subdiv; d++)
		{
			points.push_back(this->point(float(d) / float(subdiv)));
		}
		return points;
	}
	
	float Curve3Sampler::at_distance(float distance) const
	{
		const vector<float>& lengths = m_lengths;
		const size_t il = lengths.size();
		size_t i = 0;

		// binary search for the index with largest value smaller than target u distance
		size_t low = 0, high = il - 1;

		while (low <= high)
		{
			i = floor(low + (high - low) / 2); // less likely to overflow, though probably not issue here, JS doesn't really have integers, all numbers are floats

			float comparison = lengths[i] - distance;

			if (comparison < 0.f)
				low = i + 1;
			else if (comparison > 0.f)
				high = i - 1;
			else
			{
				high = i;
				break;
			}
		}

		//float i = *find_binary(lengths.begin(), lengths.end(), [&](float l) { return l - distance; });

		if (lengths[i] == distance)
			return float(i) / float(il - 1);

		// we could get finer grain at lengths, or use simple interpolation between two points
		const float before = lengths[i];
		const float after = lengths[i + 1];

		const float segment_length = after - before;

		// determine where we are between the 'before' and 'after' points
		float segmentFraction = (distance - before) / segment_length;

		// add that fractional amount to t
		float t = (i + segmentFraction) / (il - 1);

		return t;
	}

	vector<vec3> Curve3::points(size_t subdiv) const
	{
		vector<vec3> points = {};
		for (size_t d = 0; d <= subdiv; d ++)
		{
			points.push_back(this->point(float(d) / float(subdiv)));
		}
		return points;
	}

	vector<float> Curve3::lengths() const
	{
		return this->lengths(m_curved_subdiv);
	}

	vector<float> Curve3::lengths(size_t subdiv) const
	{
		vector<float> lengths;

		vec3 last = this->point(0.f);
		lengths.push_back(0);

		float sum = 0.f;
		for (size_t p = 1; p <= subdiv; p++)
		{
			vec3 current = this->point(p / subdiv);
			sum += distance(current, last);
			lengths.push_back(sum);
			last = current;
		}

		return lengths;
	}


#if 0
	template <class It, class Pr>
	inline It find_binary(const It first, const It last, Pr pred)
	{
		It low = first;
		It high = last;

		while(low <= high)
		{
			It it = floor(low + (high - low) / 2); // less likely to overflow, though probably not issue here, JS doesn't really have integers, all numbers are floats

			int result = pred(*it);

			if(result < 0)
				low = i + 1;
			else if(result > 0)
				high = i - 1;
			else
				return it;
		}

		i = high;
		return high;
	}
#endif

	vec3 Curve3::tangent(float t) const
	{
		const float delta = 0.0001;
		const float t1 = max(t - delta, 0.f);
		const float t2 = min(t + delta, 1.f);

		const vec3 pt1 = this->point(t1);
		const vec3 pt2 = this->point(t2);

		return normalize(pt2 - pt1);
	}

	// see http://www.cs.indiana.edu/pub/techreports/TR425.pdf
	Curve3::FrenetFrames Curve3::frenet_frames(size_t segments, bool closed)
	{
		vector<vec3> tangents = {};
		vector<vec3> normals = {};
		vector<vec3> binormals = {};

		Curve3Sampler sampler = { *this };
		//sampler.subdiv();
		
		// compute the tangent vectors for each segment on the curve
		for (size_t i = 0; i <= segments; i ++)
		{
			size_t u = i / segments;

			tangents[i] = sampler.tangent(u);
			tangents[i] = normalize(tangents[i]);
		}

		// select an initial normal vector perpendicular to the first tangent vector,
		// and in the direction of the minimum tangent xyz component

		normals[0] = vec3();
		binormals[0] = vec3();
		float min = FLT_MAX;
		vec3 t = abs(tangents[0]);

		vec3 normal = vec3();
		if (t.x <= min)
		{
			min = t.x;
			normal = vec3(1, 0, 0);
		}

		if (t.y <= min)
		{
			min = t.y;
			normal = vec3(0, 1, 0);
		}

		if (t.z <= min)
		{
			normal = vec3(0, 0, 1);
		}

		vec3 vec = normalize(cross(tangents[0], normal));

		normals[0] = cross(tangents[0], vec);
		binormals[0] = cross(tangents[0], normals[0]);

		// compute the slowly-varying normal and binormal vectors for each segment on the curve
		for (size_t i = 1; i <= segments; i ++)
		{
			normals[i] = normals[i - 1];
			binormals[i] = binormals[i - 1];

			vec = cross(tangents[i - 1], tangents[i]);

			if (mud::length(vec) > c_cmp_epsilon)
			{
				vec = normalize(vec);

				float theta = acos(clamp(dot(tangents[i - 1], tangents[i]), -1.f, 1.f)); // clamp for floating pt errors

				//normals[i].applyMatrix4(mat.makeRotationAxis(vec, theta));
				normals[i] = axis_angle(vec, theta) * normals[i];
			}

			binormals[i] = cross(tangents[i], normals[i]);
		}

		// if the curve is closed, postprocess the vectors so the first and last normal vectors are the same
		if (closed == true)
		{
			float theta = acos(clamp(dot(normals[0], normals[segments]), -1.f, 1.f));
			theta /= segments;

			if (dot(tangents[0], cross(normals[0], normals[segments])) > 0)
			{
				theta = - theta;
			}

			for (size_t i = 1; i <= segments; i ++)
			{
				// twist a little...
				//normals[i].applyMatrix4(mat.makeRotationAxis(tangents[i], theta * i));
				normals[i] = axis_angle(tangents[i], theta * i) * normals[i];
				binormals[i] = cross(tangents[i], normals[i]);
			}
		}

		return { tangents, normals, binormals };
	}

	template <class T>
	struct CatmullRomCoeffs
	{
		T c0; T c1; T c2; T c3;

		CatmullRomCoeffs(T x0, T x1, T t0, T t1)
			: c0(x0)
			, c1(t0)
		    , c2(-3.f * x0 + 3.f * x1 - 2.f * t0 - t1)
		    , c3(2.f * x0 - 2.f * x1 + t0 + t1)
		{}

		T calc(float t) const
		{
			const float t2 = t * t;
			const float t3 = t2 * t;
			return c0 + c1 * t + c2 * t2 + c3 * t3;
		}

		static CatmullRomCoeffs<T> uniform(T x0, T x1, T x2, T x3, float tension)
		{
			return CatmullRomCoeffs<T>(x1, x2, tension * (x2 - x0), tension * (x3 - x1));
		}

		static CatmullRomCoeffs<T> non_uniform(T x0, T x1, T x2, T x3, float dt0, float dt1, float dt2)
		{
			// compute tangents when parameterized in [t1,t2]
			T t1 = (x1 - x0) / dt0 - (x2 - x0) / (dt0 + dt1) + (x2 - x1) / dt1;
			T t2 = (x2 - x1) / dt1 - (x3 - x1) / (dt1 + dt2) + (x3 - x2) / dt2;

			// rescale tangents for parametrization in [0,1]
			t1 *= dt1;
			t2 *= dt1;

			return CatmullRomCoeffs<T>(x1, x2, t1, t2);
		}
	};

	CurveCatmullRom3::CurveCatmullRom3(const vector<vec3>& points, bool closed, CurveType curveType, float tension)
		: m_points(points), m_closed(closed), m_curve_type(curveType), m_tension(tension)
	{}

	vec3 CurveCatmullRom3::point(float t) const
	{
		const vector<vec3>& points = m_points;
		const size_t l = points.size();

		const float p = (l - (m_closed ? 0 : 1)) * t;
		int i = floor(p);
		float weight = p - i;

		if(m_closed)
		{
			i += i > 0 ? 0 : (floor(abs(i) / l) + 1) * l;
		}
		else if(weight == 0 && i == l - 1)
		{
			i = l - 2;
			weight = 1;
		}

		vec3 p0 = (m_closed || i > 0)
			? points[(i - 1) % l]
			: points[0] - points[1] + points[0];
			
		vec3 p1 = points[i % l];
		vec3 p2 = points[(i + 1) % l];

		vec3 p3 = (m_closed || i + 2 < l)
			? points[(i + 2) % l]
			: points[l - 1] - points[l - 2] + points[l - 1];

		if(m_curve_type == CurveType::Centripetal || m_curve_type == CurveType::Chordal)
		{
			float power = m_curve_type == CurveType::Chordal ? 0.5f : 0.25f;
			float dt0 = pow(distance2(p0, p1), power);
			float dt1 = pow(distance2(p1, p2), power);
			float dt2 = pow(distance2(p2, p3), power);

			// safety check for repeated points
			if(dt1 < 1e-4) dt1 = 1.0;
			if(dt0 < 1e-4) dt0 = dt1;
			if(dt2 < 1e-4) dt2 = dt1;

			CatmullRomCoeffs<vec3> catmull = CatmullRomCoeffs<vec3>::non_uniform(p0, p1, p2, p3, dt0, dt1, dt2);
			return catmull.calc(weight);
		}
		else if(m_curve_type == CurveType::CatmullRom || true)
		{
			CatmullRomCoeffs<vec3> catmull = CatmullRomCoeffs<vec3>::uniform(p0, p1, p2, p3, m_tension);
			return catmull.calc(weight);
		}
	}

	vec2 CurveEllipse::point(float t)
	{
		float angle = m_angle[1] - m_angle[0];
		bool samePoints = abs(angle) < c_cmp_epsilon;

		// ensures that deltaAngle is 0 .. 2 c_pi
		while(angle < 0) angle += c_2pi;
		while(angle > c_2pi) angle -= c_2pi;

		if(angle < c_cmp_epsilon)
		{
			angle = samePoints ? 0 : c_2pi;
		}

		if(m_clockwise && !samePoints)
		{
			angle = angle == c_2pi ? -c_2pi : angle - c_2pi;
		}

		float theta = m_angle[0] + t * angle;
		vec2 p = m_a + m_radius * vec2(cos(theta), sin(theta));

		if(m_rotation != 0.f)
		{
			const float cosa = cos(m_rotation);
			const float sina = sin(m_rotation);
			const vec2 t = p - m_a;

			// Rotate the point about the center of the ellipse.
			float x = t.x * cosa - t.y * sina + m_a.x;
			float y = t.x * sina + t.y * cosa + m_a.y;
			p = vec2(x, y);
		}

		return p;
	}

	vec2 CurveBezierCubic::point(float t)
	{
		return cubic_bezier(v0, v1, v2, v3, t);
	}

	vec3 CurveBezierCubic3::point(float t) const
	{
		return cubic_bezier(v0, v1, v2, v3, t);
	}

	vec2 CurveLine::point(float t)
	{
		if(t == 1.f)
			return v1;
		else
			return v0 + (v1 - v0) * t;
	}

	vec3 CurveLine3::point(float t) const
	{
		if(t == 1.f)
			return v1;
		else
			return v0 + (v1 - v0) * t;
	}

	vec2 CurveBezierQuadratic::point(float t)
	{
		return quad_bezier(v0, v1, v2, t);
	}

	vec3 CurveBezierQuadratic3::point(float t) const
	{
		return quad_bezier(v0, v1, v2, t);
	}

	vec2 CurveSpline::point(float t)
	{
		const vector<vec2>& points = m_points;
		const size_t last = points.size() - 1;
		const float p = float(last) * t;

		int i = floor(p);
		float weight = p - float(i);

		vec2 p0 = points[i == 0 ? i : i - 1];
		vec2 p1 = points[i];
		vec2 p2 = points[i > points.size() - 2 ? last : i + 1];
		vec2 p3 = points[i > points.size() - 3 ? last : i + 2];

		return catmull_rom_three(p0, p1, p2, p3, t);
	}
}
