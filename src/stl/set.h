#pragma once
#include <infra/Config.h>

#ifdef USE_STL
#ifndef TWO_STD_MODULES
#include <set>
#endif
namespace stl
{
	export_ using std::set;
	export_ using std::unordered_set;
}
#else
#include <stl/unordered_set.h>
namespace stl
{
	template <class T>
	export_ using set = stl::unordered_set<T>;
}
#endif

namespace two
{
	export_ using stl::set;
	export_ using stl::unordered_set;
}
