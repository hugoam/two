#pragma once
#include <infra/Config.h>

#ifndef MUD_NO_STL
#include <stl/string.h>
#else
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
