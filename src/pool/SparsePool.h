//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/unordered_map.h>
#include <stl/vector.h>
#include <infra/NonCopy.h>
#include <pool/Forward.h>

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
