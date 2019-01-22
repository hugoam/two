#pragma once

#include <infra/Config.h>

#ifndef MUD_INFRA_EXPORT
#define MUD_INFRA_EXPORT MUD_IMPORT
#endif

#ifdef MUD_NO_STL
#include <TINYSTL/allocator.h>
namespace tinystl
{
	template <typename Alloc>
	class basic_string;

	using string = basic_string<TINYSTL_ALLOCATOR>;
}
namespace mud
{
	using tinystl::string;
}
#endif
namespace mud
{
	using uchar = unsigned char;
	using ushort = unsigned short;
	using uint = unsigned int;
	using ulong = unsigned long;
	using ullong = unsigned long long;
	using llong = long long;
	using ddouble = long double;

    template <class T> struct array;
    
    struct Filepath;
    struct swallow;
    class NonCopy;
    class Movabl;
}

