
#pragma once

#include <stl/tuple.h>
#include <stl/algorithm.h>
#include <infra/Generic.h>
#include <ecs/Forward.h>
#include <ecs/ECS.h>
#include <pool/SparsePool.hpp>

namespace mud
{
	template <class F, typename... Types>
	void for_each(F&& f, Types&&... xs)
	{
		swallow{ (f(static_cast<Types&&>(xs)), 0)... };
	}

	template <class... Types>
	uint64_t any_flags(Types... xs)
	{
		uint64_t flags = false;
		for_each([&flags](uint64_t x) { flags = flags | x; }, xs...);
		return flags;
	}

#ifdef _MSC_VER // sucks
	template <class... Args>
	struct select_last;

	template <class T>
	struct select_last<T>
	{
		using type = T;
	};

	template <class T, class... Args>
	struct select_last<T, Args...>
	{
		using type = typename select_last<Args...>::type;
	};
#else
	template <class T>
	struct tag
	{
		using type = T;
	};
	
	template <class... Types>
	struct select_last
	{
		using type = typename decltype((tag<Types>{}, ...))::type;
	};
#endif

	template <bool Dense>
	inline BufferArray<Dense>::BufferArray() {}
	template <bool Dense>
	inline BufferArray<Dense>::BufferArray(Typemap& typemap, uint32_t size)
		: m_typemap(&typemap)
		, m_buffer_map(64)
	{
		m_handles.ensure(size);
	}

	template <bool Dense>
	template <class T>
	inline uint32_t BufferArray<Dense>::type_index()
	{
#if 0 //def MUD_ECS_TYPED
		return m_typemap[type<T>().m_id];
#else
		return TypedBuffer<T>::index();
#endif
	}

	template <bool Dense>
	template <class T>
	inline void BufferArray<Dense>::add_buffer()
	{
#ifdef MUD_ECS_TYPED
		m_buffers.push_back(construct<TBuffer<T>>(type<T>()));
#else
		m_buffers.push_back(construct<TBuffer<T>>());
#endif
		m_buffer_map[this->type_index<T>()] = &(*m_buffers.back());
	}

	template <bool Dense>
	template <class... Types>
	inline void BufferArray<Dense>::init()
	{
		swallow{ (this->add_buffer<Types>(), 0)... };
	}

	template <bool Dense>
	template <class T>
	inline TBuffer<T>& BufferArray<Dense>::buffer()
	{
		return static_cast<TBuffer<T>&>(*m_buffer_map[this->type_index<T>()]);
	}

	template <bool Dense>
	inline uint32_t BufferArray<Dense>::size() const { return m_handles.size(); }

	template <bool Dense>
	inline uint32_t BufferArray<Dense>::reverse(uint32_t index) const { return m_handles.reverse(index); }

	template <bool Dense>
	inline uint32_t BufferArray<Dense>::handle(uint32_t index) const { return m_handles.reverse(index); }

	template <bool Dense>
	inline void BufferArray<Dense>::ensure(uint32_t capacity)
	{
		m_handles.ensure(capacity);
	}

	template <bool Dense>
	inline void BufferArray<Dense>::clear()
	{
		m_handles.clear();
		for(auto& buffer : m_buffers)
			buffer->clear();
	}

	template <bool Dense>
	inline uint32_t BufferArray<Dense>::create()
	{
		const uint32_t handle = m_handles.create();
		for(auto& buffer : m_buffers)
			buffer->add();
		return handle;
	}

	template <bool Dense>
	inline void BufferArray<Dense>::add(uint32_t handle)
	{
		m_handles.add(handle);
		for(auto& buffer : m_buffers)
			buffer->add();
	}

	template <bool Dense>
	inline void BufferArray<Dense>::remove(uint32_t handle)
	{
		const uint32_t index = m_handles.remove(handle);
		for(auto& buffer : m_buffers)
			buffer->remove(index);
	}

	template <bool Dense>
	template <class T>
	inline void BufferArray<Dense>::set(uint32_t handle, T component)
	{
		uint32_t index = m_handles[handle];
		this->buffer<T>().m_data[index] = move(component);
	}

	template <bool Dense>
	template <class T>
	inline T& BufferArray<Dense>::get(uint32_t handle)
	{
		uint32_t index = m_handles[handle];
		return this->buffer<T>().m_data[index];
	}

