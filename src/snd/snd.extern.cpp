#ifndef USE_STL
#ifdef TWO_MODULES
module two.snd;
#else
#include <stl/vector.hpp>
#include <stl/unordered_map.hpp>
#include <snd/Api.h>
#endif

namespace stl
{
	using namespace two;
	template class TWO_SND_EXPORT vector<unique<Sound>>;
	template class TWO_SND_EXPORT unordered_map<string, unique<SharedBuffer>>;
}
#endif
