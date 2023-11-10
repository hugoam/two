//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/vector.h>
#include <infra/Config.h>

namespace two
{
#ifndef USE_STL
	template <class T>
	class reverse_pointer
	{
	public:
		using pointer = T*;
		using reference = T&;

		reverse_pointer() : m_ptr() {}
		explicit reverse_pointer(T* other) : m_ptr(other) {}

		reference operator*() const
		{
			T* temp = m_ptr;
			return *--temp;
		}

		pointer operator->() const
		{
			T* temp = m_ptr;
			--temp;
			return temp;
		}

		reverse_pointer& operator++() { --m_ptr; return *this; }
		reverse_pointer operator++(int) { reverse_pointer temp = *this; --m_ptr; return temp; }

		reverse_pointer& operator--() { ++m_ptr; return *this; }
		reverse_pointer operator--(int) { reverse_pointer temp = *this; ++m_ptr; return temp; }

		reverse_pointer& operator+=(size_t offset) { m_ptr -= offset; return *this; }
		reverse_pointer& operator-=(size_t offset) { m_ptr += offset; return *this; }
		reverse_pointer operator+(size_t offset) const { return reverse_pointer(m_ptr - offset); }
		reverse_pointer operator-(size_t offset) const { return reverse_pointer(m_ptr + offset); }

		reference operator[](size_t offset) const { return *(*this + offset); }

		T* m_ptr;
	};

	template <class T1, class T2>
	bool operator==(const reverse_pointer<T1>& left, const reverse_pointer<T2>& right) { return left.m_ptr == right.m_ptr; }

	template <class T1, class T2>
	bool operator!=(const reverse_pointer<T1>& left, const reverse_pointer<T2>& right) { return !(left == right); }

	template <class T1, class T2>
	bool operator<(const reverse_pointer<T1>& left, const reverse_pointer<T2>& right) { return right.m_ptr < left.m_ptr; }

	template <class T1, class T2>
	bool operator>(const reverse_pointer<T1>& left, const reverse_pointer<T2>& right) { return right < left; }

	template <class T1, class T2>
	bool operator<=(const reverse_pointer<T1>& left, const reverse_pointer<T2>& right) { return !(right < left); }

	template <class T1, class T2>
	bool operator>=(const reverse_pointer<T1>& left, const reverse_pointer<T2>& right) { return !(left < right); }
#endif

	export_ template <class T>
	class reverse_adapter
	{
	public:
		reverse_adapter(T& container) : m_container(container) { }
		reverse_adapter& operator=(const reverse_adapter&) = delete;

#ifndef USE_STL
		using iterator = reverse_pointer<typename T::value_type>;
		iterator begin() { return iterator(m_container.end()); }
		iterator end() { return iterator(m_container.begin()); }
#else
		typename T::reverse_iterator begin() { return m_container.rbegin(); }
		typename T::reverse_iterator end() { return m_container.rend(); }
#endif
	private:
		T& m_container;
	};

	export_ template <class T>
	reverse_adapter<T> reverse_adapt(T& container) { return reverse_adapter<T>(container); }
}
