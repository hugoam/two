#pragma once

#include <stl/tinystl/stddef.h>

namespace tinystl {

	struct placeholder {};
}

inline void* operator new(size_t, tinystl::placeholder, void* ptr) {
	return ptr;
}

inline void operator delete(void*, tinystl::placeholder, void*) throw() {}
