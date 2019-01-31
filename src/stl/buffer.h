#pragma once

#include <stl/allocator.h>

namespace stl {

	template <class T, class Alloc = TINYSTL_ALLOCATOR>
	struct buffer {
		T* first = 0;
		T* last = 0;
		T* capacity = 0;
	};
}
