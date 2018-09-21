#pragma once

#include <infra/Array.h>
#include <infra/Generic.h>
#include <proto/ECS/ECS.h>

#include <vector>
#include <string>

namespace mud
{
	using string = std::string;

	template <class T_Key, class T_Value, class T_Indices, class T_Greater>
	void quicksort(array<T_Key> keys, array<T_Value> values, T_Indices& indices, T_Greater greater, const size_t left, const size_t right)
	{
		auto partition = [](array<T_Key> keys, array<T_Value> values, T_Indices& indices, T_Greater greater, const size_t left, const size_t right)
		{
			const size_t mid = left + (right - left) / 2;
			const T_Key pivot = keys[mid];
			// move the mid point value to the front.
			std::swap(keys[mid], keys[left]);
			std::swap(values[mid], values[left]);
			std::swap(indices[keys[mid]], indices[keys[left]]);
			size_t i = left + 1;
			size_t j = right;
			while(i <= j)
			{
				while(i <= j && !greater(keys[i], pivot))
					i++;

				while(i <= j && greater(keys[j], pivot))
					j--;

				if(i < j)
					std::swap(keys[i], keys[j]);
			}
			std::swap(keys[i - 1], keys[left]);
			std::swap(values[i - 1], values[left]);
			std::swap(indices[keys[i - 1]], indices[keys[left]]);
			return i - 1;
		};

		if(left >= right)
			return;

		size_t part = partition(keys, values, indices, greater, left, right);
		quicksort(keys, values, indices, greater, left, part - 1);
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

	class BitUtils
	{
	public:
		static int BitPosition(uint32_t flag)
		{
			for(int i = 0; i < 32; i++)
				if(flag >> i == 1)
					return i;
			return -1;
		}

		static int BitPosition(uint64_t flag)
		{
			for(int i = 0; i < 64; i++)
				if(flag >> i == 1)
					return i;
			return -1;
		}

		static uint32_t BitCount(uint32_t flags)
		{
			flags = flags - ((flags >> 1)&  0x55555555u);
			flags = (flags&  0x33333333u) + ((flags >> 2)&  0x33333333u);
			return (((flags + (flags >> 4))&  0x0F0F0F0Fu) * 0x01010101u) >> 24;
		}

#define unchecked(x) x

		static uint64_t BitCount(uint64_t flags)
		{
			flags = flags - ((flags >> 1)&  0x5555555555555555ul);
			flags = (flags&  0x3333333333333333ul) + ((flags >> 2)&  0x3333333333333333ul);
			return unchecked(((flags + (flags >> 4))&  0xF0F0F0F0F0F0F0Ful) * 0x101010101010101ul) >> 56;
		}
#undef unchecked
	};
}