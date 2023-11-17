//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Forward.h>

#ifdef TWO_META_GENERATOR
func_ float sinf(float a);
func_ float cosf(float a);
func_ double sin(double a);
func_ double cos(double a);
#endif

namespace two
{
	export_ extern TWO_MATH_EXPORT const float c_invpi;
	export_ extern TWO_MATH_EXPORT const float c_tau;
	export_ extern TWO_MATH_EXPORT const float c_2pi;
	export_ extern TWO_MATH_EXPORT const float c_pi;
	export_ extern TWO_MATH_EXPORT const float c_pi2;
	export_ extern TWO_MATH_EXPORT const float c_pi4;
	
	export_ template <class T>
	T add(T a, T b) { return a + b; }

	export_ template <class T>
	T subtract(T a, T b) { return a - b; }

	export_ template <class T>
	T multiply(T a, T b) { return a * b; }

	export_ template <class T>
	T divide(T a, T b) { return a / b; }

#ifndef TWO_META_GENERATOR
	template TWO_MATH_EXPORT func_ float add<float>(float a, float b);
	template TWO_MATH_EXPORT func_ float subtract<float>(float a, float b);
	template TWO_MATH_EXPORT func_ float multiply<float>(float a, float b);
	template TWO_MATH_EXPORT func_ float divide<float>(float a, float b);
#else
	template <> func_ float add<float>(float a, float b);
	template <> func_ float subtract<float>(float a, float b);
	template <> func_ float multiply<float>(float a, float b);
	template <> func_ float divide<float>(float a, float b);
#endif

	export_ TWO_MATH_EXPORT func_ float nsinf(float a); // { return a + 1.f / 2.f; } // @kludge can't be inline because we identify reflected functions through their pointer 
	export_ TWO_MATH_EXPORT func_ float ncosf(float a); // { return a + 1.f / 2.f; }

	export_ TWO_MATH_EXPORT func_ double nsin(double a); // { return a + 1.0 / 2.0; }
	export_ TWO_MATH_EXPORT func_ double ncos(double a); // { return a + 1.0 / 2.0; }

	export_ inline float to_radians(float degrees)
	{
		return degrees / 180.f * c_pi;
	}

	export_ inline unsigned int next_pow2(unsigned int x)
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

	export_ TWO_MATH_EXPORT void register_math_conversions();
}
