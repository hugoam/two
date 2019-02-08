//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/type_traits.h>

#if defined __GNUC__
#   pragma GCC system_header
#endif

namespace mud
{
	export_ template <class T>
	constexpr bool is_object_pointer = is_pointer<T>;// && !is_function_pointer<T>;

	export_ template <class T, typename = void>
	struct is_comparable_base { constexpr static bool value = false;};

	export_ template <class T>
	struct is_comparable_base<T, decltype(declval<T&>() == declval<T&>(), (void) 0)> { constexpr static bool value = true; };

	export_ template <class T>
	constexpr bool is_comparable = is_comparable_base<T>::value;

	export_ template <class T>
	constexpr bool is_copyable = is_copy_constructible<T> && is_copy_assignable<T>;
}
