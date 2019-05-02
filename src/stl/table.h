//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <infra/Config.h>
#include <cstddef>

namespace two
{
	export_ template <class Enum, class T, size_t Size = size_t(Enum::Count)>
	struct table
	{
		T m_values[Size] = {};
		size_t size() { return Size; }
		T* data() { return m_values; }
		const T& operator[](Enum e) const { return m_values[size_t(e)]; }
		T& operator[](Enum e) { return m_values[size_t(e)]; }
		using array = T[Size];
		operator const array&() { return m_values; }
	};
}
