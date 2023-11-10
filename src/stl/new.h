#pragma once
#include <infra/Config.h>

#include <stl/stddef.h>

namespace stl {

	export_ struct placeholder {};
}

export_ inline void* operator new(size_t, stl::placeholder, void* ptr) {
	return ptr;
}

export_ inline void operator delete(void*, stl::placeholder, void*) throw() {}
