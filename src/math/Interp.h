//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <type/Ref.h>
#endif
#include <math/Forward.h>
#include <math/Vec.hpp>

namespace two
{
	inline quat lerp(const quat& a, const quat& b, float c)
	{
		return slerp(a, b, c);
	}

	export_ template <class T>
	inline T catmull_rom(const T& p0, const T& p1, const T& p2, const T& p3, float t)
	{
		const float t2 = t * t;
		const float t3 = t2 * t;

		return 0.5f * ((2.f * p1) + (-p0 + p2) * t + (2.f * p0 - 5.f * p1 + 4.f * p2 - p3) * t2 + (-p0 + 3.f * p1 - 3.f * p2 + p3) * t3);
	}

	export_ template <class T>
	inline T catmull_rom_three(const T& p0, const T& p1, const T& p2, const T& p3, float t)
	{
		const T v0 = (p2 - p0) * 0.5f;
		const T v1 = (p3 - p1) * 0.5f;
		const float t2 = t * t;
		const float t3 = t * t2;
		return (2.f * p1 - 2.f * p2 + v0 + v1) * t3 + (-3.f * p1 + 3.f * p2 - 2.f * v0 - v1) * t2 + v0 * t + p1;
	}

	export_ template <class T>
	inline T cubic_interpolate(const T& a, const T& b, const T& p0, const T& p1, float t)
	{
		const float t2 = t * t;
		const float t3 = t2 * t;

		return 0.5f * ((2.f * a) + (-p0 + b) * t + (2.f * p0 - 5.f * a + 4.f * b - p1) * t2 + (-p0 + 3.f * a - 3.f * b + p1) * t3);
	}

	export_ template <class T>
	inline T bezier(T p0, T p1, T p2, T p3, float t)
	{
		const float k = (1.f - t);
		const float k2 = k * k;
		const float k3 = k2 * k;
		const float t2 = t * t;
		const float t3 = t2 * t;

		return p0 * k3 + p1 * k2 * t * 3.f + p2 * k * t2 * 3.f + p3 * t3;
	}
	
	export_ template <class T>
	inline T cubic_bezier(T p0, T p1, T p2, T p3, float t)
	{
		auto t0 = [](T p, float t) { float k = 1.f - t;	return k * k * k * p; };
		auto t1 = [](T p, float t) { float k = 1.f - t;	return 3.f * k * k * t * p; };
		auto t2 = [](T p, float t) { float k = 1.f - t;	return 3.f * k * t * t * p; };
		auto t3 = [](T p, float t) { return t * t * t * p; };

		return t0(p0, t) + t1(p1, t) + t2(p2, t) + t3(p3, t);
	}
	
	export_ template <class T>
	inline T quad_bezier(T p0, T p1, T p2, float t)
	{
		auto t0 = [](T p, float t) { float k = 1.f - t; return k * k * p; };
		auto t1 = [](T p, float t) { float k = 1.f - t; return 2.f * k * t * p; };
		auto t2 = [](T p, float t) { return t * t * p; };

		return t0(p0, t) + t1(p1, t) + t2(p2, t);
	}

	export_ template <>
	inline quat catmull_rom(const quat& p0, const quat& p1, const quat& p2, const quat& p3, float c)
	{
		UNUSED(p0); UNUSED(p3);
		return slerp(p1, p2, c);
	}

	export_ template <>
	inline quat bezier(quat start, quat control_1, quat control_2, quat end, float t)
	{
		UNUSED(control_1); UNUSED(control_2);
		return slerp(start, end, t);
	}

	inline Colour lerp(const Colour& a, const Colour& b, float c)
	{
		vec4 va = to_vec4(a);
		vec4 vb = to_vec4(b);
		return to_colour(va + (vb - va) * c);
	}

	export_ TWO_MATH_EXPORT void interpolate(Ref result, Ref a, Ref b, float t);
	export_ inline void interpolate_cubic(Ref result, Ref a, Ref b, Ref d, Ref e, float t) { UNUSED(e); UNUSED(d); return interpolate(result, a, b, t); }
	//export_ inline Var interpolate_cubic(Ref a, Ref b, Ref d, Ref e, float t) { UNUSED(e); UNUSED(d); return interpolate(a, b, t); }
}
