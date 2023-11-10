//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
module two.pool;
#else
#include <infra/Config.h>
#include <pool/ObjectPool.h>
#include <pool/ObjectPool.hpp>
//#include <refl/Class.h>
#endif

namespace two
{
	vector<unique<Pool>> g_pools = vector<unique<Pool>>(c_max_types);

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