	inline EntityStream::EntityStream() {}
	inline EntityStream::EntityStream(cstring name, Typemap& typemap, uint32_t size)
		: BufferArray<false>(typemap, size)
		, m_name(name)
	{}

	template <class... Types>
	inline void EntityStream::init(uint64_t prototype)
	{
		m_prototype = prototype;
		swallow{ (this->add_buffer<Types>(), 0)... };
	}

	inline GridECS::GridECS()
		: BufferArray<false>(m_typemap)
	{}

	inline uint32_t GridECS::create()
	{
		uint32_t handle = m_available.size() > 0 ? pop(m_available) : m_handles.alloc();
		this->add(handle);
		return handle;
	}

	inline void GridECS::destroy(uint32_t handle)
	{
		this->remove(handle);
		m_available.push_back(handle);
	}

	template <class T>
	inline T& Entt::comp() { return m_ecs->get<T>(m_handle); }

	inline ECS::ECS(int capacity)
	{
		m_streams.reserve(64);
		m_entities.reserve(capacity);
	}

	template <class T>
	inline uint32_t ECS::type_index()
	{
#if 0 //def MUD_ECS_TYPED
		return (*m_typemap)[type<T>().m_id];
#else
		return TypedBuffer<T>::index();
#endif
	}

	template <class... Types>
	inline uint64_t ECS::prototype()
	{
		return any_flags(1ULL << this->type_index<Types>()...);
	}

	template <class... Types>
	inline EntityStream& ECS::stream()
	{
		uint64_t prototype = this->prototype<Types...>();
		uint16_t stream = m_stream_map[prototype];
		return m_streams[stream];
	}

	inline EntityStream& ECS::stream(uint32_t handle)
	{
		uint16_t stream = m_entities[handle].m_stream;
		return m_streams[stream];
	}

	inline vector<EntityStream*> ECS::match(uint64_t prototype)
	{
		vector<EntityStream*> matches;
		for(EntityStream& buffers : m_streams)
			if((buffers.m_prototype & prototype) == prototype)
				matches.push_back(&buffers);
		return matches;
	}

	template <class... Types>
	inline void ECS::add_stream(cstring name)
	{
		uint64_t prototype = this->prototype<Types...>();
		m_stream_map[prototype] = uint16_t(m_streams.size());
		m_streams.push_back({ name, m_typemap });
		m_streams.back().init<Types...>(prototype);
	}

#ifdef MUD_ECS_TYPED
	template <class T>
	inline void ECS::register_type()
	{
#if 0
		if(m_typemap[type<T>().m_id] == 0)
			m_typemap[type<T>().m_id] = ++m_type_index;
#endif
	}

	template <class... Types>
	inline void ECS::add_stream()
	{
		using T_Prototype = typename select_last<Types...>::type;
		this->add_stream<Types...>(type<T_Prototype>().m_name);
		swallow{ (this->register_type<Types&&>(), 0)... };
	}
#endif

	inline void ECS::ensure_size()
	{
		for(auto& buffer : m_streams)
			buffer.ensure(uint32_t(m_entities.size()));
	}

	inline uint32_t ECS::alloc(uint64_t prototype, uint16_t stream)
	{
		if(m_available.size() > 0)
			return pop(m_available);
		uint32_t handle = uint32_t(m_entities.size());
		m_entities.push_back({ prototype, stream });
		this->ensure_size();
		return handle;
	}

	template <class... Types>
	inline uint32_t ECS::create()
	{
		uint64_t prototype = this->prototype<Types...>();
		if(m_stream_map.find(prototype) == m_stream_map.end())
			this->add_stream<Types...>();
		uint16_t stream = m_stream_map[prototype];
		uint32_t handle = this->alloc(prototype, stream);
		m_streams[stream].add(handle);
		return handle;
	}

	inline void ECS::destroy(uint32_t handle)
	{
		EntityData& entity = m_entities[handle];
		m_streams[entity.m_stream].remove(handle);
		m_available.push_back(handle);
	}

	template <class T>
	inline void ECS::set(uint32_t handle, T component)
	{
		EntityData& entity = m_entities[handle];
		m_streams[entity.m_stream].set<T>(handle, move(component));
	}

