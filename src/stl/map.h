#pragma once
#include <infra/Config.h>

#define MUD_MAP_TINYSTL
#ifndef MUD_MAP_TINYSTL
#ifndef MUD_CPP_20
#include <map>
namespace mud
{
	export_ using std::map;
}
#endif
#else
#include <TINYSTL/unordered_map.h>
namespace mud
{
	template <class K, class T>
	export_ using map = tinystl::unordered_map<K, T>;
}
#endif
