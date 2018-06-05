// file      : libstd-modules/std-io.mxx -*- C++ -*-
// copyright : Copyright (c) 2014-2018 Code Synthesis Ltd
// license   : MIT; see accompanying LICENSE file

export module std.io;

#ifdef _MSC_VER

export import std.core;

#elif defined(__clang__)
// Empty: can't handle the below and doesn't suppor re-export.
#else

import std.core;

export
{
#include <cctype>
#include <iosfwd>
#include <istream>
#include <ostream>
#include <iostream>
#include <sstream>
#include <fstream>
}

#endif
