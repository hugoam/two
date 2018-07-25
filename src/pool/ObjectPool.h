//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
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

		inline Pool& pool(Type& type) { return *m_pools[&type].get(); }

		template <class T>
		inline TPool<T>& pool()
		{
			if(m_pools.find(&type<T>()) == m_pools.end())
				m_pools[&type<T>()] = make_unique<TPool<T>>();
			return as<TPool<T>>(*m_pools[&type<T>()].get());
		}

		template <class T, class T_Func>
		inline void iterate_objects(T_Func func)
		{
			VecPool<T>* pool = this->pool<T>().m_vec_pool.get();
			for(; pool; pool = pool->m_next.get())
				for(T* object : pool->m_objects)
					func(*object);
		}

		template <class T>
		inline TPool<T>& create_pool(size_t size = 12) { m_pools[&type<T>()] = make_unique<TPool<T>>(size); return pool<T>(); }

		std::unordered_map<Type*, unique_ptr<Pool>> m_pools;
	};

	export_ class MUD_POOL_EXPORT GlobalPool : public ObjectPool, public LazyGlobal<GlobalPool>
	{
	public:
		GlobalPool();
	};
}
