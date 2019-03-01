//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef MUD_MODULES
module mud.geom;
#else
#include <stl/string.h>
#include <math/Vec.hpp>
#include <geom/Curve.h>
#include <geom/Geom.h>
#endif

#include <cfloat>

namespace mud
{
	// Get sequence of points using point(t)
	vector<vec3> Curve3::points(size_t divisions)
	{
		vector<vec3> points = {};

		for (size_t d = 0; d <= divisions; d ++)
		{
			points.push_back(this->point(float(d) / float(divisions)));
		}

		return points;
	}

	// Get sequence of points using pointAt(u)
	vector<vec3> Curve3::getSpacedPoints(size_t divisions)
	{
		vector<vec3> points = {};

		for (size_t d = 0; d <= divisions; d ++)
		{
			points.push_back(this->point_at(float(d) / float(divisions)));
		}

		return points;
	}

	// Get list of cumulative segment lengths

	vector<float> m_cacheArcLengths;
	bool m_dirty = false;

	vector<float> Curve3::getLengths()
	{
		return getLengths(m_arcLengthDivisions);
	}

	vector<float> Curve3::getLengths(size_t divisions)
	{
		if (m_cacheArcLengths.size() == divisions + 1 && !m_dirty)
			return m_cacheArcLengths;
			
		m_dirty = false;

		vector<float> cache = {};
		vec3 current; vec3 last = current = this->point(0);
		float p, sum = 0;

		cache.push_back(0);

		for (p = 1; p <= divisions; p ++) {

			current = this->point(p / divisions);
			sum += distance(current, last);
			cache.push_back(sum);
			last = current;
		}

		m_cacheArcLengths = cache;

		return cache; // { sums: cache, sum: sum }; Sum is in the last element.

	}

	void Curve3::updateArcLengths() {

		m_dirty = true;
		this->getLengths();

	}

	// Given u (0 .. 1), get a t to find p. This gives you points which are equidistant

	float Curve3::at(float u)
	{
		vector<float> arcLengths = this->getLengths();
		return at(u, u * arcLengths.back());
	}

	float Curve3::at(float u, float distance)
	{
		vector<float> arcLengths = this->getLengths();

		size_t i = 0, il = arcLengths.size();

		float targetArcLength = distance;

		// binary search for the index with largest value smaller than target u distance

		size_t low = 0, high = il - 1, comparison;

		while (low <= high)
		{
			i = floor(low + (high - low) / 2); // less likely to overflow, though probably not issue here, JS doesn't really have integers, all numbers are floats

			comparison = arcLengths[i] - targetArcLength;

			if (comparison < 0)
				low = i + 1;
			else if (comparison > 0)
				high = i - 1;
			else
			{
				high = i;
				break;
			}
		}

		i = high;

		if (arcLengths[i] == targetArcLength)
			return i / (il - 1);

		// we could get finer grain at lengths, or use simple interpolation between two points

		float lengthBefore = arcLengths[i];
		float lengthAfter = arcLengths[i + 1];

		float segmentLength = lengthAfter - lengthBefore;

		// determine where we are between the 'before' and 'after' points

		float segmentFraction = (targetArcLength - lengthBefore) / segmentLength;

		// add that fractional amount to t

		float t = (i + segmentFraction) / (il - 1);

		return t;
	}

	// Returns a unit vector tangent at t
	// In case any sub curve does not implement its tangent derivation,
	// 2 points a small delta apart will be used to find its gradient
	// which seems to give a reasonable approximation

	vec3 Curve3::getTangent(float t)
	{
		float delta = 0.0001;
		float t1 = t - delta;
		float t2 = t + delta;

		// Capping in case of danger

		if (t1 < 0) t1 = 0;
		if (t2 > 1) t2 = 1;

		vec3 pt1 = this->point(t1);
		vec3 pt2 = this->point(t2);

		vec3 vec = pt2 - pt1;
		return normalize(vec);
	}

	vec3 Curve3::getTangentAt(float u)
	{
		float t = this->at(u);
		return this->getTangent(t);
	}

