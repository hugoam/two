#ifndef USE_STL
#ifdef MUD_MODULES
module mud.infra;
#else
#include <stl/vector.hpp>
#include <infra/Api.h>
#endif

namespace stl
{
	using namespace mud;
	template class MUD_INFRA_EXPORT vector<string>;
	template class MUD_INFRA_EXPORT vector<uchar>;
}
#endif
