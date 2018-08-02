//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <obj/Ref.h>
#include <math/Vec.h>
#endif
#include <ui/Forward.h>
#include <ui/Style/Style.h>
#include <ui/Widget.h>

#ifndef MUD_CPP_20
#include <cstdint>
#endif

namespace mud
{
namespace ui
{
	export_ struct DropdownStyles
	{
		DropdownStyles();
		Style popdown; Style dropdown; Style toggle; Style head; Style list; Style choice; Style dropdown_input; Style dropdown_input_compact; Style typedown_input;
	};

	export_ MUD_UI_EXPORT DropdownStyles& dropdown_styles();

	export_ struct MenuStyles
	{
		MenuStyles();
		Style menubar; Style menu; Style list; Style sublist;
	};

	export_ MUD_UI_EXPORT MenuStyles& menu_styles();

	export_ struct ToolbarStyles
	{
		ToolbarStyles();
		Style toolbutton; Style tooldock; Style toolbar; Style toolbar_wrap; Style mover;
	};

	export_ MUD_UI_EXPORT ToolbarStyles& toolbar_styles();

	export_ enum class PopupFlags : unsigned int
	{
		None = 0,
		Modal = (1 << 0),
		Clamp = (1 << 1),
		AutoClose = (1 << 2),
		AutoModal = Modal | AutoClose,
	};

	export_ inline bool popup_flag(PopupFlags flags, PopupFlags check) { return (uint(flags) & uint(check)) != 0; }

	export_ MUD_UI_EXPORT func_ Widget& spacer(Widget& parent);

	export_ MUD_UI_EXPORT func_ Widget& icon(Widget& parent, cstring icon);
	export_ MUD_UI_EXPORT func_ Widget& label(Widget& parent, cstring label);
	export_ MUD_UI_EXPORT func_ Widget& title(Widget& parent, cstring label);
	export_ MUD_UI_EXPORT func_ Widget& message(Widget& parent, cstring label);
	export_ MUD_UI_EXPORT func_ Widget& text(Widget& parent, cstring label);

	export_ MUD_UI_EXPORT void button_logic(Widget& self);
	export_ MUD_UI_EXPORT void toggle_logic(Widget& self, bool& on);

	export_ MUD_UI_EXPORT Widget& button(Widget& parent, Style& style, cstring content = nullptr);
	export_ MUD_UI_EXPORT Widget& multi_button(Widget& parent, Style& style, array<cstring> elements, Style* element_style = nullptr);
	export_ MUD_UI_EXPORT Widget& toggle(Widget& parent, Style& style, bool& on, cstring content = nullptr);
	export_ MUD_UI_EXPORT Widget& multi_toggle(Widget& parent, Style& style, bool& on, array<cstring> elements, Style* element_style = nullptr);

	export_ MUD_UI_EXPORT func_ Widget& button(Widget& parent, cstring content = nullptr);
	export_ MUD_UI_EXPORT func_ Widget& multi_button(Widget& parent, array<cstring> elements, Style* element_style = nullptr);
	export_ MUD_UI_EXPORT func_ Widget& toggle(Widget& parent, bool& on, cstring content = nullptr);
	export_ MUD_UI_EXPORT func_ Widget& multi_toggle(Widget& parent, bool& on, array<cstring> elements, Style* element_style = nullptr);

	export_ MUD_UI_EXPORT func_ bool modal_button(Widget& screen, Widget& parent, cstring content, uint32_t mode);
	export_ MUD_UI_EXPORT func_ bool modal_multi_button(Widget& screen, Widget& parent, array<cstring> elements, uint32_t mode);

	export_ MUD_UI_EXPORT func_ Widget& checkbox(Widget& parent, bool& on);
	export_ MUD_UI_EXPORT func_ Widget& fill_bar(Widget& parent, float percentage, Dim dim = DIM_X);

	export_ MUD_UI_EXPORT func_ Widget& image256(Widget& parent, cstring name, const Image256& source);
	export_ MUD_UI_EXPORT func_ Widget& image256(Widget& parent, cstring name, const Image256& source, const vec2& size);

	export_ MUD_UI_EXPORT func_ Widget& radio_choice(Widget& parent, cstring value, bool active);
	export_ MUD_UI_EXPORT func_ bool radio_switch(Widget& parent, array<cstring> labels, size_t& value, Dim dim = DIM_X);
	//MUD_UI_EXPORT bool radio_switch(Widget& parent, array<cstring> labels, string& value, Dim dim = DIM_X);

	//inline bool radio_switch_string(Widget& parent, array<cstring> labels, string& value) { return radio_switch(parent, labels, value); }

	export_ MUD_UI_EXPORT func_ bool popdown(Widget& parent, array<cstring> choices, size_t& value, vec2 position, PopupFlags flags);
	export_ MUD_UI_EXPORT func_ Widget& dropdown(Widget& parent, Style& style, cstring value, PopupFlags flags, Style* list_style = nullptr);
	export_ MUD_UI_EXPORT func_ bool dropdown_input(Widget& parent, array<cstring> choices, size_t& value, bool compact = false);
	export_ MUD_UI_EXPORT func_ bool typedown_input(Widget& parent, array<cstring> choices, size_t& value);

	export_ MUD_UI_EXPORT func_ Widget& menu_choice(Widget& parent, array<cstring> elements);
	export_ MUD_UI_EXPORT func_ Widget& menu_choice(Widget& parent, cstring content);
	export_ MUD_UI_EXPORT func_ Widget& menu(Widget& parent, cstring label, bool submenu = false);
	export_ MUD_UI_EXPORT func_ Widget& menubar(Widget& parent);

	export_ MUD_UI_EXPORT func_ Widget& toolbutton(Widget& parent, cstring icon);
	export_ MUD_UI_EXPORT func_ Widget& tooldock(Widget& parent);
	export_ MUD_UI_EXPORT func_ Widget& toolbar(Widget& parent, bool wrap = false);
}
}
