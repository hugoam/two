//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_CPP_20
#include <stl/stddef.h>
#endif

namespace mud
{
	//! LocklessQueue template: as provid3ed by Lf3THn4D
	//! Only 1 thread can push and 1 thread can pop it.
	template <class T>
	class LocklessQueue
	{
	private:
		T* m_buffer = nullptr;
		size_t m_head = 0;
		size_t m_tail = 0;
		size_t m_size;

	public:
		inline LocklessQueue(size_t size)
			: m_size(size + 1)
		{
			m_buffer = new/*low*/T[m_size];
		}

		inline ~LocklessQueue() { delete[] m_buffer; }

		inline bool empty() const { return (m_head == m_tail); }

		inline bool push(const T& obj)
		{
			size_t next_head = (m_head + 1) % m_size;
			if (next_head == m_tail) return false;
			m_buffer[m_head] = obj;
			m_head = next_head;
			return true;
		}


		inline bool pop(T& obj)
		{
			if (m_tail == m_head) return false;
			obj = m_buffer[m_tail];
			m_tail = (m_tail + 1) % m_size;
			return true;
		}
	};
}
