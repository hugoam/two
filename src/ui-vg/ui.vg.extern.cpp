#ifndef USE_STL
#ifdef MUD_MODULES
module mud.ui.vg;
#else
#include <stl/vector.hpp>
#include <stl/unordered_map.hpp>
#include <ui-vg/Api.h>
#endif

namespace stl
{
	using namespace mud;
	template class MUD_UI_VG_EXPORT vector<vg::GlyphPosition>;
	template class MUD_UI_VG_EXPORT unordered_map<string, vg::FontHandle>;
}
#endif
