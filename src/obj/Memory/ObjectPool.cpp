//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef MUD_CPP_20
#include <assert.h> // <cassert>
#include <stdint.h> // <cstdint>
#include <float.h> // <cfloat>
import std.core;
import std.memory;
#endif

#ifdef MUD_MODULES
module mud.obj;
#else
#include <obj/Config.h>
#include <obj/Memory/ObjectPool.h>
#include <obj/Reflect/Class.h>
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
		if(m_pools.find(&type) == m_pools.end())
			m_pools[&type] = type.m_class->m_make_pool();
		return *m_pools[&type].get();
	}

	GlobalPool::GlobalPool()
		: ObjectPool()
	{}
}
