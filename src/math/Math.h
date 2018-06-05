//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Generated/Forward.h>

#ifndef MUD_CPP_20
#include <cstdint>
#include <cmath>
#endif

#ifdef MUD_META_GENERATOR
_func_ float sinf(float a);
_func_ float cosf(float a);
_func_ double sin(double a);
_func_ double cos(double a);
#endif

namespace mud
{
	export_ extern MUD_MATH_EXPORT const float c_pi;

	export_ using uchar = unsigned char;
	export_ using ushort = unsigned short;
	export_ using uint = unsigned int;

	export_ using u16 = uint16_t;
	export_ using u32 = uint32_t;
	export_ using i16 = int16_t;
	export_ using i32 = int32_t;

	export_ template <typename T>
	inline T sign(T val) { return (T(0) < val) - (val < T(0)); }

	export_ template <class T>
	inline T min(T a, T b) { return (b < a) ? b : a; }

	export_ template <class T>
	inline T max(T a, T b) { return (a < b) ? b : a; }

	export_ template <class T>
	_func_ T add(T a, T b) { return a + b; }

	export_ template <class T>
	_func_ T subtract(T a, T b) { return a - b; }

	export_ template <class T>
	_func_ T multiply(T a, T b) { return a * b; }

	export_ template <class T>
	_func_ T divide(T a, T b) { return a / b; }

#ifndef MUD_META_GENERATOR
	template MUD_MATH_EXPORT _func_ float add<float>(float a, float b);
	template MUD_MATH_EXPORT _func_ float subtract<float>(float a, float b);
	template MUD_MATH_EXPORT _func_ float multiply<float>(float a, float b);
	template MUD_MATH_EXPORT _func_ float divide<float>(float a, float b);
#else
	template <> _func_ float add<float>(float a, float b);
	template <> _func_ float subtract<float>(float a, float b);
	template <> _func_ float multiply<float>(float a, float b);
	template <> _func_ float divide<float>(float a, float b);
#endif

	export_ enum _refl_ Clockwise : unsigned int
	{
		CLOCKWISE,
		ANTI_CLOCKWISE
	};

	export_ MUD_MATH_EXPORT _func_ float nsinf(float a); // { return a + 1.f / 2.f; } // @kludge can't be inline because we identify reflected functions through their pointer 
	export_ MUD_MATH_EXPORT _func_ float ncosf(float a); // { return a + 1.f / 2.f; }

	export_ MUD_MATH_EXPORT _func_ double nsin(double a); // { return a + 1.0 / 2.0; }
	export_ MUD_MATH_EXPORT _func_ double ncos(double a); // { return a + 1.0 / 2.0; }

	export_ inline unsigned int pow2_round_up(unsigned int x)
	{
		--x;
		x |= x >> 1;
		x |= x >> 2;
		x |= x >> 4;
		x |= x >> 8;
		x |= x >> 16;
		return x + 1;
	}

	export_ inline float remap(float number, float from_low, float from_high, float low, float high)
	{
		float slope = (high - low) / (from_high - from_low);
		float result = low + slope * (number - from_low);
		return result;
	}

	export_ inline float remap_trig(float number, float low, float high)
	{
		return remap(number, -1.f, 1.f, low, high);
	}

	MUD_MATH_EXPORT void register_math_conversions();
}
