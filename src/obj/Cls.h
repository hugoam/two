//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#define MUD_MAX_TYPES 1000U

#include <obj/Config.h>

namespace mud
{
	class Type;

	export_ template <class T>
	Type& type();

	export_ template <class T, class U>
	inline T& as(U& object) { return static_cast<T&>(object); }

	export_ template <class T, class U>
	inline const T& as(const U& object) { return static_cast<const T&>(object); }
}
