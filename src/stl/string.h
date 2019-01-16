#pragma once
#include <infra/Config.h>

#define MUD_STRING_TINYSTL
#ifndef MUD_STRING_TINYSTL
#ifndef MUD_CPP_20
#include <string>
namespace mud
{
	export_ using std::string;
}
namespace tinystl
{
	static inline size_t hash(const std::string& value) {
		return std::hash<std::string>()(value);
	}
}
#endif
#else
#include <TINYSTL/string.h>
namespace mud
{
	export_ using tinystl::string;

	inline string operator+(const string& lhs, const string& rhs)
	{
		string result;
		result.reserve(lhs.size() + rhs.size());
		result.append(lhs.c_str(), lhs.c_str() + lhs.size());
		result.append(rhs.c_str(), rhs.c_str() + rhs.size());
		return result;
	}
}
#endif
