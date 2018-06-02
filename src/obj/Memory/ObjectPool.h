//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Generated/Forward.h>
#include <obj/Memory/Pool.h>
#include <obj/NonCopy.h>
#include <obj/Util/Global.h>

#ifndef MUD_CPP_20
#include <unordered_map>
#include <memory>
#endif

namespace mud
{
	export_ class MUD_OBJ_EXPORT ObjectPool : public NonCopy
	{
	public:
		ObjectPool();

		void clear();

		Pool& pool(Type& type);

		template <class T>
		TPool<T>& pool() { return as<TPool<T>>(this->pool(type<T>())); }

		template <class T>
		TPool<T>& create_pool() { m_pools[&type<T>()] = make_unique<TPool<T>>(); return pool<T>(); }

		std::unordered_map<Type*, unique_ptr<Pool>> m_pools;
	};

	export_ class MUD_OBJ_EXPORT GlobalPool : public ObjectPool, public LazyGlobal<GlobalPool>
	{
	public:
		GlobalPool();
	};
}
