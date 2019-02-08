//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <infra/Config.h>
#include <stl/span.h>
#include <stl/stddef.h>

namespace stl
{
	template <class T>
	struct span;

	export_ template <class T, size_t Size>
	struct array
	{
		//template <class... Args>
		//span(Args... args) : m_array{ T(args)... } {}
		T m_array[Size];
		size_t size() { return Size; }
		T* data() { return m_array; }
		T& operator[](size_t at) { return m_array[at]; }
		const T& operator[](size_t at) const { return m_array[at]; }
		operator span<T>() { return{ m_array, Size }; }
	};
}

namespace mud
{
	using stl::array;
}
