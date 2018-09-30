#pragma once

#include <infra/Array.h>
#include <infra/Generic.h>
#include <proto/Forward.h>
#include <proto/ECS/ECS.h>
#include <proto/ECS/SparseBuffer.h>

#include <vector>

namespace mud
{
	template <class T_Key, class T_Value, class T_Indices, class T_Greater>
	void quicksort(array<T_Key> keys, array<T_Value> values, T_Indices& indices, T_Greater greater, const size_t left, const size_t right)
	{
		auto swap = [&](size_t first, size_t second)
		{
			std::swap(keys[first], keys[second]);
			std::swap(values[first], values[second]);
			std::swap(indices[keys[first]], indices[keys[second]]);
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

	class ComponentBufferBase
	{
	public:
		EntFlags m_flag;

		virtual void Add() = 0;
		virtual void Remove(uint32_t index) = 0;

		virtual void SortComponents() = 0;
	};

	template <class T>
	class ComponentBuffer : public ComponentBufferBase
	{
	public:
		ComponentBuffer() {}
		ComponentBuffer(int bufferIndex, int capacity = 1 << 10)
		{
			m_data.reserve(capacity);
			m_flag = uint64_t(1ULL << bufferIndex);
		}

		virtual void SortComponents() override
		{
			//quicksort(to_array(this->m_keys), to_array(this->m_data), this->m_indices);
		}

		virtual void Add()
		{
			m_data.emplace_back();
		}

		virtual void Remove(uint32_t index)
		{
			std::swap(m_data[index], m_data.back());
			m_data.pop_back();
		}

		std::vector<T> m_data;
	};
}