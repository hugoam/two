//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <infra/Config.h>
#include <stl/span.h>

#include <cstring>

namespace mud
{
	template <class T>
	void copy(span<T> dest, span<T> src) { memcpy(dest.m_pointer, src.m_pointer, sizeof(T) * src.m_count); }

	template <class T>
	void copy(T* dest, span<T> src) { memcpy(dest, src.m_pointer, sizeof(T) * src.m_count); }

	template <class T>
	void copy(void* dest, span<T> src) { memcpy(dest, src.m_pointer, sizeof(T) * src.m_count); }
}
