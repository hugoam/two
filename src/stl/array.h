//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <infra/Config.h>
#include <stl/span.h>
#include <stl/stddef.h>

namespace stl
{
	export_ template<typename T, size_t N>
	constexpr size_t array_size(T(&a)[N]) { UNUSED(a); return N; }

	export_ template <class T, size_t Size>
	struct array
	{
		T m_array[Size];
		size_t size() { return Size; }
		T* data() { return m_array; }
		T& operator[](size_t at) { return m_array[at]; }
		const T& operator[](size_t at) const { return m_array[at]; }
		operator span<T>() { return{ m_array, Size }; }
	};
}

namespace two
{
	export_ using stl::array_size;
	export_ using stl::array;
}
