//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <infra/Config.h>

#include <stdint.h>
#ifndef TWO_STD_MODULES
#include <cmath>
#include <cstdlib>
#endif

namespace stl
{
	export_ using std::abs;
	export_ using std::floor;
	export_ using std::ceil;
	export_ using std::sin;
	export_ using std::cos;
	export_ using std::pow;
	export_ using std::log2;
	export_ using std::isnan;
	export_ using std::isinf;

	export_ template <class T>
	inline constexpr T sq(T val) { return val * val; }

	export_ template <class T>
	inline constexpr T sign(T val) { return T(T(0) < val) - (val < T(0)); }

	export_ template <class T>
	inline constexpr T min(T a, T b) { return (b < a) ? b : a; }

	export_ template <class T>
	inline constexpr T max(T a, T b) { return (a < b) ? b : a; }

	export_ template <class T>
	inline constexpr T clamp(T v, T lo, T hi) { return min(max(v, lo), hi); }
}

namespace two
{
	export_ using stl::sq;
	export_ using stl::sign;
	export_ using stl::min;
	export_ using stl::max;
	export_ using stl::clamp;
	export_ using stl::isinf;
	export_ using stl::abs;
	export_ using stl::floor;
	export_ using stl::ceil;
	export_ using stl::sin;
	export_ using stl::cos;
	export_ using stl::pow;
	export_ using stl::log2;
	export_ using stl::isnan;
	export_ using stl::isinf;
}
