#ifndef USE_STL
#ifdef TWO_MODULES
module two.uio;
#else
#include <stl/vector.hpp>
#include <pool/Api.h>
#endif

namespace stl
{
	using namespace two;
	template class TWO_POOL_EXPORT vector<unique<Pool>>;
}
#endif
