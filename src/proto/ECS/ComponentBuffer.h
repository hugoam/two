#pragma once

#include <proto/Forward.h>
#include <proto/ECS/ECS.h>

#include <vector>

namespace mud
{
	class ComponentBufferBase //: IDebugString
	{
	public:
		EntFlags m_flag;
		bool m_sparse;

		virtual void SetCapacity(size_t capacity) = 0;

		virtual void SortComponents(const std::vector<EntityData>& entities) = 0;
		virtual void SortComponents() = 0;
		virtual void RemoveComponent(uint32_t handle, EntityData& entity) = 0;
	};

	template <class T, class T_Buffer>
	class ComponentBuffer : public ComponentBufferBase, public T_Buffer
	{
	private:
		std::vector<EntitySlice> m_slices;

	public:
		ComponentBuffer() {}
		ComponentBuffer(int bufferIndex, int initialSize = 1 << 10)
			: T_Buffer(initialSize)
		{
			m_flag = uint64_t(1ULL << bufferIndex);
			m_sparse = T_Buffer::is_sparse;
		}

		virtual void SetCapacity(size_t capacity) final
		{
			// if sparse
			T_Buffer::SetCapacity(capacity);
		}

		void AddComponent(int handle, T component, EntityData& entity)
		{
			AddKey(handle, std::move(component));
			entity.m_flags |= m_flag;
		}

		void UpdateSlices(const std::vector<EntityData>& entities)
		{
			m_slices.clear();

			if(m_keys.empty()) return;

			EntitySlice slice = { entities[m_keys[0]].m_flags, 0, 0 };
			for(size_t i = 0; i < m_keys.size(); ++i)
				if(entities[m_keys[i]].m_flags != slice.m_prototype)
				{
					m_slices.push_back({ slice.m_prototype, slice.m_begin, i });
					slice = { entities[m_keys[i]].m_flags, i, 0 };
				}

			m_slices.push_back({ slice.m_prototype, slice.m_begin, m_keys.size() });
		}

		virtual void SortComponents(const std::vector<EntityData>& entities) override
		{
			auto greater = [&](uint32_t a, uint32_t b)
			{
				if(entities[a].m_flags == entities[b].m_flags)
					return a > b;
				return entities[a].m_flags > entities[b].m_flags;
			};
			quicksort(to_array(m_keys), to_array(m_data), m_indices, greater);
			this->UpdateSlices(entities);
		}

		virtual void SortComponents() override
		{
			quicksort(to_array(m_keys), to_array(m_data), m_indices);
		}

		virtual void RemoveComponent(uint32_t handle, EntityData& entity) override
		{
			RemoveKey(handle);
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

	template <class T>
	class ComponentBufferSparse : public ComponentBuffer<T, MappedBufferSparse<T>>
	{
	public:
		using ComponentBuffer<T, MappedBufferSparse<T>>::ComponentBuffer;
	};

	template <class T>
	class ComponentBufferDense : public ComponentBuffer<T, MappedBufferDense<T>>
	{
	public:
		using ComponentBuffer<T, MappedBufferDense<T>>::ComponentBuffer;
	};
}