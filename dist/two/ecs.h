#pragma once

#include <two/pool.h>
#include <two/jobs.h>
#include <two/infra.h>
#include <two/type.h>



#include <stl/swap.h>



#ifndef TWO_ECS_EXPORT
#define TWO_ECS_EXPORT TWO_IMPORT
#endif

namespace two
{
	template <class T> struct ComponentHandle;
	template <class T> struct EntityHandle;

    class Prototype;
	struct Entity;
	struct Entt;
	class OEntt;
	class ECS;
	class GridECS;
	class Complex;
}

#ifdef TWO_META_GENERATOR
#include <stl/vector.h>
namespace stl
{
}
#endif
#include <stdint.h>

namespace two
{
	template <size_t EcsType, size_t Index>
	struct TypeBuffer
	{};

	template <class T>
	struct TypedBuffer
	{};

	struct refl_ struct_ TWO_ECS_EXPORT Entity
	{
		explicit operator bool() const { return m_handle != UINT32_MAX; }
		//operator uint32_t() const { return m_handle; }

		bool operator==(const Entity& other) const { return m_ecs == other.m_ecs && m_stream == other.m_stream && m_handle == other.m_handle; };
		bool operator!=(const Entity& other) const { return m_ecs != other.m_ecs || m_stream != other.m_stream || m_handle != other.m_handle; };

		void destroy(); // { if(m_handle != UINT32_MAX) s_ecs[m_ecs]->destroy(m_handle); }

		void swap(Entity& other) { using two::swap; swap(m_handle, other.m_handle); swap(m_stream, other.m_stream); swap(m_ecs, other.m_ecs); }

		uint8_t m_ecs = UINT8_MAX;
		uint16_t m_stream = UINT16_MAX;
		uint32_t m_handle = UINT32_MAX;

		uint64_t as_uint() { return uint64_t(m_ecs) << 48ULL | uint64_t(m_stream) << 32ULL | uint64_t(m_handle); }
	};

	struct refl_ struct_ TWO_ECS_EXPORT Entt
	{
		GridECS* m_ecs = nullptr;
		uint32_t m_handle = UINT32_MAX;

		template <class T>
		T& comp();
	};

	class refl_ TWO_ECS_EXPORT OEntt : public Entt
	{
	public:
		OEntt() {}
		OEntt(GridECS* ecs, uint32_t handle) : Entt{ ecs, handle } {}
		~OEntt();

		OEntt(OEntt&& other) { *this = move(other); }
		OEntt& operator=(OEntt&& other)
		{
			m_ecs = other.m_ecs; m_handle = other.m_handle;
			other.m_handle = UINT32_MAX;
			return *this;
		}
	};
}


#include <stdint.h>
#include <stl/memory.h>
#include <stl/map.h>
#include <stl/string.h>

#define TWO_ECS_TYPED

#include <stl/swap.h>
#include <stl/vector.h>
#ifdef TWO_ECS_TYPED
#endif

namespace two
{
	class Buffer
	{
	public:
		virtual ~Buffer() {}

#ifdef TWO_ECS_TYPED
		Type* m_type = nullptr;
#endif
		virtual void clear() = 0;
		virtual void create() = 0;
		virtual void create(uint32_t count) = 0;
		virtual void remove(uint32_t index) = 0;
#ifdef TWO_ECS_TYPED
		virtual Ref get(uint32_t index) = 0;
#endif
	};

	template <class T>
	class TBuffer : public Buffer
	{
	public:
		TBuffer() {}
#ifdef TWO_ECS_TYPED
		TBuffer(Type& type, int capacity = 1 << 10)
#else
		TBuffer(int capacity = 1 << 10)
#endif
		{
#ifdef TWO_ECS_TYPED
			m_type = &type;
#endif
			m_data.reserve(capacity);
		}

		TBuffer(const TBuffer& other) = delete;
		TBuffer& operator=(const TBuffer& other) = delete;

		virtual void clear() override {	m_data.clear(); }
		virtual void create() override { m_data.emplace_back(); }
		virtual void create(uint32_t count) override { m_data.resize(m_data.size() + count); }
		virtual void remove(uint32_t index) override { swap_pop(m_data, index); }

#ifdef TWO_ECS_TYPED
		virtual Ref get(uint32_t index) override { return Ref(&m_data[index], *m_type); }
#endif

