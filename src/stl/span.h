//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <infra/Config.h>
#include <stl/stddef.h>
#include <stl/initializer_list.h>

namespace stl
{
	export_ template <class T>
	struct refl_ struct_ seque_ span
	{
	public:
		span() : m_pointer(nullptr), m_count(0) {}
		span(T* pointer, size_t count) : m_pointer(pointer), m_count(count) {}
		span(std::initializer_list<T> l) : m_pointer(const_cast<T*>(l.begin())), m_count(l.size()) {}
		span(span<T> other, size_t offset) : m_pointer(other.m_pointer + offset), m_count(other.m_count - offset) {}
		span(span<T> other, size_t offset, size_t count) : m_pointer(other.m_pointer + offset), m_count(count) {}
		template <size_t size>
		span(T(&a)[size]) : m_pointer(a), m_count(size) {}
		template <class U>
		span(U& container) : m_pointer(container.data()), m_count(container.size()) {}
		template <class U>
		span(U& container, size_t offset) : m_pointer(container.data() + offset), m_count(container.size() - offset) {}
		template <class U>
		span(U& container, size_t offset, size_t count) : m_pointer(container.data() + offset), m_count(count) {}

		size_t size() const { return m_count; }
		bool empty() const { return m_count == 0; }
		T* data() const { return m_pointer; }

		//T& operator[](size_t at) { assert(at < m_count); return m_pointer[at]; }
		//const T& operator[](size_t at) const { assert(at < m_count); return m_pointer[at]; }

		T& operator[](size_t at) { return m_pointer[at]; }
		const T& operator[](size_t at) const { return m_pointer[at]; }

		T* begin() { return m_pointer; }
		T* end() { return m_pointer + m_count; }
		const T* begin() const { return m_pointer; }
		const T* end() const { return m_pointer + m_count; }

		T* m_pointer;
		size_t m_count;
	};

	export_ template <class T>
	class span2d : public span<T>
	{
	public:
		span2d(T* pointer, size_t size_x, size_t size_y) : span<T>(pointer, size_x * size_y), m_x(size_x), m_y(size_y) {}
		
		size_t m_x;
		size_t m_y;

		inline T& at(size_t x, size_t y) { return (*this)[x+y*m_x]; }
		inline const T& at(size_t x, size_t y) const { return (*this)[x+y*m_x]; }
	};
}

namespace mud
{
	using stl::span;
	using stl::span2d;
}