//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <pool/Forward.h>
#include <pool/VecPool.h>
#include <type/Any.h>

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

		virtual void alloc(Ref& ref) { set<T>(ref, m_vec_pool->alloc()); }
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
			new (at) T(std::forward<Types>(args)...);
			return *at;
		}

		unique_ptr<VecPool<T>> m_vec_pool;
	};

	export_ class refl_ MUD_POOL_EXPORT HandlePool
	{
	public:
		virtual ~HandlePool() {}

		//virtual uint32_t create() = 0;
		//virtual void destroy(uint32_t handle) = 0;
		virtual void clear() = 0;
	};

	template <class T>
	class SparsePool;

	template <class T>
	struct SparseHandle
	{
		SparseHandle() {}
		SparseHandle(SparsePool<T>& pool, uint32_t handle) : m_pool(&pool), m_handle(handle) {}

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
	struct OwnedHandle
	{
		OwnedHandle() {}
		OwnedHandle(SparsePool<T>& pool, uint32_t handle) : m_pool(&pool), m_handle(handle) {}
		~OwnedHandle();

		OwnedHandle(OwnedHandle<T>& other) = delete;
		OwnedHandle& operator=(OwnedHandle<T>& other) = delete;

		OwnedHandle(OwnedHandle<T>&& other) { other.swap(*this); }
		OwnedHandle& operator=(OwnedHandle<T>&& other) { other.swap(*this); return *this; }
		void swap(OwnedHandle<T>& other) { std::swap(m_handle, other.m_handle); std::swap(m_pool, other.m_pool); }

		operator SparseHandle<T>() const { return { *m_pool, m_handle }; }

		operator T&();
		operator const T&() const;
		T* operator->() { return &((T&)*this); }
		T& operator*() { return *this; }
		const T* operator->() const { return &((const T&)*this); }
		const T& operator*() const { return *this; }

		SparsePool<T>* m_pool = nullptr;
		uint32_t m_handle = UINT32_MAX;
	};

	export_ template <class T>
	class SparsePool : public NonCopy, public HandlePool
	{
	public:
		SparsePool() {}
		~SparsePool() {}

		uint32_t handle()
		{
			if(!m_available.empty())
				return vector_pop(m_available);
			uint32_t count = uint32_t(m_indices.size());
			m_indices.resize(count + 1);
			return count;
		}

		OwnedHandle<T> create()
		{
			uint32_t handle = this->handle();
			m_indices[handle] = m_objects.size();
			m_objects.emplace_back();
			m_handles.push_back(handle);
			return { *this, handle };
		}

		void destroy(uint32_t handle)
		{
			uint32_t index = m_indices[handle];
			std::swap(m_objects[index], m_objects.back());
			std::swap(m_handles[index], m_handles.back());
			m_objects.pop_back();
			m_handles.pop_back();
			m_indices[m_handles[index]] = index;
			m_available.push_back(handle);
		}

		T& get(uint32_t handle)
		{
			uint32_t index = m_indices[handle];
			return m_objects[index];
		}

		template <class... Types>
		inline OwnedHandle<T> construct(Types&&... args)
		{
			uint32_t handle = this->handle();
			m_indices[handle] = uint32_t(m_objects.size());
			m_objects.emplace_back(std::forward<Types>(args)...);
			m_handles.push_back(handle);
			return { *this, handle };
		}

		virtual void clear()
		{
			m_handles.clear();
			m_objects.clear();
			m_available.clear();
		}

	public:
		std::vector<T> m_objects;
		std::vector<uint32_t> m_handles;
		std::vector<uint32_t> m_indices;
		std::vector<uint32_t> m_available;
	};

	template <class T>
	OwnedHandle<T>::~OwnedHandle() { if(m_pool && m_handle != UINT32_MAX) { DestroyHandle<T>::destroy(*this); m_pool->destroy(m_handle); } }

	template <class T>
	OwnedHandle<T>::operator T&() { return m_pool->get(m_handle); }
	
	template <class T>
	OwnedHandle<T>::operator const T&() const { return m_pool->get(m_handle); }

	template <class T>
	SparseHandle<T>::operator T&() { return m_pool->get(m_handle); }

	template <class T>
	SparseHandle<T>::operator const T&() const { return m_pool->get(m_handle); }
}
