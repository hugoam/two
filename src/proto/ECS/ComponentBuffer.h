#pragma once

#include <core/Forward.h>
#include <proto/ECS/ECS.h>

#include <vector>

using namespace mud; namespace toy
{
	struct ComponentMatcher
	{
		EntFlags m_flag;

		bool Matches(EntFlags flags) { return (flags & m_flag) != 0; }
	};

	class ComponentBufferBase //: IDebugString
	{
	public:
		Type* m_object_type;
		ComponentMatcher m_matcher;
		bool m_sparse;

		virtual void SetCapacity(size_t capacity) = 0;
		virtual int ComponentCount() = 0;

		bool HasComponentSlow(EntityData& entityData)
		{
			return (entityData.m_flags & m_matcher.m_flag) != 0;
		}

		virtual void RemoveComponent(EntIdx entIdx, EntityData& dataToSetFlags) = 0;
		virtual void UpdateEntIdx(int oldIdx, int newIdx) = 0;
		virtual void UpdateEntitiesIndices(std::vector<EntIdx> moveMap, std::vector<EntityData> sortedData) = 0;

		virtual string GetDebugString(bool detailed) = 0;
		struct DebugFlagAndEntIdxs { EntFlags flag; std::vector<EntIdx> endIdxs; };
		virtual DebugFlagAndEntIdxs GetDebugFlagAndEntIdxs() = 0;
		struct DebugBuffers { void* data; std::vector<int> i2; };
		virtual DebugBuffers GetDebugUntypedBuffers() = 0;
		virtual EntIdx GetDebugIdxFromKey(EntIdx key) = 0;
	};

	template <class T>
	class TypedComponentBufferBase : public ComponentBufferBase
	{
		virtual void AddComponent(int entIdx, T component, EntityData& dataToSetFlags) = 0;
		virtual void SortComponents() = 0;
		virtual void SortPrototypes(const std::vector<EntityData>& entities) = 0;
	};


	template <class T, class T_Buffer>
	class ComponentBuffer : public TypedComponentBufferBase<T>
	{
	private:
		T_Buffer m_buffer;

		std::vector<EntitySlice> m_slices;

	public:
		ComponentBuffer() {}
		ComponentBuffer(Type& type, int bufferIndex, int initialSize = 1 << 10)
			: m_buffer(initialSize)
		{
			m_object_type = &type;
			m_matcher = { EntFlags(1u << bufferIndex) };
			m_sparse = T_Buffer::is_sparse;
		}

		virtual void SetCapacity(size_t capacity) final
		{
			// if sparse
			m_buffer.SetCapacity(capacity);
		}

		virtual int ComponentCount() final { return m_buffer.m_count; }

		typename T_Buffer::Buffers __GetBuffers()
		{
			return m_buffer.__GetBuffers();
		}

		virtual void AddComponent(int entIdx, T component, EntityData& dataToSetFlags) override
		{
			m_buffer.AddKey(entIdx, component);
			dataToSetFlags.m_flags |= m_matcher.m_flag;
		}

		void ApplyMoves(const std::vector<int>& moves)
		{
			auto newData = std::vector<T>(m_buffer.m_data.size());

			for(auto i = 0; i < m_buffer.m_count; i++)
			{
				auto oldIndex = moves[i];
				newData[i] = m_buffer.m_data[oldIndex];
				m_buffer.m_keys_to_indices[m_buffer.m_keys[i]] = i;
			}

			//todo cache sorting array (GC-less)
			m_buffer.m_data = newData;
		}

		virtual void SortPrototypes(const std::vector<EntityData>& entities) override
		{
			auto mm = m_buffer.SortPrototypesAndGetMoves(entities);
			ApplyMoves(mm);
		}

		virtual void SortComponents() override
		{
			auto mm = m_buffer.SortKeysAndGetMoves();
			ApplyMoves(mm);
		}

		virtual void RemoveComponent(EntIdx entIdx, EntityData& dataToSetFlags) override
		{
			m_buffer.RemoveKey(entIdx);
			dataToSetFlags.m_flags ^= m_matcher.m_flag;
		}

		virtual void UpdateEntIdx(EntIdx oldIdx, EntIdx newIdx) override
		{
			m_buffer.UpdateKeyForEntry(oldIdx, newIdx);
		}

		// void Streamline(std::vector<int> refKeys)
		// {
		//     m_buffer.SortDataByKeyRef(refKeys);
		// }

		virtual void UpdateEntitiesIndices(std::vector<EntIdx> moveMap, std::vector<EntityData> sortedData) override
		{
			//movemap contains the EntIdx deltas
			std::vector<EntIdx> newCompsKeys = std::vector<EntIdx>(ComponentCount());
			std::vector<int> newCompsInds = std::vector<int>(ComponentCount());

			int c = 0;
			for(int i = 0; i < moveMap.size(); i++)
			{
				EntIdx entIdxInOldArr = moveMap[i];
				EntIdx entIdxInNewArr = i;

				if(m_matcher.Matches(sortedData[entIdxInNewArr].m_flags))
				{
					auto componentIndex = m_buffer.GetIndexFromKey(entIdxInOldArr);
					auto newKeyForCompIndex = entIdxInNewArr;

					newCompsKeys[c] = newKeyForCompIndex;
					newCompsInds[c] = componentIndex;

					c++;
				}
			}

			m_buffer.SetK2i(newCompsKeys, newCompsInds);
		}

		//#region Debug

		virtual string GetDebugString(bool detailed) //override
		{
			UNUSED(detailed); return "";
			//return
			//	$"  m_flag: {Convert.ToString((long)m_matcher.m_flag, 2).PadLeft(32, '0').Replace('0', '_').Replace('1', '■')}\n" +
			//	m_buffer.GetDebugString(detailed);
		}

		virtual typename TypedComponentBufferBase<T>::DebugFlagAndEntIdxs GetDebugFlagAndEntIdxs() override
		{
			return { m_matcher.m_flag, m_buffer.__GetBuffers().indices_to_keys };
		}

		virtual DebugBuffers GetDebugUntypedBuffers() override
		{
			return { m_buffer.m_data.data(), m_buffer.m_keys };
		}

		virtual int GetDebugIdxFromKey(EntIdx key) override
		{
			return m_buffer.GetIndexFromKey(key);
		}

		//#endregion
	};

	template <class T>
	class ComponentBufferSparse : public ComponentBuffer<T, MappedBufferSparse<T>>
	{
	public:
		using ComponentBuffer<T, MappedBufferSparse<T>>::ComponentBuffer;
	};

	template <class T>
	class ComponentBufferDense : public ComponentBuffer<T, MappedBufferDense<EntIdx, T>>
	{
	public:
		using ComponentBuffer<T, MappedBufferDense<EntIdx, T>>::ComponentBuffer;
	};
}