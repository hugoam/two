#pragma once

#include <infra/Vector.h>
#include <ecs/Forward.h>
#include <ecs/ECS.h>
#include <ecs/ComponentBuffer.h>

#include <memory>
#include <functional>
#include <map>

namespace mud
{
	template <typename F, typename... Ts>
	void for_each(F&& f, Ts&&... xs)
	{
		swallow{ (f(std::forward<Ts>(xs)), 0)... };
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

		std::vector<T*> m_components;
	};

	//template <bool Dense>
	class ParallelBuffers
	{
	public:
		ParallelBuffers(size_t size = 0)
			: m_buffer_map(64)
			, m_indices(size)
		{
			m_handles.reserve(size);
		}

		template <class T>
		void AddBuffer()
		{
			m_buffers.emplace_back(std::make_unique<ComponentBuffer<T>>(int(TypedBuffer<T>::index())));
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

			std::swap(m_handles[index], m_handles.back());
			m_handles.pop_back();

			const uint32_t moved = m_handles[index];
			m_indices[moved] = index;
			m_indices.erase(handle);
		}

		template <class T>
		void Set(uint32_t handle, T component = T())
		{
			size_t index = m_indices[handle];
			this->Buffer<T>().m_data[index] = std::move(component);
		}

		template <class T>
		T& Get(uint32_t handle)
		{
			size_t index = m_indices[handle];
			return this->Buffer<T>().m_data[index];
		}

		EntFlags m_prototype;

		//SparseIndices<Dense> m_indices;
		SparseIndices<false> m_indices;
		std::vector<uint32_t> m_handles;

		std::vector<std::unique_ptr<ComponentBufferBase>> m_buffers;
		std::vector<ComponentBufferBase*> m_buffer_map;
	};

	class EntityRegistry
	{
	public:
		std::vector<ParallelBuffers> m_buffers;
		std::map<EntFlags, uint16_t> m_streams;

		std::vector<EntityData> m_entities;
		std::vector<uint32_t> m_available;

	public:
		EntityRegistry(int capacity = 1 << 10)
		{
			m_buffers.reserve(64);
			m_entities.reserve(capacity);
		}

		std::vector<ParallelBuffers*> Match(EntFlags prototype)
		{
			std::vector<ParallelBuffers*> matches;
			for(ParallelBuffers& buffers : m_buffers)
				if((buffers.m_prototype & prototype) == prototype)
					matches.push_back(&buffers);
			return matches;
		}

		template <class... T_Components>
		void AddBuffers()
		{
			EntFlags prototype = any_flags(1ULL << TypedBuffer<T_Components>::index()...);
			m_streams[prototype] = uint16_t(m_buffers.size());
			m_buffers.emplace_back();
			m_buffers.back().AddBuffers<T_Components...>();
		}

		void UpdateSize()
		{
			for(auto& buffer : m_buffers)
				buffer.SetCapacity(m_entities.size());
		}

		uint32_t AllocEntity(EntFlags prototype, uint16_t stream)
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
			EntFlags prototype = any_flags(1ULL << TypedBuffer<T_Components>::index()...);
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
			m_buffers[entity.m_stream].Set<T>(handle, std::move(component));
		}

