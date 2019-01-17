//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/vector.h>
#include <infra/Config.h>

#ifdef MUD_VECTOR_TINYSTL
#include <iterator>
#endif

namespace mud
{
	export_ template<typename T>
	class reverse_adapter
	{
	public:
		reverse_adapter(T& container) : m_container(container) { }
		reverse_adapter& operator=(const reverse_adapter&) = delete;

#ifdef MUD_VECTOR_TINYSTL
		using iterator = std::reverse_iterator<typename T::iterator>;
		iterator begin() { return iterator(m_container.end()); }
		iterator end() { return iterator(m_container.begin()); }
#else
		typename T::reverse_iterator begin() { return m_container.rbegin(); }
		typename T::reverse_iterator end() { return m_container.rend(); }
#endif
	private:
		T& m_container;
	};

	export_ template<typename T>
	reverse_adapter<T> reverse_adapt(T& container) { return reverse_adapter<T>(container); }
}
