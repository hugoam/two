#pragma once

#if defined(_WIN64)
	typedef long long unsigned int size_t;
	typedef long long int ptrdiff_t;
#elif defined(_WIN32)
	typedef unsigned int size_t;
	typedef int ptrdiff_t;
#elif defined (__linux__) && defined(__SIZE_TYPE__) && defined(__PTRDIFF_TYPE__)
	typedef __SIZE_TYPE__ size_t;
	typedef __PTRDIFF_TYPE__ ptrdiff_t;
#else
#	include <stddef.h>
#endif
