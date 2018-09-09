#pragma once

#include <proto/ECS/ECS.h>
#include <proto/ECS/Misc.h>

#include <string>
#include <vector>
#include <algorithm>

namespace toy
{
	using string = std::string;

	template <class TKey, class TData>
	class MappedBufferBase
	{
	public:
		std::vector<TData> m_data;
		std::vector<TKey> m_keys;

	public:
		int buffer_size() { return m_data.size(); }
		int m_count = 0;

	private:
		std::vector<int> m_cached_move_map;// = null; //todo encaps

	public:
		MappedBufferBase(int size)
			: m_data(size), m_keys(size)
		{}
		
		TKey GetKeyFromIndex(int index) { return m_keys[index]; }
		TData& GetDataFromIndex(int index) { return m_data[index]; }

		/// Returns index of the new element
		int AddEntry(TKey key, const TData& data)
		{
			int currentIndex = m_count;

			if(m_data.size() <= size_t(currentIndex)) //expand buffer as needed
			{
				int dataLength = m_data.size();
				int newSize = dataLength * 2;

				std::vector<TData> newData = std::vector<TData>(newSize);
				std::vector<TKey> newIndicesToKeys = std::vector<TKey>(newSize);
				std::copy(m_data.begin(), m_data.end(), newData.begin());
				std::copy(m_keys.begin(), m_keys.end(), newIndicesToKeys.begin());
				m_data = newData;
				m_keys = newIndicesToKeys;

				//OnBufferSizeChanged ? .Invoke(newSize);
			}

			m_data[currentIndex] = data;
			m_keys[currentIndex] = key;
			m_count++;

			return currentIndex;
			
			/*m_data.push_back(data);
			m_keys.push_back(key);
			return m_count++;*/
		}

		/// Returns key and index of the element that replaced the removed one
		struct Removed { TKey replacingKey; int lastIndex; };
		Removed RemoveByIndex(int indexToRemove)
		{
			int lastIndex = m_count - 1;
			TKey lastKey = m_keys[lastIndex];

			m_data[indexToRemove] = m_data[lastIndex]; //swap data for last
			m_keys[indexToRemove] = lastKey; //update key stored in index
			m_count--;

			return { lastKey, lastIndex };
		}

		//    public void Swap(int indexA, int indexB)
		//    {
		//        auto tmpData = m_data[indexB];
		//        m_data[indexB] = m_data[indexA];
		//        m_data[indexA] = tmpData;
		//
		//        auto tmpKey = m_keys[indexB];
		//        m_keys[indexB] = m_keys[indexA];
		//        m_keys[indexA] = tmpKey;
		//    }

		std::vector<int> GetCachedMoveMapArr()
		{
			if(m_cached_move_map.size() < m_data.size())
				m_cached_move_map.resize(m_data.size());
			for(auto i = 0; i < m_count; i++)
				m_cached_move_map[i] = i;
			return m_cached_move_map;
		}

		struct CompareKey
		{
			bool operator()(std::pair<TKey, int> a, std::pair<TKey, int> b) const { return a.first < b.first; }
		};

		struct CompareData
		{
			bool operator()(std::pair<TData, int> a, std::pair<TData, int> b) const { return a.first < b.first; }
		};

		std::vector<int> SortPrototypesAndGetMoves(const std::vector<EntityData>& entities)
		{
			auto moveMap = GetCachedMoveMapArr();
			auto compare = [&](std::pair<TKey, int> a, std::pair<TKey, int> b) { return entities[a.first].m_flags < entities[b.first].m_flags; };
			std::sort(make_dual_iterator(m_keys.begin(), moveMap.begin()), make_dual_iterator(m_keys.end(), moveMap.end()), compare);
			return moveMap;
		}

		std::vector<int> SortKeysAndGetMoves()
		{
			auto moveMap = GetCachedMoveMapArr();
			std::sort(make_dual_iterator(m_keys.begin(), moveMap.begin()), make_dual_iterator(m_keys.end(), moveMap.end()), CompareKey());
			return moveMap;
		}

		std::vector<int> SortDataAndGetMoves()
		{
			auto moveMap = GetCachedMoveMapArr();
			std::sort(make_dual_iterator(m_data.begin(), moveMap.begin()), make_dual_iterator(m_data.end(), moveMap.end()), CompareData());
			return moveMap;
		}

		virtual void UpdateEntryKey(int index, TKey key)
		{
			m_keys[index] = key;
		}

	public:
		virtual void UpdateKeyForEntry(TKey oldKey, TKey newKey) = 0;

		virtual string GetDebugString(bool detailed) = 0;
	};
}