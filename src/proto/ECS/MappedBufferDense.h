#pragma once

#include <proto/Forward.h>
#include <proto/ECS/MappedBuffers.h>

#include <map>
#include <unordered_map>

namespace mud
{
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
}
