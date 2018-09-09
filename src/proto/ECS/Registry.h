#pragma once

#include <infra/Vector.h>
#include <obj/Type.h>
#include <core/Forward.h>
#include <core/ECS/ECS.h>
#include <core/ECS/MappedBuffers.h>
#include <core/ECS/MappedBufferDense.h>
#include <core/ECS/MappedBufferSparse.h>
#include <core/ECS/ComponentBuffer.h>

#include <memory>
#include <tuple>
#include <functional>
#include <map>

namespace toy
{
	template<class F, class... Types, std::size_t... Indices>
	void for_each(std::tuple<Types...>& tuple, F func, std::index_sequence<Indices...>)
	{
		using expander = int[];
		(void)expander {
			0, ((void)func(std::get<Indices>(tuple)), 0)...
		};
	}

	template<class F, class... Types>
	void for_each(std::tuple<Types...>& tuple, F func)
	{
		for_each(tuple, func, std::make_index_sequence<sizeof...(Types)>());
	}

	enum class BufferType
	{
		/// Fast to loop, but uses more memory (32KiB per 1024 entities). Use for common components (e.g. position).
		Sparse,
		/// Slow to loop, but uses less memory. Best suited for uncommon components (added to less than 1/20 of entities).
		Dense,
	};

	template <class T_Self, class... T_Args>
	class BufferRegistry
	{
	public:
		std::tuple<T_Args...> m_buffers;

		void Visit(std::function<void(ComponentBufferBase&)> visit)
		{
			for_each(m_buffers, [&](auto& buffer)
			{
				visit(buffer);
			});
		}

		void VisitMatches(EntityData& entity, std::function<void(ComponentBufferBase&)> visitor)
		{
			for_each(m_buffers, [&](auto& buffer)
			{
				if(buffer.m_matcher.Matches(entity.m_flags))
					visitor(buffer);
			});
		}

		template <class T>
		auto& GetBufferSlow()
		{
			return std::get<T_Self::buffer_index<T>()>(m_buffers);
		}

		string GetDebugString(bool detailed = false)
		{
			string s = "Registered Component Buffers:\n";
			for(auto i = 0; i < m_dense_count; i++)
			{
				const ComponentBufferBase& matcher = *m_dense_buffers[i];
				//s += $" {matcher.GetType().GenericTypeArguments[0].Name}";
				if(detailed)
				{
					//	s += $"\n {matcher.GetDebugString(false)}\n";
				}
			}

			return s;
		}
	};

	template <class T_Buffers>
	class EntityRegistry
	{
	private:
		T_Buffers m_buffers;
		//    public TagsManager TagsManager = new TagsManager();
		 
		std::vector<EntityData> m_entities;
		std::vector<EntIdx> m_available;

	public:
		EntityRegistry(int capacity = 1 << 10)
		{
			m_entities.reserve(capacity);
		}

		void UpdateSize()
		{
			m_buffers.Visit([&](ComponentBufferBase& buffer)
			{
				buffer.SetCapacity(m_entities.size());
			});
		}

		EntIdx CreateEntity(EntTags tags = 0)
		{
			if(m_available.size() > 0)
				return vector_pop(m_available);
			EntIdx id = m_entities.size();
			m_entities.push_back({});
			UpdateSize();
			return id;
		}

		void UpdateEntityIndex(EntityData& entityData, EntIdx oldIdx, EntIdx newIdx)
		{
			m_buffers.VisitMatches(entityData, [&](ComponentBufferBase& buffer)
			{
				buffer.UpdateEntIdx(oldIdx, newIdx);
			});
		}

		void RemoveAllComponents(EntIdx entIdx, EntityData& entityData)
		{
			m_buffers.VisitMatches(entityData, [&](ComponentBufferBase& buffer)
			{
				buffer.RemoveComponent(entIdx, entityData);
			});
		}

		void DeleteEntity(EntIdx id)
		{
			EntityData& entData = m_entities[id];
			RemoveAllComponents(entIdx, entData);
			m_available.push_back(id);
		}

		// no need to sort entities, we only sort component buffers according on 
#if 0
		void UpdateEntityIndices(std::vector<int> mm, std::vector<EntityData> entData)
		{
			m_buffers.Visit([&](ComponentBufferBase& buffer)
			{
				buffer.UpdateEntitiesIndices(mm, entData);
			});
		}

		void SortEntities()
		{
			auto moves = SortDataApplyKeysAndGetMoves();

			//todo cache sorting array (GC-less) / non-critical - offline

			UpdateEntityIndices(moves, m_data);
			// ( ͡~ ͜ʖ ͡°)
		}
#endif

#if 0
		template <class T>
		void RegisterComponent(BufferType bufferType, int initialSize = 1 << 10)
		{
			m_buffers.CreateComponentBuffer<T>(initialSize, bufferType, *this);
		}
#endif

