// file      : libstd-modules/std-regex.mxx -*- C++ -*-
// copyright : Copyright (c) 2014-2018 Code Synthesis Ltd
// license   : MIT; see accompanying LICENSE file

// Pre-includes.
//
#include "std_detect.h"

#if   defined(_MSC_VER)
#  include <algorithm>
#  include <iterator>
#  include <locale>
#  include <stdexcept>
#  include <string>
#  include <utility>
#  include <vector>

#  include <wchar.h>
#  include <limits.h>
#  include <stdlib.h>
#  include <string.h>
#elif defined(__GLIBCXX__)
#  define _GLIBCXX_ALGORITHM
#  define _GLIBCXX_BITSET
#  define _GLIBCXX_IOSFWD
#  define _GLIBCXX_ITERATOR
#  define _GLIBCXX_LOCALE
#  define _GLIBCXX_MEMORY
#  define _GLIBCXX_SSTREAM
#  define _GLIBCXX_STACK
#  define _GLIBCXX_STDEXCEPT
#  define _GLIBCXX_STRING
#  define _GLIBCXX_UTILITY
#  define _GLIBCXX_VECTOR
#  define _GLIBCXX_MAP
#  define _GLIBCXX_CSTRING
#  define _GLIBCXX_FUNCTIONAL

#  define _GLIBCXX_STD_FUNCTION_H  // <bits/std_function.h>
#  define _ALIGNED_BUFFER_H        // <ext/aligned_buffer.h>

#  include <string.h>

#  include <debug/debug.h>   // Missing include.

#elif defined(_LIBCPP_VERSION)
#endif

export module std.regex;

#ifdef __GLIBCXX__
import std.core;
import std.io;
#endif

export
{
#include <regex>
}
