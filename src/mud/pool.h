#pragma once

#include <mud/infra.h>
#include <mud/type.h>



#ifndef MUD_POOL_EXPORT
#define MUD_POOL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	class HandlePool;
    class Pool;
    class ObjectPool;
}


#include <stl/memory.h>
//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net





namespace mud
{
	export_ template<class T>
	class VecPool : public NonCopy
	{
	public:
		VecPool(size_t size = 256)
			: m_size(size)
			, m_chunk(operator new(size * sizeof(T)))
			, m_memory((T*)m_chunk)
			, m_last(m_memory + size - 1)
		{
			++s_count;
			//printf("VecPool for type %s, count %u, size %u\n", type<T>().name().c_str(), s_count, size * sizeof(T));

			m_available.reserve(size);
			m_objects.reserve(size);

			for(size_t i = 0; i < size; ++i)
				m_available.push_back(&m_memory[i]);
		}

		~VecPool()
		{
			--s_count;

			for(T* object : m_objects)
				any_destruct(*object);
			operator delete(m_chunk);
		}

		T* alloc()
		{
			if(m_available.empty() && !m_next)
				m_next = make_unique<VecPool<T>>(m_size * 2);
			if(m_available.empty())
				return m_next->alloc();

			T* object = m_available.back();
			m_available.pop_back();
			m_objects.push_back(object);
			return object;
		}

		void destroy(T* object)
		{
			any_destruct(*object);
			this->free(object);
		}

		void free(T* object)
		{
			if(object < m_memory || object > m_last)
				return m_next->free(object);

			m_available.push_back(object);
			vector_remove(m_objects, object);
		}

	public:
		template<class... Types>
		inline T& construct(Types&&... args)
		{
			T* at = this->alloc();
			new (at) T(static_cast<Types&&>(args)...);
			return *at;
		}

	public:
		size_t m_size;
		vector<T*> m_available;
		vector<T*> m_objects;
		void* m_chunk;
		T* m_memory;
		T* m_last;

		unique<VecPool<T>> m_next;

		static int s_count;
	};
	
	template<class T>
	int VecPool<T>::s_count = 0;
}

#include <new>

namespace mud
{
	export_ class refl_ MUD_POOL_EXPORT Pool
	{
	public:
		virtual ~Pool() {}

		virtual void reset() = 0;
		virtual void clear() = 0;

		virtual void alloc(Ref& ref) = 0;
		virtual Ref alloc() = 0;

		virtual void destroy(Ref object) = 0;
		virtual void free(Ref object) = 0;
	};

	export_ template <class T>
	class TPool : public Pool
	{
	public:
		TPool(size_t size = 12) : m_vec_pool(make_unique<VecPool<T>>(size)) {}
		~TPool() {}

		inline T* talloc() { return m_vec_pool->alloc(); }
		inline void tdestroy(T& object) { m_vec_pool->destroy(&object); }
		inline void tfree(T& object) { m_vec_pool->free(&object); }

		virtual void alloc(Ref& ref) { setval<T>(ref, m_vec_pool->alloc()); }
		virtual Ref alloc() { return Ref(m_vec_pool->alloc(), type<T>()); }

		virtual void destroy(Ref object) { m_vec_pool->destroy(&val<T>(object)); }
		virtual void free(Ref object) { m_vec_pool->free(&val<T>(object)); }

		inline void reset(size_t size) { m_vec_pool = make_unique<VecPool<T>>(size); }
		virtual void reset() { m_vec_pool = make_unique<VecPool<T>>(12); }
		virtual void clear() { m_vec_pool = nullptr; }

		template <class... Types>
		inline T& construct(Types&&... args)
		{
			T* at = this->talloc();
			new (at) T(static_cast<Types&&>(args)...);
			return *at;
		}

		template <class T_Func>
		inline void iterate(T_Func func) const
		{
			VecPool<T>* pool = m_vec_pool.get();
			for(; pool; pool = pool->m_next.get())
				for(T* object : pool->m_objects)
					func(*object);
		}

