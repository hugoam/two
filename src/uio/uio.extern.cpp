#ifndef USE_STL
#ifdef MUD_MODULES
module mud.uio;
#else
#include <stl/vector.hpp>
#include <stl/unordered_map.hpp>
#include <uio/Api.h>
#endif

namespace stl
{
	using namespace mud;
	template class MUD_UIO_EXPORT vector<EditSpec>;
	template class MUD_UIO_EXPORT unordered_map<Module*, bool>;
	template class MUD_UIO_EXPORT unordered_map<const Type*, Colour>;
}
#endif
