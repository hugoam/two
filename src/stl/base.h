//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <infra/Config.h>
#include <stdint.h>

namespace stl
{
	using schar = signed char;
	using uchar = unsigned char;
	using ushort = unsigned short;
	using uint = unsigned int;
	using ulong = unsigned long;
	using ullong = unsigned long long;
	using llong = long long;
	using ldouble = long double;
}

namespace mud
{
	using stl::schar; using stl::uchar; using stl::ushort; using stl::uint;
	using stl::ulong;using stl::ullong; using stl::llong; using stl::ldouble;
}
