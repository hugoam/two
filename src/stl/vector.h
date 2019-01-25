#pragma once
#include <infra/Config.h>

#ifndef MUD_NO_STL
#ifndef MUD_CPP_20
#include <vector>
#endif
namespace mud
{
	export_ using std::vector;
}
#else
#include <TINYSTL/vector.h>
namespace mud
{
	export_ using tinystl::vector;

	template<class It1, class It2, class Pr>
	inline bool equal(It1 first1, const It1 last1, It2 first2, Pr pred)
	{
		for(; first1 != last1; ++first1, (void)++first2)
			if(!pred(*first1, *first2))
			{
				return false;
			}
		return true;
	}

	template<class It1, class It2, class Pr>
	inline bool equal(It1 first1, const It1 last1, It2 first2, const It2 last2, Pr Pred)
	{
		for(;;)
		{
			if(first1 == last1)
				return first2 == last2;

			if(first2 == last2)
				return false;

			if(!Pred(*first1, *first2))
				return false;

			++first1;
			++first2;
		}
	}

	template<class It1, class It2>
	inline bool equal(It1 first1, const It1 last1, It2 first2, const It2 last2)
	{
		auto equal_to = [](auto&& left, auto&& right)
		{
			return static_cast<decltype(left) && >(left) == static_cast<decltype(right) && >(right);
		};
		return equal(first1, last1, first2, last2, equal_to);
	}

#if 0
	template<class It1, class It2, class Pr>
	inline bool equal_mem(const It1 first1, const It1 last1, const It2 first2)
	{
		const auto first1ch = reinterpret_cast<const char*>(first1);
		const auto first2ch = reinterpret_cast<const char*>(first2);
		const size_t count = static_cast<size_t>(reinterpret_cast<const char *>(last1) - first1ch);
		return memcmp(first1ch, first2ch, count) == 0;
	}
#endif

	template<class T, class Alloc>
	inline bool operator==(const vector<T, Alloc>& left, const vector<T, Alloc>& right)
	{
		auto equal_to = [](auto&& left, auto&& right)
		{
			return static_cast<decltype(left)&&>(left) == static_cast<decltype(right)&&>(right);
		};
		return left.size() == right.size() && equal(left.begin(), left.end(), right.begin(), equal_to);
	}

}
#endif
