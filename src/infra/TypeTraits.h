//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_CPP_20
#include <stl/type_traits.h>
#endif

#if defined __GNUC__
#   pragma GCC system_header
#endif

namespace mud
{
	export_ template <class T>
	constexpr bool is_object_pointer = is_pointer<T>;// && !is_function_pointer<T>;

	export_ template <class T, typename = void>
	struct is_comparable_base : false_type {};

	export_ template <class T>
	struct is_comparable_base<T, decltype(declval<T&>() == declval<T&>(), (void) 0)> : true_type {};

	export_ template <class T>
	constexpr bool is_comparable = is_comparable_base<T>::value;

	export_ template <class T>
	constexpr bool is_copyable = is_copy_constructible<T> && is_copy_assignable<T>;
}
