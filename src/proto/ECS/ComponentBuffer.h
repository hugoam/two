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

		void SortPrototypes(const std::vector<EntityData>& entities)
		{
			auto compare = [&](uint32_t a, uint32_t b) { return entities[a].m_flags < entities[b].m_flags; };
			//  quicksort(m_keys, m_data, m_indices);
		}

		void SortComponents()
		{
			quicksort(to_array(m_keys), to_array(m_data), m_indices);
		}

		virtual void RemoveComponent(uint32_t handle, EntityData& entity) override
		{
			RemoveKey(handle);
			entity.m_flags ^= m_flag;
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