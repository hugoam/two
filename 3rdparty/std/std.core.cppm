// file      : libstd-modules/std-core.mxx -*- C++ -*-
// copyright : Copyright (c) 2014-2018 Code Synthesis Ltd
// license   : MIT; see accompanying LICENSE file

// For some standard library implementations we need to pre-include certain
// headers to prevent their exporting.

#include "std_detect.h"

#if   defined(_MSC_VER)
/*
#  include <io.h>
#  include <time.h>
#  include <stdlib.h>
#  include <string.h>
#  include <locale.h> // struct tm;
*/
#elif defined(__GLIBCXX__)
#  include <time.h>
#  include <errno.h>
#  include <wchar.h>          // struct tm forward declaration.
#  include <stdio.h>
#  include <stddef.h>
#  include <string.h>
#  include <strings.h>
#  include <sys/types.h>
#  include <ext/atomicity.h>  // Names with internal linkage.
#  include <x86intrin.h>
#elif defined(_LIBCPP_VERSION)
#endif

export module std.core;

export
{
  // These are defined in <bits/c++config.h> which we have pre-included.
  //
#ifdef __GLIBCXX__
  namespace std
  {
    typedef __SIZE_TYPE__         size_t;
    typedef __PTRDIFF_TYPE__      ptrdiff_t;
    typedef decltype(nullptr)     nullptr_t;
  }
#endif

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include <utility>
#include <type_traits>

#include <exception>
#include <stdexcept>
#include <system_error>

#include <new>
#include <memory>

#include <limits>
#include <ctime>
#include <atomic>
#include <chrono>
#include <bitset>
}

export
{
#include <iterator>
#include <algorithm>
#include <functional>

#include <string>
#include <cstring> // @@ Not in the proposal.

#include <array>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <list>
#include <forward_list>
#include <stack>
}

#if defined(_MSC_VER) || defined(__clang__)
export
{
#include <cctype>
#include <cwctype>
#include <locale>
#include <clocale>

#include <iosfwd>
#include <iomanip>
#include <istream>
#include <ostream>
#include <sstream>
#include <fstream>

#ifndef __GLIBCXX__
#  include <iostream>
#else
// Contents of <iostream> without static __ioinit.
//
namespace std _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION
  extern istream cin;
  extern ostream cout;
  extern ostream cerr;
  extern ostream clog;

  static inline ios_base::Init __ioinit;
_GLIBCXX_END_NAMESPACE_VERSION
}
#endif
}
#endif

// std.threading
//
export
{
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <thread>
}
