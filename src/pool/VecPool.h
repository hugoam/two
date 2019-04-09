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
		span<T> alloc(size_t count);
		void destroy(T* object);
		void free(T* object);

	public:
		template <class... Types>
		inline T& construct(Types&&... args);

	public:
		size_t m_size;
		vector<T*> m_recycled;
		vector<T*> m_objects;
		void* m_memory;
		T* m_first;
		T* m_last;
		T* m_end;

		unique<VecPool<T>> m_next;

		static int s_count;
	};
}
