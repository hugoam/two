#pragma once

#include <mud/pool.h>
#include <mud/jobs.h>
#include <mud/infra.h>
#include <mud/type.h>



#include <stl/swap.h>



#ifndef MUD_ECS_EXPORT
#define MUD_ECS_EXPORT MUD_IMPORT
#endif

namespace mud
{
	template <class T> struct ComponentHandle;
	template <class T> struct EntityHandle;

    class Prototype;
	struct Entity;
	class ECS;
	class GridECS;
	class Complex;
}

#ifdef MUD_META_GENERATOR
#include <stl/vector.h>
namespace stl
{
}
#endif
#include <stdint.h>

namespace mud
{
	template <class T>
	struct TypedBuffer
	{};

	struct refl_ struct_ MUD_ECS_EXPORT Entity
	{
		Entity() {}
		Entity(uint32_t handle, uint32_t ecs) : m_ecs(ecs), m_handle(handle) {}

		explicit operator bool() const { return m_handle != UINT32_MAX; }
		operator uint32_t() const { return m_handle; }

		bool operator==(const Entity& other) const { return m_handle == other.m_handle; };
		bool operator!=(const Entity& other) const { return m_handle != other.m_handle; };

		void destroy(); // { if(m_handle != UINT32_MAX) s_ecs[m_ecs]->destroy(m_handle); }

		void swap(Entity& other) { using mud::swap; swap(m_handle, other.m_handle); swap(m_ecs, other.m_ecs); }

		uint32_t m_ecs = UINT32_MAX;
		uint32_t m_handle = UINT32_MAX;
	};

	struct Entt
	{
		GridECS* m_ecs = nullptr;
		uint32_t m_handle = UINT32_MAX;

		template <class T>
		T& comp();
	};
}


#include <stdint.h>
#include <stl/memory.h>
#include <stl/map.h>

#define MUD_ECS_TYPED

#include <stl/swap.h>
#include <stl/vector.h>
#ifdef MUD_ECS_TYPED
#endif

namespace mud
{
	class Buffer
	{
	public:
		virtual ~Buffer() {}

#ifdef MUD_ECS_TYPED
		Type* m_type = nullptr;
#endif
		virtual void clear() = 0;
		virtual void add() = 0;
		virtual void remove(uint32_t index) = 0;
#ifdef MUD_ECS_TYPED
		virtual Ref get(uint32_t index) = 0;
#endif
	};

	template <class T>
	class TBuffer : public Buffer
	{
	public:
		TBuffer() {}
#ifdef MUD_ECS_TYPED
		TBuffer(Type& type, int capacity = 1 << 10)
#else
		TBuffer(int capacity = 1 << 10)
#endif
		{
#ifdef MUD_ECS_TYPED
			m_type = &type;
#endif
			m_data.reserve(capacity);
		}

		TBuffer(const TBuffer& other) = delete;
		TBuffer& operator=(const TBuffer& other) = delete;

		virtual void clear() override {	m_data.clear(); }
		virtual void add() override { m_data.emplace_back(); }
		virtual void remove(uint32_t index) override { swap_pop(m_data, index); }

#ifdef MUD_ECS_TYPED
		virtual Ref get(uint32_t index) override { return Ref(&m_data[index], *m_type); }
#endif

		vector<T> m_data;
	};
}

namespace mud
{
	struct EntityData
	{
		uint64_t m_prototype = 0;
		uint16_t m_stream = 0;

		bool operator<(EntityData& other) const { return m_prototype < other.m_prototype; }
	};
	
	using Typemap = vector<uint32_t>;

	template <bool Dense>
	class BufferArray
	{
	public:
		BufferArray();
		BufferArray(Typemap& typemap, uint32_t size = 0);

		BufferArray(BufferArray&& other) = default;
		BufferArray& operator=(BufferArray&& other) = default;

		BufferArray(const BufferArray& other) = delete;
		BufferArray& operator=(const BufferArray& other) = delete;

		template <class T>
		uint32_t type_index();

		template <class T>
		void add_buffer();

		template <class... Types>
		void init();

		template <class T>
		TBuffer<T>& buffer();

		uint32_t size() const;

		uint32_t reverse(uint32_t index) const;
		uint32_t handle(uint32_t index) const;

		void ensure(uint32_t capacity);

		void clear();
		uint32_t create();
		void add(uint32_t handle);
		void remove(uint32_t handle);

		template <class T>
		void set(uint32_t handle, T component = T());

		template <class T>
		T& get(uint32_t handle);

		Typemap* m_typemap = nullptr;

		SparseHandles<Dense> m_handles;

		vector<unique<Buffer>> m_buffers;
		vector<Buffer*> m_buffer_map;
	};

	class EntityStream : public BufferArray<false>
	{
	public:
		EntityStream();
		EntityStream(cstring name, Typemap& typemap, uint32_t size = 0);

		template <class... Types>
		void init(uint64_t prototype);

		cstring m_name;
		uint64_t m_prototype;
	};

	class GridECS : public BufferArray<false>
	{
	public:
		Typemap m_typemap;
		vector<uint32_t> m_available;

	public:
		GridECS();

		uint32_t create();
		void destroy(uint32_t handle);
	};

	class ECS
	{
	public:
		uint32_t m_index = 0;
		uint32_t m_type_index = 0;
		Typemap m_typemap;

		vector<EntityStream> m_streams;
		map<uint64_t, uint16_t> m_stream_map;

		vector<EntityData> m_entities;
		vector<uint32_t> m_available;

	public:
		ECS(int capacity = 1 << 10);

		ECS(const ECS& other) = delete;
		ECS& operator=(const ECS& other) = delete;

