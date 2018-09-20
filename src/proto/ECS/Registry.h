#pragma once

#include <infra/Vector.h>
#include <proto/Forward.h>
#include <proto/ECS/ECS.h>
#include <proto/ECS/MappedBuffers.h>
#include <proto/ECS/MappedBufferDense.h>
#include <proto/ECS/MappedBufferSparse.h>
#include <proto/ECS/ComponentBuffer.h>

#include <memory>
#include <functional>
#include <map>

namespace mud
{
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

	class EntityRegistry
	{
	private:
		std::vector<std::unique_ptr<ComponentBufferBase>> m_buffers;
		
		std::vector<EntityData> m_entities;
		std::vector<uint32_t> m_available;

	public:
		EntityRegistry(int capacity = 1 << 10)
			: m_buffers(64)
		{
			m_entities.reserve(capacity);
		}

		template <class T>
		auto& buffer()
		{
			return static_cast<typename TypedBuffer<T>::type&>(*m_buffers[TypedBuffer<T>::index()]);
		}

		template <class T>
		void AddBuffer()
		{
			m_buffers[TypedBuffer<T>::index()] = std::make_unique<typename TypedBuffer<T>::type>(TypedBuffer<T>::index());
		}
		
		void UpdateSize()
		{
			for(auto& buffer : m_buffers)
				if(buffer)
				{
					buffer->SetCapacity(m_entities.size());
				}
		}

		uint32_t CreateEntity(EntTags tags = 0)
		{
			UNUSED(tags);
			if(m_available.size() > 0)
				return vector_pop(m_available);
			uint32_t handle = m_entities.size();
			m_entities.push_back({});
			UpdateSize();
			return handle;
		}

		void ClearEntity(uint32_t handle, EntityData& entity)
		{
			for(auto& buffer : m_buffers)
				if(buffer)
					if((buffer->m_flag & entity.m_flags) != 0)
					{
						buffer->RemoveComponent(handle, entity);
					}
		}

		void ClearEntity(uint32_t handle)
		{
		    EntityData& entity = m_entities[handle];
			ClearEntity(handle, entity);
			entity.m_flags = 0;
		}

		void DeleteEntity(uint32_t handle)
		{
			EntityData& entity = m_entities[handle];
			ClearEntity(handle, entity);
			m_available.push_back(handle);
		}

		template <class T>
		T& Deref(T& component) { return component; }

		template <class T>
		T& Deref(T* component) { return *component; }

		template <class T>
		void AddComponent(uint32_t handle, T component = T())
		{
			EntityData& entity = m_entities[handle];
			auto& buffer = this->buffer<T>();
			buffer.AddComponent(handle, std::move(component), entity);
		}

		template <class T>
		void AddPointer(uint32_t handle, T* component)
		{
			EntityData& entity = m_entities[handle];
			auto& buffer = this->buffer<T>();
			buffer.AddComponent(handle, component, entity);
		}

		template <class T>
		void RemoveComponent(uint32_t handle)
		{
			EntityData& entity = m_entities[handle];
			auto& buffer = this->buffer<T>();
			buffer.RemoveComponent(handle, entity);
		}

		template <class T>
		bool HasComponent(uint32_t handle)
		{
			auto& buffer = this->buffer<T>();
			EntityData& entity = m_entities[handle];
			return (entity.m_flags & buffer.m_flag) != 0;
		}

		template <class T>
		T& GetComponent(uint32_t handle)
		{
			auto& buffer = this->buffer<T>();
			int index = buffer.m_indices[handle];
			return Deref(buffer.m_data[index]);
		}

		template <class T>
		void SortComponents()
		{
			this->buffer<T>().SortComponents();
		}

		template <class T0, class T_Function>
		void Loop(T_Function action)
		{
			auto& b0 = this->buffer<T0>();
			size_t last = b0.m_data.size() - 1;
			auto& handles = b0.m_keys;
			auto& components = b0.m_data;
			for(int i = last; i >= 0; i--)
			{
				uint32_t handle = handles[i];
				T0& component0 = Deref(components[i]);
				action(handle, component0);
			}
		}