	// see http://www.cs.indiana.edu/pub/techreports/TR425.pdf
	Curve3::FrenetFrames Curve3::computeFrenetFrames(size_t segments, bool closed)
	{
		vec3 normal = vec3();

		vector<vec3> tangents = {};
		vector<vec3> normals = {};
		vector<vec3> binormals = {};

		vec3 vec = vec3();
		mat4 mat = {};

		size_t i, u, theta;

		// compute the tangent vectors for each segment on the curve

		for (i = 0; i <= segments; i ++) 
		{
			u = i / segments;

			tangents[i] = this->getTangentAt(u);
			tangents[i] = normalize(tangents[i]);
		}

		// select an initial normal vector perpendicular to the first tangent vector,
		// and in the direction of the minimum tangent xyz component

		normals[0] = vec3();
		binormals[0] = vec3();
		float min = FLT_MAX;
		float tx = abs(tangents[0].x);
		float ty = abs(tangents[0].y);
		float tz = abs(tangents[0].z);

		if (tx <= min)
		{
			min = tx;
			normal = vec3(1, 0, 0);
		}

		if (ty <= min)
		{
			min = ty;
			normal = vec3(0, 1, 0);
		}

		if (tz <= min)
		{
			normal = vec3(0, 0, 1);
		}

		vec = normalize(cross(tangents[0], normal));

		normals[0] = cross(tangents[0], vec);
		binormals[0] = cross(tangents[0], normals[0]);

		// compute the slowly-varying normal and binormal vectors for each segment on the curve
		for (i = 1; i <= segments; i ++)
		{
			normals[i] = normals[i - 1];
			binormals[i] = binormals[i - 1];

			vec = cross(tangents[i - 1], tangents[i]);

			if (length(vec) > c_cmp_epsilon)
			{
				vec = normalize(vec);

				theta = acos(clamp(dot(tangents[i - 1], tangents[i]), -1.f, 1.f)); // clamp for floating pt errors

				//normals[i].applyMatrix4(mat.makeRotationAxis(vec, theta));
				normals[i] = axis_angle(vec, theta) * normals[i];
			}

			binormals[i] = cross(tangents[i], normals[i]);
		}

		// if the curve is closed, postprocess the vectors so the first and last normal vectors are the same
		if (closed == true)
		{
			theta = acos(clamp(dot(normals[0], normals[segments]), -1.f, 1.f));
			theta /= segments;

			if (dot(tangents[0], cross(normals[0], normals[segments])) > 0)
			{
				theta = - theta;
			}

			for (i = 1; i <= segments; i ++)
			{
				// twist a little...
				//normals[i].applyMatrix4(mat.makeRotationAxis(tangents[i], theta * i));
				normals[i] = axis_angle(tangents[i], theta * i) * normals[i];
				binormals[i] = cross(tangents[i], normals[i]);
			}
		}

		return { tangents, normals, binormals };
	}

#if 0
	struct EllipseCurve : public Curve
	{
		float m_aX = 0;
		float m_aY = 0;

		float m_xRadius = 1;
		float m_yRadius = 1;

		float m_aStartAngle = 0;
		float m_aEndAngle = 2 * c_pi;

		float m_aClockwise = false;

		float m_aRotation = 0;

		vec3 point(float t, vec2 target = vec2(0.f)) //, optionalTarget)
		{
			vec2 point; // = optionalTarget || new Vector2();

			float deltaAngle = m_aEndAngle - m_aStartAngle;
			bool samePoints = abs(deltaAngle) < Number.EPSILON;

			// ensures that deltaAngle is 0 .. 2 c_pi
			while (deltaAngle < 0) deltaAngle += c_2pi;
			while (deltaAngle > c_2pi) deltaAngle -= c_2pi;

			if (deltaAngle < Number.EPSILON)
			{
				deltaAngle = samePoints ? 0 : c_2pi;
			}

			if (m_aClockwise === true && ! samePoints)
			{
				deltaAngle = deltaAngle == c_2pi ? -c_2pi : deltaAngle - c_2pi;
			}

			float angle = m_aStartAngle + t * deltaAngle;
			float x = m_aX + m_xRadius * cos(angle);
			float y = m_aY + m_yRadius * sin(angle);

			if (m_aRotation != 0)
			{
				float cos = mud::cos(m_aRotation);
				float sin = mud::sin(m_aRotation);

				float tx = x - m_aX;
				float ty = y - m_aY;

				// Rotate the point about the center of the ellipse.
				x = tx * cos - ty * sin + m_aX;
				y = tx * sin + ty * cos + m_aY;

			}

			return point = vec2(x, y);
		};
	};

	function ArcCurve(aX, aY, aRadius, aStartAngle, aEndAngle, aClockwise) {

		EllipseCurve.call(this, aX, aY, aRadius, aRadius, aStartAngle, aEndAngle, aClockwise);

	}

	ArcCurve.prototype = Object.create(EllipseCurve.prototype);
	ArcCurve.prototype.constructor = ArcCurve;

	ArcCurve.prototype.isArcCurve = true;

#endif

	/**
	 * @author zz85 https://github.com/zz85
	 *
	 * Centripetal CatmullRom Curve - which is useful for avoiding
	 * cusps and self-intersections in non-uniform catmull rom curves.
	 * http://www.cemyuksel.com/research/catmullrom_param/catmullrom.pdf
	 *
	 * curve.type accepts centripetal(default), chordal and catmullrom
	 * curve.tension is used for catmullrom which defaults to 0.5
	 */

	/*
	Based on an optimized c++ solution in
	 - http://stackoverflow.com/questions/9489736/catmull-rom-curve-with-no-cusps-and-no-self-intersections/
	 - http://ideone.com/NoEbVM

	This CubicPoly class could be used for reusing some variables and calculations,
	but for three.js curve use, it could be possible inlined and flatten into a single function call
	which can be placed in CurveUtils.
	*/

