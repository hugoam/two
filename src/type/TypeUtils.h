//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <infra/TypeTraits.h>
#endif

#ifndef MUD_CPP_20
#include <type_traits>
#include <cstring>
#endif

#if defined __GNUC__
#   pragma GCC system_header
#endif

namespace mud
{
	export_ template <class T>
	inline typename enable_if<is_comparable<T>::value, bool>::type
		any_compare(const T& first, const T& second) { return first == second; }

	export_ template <class T>
	inline typename enable_if<!is_comparable<T>::value, bool>::type
		any_compare(const T& first, const T& second) { return &first == &second; }

	export_ template <class T>
	inline typename enable_if<is_copy_assignable<T>::value, void>::type
		any_assign(T& val, const T& other) { val = other; }

	export_ template <class T>
	inline typename enable_if<!is_copy_assignable<T>::value, void>::type
		any_assign(T& val, const T& other) { UNUSED(val); UNUSED(other); }

	export_ template <class T>
	inline typename enable_if<is_copy_constructible<T>::value, T>::type
		any_copy(const T& val) { return T(val); }

	export_ template <class T>
	inline typename enable_if<!is_copy_constructible<T>::value, T>::type
		any_copy(const T& val) { UNUSED(val); return T(); }

	export_ template <class T>
	inline typename enable_if<is_trivially_destructible<T>::value, void>::type
		any_destruct(T& val) { UNUSED(val); }
	
	export_ template <class T>
	inline typename enable_if<!is_trivially_destructible<T>::value, void>::type
		any_destruct(T& val) { val.~T(); }
}
