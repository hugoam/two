#ifdef _MSC_VER
#include <infra/Cpp20.h>

#if 1 // VS module bug kludge
_STD_BEGIN

_INLINE_VAR constexpr size_t hardware_constructive_interference_size = 64;
_INLINE_VAR constexpr size_t hardware_destructive_interference_size = 64;

_STD_END
#endif

#else
#include <assert.h>
#include <stdint.h>
#include <limits.h>
#include <float.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <wchar.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

// gcc libstdc++ specific
#include <strings.h>
#include <sys/types.h>
#include <ext/atomicity.h>
#include <x86intrin.h>
#endif