		template <class T>
		bool HasComponent(uint32_t handle)
		{
			EntFlags flag = (1ULL << TypedBuffer<T>::index());
			EntityData& entity = m_entities[handle];
			return (entity.m_flags & flag) != 0;
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
			EntFlags prototype = (1ULL << TypedBuffer<T>::index()) | any_flags(1ULL << TypedBuffer<T_Components>::index()...);
		
			ComponentArray<T> result;

			std::vector<ParallelBuffers*> matches = this->Match(prototype);
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

		template <class T0, class T_Function>
		void Loop(T_Function action)
		{
			EntFlags prototype = (1ULL << TypedBuffer<T0>::index());

			std::vector<ParallelBuffers*> matches = this->Match(prototype);
			for(ParallelBuffers* buffers : matches)
			{
				ComponentBuffer<T0>& buffer0 = buffers->Buffer<T0>();

				for(size_t i = 0; i < buffer0.m_data.size(); ++i)
				{
					uint32_t handle = buffers->m_handles[i];
					T0& component0 = buffer0.m_data[i];
					action(handle, component0);
				}
			}
		}

		template <class T0, class T1, class T_Function>
		void Loop(T_Function action)
		{
			EntFlags prototype = (1ULL << TypedBuffer<T0>::index()) | (1ULL << TypedBuffer<T1>::index());

			std::vector<ParallelBuffers*> matches = this->Match(prototype);
			for(ParallelBuffers* buffers : matches)
			{
				ComponentBuffer<T0>& buffer0 = buffers->Buffer<T0>();
				ComponentBuffer<T1>& buffer1 = buffers->Buffer<T1>();

				for(size_t i = 0; i < buffer0.m_data.size(); ++i)
				{
					uint32_t handle = buffers->m_handles[i];
					T0& component0 = buffer0.m_data[i];
					T1& component1 = buffer1.m_data[i];
					action(handle, component0, component1);
				}
			}
		}

		template <class T0, class T1, class T2, class T_Function>
		void Loop(T_Function action)
		{
			EntFlags prototype = (1ULL << TypedBuffer<T0>::index()) | (1ULL << TypedBuffer<T1>::index()) | (1ULL << TypedBuffer<T2>::index());

			std::vector<ParallelBuffers*> matches = this->Match(prototype);
			for(ParallelBuffers* buffers : matches)
			{
				ComponentBuffer<T0>& buffer0 = buffers->Buffer<T0>();
				ComponentBuffer<T1>& buffer1 = buffers->Buffer<T1>();
				ComponentBuffer<T2>& buffer2 = buffers->Buffer<T2>();

				for(size_t i = 0; i < buffer0.m_data.size(); ++i)
				{
					uint32_t handle = buffers->m_handles[i];
					T0& component0 = buffer0.m_data[i];
					T1& component1 = buffer1.m_data[i];
					T2& component2 = buffer2.m_data[i];
					action(handle, component0, component1, component2);
				}
			}
		}

		template <class T0, class T1, class T2, class T3, class T_Function>
		void Loop(T_Function action)
		{
			EntFlags prototype = (1ULL << TypedBuffer<T0>::index()) | (1ULL << TypedBuffer<T1>::index()) | (1ULL << TypedBuffer<T2>::index()) | (1ULL << TypedBuffer<T3>::index());
			
			std::vector<ParallelBuffers*> matches = this->Match(prototype);
			for(ParallelBuffers* buffers : matches)
			{
				ComponentBuffer<T0>& buffer0 = buffers->Buffer<T0>();
				ComponentBuffer<T1>& buffer1 = buffers->Buffer<T1>();
				ComponentBuffer<T2>& buffer2 = buffers->Buffer<T2>();
				ComponentBuffer<T3>& buffer3 = buffers->Buffer<T3>();

				for(size_t i = 0; i < buffer0.m_data.size(); ++i)
				{
					uint32_t handle = buffers->m_handles[i];
					T0& component0 = buffer0.m_data[i];
					T1& component1 = buffer1.m_data[i];
					T2& component2 = buffer2.m_data[i];
					T3& component3 = buffer3.m_data[i];
					action(handle, component0, component1, component2, component3);
				}
			}
		}
	};

	export_ extern MUD_ECS_EXPORT EntityRegistry s_registry;

	export_ template <class... T_Components>
	struct Tags
	{};

	struct MUD_ECS_EXPORT Entity
	{
		template <class... T_Components>
		Entity(Tags<T_Components...> tags) { UNUSED(tags); m_handle = s_registry.CreateEntity<T_Components...>(); }
		~Entity() { s_registry.DeleteEntity(m_handle); }

		uint32_t m_handle;
	};

	export_ template <class T>
	inline bool is(Entity& entity) { return s_registry.HasComponent<T>(entity.m_handle); }

	export_ template <class T>
	inline T& as(Entity& entity) { return s_registry.GetComponent<T>(entity.m_handle); }

	export_ template <class T>
	inline T* try_as(Entity& entity) { if(is<T>(entity)) return &as<T>(entity); else return nullptr; }
	
	export_ template <class T>
	inline T* try_as(Entity* entity) { if(entity && is<T>(*entity)) return &as<T>(*entity); else return nullptr; }

	template <class T>
	struct ComponentHandle
	{
		ComponentHandle() {}
		ComponentHandle(uint32_t handle) : m_handle(handle) {}

		explicit operator bool() const { return m_handle != UINT32_MAX; }

		operator T&() { return s_registry.GetComponent<T>(m_handle); }
		operator const T&() const { return s_registry.GetComponent<T>(m_handle); }
		T* operator->() { return &((T&)*this); }
		T& operator*() { return *this; }
		const T* operator->() const { return &((const T&)*this); }
		const T& operator*() const { return *this; }

		bool operator==(const ComponentHandle<T>& other) const { return m_handle == other.m_handle; };

		uint32_t m_handle = UINT32_MAX;
	};

	template <class T>
	struct Component
	{
		template <class... T_Args>
		Component(uint32_t handle, T_Args&&... args) : m_handle(handle) { s_registry.SetComponent<T>(handle, T(std::forward<T_Args>(args)...)); }

		template <class... T_Args>
		Component(const Entity& entity, T_Args&&... args) : m_handle(entity.m_handle) { s_registry.SetComponent<T>(entity.m_handle, T(std::forward<T_Args>(args)...)); }

		operator ComponentHandle<T>() const { return { m_handle }; }

		operator T&() { return s_registry.GetComponent<T>(m_handle); }
		operator const T&() const { return s_registry.GetComponent<T>(m_handle); }
		T* operator->() { return &((T&)*this); }
		T& operator*() { return *this; }
		const T* operator->() const { return &((const T&)*this); }
		const T& operator*() const { return *this; }

		bool operator==(const Component<T>& other) const { return m_handle == other.m_handle; };

		uint32_t m_handle;
	};
}