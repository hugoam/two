#pragma once
#include <infra/Config.h>

#ifndef MUD_NO_STL
#ifndef MUD_CPP_20
#include <unordered_set>
namespace mud
{
	export_ using std::unordered_set;
}
#endif
#else
#include <TINYSTL/unordered_set.h>
namespace mud
{
	export_ using unordered_set = tinystl::unordered_set<K, T>;
}
#endif
