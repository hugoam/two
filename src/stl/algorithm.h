#pragma once
#include <infra/Config.h>

//#define MUD_ALGORITHM_STL
#ifdef MUD_ALGORITHM_STL
#ifndef MUD_CPP_20
#include <algorithm>
#endif
namespace mud
{
	using std::swap;
	using std::find;
	using std::find_if;
	using std::includes;
	using std::remove;
	using std::remove_if;
	using std::transform;
	using std::reverse;
}
#else
#include <TINYSTL/vector.h>
#include <stl/swap.h>
namespace mud
{
	template<class It, class T>
	inline It find_char(It first, const It last, const T& val)
	{
		//if(!_Within_limits(first, val))
		//	return last;
		first = static_cast<It>(memchr(first, static_cast<unsigned char>(val), static_cast<size_t>(last - first)));
		return first ? first : last;
	}

	template<class It, class T>
	inline It find(It first, const It last, const T& val)
	{
		for(; first != last; ++first)
			if(*first == val)
				break;
		return first;
	}

	template<class It, class Pr>
	inline It find_if(It first, const It last, Pr pred)
	{
		for(; first != last; ++first)
			if(pred(*first))
				break;
		return first;
	}

	template<class It, class Pred>
	inline It remove_if(It first, const It last, Pred pred)
	{
		first = find_if(first, last, pred);
		It next = first;
		if(first != last)
		{
			while(++first != last)
			{
				if(!pred(*first))
				{
					*next = move(*first);
					++next;
				}
			}
		}
		return first;
	}

	template<class It, class T>
	inline It remove(It first, const It last, const T& val)
	{
		It next = first;
		if(first != last)
		{
			while(++first != last)
			{
				if(!(*first == val))
				{
					*next = move(*first);
					++next;
				}
			}
		}
		return first;
	}

	template<class InIt, class OutIt, class Fn>
	inline OutIt transform(InIt first, const InIt last, OutIt dest, Fn func)
	{
		for(; first != last; ++first, (void)++dest)
		{
			*dest = func(*first);
		}
		return dest;
	}

	template<class It1, class It2, class Pr>
	inline bool includes(It1 first1, It1 last1, It2 first2, It2 last2, Pr pred)
	{
		for(; first1 != last1 && first2 != last2; ++first1)
		{
			if(pred(*first2, *first1))
				return (false);

			if(!pred(*first1, *first2))
				++first2;
		}
		return first2 == last2;
	}

	template<class It1, class It2>
	inline bool includes(It1 first1, It1 last1, It2 first2, It2 last2)
	{
		auto less = [](auto&& left, auto&& right)
		{
			return static_cast<decltype(left)&&>(left) < static_cast<decltype(right)&&>(right);
		};
		return includes(first1, last1, first2, last2, less);
	}

	template<class It>
	inline void reverse(It first, It last)
	{
		for(; first != last && first != --last; ++first)
		{
			swap(*first, *last);
		}
	}
}
#endif
