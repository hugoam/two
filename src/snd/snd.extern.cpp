#ifndef USE_STL
#ifdef MUD_MODULES
module mud.snd;
#else
#include <stl/vector.hpp>
#include <stl/unordered_map.hpp>
#include <snd/Api.h>
#endif

namespace stl
{
	using namespace mud;
	template class MUD_SND_EXPORT vector<unique<Sound>>;
	template class MUD_SND_EXPORT unordered_map<string, unique<SharedBuffer>>;
}
#endif
