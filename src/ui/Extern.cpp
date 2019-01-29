#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.math;
#else
#include <stl/tinystl/vector.impl.h>
#include <stl/tinystl/basic_string.impl.h>
#include <stl/tinystl/unordered_map.impl.h>
#include <ui/Extern.h>
#endif

using namespace mud;
namespace tinystl
{
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

	//template class MUD_UI_EXPORT vector<LanguageDefinition::StringToken>;
	//template class MUD_UI_EXPORT vector<LanguageDefinition::RegexToken>;
	//template class MUD_UI_EXPORT unordered_map<string, Identifier>;
}
