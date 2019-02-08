#ifndef USE_STL
#include <stl/string.h>
#include <stl/string.hpp>

namespace stl {

	template class basic_string<TINYSTL_ALLOCATOR>;

	string operator+(const string& lhs, const string& rhs)
	{
		string result;
		result.reserve(lhs.size() + rhs.size());
		result.append(lhs);
		result.append(rhs);
		return result;
	}
}
#endif
