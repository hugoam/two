#ifndef USE_STL
#ifdef TWO_MODULES
module two.wfc;
#else
#include <stl/vector.hpp>
#include <stl/unordered_map.hpp>
#include <wfc/Api.h>
#endif

namespace stl
{
	using namespace two;
	template class TWO_WFC_EXPORT vector<Tile>;
	template class TWO_WFC_EXPORT unordered_map<char, uint>;
}
#endif
