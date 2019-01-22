//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <infra/Config.h>
#include <infra/Array.h>

#include <cstring>

namespace mud
{
	template <class T>
	void copy(array<T> dest, array<T> src) { memcpy(dest.m_pointer, src.m_pointer, sizeof(T) * src.m_count); }

	template <class T>
	void copy(T* dest, array<T> src) { memcpy(dest, src.m_pointer, sizeof(T) * src.m_count); }

	template <class T>
	void copy(void* dest, array<T> src) { memcpy(dest, src.m_pointer, sizeof(T) * src.m_count); }
}
