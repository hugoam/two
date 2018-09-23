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
		bool m_sparse;

		virtual void SetCapacity(size_t capacity) = 0;

		virtual void SortComponents(const std::vector<EntityData>& entities) = 0;
		virtual void SortComponents() = 0;
		virtual void RemoveComponent(uint32_t handle, EntityData& entity) = 0;
	};

	template <class T, bool dense = true>
	class ComponentBuffer : public ComponentBufferBase, public MappedBuffer<T, dense>
	{
	private:
		std::vector<EntitySlice> m_slices;

	public:
		ComponentBuffer() {}
		ComponentBuffer(int bufferIndex, int initialSize = 1 << 10)
			: MappedBuffer<T, dense>(initialSize)
		{
			m_flag = uint64_t(1ULL << bufferIndex);
			m_sparse = !dense;
		}

		virtual void SetCapacity(size_t capacity) final
		{
			// if sparse
			MappedBuffer<T, dense>::SetCapacity(capacity);
		}

		void AddComponent(int handle, T component, EntityData& entity)
		{
			this->AddKey(handle, std::move(component));
			entity.m_flags |= m_flag;
		}

		void UpdateSlices(const std::vector<EntityData>& entities)
		{
			const auto& keys = this->m_keys;
			m_slices.clear();

			if(keys.empty()) return;

			EntitySlice slice = { entities[keys[0]].m_flags, 0, 0 };
			for(size_t i = 0; i < keys.size(); ++i)
				if(entities[keys[i]].m_flags != slice.m_prototype)
				{
					m_slices.push_back({ slice.m_prototype, slice.m_begin, i });
					slice = { entities[keys[i]].m_flags, i, 0 };
				}

			m_slices.push_back({ slice.m_prototype, slice.m_begin, keys.size() });
		}

		virtual void SortComponents(const std::vector<EntityData>& entities) override
		{
			auto greater = [&](uint32_t a, uint32_t b)
			{
				if(entities[a].m_flags == entities[b].m_flags)
					return a > b;
				return entities[a].m_flags > entities[b].m_flags;
			};
			quicksort(to_array(this->m_keys), to_array(this->m_data), this->m_indices, greater);
			this->UpdateSlices(entities);
		}

		virtual void SortComponents() override
		{
			quicksort(to_array(this->m_keys), to_array(this->m_data), this->m_indices);
		}

		virtual void RemoveComponent(uint32_t handle, EntityData& entity) override
		{
			this->RemoveKey(handle);
			entity.m_flags ^= m_flag;
		}

		std::vector<EntitySlice> slices(EntFlags prototype)
		{
			std::vector<EntitySlice> result;
			for(EntitySlice& slice : m_slices)
				if((slice.m_prototype & prototype) == prototype)
				{
					result.push_back(slice);
				}
			return result;
		}
	};
}