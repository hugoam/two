#pragma once
#include <infra/Config.h>

#ifdef USE_STL
#include <algorithm>
namespace stl
{
	using std::move;
	using std::swap;
	using std::find;
	using std::find_if;
	using std::equal;
	using std::includes;
	using std::remove;
	using std::remove_if;
	using std::transform;
	using std::reverse;
}
#else
#include <stl/vector.h>
#include <stl/swap.h>
namespace stl
{
	template <class It, class T>
	inline It find_char(It first, const It last, const T& val)
	{
		//if(!_Within_limits(first, val))
		//	return last;
		first = static_cast<It>(memchr(first, static_cast<unsigned char>(val), static_cast<size_t>(last - first)));
		return first ? first : last;
	}

	template <class It, class T>
	inline It find(It first, const It last, const T& val)
	{
		for(; first != last; ++first)
			if(*first == val)
				break;
		return first;
	}

	template <class It, class Pr>
	inline It find_if(It first, const It last, Pr pred)
	{
		for(; first != last; ++first)
			if(pred(*first))
				break;
		return first;
	}

	template <class It, class Pred>
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
		first = next;
		return first;
	}

	template <class It, class T>
	inline It remove(It first, const It last, const T& val)
	{
		first = find(first, last, val);
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
		first = next;
		return first;
	}

	template <class InIt, class OutIt, class Fn>
	inline OutIt transform(InIt first, const InIt last, OutIt dest, Fn func)
	{
		for(; first != last; ++first, (void)++dest)
		{
			*dest = func(*first);
		}
		return dest;
	}

	template <class It1, class It2, class Pr>
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

	template <class It1, class It2>
	inline bool includes(It1 first1, It1 last1, It2 first2, It2 last2)
	{
		auto less = [](auto&& left, auto&& right)
		{
			return static_cast<decltype(left)&&>(left) < static_cast<decltype(right)&&>(right);
		};
		return includes(first1, last1, first2, last2, less);
	}

	template <class It1, class It2, class Pr>
	inline bool equal(It1 first1, const It1 last1, It2 first2, Pr pred)
	{
		for(; first1 != last1; ++first1, (void)++first2)
			if(!pred(*first1, *first2))
			{
				return false;
			}
		return true;
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

	template <class It1, class It2, class Pr>
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

	template <class It1, class It2>
	inline bool equal(It1 first1, const It1 last1, It2 first2, const It2 last2)
	{
		auto equal_to = [](auto&& left, auto&& right)
		{
			return static_cast<decltype(left) && >(left) == static_cast<decltype(right) && >(right);
		};
		return equal(first1, last1, first2, last2, equal_to);
	}

	template <class It>
	inline void reverse(It first, It last)
	{
		for(; first != last && first != --last; ++first)
		{
			swap(*first, *last);
		}
	}
}
#endif

namespace stl
{
	export_ template <class U, class T>
	inline bool has(const T& vec, const U& value)
	{
		return find(vec.begin(), vec.end(), value) != vec.end();
	}

	export_ template <class T, class Pred>
	inline bool has_pred(const T& vec, Pred predicate)
	{
		return find_if(vec.begin(), vec.end(), predicate) != vec.end();
	}
	
	export_ template <class T, class Pred>
	inline const typename T::value_type* find(const T& vec, Pred predicate)
	{
		auto it = find_if(vec.begin(), vec.end(), predicate);
		return it != vec.end() ? &(*it) : nullptr;
	}
	
	export_ template <class T, class U>
	inline size_t index_of(const T& vec, U value)
	{
		return find(vec.begin(), vec.end(), value) - vec.begin();
	}

	export_ template <class T, class Pred>
	inline auto find_if(T& vec, Pred predicate)
	{
		return find_if(vec.begin(), vec.end(), predicate);
	}
	
	export_ template <class T, class Pred>
	inline auto find_if(const T& vec, Pred predicate)
	{
		return find_if(vec.begin(), vec.end(), predicate);
	}
	
	export_ template <class T, class Pred>
	inline auto in(T& vec, Pred predicate)
	{
		auto result = find_if(vec.begin(), vec.end(), predicate);
		return result == vec.end() ? *result : nullptr;
	}
	
	export_ template <class T, class Pred>
	inline auto in(const T& vec, Pred predicate)
	{
		auto result = find_if(vec.begin(), vec.end(), predicate);
		return result == vec.end() ? *result : nullptr;
	}

	export_ template <class T>
	inline bool contains(const T& vec, const T& other)
	{
		return includes(vec.begin(), vec.end(), other.begin(), other.end());
	}
	
