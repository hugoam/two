#ifndef USE_STL
#ifdef MUD_MODULES
module mud.uio;
#else
#include <stl/vector.hpp>
#include <pool/Api.h>
#endif

namespace stl
{
	using namespace mud;
	template class MUD_POOL_EXPORT vector<unique<Pool>>;
}
#endif
