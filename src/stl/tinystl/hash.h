#pragma once

#include <stl/tinystl/stddef.h>

namespace tinystl {

	static inline size_t hash_string(const char* str, size_t len) {
		// Implementation of sdbm a public domain string hash from Ozan Yigit
		// see: http://www.eecs.harvard.edu/margo/papers/usenix91/paper.ps

		size_t hash = 0;
		typedef const char* pointer;
		for (pointer it = str, end = str + len; it != end; ++it)
			hash = *it + (hash << 6) + (hash << 16) - hash;

		return hash;
	}

	template<typename T>
	inline size_t hash(const T& value) {
		const size_t asint = (size_t)value;
		return hash_string((const char*)&asint, sizeof(asint));
	}
}
