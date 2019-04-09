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
		, m_memory(operator new(size * sizeof(T)))
		, m_first((T*)m_memory)
		, m_last(m_first)
		, m_end(m_first + size - 1)
	{
		++s_count;
		//printf("VecPool for type %s, count %u, size %u\n", type<T>().name().c_str(), s_count, size * sizeof(T));

		m_objects.reserve(size);
	}

	template <class T>
	VecPool<T>::~VecPool()
	{
		--s_count;

		for(T* object : m_objects)
			any_destruct(*object);
		operator delete(m_memory);
	}

	template <class T>
	T* VecPool<T>::alloc()
	{
		bool fits = m_end - m_last >= 1 || !m_recycled.empty();
		if(!fits && !m_next)
			m_next = make_unique<VecPool<T>>(m_size * 2);
		if(!fits)
			return m_next->alloc();

		T* object = !m_recycled.empty() ? pop(m_recycled) : m_last++;
		m_objects.push_back(object);
		return object;
	}

	template <class T>
	span<T> VecPool<T>::alloc(size_t count)
	{
		bool fits = size_t(m_end - m_last) >= count;
		if(!fits && !m_next)
			m_next = make_unique<VecPool<T>>(m_size * 2);
		if(!fits)
			return m_next->alloc(count);

		span<T> objects = { m_last, count };
		m_last += count;
		for(size_t i = 0; i < count; ++i)
			m_objects.push_back(&objects[i]);
		return objects;
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
		if(object < m_first || object > m_end)
			return m_next->free(object);

		m_recycled.push_back(object);
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
