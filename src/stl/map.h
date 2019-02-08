#pragma once
#include <infra/Config.h>

#ifdef USE_STL
#include <map>
namespace stl
{
	using std::map;
}
#else
#include <stl/unordered_map.h>
namespace stl
{
	template <class K, class T>
	using map = stl::unordered_map<K, T>;
}
#endif

namespace mud
{
	export_ using stl::map;
}
