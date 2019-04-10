#include <mud/geom.h>
#include <mud/math.h>
#include <mud/infra.h>
#include <mud/type.h>


#ifdef MUD_MODULES
module mud.geom;
#else
#include <stl/string.h>
#include <stl/span.h>
#include <stl/algorithm.h>
#include <stl/memory.h>
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
		span<float> lengths = m_lengths;
		const size_t il = lengths.size();
		size_t i = 0;

		// binary search for the index with largest value smaller than target u distance
		size_t low = 0, high = il - 1;

		while (low <= high)
		{
			i = low + (high - low) / 2;

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
			vec3 current = this->point(float(p) / float(subdiv));
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
		const float delta = 0.0001f;
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
			float u = float(i) / float(segments);

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

	CurveCatmullRom3::CurveCatmullRom3()
	{}

	CurveCatmullRom3::CurveCatmullRom3(const vector<vec3>& points, bool closed, CatmullType curve_type, float tension)
		: m_points(points), m_closed(closed), m_curve_type(curve_type), m_tension(tension)
	{}

	void CurveCatmullRom3::add_point(const vec3& point)
	{
		m_points.push_back(point);
	}

	vec3 CurveCatmullRom3::point(float t) const
	{
		const vector<vec3>& points = m_points;
		const int l = int(points.size());

		const float p = float(l - (m_closed ? 0 : 1)) * t;
		int i = int(floor(p));
		float weight = p - float(i);

		if(m_closed)
		{
			i += i > 0 ? 0 : (abs(i) / l + 1) * l;
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

		if(m_curve_type == CatmullType::Centripetal || m_curve_type == CatmullType::Chordal)
		{
			float power = m_curve_type == CatmullType::Chordal ? 0.5f : 0.25f;
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
		else if(m_curve_type == CatmullType::CatmullRom || true)
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
			const vec2 tp = p - m_a;

			// Rotate the point about the center of the ellipse.
			float x = tp.x * cosa - tp.y * sina + m_a.x;
			float y = tp.x * sina + tp.y * cosa + m_a.y;
			p = vec2(x, y);
		}

		return p;
	}

	vec2 CurveBezierCubic::point(float t) const
	{
		return cubic_bezier(v0, v1, v2, v3, t);
	}

	vec3 CurveBezierCubic3::point(float t) const
	{
		return cubic_bezier(v0, v1, v2, v3, t);
	}

	vec2 CurveLine::point(float t) const
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

	vec2 CurveBezierQuadratic::point(float t) const
	{
		return quad_bezier(v0, v1, v2, t);
	}

	vec3 CurveBezierQuadratic3::point(float t) const
	{
		return quad_bezier(v0, v1, v2, t);
	}

	vec2 CurveSpline::point(float t) const
	{
		const vector<vec2>& points = m_points;
		const size_t last = points.size() - 1;
		const float p = float(last) * t;

		const size_t i = size_t(floor(p));
		const float weight = p - float(i);

		const vec2 p0 = points[i == 0 ? i : i - 1];
		const vec2 p1 = points[i];
		const vec2 p2 = points[i > points.size() - 2 ? last : i + 1];
		const vec2 p3 = points[i > points.size() - 3 ? last : i + 2];

		return catmull_rom_three(p0, p1, p2, p3, weight);
	}

	vec3 CurveSpline3::point(float t) const
	{
		const vector<vec3>& points = m_points;
		const size_t last = points.size() - 1;
		const float p = float(last) * t;

		const size_t i = size_t(floor(p));
		const float weight = p - float(i);

		const vec3 p0 = points[i == 0 ? i : i - 1];
		const vec3 p1 = points[i];
		const vec3 p2 = points[i > points.size() - 2 ? last : i + 1];
		const vec3 p3 = points[i > points.size() - 3 ? last : i + 2];

		return catmull_rom_three(p0, p1, p2, p3, weight);
	}
}
#ifndef USE_STL
#ifdef MUD_MODULES
module mud.geom;
#else
#include <stl/vector.hpp>
#include <stl/unordered_map.hpp>
#endif

namespace stl
{
	using namespace mud;
	template class MUD_GEOM_EXPORT vector<Poisson*>;
	template class MUD_GEOM_EXPORT vector<Geometry*>;
	template class MUD_GEOM_EXPORT vector<Geometry>;
	template class MUD_GEOM_EXPORT vector<Circle>;
	template class MUD_GEOM_EXPORT vector<IcoSphere>;
	template class MUD_GEOM_EXPORT vector<ProcShape>;
	template class MUD_GEOM_EXPORT vector<MarchingCubes::Cache::Normal>;
	template class MUD_GEOM_EXPORT vector<Distribution::Point>;
	template class MUD_GEOM_EXPORT vector<vector<Distribution::Point>>;
	template class MUD_GEOM_EXPORT vector<vector<Distribution::Point>*>;
	template class MUD_GEOM_EXPORT unordered_map<int64_t, int>;
}
#endif

#ifdef MUD_MODULES
module mud.geom;
#else
#endif

namespace mud
{
    // Exported types
    template <> MUD_GEOM_EXPORT Type& type<mud::CatmullType>() { static Type ty("CatmullType", sizeof(mud::CatmullType)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::DrawMode>() { static Type ty("DrawMode", sizeof(mud::DrawMode)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::PrimitiveType>() { static Type ty("PrimitiveType", sizeof(mud::PrimitiveType)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::SymbolDetail>() { static Type ty("SymbolDetail", sizeof(mud::SymbolDetail)); return ty; }
    
    template <> MUD_GEOM_EXPORT Type& type<stl::vector<mud::Circle>>() { static Type ty("vector<mud::Circle>", sizeof(stl::vector<mud::Circle>)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<stl::vector<mud::ivec4>>() { static Type ty("vector<mud::ivec4>", sizeof(stl::vector<mud::ivec4>)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<stl::vector<mud::vec2>>() { static Type ty("vector<mud::vec2>", sizeof(stl::vector<mud::vec2>)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<stl::vector<mud::vec4>>() { static Type ty("vector<mud::vec4>", sizeof(stl::vector<mud::vec4>)); return ty; }
    
    template <> MUD_GEOM_EXPORT Type& type<mud::Aabb>() { static Type ty("Aabb", sizeof(mud::Aabb)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Curve2>() { static Type ty("Curve2", sizeof(mud::Curve2)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Curve3>() { static Type ty("Curve3", sizeof(mud::Curve3)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Distribution>() { static Type ty("Distribution", sizeof(mud::Distribution)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Face3>() { static Type ty("Face3", sizeof(mud::Face3)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::MarchingCubes>() { static Type ty("MarchingCubes", sizeof(mud::MarchingCubes)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::MeshAdapter>() { static Type ty("MeshAdapter", sizeof(mud::MeshAdapter)); return ty; }
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
    template <> MUD_GEOM_EXPORT Type& type<mud::Box>() { static Type ty("Box", type<mud::Shape>(), sizeof(mud::Box)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Capsule>() { static Type ty("Capsule", type<mud::Shape>(), sizeof(mud::Capsule)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Circle>() { static Type ty("Circle", type<mud::Shape>(), sizeof(mud::Circle)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::ConvexHull>() { static Type ty("ConvexHull", type<mud::Shape>(), sizeof(mud::ConvexHull)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Cube>() { static Type ty("Cube", type<mud::Shape>(), sizeof(mud::Cube)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::CurveBezierCubic>() { static Type ty("CurveBezierCubic", type<mud::Curve2>(), sizeof(mud::CurveBezierCubic)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::CurveBezierCubic3>() { static Type ty("CurveBezierCubic3", type<mud::Curve3>(), sizeof(mud::CurveBezierCubic3)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::CurveBezierQuadratic>() { static Type ty("CurveBezierQuadratic", type<mud::Curve2>(), sizeof(mud::CurveBezierQuadratic)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::CurveBezierQuadratic3>() { static Type ty("CurveBezierQuadratic3", type<mud::Curve3>(), sizeof(mud::CurveBezierQuadratic3)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::CurveCatmullRom3>() { static Type ty("CurveCatmullRom3", type<mud::Curve3>(), sizeof(mud::CurveCatmullRom3)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::CurveLine>() { static Type ty("CurveLine", type<mud::Curve2>(), sizeof(mud::CurveLine)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::CurveLine3>() { static Type ty("CurveLine3", type<mud::Curve3>(), sizeof(mud::CurveLine3)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::CurveSpline>() { static Type ty("CurveSpline", type<mud::Curve2>(), sizeof(mud::CurveSpline)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::CurveSpline3>() { static Type ty("CurveSpline3", type<mud::Curve3>(), sizeof(mud::CurveSpline3)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Cylinder>() { static Type ty("Cylinder", type<mud::Shape>(), sizeof(mud::Cylinder)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Ellipsis>() { static Type ty("Ellipsis", type<mud::Shape>(), sizeof(mud::Ellipsis)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Geometry>() { static Type ty("Geometry", type<mud::Shape>(), sizeof(mud::Geometry)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Grid2>() { static Type ty("Grid2", type<mud::Shape>(), sizeof(mud::Grid2)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Grid3>() { static Type ty("Grid3", type<mud::Shape>(), sizeof(mud::Grid3)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Icosaedr>() { static Type ty("Icosaedr", type<mud::Shape>(), sizeof(mud::Icosaedr)); return ty; }
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
    template <> MUD_GEOM_EXPORT Type& type<mud::Tetraedr>() { static Type ty("Tetraedr", type<mud::Shape>(), sizeof(mud::Tetraedr)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Torus>() { static Type ty("Torus", type<mud::Shape>(), sizeof(mud::Torus)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::TorusKnot>() { static Type ty("TorusKnot", type<mud::Shape>(), sizeof(mud::TorusKnot)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Triangle>() { static Type ty("Triangle", type<mud::Shape>(), sizeof(mud::Triangle)); return ty; }
}

#ifndef MUD_CPP_20
#include <cstdio>
#endif

#ifdef MUD_MODULES
module mud.geom;
#else
#include <stl/unordered_map.h>
#include <stl/map.h>
#include <stl/algorithm.h>
#endif

#include <cassert>

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

	MeshAdapter::MeshAdapter(uint32_t vertex_count, MeshPacker& geom)
		: m_vertex_format(geom.vertex_format()), m_index32(true)
		, m_vertex_stride(vertex_size(geom.vertex_format()))
		, m_vertex_count(vertex_count)
	{
		uint32_t vertex_format = geom.vertex_format();

		m_start.m_position.init(vertex_format, VertexAttribute::Position, geom.m_positions.data());
		m_start.m_normal.init(vertex_format, VertexAttribute::Normal, geom.m_normals.data());
		m_start.m_colour.init(vertex_format, VertexAttribute::Colour, geom.m_ucolours.data());
		m_start.m_tangent.init(vertex_format, VertexAttribute::Tangent, geom.m_tangents.data());
		m_start.m_uv0.init(vertex_format, VertexAttribute::TexCoord0, geom.m_uv0s.data());
		m_start.m_uv1.init(vertex_format, VertexAttribute::TexCoord1, geom.m_uv1s.data());

		m_start.m_index32.init(geom.m_indices.data());

		m_cursor = m_start;
	}

	void MeshAdapter::rewind() { m_cursor = m_start; m_vertex = 0; m_offset = 0; }
	void MeshAdapter::next() { m_offset = m_vertex; }

	MeshAdapter& MeshAdapter::position(const vec3& p) { m_aabb.add(p); m_cursor.m_position.write(p); ++m_vertex; return *this; }
	MeshAdapter& MeshAdapter::position4(const vec4& p) { m_aabb.add(vec3(p)); m_cursor.m_position4.write(p); ++m_vertex; return *this; }
	MeshAdapter& MeshAdapter::normal(const vec3& n) { if(m_cursor.m_normal) { m_cursor.m_normal.write(n); } return *this; }
	MeshAdapter& MeshAdapter::colour(const Colour& c) { if(m_cursor.m_colour) { m_cursor.m_colour.write(to_abgr(c)); } return *this; }
	MeshAdapter& MeshAdapter::colour(const vec3& c) { if(m_cursor.m_colour) { m_cursor.m_colour.write(to_abgr(c.r, c.g, c.b)); } return *this; }
	MeshAdapter& MeshAdapter::tangent(const vec4& t) { if(m_cursor.m_tangent) { m_cursor.m_tangent.write(t); } return *this; }
	MeshAdapter& MeshAdapter::bitangent(const vec3& b) { if(m_cursor.m_bitangent) { m_cursor.m_bitangent.write(b); } return *this; }
	MeshAdapter& MeshAdapter::uv0(const vec2& uv) { if(m_cursor.m_uv0) { m_uv0_rect.add(uv); m_cursor.m_uv0.write(uv); } return *this; }
	MeshAdapter& MeshAdapter::uv1(const vec2& uv) { if(m_cursor.m_uv1) { m_uv1_rect.add(uv); m_cursor.m_uv1.write(uv); } return *this; }
	MeshAdapter& MeshAdapter::joints(const uint32_t& j) { if(m_cursor.m_joints) { m_cursor.m_joints.write(j); } return *this; }
	MeshAdapter& MeshAdapter::weights(const vec4& w) { if(m_cursor.m_weights) { m_cursor.m_weights.write(w); } return *this; }

	void MeshAdapter::copy(MeshAdapter& dest)
	{
		MeshAdapter reader = this->read();

		for(size_t i = 0; i < reader.m_vertex_count; ++i)
		{
			dest.position(reader.position());
			dest.normal(reader.normal());
			dest.colour(reader.colour());
			dest.tangent(reader.tangent());
			dest.uv0(reader.uv0());
			dest.uv1(reader.uv1());
			dest.joints(reader.joints());
			dest.weights(reader.weights());
		}

		for(size_t i = 0; i < reader.m_index_count; ++i)
		{
			uint32_t index = reader.m_index32 ? reader.index32() : reader.index();
			assert(index <= dest.m_vertex_count);
			dest.index(index);
		}
	}

	void MeshAdapter::xcopy(MeshAdapter& dest, const mat4& transform)
	{
		MeshAdapter reader = this->read();

		for(size_t i = 0; i < reader.m_vertex_count; ++i)
		{
			dest.position(mulp(transform, reader.position()));
			dest.normal(muln(transform, reader.normal()));
			dest.colour(reader.colour());
			dest.tangent(mult(transform, reader.tangent()));
			dest.uv0(reader.uv0());
			dest.uv1(reader.uv1());
			dest.joints(reader.joints());
			dest.weights(reader.weights());
		}

		for(size_t i = 0; i < reader.m_index_count; ++i)
		{
			uint32_t index = reader.m_index32 ? reader.index32() : reader.index();
			assert(index <= dest.m_vertex_count);
			dest.index(index);
		}
	}

	MeshAdapter& MeshAdapter::qposition(const vec3& p)
	{
		half3 qposition = half3(quantize_half(p.x), quantize_half(p.y), quantize_half(p.z));
		m_cursor.m_qposition.write(qposition);
		++m_vertex;
		return *this;
	}

	MeshAdapter& MeshAdapter::qnormal(const vec3& n)
	{
		if(m_cursor.m_qnormal)
		{
			uint32_t qnormal;
			uint8_t* packed = (uint8_t*)&qnormal;
			*packed++ = uint8_t(n.x * 127.0f + 128.0f); // quantize_snorm(n.x, 8)
			*packed++ = uint8_t(n.y * 127.0f + 128.0f);
			*packed++ = uint8_t(n.z * 127.0f + 128.0f);

			m_cursor.m_qnormal.write(qnormal);
		}
		return *this;
	}

	MeshAdapter& MeshAdapter::qtangent(const vec4& t)
	{
		if(m_cursor.m_qtangent)
		{
			uint32_t qtangent;
			uint8_t* packed = (uint8_t*)&qtangent;
			*packed++ = uint8_t(t.x * 127.0f + 128.0f);  // quantize_snorm(t.x, 8)
			*packed++ = uint8_t(t.y * 127.0f + 128.0f);
			*packed++ = uint8_t(t.z * 127.0f + 128.0f);
			*packed++ = uint8_t(t.w * 127.0f + 128.0f);

			m_cursor.m_qtangent.write(qtangent);
		}
		return *this;
	}

	MeshAdapter& MeshAdapter::quv0(const vec2& uv)
	{
		if(m_cursor.m_quv0)
		{
			m_uv0_rect.add(uv);
			half2 quv = half2(quantize_half(uv.x), quantize_half(uv.y));
			m_cursor.m_quv0.write(quv);
		}
		return *this;
	}

	MeshAdapter& MeshAdapter::quv1(const vec2& uv)
	{
		if(m_cursor.m_quv1)
		{
			m_uv1_rect.add(uv);
			half2 quv = half2(quantize_half(uv.x), quantize_half(uv.y));
			m_cursor.m_quv1.write(quv);
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

	uint32_t MeshPacker::vertex_format() const
	{
		//uint32_t format = m_quantize ? VertexAttribute::QPosition : VertexAttribute::Position;
		uint32_t format = VertexAttribute::Position;
		if(!m_normals.empty())	format |= (m_quantize ? VertexAttribute::QNormal : VertexAttribute::Normal);
		if(!m_colours.empty())	format |= VertexAttribute::Colour;
		if(!m_tangents.empty())	format |= (m_quantize ? VertexAttribute::QTangent : VertexAttribute::Tangent);
		if(!m_uv0s.empty())		format |= (m_quantize ? VertexAttribute::QTexCoord0 : VertexAttribute::TexCoord0);
		if(!m_uv1s.empty())		format |= (m_quantize ? VertexAttribute::QTexCoord1 : VertexAttribute::TexCoord1);
		if(!m_bones.empty())	format |= VertexAttribute::Joints;
		if(!m_weights.empty())	format |= VertexAttribute::Weights;
		return format;
	}

	void MeshPacker::bake(bool normals, bool tangents)
	{
		if(normals && m_normals.empty()) this->gen_normals();
		if(tangents && m_tangents.empty()) this->gen_tangents();
	}

	void MeshPacker::resize(uint32_t vertex_count, uint32_t index_count, uint32_t vertex_format)
	{
		m_positions.resize(vertex_count);
		if((vertex_format & VertexAttribute::Normal)    != 0) m_normals.resize(vertex_count);
		//if((vertex_format & VertexAttribute::Colour)    != 0) m_colours.resize(vertex_count);
		// for now this is used exclusively for packing using MeshAdapter, so this doesn't break... yet
		if((vertex_format & VertexAttribute::Colour)    != 0) m_ucolours.resize(vertex_count);
		if((vertex_format & VertexAttribute::Tangent)   != 0) m_tangents.resize(vertex_count);
		if((vertex_format & VertexAttribute::TexCoord0) != 0) m_uv0s.resize(vertex_count);
		if((vertex_format & VertexAttribute::TexCoord1) != 0) m_uv1s.resize(vertex_count);
		if((vertex_format & VertexAttribute::Joints)    != 0) m_bones.resize(vertex_count);
		if((vertex_format & VertexAttribute::Weights)   != 0) m_weights.resize(vertex_count);

		m_indices.resize(index_count);
	}

	void MeshPacker::clear()
	{
		m_positions.clear();
		m_normals.clear();
		m_colours.clear();
		m_tangents.clear();
		m_uv0s.clear();
		m_uv1s.clear();
		m_bones.clear();
		m_weights.clear();

		m_indices.clear();
	}

	void MeshPacker::pack(MeshAdapter& writer) const
	{
		for(const vec3&   p  : m_positions)	 writer.position(p);
		for(const vec3&   n  : m_normals)	 m_quantize ? writer.qnormal(n) : writer.normal(n);
		for(const Colour& c  : m_colours)	 writer.colour(c);
		for(const vec4&   t  : m_tangents)	 m_quantize ? writer.qtangent(t) : writer.tangent(t);
		for(const vec2&   uv : m_uv0s)		 m_quantize ? writer.quv0(uv) : writer.uv0(uv);
		for(const vec2&   uv : m_uv1s)		 m_quantize ? writer.quv1(uv) : writer.uv1(uv);
		for(const ivec4&  b  : m_bones)		 writer.joints(joints(b));
		for(const vec4&   w  : m_weights)	 writer.weights(w);

		for(uint32_t i : m_indices) writer.index(i);
	}

	void MeshPacker::xpack(MeshAdapter& writer, const mat4& transform) const
	{
		for(const vec3&   p  : m_positions)	 writer.position(mulp(transform, p));
		for(const vec3&   n  : m_normals)	 m_quantize ? writer.qnormal(muln(transform, n)) : writer.normal(muln(transform, n));
		for(const Colour& c  : m_colours)	 writer.colour(c);
		for(const vec4&   t  : m_tangents)	 m_quantize ? writer.qtangent(mult(transform, t)) : writer.tangent(mult(transform, t));
		for(const vec2&   uv : m_uv0s)		 m_quantize ? writer.quv0(uv) : writer.uv0(uv);
		for(const vec2&   uv : m_uv1s)		 m_quantize ? writer.quv1(uv) : writer.uv1(uv);
		for(const ivec4&  b  : m_bones)		 writer.joints(joints(b));
		for(const vec4&   w  : m_weights)	 writer.weights(w);

		for(uint32_t i : m_indices) writer.index(i);
	}

	void MeshPacker::unpack(const MeshAdapter& source, const mat4& transform)
	{
		MeshAdapter reader = source.read();

		for(size_t i = 0; i < reader.m_vertex_count; ++i)
		{
			m_positions.push_back(mulp(transform, reader.position()));
			if((reader.m_vertex_format & VertexAttribute::Normal) != 0)
				m_normals.push_back(muln(transform, reader.normal()));
			if((reader.m_vertex_format & VertexAttribute::Colour) != 0)
				m_colours.push_back(reader.colour());
			if((reader.m_vertex_format & VertexAttribute::Tangent) != 0)
				m_tangents.push_back(mult(transform, reader.tangent()));
			if((reader.m_vertex_format & VertexAttribute::TexCoord0) != 0)
				m_uv0s.push_back(reader.uv0());
			if((reader.m_vertex_format & VertexAttribute::TexCoord1) != 0)
				m_uv1s.push_back(reader.uv1());
			//packer.m_bones.push_back(source.bones());
			//packer.m_weights.push_back(source.weights());
		}

		for(size_t i = 0; i < reader.m_index_count; ++i)
		{
			m_indices.push_back(reader.m_index32 ? reader.index32() : reader.index());
		}
	}

	void MeshPacker::gen_flat_normals()
	{
		const vector<vec3>& positions = m_positions;

		m_normals.resize(positions.size());

		for(size_t i = 0; i < m_indices.size(); i += 3)
		{
			const uint32_t a = m_indices[i+0];
			const uint32_t b = m_indices[i+1];
			const uint32_t c = m_indices[i+2];

			const vec3 cb = positions[c] - positions[b];
			const vec3 ab = positions[a] - positions[b];
			const vec3 normal = normalize(cross(cb, ab));

			m_normals[a] = m_normals[b] = m_normals[c] = normal;
		}
	}

	void MeshPacker::gen_normals(bool area_weighted)
	{
		vector<vec3> normals = vector<vec3>(m_positions.size(), vec3(0.f));

		// vertex normals weighted by triangle areas
		// http://www.iquilezles.org/www/articles/normals/normals.htm

		const vector<vec3>& positions = m_positions;

		for(size_t i = 0; i < m_indices.size(); i += 3)
		{
			const uint32_t a = m_indices[i+0];
			const uint32_t b = m_indices[i+1];
			const uint32_t c = m_indices[i+2];

			const vec3 cb = positions[c] - positions[b];
			const vec3 ab = positions[a] - positions[b];
			const vec3 normal = area_weighted
				? cross(cb, ab)
				: normalize(cross(cb, ab));

			normals[a] += normal;
			normals[b] += normal;
			normals[c] += normal;
		}
		
		for(vec3& n : normals)
			n = normalize(n);

		m_normals = normals;
	}

	void MeshPacker::smooth_normals()
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
		span<ShapeIndex> m_indices;
		span<ShapeVertex> m_vertices;
	};

	inline ShapeData& mikkt_mesh(const SMikkTSpaceContext* context) { return *static_cast<ShapeData*>(context->m_pUserData); }
	inline ShapeVertex& mikkt_vertex(const SMikkTSpaceContext* context, int face, int vert)
	{
		ShapeData& shape_data = *static_cast<ShapeData*>(context->m_pUserData);
		ShapeIndex index = shape_data.m_indices[face * 3 + vert];
		return shape_data.m_vertices[index];
	}

	void generate_mikkt_tangents(span<ShapeIndex> indices, span<ShapeVertex> vertices)
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

	void MeshPacker::gen_tangents()
	{
		using Context = SMikkTSpaceContext;

		m_tangents.resize(m_positions.size());

		static auto p = [](const SMikkTSpaceContext* context) -> MeshPacker& { return *static_cast<MeshPacker*>(context->m_pUserData); };
		static auto index = [](const SMikkTSpaceContext* context, int face, int vert)
		{
			MeshPacker& pp = p(context);
			return pp.m_indices.size() > 0
				? pp.m_indices[face * 3 + vert]
				: face * 3 + vert;
		};

		SMikkTSpaceInterface intf = {};
		intf.m_getNumFaces = [](const Context* c) -> int { return int(p(c).face_count()); };
		intf.m_getNumVerticesOfFace = [](const Context* c, const int face) -> int { UNUSED(c); UNUSED(face); return 3; };
		intf.m_getPosition = [](const Context* c, float pos[], const int face, const int vert) { vec_to_array(p(c).m_positions[index(c, face, vert)], pos); };
		intf.m_getNormal = [](const Context* c, float norm[], const int face, const int vert) { vec_to_array(p(c).m_normals[index(c, face, vert)], norm); };
		intf.m_getTexCoord = [](const Context* c, float uv[], const int face, const int vert) { vec_to_array(p(c).m_uv0s[index(c, face, vert)], uv); };
		
		intf.m_setTSpaceBasic = [](const SMikkTSpaceContext * c, const float tangent[], const float sign, const int face, const int vert)
		{
			p(c).m_tangents[index(c, face, vert)] = { tangent[0], tangent[1], tangent[2], sign };
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
	// ref http://www.openprocessing.org/visuals/?visualID=15599

	vector<vec3> hilbert2d(vec3 center, float size, int iterations, uint v0, uint v1, uint v2, uint v3)
	{
		float half = size / 2.f;

		const vec3 corners[] = {
			vec3(center.x - half, center.y, center.z - half),
			vec3(center.x - half, center.y, center.z + half),
			vec3(center.x + half, center.y, center.z + half),
			vec3(center.x + half, center.y, center.z - half)
		};

		const vector<vec3> curve = {
			corners[v0],
			corners[v1],
			corners[v2],
			corners[v3]
		};

		// Recurse iterations
		if(0 <= --iterations)
		{
			vector<vec3> result = {};

			extend(result, hilbert2d(curve[0], half, iterations, v0, v3, v2, v1));
			extend(result, hilbert2d(curve[1], half, iterations, v0, v1, v2, v3));
			extend(result, hilbert2d(curve[2], half, iterations, v0, v1, v2, v3));
			extend(result, hilbert2d(curve[3], half, iterations, v2, v1, v0, v3));

			// Return recursive call
			return result;
		}

		// Return complete Hilbert Curve.
		return curve;

	}

	vector<vec3> hilbert3d(vec3 center, float size, int iterations, uint v0, uint v1, uint v2, uint v3, uint v4, uint v5, uint v6, uint v7)
	{
		float half = size / 2.f;

		const vec3 corners[] =
		{
			vec3(center.x - half, center.y + half, center.z - half),
			vec3(center.x - half, center.y + half, center.z + half),
			vec3(center.x - half, center.y - half, center.z + half),
			vec3(center.x - half, center.y - half, center.z - half),
			vec3(center.x + half, center.y - half, center.z - half),
			vec3(center.x + half, center.y - half, center.z + half),
			vec3(center.x + half, center.y + half, center.z + half),
			vec3(center.x + half, center.y + half, center.z - half)
		};

		const vector<vec3> curve = {
			corners[v0],
			corners[v1],
			corners[v2],
			corners[v3],
			corners[v4],
			corners[v5],
			corners[v6],
			corners[v7]
		};

		// Recurse iterations
		if (--iterations >= 0)
		{
			vector<vec3> result = {};

			extend(result, hilbert3d(curve[0], half, iterations, v0, v3, v4, v7, v6, v5, v2, v1 ));
			extend(result, hilbert3d(curve[1], half, iterations, v0, v7, v6, v1, v2, v5, v4, v3 ));
			extend(result, hilbert3d(curve[2], half, iterations, v0, v7, v6, v1, v2, v5, v4, v3 ));
			extend(result, hilbert3d(curve[3], half, iterations, v2, v3, v0, v1, v6, v7, v4, v5 ));
			extend(result, hilbert3d(curve[4], half, iterations, v2, v3, v0, v1, v6, v7, v4, v5 ));
			extend(result, hilbert3d(curve[5], half, iterations, v4, v3, v2, v5, v6, v1, v0, v7 ));
			extend(result, hilbert3d(curve[6], half, iterations, v4, v3, v2, v5, v6, v1, v0, v7 ));
			extend(result, hilbert3d(curve[7], half, iterations, v6, v5, v2, v1, v0, v3, v4, v7 ));

			// Return recursive call
			return result;
		}

		// Return complete Hilbert Curve.
		return curve;
	}
}


#ifdef MUD_MODULES
module mud.geom;
#else
#endif

#include <stl/swap.h>

namespace mud
{
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
		if(d > (r0 + r1))
		{
			/* no solution. circles do not intersect. */
			return false;
		}
		if(d < fabs(r0 - r1))
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
			return vec3(0.f); // @todo move to optional when C++17
		return result;
	}

	vec3 plane_segment_intersection(const vec3& P1, const vec3& P2, const vec3& P3, const vec3& L1, const vec3& L2)
	{
		vec3 N = cross(P2 - P1, P3 - P1);
		vec3 result = L1 + (dot(N, P1 - L1) / dot(N, L2 - L1)) * (L2 - L1);
		if(any(isnan(result)) || any(isinf(result)))
			return vec3(0.f); // @todo move to optional when C++17
		return result;
	}

	vec3 plane_3_intersection(const Plane& plane0, const Plane& plane1, const Plane& plane2)
	{
		vec3 normal0 = plane0.m_normal;
		vec3 normal1 = plane1.m_normal;
		vec3 normal2 = plane2.m_normal;

		float denom = dot(cross(normal0, normal1), normal2);

		if(abs(denom) <= c_cmp_epsilon)
			return vec3(0.f); // @todo move to optional when C++17

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

	bool sphere_aabb_intersection(const vec3& center, float radius, const Aabb& aabb)
	{
		vec3 min = aabb.m_center - aabb.m_extents;
		vec3 max = aabb.m_center + aabb.m_extents;

		float r2 = radius * radius;
		float dmin = 0.f;

		for(vec3::length_type i = 0; i < 3; ++i)
		{
			if(center[i] < min[i]) dmin += sq(center[i] - min[i]);
			else if(center[i] > max[i]) dmin += sq(center[i] - max[i]);
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

		float rr = m_overlap ? randf(point.radius, distance)
							 : randf(distance, distance * 2.f);
		float rt = randf(0.f, c_2pi);

		float x = rr * sin(rt) + point.position.x;
		float y = rr * cos(rt) + point.position.y;

		return { vec3(x, y, 0.f), radius };
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
				pushPoint({ vec3(randf(0.f, m_size.x), randf(0.f, m_size.y), 0.f), radius });
			else
				pushPoint({ vec3(0.5f, 0.5f, 0.f), radius });
			return true;
		}

		while(!m_unprocessed.empty())
		{
			uint index = randi(0U, uint(m_unprocessed.size()) - 1);
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
	Polygon::Polygon(span<vec3> vertices) : Shape(type<Polygon>()), m_vertices(vertices.begin(), vertices.end()) {}
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
	bool Circle::operator==(const Circle& other) const { return m_radius == other.m_radius && m_axis == other.m_axis && m_center == other.m_center; }
	object<Shape> Circle::clone() const { return oconstruct<Circle>(*this); }

	Torus::Torus() : Shape(type<Torus>()) {}
	Torus::Torus(float radius, float tube, Axis axis) : Shape(type<Torus>()), m_radius(radius), m_tube(tube), m_axis(axis) {}
	Torus::Torus(const vec3& center, float radius, float tube, Axis axis) : Shape(type<Torus>(), center), m_radius(radius), m_tube(tube), m_axis(axis) {}
	//bool Torus::operator==(const Torus& other) const { return m_radius == other.m_radius && m_tube == other.m_tube && m_axis == other.m_axis && m_center == other.m_center; }
	object<Shape> Torus::clone() const { return oconstruct<Torus>(*this); }

	TorusKnot::TorusKnot() : Shape(type<TorusKnot>()) {}
	TorusKnot::TorusKnot(float radius, float tube, float p, float q) : Shape(type<TorusKnot>()), m_radius(radius), m_tube(tube), m_p(p), m_q(q) {}
	TorusKnot::TorusKnot(const vec3& center, float radius, float tube, float p, float q) : Shape(type<TorusKnot>(), center), m_radius(radius), m_tube(tube), m_p(p), m_q(q) {}
	object<Shape> TorusKnot::clone() const { return oconstruct<TorusKnot>(*this); }

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
	Cylinder::Cylinder(const vec3& center, float radius, float height, Axis axis) : Shape(type<Cylinder>(), center), m_radius(radius), m_height(height), m_axis(axis) {}
	object<Shape> Cylinder::clone() const { return oconstruct<Cylinder>(*this); }

	Capsule::Capsule() : Shape(type<Capsule>()) {}
	Capsule::Capsule(float radius, float height, Axis axis) : Shape(type<Capsule>()), m_radius(radius), m_height(height), m_axis(axis) {}
	object<Shape> Capsule::clone() const { return oconstruct<Capsule>(*this); }

	Cube::Cube() : Shape(type<Cube>()) {}
	Cube::Cube(const vec3& extents) : Shape(type<Cube>()), m_extents(extents) {}
	Cube::Cube(const vec3& center, const vec3& extents) : Shape(type<Cube>(), center), m_extents(extents) {}
	Cube::Cube(float side) : Shape(type<Cube>()), m_extents(side, side, side) {}
	Cube::Cube(const Aabb& aabb) : Cube(aabb.m_center, aabb.m_extents) {}
	object<Shape> Cube::clone() const { return oconstruct<Cube>(*this); }

	Box::Box() : Shape(type<Box>()), m_vertices() {}
	object<Shape> Box::clone() const { return oconstruct<Box>(*this); }

	Tetraedr::Tetraedr() : Shape(type<Tetraedr>()) {}
	Tetraedr::Tetraedr(float radius) : Shape(type<Tetraedr>()), m_radius(radius) {}
	Tetraedr::Tetraedr(const vec3& center, float radius) : Shape(type<Tetraedr>(), center), m_radius(radius) {}
	object<Shape> Tetraedr::clone() const { return oconstruct<Tetraedr>(*this); }

	Sphere::Sphere() : Shape(type<Sphere>()) {}
	Sphere::Sphere(float radius, float start, float end) : Shape(type<Sphere>()), m_radius(radius), m_start(start), m_end(end) {}
	Sphere::Sphere(const vec3& center, float radius, float start, float end) : Shape(type<Sphere>(), center), m_radius(radius), m_start(start), m_end(end) {}
	object<Shape> Sphere::clone() const { return oconstruct<Sphere>(*this); }

	SphereRing::SphereRing() : Shape(type<SphereRing>()) {}
	SphereRing::SphereRing(float radius, float min, float max) : Shape(type<SphereRing>()), m_radius(radius), m_min(min), m_max(max) {}
	object<Shape> SphereRing::clone() const { return oconstruct<SphereRing>(*this); }

	Spheroid::Spheroid() : Shape(type<Spheroid>()) {}
	Spheroid::Spheroid(float radius) : Shape(type<Spheroid>()), m_radius(radius), m_circleX(radius, Axis::X), m_circleY(radius, Axis::Y), m_circleZ(radius, Axis::Z) {}
	Spheroid::Spheroid(const vec3& center, float radius) : Shape(type<Spheroid>(), center), m_radius(radius), m_circleX(radius, Axis::X), m_circleY(radius, Axis::Y), m_circleZ(radius, Axis::Z) {}
	object<Shape> Spheroid::clone() const { return oconstruct<Spheroid>(*this); }

	Icosaedr::Icosaedr() : Shape(type<Icosaedr>()) {}
	Icosaedr::Icosaedr(float radius) : Shape(type<Icosaedr>()), m_radius(radius) {}
	Icosaedr::Icosaedr(const vec3& center, float radius) : Shape(type<Icosaedr>(), center), m_radius(radius) {}
	object<Shape> Icosaedr::clone() const { return oconstruct<Icosaedr>(*this); }

	Points::Points() : Shape(type<Points>()) {}
	Points::Points(span<vec3> points) : Shape(type<Points>()), m_points(points.begin(), points.end()) {}
	object<Shape> Points::clone() const { return oconstruct<Points>(*this); }

	Grid3::Grid3() : Shape(type<Grid3>()) {}
	Grid3::Grid3(const uvec2& size, span<vec3> points) : Shape(type<Grid3>()), m_size(size), m_points(points.begin(), points.end()) { m_points.resize(size.x * size.y); }
	object<Shape> Grid3::clone() const { return oconstruct<Grid3>(*this); }

	ConvexHull::ConvexHull() : Shape(type<ConvexHull>()) {}
	ConvexHull::ConvexHull(span<vec3> vertices) : Shape(type<ConvexHull>()), m_vertices(vertices.begin(), vertices.end()) {}
	object<Shape> ConvexHull::clone() const { return oconstruct<ConvexHull>(*this); }

	Aabb aabb(const vec3& min, const vec3& max)
	{
		vec3 extents = (max - min) / 2.f;
		return Aabb(min + extents, extents);
	}

	Aabb::Aabb() : m_empty(true) {}
	Aabb::Aabb(const vec3& center, const vec3& extents) : m_center(center), m_extents(extents), m_empty(false) {}
	//object<Shape> Aabb::clone() const { return {}; } //oconstruct<Aabb>(*this); }

	vec3 Aabb::bmin() const { return m_center - m_extents; }
	vec3 Aabb::bmax() const { return m_center + m_extents; }

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

	void Aabb::merge(const Aabb& other)
	{
		if(other.m_empty) return;
		if(m_empty)
		{
			*this = other;
			return;
		}

		vec3 bmax = max(m_center + m_extents, other.m_center + other.m_extents);
		vec3 bmin = min(m_center - m_extents, other.m_center - other.m_extents);

		m_center = (bmax + bmin) * 0.5f;
		m_extents = (bmax - bmin) * 0.5f;
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

	bool Aabb::cull(span<vec3> points) const
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

	void quad_vertices(const vec2& size, const vec3& u, const vec3& v, span<vec3> vertices, const vec2& offset = vec2(0.f))
	{
		vec3 offset3d = u * offset.x + v * offset.y;
		vec3 a = (u * size.x + v * size.y) / 2.f;
		vec3 b = (u * size.x - v * size.y) / 2.f;
		vertices[0] = a + offset3d;
		vertices[1] = b + offset3d;
		vertices[2] = -a + offset3d;
		vertices[3] = -b + offset3d;
	}

	Quad::Quad(const vec2& size, const vec3& x, const vec3& y) : Shape(type<Quad>()) { quad_vertices(size, x, y, { m_vertices }); }
	Quad::Quad(const vec2& offset, const vec2& size, const vec3& x, const vec3& y) : Shape(type<Quad>()) { quad_vertices(size, x, y, { m_vertices }, offset); }
	Quad::Quad(const vec3& center, const vec2& size, const vec3& x, const vec3& y) : Shape(type<Quad>(), center) { quad_vertices(size, x, y, { m_vertices }); }
	Quad::Quad(const vec3& center, const vec2& offset, const vec2& size, const vec3& x, const vec3& y) : Shape(type<Quad>(), center) { quad_vertices(size, x, y, { m_vertices }, offset); }
	Quad::Quad(float size, const vec3& x, const vec3& y) : Quad(vec2(size), x, y) {}
	// @todo this should probably be Z3, X3 since default faces up and cross(z, x) = y
	// find out where in the geometry generation is the fuckup
	Quad::Quad(const Rect& rect) : Quad(rect.m_size, X3, Z3) {}

	void box_vertices(const vec3& center, const vec3& extents, span<vec3> vertices)
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

	Box::Box(span<vec3> vertices) : Shape(type<Box>()) { span<vec3> dest = { m_vertices }; copy(dest, vertices); }
	Box::Box(const Cube& cube) : Shape(type<Box>()) { box_vertices(cube.m_center, cube.m_extents, { m_vertices }); }

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
		m_fill.a = alpha;
	}

	Symbol::Symbol(const Image256& image, float alpha)
		: Symbol()
	{
		m_image256 = &const_cast<Image256&>(image);
		m_fill.a = alpha;
	}

	bool Symbol::operator==(const Symbol& other) const
	{
		UNUSED(other);
		return true;
	}

	inline vec3 distribute_sphere(float radius, float h = 2.f, float maxh = 1.f)
	{
		const float rand0 = randf(0.f, 1.f) * h - maxh;
		const float rand1 = randf(0.f, 1.f) * c_2pi;
		const float sqrtf1 = sqrt(1.0f - rand0 * rand0);

		return vec3(sqrtf1 * cos(rand1), sqrtf1 * sin(rand1), rand0) * radius;
	}

	inline vec3 distribute_spherical(float radius, float min, float max)
	{
		const float maxh = max * 2.0f - 1.0f;
		const float minh = min * 2.0f - 1.0f;
		return distribute_sphere(radius, maxh - minh, maxh);
	}

	inline vec3 distribute_circle(float radius)
	{
		const float angle = randf(0.f, 1.f) * c_2pi;
		return vec3(cos(angle), 0.0f, sin(angle)) * radius;
	}

	inline vec3 distribute_ring(float radius, float min = 0.f, float max = 1.f)
	{
		const float size = randf(min, max);
		vec3 pos = distribute_circle(radius);
		return pos * size;
	}

	inline vec3 distribute_rect(float width = 1.f, float height = 1.f)
	{
		const float x = randf(-1.f, 1.f);
		const float y = randf(-1.f, 1.f);
		return { x * width, 0.f, y * height };
	}

	inline vec3 distribute_points(span<vec3> points)
	{
		uint index = randi(0U, uint(points.size()) - 1U);
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
			return vector<vec3>(count, vec3(0.f));

		vector<vec3> points(count);
		for(size_t i = 0; i < count; ++i)
			points[i] = RandomShapePoint::me().dispatch(Ref(&shape));
		return points;
	}
}

#ifdef MUD_MODULES
module mud.geom;
#else
#include <stl/algorithm.h>
#include <stl/table.h>
#endif

#define FLAT false
#define FLAT_BLEND 1

namespace mud
{
	extern const int c_edge_table[];

	struct CubeSide { int num; int tris[16]; };
	extern const CubeSide c_tri_table[];

	MarchingCubes::MarchingCubes(uint32_t subdiv)
	{
		// size of field, 32 is pushing it in Javascript :)
		m_subdiv = subdiv;
		m_size = subdiv * subdiv * subdiv;
		m_extent = m_subdiv / 2.0f;

		m_delta = 2.0f / float(subdiv);

		m_xd = 1;
		m_yd = subdiv;
		m_zd = subdiv * subdiv;

		m_field.resize(m_size);
		m_colour.resize(m_size);
	}
	
	uint8_t MarchingCubes::classify(size_t q, float isol) const
	{
		struct Cell { size_t q; float f; };
		auto cell = [&](size_t q) -> Cell { return { q, m_field[q] }; };
		// cache indices
		const Cell c = cell(q);
		const Cell cx = cell(q + 1);
		const Cell cy = cell(q + m_yd);
		const Cell cz = cell(q + m_zd);
		const Cell cxy = cell(q + 1 + m_yd);
		const Cell cxz = cell(q + 1 + m_zd);
		const Cell cyz = cell(q + m_yd + m_zd);
		const Cell cxyz = cell(q + 1 + m_yd + m_zd);

		uint8_t cubeindex = 0;

		if(c.f    < isol) cubeindex |= 1;
		if(cx.f   < isol) cubeindex |= 2;
		if(cy.f   < isol) cubeindex |= 8;
		if(cxy.f  < isol) cubeindex |= 4;
		if(cz.f   < isol) cubeindex |= 16;
		if(cxz.f  < isol) cubeindex |= 32;
		if(cyz.f  < isol) cubeindex |= 128;
		if(cxyz.f < isol) cubeindex |= 64;

		return cubeindex;
	}

	inline void calc_normal(MarchingCubes::Cache& cache, const MarchingCubes& cubes, size_t q)
	{
		if(!cache.m_normal[q].set)
		{
			cache.m_normal[q].n.x = cubes.m_field[q - 1] - cubes.m_field[q + 1];
			cache.m_normal[q].n.y = cubes.m_field[q - cubes.m_yd] - cubes.m_field[q + cubes.m_yd];
			cache.m_normal[q].n.z = cubes.m_field[q - cubes.m_zd] - cubes.m_field[q + cubes.m_zd];
			cache.m_normal[q].set = true;
		}
	};

	struct Cell { size_t q; float f; };

	template <Axis axis, bool flat>
	inline void calc_side(MarchingCubes::Cache& cache, const MarchingCubes& cubes, int bits, int mask, int i, float isol, const vec3& p, const Cell& a, const Cell& b)
	{
		if(bits & mask)
		{
#if !FLAT_BLEND
			if constexpr(!flat)
#endif
			{
				calc_normal(cache, cubes, a.q);
				calc_normal(cache, cubes, b.q);
			}

			const float mu = (isol - a.f) / (b.f - a.f);

			if constexpr(axis == Axis::X)
				cache.vert[i] = vec3(p.x + mu * cubes.m_delta, p.y, p.z);
			else if constexpr(axis == Axis::Y)
				cache.vert[i] = vec3(p.x, p.y + mu * cubes.m_delta, p.z);
			else if constexpr(axis == Axis::Z)
				cache.vert[i] = vec3(p.x, p.y, p.z + mu * cubes.m_delta);

#if !FLAT_BLEND
			if constexpr(!flat)
#endif
				cache.norm[i] = lerp(cache.m_normal[a.q].n, cache.m_normal[b.q].n, mu);

			cache.color[i] = lerp(cubes.m_colour[a.q], cubes.m_colour[b.q], mu);
		}
	};

	uint8_t MarchingCubes::polygonize(Cache& cache, const vec3& p, size_t q, float isol) const
	{
		auto cell = [&](size_t q) -> Cell { return { q, m_field[q] }; };
		// cache indices
		const Cell c = cell(q);
		const Cell cx = cell(q + 1);
		const Cell cy = cell(q + m_yd);
		const Cell cz = cell(q + m_zd);
		const Cell cxy = cell(q + 1 + m_yd);
		const Cell cxz = cell(q + 1 + m_zd);
		const Cell cyz = cell(q + m_yd + m_zd);
		const Cell cxyz = cell(q + 1 + m_yd + m_zd);

		uint8_t cubeindex = 0;

		if(c.f    < isol) cubeindex |= 1;
		if(cx.f   < isol) cubeindex |= 2;
		if(cy.f   < isol) cubeindex |= 8;
		if(cxy.f  < isol) cubeindex |= 4;
		if(cz.f   < isol) cubeindex |= 16;
		if(cxz.f  < isol) cubeindex |= 32;
		if(cyz.f  < isol) cubeindex |= 128;
		if(cxyz.f < isol) cubeindex |= 64;

		// if cube is entirely in/out of the surface - bail, nothing to draw

		const int bits = c_edge_table[cubeindex];
		if(bits == 0) return 0;

		const float d = m_delta;
		const vec3 pp = p + d;

		// top of the cube

		// top of the cube
		calc_side<Axis::X, FLAT>(cache, *this, bits, 1,    0,  isol, vec3(p.x,  p.y,  p.z ), c,   cx);
		calc_side<Axis::Y, FLAT>(cache, *this, bits, 2,    1,  isol, vec3(pp.x, p.y,  p.z ), cx,  cxy);
		calc_side<Axis::X, FLAT>(cache, *this, bits, 4,    2,  isol, vec3(p.x,  pp.y, p.z ), cy,  cxy);
		calc_side<Axis::Y, FLAT>(cache, *this, bits, 8,    3,  isol, vec3(p.x,  p.y,  p.z ), c,   cy);
		calc_side<Axis::X, FLAT>(cache, *this, bits, 16,   4,  isol, vec3(p.x,  p.y,  pp.z), cz,  cxz);
		calc_side<Axis::Y, FLAT>(cache, *this, bits, 32,   5,  isol, vec3(pp.x, p.y,  pp.z), cxz, cxyz);
		calc_side<Axis::X, FLAT>(cache, *this, bits, 64,   6,  isol, vec3(p.x,  pp.y, pp.z), cyz, cxyz);
		calc_side<Axis::Y, FLAT>(cache, *this, bits, 128,  7,  isol, vec3(p.x,  p.y,  pp.z), cz,  cyz);
		calc_side<Axis::Z, FLAT>(cache, *this, bits, 256,  8,  isol, vec3(p.x,  p.y,  p.z ), c,   cz);
		calc_side<Axis::Z, FLAT>(cache, *this, bits, 512,  9,  isol, vec3(pp.x, p.y,  p.z ), cx,  cxz);
		calc_side<Axis::Z, FLAT>(cache, *this, bits, 1024, 10, isol, vec3(pp.x, pp.y, p.z ), cxy, cxyz);
		calc_side<Axis::Z, FLAT>(cache, *this, bits, 2048, 11, isol, vec3(p.x,  pp.y, p.z ), cy,  cyz);

		return cubeindex;
	}

	uint32_t MarchingCubes::triangulate(MeshAdapter& output, Cache& cache, uint8_t cubeindex) const
	{
		const CubeSide& side = c_tri_table[cubeindex];

		auto triangle = [&](size_t o1, size_t o2, size_t o3, bool flat = false)
		{
			output.dposition(cache.vert[o1]);
			output.dposition(cache.vert[o2]);
			output.dposition(cache.vert[o3]);

			if(flat)
			{
#if FLAT_BLEND
				vec3 n = normalize(cache.norm[o1] + cache.norm[o2] + cache.norm[o3]);
#else
				vec3 n = normalize(cross(cache.vert[o2] - cache.vert[o1], cache.vert[o3] - cache.vert[o1]));
#endif
				output.normal(n);
				output.normal(n);
				output.normal(n);
			}
			else
			{
				output.normal(cache.norm[o1]);
				output.normal(cache.norm[o2]);
				output.normal(cache.norm[o3]);
			}

			if((output.m_vertex_format & VertexAttribute::TexCoord0) != 0)
			{
				output.duv0(vec2(cache.vert[o1]));
				output.duv0(vec2(cache.vert[o2]));
				output.duv0(vec2(cache.vert[o3]));
			}

			if((output.m_vertex_format & VertexAttribute::Colour) != 0)
			{
				output.colour(cache.color[o1]);
				output.colour(cache.color[o2]);
				output.colour(cache.color[o3]);
			}
		};

		size_t i = 0;
		while(side.tris[i] != -1)
		{
			triangle(side.tris[i+0], side.tris[i+1], side.tris[i+2], FLAT);
			i += 3;
		}

		//assert(i / 3 == side.num);
		return uint32_t(side.num);
	}

	uint32_t MarchingCubes::triangulate(MeshPacker& output, Cache& cache, uint8_t cubeindex) const
	{
		const CubeSide& side = c_tri_table[cubeindex];

		auto triangle = [&](size_t o1, size_t o2, size_t o3, bool flat = false)
		{
			output.m_positions.push_back(cache.vert[o1]);
			output.m_positions.push_back(cache.vert[o2]);
			output.m_positions.push_back(cache.vert[o3]);

			if(flat)
			{
#if FLAT_BLEND
				vec3 n = normalize(cache.norm[o1] + cache.norm[o2] + cache.norm[o3]);
#else
				vec3 n = normalize(cross(cache.vert[o2] - cache.vert[o1], cache.vert[o3] - cache.vert[o1]));
#endif
				output.m_normals.push_back(n);
				output.m_normals.push_back(n);
				output.m_normals.push_back(n);
			}
			else
			{
				output.m_normals.push_back(cache.norm[o1]);
				output.m_normals.push_back(cache.norm[o2]);
				output.m_normals.push_back(cache.norm[o3]);
			}

			if(false) //output.m_has_uvs)
			{
				output.m_uv0s.push_back(vec2(cache.vert[o1]));
				output.m_uv0s.push_back(vec2(cache.vert[o2]));
				output.m_uv0s.push_back(vec2(cache.vert[o3]));
			}
			
			if(false) //output.m_has_colors)
			{
				output.m_colours.push_back(to_colour(cache.color[o1]));
				output.m_colours.push_back(to_colour(cache.color[o2]));
				output.m_colours.push_back(to_colour(cache.color[o3]));
			}
		};

		size_t i = 0;
		while(side.tris[i] != -1)
		{
			triangle(side.tris[i+0], side.tris[i+1], side.tris[i+2], FLAT);
			i += 3;
		}

		//assert(i / 3 == side.num);
		return uint32_t(side.num);
	}

	void MarchingCubes::reset()
	{
		for(size_t i = 0; i < m_size; i++)
		{
			m_field[i] = 0.f;
			m_colour[i] = vec3(0.f);
		}
	}

	void MarchingCubes::begin(Cache& cache) const
	{
		if(cache.m_normal.size() != m_size)
			cache.m_normal.resize(m_size);

		//for(size_t i = 0; i < m_size; i++)
		//	cache.m_normal[i].set = false;

		memset(cache.m_normal.data(), 0, cache.m_normal.size() * sizeof(Cache::Normal));
	}

	uint32_t MarchingCubes::count() const
	{
		uint32_t num_tris = 0;

		const uint32_t subdiv = m_subdiv - 2;
		for(uint32_t z = 1; z < subdiv; z++)
			for(uint32_t y = 1; y < subdiv; y++)
				for(uint32_t x = 1; x < subdiv; x++)
				{
					const size_t q = m_zd * z + m_yd * y + x;
					const uint8_t cubeindex = classify(q, m_isolation);
					num_tris += c_tri_table[cubeindex].num;
				}

		return num_tris;
	}

	void MarchingCubes::direct(MeshAdapter& output) const
	{
		this->begin(m_cache);

		const uint32_t subdiv = m_subdiv - 2;
		for(uint32_t z = 1; z < subdiv; z++)
			for(uint32_t y = 1; y < subdiv; y++)
				for(uint32_t x = 1; x < subdiv; x++)
				{
					const size_t q = m_zd * z + m_yd * y + x;
					const vec3 f = (vec3(float(x), float(y), float(z)) - m_extent) / m_extent; //+ 1
					const uint8_t cubeindex = polygonize(m_cache, f, q, m_isolation);
					triangulate(output, m_cache, cubeindex);
				}
	}

	void MarchingCubes::render(MeshPacker& output) const
	{
		this->begin(m_cache);

		const uint32_t subdiv = m_subdiv - 2;

		for(uint32_t z = 1; z < subdiv; z++)
			for(uint32_t y = 1; y < subdiv; y++)
				for(uint32_t x = 1; x < subdiv; x++)
				{
					const size_t q = m_zd * z + m_yd * y + x;
					const vec3 f = (vec3(uvec3(x, y, z)) - m_extent) / m_extent; //+ 1
					const uint8_t cubeindex = polygonize(m_cache, f, q, m_isolation);
					triangulate(output, m_cache, cubeindex);
				}
	}

	void add_ball(MarchingCubes& cubes, const vec3& ball, float strength, float subtract, const Colour& colour)
	{
		const float sign = mud::sign(strength);
		strength = abs(strength);

		// Let's solve the equation to find the radius:
		// 1.0 / (0.000001 + radius^2) * strength - subtract = 0
		// -> radius = sqrt(strength / subtract)

		const float size = float(cubes.m_subdiv);
		const float radius = size * sqrt(strength / subtract);
		const vec3 s = ball * size;

		// Don't polygonize in the outer layer because normals aren't well-defined there.
		const uvec3 lo = uvec3(max(ivec3(floor(s - radius)), ivec3(1)));
		const uvec3 hi = uvec3(min(ivec3(floor(s + radius)), ivec3(int(cubes.m_subdiv - 1))));

		for(uint32_t z = lo.z; z < hi.z; z++)
			for(uint32_t y = lo.y; y < hi.y; y++)
				for(uint32_t x = lo.x; x < hi.x; x++)
				{
					const size_t offset = cubes.m_zd * z + cubes.m_yd * y + x;

					const vec3 p = vec3(uvec3(x, y, z));
					const vec3 f = p / size - ball;

					const float val = strength / (0.000001f + sq(f.x) + sq(f.y) + sq(f.z)) - subtract;
					if(val > 0.f)
					{
						cubes.m_field[offset] += val * sign;
						
						// optimization - http://www.geisswerks.com/ryan/BLOBS/blobs.html
						const float r = sqrt(sq(p.x - s.x) + sq(p.y - s.y) + sq(p.z - s.z)) / radius;
						const float contrib = 1.f - r * r * r * (r * (r * 6.f - 15.f ) + 10.f );
						cubes.m_colour[offset] += to_vec3(colour) * contrib;
					}
				}
	}

	void add_ball(MarchingCubes& cubes, const vec3& ball, float strength, float subtract)
	{
		add_ball(cubes, ball, strength, subtract, Colour(ball.x, ball.y, ball.z));
	}

	void add_planeX(MarchingCubes& cubes, float strength, float subtract)
	{
		const size_t subdiv = cubes.m_subdiv;
		const float size = float(cubes.m_subdiv);
		const size_t yd = cubes.m_yd;
		const size_t zd = cubes.m_zd;
		vector<float>& field = cubes.m_field;

		//const size_t dist = size_t(min(size, size * sqrt(strength / subtract)));
		const size_t dist = size_t(min(size, size * float(sqrt(strength / subtract)))); // clang, why do you hate me

		for(size_t x = 0; x < dist; x++)
		{
			const float xdiv = float(x) / size;
			const float xx = xdiv * xdiv;
			const float val = strength / (0.0001f + xx) - subtract;

			if(val <= 0.0) continue;

			for(size_t y = 0; y < subdiv; y++)
			{
				const size_t cxy = x + y * yd;

				for(size_t z = 0; z < subdiv; z++)
					field[zd * z + cxy] += val;
			}
		}
	}

	void add_planeY(MarchingCubes& cubes, float strength, float subtract)
	{
		const size_t subdiv = cubes.m_subdiv;
		const float size = float(cubes.m_subdiv);
		const size_t yd = cubes.m_yd;
		const size_t zd = cubes.m_zd;
		vector<float>& field = cubes.m_field;

		//const size_t dist = size_t(min(size, size * sqrt(strength / subtract)));
		const size_t dist = size_t(min(size, size * float(sqrt(strength / subtract)))); // clang, why do you hate me

		for(size_t y = 0; y < dist; y++)
		{
			const float ydiv = y / size;
			const float yy = ydiv * ydiv;
			const float val = strength / (0.0001f + yy) - subtract;

			if(val <= 0.f) continue;

			const size_t cy = y * yd;

			for(size_t x = 0; x < subdiv; x++)
			{
				const size_t cxy = cy + x;

				for(size_t z = 0; z < subdiv; z++)
					field[zd * z + cxy] += val;
			}
		}
	}

	void add_planeZ(MarchingCubes& cubes, float strength, float subtract)
	{
		const size_t subdiv = cubes.m_subdiv;
		const float size = float(cubes.m_subdiv);
		const size_t yd = cubes.m_yd;
		const size_t zd = cubes.m_zd;
		vector<float>& field = cubes.m_field;

		//const size_t dist = size_t(min(size, size * sqrt(strength / subtract)));
		const size_t dist = size_t(min(size, size * float(sqrt(strength / subtract)))); // clang, why do you hate me

		for(size_t z = 0; z < dist; z++)
		{
			const float zdiv = z / size;
			const float zz = zdiv * zdiv;
			const float val = strength / (0.0001f + zz) - subtract;
			if(val <= 0.f) continue;

			const size_t cz = zd * z;

			for(size_t y = 0; y < subdiv; y++)
			{
				const size_t cyz = cz + y * yd;

				for(size_t x = 0; x < subdiv; x++)
					field[cyz + x] += val;
			}
		}
	}


	// These tables are straight from Paul Bourke's page:
	// http://paulbourke.net/geometry/polygonise/
	// who in turn got them from Cory Gene Bloyd.

	const int c_edge_table[] =
	{
		0x0, 0x109, 0x203, 0x30a, 0x406, 0x50f, 0x605, 0x70c,
		0x80c, 0x905, 0xa0f, 0xb06, 0xc0a, 0xd03, 0xe09, 0xf00,
		0x190, 0x99, 0x393, 0x29a, 0x596, 0x49f, 0x795, 0x69c,
		0x99c, 0x895, 0xb9f, 0xa96, 0xd9a, 0xc93, 0xf99, 0xe90,
		0x230, 0x339, 0x33, 0x13a, 0x636, 0x73f, 0x435, 0x53c,
		0xa3c, 0xb35, 0x83f, 0x936, 0xe3a, 0xf33, 0xc39, 0xd30,
		0x3a0, 0x2a9, 0x1a3, 0xaa, 0x7a6, 0x6af, 0x5a5, 0x4ac,
		0xbac, 0xaa5, 0x9af, 0x8a6, 0xfaa, 0xea3, 0xda9, 0xca0,
		0x460, 0x569, 0x663, 0x76a, 0x66, 0x16f, 0x265, 0x36c,
		0xc6c, 0xd65, 0xe6f, 0xf66, 0x86a, 0x963, 0xa69, 0xb60,
		0x5f0, 0x4f9, 0x7f3, 0x6fa, 0x1f6, 0xff, 0x3f5, 0x2fc,
		0xdfc, 0xcf5, 0xfff, 0xef6, 0x9fa, 0x8f3, 0xbf9, 0xaf0,
		0x650, 0x759, 0x453, 0x55a, 0x256, 0x35f, 0x55, 0x15c,
		0xe5c, 0xf55, 0xc5f, 0xd56, 0xa5a, 0xb53, 0x859, 0x950,
		0x7c0, 0x6c9, 0x5c3, 0x4ca, 0x3c6, 0x2cf, 0x1c5, 0xcc,
		0xfcc, 0xec5, 0xdcf, 0xcc6, 0xbca, 0xac3, 0x9c9, 0x8c0,
		0x8c0, 0x9c9, 0xac3, 0xbca, 0xcc6, 0xdcf, 0xec5, 0xfcc,
		0xcc, 0x1c5, 0x2cf, 0x3c6, 0x4ca, 0x5c3, 0x6c9, 0x7c0,
		0x950, 0x859, 0xb53, 0xa5a, 0xd56, 0xc5f, 0xf55, 0xe5c,
		0x15c, 0x55, 0x35f, 0x256, 0x55a, 0x453, 0x759, 0x650,
		0xaf0, 0xbf9, 0x8f3, 0x9fa, 0xef6, 0xfff, 0xcf5, 0xdfc,
		0x2fc, 0x3f5, 0xff, 0x1f6, 0x6fa, 0x7f3, 0x4f9, 0x5f0,
		0xb60, 0xa69, 0x963, 0x86a, 0xf66, 0xe6f, 0xd65, 0xc6c,
		0x36c, 0x265, 0x16f, 0x66, 0x76a, 0x663, 0x569, 0x460,
		0xca0, 0xda9, 0xea3, 0xfaa, 0x8a6, 0x9af, 0xaa5, 0xbac,
		0x4ac, 0x5a5, 0x6af, 0x7a6, 0xaa, 0x1a3, 0x2a9, 0x3a0,
		0xd30, 0xc39, 0xf33, 0xe3a, 0x936, 0x83f, 0xb35, 0xa3c,
		0x53c, 0x435, 0x73f, 0x636, 0x13a, 0x33, 0x339, 0x230,
		0xe90, 0xf99, 0xc93, 0xd9a, 0xa96, 0xb9f, 0x895, 0x99c,
		0x69c, 0x795, 0x49f, 0x596, 0x29a, 0x393, 0x99, 0x190,
		0xf00, 0xe09, 0xd03, 0xc0a, 0xb06, 0xa0f, 0x905, 0x80c,
		0x70c, 0x605, 0x50f, 0x406, 0x30a, 0x203, 0x109, 0x0
	};

	const CubeSide c_tri_table[] =
	{
		{ 0, { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 1, { 0, 8, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 1, { 0, 1, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 1, 8, 3, 9, 8, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 1, { 1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 0, 8, 3, 1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 9, 2, 10, 0, 2, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 2, 8, 3, 2, 10, 8, 10, 9, 8, -1, -1, -1, -1, -1, -1, -1 } },
		{ 1, { 3, 11, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 0, 11, 2, 8, 11, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 1, 9, 0, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 1, 11, 2, 1, 9, 11, 9, 8, 11, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 3, 10, 1, 11, 10, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 0, 10, 1, 0, 8, 10, 8, 11, 10, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 3, 9, 0, 3, 11, 9, 11, 10, 9, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 9, 8, 10, 10, 8, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 1, { 4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 4, 3, 0, 7, 3, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 0, 1, 9, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 4, 1, 9, 4, 7, 1, 7, 3, 1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 1, 2, 10, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 3, 4, 7, 3, 0, 4, 1, 2, 10, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 9, 2, 10, 9, 0, 2, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 2, 10, 9, 2, 9, 7, 2, 7, 3, 7, 9, 4, -1, -1, -1, -1 } },
		{ 2, { 8, 4, 7, 3, 11, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 11, 4, 7, 11, 2, 4, 2, 0, 4, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 9, 0, 1, 8, 4, 7, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 4, 7, 11, 9, 4, 11, 9, 11, 2, 9, 2, 1, -1, -1, -1, -1 } },
		{ 3, { 3, 10, 1, 3, 11, 10, 7, 8, 4, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 1, 11, 10, 1, 4, 11, 1, 0, 4, 7, 11, 4, -1, -1, -1, -1 } },
		{ 4, { 4, 7, 8, 9, 0, 11, 9, 11, 10, 11, 0, 3, -1, -1, -1, -1 } },
		{ 3, { 4, 7, 11, 4, 11, 9, 9, 11, 10, -1, -1, -1, -1, -1, -1, -1 } },
		{ 1, { 9, 5, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 9, 5, 4, 0, 8, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 0, 5, 4, 1, 5, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 8, 5, 4, 8, 3, 5, 3, 1, 5, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 1, 2, 10, 9, 5, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 3, 0, 8, 1, 2, 10, 4, 9, 5, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 5, 2, 10, 5, 4, 2, 4, 0, 2, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 2, 10, 5, 3, 2, 5, 3, 5, 4, 3, 4, 8, -1, -1, -1, -1 } },
		{ 2, { 9, 5, 4, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 0, 11, 2, 0, 8, 11, 4, 9, 5, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 0, 5, 4, 0, 1, 5, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 2, 1, 5, 2, 5, 8, 2, 8, 11, 4, 8, 5, -1, -1, -1, -1 } },
		{ 3, { 10, 3, 11, 10, 1, 3, 9, 5, 4, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 4, 9, 5, 0, 8, 1, 8, 10, 1, 8, 11, 10, -1, -1, -1, -1 } },
		{ 4, { 5, 4, 0, 5, 0, 11, 5, 11, 10, 11, 0, 3, -1, -1, -1, -1 } },
		{ 3, { 5, 4, 8, 5, 8, 10, 10, 8, 11, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 9, 7, 8, 5, 7, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 9, 3, 0, 9, 5, 3, 5, 7, 3, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 0, 7, 8, 0, 1, 7, 1, 5, 7, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 1, 5, 3, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 9, 7, 8, 9, 5, 7, 10, 1, 2, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 10, 1, 2, 9, 5, 0, 5, 3, 0, 5, 7, 3, -1, -1, -1, -1 } },
		{ 4, { 8, 0, 2, 8, 2, 5, 8, 5, 7, 10, 5, 2, -1, -1, -1, -1 } },
		{ 3, { 2, 10, 5, 2, 5, 3, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 7, 9, 5, 7, 8, 9, 3, 11, 2, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 9, 5, 7, 9, 7, 2, 9, 2, 0, 2, 7, 11, -1, -1, -1, -1 } },
		{ 4, { 2, 3, 11, 0, 1, 8, 1, 7, 8, 1, 5, 7, -1, -1, -1, -1 } },
		{ 3, { 11, 2, 1, 11, 1, 7, 7, 1, 5, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 9, 5, 8, 8, 5, 7, 10, 1, 3, 10, 3, 11, -1, -1, -1, -1 } },
		{ 5, { 5, 7, 0, 5, 0, 9, 7, 11, 0, 1, 0, 10, 11, 10, 0, -1 } },
		{ 5, { 11, 10, 0, 11, 0, 3, 10, 5, 0, 8, 0, 7, 5, 7, 0, -1 } },
		{ 2, { 11, 10, 5, 7, 11, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 1, { 10, 6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 0, 8, 3, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 9, 0, 1, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 1, 8, 3, 1, 9, 8, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 1, 6, 5, 2, 6, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 1, 6, 5, 1, 2, 6, 3, 0, 8, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 9, 6, 5, 9, 0, 6, 0, 2, 6, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 5, 9, 8, 5, 8, 2, 5, 2, 6, 3, 2, 8, -1, -1, -1, -1 } },
		{ 2, { 2, 3, 11, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 11, 0, 8, 11, 2, 0, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 0, 1, 9, 2, 3, 11, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 5, 10, 6, 1, 9, 2, 9, 11, 2, 9, 8, 11, -1, -1, -1, -1 } },
		{ 3, { 6, 3, 11, 6, 5, 3, 5, 1, 3, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 0, 8, 11, 0, 11, 5, 0, 5, 1, 5, 11, 6, -1, -1, -1, -1 } },
		{ 4, { 3, 11, 6, 0, 3, 6, 0, 6, 5, 0, 5, 9, -1, -1, -1, -1 } },
		{ 3, { 6, 5, 9, 6, 9, 11, 11, 9, 8, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 5, 10, 6, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 4, 3, 0, 4, 7, 3, 6, 5, 10, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 1, 9, 0, 5, 10, 6, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 10, 6, 5, 1, 9, 7, 1, 7, 3, 7, 9, 4, -1, -1, -1, -1 } },
		{ 3, { 6, 1, 2, 6, 5, 1, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 1, 2, 5, 5, 2, 6, 3, 0, 4, 3, 4, 7, -1, -1, -1, -1 } },
		{ 4, { 8, 4, 7, 9, 0, 5, 0, 6, 5, 0, 2, 6, -1, -1, -1, -1 } },
		{ 5, { 7, 3, 9, 7, 9, 4, 3, 2, 9, 5, 9, 6, 2, 6, 9, -1 } },
		{ 3, { 3, 11, 2, 7, 8, 4, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 5, 10, 6, 4, 7, 2, 4, 2, 0, 2, 7, 11, -1, -1, -1, -1 } },
		{ 4, { 0, 1, 9, 4, 7, 8, 2, 3, 11, 5, 10, 6, -1, -1, -1, -1 } },
		{ 5, { 9, 2, 1, 9, 11, 2, 9, 4, 11, 7, 11, 4, 5, 10, 6, -1 } },
		{ 4, { 8, 4, 7, 3, 11, 5, 3, 5, 1, 5, 11, 6, -1, -1, -1, -1 } },
		{ 5, { 5, 1, 11, 5, 11, 6, 1, 0, 11, 7, 11, 4, 0, 4, 11, -1 } },
		{ 5, { 0, 5, 9, 0, 6, 5, 0, 3, 6, 11, 6, 3, 8, 4, 7, -1 } },
		{ 4, { 6, 5, 9, 6, 9, 11, 4, 7, 9, 7, 11, 9, -1, -1, -1, -1 } },
		{ 2, { 10, 4, 9, 6, 4, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 4, 10, 6, 4, 9, 10, 0, 8, 3, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 10, 0, 1, 10, 6, 0, 6, 4, 0, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 8, 3, 1, 8, 1, 6, 8, 6, 4, 6, 1, 10, -1, -1, -1, -1 } },
		{ 3, { 1, 4, 9, 1, 2, 4, 2, 6, 4, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 3, 0, 8, 1, 2, 9, 2, 4, 9, 2, 6, 4, -1, -1, -1, -1 } },
		{ 2, { 0, 2, 4, 4, 2, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 8, 3, 2, 8, 2, 4, 4, 2, 6, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 10, 4, 9, 10, 6, 4, 11, 2, 3, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 0, 8, 2, 2, 8, 11, 4, 9, 10, 4, 10, 6, -1, -1, -1, -1 } },
		{ 4, { 3, 11, 2, 0, 1, 6, 0, 6, 4, 6, 1, 10, -1, -1, -1, -1 } },
		{ 5, { 6, 4, 1, 6, 1, 10, 4, 8, 1, 2, 1, 11, 8, 11, 1, -1 } },
		{ 4, { 9, 6, 4, 9, 3, 6, 9, 1, 3, 11, 6, 3, -1, -1, -1, -1 } },
		{ 5, { 8, 11, 1, 8, 1, 0, 11, 6, 1, 9, 1, 4, 6, 4, 1, -1 } },
		{ 3, { 3, 11, 6, 3, 6, 0, 0, 6, 4, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 6, 4, 8, 11, 6, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 7, 10, 6, 7, 8, 10, 8, 9, 10, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 0, 7, 3, 0, 10, 7, 0, 9, 10, 6, 7, 10, -1, -1, -1, -1 } },
		{ 4, { 10, 6, 7, 1, 10, 7, 1, 7, 8, 1, 8, 0, -1, -1, -1, -1 } },
		{ 3, { 10, 6, 7, 10, 7, 1, 1, 7, 3, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 1, 2, 6, 1, 6, 8, 1, 8, 9, 8, 6, 7, -1, -1, -1, -1 } },
		{ 5, { 2, 6, 9, 2, 9, 1, 6, 7, 9, 0, 9, 3, 7, 3, 9, -1 } },
		{ 3, { 7, 8, 0, 7, 0, 6, 6, 0, 2, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 7, 3, 2, 6, 7, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 2, 3, 11, 10, 6, 8, 10, 8, 9, 8, 6, 7, -1, -1, -1, -1 } },
		{ 5, { 2, 0, 7, 2, 7, 11, 0, 9, 7, 6, 7, 10, 9, 10, 7, -1 } },
		{ 5, { 1, 8, 0, 1, 7, 8, 1, 10, 7, 6, 7, 10, 2, 3, 11, -1 } },
		{ 4, { 11, 2, 1, 11, 1, 7, 10, 6, 1, 6, 7, 1, -1, -1, -1, -1 } },
		{ 5, { 8, 9, 6, 8, 6, 7, 9, 1, 6, 11, 6, 3, 1, 3, 6, -1 } },
		{ 2, { 0, 9, 1, 11, 6, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 7, 8, 0, 7, 0, 6, 3, 11, 0, 11, 6, 0, -1, -1, -1, -1 } },
		{ 1, { 7, 11, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 1, { 7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 3, 0, 8, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 0, 1, 9, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 8, 1, 9, 8, 3, 1, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 10, 1, 2, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 1, 2, 10, 3, 0, 8, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 2, 9, 0, 2, 10, 9, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 6, 11, 7, 2, 10, 3, 10, 8, 3, 10, 9, 8, -1, -1, -1, -1 } },
		{ 2, { 7, 2, 3, 6, 2, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 7, 0, 8, 7, 6, 0, 6, 2, 0, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 2, 7, 6, 2, 3, 7, 0, 1, 9, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 1, 6, 2, 1, 8, 6, 1, 9, 8, 8, 7, 6, -1, -1, -1, -1 } },
		{ 3, { 10, 7, 6, 10, 1, 7, 1, 3, 7, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 10, 7, 6, 1, 7, 10, 1, 8, 7, 1, 0, 8, -1, -1, -1, -1 } },
		{ 4, { 0, 3, 7, 0, 7, 10, 0, 10, 9, 6, 10, 7, -1, -1, -1, -1 } },
		{ 3, { 7, 6, 10, 7, 10, 8, 8, 10, 9, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 6, 8, 4, 11, 8, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 3, 6, 11, 3, 0, 6, 0, 4, 6, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 8, 6, 11, 8, 4, 6, 9, 0, 1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 9, 4, 6, 9, 6, 3, 9, 3, 1, 11, 3, 6, -1, -1, -1, -1 } },
		{ 3, { 6, 8, 4, 6, 11, 8, 2, 10, 1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 1, 2, 10, 3, 0, 11, 0, 6, 11, 0, 4, 6, -1, -1, -1, -1 } },
		{ 4, { 4, 11, 8, 4, 6, 11, 0, 2, 9, 2, 10, 9, -1, -1, -1, -1 } },
		{ 5, { 10, 9, 3, 10, 3, 2, 9, 4, 3, 11, 3, 6, 4, 6, 3, -1 } },
		{ 3, { 8, 2, 3, 8, 4, 2, 4, 6, 2, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 0, 4, 2, 4, 6, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 1, 9, 0, 2, 3, 4, 2, 4, 6, 4, 3, 8, -1, -1, -1, -1 } },
		{ 3, { 1, 9, 4, 1, 4, 2, 2, 4, 6, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 8, 1, 3, 8, 6, 1, 8, 4, 6, 6, 10, 1, -1, -1, -1, -1 } },
		{ 3, { 10, 1, 0, 10, 0, 6, 6, 0, 4, -1, -1, -1, -1, -1, -1, -1 } },
		{ 5, { 4, 6, 3, 4, 3, 8, 6, 10, 3, 0, 3, 9, 10, 9, 3, -1 } },
		{ 2, { 10, 9, 4, 6, 10, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 4, 9, 5, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 0, 8, 3, 4, 9, 5, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 5, 0, 1, 5, 4, 0, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 11, 7, 6, 8, 3, 4, 3, 5, 4, 3, 1, 5, -1, -1, -1, -1 } },
		{ 3, { 9, 5, 4, 10, 1, 2, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 6, 11, 7, 1, 2, 10, 0, 8, 3, 4, 9, 5, -1, -1, -1, -1, } },
		{ 4, { 7, 6, 11, 5, 4, 10, 4, 2, 10, 4, 0, 2, -1, -1, -1, -1 } },
		{ 5, { 3, 4, 8, 3, 5, 4, 3, 2, 5, 10, 5, 2, 11, 7, 6, -1 } },
		{ 3, { 7, 2, 3, 7, 6, 2, 5, 4, 9, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 9, 5, 4, 0, 8, 6, 0, 6, 2, 6, 8, 7, -1, -1, -1, -1 } },
		{ 4, { 3, 6, 2, 3, 7, 6, 1, 5, 0, 5, 4, 0, -1, -1, -1, -1 } },
		{ 5, { 6, 2, 8, 6, 8, 7, 2, 1, 8, 4, 8, 5, 1, 5, 8, -1 } },
		{ 4, { 9, 5, 4, 10, 1, 6, 1, 7, 6, 1, 3, 7, -1, -1, -1, -1 } },
		{ 5, { 1, 6, 10, 1, 7, 6, 1, 0, 7, 8, 7, 0, 9, 5, 4, -1 } },
		{ 5, { 4, 0, 10, 4, 10, 5, 0, 3, 10, 6, 10, 7, 3, 7, 10, -1 } },
		{ 4, { 7, 6, 10, 7, 10, 8, 5, 4, 10, 4, 8, 10, -1, -1, -1, -1 } },
		{ 3, { 6, 9, 5, 6, 11, 9, 11, 8, 9, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 3, 6, 11, 0, 6, 3, 0, 5, 6, 0, 9, 5, -1, -1, -1, -1 } },
		{ 4, { 0, 11, 8, 0, 5, 11, 0, 1, 5, 5, 6, 11, -1, -1, -1, -1 } },
		{ 3, { 6, 11, 3, 6, 3, 5, 5, 3, 1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 1, 2, 10, 9, 5, 11, 9, 11, 8, 11, 5, 6, -1, -1, -1, -1 } },
		{ 5, { 0, 11, 3, 0, 6, 11, 0, 9, 6, 5, 6, 9, 1, 2, 10, -1 } },
		{ 5, { 11, 8, 5, 11, 5, 6, 8, 0, 5, 10, 5, 2, 0, 2, 5, -1 } },
		{ 4, { 6, 11, 3, 6, 3, 5, 2, 10, 3, 10, 5, 3, -1, -1, -1, -1 } },
		{ 4, { 5, 8, 9, 5, 2, 8, 5, 6, 2, 3, 8, 2, -1, -1, -1, -1 } },
		{ 3, { 9, 5, 6, 9, 6, 0, 0, 6, 2, -1, -1, -1, -1, -1, -1, -1 } },
		{ 5, { 1, 5, 8, 1, 8, 0, 5, 6, 8, 3, 8, 2, 6, 2, 8, -1 } },
		{ 2, { 1, 5, 6, 2, 1, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 5, { 1, 3, 6, 1, 6, 10, 3, 8, 6, 5, 6, 9, 8, 9, 6, -1 } },
		{ 4, { 10, 1, 0, 10, 0, 6, 9, 5, 0, 5, 6, 0, -1, -1, -1, -1 } },
		{ 2, { 0, 3, 8, 5, 6, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 1, { 10, 5, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 11, 5, 10, 7, 5, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 11, 5, 10, 11, 7, 5, 8, 3, 0, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 5, 11, 7, 5, 10, 11, 1, 9, 0, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 10, 7, 5, 10, 11, 7, 9, 8, 1, 8, 3, 1, -1, -1, -1, -1 } },
		{ 3, { 11, 1, 2, 11, 7, 1, 7, 5, 1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 0, 8, 3, 1, 2, 7, 1, 7, 5, 7, 2, 11, -1, -1, -1, -1 } },
		{ 4, { 9, 7, 5, 9, 2, 7, 9, 0, 2, 2, 11, 7, -1, -1, -1, -1 } },
		{ 5, { 7, 5, 2, 7, 2, 11, 5, 9, 2, 3, 2, 8, 9, 8, 2, -1 } },
		{ 3, { 2, 5, 10, 2, 3, 5, 3, 7, 5, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 8, 2, 0, 8, 5, 2, 8, 7, 5, 10, 2, 5, -1, -1, -1, -1 } },
		{ 4, { 9, 0, 1, 5, 10, 3, 5, 3, 7, 3, 10, 2, -1, -1, -1, -1 } },
		{ 5, { 9, 8, 2, 9, 2, 1, 8, 7, 2, 10, 2, 5, 7, 5, 2, -1 } },
		{ 2, { 1, 3, 5, 3, 7, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 0, 8, 7, 0, 7, 1, 1, 7, 5, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 9, 0, 3, 9, 3, 5, 5, 3, 7, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 9, 8, 7, 5, 9, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 5, 8, 4, 5, 10, 8, 10, 11, 8, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 5, 0, 4, 5, 11, 0, 5, 10, 11, 11, 3, 0, -1, -1, -1, -1 } },
		{ 4, { 0, 1, 9, 8, 4, 10, 8, 10, 11, 10, 4, 5, -1, -1, -1, -1 } },
		{ 5, { 10, 11, 4, 10, 4, 5, 11, 3, 4, 9, 4, 1, 3, 1, 4, -1 } },
		{ 4, { 2, 5, 1, 2, 8, 5, 2, 11, 8, 4, 5, 8, -1, -1, -1, -1 } },
		{ 5, { 0, 4, 11, 0, 11, 3, 4, 5, 11, 2, 11, 1, 5, 1, 11, -1 } },
		{ 5, { 0, 2, 5, 0, 5, 9, 2, 11, 5, 4, 5, 8, 11, 8, 5, -1 } },
		{ 2, { 9, 4, 5, 2, 11, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 2, 5, 10, 3, 5, 2, 3, 4, 5, 3, 8, 4, -1, -1, -1, -1 } },
		{ 3, { 5, 10, 2, 5, 2, 4, 4, 2, 0, -1, -1, -1, -1, -1, -1, -1 } },
		{ 5, { 3, 10, 2, 3, 5, 10, 3, 8, 5, 4, 5, 8, 0, 1, 9, -1 } },
		{ 4, { 5, 10, 2, 5, 2, 4, 1, 9, 2, 9, 4, 2, -1, -1, -1, -1 } },
		{ 3, { 8, 4, 5, 8, 5, 3, 3, 5, 1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 0, 4, 5, 1, 0, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 8, 4, 5, 8, 5, 3, 9, 0, 5, 0, 3, 5, -1, -1, -1, -1 } },
		{ 1, { 9, 4, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 4, 11, 7, 4, 9, 11, 9, 10, 11, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 0, 8, 3, 4, 9, 7, 9, 11, 7, 9, 10, 11, -1, -1, -1, -1 } },
		{ 4, { 1, 10, 11, 1, 11, 4, 1, 4, 0, 7, 4, 11, -1, -1, -1, -1 } },
		{ 5, { 3, 1, 4, 3, 4, 8, 1, 10, 4, 7, 4, 11, 10, 11, 4, -1 } },
		{ 4, { 4, 11, 7, 9, 11, 4, 9, 2, 11, 9, 1, 2, -1, -1, -1, -1 } },
		{ 5, { 9, 7, 4, 9, 11, 7, 9, 1, 11, 2, 11, 1, 0, 8, 3, -1 } },
		{ 3, { 11, 7, 4, 11, 4, 2, 2, 4, 0, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 11, 7, 4, 11, 4, 2, 8, 3, 4, 3, 2, 4, -1, -1, -1, -1 } },
		{ 4, { 2, 9, 10, 2, 7, 9, 2, 3, 7, 7, 4, 9, -1, -1, -1, -1 } },
		{ 5, { 9, 10, 7, 9, 7, 4, 10, 2, 7, 8, 7, 0, 2, 0, 7, -1 } },
		{ 5, { 3, 7, 10, 3, 10, 2, 7, 4, 10, 1, 10, 0, 4, 0, 10, -1 } },
		{ 2, { 1, 10, 2, 8, 7, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 4, 9, 1, 4, 1, 7, 7, 1, 3, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 4, 9, 1, 4, 1, 7, 0, 8, 1, 8, 7, 1, -1, -1, -1, -1 } },
		{ 2, { 4, 0, 3, 7, 4, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 1, { 4, 8, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 9, 10, 8, 10, 11, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 3, 0, 9, 3, 9, 11, 11, 9, 10, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 0, 1, 10, 0, 10, 8, 8, 10, 11, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 3, 1, 10, 11, 3, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 1, 2, 11, 1, 11, 9, 9, 11, 8, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 3, 0, 9, 3, 9, 11, 1, 2, 9, 2, 11, 9, -1, -1, -1, -1 } },
		{ 2, { 0, 2, 11, 8, 0, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 1, { 3, 2, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 2, 3, 8, 2, 8, 10, 10, 8, 9, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 9, 10, 2, 0, 9, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 2, 3, 8, 2, 8, 10, 0, 1, 8, 1, 10, 8, -1, -1, -1, -1 } },
		{ 1, { 1, 10, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 1, 3, 8, 9, 1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 1, { 0, 9, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 1, { 0, 3, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 0, { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } }
	};
}


#ifdef MUD_MODULES
module mud.geom;
#else
#endif

#include <cassert>

namespace mud
{
	uint16_t circle_subdiv(uint lod) { return uint16_t(6 + 12 * lod); }

	uint16_t circle_subdiv(const Symbol& symbol)
	{
		return symbol.m_subdiv == uvec2(0U)
			? circle_subdiv(uint(symbol.m_detail))
			: symbol.m_subdiv.x;
	}

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
		uint16_t subdiv = circle_subdiv(shape.m_symbol);

		float increment = c_2pi / subdiv;
		float angle = 0.0f;

		for(uint16_t i = 0; i < subdiv; i++)
		{
			vec2 xy = vec2(radius.x * cos(angle), radius.y * sin(angle));
			vec3 point = flip_point_axis({ xy.x, 0.f, xy.y }, axis);
			vec2 uv = xy / 2.f + 0.5f;
			writer.position(position + point)
				  .normal(outward_normals ? point : to_vec3(axis))
				  .colour(lines ? shape.m_symbol.m_outline : shape.m_symbol.m_fill)
				  .uv0(uv);
			angle += increment;
		}

		if(!lines)
			writer.position(position)
				  .normal(to_vec3(axis))
				  .colour(lines ? shape.m_symbol.m_outline : shape.m_symbol.m_fill)
				  .uv0(vec2(0.5f));

		return subdiv;
	}

	ShapeSize size_shape_lines(const ProcShape& shape, const Circle& circle)
	{
		UNUSED(circle);
		uint16_t subdiv = circle_subdiv(shape.m_symbol);
		return { subdiv, subdiv * 2U };
	}

	void draw_shape_lines(const ProcShape& shape, const Circle& circle, MeshAdapter& writer)
	{
		uint16_t subdiv = circle_vertices(shape, circle.m_center, vec2(circle.m_radius), to_signed_axis(circle.m_axis, true), true, writer);

		for(uint16_t i = 0; i < subdiv; i++)
			writer.line(i, i + 1 < subdiv ? i + 1 : 0);
	}

	ShapeSize size_shape_triangles(const ProcShape& shape, const Circle& circle)
	{
		UNUSED(circle);
		uint16_t subdiv = circle_subdiv(shape.m_symbol);
		return { subdiv + 1U, subdiv * 3U };
	}

	void draw_shape_triangles(const ProcShape& shape, const Circle& circle, MeshAdapter& writer)
	{
		uint16_t subdiv = circle_vertices(shape, circle.m_center, vec2(circle.m_radius), to_signed_axis(circle.m_axis, true), false, writer);

		for(uint16_t i = 0; i < subdiv; i++)
			writer.tri(i + 1 < subdiv ? i + 1 : 0, i,  subdiv);
	}

	
	ShapeSize size_shape_lines(const ProcShape& shape, const Ellipsis& ellipsis)
	{
		UNUSED(ellipsis);
		uint16_t subdiv = circle_subdiv(shape.m_symbol);
		return { subdiv, subdiv * 2U };
	}

	void draw_shape_lines(const ProcShape& shape, const Ellipsis& ellipsis, MeshAdapter& writer)
	{
		uint16_t subdiv = circle_vertices(shape, ellipsis.m_center, ellipsis.m_radius, to_signed_axis(ellipsis.m_axis, true), true, writer);

		for(uint16_t i = 0; i < subdiv; i++)
			writer.line(i, i + 1 < subdiv ? i + 1 : 0);
	}

	ShapeSize size_shape_triangles(const ProcShape& shape, const Ellipsis& ellipsis)
	{
		UNUSED(ellipsis);
		uint16_t subdiv = circle_subdiv(shape.m_symbol);
		return { subdiv + 1U, subdiv * 3U };
	}

	void draw_shape_triangles(const ProcShape& shape, const Ellipsis& ellipsis, MeshAdapter& writer)
	{
		uint16_t subdiv = circle_vertices(shape, ellipsis.m_center, ellipsis.m_radius, to_signed_axis(ellipsis.m_axis, true), false, writer);

		for(uint16_t i = 0; i < subdiv; i++)
			writer.tri(i + 1 < subdiv ? i + 1 : 0, i,  subdiv);
	}

	ShapeSize size_shape_lines(const ProcShape& shape, const ArcLine& arc)
	{
		UNUSED(arc);
		uint16_t subdiv = circle_subdiv(shape.m_symbol);
		return { subdiv, (subdiv-1U) * 2U };
	}

	void draw_shape_lines(const ProcShape& shape, const ArcLine& arc, MeshAdapter& writer)
	{
		uint16_t subdiv = circle_subdiv(shape.m_symbol);

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

	uint16_t torus_sides(uint lod) { return uint16_t(6 + 6 * lod); }
	uint16_t torus_rings(uint lod) { return uint16_t(6 + 6 * lod); }

	uint16_t torus_sides(const Symbol& symbol)
	{
		return symbol.m_subdiv == uvec2(0U)
			? torus_sides(uint(symbol.m_detail))
			: symbol.m_subdiv.x;
	}

	uint16_t torus_rings(const Symbol& symbol)
	{
		return symbol.m_subdiv == uvec2(0U)
			? torus_rings(uint(symbol.m_detail))
			: symbol.m_subdiv.y;
	}

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
		uint16_t sides_subdiv = torus_sides(shape.m_symbol) + 1;
		uint16_t rings_subdiv = torus_rings(shape.m_symbol) + 1;
		return { uint32_t(sides_subdiv * rings_subdiv), uint32_t((sides_subdiv-1U) * (rings_subdiv-1U) * 6U) };
	}

	void draw_shape_triangles(const ProcShape& shape, const Torus& torus, MeshAdapter& writer)
	{
		const SignedAxis axis = to_signed_axis(torus.m_axis, true);

		const uint16_t rings = torus_rings(shape.m_symbol);
		const uint16_t sides = torus_sides(shape.m_symbol);

		const uint16_t rings_subdiv = rings + 1;
		const uint16_t sides_subdiv = sides + 1;

		const float ring_step = c_2pi / float(rings);
		const float side_step = c_2pi / float(sides);

		for(uint16_t v = 0; v < sides_subdiv; v++)
			for(uint16_t h = 0; h < rings_subdiv; h++)
			{
				const float theta = ring_step * h;
				const float phi = side_step * v;

				const float x = cos(theta) * (torus.m_radius + torus.m_tube * cos(phi));
				const float y = torus.m_tube * sin(phi);
				const float z = sin(theta) * (torus.m_radius + torus.m_tube * cos(phi));

				const vec3 circle = flip_point_axis(vec3(cos(theta), 0.f, sin(theta)) * torus.m_radius, axis);
				const vec3 point = flip_point_axis(vec3(x, y, z), axis);

				const vec3 normal = normalize(point - circle);

				writer.position(point)
					  .normal(normal)
					  .colour(shape.m_symbol.m_fill)
					  .uv0(vec2(theta / c_2pi, phi / c_2pi));
			}

		for(uint16_t v = 0; v < sides; v++)
			for(uint16_t h = 0; h < rings; h++)
			{
				const uint16_t lt = h + v * rings_subdiv;
				const uint16_t rt = (h + 1) + v * rings_subdiv;

				const uint16_t lb = h + (v + 1) * rings_subdiv;
				const uint16_t rb = (h + 1) + (v + 1) * rings_subdiv;

				writer.tri(lt, rt, lb);
				writer.tri(rt, rb, lb);
			}
	}

	uint16_t torus_tube_subdiv(uint lod) { return uint16_t(64U); }
	uint16_t torus_radial_subdiv(uint lod) { return uint16_t(8U); }

	uint16_t torus_tube_subdiv(const Symbol& symbol)
	{
		return symbol.m_subdiv == uvec2(0U)
			? torus_tube_subdiv(uint(symbol.m_detail))
			: symbol.m_subdiv.x;
	}

	uint16_t torus_radial_subdiv(const Symbol& symbol)
	{
		return symbol.m_subdiv == uvec2(0U)
			? torus_radial_subdiv(uint(symbol.m_detail))
			: symbol.m_subdiv.y;
	}

	ShapeSize size_shape_triangles(const ProcShape& shape, const TorusKnot& torus)
	{
		UNUSED(torus);
		const uint16_t tubular = torus_tube_subdiv(shape.m_symbol) + 1;
		const uint16_t radial = torus_radial_subdiv(shape.m_symbol) + 1;
		return { uint32_t(tubular * radial), uint32_t((tubular-1U) * (radial-1U) * 6U) };
	}

	void draw_shape_triangles(const ProcShape& shape, const TorusKnot& torus, MeshAdapter& writer)
	{
		const float radius = torus.m_radius;
		const float tube = torus.m_tube;
		const uint16_t tubular = torus_tube_subdiv(shape.m_symbol);
		const uint16_t radial = torus_radial_subdiv(shape.m_symbol);
		const float p = torus.m_p;
		const float q = torus.m_q;

		auto knot_curve = [](float u, float p, float q, float radius) -> vec3
		{
			const float cu = cos(u);
			const float su = sin(u);
			const float quOverP = q / p * u;
			const float cs = cos(quOverP);

			const float x = radius * (2.f + cs) * 0.5f * cu;
			const float y = radius * (2.f + cs) * su * 0.5f;
			const float z = radius * sin(quOverP) * 0.5f;
			return vec3(x, y, z);
		};

		for(uint16_t i = 0; i <= tubular; ++i)
		{
			// the radian "u" is used to calculate the position on the torus curve of the current tubular segement
			const float u = float(i) / float(tubular) * p * c_2pi;

			// now we calculate two points. P1 is our current position on the curve, P2 is a little farther ahead.
			// these points are used to create a special "coordinate space", which is necessary to calculate the correct vertex positions
			const vec3 P1 = knot_curve(u, p, q, radius);
			const vec3 P2 = knot_curve(u + 0.01f, p, q, radius);

			// calculate orthonormal basis
			const vec3 oT = P2 - P1;
			const vec3 oN = P2 + P1;
			const vec3 B = normalize(cross(oT, oN));
			const vec3 N = normalize(cross(B, oT));

			for(uint16_t j = 0; j <= radial; ++j)
			{
				// now calculate the vertices. they are nothing more than an extrusion of the torus curve.
				// because we extrude a shape in the xy-plane, there is no need to calculate a z-value.
				const float v = float(j) / float(radial) * c_2pi;
				const float cx = -tube * cos(v);
				const float cy = tube * sin(v);

				// now calculate the final vertex position.
				// first we orient the extrusion with our basis vectos, then we add it to the current position on the curve
				const float x = P1.x + (cx * N.x + cy * B.x);
				const float y = P1.y + (cx * N.y + cy * B.y);
				const float z = P1.z + (cx * N.z + cy * B.z);
				
				const vec3 p = vec3(x, y, z);
				// normal (P1 is always the center/origin of the extrusion, thus we can use it to calculate the normal)
				const vec3 n = normalize(p - P1);
				const vec2 uv = vec2(float(i) / float(tubular), float(j) / float(radial));

				writer.position(p)
					  .normal(n)
					  .colour(shape.m_symbol.m_fill)
					  .uv0(uv);
			}

		}

		for(uint16_t j = 1; j <= tubular; j++)
		{
			for(uint16_t i = 1; i <= radial; i++)
			{
				const uint16_t a = (radial + 1) * (j - 1) + (i - 1);
				const uint16_t b = (radial + 1) * j + (i - 1);
				const uint16_t c = (radial + 1) * j + i;
				const uint16_t d = (radial + 1) * (j - 1) + i;

				writer.tri(a, b, d);
				writer.tri(b, c, d);
			}
		}
	}
}


#ifdef MUD_MODULES
module mud.geom;
#else
#include <stl/array.h>
#endif

#include <stl/vector.hpp>

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

		for(int i = 0; i < 8; ++i)
			writer.position(box.m_center + box.m_vertices[i])
				  .colour(shape.m_symbol.m_outline);

		for(uint16_t i = 0; i < 4; ++i)
			writer.line(i, (i + 1) % 4);

		for(uint16_t i = 4; i < 8; ++i)
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

		for(int i = 0; i < 8; ++i)
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

	// Angle around the Y axis, counter-clockwise when looking from above.
	inline float azimuth(const vec3& v) { return atan2(v.z, -v.x); };

	// Angle above the XZ plane.
	inline float inclination(const vec3& v) { return atan2(-v.y, sqrt((v.x * v.x) + (v.z * v.z))); };

#if 1
	void draw_polyhedron(const ProcShape& shape, MeshAdapter& writer, span<vec3> points, span<uint32_t> indices, float radius = 1.f, int detail = 0)
	{
		// the subdivision creates the vertex buffer data

		vector<vec3> vertices;
		vector<vec2> uvs;

		auto vertex = [&](vec3 v) {
			//writer.position(v);
			vertices.push_back(v);
		};

		auto subdivideFace = [&](vec3 a, vec3 b, vec3 c, int detail) {

			size_t cols = pow(2, detail);

			// we use this multidimensional array as a data structure for creating the subdivision

			vector<vector<vec3>> v;
			v.resize(cols+1);

			// construct all of the vertices for this subdivision

			for(int i = 0; i <= cols; i++) {

				vec3 aj = lerp(a, c, float(i) / float(cols));
				vec3 bj = lerp(b, c, float(i) / float(cols));

				int rows = cols - i;

				v[i].resize(rows+1);

				for(int j = 0; j <= rows; j++)
				{
					if(j == 0 && i ==  cols)
						v[i][j] = aj;
					else
						v[i][j] = lerp(aj, bj, float(j) / float(rows));
				}
			}

			// construct all of the faces

			for(int i = 0; i < cols; i++)
				for(int j = 0; j < 2 * (cols - i) - 1; j++)
				{
					int k = floor(j / 2);

					if(j % 2 == 0) {
						vertex(v[i][k + 1]);
						vertex(v[i + 1][k]);
						vertex(v[i][k]);
					}
					else {
						vertex(v[i][k + 1]);
						vertex(v[i + 1][k + 1]);
						vertex(v[i + 1][k]);
					}
				}
		};

		auto subdivide = [&](int detail) {

			// iterate over all faces and apply a subdivison with the given detail value

			for(int i = 0; i < indices.size(); i += 3) {

				// get the vertices of the face
				vec3 a = points[indices[i + 0]];
				vec3 b = points[indices[i + 1]];
				vec3 c = points[indices[i + 2]];

				// perform subdivision
				subdivideFace(a, b, c, detail);
			}
		};

		auto correctUV = [](vec2& uv, const vec3& p, float azimuth) {

			if((azimuth < 0) && (uv.x == 1.f))
				uv.x = uv.x - 1.f;
			if((p.x == 0.f) && (p.z == 0.f))
				uv.x = azimuth / 2.f / c_pi + 0.5f;
		};

		auto correctUVs = [&]() {

			for(int i = 0; i < vertices.size(); i += 3) {

				vec3 a = vertices[i+0];
				vec3 b = vertices[i+1];
				vec3 c = vertices[i+2];

				vec3 centroid = (a + b + c) / 3.f;

				float azi = azimuth(centroid);

				correctUV(uvs[i+0], a, azi);
				correctUV(uvs[i+1], b, azi);
				correctUV(uvs[i+2], c, azi);
			}
		};

		auto correctSeam = [&]() {

			// handle case when face straddles the seam, see #3269
			for(int i = 0; i < uvs.size(); ++i) {

				// uv data of a single face
				float x0 = uvs[i + 0].x;
				float x1 = uvs[i + 1].x;
				float x2 = uvs[i + 2].x;

				float hi = max(x0, max(x1, x2));
				float lo = min(x0, min(x1, x2));

				// 0.9 is somewhat arbitrar
				if(hi > 0.9f && lo < 0.1f)
				{
					if(x0 < 0.2) uvs[i + 0].x += 1.f;
					if(x1 < 0.2) uvs[i + 1].x += 1.f;
					if(x2 < 0.2) uvs[i + 2].x += 1.f;
				}
			}
		};

		auto generateUVs = [&]() {

			for(int i = 0; i < vertices.size(); ++i) {

				vec3 vertex = vertices[i + 0];

				float u = azimuth(vertex) / 2.f / c_pi + 0.5f;
				float v = inclination(vertex) / c_pi + 0.5f;
				uvs.push_back(vec2(u, 1.f - v));
			}

			correctUVs();
			correctSeam();
		};

		subdivide(detail);

		// all vertices should lie on a conceptual sphere with a given radius

		auto appplyRadius = [&](float radius) {

			// iterate over the entire buffer and apply the radius to each vertex
			for(int i = 0; i < vertices.size(); ++i)
			{
				vec3& v = vertices[i];
				v = normalize(v) * radius;
			}

		};

		appplyRadius(radius);

		// finally, create the uv data

		generateUVs();

		const size_t num = vertices.size();
		for(size_t i = 0; i < vertices.size(); ++i)
		{
			writer.position(vertices[i])
				  .colour(shape.m_symbol.m_fill)
				  .normal(normalize(vertices[i]))
				  .uv0(uvs[i]);
		}
		//if(flat) this.computeVertexNormals(); // flat normals
		//else this.normalizeNormals(); // smooth normals

	}
#endif

	void draw_polyedr(const ProcShape& shape, MeshAdapter& writer, span<vec3> vertices, span<uint32_t> indices, float radius)
	{
		for(size_t i = 0; i < vertices.size(); ++i)
		{
			const vec3& p = vertices[i];
			const float u = azimuth(p) / 2.f / c_pi + 0.5f;
			const float v = inclination(p) / c_pi + 0.5f;

			writer.position(normalize(p) * radius)
				  .colour(shape.m_symbol.m_fill)
				  .normal(normalize(p))
				  .uv0(vec2(u, 1.f - v));
		}

		for(size_t i = 0; i < indices.size(); ++i)
			writer.index(indices[i]);
	}

	ShapeSize size_shape_triangles(const ProcShape& shape, const Tetraedr& tetra)
	{
		UNUSED(shape); UNUSED(tetra);
		return { 4U, 4U * 3U };
	}

	void draw_shape_triangles(const ProcShape& shape, const Tetraedr& tetra, MeshAdapter& writer)
	{
		constexpr vec3 vertices[] = {
			vec3(1, 1, 1), vec3(-1, -1, 1), vec3(-1, 1, -1), vec3(1, -1, -1)
		};

		constexpr uint32_t indices[] = {
			2, 1, 0, 0, 3, 2, 1, 3, 0, 2, 3, 1
		};

		draw_polyedr(shape, writer, vertices, indices, tetra.m_radius);

		//draw_polyhedron(writer, vertices, indices, tetra.m_radius, 0);
	}
	
	ShapeSize size_shape_triangles(const ProcShape& shape, const Icosaedr& icosa)
	{
		UNUSED(shape); UNUSED(icosa);
		//return { 12U, 20U * 3U };
		uint32_t detail = 1U;
		uint32_t num_verts = 60U * 4U * detail;
		return { num_verts, 0U };
	}

	void draw_shape_triangles(const ProcShape& shape, const Icosaedr& icosa, MeshAdapter& writer)
	{
		static const float t = (1.f + sqrt(5.f)) / 2.f;

		static const vec3 vertices[] = {
			vec3(-1, t, 0), vec3(1, t, 0), vec3(-1, -t, 0), vec3(1, -t, 0),
			vec3(0, -1, t), vec3(0, 1, t), vec3(0, -1, -t), vec3(0, 1, -t),
			vec3(t, 0, -1), vec3(t, 0, 1), vec3(-t, 0, -1), vec3(-t, 0, 1),
		};

		static const uint32_t indices[] = {
			0, 11, 5, 	0, 5, 1, 	0, 1, 7, 	0, 7, 10, 	0, 10, 11,
			1, 5, 9, 	5, 11, 4,	11, 10, 2,	10, 7, 6,	7, 1, 8,
			3, 9, 4, 	3, 4, 2,	3, 2, 6,	3, 6, 8,	3, 8, 9,
			4, 9, 5, 	2, 4, 11,	6, 2, 10,	8, 6, 7,	9, 8, 1
		};

		//draw_polyedr(shape, writer, vertices, indices, icosa.m_radius);

		draw_polyhedron(shape, writer, vertices, indices, icosa.m_radius, 1);
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
		uint16_t subdiv = circle_vertices(shape, cylinder.m_center + offset, vec2(circle.m_radius), to_signed_axis(circle.m_axis, true), true, writer);
						  circle_vertices(shape, cylinder.m_center - offset, vec2(circle.m_radius), to_signed_axis(circle.m_axis, false), true, writer);

		for(uint16_t i = 0; i < subdiv; i++)
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

		uint16_t subdiv = circle_vertices(shape, cylinder.m_center - offset, vec2(circle.m_radius), to_signed_axis(circle.m_axis, false), false, writer);

		for(uint16_t i = 0; i < subdiv; i++)
			writer.tri(i + 1 < subdiv ? i + 1 : 0, i, subdiv);
		writer.next();

		circle_vertices(shape, cylinder.m_center + offset, vec2(circle.m_radius), to_signed_axis(circle.m_axis, true), false, writer);

		for(uint16_t i = 0; i < subdiv; i++)
			writer.tri(i, i + 1 < subdiv ? i + 1 : 0, subdiv);
		writer.next();

		circle_vertices(shape, cylinder.m_center - offset, vec2(circle.m_radius), to_signed_axis(circle.m_axis, false), false, writer, true);
		circle_vertices(shape, cylinder.m_center + offset, vec2(circle.m_radius), to_signed_axis(circle.m_axis, true), false, writer, true);

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
		return { uint32_t(geometry.m_vertices.size()), uint32_t(geometry.m_triangles.size()) * 6U };
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
		return { uint32_t(geometry.m_vertices.size()), uint32_t(geometry.m_triangles.size()) * 3U };
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

		if(m_middle_point_cache.find(key) != m_middle_point_cache.end())
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
		return { lines * 2U, lines * 2U };
	}

	void draw_shape_lines(const ProcShape& shape, const Grid2& grid, MeshAdapter& writer)
	{
		vec2 half = grid.m_size * grid.m_space / 2.f;
		vec3 origin = grid.m_center - vec3(half.x, 0.f, half.y);

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
		decl_shape<Line>(*this);
		decl_shape<ArcLine>(*this);
		decl_shape<Circle>(*this);
		decl_shape<Ellipsis>(*this);
		decl_shape<Grid2>(*this);
		decl_shape<Grid3>(*this);
		decl_shape<Quad>(*this);
		decl_shape<Rect>(*this);
		decl_shape<Triangle>(*this);

		decl_shape<Box>(*this);
		decl_shape<Cube>(*this);
		//declare_shape<Aabb>(*this);
		decl_shape<Cylinder>(*this);
		decl_shape<Sphere>(*this);
		decl_shape<Torus>(*this);
		decl_shape_triangles<TorusKnot>(*this);

		// polyhedrons
		decl_shape_triangles<Tetraedr>(*this);
		decl_shape_triangles<Icosaedr>(*this);

		decl_shape<Geometry>(*this);

		decl_compound_shape<Spheroid>(*this);
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

	void quad_vertices(const ProcShape& shape, const vec3& center, span<vec3> vertices, bool fill, MeshAdapter& writer)
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

	uint32_t num_rects(const Grid3& grid) { return (grid.m_size.x-1) * (grid.m_size.y-1); }

	ShapeSize size_shape_lines(const ProcShape& shape, const Grid3& grid)
	{
		UNUSED(shape);
		uint32_t rects = num_rects(grid);
		return { rects * 4U, rects * 8U };
	}

	void draw_shape_lines(const ProcShape& shape, const Grid3& grid, MeshAdapter& writer)
	{
		// @todo: could draw it like a grid instead of per quads...
		span2d<vec3> points = { const_cast<vec3*>(grid.m_points.data()), grid.m_size.x, grid.m_size.y };

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
		uint32_t rects = num_rects(grid);
		return { rects * 4U, rects * 6U };
	}

	void draw_shape_triangles(const ProcShape& shape, const Grid3& grid, MeshAdapter& writer)
	{
		span2d<vec3> points = { const_cast<vec3*>(grid.m_points.data()), grid.m_size.x, grid.m_size.y };

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

		return { uint32_t(icosphere.m_vertices.size()), uint32_t(icosphere.m_lines.size()) * 2U };
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

		return { uint32_t(icosphere.m_vertices.size()), uint32_t(icosphere.m_faces.size()) * 3U };
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

	uvec2 sphere_subdiv(uint lod) { return uvec2(uint(6 + 6 * lod)); }

	uvec2 sphere_subdiv(const Symbol& symbol)
	{
		return symbol.m_subdiv != uvec2(0U)
			? symbol.m_subdiv + uvec2(1U)
			: sphere_subdiv(uint(symbol.m_detail));
	}

	void sphere_vertices(MeshAdapter& writer, const vec3& center, float radius, uvec2 subdiv, const Colour& colour,
						 float phi = 0.f, float arcphi = c_2pi, float theta = 0.f, float arctheta = c_pi)
	{
		float const R = 1.f / (float)(subdiv.x - 1);
		float const S = 1.f / (float)(subdiv.y - 1);
		float repeat = 1.f;

		for(uint16_t r = 0; r < subdiv.x; r++)
		for(uint16_t s = 0; s < subdiv.y; s++)
		{
			float const x = cos(phi + arcphi * s * S) * sin(theta + arctheta * r * R);
			float const y = sin(-c_pi2 + theta + arctheta * r * R);
			float const z = sin(phi + arcphi * s * S) * sin(theta + arctheta * r * R);

			writer.position(center + vec3(x, y, z) * radius)
				  .normal({ x, y, z })
				  .uv0({ s * S * repeat, r * R * repeat })
				  .colour(colour);
		}
	}

	ShapeSize size_sphere_lines(const ProcShape& shape, const Sphere& sphere)
	{
		UNUSED(shape); UNUSED(sphere);
		const uvec2 subdiv = sphere_subdiv(shape.m_symbol);

		return { subdiv.x * subdiv.y, uint32_t((subdiv.x-1U) * (subdiv.y-1U) * 4U) };
	}

	void draw_sphere_lines(const ProcShape& shape, const Sphere& sphere, MeshAdapter& writer)
	{
		const uvec2 subdiv = sphere_subdiv(shape.m_symbol);

		sphere_vertices(writer, sphere.m_center, sphere.m_radius, subdiv, shape.m_symbol.m_outline, sphere.m_start, sphere.m_end);

		for(uint16_t r = 0; r < subdiv.x - 1; r++)
		for(uint16_t s = 0; s < subdiv.y - 1; s++)
		{
			writer.line(r * subdiv.y + (s + 1),
					    r * subdiv.y + s);
			writer.line((r + 1) * subdiv.y + (s + 1),
					    r * subdiv.y + (s + 1));
		}
	}

	ShapeSize size_sphere_triangles(const ProcShape& shape, const Sphere& sphere)
	{
		UNUSED(shape); UNUSED(sphere);
		const uvec2 subdiv = sphere_subdiv(shape.m_symbol);

		return { uint32_t(subdiv.x * subdiv.y), uint32_t((subdiv.x-1U) * (subdiv.y-1U) * 6U) };
	}

	void draw_sphere_triangles(const ProcShape& shape, const Sphere& sphere, MeshAdapter& writer)
	{
		const uvec2 subdiv = sphere_subdiv(shape.m_symbol);

		sphere_vertices(writer, sphere.m_center, sphere.m_radius, subdiv, shape.m_symbol.m_outline, sphere.m_start, sphere.m_end);

		for(uint16_t r = 0; r < subdiv.x - 1; r++)
		for(uint16_t s = 0; s < subdiv.y - 1; s++)
		{
			writer.quad((r + 1) * subdiv.y + s,
					    (r + 1) * subdiv.y + (s + 1),
					    r * subdiv.y + (s + 1),
					    r * subdiv.y + s);
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