		vector<T> m_data;
	};
}

namespace two
{
	class BufferArray
	{
	public:
		BufferArray();
		BufferArray(uint32_t size);

		BufferArray(BufferArray&& other) = default;
		BufferArray& operator=(BufferArray&& other) = default;

		BufferArray(const BufferArray& other) = delete;
		BufferArray& operator=(const BufferArray& other) = delete;

		void add_buffer(uint32_t index, unique<Buffer> buffer)
		{
			m_buffers.push_back(move(buffer));
			m_buffer_map[index] = &(*m_buffers.back());
		}

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
		uint32_t create(uint32_t count);
		void add();
		void remove(uint32_t handle);

		template <class T>
		void set(uint32_t handle, T component = T());

		template <class T>
		T& get(uint32_t handle);

		SparseHandles m_handles;

		vector<unique<Buffer>> m_buffers;
		vector<Buffer*> m_buffer_map;
	};

	using cstring = const char*;

	class EntityStream : public BufferArray
	{
	public:
		EntityStream();
		EntityStream(cstring name, uint16_t index, uint32_t size = 0);

		template <class... Types>
		void init(uint64_t prototype);

		cstring m_name;
		uint16_t m_index;
		uint64_t m_prototype;
	};

	class GridECS : public BufferArray
	{
	public:
		vector<uint32_t> m_available;

	public:
		GridECS();

		uint32_t create();
		void destroy(uint32_t handle);
	};

	class ECS
	{
	public:
		uint8_t m_index = 0;
		uint32_t m_type_index = 0;

		vector<EntityStream> m_streams;
		map<uint64_t, uint16_t> m_stream_map;

	public:
		ECS(int capacity = 1 << 10);

		ECS(const ECS& other) = delete;
		ECS& operator=(const ECS& other) = delete;

		template <class T>
		uint32_t type_index();

		template <class T>
		uint32_t type_mask();

		template <class... Types>
		uint64_t prototype();

		template <class... Types>
		EntityStream& stream();

		EntityStream& stream(uint32_t handle);

		vector<EntityStream*> match(uint64_t prototype);

		template <class... Types>
		void add_stream(cstring name);

#ifdef TWO_ECS_TYPED
		template <class T>
		void register_type();

		template <class... Types>
		void add_stream();
#endif

		uint32_t create(uint64_t prototype);

		template <class... Types>
		Entity create();

		void destroy(Entity handle);

		template <class T>
		void set(Entity handle, T component = T());

		template <class T>
		bool has(Entity handle);

		template <class T>
		T& get(Entity handle);

		template <class T, class... Types>
		vector<T*> gather();

		template <class... Types, class T_Function>
		void loop(T_Function action);

		template <class... Types, class T_Function>
		void loop_ent(T_Function action);
	};

	template <unsigned EcsType, unsigned NumComponents>
	class tECS : public ECS
	{
	public:
		void add_buffer(EntityStream& stream, uint64_t prototype, uint32_t index, unique<Buffer> buffer);

		void add_stream(uint64_t prototype, const string& name = "");

		EntityStream& stream(uint64_t prototype);

		Entity create(uint64_t prototype);
		Entity create(uint64_t prototype, uint32_t count);
	};

	export_ extern TWO_ECS_EXPORT ECS* s_ecs[256];

	export_ template <class T>
	inline bool isa(const Entity& entity) { return s_ecs[entity.m_ecs]->has<T>(entity); }

	export_ template <class T>
	inline T& asa(const Entity& entity) { return s_ecs[entity.m_ecs]->get<T>(entity); }

	export_ template <class T>
	inline T* try_asa(const Entity& entity) { if(entity && isa<T>(entity)) return &asa<T>(entity); else return nullptr; }
	
	export_ template <class T>
	inline T* try_asa(const Entity* entity) { if(entity && isa<T>(*entity)) return &asa<T>(*entity); else return nullptr; }

#ifdef TWO_ECS_TYPED
	struct EntityRef {};

	export_ template <> TWO_ECS_EXPORT Type& type<EntityRef>();

