#pragma once

#ifdef USE_STL
#include <vector>
namespace stl = std;
#else
#include <stl/initializer_list.h>

#include <stl/allocator.h>
#include <stl/buffer.h>
#include <stl/stddef.h>

#define USE_UVECTOR

#ifdef USE_UVECTOR
#include <stl/ubuffer.h>
#endif

namespace stl {

#ifdef USE_UVECTOR
	template <class T, class Alloc = TINYSTL_ALLOCATOR>
	using vector = uvector<T>;
#elif defined USE_BUFFER
	template <class T, class Alloc = TINYSTL_ALLOCATOR>
	using vector = buffer<T>;
#else
	template <class T, class Alloc = TINYSTL_ALLOCATOR>
	class vector : public buffer<T, Alloc> {
	public:
		using buffer<T, Alloc>::buffer;

		using value_type = T;
		using pointer = T*;
		using iterator = T*;
		using const_iterator = const T*;

		void assign(const T* first, const T* last);

		iterator insert(iterator where);
		iterator insert(iterator where, const T& value);
		iterator insert(iterator where, T&& value);
		iterator insert(iterator where, const T* first, const T* last);

		template <class... Params>
		void emplace(iterator where, Params&&... params);

		iterator erase(iterator where);
		iterator erase(iterator first, iterator last);

		iterator erase_unordered(iterator where);
		iterator erase_unordered(iterator first, iterator last);
	};
#endif
}
#endif

namespace mud
{
	using stl::vector;

	template <class It1, class It2, class Pr>
	inline bool equal(It1 first1, const It1 last1, It2 first2, Pr pred)
	{
		for (; first1 != last1; ++first1, (void)++first2)
			if (!pred(*first1, *first2))
			{
				return false;
			}
		return true;
	}

	template <class It1, class It2, class Pr>
	inline bool equal(It1 first1, const It1 last1, It2 first2, const It2 last2, Pr Pred)
	{
		for (;;)
		{
			if (first1 == last1)
				return first2 == last2;

			if (first2 == last2)
				return false;

			if (!Pred(*first1, *first2))
				return false;

			++first1;
			++first2;
		}
	}

	template <class It1, class It2>
	inline bool equal(It1 first1, const It1 last1, It2 first2, const It2 last2)
	{
		auto equal_to = [](auto&& left, auto&& right)
		{
			return static_cast<decltype(left) && >(left) == static_cast<decltype(right) && >(right);
		};
		return equal(first1, last1, first2, last2, equal_to);
	}

#if 0
	template <class It1, class It2, class Pr>
	inline bool equal_mem(const It1 first1, const It1 last1, const It2 first2)
	{
		const auto first1ch = reinterpret_cast<const char*>(first1);
		const auto first2ch = reinterpret_cast<const char*>(first2);
		const size_t count = static_cast<size_t>(reinterpret_cast<const char *>(last1) - first1ch);
		return memcmp(first1ch, first2ch, count) == 0;
	}
#endif

	template <class T, class Alloc>
	inline bool operator==(const vector<T, Alloc>& left, const vector<T, Alloc>& right)
	{
		auto equal_to = [](auto&& left, auto&& right)
		{
			return static_cast<decltype(left) && >(left) == static_cast<decltype(right) && >(right);
		};
		return left.size() == right.size() && equal(left.begin(), left.end(), right.begin(), equal_to);
	}
}
