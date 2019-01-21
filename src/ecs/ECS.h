
#pragma once

#include <cstdint>
#include <stl/memory.h>
#include <stl/map.h>
#include <stl/tuple.h>
#include <infra/Vector.h>
#include <type/Type.h>
#include <type/Ref.h>
#include <ecs/Forward.h>
#include <ecs/Entity.h>
#include <ecs/ComponentBuffer.h>

namespace mud
{
	struct EntityData
	{
		uint64_t m_prototype = 0;
		uint16_t m_stream = 0;

		EntityData() {}
		EntityData(uint64_t prototype, uint16_t stream) : m_prototype(prototype), m_stream(stream) {}
		
		bool operator<(EntityData& other) const { return m_prototype < other.m_prototype; }
	};
	
	template <typename F, typename... Ts>
	void for_each(F&& f, Ts&&... xs)
	{
		swallow{ (f(static_cast<Ts&&>(xs)), 0)... };
	}

	template <typename... Ts>
	uint64_t any_flags(Ts... xs)
	{
		uint64_t flags = false;
		for_each([&flags](uint64_t x) { flags = flags | x; }, xs...);
		return flags;
	}

	enum class BufferType
	{
		/// Fast to loop, but uses more memory (32KiB per 1024 entities). Use for common components (e.g. position).
		Sparse,
		/// Slow to loop, but uses less memory. Best suited for uncommon components (added to less than 1/20 of entities).
		Dense,
	};

	template <class T>
	struct TypedBuffer
	{};

	template <class T>
	class ComponentArray
	{
	public:
		size_t size() const { return m_components.size(); }

		T& operator[](size_t index) { return *m_components[index]; }
		const T& operator[](size_t index) const { return *m_components[index]; }

		vector<T*> m_components;
	};

	//template <bool Dense>
	class ParallelBuffers
	{
	public:
		ParallelBuffers(cstring name, size_t size = 0)
			: m_name(name)
			, m_indices(size)
			, m_buffer_map(64)
		{
			m_handles.reserve(size);
		}

		ParallelBuffers(ParallelBuffers&& other) = default;
		ParallelBuffers& operator=(ParallelBuffers&& other) = default;

		ParallelBuffers(const ParallelBuffers& other) = delete;
		ParallelBuffers& operator=(const ParallelBuffers& other) = delete;

		template <class T>
		void AddBuffer()
		{
#ifdef MUD_ECS_TYPED
			m_buffers.emplace_back(make_unique<ComponentBuffer<T>>(type<T>(), int(TypedBuffer<T>::index()), int(m_handles.capacity())));
#else
			m_buffers.emplace_back(make_unique<ComponentBuffer<T>>(int(TypedBuffer<T>::index()), int(m_handles.capacity())));
#endif
			m_buffer_map[TypedBuffer<T>::index()] = &(*m_buffers.back());
		}

		template <class... T_Components>
		void AddBuffers()
		{
			m_prototype = any_flags(1ULL << TypedBuffer<T_Components>::index()...);
			swallow{ (AddBuffer<T_Components>(), 0)... };
		}

		template <class T>
		ComponentBuffer<T>& Buffer()
		{
			return static_cast<ComponentBuffer<T>&>(*m_buffer_map[TypedBuffer<T>::index()]);
		}

		void SortComponents()
		{
			for(auto& buffer : m_buffers)
				buffer->SortComponents();
		}

		void SetCapacity(size_t capacity)
		{
			m_indices.ensure(capacity);
		}

		void Clear()
		{
			for(auto& buffer : m_buffers)
				buffer->Clear();

			m_handles.clear();
			m_indices.clear();
		}

		void Add(uint32_t handle)
		{
			const uint32_t index = uint32_t(m_handles.size());

			for(auto& buffer : m_buffers)
				buffer->Add();

			m_handles.push_back(handle);
			m_indices[handle] = index;
		}

		void Remove(uint32_t handle)
		{
			const uint32_t index = m_indices[handle];

			for(auto& buffer : m_buffers)
				buffer->Remove(index);

			swap(m_handles[index], m_handles.back());
			m_handles.pop_back();

			const uint32_t moved = m_handles[index];
			m_indices[moved] = index;
			m_indices.erase(handle);
		}

		template <class T>
		void Set(uint32_t handle, T component = T())
		{
			size_t index = m_indices[handle];
			this->Buffer<T>().m_data[index] = move(component);
		}

		template <class T>
		T& Get(uint32_t handle)
		{
			size_t index = m_indices[handle];
			return this->Buffer<T>().m_data[index];
		}