		template <class T>
		uint32_t type_index();

		template <class... Types>
		uint64_t prototype();

		template <class... Types>
		EntityStream& stream();

		EntityStream& stream(uint32_t handle);

		vector<EntityStream*> match(uint64_t prototype);

		template <class... Types>
		void add_stream(cstring name);

#ifdef MUD_ECS_TYPED
		template <class T>
		void register_type();

		template <class... Types>
		void add_stream();
#endif

		void ensure_size();

		uint32_t alloc(uint64_t prototype, uint16_t stream);

		template <class... Types>
		uint32_t create();

		void destroy(uint32_t handle);

		template <class T>
		void set(uint32_t handle, T component = T());

		template <class T>
		bool has(uint32_t handle);

		template <class T>
		T& get(uint32_t handle);

		template <class T, class... Types>
		vector<T*> gather();

		template <class... Types, class T_Function>
		void loop(T_Function action);

		template <class... Types, class T_Function>
		void loop_ent(T_Function action);
	};

	export_ extern MUD_ECS_EXPORT ECS* s_ecs[256];

	export_ template <class T>
	inline bool isa(const Entity& entity) { return s_ecs[entity.m_ecs]->has<T>(entity.m_handle); }

	export_ template <class T>
	inline T& asa(const Entity& entity) { return s_ecs[entity.m_ecs]->get<T>(entity.m_handle); }

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
		EntityStream& stream = s_ecs[entity.m_ecs]->stream(entity.m_handle);
		return stream.m_name;
	}

	template <class T>
	struct refl_ struct_ ComponentHandle : public Entity
	{
		ComponentHandle();
		ComponentHandle(uint32_t handle, uint32_t stream);
		ComponentHandle(const Entity& entity);

		operator T&();
		operator const T&() const;

		T* operator->();
		T& operator*();
		const T* operator->() const;
		const T& operator*() const;
	};

	template <class T>
	struct refl_ struct_ nocopy_ EntityHandle : public ComponentHandle<T>
	{
		EntityHandle();
		EntityHandle(uint32_t handle, uint32_t stream);
		~EntityHandle();

		EntityHandle(EntityHandle<T>& other) = delete;
		EntityHandle& operator=(EntityHandle<T>& other) = delete;

		EntityHandle(EntityHandle<T>&& other);
		EntityHandle& operator=(EntityHandle<T>&& other);

		operator Entity() const;
	};
}
//#include <ecs/ECS.hpp>


#include <stl/vector.h>

namespace mud
{
	export_ class refl_ MUD_ECS_EXPORT Complex
	{
	public:
		constr_ Complex(uint32_t id, Type& type);
		constr_ Complex(uint32_t id, Type& type, const vector<Ref>& parts);
		virtual ~Complex();

		template <class... T_Parts>
		Complex(uint32_t id, Type& type, T_Parts&&... parts)
			: Complex(id, type)
		{
			swallow{ (this->add_part(Ref(&parts, mud::type<type_class<T_Parts>>())), 1)... };
		}

		attr_ uint32_t m_id;
		attr_ Type& m_type;
		attr_ Prototype& m_prototype;

		attr_ vector<Ref> m_parts;

		meth_ void setup(const vector<Ref>& parts);

		meth_ void add_part(Ref part) { m_parts[m_prototype.part_index(type(part))] = part; }
		meth_ bool has_part(Type& type) { return m_prototype.has_part(type); }
		meth_ Ref part(Type& type) { return m_parts[m_prototype.part_index(type)]; }
		meth_ Ref try_part(Type& type) { if(has_part(type)) return this->part(type); else return Ref(); }
	};

	export_ template <class T>
	inline bool is(Complex& complex) { return complex.m_type.template is<T>() || complex.has_part(type<T>()); }

	export_ template <class T>
	inline T& as(Complex& complex) { return *static_cast<T*>(complex.part(type<T>()).m_value); }

	export_ template <class T>
	inline T* try_as(Complex& complex) { return is<T>(complex) ? *as<T>(complex) : nullptr; }
}

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

#ifndef MUD_MODULES
#endif


namespace mud
{
    // Exported types
    
    
    export_ template <> MUD_ECS_EXPORT Type& type<mud::Complex>();
    export_ template <> MUD_ECS_EXPORT Type& type<mud::Entity>();
}



#include <stl/tuple.h>
#include <stl/algorithm.h>

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

#include <stl/tuple.h>

namespace mud
{
	template <class... Types, size_t... Is, class T_Function>
	Job* for_components_impl(JobSystem& job_system, Job* parent, ECS& ecs, T_Function action, index_sequence<Is...>)
	{
		uint64_t prototype = ecs.prototype<Types...>();

		Job* job = job_system.job(parent);

		vector<EntityStream*> matches = ecs.match(prototype);
		for(EntityStream* stream : matches)
		{
			tuple<TBuffer<Types>&...> buffers = { stream->buffer<Types>()... };

			auto process = [=](JobSystem& js, Job* job, uint32_t start, uint32_t count)
			{
				UNUSED(js); UNUSED(job);
				for(uint32_t i = start; i < start + count; ++i)
				{
					action(at<Is>(buffers).m_data[i]...);
				}
			};

			Job* stream_job = split_jobs<64>(job_system, job, 0, uint32_t(stream->size()), process);
			job_system.run(stream_job);
		}

		return job;
	}

	template <class... Types, class T_Function>
	Job* for_components(JobSystem& job_system, Job* parent, ECS& ecs, T_Function action)
	{
		return for_components_impl<Types...>(job_system, parent, ecs, action, index_tuple<sizeof...(Types)>());
	}
}
