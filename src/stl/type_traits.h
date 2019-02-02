#pragma once

#include <stl/traits.h>
#ifdef _MSC_VER
namespace stl
{
	template<class T>
	constexpr bool is_trivially_destructible = __is_trivially_destructible(T);
}
#else
#include <type_traits>
namespace stl
{
	template <class T>
	constexpr bool is_trivially_destructible = std::is_trivially_destructible_v<T>;
}
#endif

namespace mud
{
	//using stl::is_function;
	using stl::is_trivially_destructible;
}
