//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <pool/SparsePool.h>

namespace mud
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
	inline void OwnedHandle<T>::swap(OwnedHandle& other) { using mud::swap; swap(this->m_handle, other.m_handle); swap(this->m_pool, other.m_pool); }

	template <class T>
	inline OwnedHandle<T>::operator SparseHandle<T>() const { return { *this->m_pool, this->m_handle }; }
	

	template <> inline SparseIndices<false>::SparseIndices() {}
	template <> inline void SparseIndices<false>::add() { m_indices.emplace_back(); }
	template <> inline void SparseIndices<false>::clear() { m_indices.resize(m_indices.size(), UINT32_MAX); }
	template <> inline void SparseIndices<false>::erase(uint32_t handle) { m_indices[handle] = UINT32_MAX; }
	template <> inline void SparseIndices<false>::ensure(uint32_t capacity) { m_indices.resize(capacity, UINT32_MAX); }
	template <> inline uint32_t& SparseIndices<false>::operator[](uint32_t at) { return m_indices[at]; }
	template <> inline uint32_t SparseIndices<false>::size() const { return uint32_t(m_indices.size()); }

	inline SparseIndices<true>::SparseIndices() {}
	inline void SparseIndices<true>::add() {}
	inline void SparseIndices<true>::clear() { m_indices.clear(); }
	inline void SparseIndices<true>::erase(uint32_t handle) { m_indices.erase(handle); }
	inline void SparseIndices<true>::ensure(uint32_t capacity) { UNUSED(capacity); }
	inline uint32_t& SparseIndices<true>::operator[](uint32_t at) { return m_indices[at]; }
	inline uint32_t SparseIndices<true>::size() const { return uint32_t(m_indices.size()); }

	template <bool Dense>
	inline SparseHandles<Dense>::SparseHandles() {}
	template <bool Dense>
	inline void SparseHandles<Dense>::ensure(uint32_t capacity)
	{
		m_indices.ensure(capacity);
	}

	template <bool Dense>
	inline uint32_t SparseHandles<Dense>::alloc()
	{
		const uint32_t count = uint32_t(m_indices.size());
		m_indices.add();
		return count;
	}

	template <bool Dense>
	inline uint32_t SparseHandles<Dense>::create()
	{
		uint32_t handle = this->alloc();
		this->add(handle);
		return handle;
	}

	template <bool Dense>
	inline void SparseHandles<Dense>::add(uint32_t handle)
	{
		const uint32_t index = uint32_t(m_handles.size());
		m_indices[handle] = index;
		m_handles.push_back(handle);
	}

	template <bool Dense>
	inline uint32_t SparseHandles<Dense>::remove(uint32_t handle)
	{
		const uint32_t index = m_indices[handle];
		swap_pop(m_handles, index);

		const uint32_t moved = m_handles[index];
		m_indices[moved] = index;
		m_indices.erase(handle);
		return index;
	}

	template <bool Dense>
	inline void SparseHandles<Dense>::clear()
	{
		m_indices.clear();
		m_handles.clear();
	}

	template <bool Dense>
	inline uint32_t& SparseHandles<Dense>::operator[](uint32_t at) { return m_indices[at]; }

	template <bool Dense>
	inline uint32_t SparseHandles<Dense>::size() const { return uint32_t(m_handles.size()); }

	template <bool Dense>
	inline uint32_t SparseHandles<Dense>::count() const { return uint32_t(m_handles.size()); }

	template <bool Dense>
	inline uint32_t SparseHandles<Dense>::reverse(uint32_t index) const { return m_handles[index]; }

	template <bool Dense>
	inline uint32_t SparseHandles<Dense>::handle(uint32_t index) const { return m_handles[index]; }

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