		cstring m_name;
		uint64_t m_prototype;

		//SparseIndices<Dense> m_indices;
		SparseIndices<false> m_indices;
		vector<uint32_t> m_handles;

		vector<unique<ComponentBufferBase>> m_buffers;
		vector<ComponentBufferBase*> m_buffer_map;
	};

	class ECS
	{
	public:
		uint32_t m_index = 0;

		vector<ParallelBuffers> m_buffers;
		map<uint64_t, uint16_t> m_streams;

		vector<EntityData> m_entities;
		vector<uint32_t> m_available;

	public:
		ECS(int capacity = 1 << 10)
		{
			m_buffers.reserve(64);
			m_entities.reserve(capacity);
		}

		ECS(const ECS& other) = delete;
		ECS& operator=(const ECS& other) = delete;

		template <class... T_Components>
		ParallelBuffers& Stream()
		{
			uint64_t prototype = any_flags(1ULL << TypedBuffer<T_Components>::index()...);
			uint16_t stream = m_streams[prototype];
			return m_buffers[stream];
		}

		ParallelBuffers& Stream(uint32_t handle)
		{
			uint16_t stream = m_entities[handle].m_stream;
			return m_buffers[stream];
		}

		vector<ParallelBuffers*> Match(uint64_t prototype)
		{
			vector<ParallelBuffers*> matches;
			for(ParallelBuffers& buffers : m_buffers)
				if((buffers.m_prototype & prototype) == prototype)
					matches.push_back(&buffers);
			return matches;
		}

		template <class... T_Components>
		void AddBuffers(cstring name)
		{
			uint64_t prototype = any_flags(1ULL << TypedBuffer<T_Components>::index()...);
			m_streams[prototype] = uint16_t(m_buffers.size());
			m_buffers.emplace_back(name);
			m_buffers.back().AddBuffers<T_Components...>();
		}

		void UpdateSize()
		{
			for(auto& buffer : m_buffers)
				buffer.SetCapacity(m_entities.size());
		}

		uint32_t AllocEntity(uint64_t prototype, uint16_t stream)
		{
			if(m_available.size() > 0)
				return vector_pop(m_available);
			uint32_t handle = uint32_t(m_entities.size());
			m_entities.push_back({ prototype, stream });
			this->UpdateSize();
			return handle;
		}

		template <class... T_Components>
		uint32_t CreateEntity()
		{
			uint64_t prototype = any_flags(1ULL << TypedBuffer<T_Components>::index()...);
			if(m_streams.find(prototype) == m_streams.end())
				this->AddBuffers<T_Components...>("Todo");
			uint16_t stream = m_streams[prototype];
			uint32_t handle = AllocEntity(prototype, stream);
			m_buffers[stream].Add(handle);
			return handle;
		}

		void DeleteEntity(uint32_t handle)
		{
			EntityData& entity = m_entities[handle];
			m_buffers[entity.m_stream].Remove(handle);
			m_available.push_back(handle);
		}

		template <class T>
		void SetComponent(uint32_t handle, T component = T())
		{
			EntityData& entity = m_entities[handle];
			m_buffers[entity.m_stream].Set<T>(handle, move(component));
		}

		template <class T>
		bool HasComponent(uint32_t handle)
		{
			uint64_t flag = (1ULL << TypedBuffer<T>::index());
			EntityData& entity = m_entities[handle];
			return (entity.m_prototype & flag) != 0;
		}

		template <class T>
		T& GetComponent(uint32_t handle)
		{
			EntityData& entity = m_entities[handle];
			return m_buffers[entity.m_stream].Get<T>(handle);
		}

		void SortComponents()
		{
			for(ParallelBuffers& buffers : m_buffers)
				buffers.SortComponents();
		}

		template <class T, class... T_Components>
		ComponentArray<T> Components()
		{
			uint64_t prototype = (1ULL << TypedBuffer<T>::index()) | any_flags(1ULL << TypedBuffer<T_Components>::index()...);
		
			ComponentArray<T> result;

			vector<ParallelBuffers*> matches = this->Match(prototype);
			for(ParallelBuffers* buffers : matches)
			{
				ComponentBuffer<T>& buffer = buffers->Buffer<T>();

				size_t count = buffer.m_data.size();
				size_t size = result.m_components.size();
				result.m_components.reserve(size + count);

				for(size_t i = 0; i < count; ++i)
					result.m_components.push_back(&buffer.m_data[size + i]);
			}

			return result;
		}

