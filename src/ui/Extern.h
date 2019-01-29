#pragma once

#include <stl/vector.h>
#include <stl/string.h>
#include <stl/unordered_map.h>
#include <ui/Api.h>
//#include <ui/Edit/Lang.h>

namespace tinystl
{
	using namespace mud;
	export_ extern template class vector<TextGlyph>;
	export_ extern template class vector<TextRow>;
	export_ extern template class vector<Text::ColorSection>;
	export_ extern template class vector<TextMarker>;
	export_ extern template class vector<TextEdit::Action>;
	export_ extern template class vector<Space>;
	export_ extern template class vector<FrameSolver*>;
	export_ extern template class vector<Image*>;
	export_ extern template class vector<Style*>;
	export_ extern template class vector<Layer*>;
	export_ extern template class vector<Docker*>;
	export_ extern template class vector<Dock*>;
	export_ extern template class vector<Node*>;
	export_ extern template class vector<EventBatch>;
	export_ extern template class vector<KeyEvent>;
	export_ extern template class vector<MouseEvent>;
	export_ extern template class vector<InkStyle>;
	export_ extern template class vector<FrameSolver>;
	export_ extern template class vector<RowSolver>;
	export_ extern template class vector<unique<Widget>>;
	export_ extern template class vector<unique<FrameSolver>>;
	export_ extern template class vector<unique<Image>>;
	export_ extern template class unordered_map<int, InputEvent*>;
	export_ extern template class unordered_map<KeyCombo, KeyHandler>;
	export_ extern template class unordered_map<string, Dock>;
	export_ extern template class unordered_map<string, Style*>;

	//export_ extern template class vector<LanguageDefinition::StringToken>;
	//export_ extern template class vector<LanguageDefinition::RegexToken>;
	//export_ extern template class unordered_map<string, Identifier>;
}
