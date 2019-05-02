//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <type/Type.h>
#include <pool/Forward.h>
#include <pool/ObjectPool.h>
#include <pool/Pool.hpp>

namespace two
{
	inline Pool& ObjectPool::pool(Type& type) { return *m_pools[type.m_id].get(); }

	template <class T>
	inline TPool<T>& ObjectPool::pool()
	{
		if(!m_pools[type<T>().m_id])
			m_pools[type<T>().m_id] = make_unique<TPool<T>>();
		return as<TPool<T>>(*m_pools[type<T>().m_id].get());
	}

	template <class T>
	inline TPool<T>& ObjectPool::create_pool(size_t size)
	{
		m_pools[type<T>().m_id] = make_unique<TPool<T>>(size);
		return pool<T>();
	}

	template <class T>
	inline TPool<T>& global_pool()
	{
		if(!g_pools[type<T>().m_id])
			g_pools[type<T>().m_id] = make_unique<TPool<T>>();
		return as<TPool<T>>(*g_pools[type<T>().m_id].get());
	}
}
