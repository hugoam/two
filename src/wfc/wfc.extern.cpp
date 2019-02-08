#ifndef USE_STL
#ifdef MUD_MODULES
module mud.wfc;
#else
#include <stl/vector.hpp>
#include <stl/unordered_map.hpp>
#include <wfc/Api.h>
#endif

namespace stl
{
	using namespace mud;
	template class MUD_GLTF_EXPORT vector<Tile>;
	template class MUD_GLTF_EXPORT unordered_map<char, uint>;
}
#endif
