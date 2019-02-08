//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/vector.h>
#include <type/Unique.h>

namespace mud
{
	export_ template <class T>
	class VecPool
	{
	public:
		VecPool(size_t size = 256);
		~VecPool();

		T* alloc();
		void destroy(T* object);
		void free(T* object);

	public:
		template <class... Types>
		inline T& construct(Types&&... args);

	public:
		size_t m_size;
		vector<T*> m_available;
		vector<T*> m_objects;
		void* m_chunk;
		T* m_memory;
		T* m_last;

		unique<VecPool<T>> m_next;

		static int s_count;
	};
}
