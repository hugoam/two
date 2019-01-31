#pragma once
#include <infra/Config.h>

#ifdef USE_STL
#include <string>
#include <functional>
#else
#include <stl/allocator.h>
namespace stl
{
	template <class Alloc>
	class basic_string;

	using string = basic_string<TINYSTL_ALLOCATOR>;

	template <class T>
	class function;
}
namespace mud
{
	using stl::string;
	using stl::function;
}
#endif
