//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
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
	vector<unique_ptr<Pool>> g_pools = vector<unique_ptr<Pool>>(c_max_types);

	ObjectPool::ObjectPool()
		: m_pools(c_max_types)
	{}

	void ObjectPool::clear()
	{
		for(auto& pool : m_pools)
			if(pool)
				pool->clear();
	}
}
