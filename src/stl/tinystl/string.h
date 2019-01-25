#pragma once

#include <stl/tinystl/allocator.h>
#include <stl/tinystl/basic_string.h>

namespace tinystl {

	extern template class basic_string<TINYSTL_ALLOCATOR>;
	using string = basic_string<TINYSTL_ALLOCATOR>;
}
