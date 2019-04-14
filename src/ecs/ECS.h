
#pragma once

#include <stdint.h>
#include <stl/memory.h>
#include <stl/map.h>
#include <stl/string.h>
#include <pool/SparsePool.h>
#include <type/Type.h>
#include <type/Ref.h>
#include <ecs/Forward.h>
#include <ecs/Entity.h>
#include <ecs/Buffer.h>

namespace mud
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

#ifdef MUD_ECS_TYPED
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

	export_ extern MUD_ECS_EXPORT ECS* s_ecs[256];

	export_ template <class T>
	inline bool isa(const Entity& entity) { return s_ecs[entity.m_ecs]->has<T>(entity); }

	export_ template <class T>
	inline T& asa(const Entity& entity) { return s_ecs[entity.m_ecs]->get<T>(entity); }

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
