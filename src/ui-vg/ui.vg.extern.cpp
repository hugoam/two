#ifndef USE_STL
#ifdef TWO_MODULES
module two.ui.vg;
#else
#include <stl/vector.hpp>
#include <stl/unordered_map.hpp>
#include <ui-vg/Api.h>
#endif

namespace stl
{
	using namespace two;
	template class TWO_UI_VG_EXPORT vector<vg::GlyphPosition>;
	template class TWO_UI_VG_EXPORT unordered_map<string, vg::FontHandle>;
}
#endif
