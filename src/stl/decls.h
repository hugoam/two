#pragma once
#include <infra/Config.h>

#ifdef USE_STL
namespace stl
{
	template <class T> struct span;
	template <class T, size_t Size> struct array;
}
#include <string>
#include <functional>
#include <vector>
namespace stl
{
	using std::string;
	using std::function;
	using std::vector;
}
#else
#include <stl/allocator.h>
namespace stl
{
	template <class Alloc> class basic_string;
	using string = basic_string<TINYSTL_ALLOCATOR>;

	template <class T> struct span;
	template <class T, size_t Size> struct array;
	template <class T, class Alloc = TINYSTL_ALLOCATOR> class vector;

	template <class T> class function;
}
#endif

namespace mud
{
	using stl::string;
	using stl::function;
	using stl::vector;
	using stl::array;
	using stl::span;
}
