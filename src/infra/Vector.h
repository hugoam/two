//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/vector.h>
#include <stl/algorithm.h>
#include <infra/Config.h>
#include <infra/Array.h>
#include <infra/TypeTraits.h>

namespace mud
{
	template <class T>
	constexpr bool is_comparable<vector<T>> = is_comparable<T>;

	export_ template <class T>
	array<T> to_array(vector<T>& vec) { return { &vec[0], vec.size() }; }
	export_ template <class T>
	array<T> to_array(vector<T>& vec, size_t offset) { return { &vec[offset], vec.size() - offset }; }
	export_ template <class T>
	array<T> to_array(vector<T>& vec, size_t offset, size_t count) { return { &vec[offset], count }; }

	template <class T, class U>
	array<T> to_array_cast(vector<U>& vec) { return{ (T*)&vec[0], vec.size() }; }

	export_ template <class T>
	vector<T> to_vector(const array<T>& array) { return { array.m_pointer, array.m_pointer + array.m_count }; }

	export_ template <class T>
	inline void vector_extend(vector<T>& vec, const vector<T>& other)
	{
		vec.insert(vec.end(), other.begin(), other.end());
	}
	
	export_ template <class T>
	inline void vector_prepend(vector<T>& vec, const T& value)
	{
		vec.insert(vec.begin(), value);
	}

	export_ template <class T>
	inline void vector_prepend(vector<T>& vec, const vector<T>& other)
	{
		vec.insert(vec.begin(), other.begin(), other.end());
	}

	export_ template <class T>
	inline vector<T> vector_union(const vector<T>& first, const vector<T>& second)
	{
		vector<T> result; vector_extend(result, first); vector_extend(result, second); return result;
	}

	export_ template <class T, class... T_Args>
	inline T& vector_push(vector<T>& vec, T_Args&&... args)
	{
		vec.emplace_back(static_cast<T_Args&&>(args)...);
		return vec.back();
	}

	export_ template <class T>
	inline T pop(vector<T>& vec)
	{
		T val = move(vec.back());
		vec.pop_back();
		return val;
	}

	export_ template <class T>
	inline void swap_pop(vector<T>& vec, size_t index)
	{
		swap(vec[index], vec.back());
		vec.pop_back();
	}

	export_ template <class T, class U>
	inline void vector_cast(const vector<T>& source, vector<U>& target)
	{
		target.reserve(source.size());
		for(const T& val : source)
			target.push_back(static_cast<U>(val));
	}

	export_ template <class U, class T>
	inline vector<U> vector_convert(const vector<T>& source)
	{
		vector<U> target;
		vector_cast(source, target);
		return target;
	}

	export_ template <class U, class T, class Op>
	inline vector<U> vector_convert(const vector<T>& source, Op op)
	{
		vector<U> result;
		result.resize(source.size());
		transform(source.begin(), source.end(), result.begin(), op);
		return result;
	}

	export_ template <class T>
	inline void vector_remove(vector<T>& vec, T value)
	{
		vec.erase(remove(vec.begin(), vec.end(), value), vec.end());
	}

	export_ template <class T>
	inline void vector_remove_ref(vector<T>& vec, T& value)
	{
		size_t index = &value - vec.data();
		vec.erase(vec.begin() + index);
	}

	export_ template <class T, class Pred>
	inline auto vector_remove_if(vector<T>& vec, Pred predicate)
	{
		return vec.erase(remove_if(vec.begin(), vec.end(), predicate), vec.end());
	}

	export_ template <class T, class Pred>
	inline void vector_prune(vector<T>& vec, Pred predicate)
	{
		for(int i = int(vec.size()) - 1; i >= 0; i--)
			if(predicate(vec[i]))
				vec.erase(vec.begin() + i);
	}

	export_ template <class T>
	inline size_t vector_index(const vector<T>& vec, T value)
	{
		return find(vec.begin(), vec.end(), value) - vec.begin();
	}
	
	export_ template <class T>
	inline size_t array_index(array<T> vec, T value)
	{
		return find(vec.begin(), vec.end(), value) - vec.begin();
	}

	export_ template <class T>
	inline bool vector_has(const vector<T>& vec, T value)
	{
		return find(vec.begin(), vec.end(), value) != vec.end();
	}

	export_ template <class T, class Pred>
	inline bool has_pred(const T& vec, Pred predicate)
	{
		return find_if(vec.begin(), vec.end(), predicate) != vec.end();
	}

	export_ template <class T, class Pred>
	inline const T* vector_find(const vector<T>& vec, Pred predicate)
	{
		auto it = find_if(vec.begin(), vec.end(), predicate);
		return it != vec.end() ? &(*it) : nullptr;
	}

	export_ template <class T, class Pred>
	inline auto vector_find_if(vector<T>& vec, Pred predicate)
	{
		return find_if(vec.begin(), vec.end(), predicate);
	}
	
