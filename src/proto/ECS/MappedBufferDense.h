#pragma once

#include <core/Forward.h>
#include <proto/ECS/MappedBuffers.h>

#include <map>
#include <unordered_map>

namespace toy
{
	template <class TKey, class TData>
	class MappedBufferDense : public MappedBufferBase<TKey, TData>
	{
	public:
		static constexpr bool is_sparse = false;

	public:
		std::unordered_map<TKey, int> m_keys_to_indices;

	public:
		MappedBufferDense(int capacity = 1 << 10)
			: MappedBufferBase<TKey, TData>(4)
			, m_keys_to_indices(4) // NOTE: We intentionally don't use initialSize for dense buffers
		{
			UNUSED(capacity);
		}

		void SetCapacity(size_t capacity)
		{
			UNUSED(capacity);
		}

		struct Buffers { std::unordered_map<TKey, int> keys_to_indices; std::vector<TKey> indices_to_keys; std::vector<TData> data; };
		Buffers __GetBuffers()
		{
			return { m_keys_to_indices, m_keys, m_data };
		}

		void SetK2i(std::vector<TKey> keys, std::vector<int> ints)
		{
			m_keys_to_indices.clear();
			for(auto i = 0; i < keys.size(); i++)
			{
				m_keys_to_indices[keys[i]] = ints[i];
				m_keys[ints[i]] = keys[i];
			}
		}

		int GetIndexFromKey(TKey key) // internal
		{
			return m_keys_to_indices[key];
		}

	public:
		TData& GetDataFromKey(TKey key) // internal
		{
			return ref m_data[m_keys_to_indices[key]];
		}

		void AddKey(TKey key, const TData& data)
		{
			m_keys_to_indices[key] = AddEntry(key, data);
		}

		int RemoveKey(TKey key) // internal
		{
			auto keyIndex = GetIndexFromKey(key);
			Removed removed = RemoveByIndex(keyIndex);
			m_keys_to_indices[removed.replacingKey] = keyIndex; //update index of last key
			m_keys_to_indices.erase(key);
			return removed.lastIndex;
		}

	public:
		virtual void UpdateKeyForEntry(TKey oldKey, TKey newKey) override
		{
			auto replacedKeyValue = m_keys_to_indices[oldKey];
			m_keys_to_indices.erase(oldKey);
			m_keys_to_indices[newKey] = replacedKeyValue;
			UpdateEntryKey(replacedKeyValue, newKey);
		}

		std::vector<int> SortDataApplyKeysAndGetMoves()
		{
			auto moves = SortDataAndGetMoves();

			auto newKeys = std::vector<TKey>(m_keys.size());

			for(auto i = 0; i < m_count; i++)
			{
				newKeys[i] = m_keys[moves[i]];
				m_keys_to_indices[m_keys[moves[i]]] = i;
			}

			m_keys = newKeys;

			return moves;
		}

		string GetDebugString(bool detailed) // override
		{
			UNUSED(detailed); return "";
			//return
			//	$"  Entries: {m_count}, Map Entries: {m_keys_to_indices.m_count}\n" +
			//	$"  Map: {string.Join(", ", m_keys_to_indices.Select(x => x.Key + ":" + x.Value))}";
		}
	};
}
