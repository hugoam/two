
#pragma once

#include <cstdint>
#include <stl/memory.h>
#include <stl/map.h>
#include <stl/tuple.h>
#include <infra/Vector.h>
#include <infra/Generic.h>
#include <pool/SparsePool.h>
#include <type/Type.h>
#include <type/Ref.h>
#include <ecs/Forward.h>
#include <ecs/Entity.h>
#include <ecs/Buffer.h>
#include <ecs/SparseBuffer.h>

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
	
	template <typename F, typename... Types>
	void for_each(F&& f, Types&&... xs)
	{
		swallow{ (f(static_cast<Types&&>(xs)), 0)... };
	}

	template <typename... Types>
	uint64_t any_flags(Types... xs)
	{
		uint64_t flags = false;
		for_each([&flags](uint64_t x) { flags = flags | x; }, xs...);
		return flags;
	}

#ifdef _MSC_VER // sucks
	template <class... Args>
	struct select_last;

	template <typename T>
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
	template<typename T>
	struct tag
	{
		using type = T;
	};
	
	template<typename... Types>
	struct select_last
	{
		using type = typename decltype((tag<Types>{}, ...))::type;
	};
#endif

	using Typemap = vector<uint32_t>;

	template <bool Dense>
	class BufferArray
	{
	public:
		BufferArray(Typemap& typemap, uint32_t size = 0)
			: m_typemap(typemap)
			, m_buffer_map(64)
		{
			m_handles.ensure(size);
		}

		BufferArray(BufferArray&& other) = default;
		BufferArray& operator=(BufferArray&& other) = default;

		BufferArray(const BufferArray& other) = delete;
		BufferArray& operator=(const BufferArray& other) = delete;

		template <class T>
		uint32_t type_index()
		{
#if 0 //def MUD_ECS_TYPED
			return m_typemap[type<T>().m_id];
#else
			return TypedBuffer<T>::index();
#endif
		}

		template <class T>
		void add_buffer()
		{
#ifdef MUD_ECS_TYPED
			m_buffers.emplace_back(construct<TBuffer<T>>(type<T>()));
#else
			m_buffers.emplace_back(construct<TBuffer<T>>());
#endif
			m_buffer_map[this->type_index<T>()] = &(*m_buffers.back());
		}

		template <class... Types>
		void init()
		{
			swallow{ (this->add_buffer<Types>(), 0)... };
		}

		template <class T>
		TBuffer<T>& buffer()
		{
			return static_cast<TBuffer<T>&>(*m_buffer_map[this->type_index<T>()]);
		}

		uint32_t size() const { return m_handles.size(); }

		uint32_t reverse(uint32_t index) const { return m_handles.reverse(index); }
		uint32_t handle(uint32_t index) const { return m_handles.reverse(index); }

		void ensure(uint32_t capacity)
		{
			m_handles.ensure(capacity);
		}

		void clear()
		{
			m_handles.clear();
			for(auto& buffer : m_buffers)
				buffer->clear();
		}

		uint32_t create()
		{
			const uint32_t handle = m_handles.create();
			for (auto& buffer : m_buffers)
				buffer->add();
			return handle;
		}

		void add(uint32_t handle)
		{
			m_handles.add(handle);
			for(auto& buffer : m_buffers)
				buffer->add();
		}

		void remove(uint32_t handle)
		{
			const uint32_t index = m_handles.remove(handle);
			for(auto& buffer : m_buffers)
				buffer->remove(index);
		}

		template <class T>
		void set(uint32_t handle, T component = T())
		{
			uint32_t index = m_handles[handle];
			this->buffer<T>().m_data[index] = move(component);
		}

		template <class T>
		T& get(uint32_t handle)
		{
			uint32_t index = m_handles[handle];
			return this->buffer<T>().m_data[index];
		}

		template <class T>
		T& has(uint32_t handle)
		{
			T& comp = this->get<T>(handle);
			return comp.m_enabled;
		}

		Typemap& m_typemap;

		SparseHandles<Dense> m_handles;

		vector<unique<Buffer>> m_buffers;
		vector<Buffer*> m_buffer_map;
	};

	class EntityStream : public BufferArray<false>
	{
	public:
		EntityStream(cstring name, Typemap& typemap, uint32_t size = 0)
			: BufferArray<false>(typemap, size)
			, m_name(name)
		{}

		template <class... Types>
		void init(uint64_t prototype)
		{
			m_prototype = prototype;
			swallow{ (this->add_buffer<Types>(), 0)... };
		}

		cstring m_name;
		uint64_t m_prototype;
	};

	class GridECS : public BufferArray<false>
	{
	public:
		Typemap m_typemap;
		vector<uint32_t> m_available;

	public:
		GridECS()
			: BufferArray<false>(m_typemap)
		{}

		uint32_t create()
		{
			uint32_t handle = m_available.size() > 0 ? pop(m_available) : m_handles.alloc();
			this->add(handle);
			return handle;
		}

		void destroy(uint32_t handle)
		{
			this->remove(handle);
			m_available.push_back(handle);
		}
	};

	template <class T>
	T& Entt::comp() { return m_ecs->get<T>(m_handle); }

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
		ECS(int capacity = 1 << 10)
		{
			m_streams.reserve(64);
			m_entities.reserve(capacity);
		}

		ECS(const ECS& other) = delete;
		ECS& operator=(const ECS& other) = delete;

		template <class T>
		uint32_t type_index()
		{
#if 0 //def MUD_ECS_TYPED
			return m_typemap[type<T>().m_id];
#else
			return TypedBuffer<T>::index();
#endif
		}

		template <class... Types>
		uint64_t prototype()
		{
			return any_flags(1ULL << this->type_index<Types>()...);
		}

		template <class... Types>
		EntityStream& stream()
		{
			uint64_t prototype = this->prototype<Types...>();
			uint16_t stream = m_stream_map[prototype];
			return m_streams[stream];
		}

		EntityStream& stream(uint32_t handle)
		{
			uint16_t stream = m_entities[handle].m_stream;
			return m_streams[stream];
		}

		vector<EntityStream*> match(uint64_t prototype)
		{
			vector<EntityStream*> matches;
			for(EntityStream& buffers : m_streams)
				if((buffers.m_prototype & prototype) == prototype)
					matches.push_back(&buffers);
			return matches;
		}

		template <class... Types>
		void add_stream(cstring name)
		{
			uint64_t prototype = this->prototype<Types...>();
			m_stream_map[prototype] = uint16_t(m_streams.size());
			m_streams.emplace_back(name, m_typemap);
			m_streams.back().init<Types...>(prototype);
		}

