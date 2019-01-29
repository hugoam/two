#pragma once

#include <stl/tinystl/allocator.h>

namespace tinystl {

	template<typename T, typename Alloc = TINYSTL_ALLOCATOR>
	struct buffer {
		T* first = 0;
		T* last = 0;
		T* capacity = 0;
	};
}