		template <class T0, class T1, class T_Function>
		void Loop(T_Function action)
		{
			auto& b0 = this->buffer<T0>();
			auto& b1 = this->buffer<T1>();
			size_t last = b0.m_data.size() - 1;
			auto& handles = b0.m_keys;
			auto& components = b0.m_data;
			EntFlags flags = b1.m_flag;

			for(int i = last; i >= 0; i--)
			{
				uint32_t handle = handles[i];
				EntityData& entity = m_entities[handle];

				if((entity.m_flags & flags) == flags)
				{
					T0& component0 = Deref(components[i]);
					int index1 = b1.m_indices[handle];
					T1& component1 = Deref(b1.m_data[index1]);
					action(handle, component0, component1);
				}
			}
		}


		template <class T0, class T1, class T2, class T_Function>
		void Loop(T_Function action)
		{
			auto& b0 = this->buffer<T0>();
			auto& b1 = this->buffer<T1>();
			auto& b2 = this->buffer<T2>();
			size_t last = b0.m_data.size() - 1;
			auto& handles = b0.m_keys;
			auto& components = b0.m_data;
			EntFlags flags = b1.m_flag | b2.m_flag;

			for(int i = last; i >= 0; i--)
			{
				uint32_t handle = handles[i];;
				EntityData& entity = m_entities[handle];

				if((entity.m_flags & flags) == flags)
				{
					T0& component0 = Deref(components[i]);
					int index1 = b1.m_indices[handle];
					T1& component1 = Deref(b1.m_data[index1]);
					int index2 = b2.m_indices[handle];
					T2& component2 = Deref(b2.m_data[index2]);
					action(handle, component0, component1, component2);
				}
			}
		}

		template <class T0, class T1, class T2, class T3, class T_Function>
		void Loop(T_Function action)
		{
			auto& b0 = this->buffer<T0>();
			auto& b1 = this->buffer<T1>();
			auto& b2 = this->buffer<T2>();
			auto& b3 = this->buffer<T3>();
			size_t last = b0.m_data.size() - 1;
			auto& handles = b0.m_keys;
			auto& components = b0.m_data;

			EntFlags flags = b1.m_flag | b2.m_flag | b3.m_flag;

			for(int i = last; i >= 0; i--)
			{
				uint32_t handle = handles[i];
				EntityData& entity = m_entities[handle];

				if((entity.m_flags & flags) == flags)
				{
					T0& component0 = Deref(components[i]);
					int index1 = b1.m_indices[handle];
					T1& component1 = Deref(b1.m_data[index1]);
					int index2 = b2.m_indices[handle];
					T2& component2 = Deref(b2.m_data[index2]);
					int index3 = b3.m_indices[handle];
					T3& component3 = Deref(b3.m_data[index3]);
					action(handle, component0, component1, component2, component3);
				}
			}
		}

#ifdef MUD_ECS_SLICES
		std::vector<EntFlags> prototypes(EntFlags components);

		template <class T0, class T_Function>
		void LoopFast(T_Function action)
		{
			EntFlags prototype = (1 << TypedBuffer<T0>::index());
			auto prototypes = this->prototypes(prototype);
			auto& buffer0 = this->buffer<T0>();
			
			for(auto& prototype : prototypes)
			{
				EntitySlice slice = this->slice(prototype);
				EntitySlice slice0 = buffer0.slice(prototype);
				for(size_t i = ; i < slice0.m_end; ++i)
				{
					uint32_t entity = m_entities[slice.m_begin + i];
					T0& component0 = Deref(buffer0.m_data[slice0.m_begin + i]);
					action(handle, component0);
				}
			}
		}