	struct CubicPoly
	{
		float c0 = 0, c1 = 0, c2 = 0, c3 = 0;

		/*
		 * Compute coefficients for a cubic polynomial
		 *   p(s) = c0 + c1*s + c2*s^2 + c3*s^3
		 * such that
		 *   p(0) = x0, p(1) = x1
		 *  and
		 *   p'(0) = t0, p'(1) = t1.
		 */
		void init(float x0, float x1, float t0, float t1) {

			c0 = x0;
			c1 = t0;
			c2 = - 3 * x0 + 3 * x1 - 2 * t0 - t1;
			c3 = 2 * x0 - 2 * x1 + t0 + t1;

		}

		void initCatmullRom(float x0, float x1, float x2, float x3, float tension)
		{
			init(x1, x2, tension * (x2 - x0), tension * (x3 - x1));
		}

		void initNonuniformCatmullRom(float x0, float x1, float x2, float x3, float dt0, float dt1, float dt2)
		{
			// compute tangents when parameterized in [t1,t2]
			float t1 = (x1 - x0) / dt0 - (x2 - x0) / (dt0 + dt1) + (x2 - x1) / dt1;
			float t2 = (x2 - x1) / dt1 - (x3 - x1) / (dt1 + dt2) + (x3 - x2) / dt2;

			// rescale tangents for parametrization in [0,1]
			t1 *= dt1;
			t2 *= dt1;

			init(x1, x2, t1, t2);
		}

		float calc(float t)
		{
			float t2 = t * t;
			float t3 = t2 * t;
			return c0 + c1 * t + c2 * t2 + c3 * t3;
		}
	};

	vec3 CatmullRomCurve3::point(float t, vec3 target)
	{
		static CubicPoly px;
		static CubicPoly py;
		static CubicPoly pz;

		vec3 point = target;

		const vector<vec3>& points = m_points;
		size_t l = points.size();

		float p = (l - (m_closed ? 0 : 1)) * t;
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

		vec3 p0, p1, p2, p3; // 4 points

		if(m_closed || i > 0)
		{
			p0 = points[(i - 1) % l];
		}
		else
		{
			// extrapolate first point
			p0 = points[0] - points[1] + points[0];
		}

		p1 = points[i % l];
		p2 = points[(i + 1) % l];

		if(m_closed || i + 2 < l)
		{
			p3 = points[(i + 2) % l];
		}
		else
		{
			// extrapolate last point
			p3 = points[l - 1] - points[l - 2] + points[l - 1];
		}

		if(m_curveType == CurveType::Centripetal || m_curveType == CurveType::Chordal)
		{
			// init Centripetal / Chordal Catmull-Rom
			float power = m_curveType == CurveType::Chordal ? 0.5f : 0.25f;
			float dt0 = pow(distance2(p0, p1), power);
			float dt1 = pow(distance2(p1, p2), power);
			float dt2 = pow(distance2(p2, p3), power);

			// safety check for repeated points
			if(dt1 < 1e-4) dt1 = 1.0;
			if(dt0 < 1e-4) dt0 = dt1;
			if(dt2 < 1e-4) dt2 = dt1;

			px.initNonuniformCatmullRom(p0.x, p1.x, p2.x, p3.x, dt0, dt1, dt2);
			py.initNonuniformCatmullRom(p0.y, p1.y, p2.y, p3.y, dt0, dt1, dt2);
			pz.initNonuniformCatmullRom(p0.z, p1.z, p2.z, p3.z, dt0, dt1, dt2);
		}
		else if(m_curveType == CurveType::CatmullRom)
		{
			px.initCatmullRom(p0.x, p1.x, p2.x, p3.x, m_tension);
			py.initCatmullRom(p0.y, p1.y, p2.y, p3.y, m_tension);
			pz.initCatmullRom(p0.z, p1.z, p2.z, p3.z, m_tension);
		}

		point = vec3(
			px.calc(weight),
			py.calc(weight),
			pz.calc(weight)
		);

		return point;
	}

	/**
	 * @author zz85 / http://www.lab4games.net/zz85/blog
	 *
	 * Bezier Curves formulas obtained from
	 * http://en.wikipedia.org/wiki/Bézier_curve
	 */

#if 0
	function CatmullRom(t, p0, p1, p2, p3) {

		var v0 = (p2 - p0) * 0.5;
		var v1 = (p3 - p1) * 0.5;
		var t2 = t * t;
		var t3 = t * t2;
		return (2 * p1 - 2 * p2 + v0 + v1) * t3 + (- 3 * p1 + 3 * p2 - 2 * v0 - v1) * t2 + v0 * t + p1;

	}

	//

	function QuadraticBezierP0(t, p) {

		var k = 1 - t;
		return k * k * p;

	}

