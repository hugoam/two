//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Forward.h>
#include <math/Vec.h>
#include <math/Colour.h>

namespace two
{
	export_ template <class T>
	struct refl_ struct_ Range
	{
		Range() {}
		Range(T min, T max) : m_min(min), m_max(max) {}
		attr_ T m_min = {};
		attr_ T m_max = {};
		bool operator==(const Range<T>& other) const { return m_min == other.m_min && m_max == other.m_max; }
	};

	export_ extern template struct refl_ Range<vec3>;
	export_ extern template struct refl_ Range<quat>;
	export_ extern template struct refl_ Range<float>;
	export_ extern template struct refl_ Range<uint32_t>;
	export_ extern template struct refl_ Range<Colour>;
}
