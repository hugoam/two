//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <pool/Forward.h>
#include <pool/ObjectPool.h>
#include <pool/ChunkedPool.hpp>

namespace two
{
	inline Pool& ObjectPool::pool(Type& type) { return *m_pools[type.m_id].get(); }

	template <class T>
	inline ChunkedPool<T>& ObjectPool::pool()
	{
		if(!m_pools[type<T>().m_id])
			m_pools[type<T>().m_id] = make_unique<ChunkedPool<T>>();
		return as<ChunkedPool<T>>(*m_pools[type<T>().m_id].get());
	}

	template <class T>
	inline ChunkedPool<T>& ObjectPool::create_pool(uint32_t chunk_size)
	{
		m_pools[type<T>().m_id] = make_unique<ChunkedPool<T>>(chunk_size);
		return pool<T>();
	}

	template <class T>
	inline ChunkedPool<T>& global_pool()
	{
		if(!g_pools[type<T>().m_id])
			g_pools[type<T>().m_id] = make_unique<ChunkedPool<T>>();
		return as<ChunkedPool<T>>(*g_pools[type<T>().m_id].get());
	}
}
