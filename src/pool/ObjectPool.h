//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <stl/memory.h>
#include <stl/vector.h>
#endif
#include <pool/Forward.h>
#include <pool/Pool.h>

namespace two
{
	export_ class TWO_POOL_EXPORT ObjectPool //
	{
	public:
		ObjectPool();

		ObjectPool(const ObjectPool& other) = delete;
		ObjectPool& operator=(const ObjectPool& other) = delete;

		void clear();

		inline Pool& pool(Type& type);

		template <class T>
		inline TPool<T>& pool();

		template <class T>
		inline TPool<T>& create_pool(size_t size = 12);

		vector<unique<Pool>> m_pools;
	};

	//export_extern TWO_POOL_EXPORT vector<unique<Pool>> g_pool_makers;
	export_ extern TWO_POOL_EXPORT vector<unique<Pool>> g_pools;

	export_ template <class T>
	inline TPool<T>& global_pool();
}