		template <class T>
		void AddComponent(EntIdx id, T component = default)
		{
			EntityData& entData = m_entities[id];
			auto buffer = m_buffers.GetBufferSlow<T>();
			buffer.AddComponent(id, component, entData);
		}

		template <class T>
		void RemoveComponent(EntIdx id)
		{
			EntityData& entData = m_entities[id];
			auto buffer = m_buffers.GetBufferSlow<T>();
			buffer.RemoveComponent(entIdx, entData);
		}

		// void RemoveAllComponents(EntIdx id)
		// {
		//     EntIdx entIdx = GetIndexFromKey(id);
		//     ref EntityData entData = ref GetDataFromIndex(entIdx);
		//     m_buffers.RemoveAllComponents(entIdx, entData.Flags);
		//     entData.Flags = 0;
		// }

		template <class T>
		void SortComponents()
		{
			m_buffers.GetBufferSlow<T>().SortComponents();
		}

		// public void StreamlineComponents<TModel, TStream>() where TModel : struct  where TStream : struct
		// {
		//     auto modelBuf = m_buffers.GetBufferSlow<TModel>();
		//     auto bufToStreamline = m_buffers.GetBufferSlow<TStream>();
		//     if (modelBuf.m_sparse && bufToStreamline.m_sparse)
		//     {
		//         auto castBuf = (ComponentBufferSparse<TModel>) modelBuf;
		//         auto castBufTS = (ComponentBufferSparse<TStream>) bufToStreamline;
		//
		//         castBufTS.Streamline(castBuf.__GetBuffers().entIdx2i);
		//     }
		//     else
		//     {
		//         throw new NotImplementedException("Streamlining dense buffers is not currently supported - it probably never makes sense");
		//     }
		// }

		//#region Debug

#if 0
		string GetEntityDebugData(EntIdx id)
		{
			/*return $"Entity Debug Data: UID: {id}, Idx: {GetIndexFromKey(id)}\n" +
				$" FlagsD:{Convert.ToString((long)GetDataFromKey(id).m_flags, 2).PadLeft(32, '0').Replace('0', '_').Replace('1', '■')}\n" +
				$" FlagsS:{Convert.ToString((long)GetDataFromKey(id).m_flags, 2).PadLeft(32, '0').Replace('0', '_').Replace('1', '■')}\n" +
				$" m_tags:  {Convert.ToString((long)GetDataFromKey(id).m_tags, 2).PadLeft(32, '0').Replace('0', '_').Replace('1', '■')}\n" +
				$" Components: {string.Join(", ", m_buffers.MatchersFromFlagsSlow(GetDataFromKey(id)).Select(x => x.GetType().GenericTypeArguments[0].Name))}"
				;*/
		}

		string GetDebugString(bool detailed = false) override
		{
			string s = "";
			//	$"Entity count: {m_count}, UID Dict Entries: {KeysToIndicesDebug.m_count}, Component Buffers: {m_buffers.m_dense_count}";
			if(detailed)
			{
				s += "\n";
				for(auto pair : KeysToIndicesDebug)
					s += GetEntityDebugData(pair.Key) + "\n";
				s += "\n";
			}
			return s;
		}

		std::vector<ComponentBufferBase*> GetDebugComponentBufferBases()
		{
			return m_buffers.MatchersFromFlagsSlow(EntityData(UINT64_MAX, UINT64_MAX));
		}

		using DebugLoopDelegate = std::function<void(int entIdx, std::map<ComponentBufferBase*, int> buffersIndices)>;
		void DebugLoop(DebugLoopDelegate func, std::vector<string> compNames) //no variadic templates so we use a hack
		{
			std::vector<ComponentBufferBase> compBuffers = std::vector<ComponentBufferBase>(compNames.size());

			for(auto i = 0; i < compNames.size(); i++)
			{
				string compName = compNames[i];
				auto compType = Type.GetType(compName);
				auto buffer = m_buffers.GetType().GetMethod("GetBufferSlow").MakeGenericMethod(compType).Invoke(m_buffers, new object[0]);
				compBuffers[i] = (ComponentBufferBase)buffer;
			}

			for(auto i = compBuffers[0].ComponentCount - 1; i >= 0; i--)
			{
				auto comp = compBuffers[0].GetDebugUntypedBuffers();
				EntIdx entIdx = comp.i2k[i];
				EntityData& entityData = m_entities[entIdx];

				auto indsDict = std::map<ComponentBufferBase*, int>();
				indsDict[&compBuffers[0]] = i;

				for(int j = 1; j < compBuffers.size(); j++)
				{
					if(compBuffers[j].HasComponentSlow(entityData))
					{
						int indexInBuf = compBuffers[j].GetDebugIdxFromKey(entIdx);
						indsDict[&compBuffers[j]] = indexInBuf;
					}
					else
						break;

					if(j == compBuffers.size() - 1)
					{
						func(entIdx, indsDict);
					}
				}
			}
		}
#endif
		//#endregion