	function QuadraticBezierP1(t, p) {

		return 2 * (1 - t) * t * p;

	}

	function QuadraticBezierP2(t, p) {

		return t * t * p;

	}

	function QuadraticBezier(t, p0, p1, p2) {

		return QuadraticBezierP0(t, p0) + QuadraticBezierP1(t, p1) +
			QuadraticBezierP2(t, p2);

	}

	//

	function CubicBezierP0(t, p) {

		var k = 1 - t;
		return k * k * k * p;

	}

	function CubicBezierP1(t, p) {

		var k = 1 - t;
		return 3 * k * k * t * p;

	}

	function CubicBezierP2(t, p) {

		return 3 * (1 - t) * t * t * p;

	}

	function CubicBezierP3(t, p) {

		return t * t * t * p;

	}

	function CubicBezier(t, p0, p1, p2, p3) {

		return CubicBezierP0(t, p0) + CubicBezierP1(t, p1) + CubicBezierP2(t, p2) +
			CubicBezierP3(t, p3);

	}

	function CubicBezierCurve(v0, v1, v2, v3) {

		Curve.call(this);

		this->type = 'CubicBezierCurve';

		this->v0 = v0 || new Vector2();
		this->v1 = v1 || new Vector2();
		this->v2 = v2 || new Vector2();
		this->v3 = v3 || new Vector2();

	}

	CubicBezierCurve.prototype = Object.create(Curve.prototype);
	CubicBezierCurve.prototype.constructor = CubicBezierCurve;

	CubicBezierCurve.prototype.isCubicBezierCurve = true;

	CubicBezierCurve.prototype.point = function (t, optionalTarget) {

		var point = optionalTarget || new Vector2();

		var v0 = this->v0, v1 = this->v1, v2 = this->v2, v3 = this->v3;

		point.set(
			CubicBezier(t, v0.x, v1.x, v2.x, v3.x),
			CubicBezier(t, v0.y, v1.y, v2.y, v3.y)
		);

		return point;

	};

	CubicBezierCurve.prototype.copy = function (source) {

		Curve.prototype.copy.call(this, source);

		this->v0.copy(source.v0);
		this->v1.copy(source.v1);
		this->v2.copy(source.v2);
		this->v3.copy(source.v3);

		return this;

	};

	CubicBezierCurve.prototype.toJSON = function () {

		var data = Curve.prototype.toJSON.call(this);

		data.v0 = this->v0.toArray();
		data.v1 = this->v1.toArray();
		data.v2 = this->v2.toArray();
		data.v3 = this->v3.toArray();

		return data;

	};

	CubicBezierCurve.prototype.fromJSON = function (json) {

		Curve.prototype.fromJSON.call(this, json);

		this->v0.fromArray(json.v0);
		this->v1.fromArray(json.v1);
		this->v2.fromArray(json.v2);
		this->v3.fromArray(json.v3);

		return this;

	};

	function CubicBezierCurve3(v0, v1, v2, v3) {

		Curve.call(this);

		this->v0 = v0 || vec3();
		this->v1 = v1 || vec3();
		this->v2 = v2 || vec3();
		this->v3 = v3 || vec3();

	}

	CubicBezierCurve3.prototype = Object.create(Curve.prototype);
	CubicBezierCurve3.prototype.constructor = CubicBezierCurve3;

	CubicBezierCurve3.prototype.isCubicBezierCurve3 = true;

	CubicBezierCurve3.prototype.point = function (t, optionalTarget) {

		var point = optionalTarget || vec3();

		var v0 = this->v0, v1 = this->v1, v2 = this->v2, v3 = this->v3;

		point = vec3(
			CubicBezier(t, v0.x, v1.x, v2.x, v3.x),
			CubicBezier(t, v0.y, v1.y, v2.y, v3.y),
			CubicBezier(t, v0.z, v1.z, v2.z, v3.z)
		);

		return point;

	};

	CubicBezierCurve3.prototype.copy = function (source) {

		Curve.prototype.copy.call(this, source);

		this->v0.copy(source.v0);
		this->v1.copy(source.v1);
		this->v2.copy(source.v2);
		this->v3.copy(source.v3);

		return this;

	};

	CubicBezierCurve3.prototype.toJSON = function () {

		var data = Curve.prototype.toJSON.call(this);

		data.v0 = this->v0.toArray();
		data.v1 = this->v1.toArray();
		data.v2 = this->v2.toArray();
		data.v3 = this->v3.toArray();

		return data;

	};

	CubicBezierCurve3.prototype.fromJSON = function (json) {

		Curve.prototype.fromJSON.call(this, json);

		this->v0.fromArray(json.v0);
		this->v1.fromArray(json.v1);
		this->v2.fromArray(json.v2);
		this->v3.fromArray(json.v3);

		return this;

	};

	function LineCurve(v1, v2) {

		Curve.call(this);

		this->v1 = v1 || new Vector2();
		this->v2 = v2 || new Vector2();

	}

