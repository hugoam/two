#pragma once
#include <infra/Config.h>

#ifndef MUD_NO_STL
#ifndef MUD_CPP_20
#include <map>
namespace mud
{
	export_ using std::map;
}
#endif
#else
#include <stl/tinystl/unordered_map.h>
namespace mud
{
	template <class K, class T>
	export_ using map = tinystl::unordered_map<K, T>;
}
#endif
