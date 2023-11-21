#ifndef USE_STL
module two.ui.vg;

namespace stl
{
	using namespace two;
	template class TWO_UI_VG_EXPORT vector<vg::GlyphPosition>;
	template class TWO_UI_VG_EXPORT unordered_map<string, vg::FontHandle>;
}
#endif