	export_ template <class T>
	inline T reverse(const T& vec)
	{
		T result = vec;
		reverse(result.begin(), result.end());
		return result;
	}
	
	export_ template <class T, class... Args>
	inline auto& push(T& vec, Args&&... args)
	{
		vec.emplace_back(static_cast<Args&&>(args)...);
		return vec.back();
	}
	
	export_ template <class T, class U>
	inline void add(T& vec, U value)
	{
		if(!has(vec, value))
			vec.push_back(value);
	}

	export_ template <class T>
	inline typename T::value_type pop(T& vec)
	{
		auto val = move(vec.back());
		vec.pop_back();
		return val;
	}

	export_ template <class T>
	inline void swap_pop(T& vec, size_t index)
	{
		swap(vec[index], vec.back());
		vec.pop_back();
	}

	export_ template <class T>
	inline void extend(T& vec, const T& other)
	{
		vec.insert(vec.end(), other.begin(), other.end());
	}
	
	export_ template <class T, class U>
	inline void extend(T& vec, const U& other)
	{
		vec.insert(vec.end(), other.begin(), other.end());
	}

	export_ template <class T>
	inline T merge(const T& first, const T& second)
	{
		T result; extend(result, first); extend(result, second); return result;
	}

	//export_ template <class T, class U>
	//inline void prepend(T& vec, const U& value)
	//{
	//	vec.insert(vec.begin(), value);
	//}

	export_ template <class T, class U>
	inline void prepend(T& vec, const U& other)
	{
		vec.insert(vec.begin(), other.begin(), other.end());
	}

	export_ template <class T>
	inline void prepend(T& vec, const T& other)
	{
		vec.insert(vec.begin(), other.begin(), other.end());
	}

	export_ template <class T, class U>
	inline void remove(T& vec, U value)
	{
		vec.erase(remove(vec.begin(), vec.end(), value), vec.end());
	}
	
	export_ template <class T, class U>
	inline void remove_ref(T& vec, U& value)
	{
		size_t index = &value - vec.data();
		vec.erase(vec.begin() + index);
	}
	
	export_ template <class T, class U>
	inline void remove_object(T& vec, U& object)
	{
		auto pos = find_if(vec.begin(), vec.end(), [&](const U& look) { return &look == &object; });
		vec.erase(pos);
	}

	export_ template <class T, class V>
	inline auto remove_pt(T& vec, V& value)
	{
		auto pos = find_if(vec.begin(), vec.end(), [&](auto& pt) { return pt.get() == &value; });
		vec.erase(pos);
	}

	export_ template <class T, class Pred>
	inline auto remove_if(T& vec, Pred predicate)
	{
		return vec.erase(remove_if(vec.begin(), vec.end(), predicate), vec.end());
	}
	
	export_ template <class T, class Pred>
	inline void prune(T& vec, Pred predicate)
	{
		for(int i = int(vec.size()) - 1; i >= 0; i--)
			if(predicate(vec[i]))
				vec.erase(vec.begin() + i);
	}

	export_ template <class T, class U>
	inline void select(T& vec, U value) { vec.clear(); vec.push_back(value); }

	export_ template <class T, class U>
	inline bool select_swap(T& vec, U value) { if(has(vec, value)) { remove(vec, value); return false; } else { add(vec, value); return true; } }
	
	export_ template <class T, class U>
	inline auto transfer_unique(T& source, T& target, U& value)
	{
		auto pos = find_if(source.begin(), source.end(), [&](auto& pt) { return pt.get() == &value; });
		target.push_back(move(*pos));
		source.erase(pos);
	}
}

namespace mud
{
	using stl::move;
	//using stl::swap;
	using stl::find;
	using stl::find_if;
	using stl::includes;
	using stl::remove;
	using stl::remove_if;
	using stl::transform;
	using stl::reverse;
	using stl::has;
	using stl::has_pred;
	using stl::find;
	using stl::index_of;
	using stl::find_if;
	//using stl::in;
	using stl::equal;
	using stl::contains;
	using stl::reverse;
	using stl::push;
	using stl::add;
	using stl::pop;
	using stl::swap_pop;
	using stl::extend;
	using stl::merge;
	using stl::prepend;
	using stl::remove;
	using stl::remove_ref;
	using stl::remove_object;
	using stl::remove_pt;
	using stl::remove_if;
	using stl::prune;
	using stl::select;
	using stl::select_swap;
	using stl::transfer_unique;
}