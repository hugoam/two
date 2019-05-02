#ifndef USE_STL
#ifdef TWO_MODULES
module two.uio;
#else
#include <stl/vector.hpp>
#include <stl/unordered_map.hpp>
#include <uio/Api.h>
#endif

namespace stl
{
	using namespace two;
	template class TWO_UIO_EXPORT vector<EditSpec>;
	template class TWO_UIO_EXPORT unordered_map<Module*, bool>;
	template class TWO_UIO_EXPORT unordered_map<const Type*, Colour>;
}
#endif