		template <class T0, class T1, class T_Function>
		void LoopFast(T_Function action)
		{
			EntFlags prototype = (1 << TypedBuffer<T0>::index()) | (1 << TypedBuffer<T1>::index());
			auto prototypes = this->prototypes(prototype);
			auto& buffer0 = this->buffer<T0>();
			auto& buffer1 = this->buffer<T1>();

			for(auto& prototype : prototypes)
			{
				EntitySlice slice = this->slice(prototype);
				EntitySlice slice0 = buffer0.slice(prototype);
				EntitySlice slice1 = buffer1.slice(prototype);
				for(size_t i = ; i < slice0.m_end; ++i)
				{
					uint32_t entity = m_entities[slice.m_begin + i];
					T0& component0 = Deref(buffer0.m_data[slice0.m_begin + i]);
					T1& component1 = Deref(buffer1.m_data[slice1.m_begin + i]);
					action(handle, component0, component1);
				}
			}
		}


		template <class T0, class T1, class T2, class T_Function>
		void LoopFast(T_Function action)
		{
			EntFlags prototype = (1 << TypedBuffer<T0>::index()) | (1 << TypedBuffer<T1>::index()) | (1 << TypedBuffer<T2>::index());
			auto prototypes = this->prototypes(prototype);
			auto& buffer0 = this->buffer<T0>();
			auto& buffer1 = this->buffer<T1>();
			auto& buffer2 = this->buffer<T2>();

			for(auto& prototype : prototypes)
			{
				EntitySlice slice = this->slice(prototype);
				EntitySlice slice0 = buffer0.slice(prototype);
				EntitySlice slice1 = buffer1.slice(prototype);
				EntitySlice slice2 = buffer2.slice(prototype);
				for(size_t i = 0 ; i < slice0.m_end; ++i)
				{
					uint32_t entity = m_entities[slice.m_begin + i];
					T0& component0 = Deref(buffer0.m_data[slice0.m_begin + i]);
					T1& component1 = Deref(buffer1.m_data[slice1.m_begin + i]);
					T2& component2 = Deref(buffer2.m_data[slice2.m_begin + i]);
					action(handle, component0, component1);
				}
			}
		}

		template <class T0, class T1, class T2, class T3, class T_Function>
		void LoopFast(T_Function action)
		{
			EntFlags prototype = (1 << TypedBuffer<T0>::index()) | (1 << TypedBuffer<T1>::index()) | (1 << TypedBuffer<T2>::index()) | (1 << TypedBuffer<T3>::index());
			auto prototypes = this->prototypes(prototype);
			auto& buffer0 = this->buffer<T0>();
			auto& buffer1 = this->buffer<T1>();
			auto& buffer2 = this->buffer<T2>();
			auto& buffer3 = this->buffer<T3>();

			for(auto& prototype : prototypes)
			{
				EntitySlice slice = this->slice(prototype);
				EntitySlice slice0 = buffer0.slice(prototype);
				EntitySlice slice1 = buffer1.slice(prototype);
				EntitySlice slice2 = buffer2.slice(prototype);
				EntitySlice slice3 = buffer3.slice(prototype);
				for(size_t i = 0; i < slice0.m_end; ++i)
				{
					uint32_t entity = m_entities[slice.m_begin + i];
					T0& component0 = Deref(buffer0.m_data[slice0.m_begin + i]);
					T1& component1 = Deref(buffer1.m_data[slice1.m_begin + i]);
					T2& component2 = Deref(buffer2.m_data[slice2.m_begin + i]);
					T3& component3 = Deref(buffer3.m_data[slice3.m_begin + i]);
					action(handle, component0, component1);
				}
			}
		}
#endif

	};

	export_ extern MUD_PROTO_EXPORT EntityRegistry s_registry;

	struct MUD_PROTO_EXPORT Entity
	{
		Entity() { m_handle = s_registry.CreateEntity(); }
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
		Component(uint32_t handle, T_Args&&... args) : m_handle(handle) { s_registry.AddComponent<T>(handle, T(std::forward<T_Args>(args)...)); }

		template <class... T_Args>
		Component(const Entity& entity, T_Args&&... args) : m_handle(entity.m_handle) { s_registry.AddComponent<T>(entity.m_handle, T(std::forward<T_Args>(args)...)); }

		~Component() { s_registry.RemoveComponent<T>(m_handle); }

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