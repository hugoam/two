#  include <time.h>
#  include <errno.h>
#  include <wchar.h>          // struct tm forward declaration.
#  include <stdio.h>
#  include <string.h>
#  include <strings.h>
#  include <sys/types.h>
#  include <ext/atomicity.h>  // Names with internal linkage.
#  include <x86intrin.h>

export module json11;

export
{
#include <json11.hpp>
}
