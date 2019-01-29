#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.uio;
#else
#include <stl/tinystl/vector.impl.h>
#include <stl/tinystl/unordered_map.impl.h>
#include <ui-vg/Extern.h>
#endif

namespace tinystl
{
	using namespace mud;
	template class MUD_UI_VG_EXPORT vector<vg::GlyphPosition>;
	template class MUD_UI_VG_EXPORT unordered_map<string, vg::FontHandle>;
}