	inline Ref ent_ref(uint32_t entity) { return Ref((void*)uintptr_t(entity), type<EntityRef>()); }
	inline uint32_t as_ent(const Ref& ref) { return ref.m_type->is<EntityRef>() ? uint32_t((uintptr_t)ref.m_value) : UINT32_MAX; }
#endif

	inline string entity_prototype(const Entity& entity)
	{
		EntityStream& stream = s_ecs[entity.m_ecs]->stream(entity.m_stream);
		return stream.m_name;
	}

	template <class T>
	struct refl_ struct_ ComponentHandle : public Entity
	{
		ComponentHandle();
		//ComponentHandle(uint32_t handle, uint32_t stream);
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
		EntityHandle(Entity entity);
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
#include <stl/span.h>

namespace two
{
	export_ class refl_ TWO_ECS_EXPORT Complex
	{
	public:
		constr_ Complex(uint32_t id, Type& type);
		constr_ Complex(uint32_t id, Type& type, span<Ref> parts);
		virtual ~Complex();

		template <class... T_Parts>
		Complex(uint32_t id, Type& type, T_Parts&&... parts)
			: Complex(id, type)
		{
			swallow{ (this->add_part(Ref(&parts, two::type<type_class<T_Parts>>())), 1)... };
		}

		attr_ uint32_t m_id;
		attr_ Type& m_type;
		attr_ Prototype& m_prototype;

		attr_ vector<Ref> m_parts;

		meth_ void setup(span<Ref> parts);

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

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

#ifndef TWO_MODULES
#endif


namespace two
{
    // Exported types
    
    
    export_ template <> TWO_ECS_EXPORT Type& type<two::Entity>();
    export_ template <> TWO_ECS_EXPORT Type& type<two::Entt>();
    export_ template <> TWO_ECS_EXPORT Type& type<two::OEntt>();
    export_ template <> TWO_ECS_EXPORT Type& type<two::Complex>();
}



#include <stl/tuple.h>
#include <stl/algorithm.h>

//#include <cstdio>
#include <cassert>

namespace two
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

	inline BufferArray::BufferArray()
		: m_buffer_map(64)
	{}

	inline BufferArray::BufferArray(uint32_t size)
		: m_buffer_map(64)
	{
		m_handles.ensure(size);
	}

	template <class T>
	inline uint32_t BufferArray::type_index()
	{
		return TypedBuffer<T>::index();
	}

	template <class T>
	inline void BufferArray::add_buffer()
	{
#ifdef TWO_ECS_TYPED
		m_buffers.push_back(construct<TBuffer<T>>(type<T>()));
#else
		m_buffers.push_back(construct<TBuffer<T>>());
#endif
		assert(this->type_index<T>() < m_buffer_map.size());
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
	inline EntityStream::EntityStream(cstring name, uint16_t index, uint32_t size)
		: BufferArray(size)
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
		: BufferArray()
	{}

	inline uint32_t GridECS::create()
	{
		uint32_t handle = m_available.size() > 0 ? pop(m_available) : m_handles.alloc();
		//printf("ecs created handle %i\n", int(handle));
		m_handles.add(handle);
		this->add();
		return handle;
	}

	inline void GridECS::destroy(uint32_t handle)
	{
		//printf("ecs destroy handle %i\n", int(handle));
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
		return TypedBuffer<T>::index();
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
		m_streams.push_back({ name, index });
		m_streams.back().init<Types...>(prototype);
		m_stream_map[prototype] = index;
	}

#ifdef TWO_ECS_TYPED
	template <class T>
	inline void ECS::register_type()
	{
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
		const uint64_t prototype = ecs.prototype<Types...>();

		const vector<EntityStream*> matches = ecs.match(prototype);
		for(EntityStream* stream : matches)
		{
			tuple<TBuffer<Types>&...> buffers = { stream->buffer<Types>()... };

			const uint32_t size = stream->size();
			for(uint32_t i = 0; i < size; ++i)
			{
				Entity entity = { ecs.m_index, stream->m_index, stream->handle(i) };
				action(entity, at<Is>(buffers).m_data[i]...);
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
		m_streams.push_back({ name.c_str(), index });
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
	template <class T>
	inline EntityHandle<T>::EntityHandle(Entity entity) : ComponentHandle<T>(entity) {}
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

namespace two
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
