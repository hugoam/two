//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/vector.h>
#include <stl/algorithm.h>
#include <infra/Config.h>
#include <stl/span.h>

namespace two
{
	export_ template <class T>
	span<T> to_array(vector<T>& vec) { return { &vec[0], vec.size() }; }
	export_ template <class T>
	span<T> to_array(vector<T>& vec, size_t offset) { return { &vec[offset], vec.size() - offset }; }
	export_ template <class T>
	span<T> to_array(vector<T>& vec, size_t offset, size_t count) { return { &vec[offset], count }; }

	export_ template <class T, class U>
	span<T> to_array_cast(vector<U>& vec) { return{ (T*)&vec[0], vec.size() }; }

	export_ template <class T>
	vector<T> to_vector(const span<T>& span) { return { span.m_pointer, span.m_pointer + span.m_count }; }
	
	export_ template <class T>
	inline bool has(span<T> vec, const T& value)
	{
		return find(vec.begin(), vec.end(), value) != vec.end();
	}

	export_ template <class T>
	inline bool has(std::initializer_list<T> vec, const T& value)
	{
		return find(vec.begin(), vec.end(), value) != vec.end();
	}
	
	export_ template <class T>
	inline vector<T> slice(span<T> vec, size_t begin, size_t end)
	{
		vector<T> result;
		for(size_t i = begin; i < end; ++i)
			result.push_back(vec[i]);
		return result;
	}
	
	export_ template <class T>
	inline vector<T> prepend(span<T> vec, const T& value)
	{
		vector<T> result(vec.begin(), vec.end());
		result.insert(result.begin(), value);
		return result;
	}

	export_ template <class T, class U>
	inline void cast(span<T> source, vector<U>& target)
	{
		target.reserve(source.size());
		for(const T& val : source)
			target.push_back(static_cast<U>(val));
	}

	export_ template <class U, class T>
	inline vector<U> convert(span<T> source)
	{
		vector<U> target;
		cast(source, target);
		return target;
	}

	export_ template <class U, class T, class Op>
	inline vector<U> convert(span<T> source, Op op)
	{
		vector<U> result;
		result.resize(source.size());
		transform(source.begin(), source.end(), result.begin(), op);
		return result;
	}

	export_ template <class U, class T, class F>
	vector<U> transform(span<T> vec, F func)
	{
		vector<U> result;
		for(const T& value : vec)
			result.push_back(func(value));
		return result;
	}

	export_ template <class V, class T, class U, class F>
	vector<V> transform(span<T> a, span<U> b, F func)
	{
		vector<V> result;
		for(size_t i = 0; i < a.size(); ++i)
			result.push_back(func(a[i], b[i]));
		return result;
	}

	export_ template <class T, class F>
	vector<T> transform(size_t begin, size_t end, F func)
	{
		vector<T> result;
		for(size_t i = begin; i < end; ++i)
			result.push_back(func(i));
		return result;
	}
}
