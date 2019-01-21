#pragma once
#include <infra/Config.h>

#ifndef MUD_NO_STL
#ifndef MUD_CPP_20
#include <unordered_map>
namespace mud
{
	export_ using std::unordered_map;
}
#endif
#else
#include <TINYSTL/unordered_map.h>
namespace mud
{
	export_ using tinystl::unordered_map;
}
#endif
