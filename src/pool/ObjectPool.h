//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <pool/Forward.h>
#include <pool/Pool.h>
#include <infra/NonCopy.h>
#include <infra/Global.h>

#ifndef MUD_CPP_20
#include <unordered_map>
#include <memory>
#endif

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

		std::vector<unique_ptr<Pool>> m_pools;
	};

	//export_ extern MUD_POOL_EXPORT std::vector<unique_ptr<Pool>> g_pool_makers;
	export_ extern MUD_POOL_EXPORT std::vector<unique_ptr<Pool>> g_pools;

	template <class T>
	inline TPool<T>& global_pool()
	{
		if(!g_pools[type<T>().m_id])
			g_pools[type<T>().m_id] = make_unique<TPool<T>>();
		return as<TPool<T>>(*g_pools[type<T>().m_id].get());
	}

	export_ template <class T>
	class TGlobalPool
	{
		TGlobalPool() { global_pool<T>(); }
	};
}
