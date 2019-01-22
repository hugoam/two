#pragma once
#include <infra/Config.h>

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
