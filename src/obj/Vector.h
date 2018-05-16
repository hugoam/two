//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Generated/Forward.h>
#include <obj/Array.h>
#include <obj/Cls.h>
#include <obj/TypeUtils.h>

#include <vector>
#include <algorithm>

namespace mud
{
	template <typename T>
	struct is_comparable<std::vector<T>> : is_comparable_base<T> {};

	template <class T>
	array<T> to_array(std::vector<T>& vector) { return { &vector[0], vector.size() }; }
	template <class T>
	array<T> to_array(std::vector<T>& vector, size_t offset) { return { &vector[offset], vector.size() - offset }; }
	template <class T>
	array<T> to_array(std::vector<T>& vector, size_t offset, size_t count) { return { &vector[offset], count }; }

	template <class T>
	std::vector<T> to_vector(const array<T>& array) { return { array.m_pointer, array.m_pointer + array.m_count }; }

	template <class... T_Args>
	inline std::vector<Type*> type_vector()
	{
		return { &type<T_Args>()... };
	}

	template <class T>
	inline void vector_extend(std::vector<T>& vector, const std::vector<T>& other)
	{
		vector.insert(vector.end(), other.begin(), other.end());
	}

	template <class T>
	inline void vector_prepend(std::vector<T>& vector, const std::vector<T>& other)
	{
		vector.insert(vector.begin(), other.begin(), other.end());
	}

	template <class T>
	inline std::vector<T> vector_union(const std::vector<T>& first, const std::vector<T>& second)
	{
		std::vector<T> result; vector_extend(result, first); vector_extend(result, second); return result;
	}

	template <class T>
	inline void vector_push(std::vector<T>& vector, T value)
	{
		vector.insert(vector.begin(), value);
	}

	template <class T>
	inline T vector_pop(std::vector<T>& vector)
	{
		T val = std::move(vector.back());
		vector.pop_back();
		return val;
	}

	template <class T, class U>
	inline void vector_cast(const std::vector<T>& source, std::vector<U>& target)
	{
		target.reserve(source.size());
		for(const T& val : source)
			target.push_back(static_cast<U>(val));
	}

	template <class U, class T>
	inline std::vector<U> vector_convert(const std::vector<T>& source)
	{
		std::vector<U> target;
		target.reserve(source.size());
		for(const T& val : source)
			target.push_back(static_cast<U>(val));
		return target;
	}

	template <class U, class T, class Op>
	inline std::vector<U> vector_convert(const std::vector<T>& source, Op op)
	{
		std::vector<U> result;
		result.resize(source.size());
		std::transform(source.begin(), source.end(), result.begin(), op);
		return result;
	}

	template <class T>
	inline void vector_remove(std::vector<T>& vector, T value)
	{
		vector.erase(std::remove(vector.begin(), vector.end(), value), vector.end());
	}

	template <class T>
	inline void vector_remove_ref(std::vector<T>& vector, T& value)
	{
		size_t index = &value - vector.data();
		vector.erase(vector.begin() + index);
	}

	template <class T, class Pred>
	inline auto vector_remove_if(std::vector<T>& vector, Pred predicate)
	{
		return vector.erase(std::remove_if(vector.begin(), vector.end(), predicate), vector.end());
	}

	template <class T, class Pred>
	inline void vector_prune(std::vector<T>& vector, Pred predicate)
	{
		for(int i = vector.size() - 1; i >= 0; i--)
			if(predicate(vector[i]))
				vector.erase(vector.begin() + i);
	}

	template <class T>
	inline size_t vector_index(const std::vector<T>& vector, T value)
	{
		return std::find(vector.begin(), vector.end(), value) - vector.begin();
	}
	
	template <class T>
	inline size_t array_index(array<T> vector, T value)
	{
		return std::find(vector.begin(), vector.end(), value) - vector.begin();
	}

	template <class T>
	inline bool vector_has(const std::vector<T>& vector, T value)
	{
		return std::find(vector.begin(), vector.end(), value) != vector.end();
	}

	template <class T, class Pred>
	inline bool vector_has_pred(const std::vector<T>& vector, Pred predicate)
	{
		return std::find_if(vector.begin(), vector.end(), predicate) != vector.end();
	}

	template <class T, class Pred>
	inline T* vector_find(std::vector<T>& vector, Pred predicate)
	{
		auto it = std::find_if(vector.begin(), vector.end(), predicate);
		return it != vector.end() ? &(*it) : nullptr;
	}

	template <class T, class Pred>
	inline auto vector_find_if(const std::vector<T>& vector, Pred predicate)
	{
		return std::find_if(vector.begin(), vector.end(), predicate);
	}

	template <class T>
	inline void vector_remove_object(std::vector<T>& vector, T& object)
	{
		auto pos = vector_find_if(vector, [&](const T& look) { return &look == &object; });
		vector.erase(pos);
	}

	template <class T>
	inline bool vector_contains(const std::vector<T>& vector, const std::vector<T>& other)
	{
		return std::includes(vector.begin(), vector.end(), other.begin(), other.end());
	}

	template <class T>
	inline std::vector<T> vector_reverse(const std::vector<T>& vector)
	{
		std::vector<T> result = vector;
		std::reverse(result.begin(), result.end());
		return result;
	}

	template <class T, class V>
	inline auto vector_remove_pt(std::vector<T>& vector, V& value)
	{
		auto pos = vector_find_if(vector, [&](auto& pt) { return pt.get() == &value; });
		vector.erase(pos);
	}

	template <class T, class V>
	inline auto vector_transfer_pt(std::vector<T>& source, std::vector<T>& target, V& value)
	{
		auto pos = vector_find_if(source, [&](auto& pt) { return pt.get() == &value; });
		target.emplace_back(std::move(*pos));
		source.erase(pos);
	}

	template <class T>
	inline void vector_add(std::vector<T>& vector, T value)
	{
		if(!vector_has(vector, value))
			vector.push_back(value);
	}

	template <class T>
	inline void vector_select(std::vector<T>& vector, T value) { vector.clear(); vector.push_back(value); }

	template <class T>
	inline bool vector_swap(std::vector<T>& vector, T value) { if(vector_has(vector, value)) { vector_remove(vector, value); return false; } else { vector_add(vector, value); return true; } }
}
