#pragma once
#include <infra/Config.h>

#ifdef USE_STL
#include <set>
namespace stl
{
	using std::set;
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
}
