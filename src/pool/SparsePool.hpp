//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <pool/SparsePool.h>

namespace two
{
	template <class T>
	inline SparseHandle<T>::SparseHandle() {}
	template <class T>
	inline SparseHandle<T>::SparseHandle(SparsePool<T>& pool, uint32_t handle) : m_pool(&pool), m_handle(handle) {}

	template <class T>
	inline void SparseHandle<T>::destroy() { if(m_pool && m_handle != UINT32_MAX) { DestroyHandle<T>::destroy(*this); m_pool->destroy(m_handle); } }

	template <class T>
	inline SparseHandle<T>::operator bool() const { return m_handle != UINT32_MAX; }
	template <class T>
	inline SparseHandle<T>::operator T&() { return m_pool->get(m_handle); }
	template <class T>
	inline SparseHandle<T>::operator const T&() const { return m_pool->get(m_handle); }
	template <class T>
	inline T* SparseHandle<T>::operator->() { return &((T&)*this); }
	template <class T>
	inline T& SparseHandle<T>::operator*() { return *this; }
	template <class T>
	inline const T*SparseHandle<T>::operator->() const { return &((const T&)*this); }
	template <class T>
	inline const T& SparseHandle<T>::operator*() const { return *this; }

	template <class T>
	inline OwnedHandle<T>::OwnedHandle() {}
	template <class T>
	inline OwnedHandle<T>::OwnedHandle(SparsePool<T>& pool, uint32_t handle) : SparseHandle<T>(pool, handle) {}
	template <class T>
	inline OwnedHandle<T>::~OwnedHandle() { this->destroy(); }

	template <class T>
	inline OwnedHandle<T>::OwnedHandle(OwnedHandle&& other) { other.swap(*this); }
	template <class T>
	inline OwnedHandle<T>& OwnedHandle<T>::operator=(OwnedHandle&& other) { other.swap(*this); return *this; }

	template <class T>
	inline void OwnedHandle<T>::swap(OwnedHandle& other) { using stl::swap; swap(this->m_handle, other.m_handle); swap(this->m_pool, other.m_pool); }

	template <class T>
	inline OwnedHandle<T>::operator SparseHandle<T>() const { return { *this->m_pool, this->m_handle }; }
	
	inline SparseHandles::SparseHandles() {}
	inline void SparseHandles::ensure(uint32_t capacity)
	{
		m_indices.resize(capacity, UINT32_MAX);
	}

	inline uint32_t SparseHandles::alloc()
	{
		const uint32_t index = uint32_t(m_indices.size());
		m_indices.emplace_back();
		return index;
	}

	inline uint32_t SparseHandles::alloc(uint32_t count)
	{
		const uint32_t index = uint32_t(m_indices.size());
		m_indices.resize(m_indices.size() + count);
		return index;
	}

	inline uint32_t SparseHandles::create()
	{
		uint32_t handle = this->alloc();
		this->add(handle);
		return handle;
	}

	inline uint32_t SparseHandles::create(uint32_t count)
	{
		uint32_t first = this->alloc(count);
		for(uint32_t handle = first; handle < first + count; ++handle)
			this->add(handle);
		return first;
	}

	inline void SparseHandles::add(uint32_t handle)
	{
		const uint32_t index = uint32_t(m_handles.size());
		m_indices[handle] = index;
		m_handles.push_back(handle);
	}

	inline uint32_t SparseHandles::remove(uint32_t handle)
	{
		const uint32_t index = m_indices[handle];
		const bool back = index == m_handles.size() - 1;
		swap_pop(m_handles, index);

		if(!back)
		{
			const uint32_t moved = m_handles[index];
			m_indices[moved] = index;
		}
		m_indices[handle] = UINT32_MAX;
		return index;
	}

	inline void SparseHandles::clear()
	{
		m_indices.resize(m_indices.size(), UINT32_MAX);
		m_handles.clear();
	}

	inline uint32_t& SparseHandles::operator[](uint32_t at) { return m_indices[at]; }

	inline uint32_t SparseHandles::size() const { return uint32_t(m_handles.size()); }

	inline uint32_t SparseHandles::count() const { return uint32_t(m_handles.size()); }

	inline uint32_t SparseHandles::reverse(uint32_t index) const { return m_handles[index]; }

	inline uint32_t SparseHandles::handle(uint32_t index) const { return m_handles[index]; }

	template <class T>
	inline SparsePool<T>::SparsePool() {}
	template <class T>
	inline SparsePool<T>::~SparsePool() {}

	template <class T>
	template <class... Types>
	inline OwnedHandle<T> SparsePool<T>::create(Types&&... args)
	{
		uint32_t handle = m_available.empty() ? m_handles.alloc() : pop(m_available);
		m_objects.push_back(T(static_cast<Types&&>(args)...));
		m_handles.add(handle);
		return { *this, handle };
	}

	template <class T>
	inline void SparsePool<T>::destroy(uint32_t handle)
	{
		uint32_t index = m_handles.remove(handle);
		swap_pop(m_objects, index);
		m_available.push_back(handle);
	}

	template <class T>
	inline T& SparsePool<T>::get(uint32_t handle)
	{
		uint32_t index = m_handles[handle];
		return m_objects[index];
	}

	template <class T>
	inline void SparsePool<T>::clear()
	{
		m_handles.clear();
		m_objects.clear();
		m_available.clear();
	}
}
