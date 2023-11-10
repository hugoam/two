#ifndef USE_STL
#ifdef TWO_MODULES
module two.fract;
#else
#include <stl/vector.hpp>
#include <stl/unordered_map.hpp>
#include <fract/Api.h>
#endif

namespace stl
{
	using namespace two;
	template class TWO_FRACT_EXPORT vector<FractTab>;
	template class TWO_FRACT_EXPORT vector<Pixircle>;
}
#endif
