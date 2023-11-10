#ifndef USE_STL
#ifdef TWO_MODULES
module two.infra;
#else
#include <stl/vector.hpp>
#include <infra/Api.h>
#endif

namespace stl
{
	using namespace two;
	template class TWO_INFRA_EXPORT vector<string>;
	template class TWO_INFRA_EXPORT vector<uchar>;
}
#endif
