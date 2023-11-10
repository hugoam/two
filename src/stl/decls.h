#pragma once
#include <infra/Config.h>

#ifdef USE_STL
#ifndef TWO_STD_MODULES
#include <cstddef>
#endif
namespace stl
{
	export_ template <class T> struct span;
	export_ template <class T, size_t Size> struct array;
}
#ifndef TWO_MODULES
#include <string>
#include <functional>
#include <vector>
#endif
namespace stl
{
	export_ using std::string;
	export_ using std::function;
	export_ using std::vector;
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

namespace two
{
	export_ using stl::string;
	export_ using stl::function;
	export_ using stl::vector;
	export_ using stl::array;
	export_ using stl::span;
}