		template <class... Ts, size_t... Is, class T_Function>
		void LoopHImpl(T_Function action, index_sequence<Is...>)
		{
			uint64_t prototype = any_flags(1ULL << TypedBuffer<Ts>::index()...);

			vector<ParallelBuffers*> matches = this->Match(prototype);
			for(ParallelBuffers* stream : matches)
			{
				tuple<ComponentBuffer<Ts>&...> buffers = { stream->Buffer<Ts>()... };

				const size_t size = stream->m_handles.size();
				for(size_t i = 0; i < size; ++i)
				{
					uint32_t handle = stream->m_handles[i];
					action(handle, at<Is>(buffers).m_data[i]...);
				}
			}
		}

		template <class... Ts, size_t... Is, class T_Function>
		void LoopImpl(T_Function action, index_sequence<Is...>)
		{
			uint64_t prototype = any_flags(1ULL << TypedBuffer<Ts>::index()...);

			vector<ParallelBuffers*> matches = this->Match(prototype);
			for(ParallelBuffers* stream : matches)
			{
				tuple<ComponentBuffer<Ts>&...> buffers = { stream->Buffer<Ts>()... };

				const size_t size = stream->m_handles.size();
				for(size_t i = 0; i < size; ++i)
				{
					action(at<Is>(buffers).m_data[i]...);
				}
			}
		}

		template <class... Ts, class T_Function>
		void Loop(T_Function action)
		{
			this->LoopImpl<Ts...>(action, index_tuple<sizeof...(Ts)>());
		}

		template <class... Ts, class T_Function>
		void LoopH(T_Function action)
		{
			this->LoopHImpl<Ts...>(action, index_tuple<sizeof...(Ts)>());
		}
	};

	export_ extern MUD_ECS_EXPORT ECS* s_ecs[256];

	export_ template <class T>
	inline bool isa(const Entity& entity) { return s_ecs[entity.m_ecs]->HasComponent<T>(entity.m_handle); }

	export_ template <class T>
	inline T& asa(const Entity& entity) { return s_ecs[entity.m_ecs]->GetComponent<T>(entity.m_handle); }

	export_ template <class T>
	inline T* try_asa(const Entity& entity) { if(entity && isa<T>(entity)) return &asa<T>(entity); else return nullptr; }
	
	export_ template <class T>
	inline T* try_asa(const Entity* entity) { if(entity && isa<T>(*entity)) return &asa<T>(*entity); else return nullptr; }

#ifdef MUD_ECS_TYPED
	struct EntityRef {};

	export_ template <> MUD_ECS_EXPORT Type& type<EntityRef>();

	inline Ref ent_ref(uint32_t entity) { return Ref((void*)uintptr_t(entity), type<EntityRef>()); }
	inline uint32_t as_ent(const Ref& ref) { return ref.m_type->is<EntityRef>() ? uint32_t((uintptr_t)ref.m_value) : UINT32_MAX; }
#endif

	inline cstring entity_prototype(const Entity& entity)
	{
		ParallelBuffers& stream = s_ecs[entity.m_ecs]->Stream(entity.m_handle);
		return stream.m_name;
	}

	template <class T>
	struct refl_ struct_ ComponentHandle : public Entity
	{
		ComponentHandle() {}
		ComponentHandle(uint32_t handle, uint32_t stream) : Entity(handle, stream) {}
		ComponentHandle(const Entity& entity) : Entity(entity) {}

		operator T&() { return asa<T>(*this); }
		operator const T&() const { return asa<T>(*this); }
		T* operator->() { return &asa<T>(*this); }
		T& operator*() { return asa<T>(*this); }
		const T* operator->() const { return &asa<T>(*this); }
		const T& operator*() const { return asa<T>(*this); }
	};

	template <class T>
	struct refl_ struct_ nocopy_ EntityHandle : public ComponentHandle<T>
	{
		EntityHandle() {}
		EntityHandle(uint32_t handle, uint32_t stream) : ComponentHandle<T>(handle, stream) {}
		~EntityHandle() { this->destroy(); }

		EntityHandle(EntityHandle<T>& other) = delete;
		EntityHandle& operator=(EntityHandle<T>& other) = delete;

		EntityHandle(EntityHandle<T>&& other) { other.swap(*this); }
		EntityHandle& operator=(EntityHandle<T>&& other) { other.swap(*this); return *this; }

		operator Entity() const { return { this->m_handle, this->m_stream }; }
	};
}