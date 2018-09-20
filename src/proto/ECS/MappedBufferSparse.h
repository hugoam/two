#pragma once

#include <proto/ECS/MappedBuffers.h>

namespace mud
{
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