//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <obj/Var.h>
#include <infra/Global.h>
#include <obj/Dispatch.h>
#include <refl/Meta.h>
#endif
#include <math/Forward.h>
#include <math/VecOps.h>

namespace mud
{
	export_ class MUD_MATH_EXPORT Lerp : public Dispatch<void, Ref, Ref, float>, public LazyGlobal<Lerp>
	{
	public:
		Lerp();
	};

	export_ template <class T>
	inline T lerp(const T& a, const T& b, float c)
	{
		return T(a + (b - a) * c);
	}

	export_ template <class T>
	inline T catmull_rom(const T& p0, const T& p1, const T& p2, const T& p3, float t)
	{
		float t2 = t * t;
		float t3 = t2 * t;

		return 0.5f * ((2.0f * p1) + (-p0 + p2) * t + (2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3) * t2 + (-p0 + 3.0f * p1 - 3.0f * p2 + p3) * t3);
	}

	export_ template <class T>
	inline T bezier(T start, T control_1, T control_2, T end, float t)
	{
		/* Formula from Wikipedia article on Bezier curves.*/
		float omt = (1.f - t);
		float omt2 = omt * omt;
		float omt3 = omt2 * omt;
		float t2 = t * t;
		float t3 = t2 * t;

		return start * omt3 + control_1 * omt2 * t * 3.f + control_2 * omt * t2 * 3.f + end * t3;
	}

	export_ template <class T>
	inline T cubic_interpolate(const T& a, const T& b, const T& pre_a, const T& post_b, float t)
	{
		float t2 = t * t;
		float t3 = t2 * t;

		return 0.5f * ((2.f * a) + (-pre_a + b) * t + (2.f * pre_a - 5.f* a + 4.f * b - post_b) * t2 + (-pre_a + 3.f * a - 3.f * b + post_b) * t3);
	}

	export_ template <>
	inline quat lerp(const quat& a, const quat& b, float c)
	{
		return slerp(a, b, c);
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

	export_ template <>
	inline Colour lerp(const Colour& a, const Colour& b, float c)
	{
		vec4 va = to_vec4(a);
		vec4 vb = to_vec4(b);
		return to_colour(va + (vb - va) * c);
	}

	export_ inline Var interpolate(Ref a, Ref b, float t) { Var result = meta(a).m_empty_var(); Lerp::me().dispatch(result.m_ref, a, b, t); return result; }
	export_ inline void interpolate(Var& result, Ref a, Ref b, float t) { Lerp::me().dispatch(result.m_ref, a, b, t); }
	export_ inline Var interpolate(const Var& a, const Var& b, float t) { return interpolate(a.m_ref, b.m_ref, t); }
	export_ inline void interpolate(Var& result, const Var& a, const Var& b, float t) { Lerp::me().dispatch(result.m_ref, a.m_ref, b.m_ref, t); }
	export_ inline Var interpolate_cubic(const Var& a, const Var& b, const Var& d, const Var& e, float t) { UNUSED(e); UNUSED(d); return interpolate(a.m_ref, b.m_ref, t); }
}
