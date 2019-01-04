//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_CPP_20
#include <type_traits>
#include <cstring>
#endif

#if defined __GNUC__
#   pragma GCC system_header
#endif

namespace mud
{
	using std::enable_if; using std::is_copy_assignable; using std::is_copy_constructible; using std::is_pointer;
	using std::is_function; using std::integral_constant; using std::remove_pointer; using std::is_trivially_destructible;

	export_ template <typename T>
	struct is_function_pointer : integral_constant<bool, is_pointer<T>::value
													  && is_function<typename remove_pointer<T>::type>::value> {};

	export_ template <typename T>
	struct is_object_pointer : integral_constant<bool, is_pointer<T>::value
													&& !is_function_pointer<T>::value> {};

	export_ template <typename T, typename = void>
	struct is_comparable_base : std::false_type {};

	export_ template <typename T>
	struct is_comparable_base<T, decltype(std::declval<T&>() == std::declval<T&>(), (void) 0)> : std::true_type {};

	export_ template <typename T>
	struct is_comparable : is_comparable_base<T> {};

	export_ template <typename T>
	struct is_copyable : integral_constant<bool, is_copy_constructible<T>::value
											  && is_copy_assignable<T>::value> {};
}
