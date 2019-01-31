#pragma once
#include <infra/Config.h>

#ifdef USE_STL
#ifndef MUD_CPP_20
#include <map>
namespace mud
{
	export_ using std::map;
}
#endif
#else
#include <stl/unordered_map.h>
namespace mud
{
	template <class K, class T>
	export_ using map = stl::unordered_map<K, T>;
}
#endif
