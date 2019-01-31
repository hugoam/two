//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <infra/TypeTraits.h>
#endif

#if defined __GNUC__
#   pragma GCC system_header
#endif

namespace mud
{
	export_ template <class T>
	inline enable_if<is_comparable<T>, bool>
		any_compare(const T& first, const T& second) { return first == second; }

	export_ template <class T>
	inline enable_if<!is_comparable<T>, bool>
		any_compare(const T& first, const T& second) { return &first == &second; }

	export_ template <class T>
	inline enable_if<is_copy_assignable<T>, void>
		any_assign(T& val, const T& other) { val = other; }

	export_ template <class T>
	inline enable_if<!is_copy_assignable<T>, void>
		any_assign(T& val, const T& other) { UNUSED(val); UNUSED(other); }

	export_ template <class T>
	inline enable_if<is_copy_constructible<T>, T>
		any_copy(const T& val) { return T(val); }

	export_ template <class T>
	inline enable_if<!is_copy_constructible<T>, T>
		any_copy(const T& val) { UNUSED(val); return T(); }

	export_ template <class T>
	inline enable_if<is_trivially_destructible<T>, void>
		any_destruct(T& val) { UNUSED(val); }
	
	export_ template <class T>
	inline enable_if<!is_trivially_destructible<T>, void>
		any_destruct(T& val) { val.~T(); }
}
