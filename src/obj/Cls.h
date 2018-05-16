//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#define MUD_MAX_TYPES 1000U

namespace mud
{
	class Type;

	template <class T>
	Type& type();

	template <class T, class U>
	inline T& as(U& object) { return static_cast<T&>(object); }

	template <class T, class U>
	inline const T& as(const U& object) { return static_cast<const T&>(object); }
}
