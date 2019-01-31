#pragma once

#include <stl/stddef.h>

namespace stl {

	struct allocator {
		static void* static_allocate(size_t bytes) {
			return operator new(bytes);
		}

		static void static_deallocate(void* ptr, size_t /*bytes*/) {
			operator delete(ptr);
		}
	};
}

#ifndef TINYSTL_ALLOCATOR
#	define TINYSTL_ALLOCATOR ::stl::allocator
#endif