#ifdef MUD_ECS_TYPED
		template <class T>
		void register_type()
		{
#if 0
			if(m_typemap[type<T>().m_id] == 0)
				m_typemap[type<T>().m_id] = ++m_type_index;
#endif
		}

		template <class... Types>
		void add_stream()
		{
			using T_Prototype = typename select_last<Types...>::type;
			this->add_stream<Types...>(type<T_Prototype>().m_name);
			swallow{ (this->register_type<Types&&>(), 0)... };
		}
#endif

		void ensure_size()
		{
			for(auto& buffer : m_streams)
				buffer.ensure(uint32_t(m_entities.size()));
		}

		uint32_t alloc(uint64_t prototype, uint16_t stream)
		{
			if(m_available.size() > 0)
				return pop(m_available);
			uint32_t handle = uint32_t(m_entities.size());
			m_entities.push_back({ prototype, stream });
			this->ensure_size();
			return handle;
		}

		template <class... Types>
		uint32_t create()
		{
			uint64_t prototype = this->prototype<Types...>();
			if(m_stream_map.find(prototype) == m_stream_map.end())
				this->add_stream<Types...>();
			uint16_t stream = m_stream_map[prototype];
			uint32_t handle = this->alloc(prototype, stream);
			m_streams[stream].add(handle);
			return handle;
		}

		void destroy(uint32_t handle)
		{
			EntityData& entity = m_entities[handle];
			m_streams[entity.m_stream].remove(handle);
			m_available.push_back(handle);
		}

		template <class T>
		void set(uint32_t handle, T component = T())
		{
			EntityData& entity = m_entities[handle];
			m_streams[entity.m_stream].set<T>(handle, move(component));
		}

		template <class T>
		bool has(uint32_t handle)
		{
			uint64_t flag = (1ULL << this->type_index<T>());
			EntityData& entity = m_entities[handle];
			return (entity.m_prototype & flag) != 0;
		}

		template <class T>
		T& get(uint32_t handle)
		{
			EntityData& entity = m_entities[handle];
			return m_streams[entity.m_stream].get<T>(handle);
		}

		template <class T, class... Types>
		vector<T*> gather()
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
		void loop_ent_impl(T_Function action, index_sequence<Is...>)
		{
			uint64_t prototype = this->prototype<Types...>();

			vector<EntityStream*> matches = this->match(prototype);
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
		void loop_impl(T_Function action, index_sequence<Is...>)
		{
			uint64_t prototype = this->prototype<Types...>();

			vector<EntityStream*> matches = this->match(prototype);
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
		void loop(T_Function action)
		{
			this->loop_impl<Types...>(action, index_tuple<sizeof...(Types)>());
		}

		template <class... Types, class T_Function>
		void loop_ent(T_Function action)
		{
			this->loop_ent_impl<Types...>(action, index_tuple<sizeof...(Types)>());
		}
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