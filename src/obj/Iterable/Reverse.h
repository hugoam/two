//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

namespace mud
{
	template<typename T> class reverse_adapter
	{
	public:
		reverse_adapter(T& container) : m_container(container) { }
		reverse_adapter& operator=(const reverse_adapter&) = delete;
		typename T::reverse_iterator begin() { return m_container.rbegin(); }
		typename T::reverse_iterator end() { return m_container.rend(); }
	private:
		T& m_container;
	};

	template<typename T> reverse_adapter<T> reverse_adapt(T& container) { return reverse_adapter<T>(container); }
}