	LineCurve.prototype = Object.create(Curve.prototype);
	LineCurve.prototype.constructor = LineCurve;

	LineCurve.prototype.isLineCurve = true;

	LineCurve.prototype.point = function (t, optionalTarget) {

		var point = optionalTarget || new Vector2();

		if (t === 1) {

			point.copy(this->v2);

		} else {

			point.copy(this->v2).sub(this->v1);
			point.multiplyScalar(t).add(this->v1);

		}

		return point;

	};

	// Line curve is linear, so we can overwrite default pointAt

	LineCurve.prototype.pointAt = function (u, optionalTarget) {

		return this->point(u, optionalTarget);

	};

	LineCurve.prototype.getTangent = function (/* t */) {

		var tangent = this->v2.clone().sub(this->v1);

		return tangent.normalize();

	};

	LineCurve.prototype.copy = function (source) {

		Curve.prototype.copy.call(this, source);

		this->v1.copy(source.v1);
		this->v2.copy(source.v2);

		return this;

	};

	LineCurve.prototype.toJSON = function () {

		var data = Curve.prototype.toJSON.call(this);

		data.v1 = this->v1.toArray();
		data.v2 = this->v2.toArray();

		return data;

	};

	LineCurve.prototype.fromJSON = function (json) {

		Curve.prototype.fromJSON.call(this, json);

		this->v1.fromArray(json.v1);
		this->v2.fromArray(json.v2);

		return this;

	};

	function LineCurve3(v1, v2) {

		Curve.call(this);

		this->v1 = v1 || vec3();
		this->v2 = v2 || vec3();

	}

	LineCurve3.prototype = Object.create(Curve.prototype);
	LineCurve3.prototype.constructor = LineCurve3;

	LineCurve3.prototype.isLineCurve3 = true;

	LineCurve3.prototype.point = function (t, optionalTarget) {

		var point = optionalTarget || vec3();

		if (t === 1) {

			point.copy(this->v2);

		} else {

			point.copy(this->v2).sub(this->v1);
			point.multiplyScalar(t).add(this->v1);

		}

		return point;

	};

	// Line curve is linear, so we can overwrite default pointAt

	LineCurve3.prototype.pointAt = function (u, optionalTarget) {

		return this->point(u, optionalTarget);

	};

	LineCurve3.prototype.copy = function (source) {

		Curve.prototype.copy.call(this, source);

		this->v1.copy(source.v1);
		this->v2.copy(source.v2);

		return this;

	};

	LineCurve3.prototype.toJSON = function () {

		var data = Curve.prototype.toJSON.call(this);

		data.v1 = this->v1.toArray();
		data.v2 = this->v2.toArray();

		return data;

	};

	LineCurve3.prototype.fromJSON = function (json) {

		Curve.prototype.fromJSON.call(this, json);

		this->v1.fromArray(json.v1);
		this->v2.fromArray(json.v2);

		return this;

	};

	function QuadraticBezierCurve(v0, v1, v2) {

		Curve.call(this);

		this->v0 = v0 || new Vector2();
		this->v1 = v1 || new Vector2();
		this->v2 = v2 || new Vector2();

	}

	QuadraticBezierCurve.prototype = Object.create(Curve.prototype);
	QuadraticBezierCurve.prototype.constructor = QuadraticBezierCurve;

	QuadraticBezierCurve.prototype.isQuadraticBezierCurve = true;

	QuadraticBezierCurve.prototype.point = function (t, optionalTarget) {

		var point = optionalTarget || new Vector2();

		var v0 = this->v0, v1 = this->v1, v2 = this->v2;

		point.set(
			QuadraticBezier(t, v0.x, v1.x, v2.x),
			QuadraticBezier(t, v0.y, v1.y, v2.y)
		);

		return point;

	};

	QuadraticBezierCurve.prototype.copy = function (source) {

		Curve.prototype.copy.call(this, source);

		this->v0.copy(source.v0);
		this->v1.copy(source.v1);
		this->v2.copy(source.v2);

		return this;

	};

	QuadraticBezierCurve.prototype.toJSON = function () {

		var data = Curve.prototype.toJSON.call(this);

		data.v0 = this->v0.toArray();
		data.v1 = this->v1.toArray();
		data.v2 = this->v2.toArray();

		return data;

	};

	QuadraticBezierCurve.prototype.fromJSON = function (json) {

		Curve.prototype.fromJSON.call(this, json);

		this->v0.fromArray(json.v0);
		this->v1.fromArray(json.v1);
		this->v2.fromArray(json.v2);

		return this;

	};

	function QuadraticBezierCurve3(v0, v1, v2) {

		Curve.call(this);

		this->v0 = v0 || vec3();
		this->v1 = v1 || vec3();
		this->v2 = v2 || vec3();

	}

	QuadraticBezierCurve3.prototype = Object.create(Curve.prototype);
	QuadraticBezierCurve3.prototype.constructor = QuadraticBezierCurve3;

