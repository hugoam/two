// file      : libstd-modules/std-threading.mxx -*- C++ -*-
// copyright : Copyright (c) 2014-2018 Code Synthesis Ltd
// license   : MIT; see accompanying LICENSE file

export module std.threading; // Dummy.

#if 0
// Pre-includes.
//
#include <libstd-modules/std-detect.hxx>

#if   defined(_MSC_VER)
#error TODO
#elif defined(__GLIBCXX__)

// <mutex>
#  define _GLIBCXX_TUPLE
#  define _GLIBCXX_CHRONO
#  define __EXCEPTION__            // <exception>
#  define _GLIBCXX_TYPE_TRAITS
#  define _GLIBCXX_SYSTEM_ERROR
#  define _GLIBCXX_STD_FUNCTION_H  // <bits/std_function.h>
#  define _FUNCTEXCEPT_H
#  define _MOVE_H

// <shared_mutex>
#  include <cerrno> // Missing include.

// <condition_variable>
#  define _CONCURRENCE_H    // <ext/concurrence.h>
#  define _ALLOC_TRAITS_H   // <bits/alloc_traits.h>
#  define _ALLOCATOR_H      // <bits/allocator.h>
#  define _UNIQUE_PTR_H     // <bits/unique_ptr.h>
#  define _SHARED_PTR_H     // <bits/shared_ptr.h>
#  define _CXXABI_FORCED_H  // <bits/cxxabi_forced.h>
#  include <bits/exception_defines.h> // Missing include.

// <thread>
#  define _GLIBCXX_MEMORY
#  define _FUNCTIONAL_HASH_H  // <bits/functional_hash.h>
#  define _GLIBCXX_INVOKE_H   // <bits/invoke.h>

#  include <bits/gthr.h>
#elif defined(_LIBCPP_VERSION)
#endif

export module std.threading;

#ifdef __GLIBCXX__
import std.core;
#endif

export
{
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <thread>
}
#endif
