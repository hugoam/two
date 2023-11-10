#if defined _MSC_VER
#include <io.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#elif defined __GLIBCXX__
#include <time.h>
#include <errno.h>
#include <wchar.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <bits/c++locale.h>
#include <ext/atomicity.h>
#include <x86intrin.h>
#endif
