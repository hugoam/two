//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/algorithm.h>
#include <pool/VecPool.h>
#include <type/TypeUtils.h>

namespace mud
{
	template <class T>
	VecPool<T>::VecPool(size_t size)
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

	template <class T>
	VecPool<T>::~VecPool()
	{
		--s_count;

		for(T* object : m_objects)
			any_destruct(*object);
		operator delete(m_chunk);
	}

	template <class T>
	T* VecPool<T>::alloc()
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

	template <class T>
	void VecPool<T>::destroy(T* object)
	{
		any_destruct(*object);
		this->free(object);
	}

	template <class T>
	void VecPool<T>::free(T* object)
	{
		if(object < m_memory || object > m_last)
			return m_next->free(object);

		m_available.push_back(object);
		remove(m_objects, object);
	}

	template <class T>
	template <class... Types>
	inline T& VecPool<T>::construct(Types&&... args)
	{
		T* at = this->alloc();
		new (at) T(static_cast<Types&&>(args)...);
		return *at;
	}

	template <class T>
	int VecPool<T>::s_count = 0;
}
