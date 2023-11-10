#pragma once

#include <stl/traits.h>
#ifdef _MSC_VER
namespace stl
{
	export_ template<class T>
	constexpr bool is_trivially_destructible = __is_trivially_destructible(T);
}
#else
#include <type_traits>
namespace stl
{
	export_ template <class T>
	constexpr bool is_trivially_destructible = std::is_trivially_destructible_v<T>;
}
#endif

namespace two
{
	//using stl::is_function;
	export_ using stl::is_trivially_destructible;
}
