
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

	inline BufferArray::BufferArray() {}
	inline BufferArray::BufferArray(Typemap& typemap, uint32_t size)
		: m_typemap(&typemap)
		, m_buffer_map(64)
	{
		m_handles.ensure(size);
	}

	template <class T>
	inline uint32_t BufferArray::type_index()
	{
#if 0 //def MUD_ECS_TYPED
		return m_typemap[type<T>().m_id];
#else
		return TypedBuffer<T>::index();
#endif
	}

	template <class T>
	inline void BufferArray::add_buffer()
	{
#ifdef MUD_ECS_TYPED
		m_buffers.push_back(construct<TBuffer<T>>(type<T>()));
#else
		m_buffers.push_back(construct<TBuffer<T>>());
#endif
		m_buffer_map[this->type_index<T>()] = &(*m_buffers.back());
	}

	template <class... Types>
	inline void BufferArray::init()
	{
		swallow{ (this->add_buffer<Types>(), 0)... };
	}

	template <class T>
	inline TBuffer<T>& BufferArray::buffer()
	{
		return static_cast<TBuffer<T>&>(*m_buffer_map[this->type_index<T>()]);
	}

	inline uint32_t BufferArray::size() const { return m_handles.size(); }

	inline uint32_t BufferArray::reverse(uint32_t index) const { return m_handles.reverse(index); }

	inline uint32_t BufferArray::handle(uint32_t index) const { return m_handles.reverse(index); }

	inline void BufferArray::ensure(uint32_t capacity)
	{
		m_handles.ensure(capacity);
	}

	inline void BufferArray::clear()
	{
		m_handles.clear();
		for(auto& buffer : m_buffers)
			buffer->clear();
	}

	inline uint32_t BufferArray::create()
	{
		const uint32_t handle = m_handles.create();
		for(auto& buffer : m_buffers)
			buffer->create();
		return handle;
	}

	inline uint32_t BufferArray::create(uint32_t count)
	{
		const uint32_t handle = m_handles.create(count);
		for(auto& buffer : m_buffers)
			buffer->create(count);
		return handle;
	}

	inline void BufferArray::add()
	{
		for(auto& buffer : m_buffers)
			buffer->create();
	}

	inline void BufferArray::remove(uint32_t handle)
	{
		const uint32_t index = m_handles.remove(handle);
		for(auto& buffer : m_buffers)
			buffer->remove(index);
	}

	template <class T>
	inline void BufferArray::set(uint32_t handle, T component)
	{
		const uint32_t index = m_handles[handle];
		this->buffer<T>().m_data[index] = move(component);
	}

	template <class T>
	inline T& BufferArray::get(uint32_t handle)
	{
		const uint32_t index = m_handles[handle];
		return this->buffer<T>().m_data[index];
	}

	inline EntityStream::EntityStream() {}
	inline EntityStream::EntityStream(cstring name, uint16_t index, Typemap& typemap, uint32_t size)
		: BufferArray(typemap, size)
		, m_name(name)
		, m_index(index)
	{}

	template <class... Types>
	inline void EntityStream::init(uint64_t prototype)
	{
		m_prototype = prototype;
		swallow{ (this->add_buffer<Types>(), 0)... };
	}

	inline GridECS::GridECS()
		: BufferArray(m_typemap)
	{}

	inline uint32_t GridECS::create()
	{
		uint32_t handle = m_available.size() > 0 ? pop(m_available) : m_handles.alloc();
		this->add();
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
		UNUSED(capacity);
		m_streams.reserve(1024);
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

	template <class T>
	inline uint32_t ECS::type_mask()
	{
		return 1ULL << this->type_index<T>();
	}

	template <class... Types>
	inline uint64_t ECS::prototype()
	{
		return any_flags(1ULL << this->type_index<Types>()...);
	}

	template <class... Types>
	inline EntityStream& ECS::stream()
	{
		const uint64_t prototype = this->prototype<Types...>();
		if(m_stream_map.find(prototype) == m_stream_map.end())
			this->add_stream<Types...>("todo");
		const uint16_t stream = m_stream_map[prototype];
		return m_streams[stream];
	}

	inline EntityStream& ECS::stream(uint32_t stream)
	{
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
		const uint64_t prototype = this->prototype<Types...>();
		const uint16_t index = uint16_t(m_streams.size());
		m_streams.push_back({ name, index, m_typemap });
		m_streams.back().init<Types...>(prototype);
		m_stream_map[prototype] = index;
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

	template <class... Types>
	inline Entity ECS::create()
	{
		EntityStream& stream = this->stream<Types...>();
		const uint32_t handle = stream.create();
		return { m_index, stream.m_index, handle };
	}

	inline void ECS::destroy(Entity entity)
	{
		m_streams[entity.m_stream].remove(entity.m_handle);
	}

	template <class T>
	inline void ECS::set(Entity entity, T component)
	{
		m_streams[entity.m_stream].set<T>(entity.m_handle, move(component));
	}

	template <class T>
	inline bool ECS::has(Entity entity)
	{
		const uint64_t flag = (1ULL << this->type_index<T>());
		const uint64_t prototype = m_streams[entity.m_stream].m_prototype;
		return (prototype & flag) != 0;
	}

	template <class T>
	inline T& ECS::get(Entity entity)
	{
		return m_streams[entity.m_stream].get<T>(entity.m_handle);
	}

	template <class T, class... Types>
	inline vector<T*> ECS::gather()
	{
		const uint64_t prototype = this->prototype<T, Types...>();
		
		vector<T*> result;

		const vector<EntityStream*> matches = this->match(prototype);
		for(EntityStream* buffers : matches)
		{
			const TBuffer<T>& buffer = buffers->buffer<T>();

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
		const uint64_t prototype = ecs.prototype<Types...>();

		const vector<EntityStream*> matches = ecs.match(prototype);
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
		const uint64_t prototype = ecs.prototype<Types...>();

		const vector<EntityStream*> matches = ecs.match(prototype);
		//const size_t num_matches = matches.size();
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

	template <unsigned EcsType, unsigned NumComponents>
	inline void tECS<EcsType, NumComponents>::add_buffer(EntityStream& stream, uint64_t prototype, uint32_t index, unique<Buffer> buffer)
	{
		if((prototype & (1ULL << index)) != 0)
			stream.add_buffer(index, move(buffer));
	}

	template <unsigned EcsType, unsigned NumComponents, uint32_t... Is>
	inline void init_stream(tECS<EcsType, NumComponents>& ecs, EntityStream& stream, uint64_t prototype, index_sequence<Is...>)
	{
		swallow{ (ecs.add_buffer(stream, prototype, Is, TypeBuffer<EcsType, Is>::create()), 0)... };
	}

	template <unsigned EcsType, unsigned NumComponents>
	inline void tECS<EcsType, NumComponents>::add_stream(uint64_t prototype, const string& name)
	{
		const uint16_t index = uint16_t(m_streams.size());
		m_streams.push_back({ name.c_str(), index, m_typemap });
		EntityStream& stream = m_streams.back();
		stream.m_prototype = prototype;
		this->init_stream(stream, prototype, index_tuple<NumComponents>());
		m_stream_map[prototype] = index;
	}

	template <unsigned EcsType, unsigned NumComponents>
	inline EntityStream& tECS<EcsType, NumComponents>::stream(uint64_t prototype)
	{
		if(m_stream_map.find(prototype) == m_stream_map.end())
			this->add_stream(prototype);
		const uint16_t stream = m_stream_map[prototype];
		return m_streams[stream];
	}

	template <unsigned EcsType, unsigned NumComponents>
	inline Entity tECS<EcsType, NumComponents>::create(uint64_t prototype)
	{
		EntityStream& stream = this->stream(prototype);
		uint32_t handle = stream.create();
		return { m_index, stream.m_index, handle };
	}

	template <unsigned EcsType, unsigned NumComponents>
	inline Entity tECS<EcsType, NumComponents>::create(uint64_t prototype, uint32_t count)
	{
		EntityStream& stream = this->stream(prototype);
		uint32_t handle = stream.create(count);
		return { m_index, stream.m_index, handle };
	}

	template <class T>
	inline ComponentHandle<T>::ComponentHandle() {}
	//template <class T>
	//inline ComponentHandle<T>::ComponentHandle(uint32_t handle, uint32_t stream) : Entity(handle, stream) {}
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
	//template <class T>
	//inline EntityHandle<T>::EntityHandle(uint32_t handle, uint32_t stream) : ComponentHandle<T>(handle, stream) {}
	template <class T>
	inline EntityHandle<T>::~EntityHandle() { this->destroy(); }

	template <class T>
	inline EntityHandle<T>::EntityHandle(EntityHandle<T>&& other) { other.swap(*this); }
	template <class T>
	inline EntityHandle<T>& EntityHandle<T>::operator=(EntityHandle<T>&& other) { other.swap(*this); return *this; }

	template <class T>
	inline EntityHandle<T>::operator Entity() const { return { this->m_handle, this->m_stream }; }
}