		template <class T_Test>
		inline T* find(T_Test test) const
		{
			VecPool<T>* pool = m_vec_pool.get();
			for(; pool; pool = pool->m_next.get())
				for(T* object : pool->m_objects)
					if(test(*object))
						return object;
			return nullptr;
		}

		unique<VecPool<T>> m_vec_pool;
	};
}

namespace mud
{
	export_ class MUD_POOL_EXPORT ObjectPool : public NonCopy
	{
	public:
		ObjectPool();

		void clear();

		inline Pool& pool(Type& type) { return *m_pools[type.m_id].get(); }

		template <class T>
		inline TPool<T>& pool()
		{
			if(!m_pools[type<T>().m_id])
				m_pools[type<T>().m_id] = make_unique<TPool<T>>();
			return as<TPool<T>>(*m_pools[type<T>().m_id].get());
		}

		template <class T>
		inline TPool<T>& create_pool(size_t size = 12) { m_pools[type<T>().m_id] = make_unique<TPool<T>>(size); return pool<T>(); }

		vector<unique<Pool>> m_pools;
	};

	//export_ extern MUD_POOL_EXPORT vector<unique<Pool>> g_pool_makers;
	export_ extern MUD_POOL_EXPORT vector<unique<Pool>> g_pools;

	template <class T>
	inline TPool<T>& global_pool()
	{
		if(!g_pools[type<T>().m_id])
			g_pools[type<T>().m_id] = make_unique<TPool<T>>();
		return as<TPool<T>>(*g_pools[type<T>().m_id].get());
	}
}
//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net


#include <stl/unordered_map.h>
#include <stl/vector.h>

#include <cstdint>
#include <new>

namespace mud
{
	export_ class refl_ MUD_POOL_EXPORT HandlePool
	{
	public:
		virtual ~HandlePool() {}
		virtual void clear() = 0;
	};

	template <class T>
	class SparsePool;

	template <class T>
	struct refl_ struct_ SparseHandle
	{
		SparseHandle() {}
		SparseHandle(SparsePool<T>& pool, uint32_t handle) : m_pool(&pool), m_handle(handle) {}

		explicit operator bool() const { return m_handle != UINT32_MAX; }

		void destroy();

		operator T&();
		operator const T&() const;

		T* operator->() { return &((T&)*this); }
		T& operator*() { return *this; }
		const T* operator->() const { return &((const T&)*this); }
		const T& operator*() const { return *this; }

		SparsePool<T>* m_pool = nullptr;
		uint32_t m_handle = UINT32_MAX;
	};

	template <class T>
	struct OwnedHandle;

	template <class T>
	struct DestroyHandle
	{
		static void destroy(const OwnedHandle<T>& handle) { UNUSED(handle); }
	};

	template <class T>
	struct refl_ struct_ nocopy_ OwnedHandle : public SparseHandle<T>
	{
		OwnedHandle() {}
		OwnedHandle(SparsePool<T>& pool, uint32_t handle) : SparseHandle<T>(pool, handle) {}
		~OwnedHandle() { this->destroy(); }

		OwnedHandle(OwnedHandle& other) = delete;
		OwnedHandle& operator=(OwnedHandle& other) = delete;

		OwnedHandle(OwnedHandle&& other) { other.swap(*this); }
		OwnedHandle& operator=(OwnedHandle&& other) { other.swap(*this); return *this; }

		void swap(OwnedHandle& other) { using mud::swap; swap(this->m_handle, other.m_handle); swap(this->m_pool, other.m_pool); }

		operator SparseHandle<T>() const { return { *this->m_pool, this->m_handle }; }
	};

	template <bool Dense = false>
	class SparseIndices
	{
	public:
		SparseIndices() {}

		void add() { m_indices.emplace_back(); }
		void clear() { m_indices.resize(m_indices.size(), UINT32_MAX); }
		void erase(uint32_t handle) { m_indices[handle] = UINT32_MAX; }
		void ensure(uint32_t capacity) { m_indices.resize(capacity, UINT32_MAX); }
		uint32_t& operator[](uint32_t at) { return m_indices[at]; }
		uint32_t size() const { return uint32_t(m_indices.size()); }

