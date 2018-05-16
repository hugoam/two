//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Vec.h>
#include <ui/Generated/Forward.h>
#include <ui/Style/Style.h>
#include <ui/Widget.h>

#include <stdint.h>

namespace mud
{
namespace ui
{
	struct DropdownStyles
	{
		DropdownStyles();
		Style popdown; Style dropdown; Style toggle; Style head; Style list; Style choice; Style dropdown_input; Style dropdown_input_compact; Style typedown_input;
	};

	MUD_UI_EXPORT DropdownStyles& dropdown_styles();

	struct MenuStyles
	{
		MenuStyles();
		Style menubar; Style menu; Style list; Style sublist;
	};

	MUD_UI_EXPORT MenuStyles& menu_styles();

	struct ToolbarStyles
	{
		ToolbarStyles();
		Style toolbutton; Style tooldock; Style toolbar; Style toolbar_wrap; Style mover;
	};

	MUD_UI_EXPORT ToolbarStyles& toolbar_styles();

	enum PopupFlags : unsigned int
	{
		PopupNone = 0,
		PopupModal = (1 << 0),
		PopupClamp = (1 << 1)
	};

	MUD_UI_EXPORT _func_ Widget& spacer(Widget& parent);

	MUD_UI_EXPORT _func_ Widget& icon(Widget& parent, cstring icon);
	MUD_UI_EXPORT _func_ Widget& label(Widget& parent, cstring label);
	MUD_UI_EXPORT _func_ Widget& text(Widget& parent, cstring label);

	MUD_UI_EXPORT Widget& button(Widget& parent, Style& style, cstring content = nullptr);
	MUD_UI_EXPORT Widget& multi_button(Widget& parent, Style& style, array<cstring> elements, Style* element_style = nullptr);
	MUD_UI_EXPORT Widget& toggle(Widget& parent, Style& style, bool& on, cstring content = nullptr);
	MUD_UI_EXPORT Widget& multi_toggle(Widget& parent, Style& style, bool& on, array<cstring> elements, Style* element_style = nullptr);

	MUD_UI_EXPORT _func_ Widget& button(Widget& parent, cstring content = nullptr);
	MUD_UI_EXPORT _func_ Widget& multi_button(Widget& parent, array<cstring> elements, Style* element_style = nullptr);
	MUD_UI_EXPORT _func_ Widget& toggle(Widget& parent, bool& on, cstring content = nullptr);
	MUD_UI_EXPORT _func_ Widget& multi_toggle(Widget& parent, bool& on, array<cstring> elements, Style* element_style = nullptr);

	MUD_UI_EXPORT _func_ bool modal_button(Widget& screen, Widget& parent, cstring content, uint32_t mode);
	MUD_UI_EXPORT _func_ bool modal_multi_button(Widget& screen, Widget& parent, array<cstring> elements, uint32_t mode);

	MUD_UI_EXPORT _func_ Widget& checkbox(Widget& parent, bool& on);
	MUD_UI_EXPORT _func_ Widget& fill_bar(Widget& parent, float percentage, Dim dim = DIM_X);
	MUD_UI_EXPORT _func_ Widget& figure(Widget& parent, const Image256& source);

	MUD_UI_EXPORT _func_ Widget& radio_choice(Widget& parent, cstring value, bool active);
	MUD_UI_EXPORT _func_ bool radio_switch(Widget& parent, array<cstring> labels, size_t& value, Dim dim = DIM_X);
	//MUD_UI_EXPORT bool radio_switch(Widget& parent, array<cstring> labels, string& value, Dim dim = DIM_X);

	//inline bool radio_switch_string(Widget& parent, array<cstring> labels, string& value) { return radio_switch(parent, labels, value); }

	MUD_UI_EXPORT _func_ bool popdown(Widget& parent, array<cstring> choices, size_t& value, vec2 position, PopupFlags flags);
	MUD_UI_EXPORT _func_ Widget& dropdown(Widget& parent, Style& style, cstring value, PopupFlags flags, Style* list_style = nullptr);
	MUD_UI_EXPORT _func_ bool dropdown_input(Widget& parent, array<cstring> choices, size_t& value, bool compact = false);
	MUD_UI_EXPORT _func_ bool typedown_input(Widget& parent, array<cstring> choices, size_t& value);

	MUD_UI_EXPORT _func_ Widget& menu_choice(Widget& parent, array<cstring> elements);
	MUD_UI_EXPORT _func_ Widget& menu_choice(Widget& parent, cstring content);
	MUD_UI_EXPORT _func_ Widget& menu(Widget& parent, cstring label, bool submenu = false);
	MUD_UI_EXPORT _func_ Widget& menubar(Widget& parent);

	MUD_UI_EXPORT _func_ Widget& toolbutton(Widget& parent, cstring icon);
	MUD_UI_EXPORT _func_ Widget& tooldock(Widget& parent);
	MUD_UI_EXPORT _func_ Widget& toolbar(Widget& parent, bool wrap = false);
}
}
