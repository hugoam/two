#pragma once

#include <proto/ECS/MappedBuffers.h>

namespace toy
{
	template <class TData>
	class MappedBufferSparse : public MappedBufferBase<int, TData>
	{
	public:
		static constexpr bool is_sparse = true;

	public:
		std::vector<int> m_keys_to_indices;

	public:
		MappedBufferSparse(int capacity = 1 << 10)
			: MappedBufferBase<int, TData>(capacity) // internal
			, m_keys_to_indices(capacity, -1)
		{}

		void SetCapacity(size_t capacity)
		{
			m_keys_to_indices.resize(capacity);
		}

		struct Buffers { std::vector<int> keys_to_indices; std::vector<int> indices_to_keys; std::vector<TData> data; };
		Buffers __GetBuffers() // internal
		{
			return { m_keys_to_indices, m_keys, m_data };
		}

		void SetK2i(std::vector<int> keys, std::vector<int> ints)
		{
			//todo fixme this is slow - used only when reordering entities - i.e. offline so not critical

			for(auto i = 0; i < m_keys_to_indices.size(); i++)
			{
				m_keys_to_indices[i] = -1;
			}

			for(auto i = 0; i < keys.size(); i++)
			{
				m_keys_to_indices[keys[i]] = ints[i];
				m_keys[ints[i]] = keys[i];
			}
		}

		int GetIndexFromKey(int key) // internal
		{
			return m_keys_to_indices[key];
		}

		TData& GetDataFromKey(int key)
		{
			return m_data[m_keys_to_indices[key]];
		}

		void AddKey(int key, const TData& data)
		{
			//todo check tkey existence?
			m_keys_to_indices[key] = AddEntry(key, data);
		}

		int RemoveKey(int key)
		{
			auto keyIndex = GetIndexFromKey(key);
			Removed removed = RemoveByIndex(keyIndex);
			m_keys_to_indices[removed.replacingKey] = keyIndex; //update index of last key
			m_keys_to_indices[key] = -1;
			return removed.lastIndex; //todo this could be void? (only sparse)
		}

		virtual void UpdateKeyForEntry(int oldKey, int newKey) override
		{
			auto replacedKeyValue = m_keys_to_indices[oldKey];
			m_keys_to_indices[oldKey] = -1;
			m_keys_to_indices[newKey] = replacedKeyValue;
			UpdateEntryKey(replacedKeyValue, newKey);
		}


		// THIS IS SLOW AS BALLS :(
		// class CustomKeyComparer : IComparer<int>
		// {
		//     private std::vector<int> RefK2i { get; }
		//
		//     public CustomKeyComparer(std::vector<int> refK2i)
		//     {
		//         RefK2i = refK2i;
		//     }
		//
		//     public int Compare(int x, int y)
		//     {
		//         return RefK2i[x].CompareTo(RefK2i[y]);
		//     }
		// }

		// public void SortDataByKeyRef(std::vector<int> refK2i) //THIS IS THE ONLY CRITICAL SORTING (streamline)
		// {
		//     auto mm = GetCachedMoveMapArr();
		//     Array.Sort(m_keys, mm, 0, m_count);
		//
		//     auto newData = new TData[m_count]; //todo
		//
		//     for (auto i = 0; i < m_count; i++)
		//     {
		//         auto oldIndex = mm[i];
		//         newData[i] = m_data[oldIndex];
		//         m_keys_to_indices[m_keys[i]] = i;
		//     }
		//
		//     //todo cache sorting array (GC-less)
		//     m_data = newData;
		// }

		string GetDebugString(bool detailed) // override
		{
			UNUSED(detailed); return "";
			//return
			//	$"  Entries: {m_count}, m_sparse Entries: {m_keys_to_indices.size()}\n" +
			//	$"  Map: {string.Join(", ", m_keys_to_indices.Where(x => x >= 0))}";
		}

	};
}