	private:
		vector<uint32_t> m_indices;
	};

	template <>
	class SparseIndices<true>
	{
	public:
		SparseIndices() {}

		void add() {}
		void clear() { m_indices.clear(); }
		void erase(uint32_t handle) { m_indices.erase(handle); }
		void ensure(uint32_t capacity) { UNUSED(capacity); }
		uint32_t& operator[](uint32_t at) { return m_indices[at]; }
		uint32_t size() const { return uint32_t(m_indices.size()); }

	private:
		unordered_map<uint32_t, uint32_t> m_indices;
	};

	template <bool Dense = false>
	class SparseHandles
	{
	public:
		SparseHandles() {}

		void ensure(uint32_t capacity)
		{
			m_indices.ensure(capacity);
		}

		uint32_t alloc()
		{
			const uint32_t count = uint32_t(m_indices.size());
			m_indices.add();
			return count;
		}

		uint32_t create()
		{
			uint32_t handle = this->alloc();
			this->add(handle);
			return handle;
		}

		void add(uint32_t handle)
		{
			const uint32_t index = uint32_t(m_handles.size());
			m_indices[handle] = index;
			m_handles.push_back(handle);
		}

		uint32_t remove(uint32_t handle)
		{
			const uint32_t index = m_indices[handle];
			swap_pop(m_handles, index);

			const uint32_t moved = m_handles[index];
			m_indices[moved] = index;
			m_indices.erase(handle);
			return index;
		}

		void clear()
		{
			m_indices.clear();
			m_handles.clear();
		}

		uint32_t& operator[](uint32_t at) { return m_indices[at]; }

		uint32_t size() const { return uint32_t(m_handles.size()); }
		uint32_t count() const { return uint32_t(m_handles.size()); }

		uint32_t reverse(uint32_t index) const { return m_handles[index]; }
		uint32_t handle(uint32_t index) const { return m_handles[index]; }

	private:
		SparseIndices<Dense> m_indices;
		vector<uint32_t> m_handles;
	};

	export_ template <class T>
	class SparsePool : public NonCopy, public HandlePool
	{
	public:
		SparsePool() {}
		~SparsePool() {}

		template <class... Types>
		inline OwnedHandle<T> create(Types&&... args)
		{
			uint32_t handle = m_available.empty() ? m_handles.alloc() : pop(m_available);
			m_objects.emplace_back(static_cast<Types&&>(args)...);
			m_handles.add(handle);
			return { *this, handle };
		}

		void destroy(uint32_t handle)
		{
			uint32_t index = m_handles.remove(handle);
			swap_pop(m_objects, index);
			m_available.push_back(handle);
		}

		T& get(uint32_t handle)
		{
			uint32_t index = m_handles[handle];
			return m_objects[index];
		}

		virtual void clear()
		{
			m_handles.clear();
			m_objects.clear();
			m_available.clear();
		}

	public:
		SparseHandles<false> m_handles;
		vector<T> m_objects;
		vector<uint32_t> m_available;
	};

	template <class T>
	void SparseHandle<T>::destroy() { if(m_pool && m_handle != UINT32_MAX) { DestroyHandle<T>::destroy(*this); m_pool->destroy(m_handle); } }

	template <class T>
	SparseHandle<T>::operator T&() { return m_pool->get(m_handle); }

	template <class T>
	SparseHandle<T>::operator const T&() const { return m_pool->get(m_handle); }
}


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

#ifndef MUD_MODULES
#endif

#ifndef MUD_CPP_20
#include <stl/string.h>
#include <cstdint>
#include <stl/vector.h>
#endif


namespace mud
{
    // Exported types
    
    export_ template <> MUD_POOL_EXPORT Type& type<mud::HandlePool>();
    export_ template <> MUD_POOL_EXPORT Type& type<mud::Pool>();
    
    export_ template struct MUD_POOL_EXPORT Typed<vector<mud::HandlePool*>>;
    export_ template struct MUD_POOL_EXPORT Typed<vector<mud::Pool*>>;
}

