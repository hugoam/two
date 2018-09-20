#pragma once

#include <proto/ECS/ECS.h>
#include <proto/ECS/Misc.h>

#include <string>
#include <vector>
#include <algorithm>

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
}