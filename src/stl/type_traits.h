#pragma once

#include <stl/traits.h>
#include <type_traits>

namespace stl
{
	template <class T>
	constexpr bool is_function = std::is_function_v<T>;

	template <class T>
	constexpr bool is_trivially_destructible = std::is_trivially_destructible_v<T>;
}

namespace mud
{
	using stl::is_function;
	using stl::is_trivially_destructible;
}
