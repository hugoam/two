//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_CPP_20
#include <functional>
#endif

#ifndef MUD_CPP_20
#include <infra/Config.h>

namespace mud
{
	export_ template<class T, class Compare>
	constexpr const T& clamp(const T& v, const T& lo, const T& hi, Compare comp)
	{
		return comp(v, lo) ? lo : comp(hi, v) ? hi : v;
	}

	export_ template<class T>
	constexpr const T& clamp(const T& v, const T& lo, const T& hi)
	{
		return clamp(v, lo, hi, std::less<>());
	}
}
#endif