		//TODO filter loops by tag too
		//TODO in loop, sort buffers by entries count NOT VIABLE

		//TODO signatures:
		//            * prefiltertags, action
		//              prefiltertags, action, postfilterexcludetags
		//              prefiltertags, action, postfilterexcludecomponents
		//              prefiltertags, action, postfilterexcludetags, postfilterexcludecomponents
		//              action, postfilterexcludetags, postfilterexcludecomponents
		//              action, postfilterexcludecomponents

		enum CollectionType
		{
			Dictionary, Array
		};

		template <class T0>
		using ProcessComponent0 = std::function<void(int entIdx, T0& component0)>;

		template <class T0, class T1>
		using ProcessComponent1 = std::function<void(int entIdx, T0& component0, T1& component1)>;

		template <class T0, class T1, class T2>
		using ProcessComponent2 = std::function<void(int entIdx, T0& component0, T1& component1, T2& component2)>;

		template <class T0, class T1, class T2, class T3>
		using ProcessComponent3 = std::function<void(int entIdx, T0& component0, T1& component1, T2& component2, T3& component3)>;

#if 0
		struct CustomLoopReturn {
			std::vector<EntityData> entityData;
			std::vector<EntIdx> buf0Idx2EntIdx; T0[] buf0Data; object EntIdx2buf0Idx; CollectionType EntIdx2buf0IdxType;
			std::vector<EntIdx> buf1Idx2EntIdx; T1[] buf1Data; object EntIdx2buf1Idx; CollectionType EntIdx2buf1IdxType;
		};
		public
			(
				
				)
			CustomLoop<T0, T1>()
		{
			throw new NotImplementedException();
		}
#endif

#if 0
		template <class T0, class T1>
		void Loop(EntTags preFilterTags, ProcessComponent1<T0, T1> loopAction)
		{
			ushort typeMask = 0;

			auto t0Base = m_buffers.GetBufferSlow<T0>();
			if(t0Base.m_sparse) typeMask |= 1 << 0;

			auto t1Base = m_buffers.GetBufferSlow<T1>();
			if(t1Base.m_sparse) typeMask |= 1 << 1;

			switch(typeMask)
			{
			case 0b_0000_0000_0000_0000:
				Loop00(preFilterTags, loopAction,
					(ComponentBufferDense<T0>)t0Base,
					(ComponentBufferDense<T1>)t1Base
				); return;
			}

		}

		template <class T0, class T2>
		void Loop00<T1, T2>(EntTags preFilterTags,
			ProcessComponent<T1, T2> loopAction,
			ComponentBufferDense<T1> t1B, ComponentBufferDense<T2> t2B
			)
		where T1 : struct where T2 : struct
		{
			auto compBuffers = t1B.__GetBuffers();
			auto compIdx2EntIdx = compBuffers.indices_to_keys;
			auto components = compBuffers.data;

			auto matcher2Flag = t2B.m_matcher.m_flag;
			auto matcher2Buffers = t2B.__GetBuffers();
			for(auto i = components.size() - 1; i >= 0; i--)
			{
				T1& component = components[i];
				EntIdx entIdx = compIdx2EntIdx[i];
				EntityData& entityData = m_entities[entIdx];
				if((entityData.m_flags & matcher2Flag) != 0)
				{
					int indexInMatcher2 = matcher2Buffers.entIdx2i[entIdx];
					T2& component2 = matcher2Buffers.data[indexInMatcher2];
					loopAction(entIdx, component, component2);
				}
			}
		}
#endif

		using ushort = uint16_t;

		template <class T0>
		void Loop(ProcessComponent0<T0> loopAction)
		{
			auto t0Base = m_buffers.GetBufferSlow<T0>();
			auto compBuffers = t0B.__GetBuffers();
			auto lastCompIndex = t0B.ComponentCount - 1;
			auto compIdx2EntIdx = compBuffers.indices_to_keys;
			auto components = compBuffers.data;
			for(auto i = lastCompIndex; i >= 0; i--)
			{
				T0& component0 = components[i];
				EntIdx entIdx = compIdx2EntIdx[i];
				EntityData& entityData = m_entities[entIdx];
				loopAction(entIdx, component0);
			}
		}

