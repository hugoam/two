#pragma once

#include <proto/ECS/ECS.h>

#include <vector>
#include <algorithm>
#include <unordered_map>

namespace mud
{
	template <bool dense = false>
	class SparseIndices
	{
	public:
		SparseIndices(size_t capacity = 1 << 10) : m_indices(4) { UNUSED(capacity); }

		void erase(uint32_t handle) { m_indices.erase(handle); }

		void ensure(size_t capacity) { UNUSED(capacity); }

		uint32_t& operator[](uint32_t at) { return m_indices[at]; }

	private:
		std::unordered_map<uint32_t, uint32_t> m_indices;
	};

	template <>
	class SparseIndices<true>
	{
	public:
		SparseIndices(size_t capacity = 1 << 10) : m_indices(capacity, UINT32_MAX) {}

		void erase(uint32_t handle) { m_indices[handle] = UINT32_MAX; }
		
		void ensure(size_t capacity) { m_indices.resize(capacity, UINT32_MAX); }

		uint32_t& operator[](uint32_t at) { return m_indices[at]; }

	private:
		std::vector<uint32_t> m_indices;
	};

	template <class TData, bool dense = false>
	class MappedBuffer
	{
	public:
		std::vector<TData> m_data;
		std::vector<uint32_t> m_keys;
		SparseIndices<dense> m_indices;

	public:
		MappedBuffer(size_t size)
			: m_indices(size)
		{
			m_data.reserve(size);
			m_keys.reserve(size);
		}
		
		void SetCapacity(size_t capacity)
		{
			m_indices.ensure(capacity);
		}

		void AddKey(uint32_t key, TData data)
		{
			const uint32_t index = m_data.size();
			m_data.emplace_back(std::move(data));
			m_keys.push_back(key);
			m_indices[key] = index;
		}

		void RemoveKey(uint32_t key)
		{
			const uint32_t index = m_indices[key];

			std::swap(m_data[index], m_data.back());
			std::swap(m_keys[index], m_keys.back());
			m_data.pop_back();
			m_keys.pop_back();

			const uint32_t moved = m_keys[index];
			m_indices[moved] = index;
			m_indices.erase(key);
		}

		TData& At(uint32_t key)
		{
			return m_data[m_indices[key]];
		}

		void Swap(size_t first, size_t second)
		{
			std::swap(m_data[first], m_data[second]);
			std::swap(m_keys[first], m_keys[second]);
		}

		void Move(uint32_t from, uint32_t to)
		{
			uint32_t replaced = m_indices[from];
			m_indices.erase(from);
			m_indices[to] = replaced;
			m_keys[replaced] = to;
		}
	};
}