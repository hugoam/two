#pragma once

#include <stl/stddef.h>

namespace stl {

	struct placeholder {};
}

inline void* operator new(size_t, stl::placeholder, void* ptr) {
	return ptr;
}

inline void operator delete(void*, stl::placeholder, void*) throw() {}
