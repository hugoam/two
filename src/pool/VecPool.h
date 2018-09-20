//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <infra/NonCopy.h>
#include <infra/Vector.h>
#include <obj/Unique.h>
#include <obj/TypeUtils.h>

namespace mud
{
	export_ template<class T>
	class VecPool : public NonCopy
	{
	public:
		VecPool(size_t size = 256)
			: m_size(size)
			, m_chunk(operator new(size * sizeof(T)))
			, m_memory((T*)m_chunk)
			, m_last(m_memory + size - 1)
		{
			++s_count;
			//printf("VecPool for type %s, count %u, size %u\n", type<T>().name().c_str(), s_count, size * sizeof(T));

			m_available.reserve(size);
			m_objects.reserve(size);

			for(size_t i = 0; i < size; ++i)
				m_available.push_back(&m_memory[i]);
		}

		~VecPool()
		{
			--s_count;

			for(T* object : m_objects)
				any_destruct(*object);
			operator delete(m_chunk);
		}

		T* alloc()
		{
			if(m_available.empty() && !m_next)
				m_next = make_unique<VecPool<T>>(m_size * 2);
			if(m_available.empty())
				return m_next->alloc();

			T* object = m_available.back();
			m_available.pop_back();
			m_objects.push_back(object);
			return object;
		}

		void destroy(T* object)
		{
			any_destruct(*object);
			this->free(object);
		}

		void free(T* object)
		{
			if(object < m_memory || object > m_last)
				return m_next->free(object);

			m_available.push_back(object);
			vector_remove(m_objects, object);
		}

	public:
		template<class... Types>
		inline T& construct(Types&&... args)
		{
			T* at = this->alloc();
			new (at) T(std::forward<Types>(args)...);
			return *at;
		}

	public:
		size_t m_size;
		std::vector<T*> m_available;
		std::vector<T*> m_objects;
		void* m_chunk;
		T* m_memory;
		T* m_last;

		unique_ptr<VecPool<T>> m_next;

		static int s_count;
	};
	
	template<class T>
	int VecPool<T>::s_count = 0;
}
