#pragma once

#include <proto/ECS/ECS.h>

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

namespace mud
{
	using string = std::string;

	template <class TData>
	class MappedBufferBase
	{
	public:
		std::vector<TData> m_data;
		std::vector<uint32_t> m_keys;

	public:
		MappedBufferBase(size_t size)
		{
			m_data.reserve(size);
			m_keys.reserve(size);
		}
		
		uint32_t AddEntry(uint32_t key, TData data)
		{
			uint32_t index = m_data.size();
			m_data.emplace_back(std::move(data));
			m_keys.push_back(key);
			return index;
		}

		/// Returns key and index of the element that replaced the removed one
		uint32_t RemoveByIndex(uint32_t index)
		{
			std::swap(m_data[index], m_data.back());
			std::swap(m_keys[index], m_keys.back());
			m_data.pop_back();
			m_keys.pop_back();
			return m_keys[index];
		}

		void Swap(size_t first, size_t second)
		{
			std::swap(m_data[first], m_data[second]);
			std::swap(m_keys[first], m_keys[second]);
		}

		virtual void UpdateEntryKey(int index, uint32_t key)
		{
			m_keys[index] = key;
		}

	public:
		virtual void Move(uint32_t oldKey, uint32_t newKey) = 0;
	};

	template <class TData>
	class MappedBufferDense : public MappedBufferBase<TData>
	{
	public:
		static constexpr bool is_sparse = false;

	public:
		std::unordered_map<uint32_t, int> m_indices;

	public:
		MappedBufferDense(int capacity = 1 << 10)
			: MappedBufferBase<TData>(4)
			, m_indices(4) // NOTE: We intentionally don't use initialSize for dense buffers
		{
			UNUSED(capacity);
		}

		void SetCapacity(size_t capacity)
		{
			UNUSED(capacity);
		}

		TData& At(uint32_t key) // internal
		{
			return m_data[m_indices[key]];
		}

		void AddKey(uint32_t key, TData data)
		{
			m_indices[key] = AddEntry(key, std::move(data));
		}

		void RemoveKey(uint32_t key) // internal
		{
			uint32_t index = m_indices[key];
			uint32_t moved = RemoveByIndex(index);
			m_indices[moved] = index; //update index of last key
			m_indices.erase(key);
		}

		void Move(uint32_t oldKey, uint32_t newKey) override
		{
			auto replacedKeyValue = m_indices[oldKey];
			m_indices.erase(oldKey);
			m_indices[newKey] = replacedKeyValue;
			UpdateEntryKey(replacedKeyValue, newKey);
		}
	};

	template <class TData>
	class MappedBufferSparse : public MappedBufferBase<TData>
	{
	public:
		static constexpr bool is_sparse = true;

	public:
		std::vector<uint32_t> m_indices;

	public:
		MappedBufferSparse(int capacity = 1 << 10)
			: MappedBufferBase<uint32_t, TData>(capacity) // internal
			, m_indices(capacity, UINT32_MAX)
		{}

		void SetCapacity(size_t capacity)
		{
			m_indices.resize(capacity);
		}

		TData& At(uint32_t key)
		{
			return m_data[m_indices[key]];
		}

		void AddKey(uint32_t key, TData data)
		{
			//todo check tkey existence?
			m_indices[key] = AddEntry(key, std::move(data));
		}

		void RemoveKey(uint32_t key)
		{
			uint32_t index = m_indices[key];
			uint32_t moved = RemoveByIndex(index);
			m_indices[moved] = index; //update index of last key
			m_indices[key] = UINT32_MAX;
		}

		void Move(uint32_t oldKey, uint32_t newKey) override
		{
			uint32_t replacedKeyValue = m_indices[oldKey];
			m_indices[oldKey] = UINT32_MAX;
			m_indices[newKey] = replacedKeyValue;
			UpdateEntryKey(replacedKeyValue, newKey);
		}
	};
}