	QuadraticBezierCurve3.prototype.isQuadraticBezierCurve3 = true;

	QuadraticBezierCurve3.prototype.point = function (t, optionalTarget) {

		var point = optionalTarget || vec3();

		var v0 = this->v0, v1 = this->v1, v2 = this->v2;

		point = vec3(
			QuadraticBezier(t, v0.x, v1.x, v2.x),
			QuadraticBezier(t, v0.y, v1.y, v2.y),
			QuadraticBezier(t, v0.z, v1.z, v2.z)
		);

		return point;

	};

	QuadraticBezierCurve3.prototype.copy = function (source) {

		Curve.prototype.copy.call(this, source);

		this->v0.copy(source.v0);
		this->v1.copy(source.v1);
		this->v2.copy(source.v2);

		return this;

	};

	QuadraticBezierCurve3.prototype.toJSON = function () {

		var data = Curve.prototype.toJSON.call(this);

		data.v0 = this->v0.toArray();
		data.v1 = this->v1.toArray();
		data.v2 = this->v2.toArray();

		return data;

	};

	QuadraticBezierCurve3.prototype.fromJSON = function (json) {

		Curve.prototype.fromJSON.call(this, json);

		this->v0.fromArray(json.v0);
		this->v1.fromArray(json.v1);
		this->v2.fromArray(json.v2);

		return this;

	};

	function SplineCurve(points /* array of Vector2 */) {

		Curve.call(this);

		this->points = points || [];

	}

	SplineCurve.prototype = Object.create(Curve.prototype);
	SplineCurve.prototype.constructor = SplineCurve;

	SplineCurve.prototype.isSplineCurve = true;

	SplineCurve.prototype.point = function (t, optionalTarget) {

		var point = optionalTarget || new Vector2();

		var points = this->points;
		var p = (points.size() - 1) * t;

		var i = floor(p);
		var weight = p - i;

		var p0 = points[i === 0 ? i : i - 1];
		var p1 = points[i];
		var p2 = points[i > points.size() - 2 ? points.size() - 1 : i + 1];
		var p3 = points[i > points.size() - 3 ? points.size() - 1 : i + 2];

		point.set(
			CatmullRom(weight, p0.x, p1.x, p2.x, p3.x),
			CatmullRom(weight, p0.y, p1.y, p2.y, p3.y)
		);

		return point;

	};

	SplineCurve.prototype.copy = function (source) {

		Curve.prototype.copy.call(this, source);

		this->points = [];

		for (var i = 0, l = source.points.size(); i < l; i ++) {

			var point = source.points[i];

			this->points.push_back(point.clone());

		}

		return this;

	};

	SplineCurve.prototype.toJSON = function () {

		var data = Curve.prototype.toJSON.call(this);

		data.points = [];

		for (var i = 0, l = this->points.size(); i < l; i ++) {

			var point = this->points[i];
			data.points.push_back(point.toArray());

		}

		return data;

	};

	SplineCurve.prototype.fromJSON = function (json) {

		Curve.prototype.fromJSON.call(this, json);

		this->points = [];

		for (var i = 0, l = json.points.size(); i < l; i ++) {

			var point = json.points[i];
			this->points.push_back(new Vector2().fromArray(point));

		}

		return this;

	};



	var Curves = /*#__PURE__*/Object.freeze({
		ArcCurve: ArcCurve,
		CatmullRomCurve3: CatmullRomCurve3,
		CubicBezierCurve: CubicBezierCurve,
		CubicBezierCurve3: CubicBezierCurve3,
		EllipseCurve: EllipseCurve,
		LineCurve: LineCurve,
		LineCurve3: LineCurve3,
		QuadraticBezierCurve: QuadraticBezierCurve,
		QuadraticBezierCurve3: QuadraticBezierCurve3,
		SplineCurve: SplineCurve
	});

	/**
	 * @author zz85 / http://www.lab4games.net/zz85/blog
	 *
	 **/

	/**************************************************************
	 *	Curved Path - a curve path is simply a array of connected
	 *  curves, but retains the api of a curve
	 **************************************************************/

	function CurvePath() {

		Curve.call(this);

		this->curves = [];
		this->autoClose = false; // Automatically closes the path

	}

