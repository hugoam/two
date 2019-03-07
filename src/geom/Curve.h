//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/vector.h>
#include <math/Vec.h>
#include <math/Math.h>
#include <geom/Forward.h>

namespace mud
{
	class refl_ Curve2
	{
	public:
		meth_ virtual vec2 point(float t) const = 0;
	};

	class refl_ Curve3
	{
	public:
		meth_ virtual vec3 point(float t) const = 0;
		//virtual vec2 point(float t) const = 0;

		//meth_ float length() const;

		vec3 tangent(float t) const;

		vector<vec3> points(size_t subdiv = 5) const;

		vector<float> lengths() const;
		vector<float> lengths(size_t subdiv) const;

		struct FrenetFrames
		{
			vector<vec3> tangents;
			vector<vec3> normals;
			vector<vec3> binormals;
		};

		// see http://www.cs.indiana.edu/pub/techreports/TR425.pdf
		FrenetFrames frenet_frames(size_t segments, bool closed);

		size_t m_curved_subdiv = 200;
	};

	struct Curve3Sampler
	{
		Curve3Sampler(Curve3& curve);

		void subdiv(size_t subdiv);
		vector<vec3> points(size_t subdiv = 5) const;
		vec3 point(float u) const;
		vec3 tangent(float u) const;
		float at(float u) const;
		float at_distance(float distance) const;

		Curve3& m_curve;
		vector<float> m_lengths;
		bool m_dirty = false;
	};

	struct refl_ CurveSpline : public Curve2
	{
		virtual vec2 point(float t) const override;

		attr_ vector<vec2> m_points;
	};

	struct refl_ CurveSpline3 : public Curve3
	{
		virtual vec3 point(float t) const override;

		attr_ vector<vec3> m_points;
	};

	struct CurveEllipse
	{
		vec2 m_a = vec2(0.f);
		vec2 m_radius = vec2(1.f);
		float m_angle[2] = { 0.f, c_2pi };

		bool m_clockwise = false;
		float m_rotation = 0.f;

		vec2 point(float t);
	};

	struct CurveArcCurve : public CurveEllipse
	{};

	struct refl_ CurveBezierCubic : public Curve2
	{
		virtual vec2 point(float t) const override;

		attr_ vec2 v0;
		attr_ vec2 v1;
		attr_ vec2 v2;
		attr_ vec2 v3;
	};

	struct refl_ CurveBezierCubic3 : public Curve3
	{
		virtual vec3 point(float t) const override;

		attr_ vec3 v0;
		attr_ vec3 v1;
		attr_ vec3 v2;
		attr_ vec3 v3;
	};

	struct refl_ CurveLine : public Curve2
	{
		virtual vec2 point(float t) const override;

		attr_ vec2 v0;
		attr_ vec2 v1;
	};

	struct refl_ CurveLine3 : public Curve3
	{
		virtual vec3 point(float t) const override;

		attr_ vec3 v0;
		attr_ vec3 v1;
	};

	struct refl_ CurveBezierQuadratic : public Curve2
	{
		virtual vec2 point(float t) const override;

		attr_ vec2 v0;
		attr_ vec2 v1;
		attr_ vec2 v2;
	};

	struct refl_ CurveBezierQuadratic3 : public Curve3
	{
		virtual vec3 point(float t) const override;

		attr_ vec3 v0;
		attr_ vec3 v1;
		attr_ vec3 v2;
	};

	enum class refl_ CatmullType : unsigned int
	{
		Centripetal,
		Chordal,
		CatmullRom
	};

	struct refl_ CurveCatmullRom3 : public Curve3
	{
		constr_ CurveCatmullRom3();
		constr_ CurveCatmullRom3(const vector<vec3>& points, bool closed = false, CatmullType curve_type = CatmullType::Centripetal, float tension = 0.5f);

		virtual vec3 point(float t) const override;

		meth_ void add_point(const vec3& point);

		attr_ vector<vec3> m_points = {};
		attr_ bool m_closed = false;
		attr_ CatmullType m_curve_type = CatmullType::Centripetal;
		attr_ float m_tension = 0.5f;
	};
}
