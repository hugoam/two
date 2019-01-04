//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <infra/Config.h>

#ifndef MUD_CPP_20
#include <cstdint>
#include <cstring>
#include <cassert>
#endif

namespace mud
{
	using cstring = const char*;

	template <typename T>
	struct array;

	export_ template <class T, size_t Size>
	struct carray
	{
		template <class... T_Args>
		carray(T_Args... args) : m_array{ T(args)... } {}
		T m_array[Size];
		size_t size() { return Size; }
		T* data() { return m_array; }
		T& operator[](size_t at) { return m_array[at]; }
		const T& operator[](size_t at) const { return m_array[at]; }
		operator array<T>() { return{ m_array, Size }; }
	};

	template <class... T_Args, size_t size = sizeof...(T_Args)>
	carray<cstring, size> cstrarray(T_Args... args) { return carray<cstring, size>{ args... }; }

	template <class... T_Args, size_t size = sizeof...(T_Args)>
	carray<cstring, size> strarray(T_Args... args) { return carray<cstring, size>{ args.c_str()... }; }

	export_ template <typename T>
	struct refl_ struct_ array
	{
	public:
		array() : m_pointer(nullptr), m_count(0) {}
		array(T* pointer, size_t count) : m_pointer(pointer), m_count(count) {}
		array(array<T> other, size_t offset) : m_pointer(other.m_pointer + offset), m_count(other.m_count - offset) {}
		array(array<T> other, size_t offset, size_t count) : m_pointer(other.m_pointer + offset), m_count(count) {}
		template <class U>
		array(U& container) : m_pointer(container.data()), m_count(container.size()) {}

		size_t size() { return m_count; }
		T* data() const { return m_pointer; }

		T& operator[](size_t at) { assert(at < m_count); return m_pointer[at]; }
		const T& operator[](size_t at) const { assert(at < m_count); return m_pointer[at]; }

		T* begin() { return m_pointer; }
		T* end() { return m_pointer + m_count; }
		const T* begin() const { return m_pointer; }
		const T* end() const { return m_pointer + m_count; }

		void copy(array<T> dest) { memcpy(dest.m_pointer, m_pointer, sizeof(T) * m_count); }
		void copy(void* dest) { memcpy(dest, m_pointer, sizeof(T) * m_count); }

		T* m_pointer;
		size_t m_count;
	};

	export_ template<typename T> class array_2d : public array<T>
	{
	public:
		array_2d(T* pointer, size_t size_x, size_t size_y) : array<T>(pointer, size_x * size_y), m_size_x(size_x), m_size_y(size_y) {}
		
		size_t m_size_x;
		size_t m_size_y;

		inline T& at(size_t x, size_t y) { return (*this)[x+y*m_size_x]; }
		inline const T& at(size_t x, size_t y) const { return (*this)[x+y*m_size_x]; }
	};

#if 0
	// quicksort implementation for sorting multiple arrays at once
	template <class T, class... T_Arrays>
	void quicksort(array<T> keys, const size_t left, const size_t right, T_Arrays... arrays)
	{
		auto partition = [](array<T> keys, const size_t left, const size_t right, T_Arrays... arrays)
		{
			const size_t mid = left + (right - left) / 2;
			const T pivot = keys[mid];
			// move the mid point value to the front.
			std::swap(keys[mid], keys[left]);
			swallow{ (std::swap(arrays[mid], arrays[left]), 1)... };
			size_t i = left + 1;
			size_t j = right;
			while(i <= j)
			{
				while(i <= j && keys[i] <= pivot)
					i++;

				while(i <= j && keys[j] > pivot)
					j--;

				if(i < j)
					std::swap(keys[i], keys[j]);
			}
			std::swap(keys[i - 1], keys[left]);
			swallow{ (std::swap(arrays[i - 1], arrays[left]), 1)... };
			return i - 1;
		};

		if(left >= right)
			return;

		size_t part = partition(keys, left, right);
		quicksort(keys, left, part - 1, arrays...);
		quicksort(keys, part + 1, right, arrays...);
	}

	template <class T, class... T_Arrays>
	void quicksort(array<T> keys, T_Arrays... arrays)
	{
		quicksort(keys, 0, keys.size() - 1, arrays...);
	}
#endif
}
