#ifndef USE_STL
#ifdef TWO_MODULES
module two.wfc.gfx;
#else
#include <stl/vector.hpp>
#include <wfc-gfx/Api.h>
#endif

namespace stl
{
	using namespace two;
	template class TWO_WFC_GFX_EXPORT vector<TileModel>;
}
#endif
