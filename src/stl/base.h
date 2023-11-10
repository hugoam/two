//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <infra/Config.h>
#include <stdint.h>

export_ using schar = signed char;
export_ using uchar = unsigned char;
export_ using ushort = unsigned short;
export_ using uint = unsigned int;
export_ using ulong = unsigned long;
export_ using ullong = unsigned long long;
export_ using llong = long long;
export_ using ldouble = long double;

namespace stl
{
	export_ template <class T>
	inline bool bit(T flags, T bit) { return (uint(flags) & uint(bit)) != 0; }
}

namespace two
{
	export_ using stl::bit;
}