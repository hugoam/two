//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <infra/Config.h>

#include <stdint.h>
#include <cmath>
#include <cstdlib>

namespace stl
{
	using std::abs;
	using std::floor;
	using std::ceil;
	using std::sin;
	using std::cos;
	using std::pow;
	using std::log2;
	using std::isnan;
	using std::isinf;

	template <class T>
	inline constexpr T sq(T val) { return val * val; }

	template <class T>
	inline constexpr T sign(T val) { return T(T(0) < val) - (val < T(0)); }

	template <class T>
	inline constexpr T min(T a, T b) { return (b < a) ? b : a; }

	template <class T>
	inline constexpr T max(T a, T b) { return (a < b) ? b : a; }

	template <class T>
	inline constexpr T clamp(T v, T lo, T hi) { return min(max(v, lo), hi); }
}

namespace mud
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