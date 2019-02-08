#ifndef USE_STL
#ifdef MUD_MODULES
module mud.math;
#else
#include <stl/vector.hpp>
#include <stl/string.hpp>
#include <stl/unordered_set.hpp>
#include <stl/unordered_map.hpp>
#include <ui/Api.h>
#include <ui/Edit/Lang.h>
#endif

namespace stl
{
	using namespace mud;
	template class MUD_UI_EXPORT vector<TextGlyph>;
	template class MUD_UI_EXPORT vector<TextRow>;
	template class MUD_UI_EXPORT vector<Text::ColorSection>;
	template class MUD_UI_EXPORT vector<TextMarker>;
	template class MUD_UI_EXPORT vector<TextEdit::Action>;
	template class MUD_UI_EXPORT vector<Space>;
	template class MUD_UI_EXPORT vector<FrameSolver*>;
	template class MUD_UI_EXPORT vector<Image*>;
	template class MUD_UI_EXPORT vector<Style*>;
	template class MUD_UI_EXPORT vector<Layer*>;
	template class MUD_UI_EXPORT vector<Docker*>;
	template class MUD_UI_EXPORT vector<Dock*>;
	template class MUD_UI_EXPORT vector<Node*>;
	template class MUD_UI_EXPORT vector<EventBatch>;
	template class MUD_UI_EXPORT vector<KeyEvent>;
	template class MUD_UI_EXPORT vector<MouseEvent>;
	template class MUD_UI_EXPORT vector<InkStyle>;
	template class MUD_UI_EXPORT vector<FrameSolver>;
	template class MUD_UI_EXPORT vector<RowSolver>;
	template class MUD_UI_EXPORT vector<unique<Widget>>;
	template class MUD_UI_EXPORT vector<unique<FrameSolver>>;
	template class MUD_UI_EXPORT vector<unique<Image>>;
	template class MUD_UI_EXPORT unordered_map<int, InputEvent*>;
	template class MUD_UI_EXPORT unordered_map<KeyCombo, KeyHandler>;
	template class MUD_UI_EXPORT unordered_map<string, Dock>;
	template class MUD_UI_EXPORT unordered_map<string, Style*>;

	template class MUD_UI_EXPORT unordered_set<string>;
	template class MUD_UI_EXPORT vector<LanguageDefinition::StringToken>;
	template class MUD_UI_EXPORT vector<LanguageDefinition::RegexToken>;
	template class MUD_UI_EXPORT unordered_map<string, Identifier>;
}
#endif