		template <class T0, class T1>
		void Loop(ProcessComponent1<T0, T1> loopAction)
		{
			auto& t0B = m_buffers.GetBufferSlow<T0>();
			auto& t1B = m_buffers.GetBufferSlow<T1>();
			auto compBuffers = t0B.__GetBuffers();
			auto lastCompIndex = t0B.ComponentCount() - 1;
			auto compIdx2EntIdx = compBuffers.indices_to_keys;
			auto components = compBuffers.data;
			auto matcher1Flag = t1B.m_matcher.m_flag;
			auto matcher1Buffers = t1B.__GetBuffers();
			for(auto i = lastCompIndex; i >= 0; i--)
			{
				EntIdx entIdx = compIdx2EntIdx[i];
				EntityData& entityData = m_entities[entIdx];

				if((entityData.m_flags & matcher1Flag) != 0)
				{
					T0& component0 = components[i];
					int indexInMatcher1 = matcher1Buffers.keys_to_indices[entIdx];
					T1& component1 = matcher1Buffers.data[indexInMatcher1];
					loopAction(entIdx, component0, component1);
				}
			}
		}


		template <class T0, class T1, class T2>
		void Loop(ProcessComponent2<T0, T1, T2> loopAction)
		{
			auto t0Base = m_buffers.GetBufferSlow<T0>();
			auto t1Base = m_buffers.GetBufferSlow<T1>();
			auto t2Base = m_buffers.GetBufferSlow<T2>();
			auto compBuffers = t0B.__GetBuffers();
			auto lastCompIndex = t0B.ComponentCount() - 1;
			auto compIdx2EntIdx = compBuffers.indices_to_keys;
			auto components = compBuffers.data;
			auto matcher1Flag = t1B.m_matcher.m_flag;
			auto matcher1Buffers = t1B.__GetBuffers();
			auto matcher2Flag = t2B.m_matcher.m_flag;
			auto matcher2Buffers = t2B.__GetBuffers();
			for(auto i = lastCompIndex; i >= 0; i--)
			{
				EntIdx entIdx = compIdx2EntIdx[i];
				EntityData& entityData = m_entities[entIdx];

				if((entityData.m_flags & matcher1Flag) != 0
				&& (entityData.m_flags & matcher2Flag) != 0)
				{
					T0& component0 = components[i];
					int indexInMatcher1 = matcher1Buffers.keys_to_indices[entIdx];
					T1& component1 = matcher1Buffers.data[indexInMatcher1];
					int indexInMatcher2 = matcher2Buffers.keys_to_indices[entIdx];
					T2& component2 = matcher2Buffers.data[indexInMatcher2];
					loopAction(entIdx, component0, component1, component2);
				}
			}
		}

		template <class T0, class T1, class T2, class T3>
		void Loop(ProcessComponent3<T0, T1, T2, T3> loopAction)
		{
			auto t0Base = m_buffers.GetBufferSlow<T0>();
			auto t1Base = m_buffers.GetBufferSlow<T1>();
			auto t2Base = m_buffers.GetBufferSlow<T2>();
			auto t3Base = m_buffers.GetBufferSlow<T3>();
			auto compBuffers = t0B.__GetBuffers();
			auto lastCompIndex = t0B.ComponentCount() - 1;
			auto compIdx2EntIdx = compBuffers.indices_to_keys;
			auto components = compBuffers.data;

			auto matcher1Flag = t1B.m_matcher.m_flag;
			auto matcher1Buffers = t1B.__GetBuffers();
			auto matcher2Flag = t2B.m_matcher.m_flag;
			auto matcher2Buffers = t2B.__GetBuffers();
			auto matcher3Flag = t3B.m_matcher.m_flag;
			auto matcher3Buffers = t3B.__GetBuffers();

			for(auto i = lastCompIndex; i >= 0; i--)
			{
				EntIdx entIdx = compIdx2EntIdx[i];
				EntityData& entityData = m_entities[entIdx];

				if((entityData.m_flags & matcher1Flag) != 0
				&& (entityData.m_flags & matcher2Flag) != 0
				&& (entityData.m_flags & matcher3Flag) != 0)
				{
					T0& component0 = components[i];
					int indexInMatcher1 = matcher1Buffers.keys_to_indices[entIdx];
					T1& component1 = matcher1Buffers.data[indexInMatcher1];
					int indexInMatcher2 = matcher2Buffers.keys_to_indices[entIdx];
					T2& component2 = matcher2Buffers.data[indexInMatcher2];
					int indexInMatcher3 = matcher3Buffers.keys_to_indices[entIdx];
					T3& component3 = matcher3Buffers.data[indexInMatcher3];
					loopAction(entIdx, component0, component1, component2, component3);
				}
			}
		}
	};
}