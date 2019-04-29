//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stdint.h>
#include <stl/decls.h>
#include <type/Ref.h>
#include <math/Vec.h>
#endif
#include <ui/Forward.h>
#include <ui/Style/Style.h>
#include <ui/Widget.h>

namespace mud
{
namespace ui
{
	export_ struct DropdownStyles
	{
		void reset();
		Style popdown; Style dropdown; Style toggle; Style head; Style list; Style choice; Style dropdown_input; Style dropdown_input_compact; Style typedown_input;
	};

	export_ MUD_UI_EXPORT DropdownStyles& dropdown_styles();

	export_ struct MenuStyles
	{
		void reset();
		Style menubar; Style menu; Style list; Style sublist; Style choice;
	};

	export_ MUD_UI_EXPORT MenuStyles& menu_styles();

	export_ struct ToolbarStyles
	{
		void reset();
		Style toolbutton; Style tooldock; Style toolbar; Style toolbar_wrap; Style mover;
	};

	export_ MUD_UI_EXPORT ToolbarStyles& toolbar_styles();

	export_ enum class refl_ PopupFlags : unsigned int
	{
		None = 0,
		Modal = (1 << 0),
		Clamp = (1 << 1),
		AutoClose = (1 << 2),
		AutoModal = Modal | AutoClose,
	};

	export_ MUD_UI_EXPORT func_ Widget& spacer(Widget& parent);
	export_ MUD_UI_EXPORT func_ Widget& separator(Widget& parent);

	export_ MUD_UI_EXPORT func_ Widget& icon(Widget& parent, cstring image);
	export_ MUD_UI_EXPORT func_ Widget& label(Widget& parent, cstring label);
	export_ MUD_UI_EXPORT func_ Widget& title(Widget& parent, cstring label);
	export_ MUD_UI_EXPORT func_ Widget& message(Widget& parent, cstring label);
	export_ MUD_UI_EXPORT func_ Widget& text(Widget& parent, cstring label);
	export_ MUD_UI_EXPORT func_ Widget& bullet(Widget& parent, cstring label);
	export_ MUD_UI_EXPORT func_ Widget& selectable(Widget& parent, cstring label, bool& selected);

	export_ MUD_UI_EXPORT func_ Widget& labelf(Widget& parent, cstring label, ...);

	export_ MUD_UI_EXPORT Widget& icon(Widget& parent, const string& image);
	export_ MUD_UI_EXPORT Widget& label(Widget& parent, const string& text);
	export_ MUD_UI_EXPORT Widget& title(Widget& parent, const string& label);
	export_ MUD_UI_EXPORT Widget& message(Widget& parent, const string& label);
	export_ MUD_UI_EXPORT Widget& text(Widget& parent, const string& label);
	export_ MUD_UI_EXPORT Widget& bullet(Widget& parent, const string& label);
	export_ MUD_UI_EXPORT Widget& selectable(Widget& parent, const string& label, bool& selected);

	export_ MUD_UI_EXPORT void button_logic(Widget& self);
	export_ MUD_UI_EXPORT void toggle_logic(Widget& self, bool& on);

	export_ MUD_UI_EXPORT Widget& button(Widget& parent, Style& style, cstring content = nullptr);
	export_ MUD_UI_EXPORT Widget& toggle(Widget& parent, Style& style, bool& on, cstring content = nullptr);

	export_ MUD_UI_EXPORT Widget& multi_button(Widget& parent, Style& style, span<cstring> elements, Style* element_style = nullptr);
	export_ MUD_UI_EXPORT Widget& multi_toggle(Widget& parent, Style& style, bool& on, span<cstring> elements, Style* element_style = nullptr);

	export_ MUD_UI_EXPORT func_ Widget& button(Widget& parent, cstring content = nullptr);
	export_ MUD_UI_EXPORT func_ Widget& toggle(Widget& parent, bool& on, cstring content = nullptr);

	export_ MUD_UI_EXPORT func_ Widget& button(Widget& parent, const string& content);
	export_ MUD_UI_EXPORT func_ Widget& toggle(Widget& parent, bool& on, const string& content);

	export_ MUD_UI_EXPORT func_ Widget& multi_button(Widget& parent, span<cstring> elements, Style* element_style = nullptr);
	export_ MUD_UI_EXPORT func_ Widget& multi_toggle(Widget& parent, bool& on, span<cstring> elements, Style* element_style = nullptr);

	export_ MUD_UI_EXPORT func_ bool modal_button(Widget& screen, Widget& parent, cstring content, uint32_t mode);
	export_ MUD_UI_EXPORT func_ bool modal_multi_button(Widget& screen, Widget& parent, span<cstring> elements, uint32_t mode);

	export_ MUD_UI_EXPORT func_ Widget& checkbox(Widget& parent, bool& on);
	export_ MUD_UI_EXPORT func_ Widget& fill_bar(Widget& parent, float percentage, Axis dim = Axis::X);

	export_ MUD_UI_EXPORT func_ Widget& image256(Widget& parent, cstring name, const Image256& source);
	export_ MUD_UI_EXPORT func_ Widget& image256(Widget& parent, cstring name, const Image256& source, const vec2& size);

	export_ MUD_UI_EXPORT func_ Widget& image256(Widget& parent, const string& name, const Image256& source);
	export_ MUD_UI_EXPORT func_ Widget& image256(Widget& parent, const string& name, const Image256& source, const vec2& size);

	export_ MUD_UI_EXPORT func_ Widget& radio_choice(Widget& parent, cstring label, bool active);
	export_ MUD_UI_EXPORT func_ Widget& radio_button(Widget& parent, cstring label, uint32_t& value, uint32_t index);

	export_ MUD_UI_EXPORT func_ bool radio_switch(Widget& parent, span<cstring> labels, uint32_t& value, Axis dim = Axis::X);
	//MUD_UI_EXPORT bool radio_switch(Widget& parent, span<cstring> labels, string& value, Axis dim = Axis::X);

	//inline bool radio_switch_string(Widget& parent, span<cstring> labels, string& value) { return radio_switch(parent, labels, value); }

	export_ MUD_UI_EXPORT func_ bool popdown(Widget& parent, span<cstring> choices, uint32_t& value, vec2 position, PopupFlags flags);
	export_ MUD_UI_EXPORT func_ Widget& dropdown(Widget& parent, Style& style, cstring value, PopupFlags flags, bool no_toggle = false, Style* list_style = nullptr);
	export_ MUD_UI_EXPORT func_ bool dropdown_input(Widget& parent, span<cstring> choices, uint32_t& value, bool compact = false);
	export_ MUD_UI_EXPORT func_ bool typedown_input(Widget& parent, span<cstring> choices, uint32_t& value);

	export_ MUD_UI_EXPORT Widget& menu_choice(Widget& parent, span<cstring> elements);
	export_ MUD_UI_EXPORT func_ Widget& menu_choice(Widget& parent, cstring content, cstring shortcut = nullptr);
	export_ MUD_UI_EXPORT func_ Widget& menu_option(Widget& parent, cstring content, cstring shortcut, bool enabled);
	export_ MUD_UI_EXPORT func_ Widget& menu(Widget& parent, cstring label, bool submenu = false);
	export_ MUD_UI_EXPORT func_ Widget& menubar(Widget& parent);

	export_ MUD_UI_EXPORT func_ Widget& toolbutton(Widget& parent, cstring icon);
	export_ MUD_UI_EXPORT func_ Widget& tooldock(Widget& parent);
	export_ MUD_UI_EXPORT func_ Widget& toolbar(Widget& parent, bool wrap = false);
}
}
