#ifndef USE_STL
#ifdef TWO_MODULES
module two.ui;
#else
#include <stl/vector.hpp>
#include <stl/unordered_set.hpp>
#include <stl/unordered_map.hpp>
#include <ui/Api.h>
#include <ui/Edit/Lang.h>
#endif

namespace stl
{
	using namespace two;
	template class TWO_UI_EXPORT vector<TextGlyph>;
	template class TWO_UI_EXPORT vector<TextRow>;
	template class TWO_UI_EXPORT vector<Text::ColorSection>;
	template class TWO_UI_EXPORT vector<TextMarker>;
	template class TWO_UI_EXPORT vector<TextEdit::Action>;
	template class TWO_UI_EXPORT vector<Space>;
	template class TWO_UI_EXPORT vector<FrameSolver*>;
	template class TWO_UI_EXPORT vector<Style*>;
	template class TWO_UI_EXPORT vector<Layer*>;
	template class TWO_UI_EXPORT vector<Docker*>;
	template class TWO_UI_EXPORT vector<Dock*>;
	template class TWO_UI_EXPORT vector<Node*>;
	template class TWO_UI_EXPORT vector<InkStyle>;
	template class TWO_UI_EXPORT vector<Subskin>;
	template class TWO_UI_EXPORT vector<FrameSolver>;
	template class TWO_UI_EXPORT vector<RowSolver>;
	template class TWO_UI_EXPORT vector<unique<Widget>>;
	template class TWO_UI_EXPORT vector<unique<FrameSolver>>;
	template class TWO_UI_EXPORT vector<unique<Image>>;
	template class TWO_UI_EXPORT unordered_map<KeyCombo, KeyHandler>;
	template class TWO_UI_EXPORT unordered_map<string, Dock>;
	template class TWO_UI_EXPORT unordered_map<string, Style*>;

	template class TWO_UI_EXPORT unordered_set<string>;
	template class TWO_UI_EXPORT vector<LanguageDefinition::StringToken>;
	template class TWO_UI_EXPORT vector<LanguageDefinition::RegexToken>;
	template class TWO_UI_EXPORT unordered_map<string, Identifier>;
}
#endif
