#pragma once
#include <infra/Config.h>

#ifndef MUD_NO_STL
#ifndef MUD_CPP_20
#include <set>
namespace mud
{
	export_ using std::set;
}
#endif
#else
#include <TINYSTL/unordered_set.h>
namespace mud
{
	template <class T>
	export_ using set = tinystl::unordered_set<T>;
}
#endif