	CurvePath.prototype = Object.assign(Object.create(Curve.prototype), {

		constructor: CurvePath,

		add(curve) {

			this->curves.push_back(curve);

		},

		closePath() {

			// Add a line curve if start and end of lines are not connected
			var startPoint = this->curves[0].point(0);
			var endPoint = this->curves[this->curves.size() - 1].point(1);

			if (! startPoint.equals(endPoint)) {

				this->curves.push_back(new LineCurve(endPoint, startPoint));

			}

		},

		// To get accurate point with reference to
		// entire path distance at time t,
		// following has to be done:

		// 1. Length of each sub path have to be known
		// 2. Locate and identify type of curve
		// 3. Get t for the curve
		// 4. Return curve.pointAt(t')

		point(t) {

			var d = t * this->getLength();
			var curveLengths = this->getCurveLengths();
			var i = 0;

			// To think about boundaries points.

			while (i < curveLengths.size()) {

				if (curveLengths[i] >= d) {

					var diff = curveLengths[i] - d;
					var curve = this->curves[i];

					var segmentLength = curve.getLength();
					var u = segmentLength === 0 ? 0 : 1 - diff / segmentLength;

					return curve.pointAt(u);

				}

				i ++;

			}

			return null;

			// loop where sum != 0, sum > d , sum+1 <d

		},

		// We cannot use the default Curve point() with getLength() because in
		// Curve, getLength() depends on point() but in CurvePath
		// point() depends on getLength

		getLength() {

			var lens = this->getCurveLengths();
			return lens[lens.size() - 1];

		},

		// cacheLengths must be recalculated.
		updateArcLengths() {

			m_dirty = true;
			this->cacheLengths = null;
			this->getCurveLengths();

		},

		// Compute lengths and cache them
		// We cannot overwrite getLengths() because UtoT mapping uses it.

		getCurveLengths() {

			// We use cache values if curves and cache array are same length

			if (this->cacheLengths && this->cacheLengths.size() === this->curves.size()) {

				return this->cacheLengths;

			}

			// Get length of sub-curve
			// Push sums into cached array

			var lengths = [], sums = 0;

			for (var i = 0, l = this->curves.size(); i < l; i ++) {

				sums += this->curves[i].getLength();
				lengths.push_back(sums);

			}

			this->cacheLengths = lengths;

			return lengths;

		},

		getSpacedPoints(divisions) {

			if (divisions === undefined) divisions = 40;

			var points = [];

			for (var i = 0; i <= divisions; i ++) {

				points.push_back(this->point(i / divisions));

			}

			if (this->autoClose) {

				points.push_back(points[0]);

			}

			return points;

		},

		points(divisions) {

			divisions = divisions || 12;

			var points = [], last;

			for (var i = 0, curves = this->curves; i < curves.size(); i ++) {

				var curve = curves[i];
				var resolution = (curve && curve.isEllipseCurve) ? divisions * 2
					: (curve && (curve.isLineCurve || curve.isLineCurve3)) ? 1
						: (curve && curve.isSplineCurve) ? divisions * curve.points.size()
							: divisions;

				var pts = curve.points(resolution);

				for (var j = 0; j < pts.size(); j ++) {

					var point = pts[j];

					if (last && last.equals(point)) continue; // ensures no consecutive points are duplicates

					points.push_back(point);
					last = point;

				}

			}

			if (this->autoClose && points.size() > 1 && ! points[points.size() - 1].equals(points[0])) {

				points.push_back(points[0]);

			}

			return points;

		},

		copy(source) {

			Curve.prototype.copy.call(this, source);

			this->curves = [];

			for (var i = 0, l = source.curves.size(); i < l; i ++) {

				var curve = source.curves[i];

				this->curves.push_back(curve.clone());

			}

			this->autoClose = source.autoClose;

			return this;

		},

		toJSON() {

			var data = Curve.prototype.toJSON.call(this);

			data.autoClose = this->autoClose;
			data.curves = [];

			for (var i = 0, l = this->curves.size(); i < l; i ++) {

				var curve = this->curves[i];
				data.curves.push_back(curve.toJSON());

			}

			return data;

		},

		fromJSON(json) {

			Curve.prototype.fromJSON.call(this, json);

			this->autoClose = json.autoClose;
			this->curves = [];

			for (var i = 0, l = json.curves.size(); i < l; i ++) {

				var curve = json.curves[i];
				this->curves.push_back(new Curves[curve.type]().fromJSON(curve));

			}

			return this;

		}

	});

	/**
	 * @author zz85 / http://www.lab4games.net/zz85/blog
	 * Creates free form 2d path using series of points, lines or curves.
	 **/

	function Path(points) {

		CurvePath.call(this);

		this->type = 'Path';

		this->currentPoint = new Vector2();

		if (points) {

			this->setFromPoints(points);

		}

	}

