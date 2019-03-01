//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/vector.h>
#include <math/Vec.h>
#include <geom/Forward.h>

namespace mud
{

	struct Curve3
	{
		size_t m_arcLengthDivisions = 200;

		virtual vec3 point(float t, vec3 target = vec3(0.f)) = 0;
		//virtual vec2 point(float t, vec2 target = vec2(0.f)) = 0;

		// Get point at relative position in curve according to arc length
		// - u [0 .. 1]
		vec3 point_at(float u, vec3 target = vec3(0.f))//, bool optionalTarget)
		{
			float t = this->at(u);
			return this->point(t, target); // , optionalTarget);
		}

		// Get sequence of points using point(t)
		vector<vec3> points(size_t divisions = 5);

		// Get sequence of points using pointAt(u)
		vector<vec3> getSpacedPoints(size_t divisions = 5);

		// Get total curve arc length
		float getLength();

		// Get list of cumulative segment lengths

		vector<float> m_cacheArcLengths;
		bool m_dirty = false;

		vector<float> getLengths();
		vector<float> getLengths(size_t divisions);

		void updateArcLengths();

		// Given u (0 .. 1), get a t to find p. This gives you points which are equidistant

		float at(float u);
		float at(float u, float distance);

		// Returns a unit vector tangent at t
		// In case any sub curve does not implement its tangent derivation,
		// 2 points a small delta apart will be used to find its gradient
		// which seems to give a reasonable approximation

		vec3 getTangent(float t);
		vec3 getTangentAt(float u);

		struct FrenetFrames
		{
			vector<vec3> tangents;
			vector<vec3> normals;
			vector<vec3> binormals;
		};

		// see http://www.cs.indiana.edu/pub/techreports/TR425.pdf
		FrenetFrames computeFrenetFrames(size_t segments, bool closed);
	};

	struct CatmullRomCurve3 : public Curve3
	{
		enum class CurveType
		{
			Centripetal,
			Chordal,
			CatmullRom
		};

		CatmullRomCurve3(const vector<vec3>& points, bool closed = false, CurveType curveType = CurveType::Centripetal, float tension = 0.5f)
			: m_points(points), m_closed(closed), m_curveType(curveType), m_tension(tension)
		{}

		vector<vec3> m_points = {};
		bool m_closed = false;
		CurveType m_curveType = CurveType::Centripetal;
		float m_tension = 0.5f;

		virtual vec3 point(float t, vec3 target = vec3(0.f)) override;
	};
}
