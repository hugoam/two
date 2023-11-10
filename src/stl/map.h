#pragma once
#include <infra/Config.h>

#ifdef USE_STL
#ifndef TWO_STD_MODULES
#include <map>
#endif
namespace stl
{
	export_ using std::map;
	export_ using std::unordered_map;
}
#else
#include <stl/unordered_map.h>
namespace stl
{
	export_ template <class K, class T>
	using map = stl::unordered_map<K, T>;
}
#endif

namespace two
{
	export_ using stl::map;
	export_ using stl::unordered_map;
}