	template <class T>
	inline bool ECS::has(uint32_t handle)
	{
		uint64_t flag = (1ULL << this->type_index<T>());
		EntityData& entity = m_entities[handle];
		return (entity.m_prototype & flag) != 0;
	}

	template <class T>
	inline T& ECS::get(uint32_t handle)
	{
		EntityData& entity = m_entities[handle];
		return m_streams[entity.m_stream].get<T>(handle);
	}

	template <class T, class... Types>
	inline vector<T*> ECS::gather()
	{
		uint64_t prototype = this->prototype<T, Types...>();
		
		vector<T*> result;

		vector<EntityStream*> matches = this->match(prototype);
		for(EntityStream* buffers : matches)
		{
			TBuffer<T>& buffer = buffers->buffer<T>();

			const size_t count = buffer.m_data.size();
			const size_t size = result.size();
			result.reserve(size + count);

			for(size_t i = 0; i < count; ++i)
				result.push_back(&buffer.m_data[size + i]);
		}

		return result;
	}

	template <class... Types, size_t... Is, class T_Function>
	inline void loop_ent_impl(ECS& ecs, T_Function action, index_sequence<Is...>)
	{
		uint64_t prototype = ecs.prototype<Types...>();

		vector<EntityStream*> matches = ecs.match(prototype);
		for(EntityStream* stream : matches)
		{
			tuple<TBuffer<Types>&...> buffers = { stream->buffer<Types>()... };

			const uint32_t size = stream->size();
			for(uint32_t i = 0; i < size; ++i)
			{
				uint32_t handle = stream->handle(i);
				action(handle, at<Is>(buffers).m_data[i]...);
			}
		}
	}

	template <class... Types, size_t... Is, class T_Function>
	inline void loop_impl(ECS& ecs, T_Function action, index_sequence<Is...>)
	{
		uint64_t prototype = ecs.prototype<Types...>();

		vector<EntityStream*> matches = ecs.match(prototype);
		for(EntityStream* stream : matches)
		{
			tuple<TBuffer<Types>&...> buffers = { stream->buffer<Types>()... };

			const uint32_t size = stream->size();
			for(uint32_t i = 0; i < size; ++i)
			{
				action(at<Is>(buffers).m_data[i]...);
			}
		}
	}

	template <class... Types, class T_Function>
	inline void ECS::loop(T_Function action)
	{
		loop_impl<Types...>(*this, action, index_tuple<sizeof...(Types)>());
	}

	template <class... Types, class T_Function>
	inline void ECS::loop_ent(T_Function action)
	{
		loop_ent_impl<Types...>(*this, action, index_tuple<sizeof...(Types)>());
	}

	template <class T>
	inline ComponentHandle<T>::ComponentHandle() {}
	template <class T>
	inline ComponentHandle<T>::ComponentHandle(uint32_t handle, uint32_t stream) : Entity(handle, stream) {}
	template <class T>
	inline ComponentHandle<T>::ComponentHandle(const Entity& entity) : Entity(entity) {}

	template <class T>
	inline ComponentHandle<T>::operator T&() { return asa<T>(*this); }
	template <class T>
	inline ComponentHandle<T>::operator const T&() const { return asa<T>(*this); }

	template <class T>
	inline T* ComponentHandle<T>::operator->() { return &asa<T>(*this); }
	template <class T>
	inline T& ComponentHandle<T>::operator*() { return asa<T>(*this); }
	template <class T>
	inline const T* ComponentHandle<T>::operator->() const { return &asa<T>(*this); }
	template <class T>
	inline const T& ComponentHandle<T>::operator*() const { return asa<T>(*this); }

	template <class T>
	inline EntityHandle<T>::EntityHandle() {}
	template <class T>
	inline EntityHandle<T>::EntityHandle(uint32_t handle, uint32_t stream) : ComponentHandle<T>(handle, stream) {}
	template <class T>
	inline EntityHandle<T>::~EntityHandle() { this->destroy(); }

	template <class T>
	inline EntityHandle<T>::EntityHandle(EntityHandle<T>&& other) { other.swap(*this); }
	template <class T>
	inline EntityHandle<T>& EntityHandle<T>::operator=(EntityHandle<T>&& other) { other.swap(*this); return *this; }

	template <class T>
	inline EntityHandle<T>::operator Entity() const { return { this->m_handle, this->m_stream }; }
}