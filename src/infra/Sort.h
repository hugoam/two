//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/swap.h>
#include <infra/Config.h>
#include <infra/Array.h>

namespace mud
{
#if 0
	template <class T_Key, class T_Value, class T_Indices, class T_Greater>
	void quicksort(array<T_Key> keys, array<T_Value> values, T_Indices& indices, T_Greater greater, const size_t left, const size_t right)
	{
		auto swap = [&](size_t first, size_t second)
		{
			using mud::swap;
			swap(keys[first], keys[second]);
			swap(values[first], values[second]);
			swap(indices[keys[first]], indices[keys[second]]);
		};

		auto partition = [&](const size_t left, const size_t right)
		{
			const size_t mid = left + (right - left) / 2;
			const T_Key pivot = keys[mid];
			// move the mid point value to the front.
			swap(mid, left);
			size_t i = left + 1;
			size_t j = right;
			while(i <= j)
			{
				while(i <= j && !greater(keys[i], pivot))
					i++;

				while(i <= j && greater(keys[j], pivot))
					j--;

				if(i < j)
					swap(i, j);
			}
			swap(i - 1, left);
			return i - 1;
		};

		size_t part = partition(left, right);

		if(int(left) < int(part) - 1)
			quicksort(keys, values, indices, greater, left, part - 1);
		if(part + 1 < right)
			quicksort(keys, values, indices, greater, part + 1, right);
	}

	template <class T_Key, class T_Value, class T_Indices, class T_Greater>
	void quicksort(array<T_Key> keys, array<T_Value> values, T_Indices& indices, T_Greater greater)
	{
		if(keys.size() > 0)
			quicksort(keys, values, indices, greater, 0, keys.size() - 1);
	}

	template <class T_Key, class T_Value, class T_Indices>
	void quicksort(array<T_Key> keys, array<T_Value> values, T_Indices& indices)
	{
		auto greater = [](T_Key a, T_Key b) { return a > b; };
		if(keys.size() > 0)
			quicksort(keys, values, indices, greater, 0, keys.size() - 1);
	}
#endif
	
	template <class T, class Pred>
	void quicksort(array<T> vec, Pred greater, const size_t left, const size_t right)
	{
		auto partition = [&](const size_t left, const size_t right)
		{
			const size_t mid = left + (right - left) / 2;
			const T& pivot = vec[mid];
			// move the mid point value to the front.
			swap(vec[mid], vec[left]);
			size_t i = left + 1;
			size_t j = right;
			while(i <= j)
			{
				while(i <= j && !greater(vec[i], pivot))
					i++;

				while(i <= j && greater(vec[j], pivot))
					j--;

				if(i < j)
					swap(vec[i], vec[j]);
			}
			swap(vec[i - 1], vec[left]);
			return i - 1;
		};

		size_t part = partition(left, right);

		if(int(left) < int(part) - 1)
			quicksort(vec, greater, left, part - 1);
		if(part + 1 < right)
			quicksort(vec, greater, part + 1, right);
	}

	template <class T, class Pred>
	void quicksort(array<T> values, Pred greater)
	{
		if(values.size() > 0)
			quicksort(values, greater, 0, values.size() - 1);
	}

	template <class T>
	void quicksort(array<T> values)
	{
		auto greater = [](T a, T b) { return a > b; };
		if(values.size() > 0)
			quicksort(values, greater, 0, values.size() - 1);
	}
}