	export_ template <class T, class Pred>
	inline auto vector_find_if(const vector<T>& vec, Pred predicate)
	{
		return find_if(vec.begin(), vec.end(), predicate);
	}
	
	export_ template <class T>
	inline void vector_remove_object(vector<T>& vec, T& object)
	{
		auto pos = find_if(vec.begin(), vec.end(), [&](const T& look) { return &look == &object; });
		vec.erase(pos);
	}

	export_ template <class T>
	inline bool vector_contains(const vector<T>& vec, const vector<T>& other)
	{
		return includes(vec.begin(), vec.end(), other.begin(), other.end());
	}

	export_ template <class T>
	inline vector<T> vector_reverse(const vector<T>& vec)
	{
		vector<T> result = vec;
		reverse(result.begin(), result.end());
		return result;
	}

	export_ template <class T, class V>
	inline auto vector_remove_pt(vector<T>& vec, V& value)
	{
		auto pos = find_if(vec.begin(), vec.end(), [&](auto& pt) { return pt.get() == &value; });
		vec.erase(pos);
	}

	export_ template <class T, class V>
	inline auto vector_transfer_pt(vector<T>& source, vector<T>& target, V& value)
	{
		auto pos = find_if(source.begin(), source.end(), [&](auto& pt) { return pt.get() == &value; });
		target.push_back(move(*pos));
		source.erase(pos);
	}

	export_ template <class T>
	inline void vector_add(vector<T>& vec, T value)
	{
		if(!vector_has(vec, value))
			vec.push_back(value);
	}

	export_ template <class T>
	inline void vector_select(vector<T>& vec, T value) { vec.clear(); vec.push_back(value); }

	export_ template <class T>
	inline bool vector_swap(vector<T>& vec, T value) { if(vector_has(vec, value)) { vector_remove(vec, value); return false; } else { vector_add(vec, value); return true; } }
	
	export_ template <class T>
	inline size_t index_of(const vector<T>& vec, const T& value)
	{
		return find(vec.begin(), vec.end(), value) - vec.begin();
	}

	template <class U, class T, class F>
	export_ vector<U> transform(const vector<T>& vec, F func)
	{
		vector<U> result;
		for(const T& value : vec)
			result.push_back(func(value));
		return result;
	}

	template <class V, class T, class U, class F>
	export_ vector<V> transform(const vector<T>& a, const vector<U>& b, F func)
	{
		vector<V> result;
		for(size_t i = 0; i < a.size(); ++i)
			result.push_back(func(a[i], b[i]));
		return result;
	}

	template <class T, class F>
	export_ vector<T> transform(size_t begin, size_t end, F func)
	{
		vector<T> result;
		for(size_t i = begin; i < end; ++i)
			result.push_back(func(i));
		return result;
	}
}

#if defined(WIN32)
#include <malloc.h>
#else
#include <cstdlib>
#endif

namespace mud
{
	inline void* aligned_alloc(size_t size, size_t align) noexcept
	{
		assert(align && !(align & (align - 1)));
		void* p = nullptr;

		// must be a power of two and >= sizeof(void*)
		while(align < sizeof(void*))
			align <<= 1;

#if defined(WIN32)
		p = ::_aligned_malloc(size, align);
#else
		::posix_memalign(&p, align, size);
#endif
		return p;
	}

	inline void aligned_free(void* p) noexcept
	{
#if defined(WIN32)
		::_aligned_free(p);
#else
		::free(p);
#endif
	}

#ifdef MUD_NO_STL
	template <class T>
	class TinystlAlignedAllocator
	{
	public:
		static inline T* static_allocate(size_t bytes) { return (T*)aligned_alloc(bytes, alignof(T)); };
		static inline void static_deallocate(T* ptr, size_t /*bytes*/) { aligned_free(ptr); }
	};
#else
	template <class T>
	class STLAlignedAllocator
	{
		static_assert(!(alignof(T) & (alignof(T)-1)), "alignof(T) must be a power of two");

	public:
		using value_type = T;
		using pointer = T*;
		using const_pointer = const T*;
		using reference = T&;
		using const_reference = const T&;
		using size_type = size_t;
		using difference_type = std::ptrdiff_t;
		using propagate_on_container_move_assignment = true_type;
		using is_always_equal = true_type;

		template <class U>
		struct rebind { using other = STLAlignedAllocator<U>; };

	public:
		inline STLAlignedAllocator() noexcept = default;
		inline ~STLAlignedAllocator() noexcept = default;

		template <class U>
		inline explicit STLAlignedAllocator(const STLAlignedAllocator<U>&) noexcept {}

		inline pointer allocate(size_type n) noexcept { return (pointer)aligned_alloc(n * sizeof(value_type), alignof(T)); }
		inline void deallocate(pointer p, size_type) { aligned_free(p); }

		inline bool operator==(const STLAlignedAllocator<T>&) const { return true; }
		inline bool operator!=(const STLAlignedAllocator<T>&) const { return false; }
	};
#endif
}
