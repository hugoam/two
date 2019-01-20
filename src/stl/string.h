#pragma once
#include <infra/Config.h>

#ifndef MUD_NO_STL
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
		result.append(lhs);
		result.append(rhs);
		return result;
	}
}
#endif
