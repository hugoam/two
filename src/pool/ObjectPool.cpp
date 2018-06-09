//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.pool;
#else
#include <infra/Config.h>
#include <pool/ObjectPool.h>
//#include <refl/Class.h>
#endif

namespace mud
{
	ObjectPool::ObjectPool()
	{}

	void ObjectPool::clear()
	{
		for(auto& kv : m_pools)
			kv.second->clear();
	}

	Pool& ObjectPool::pool(Type& type)
	{
		//if(m_pools.find(&type) == m_pools.end())
		//	m_pools[&type] = cls(type).m_make_pool();
		return *m_pools[&type].get();
	}

	GlobalPool::GlobalPool()
		: ObjectPool()
	{}
}