	Path.prototype = Object.assign(Object.create(CurvePath.prototype), {

		constructor: Path,

		setFromPoints(points) {

			this->moveTo(points[0].x, points[0].y);

			for (var i = 1, l = points.size(); i < l; i ++) {

				this->lineTo(points[i].x, points[i].y);

			}

		},

		moveTo(x, y) {

			this->currentPoint.set(x, y); // TODO consider referencing vectors instead of copying?

		},

		lineTo(x, y) {

			var curve = new LineCurve(this->currentPoint.clone(), new Vector2(x, y));
			this->curves.push_back(curve);

			this->currentPoint.set(x, y);

		},

		quadraticCurveTo(aCPx, aCPy, aX, aY) {

			var curve = new QuadraticBezierCurve(
				this->currentPoint.clone(),
				new Vector2(aCPx, aCPy),
				new Vector2(aX, aY)
			);

			this->curves.push_back(curve);

			this->currentPoint.set(aX, aY);

		},

		bezierCurveTo(aCP1x, aCP1y, aCP2x, aCP2y, aX, aY) {

			var curve = new CubicBezierCurve(
				this->currentPoint.clone(),
				new Vector2(aCP1x, aCP1y),
				new Vector2(aCP2x, aCP2y),
				new Vector2(aX, aY)
			);

			this->curves.push_back(curve);

			this->currentPoint.set(aX, aY);

		},

		splineThru(pts /*Array of Vector*/) {

			var npts = [this->currentPoint.clone()].concat(pts);

			var curve = new SplineCurve(npts);
			this->curves.push_back(curve);

			this->currentPoint.copy(pts[pts.size() - 1]);

		},

		arc(aX, aY, aRadius, aStartAngle, aEndAngle, aClockwise) {

			var x0 = this->currentPoint.x;
			var y0 = this->currentPoint.y;

			this->absarc(aX + x0, aY + y0, aRadius,
				aStartAngle, aEndAngle, aClockwise);

		},

		absarc(aX, aY, aRadius, aStartAngle, aEndAngle, aClockwise) {

			this->absellipse(aX, aY, aRadius, aRadius, aStartAngle, aEndAngle, aClockwise);

		},

		ellipse(aX, aY, xRadius, yRadius, aStartAngle, aEndAngle, aClockwise, aRotation) {

			var x0 = this->currentPoint.x;
			var y0 = this->currentPoint.y;

			this->absellipse(aX + x0, aY + y0, xRadius, yRadius, aStartAngle, aEndAngle, aClockwise, aRotation);

		},

		absellipse(aX, aY, xRadius, yRadius, aStartAngle, aEndAngle, aClockwise, aRotation) {

			var curve = new EllipseCurve(aX, aY, xRadius, yRadius, aStartAngle, aEndAngle, aClockwise, aRotation);

			if (this->curves.size() > 0) {

				// if a previous curve is present, attempt to join
				var firstPoint = curve.point(0);

				if (! firstPoint.equals(this->currentPoint)) {

					this->lineTo(firstPoint.x, firstPoint.y);

				}

			}

			this->curves.push_back(curve);

			var lastPoint = curve.point(1);
			this->currentPoint.copy(lastPoint);

		},

		copy(source) {

			CurvePath.prototype.copy.call(this, source);

			this->currentPoint.copy(source.currentPoint);

			return this;

		},

		toJSON() {

			var data = CurvePath.prototype.toJSON.call(this);

			data.currentPoint = this->currentPoint.toArray();

			return data;

		},

		fromJSON(json) {

			CurvePath.prototype.fromJSON.call(this, json);

			this->currentPoint.fromArray(json.currentPoint);

			return this;

		}

	});

	/**
	 * @author zz85 / http://www.lab4games.net/zz85/blog
	 * Defines a 2d shape plane using paths.
	 **/

	// STEP 1 Create a path.
	// STEP 2 Turn path into shape.
	// STEP 3 ExtrudeGeometry takes in Shape/Shapes
	// STEP 3a - Extract points from each shape, turn to vertices
	// STEP 3b - Triangulate each shape, add faces.

	function Shape(points) {

		Path.call(this, points);

		this->uuid = _generateUUID();

		this->holes = [];

	}

	Shape.prototype = Object.assign(Object.create(Path.prototype), {

		constructor: Shape,

		pointsHoles(divisions) {

			var holesPts = [];

			for (var i = 0, l = this->holes.size(); i < l; i ++) {

				holesPts[i] = this->holes[i].points(divisions);

			}

			return holesPts;

		},

		// get points of shape and holes (keypoints based on segments parameter)

		extractPoints(divisions) {

			return {

				shape: this->points(divisions),
				holes: this->pointsHoles(divisions)

			};

		},

		copy(source) {

			Path.prototype.copy.call(this, source);

			this->holes = [];

			for (var i = 0, l = source.holes.size(); i < l; i ++) {

				var hole = source.holes[i];

				this->holes.push_back(hole.clone());

			}

			return this;

		},

		toJSON() {

			var data = Path.prototype.toJSON.call(this);

			data.uuid = this->uuid;
			data.holes = [];

			for (var i = 0, l = this->holes.size(); i < l; i ++) {

				var hole = this->holes[i];
				data.holes.push_back(hole.toJSON());

			}

			return data;

		},

		fromJSON(json) {

			Path.prototype.fromJSON.call(this, json);

			this->uuid = json.uuid;
			this->holes = [];

			for (var i = 0, l = json.holes.size(); i < l; i ++) {

				var hole = json.holes[i];
				this->holes.push_back(new Path().fromJSON(hole));

			}

			return this;

		}

	});
#endif
}
