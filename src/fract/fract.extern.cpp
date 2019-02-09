#ifndef USE_STL
#ifdef MUD_MODULES
module mud.fract;
#else
#include <stl/vector.hpp>
#include <stl/unordered_map.hpp>
#include <fract/Api.h>
#endif

namespace stl
{
	using namespace mud;
	template class MUD_FRACT_EXPORT vector<FractTab>;
	template class MUD_FRACT_EXPORT vector<Pixircle>;
}
#endif
