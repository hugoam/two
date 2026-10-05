//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Forward.h>
#include <ui/Style/Style.h>
#include <ui/Widget.h>

namespace two
{
namespace ui
{
	export_ struct DropdownStyles
	{
		void reset();
		Style popdown; Style dropdown; Style toggle; Style head; Style list; Style choice; Style dropdown_input; Style dropdown_input_compact; Style typedown_input;
	};

	export_ TWO_UI_EXPORT DropdownStyles& dropdown_styles();

	// a dropdown opened by its header: the list is in the body when it's open
	export_ struct Dropdown
	{
		Widget& self;
		Widget* body;
		operator Widget&() const { return self; }
	};

	export_ struct MenuStyles
	{
		void reset();
		Style menubar; Style menu; Style list; Style sublist; Style choice;
	};

	export_ TWO_UI_EXPORT MenuStyles& menu_styles();

	export_ struct ToolbarStyles
	{
		void reset();
		Style toolbutton; Style tooldock; Style toolbar; Style toolbar_wrap; Style mover;
	};

	export_ TWO_UI_EXPORT ToolbarStyles& toolbar_styles();

	export_ enum class refl_ PopupFlags : unsigned int
	{
		None = 0,
		Modal = (1 << 0),
		Clamp = (1 << 1),
		AutoClose = (1 << 2),
		AutoModal = Modal | AutoClose,
	};

	export_ TWO_UI_EXPORT func_ Widget& spacer(NodeKey id, Widget& parent);
	export_ TWO_UI_EXPORT func_ Widget& separator(NodeKey id, Widget& parent);

	export_ TWO_UI_EXPORT func_ Widget& icon(NodeKey id, Widget& parent, cstring image);
	export_ TWO_UI_EXPORT func_ Widget& label(NodeKey id, Widget& parent, cstring label);
	export_ TWO_UI_EXPORT func_ Widget& title(NodeKey id, Widget& parent, cstring label);
	export_ TWO_UI_EXPORT func_ Widget& message(NodeKey id, Widget& parent, cstring label);
	export_ TWO_UI_EXPORT func_ Widget& text(NodeKey id, Widget& parent, cstring label);
	export_ TWO_UI_EXPORT func_ Widget& bullet(NodeKey id, Widget& parent, cstring label);
	export_ TWO_UI_EXPORT func_ Widget& selectable(NodeKey id, Widget& parent, cstring label, bool& selected);

	export_ TWO_UI_EXPORT Widget& labelf(NodeKey id, Widget& parent, cstring label, ...);

	export_ TWO_UI_EXPORT Widget& icon(NodeKey id, Widget& parent, const string& image);
	export_ TWO_UI_EXPORT Widget& label(NodeKey id, Widget& parent, const string& text);
	export_ TWO_UI_EXPORT Widget& title(NodeKey id, Widget& parent, const string& label);
	export_ TWO_UI_EXPORT Widget& message(NodeKey id, Widget& parent, const string& label);
	export_ TWO_UI_EXPORT Widget& text(NodeKey id, Widget& parent, const string& label);
	export_ TWO_UI_EXPORT Widget& bullet(NodeKey id, Widget& parent, const string& label);
	export_ TWO_UI_EXPORT Widget& selectable(NodeKey id, Widget& parent, const string& label, bool& selected);

	export_ TWO_UI_EXPORT void button_logic(Widget& self);
	export_ TWO_UI_EXPORT void toggle_logic(Widget& self, bool& on);

	export_ TWO_UI_EXPORT Widget& button(NodeKey id, Widget& parent, Style& style, cstring content = nullptr);
	export_ TWO_UI_EXPORT Widget& toggle(NodeKey id, Widget& parent, Style& style, bool& on, cstring content = nullptr);

	export_ TWO_UI_EXPORT Widget& multi_button(NodeKey id, Widget& parent, Style& style, span<cstring> elements, Style* element_style = nullptr);
	export_ TWO_UI_EXPORT Widget& multi_toggle(NodeKey id, Widget& parent, Style& style, bool& on, span<cstring> elements, Style* element_style = nullptr);

	export_ TWO_UI_EXPORT func_ Widget& button(NodeKey id, Widget& parent, cstring content = nullptr);
	export_ TWO_UI_EXPORT func_ Widget& toggle(NodeKey id, Widget& parent, bool& on, cstring content = nullptr);

	export_ TWO_UI_EXPORT func_ Widget& button(NodeKey id, Widget& parent, const string& content);
	export_ TWO_UI_EXPORT func_ Widget& toggle(NodeKey id, Widget& parent, bool& on, const string& content);

	export_ TWO_UI_EXPORT func_ Widget& multi_button(NodeKey id, Widget& parent, span<cstring> elements, Style* element_style = nullptr);
	export_ TWO_UI_EXPORT func_ Widget& multi_toggle(NodeKey id, Widget& parent, bool& on, span<cstring> elements, Style* element_style = nullptr);

	export_ TWO_UI_EXPORT func_ bool modal_button(NodeKey id, Widget& screen, Widget& parent, cstring content, uint32_t mode);
	export_ TWO_UI_EXPORT func_ bool modal_multi_button(NodeKey id, Widget& screen, Widget& parent, span<cstring> elements, uint32_t mode);

	export_ TWO_UI_EXPORT func_ Widget& checkbox(NodeKey id, Widget& parent, bool& on);
	export_ TWO_UI_EXPORT func_ Widget& fill_bar(NodeKey id, Widget& parent, float percentage, Axis dim = Axis::X);

	export_ TWO_UI_EXPORT func_ Widget& image256(NodeKey id, Widget& parent, cstring name, const Image256& source);
	export_ TWO_UI_EXPORT func_ Widget& image256(NodeKey id, Widget& parent, cstring name, const Image256& source, const vec2& size);

	export_ TWO_UI_EXPORT func_ Widget& image256(NodeKey id, Widget& parent, const string& name, const Image256& source);
	export_ TWO_UI_EXPORT func_ Widget& image256(NodeKey id, Widget& parent, const string& name, const Image256& source, const vec2& size);

	export_ TWO_UI_EXPORT func_ Widget& radio_choice(NodeKey id, Widget& parent, cstring label, bool active);
	export_ TWO_UI_EXPORT func_ Widget& radio_button(NodeKey id, Widget& parent, cstring label, uint32_t& value, uint32_t index);

	export_ TWO_UI_EXPORT func_ bool radio_switch(NodeKey id, Widget& parent, span<cstring> labels, uint32_t& value, Axis dim = Axis::X);
	//TWO_UI_EXPORT bool radio_switch(NodeKey id, Widget& parent, span<cstring> labels, string& value, Axis dim = Axis::X);

	//inline bool radio_switch_string(NodeKey id, Widget& parent, span<cstring> labels, string& value) { return radio_switch(id, parent, labels, value); }

	export_ TWO_UI_EXPORT func_ bool popdown(NodeKey id, Widget& parent, span<cstring> choices, uint32_t& value, vec2 position, PopupFlags flags);
	export_ TWO_UI_EXPORT Dropdown dropdown(NodeKey id, Widget& parent, Style& style, cstring value, PopupFlags flags, bool no_toggle = false, Style* list_style = nullptr);
	export_ TWO_UI_EXPORT func_ bool dropdown_input(NodeKey id, Widget& parent, span<cstring> choices, uint32_t& value, bool compact = false);
	export_ TWO_UI_EXPORT func_ bool typedown_input(NodeKey id, Widget& parent, span<cstring> choices, uint32_t& value);

	export_ TWO_UI_EXPORT Widget& menu_choice(NodeKey id, Widget& parent, span<cstring> elements);
	export_ TWO_UI_EXPORT func_ Widget& menu_choice(NodeKey id, Widget& parent, cstring content, cstring shortcut = nullptr);
	export_ TWO_UI_EXPORT func_ Widget& menu_option(NodeKey id, Widget& parent, cstring content, cstring shortcut, bool enabled);
	export_ TWO_UI_EXPORT Dropdown menu(NodeKey id, Widget& parent, cstring label, bool submenu = false);
	export_ TWO_UI_EXPORT func_ Widget& menubar(NodeKey id, Widget& parent);

	export_ TWO_UI_EXPORT func_ Widget& toolbutton(NodeKey id, Widget& parent, cstring icon);
	export_ TWO_UI_EXPORT func_ Widget& tooldock(NodeKey id, Widget& parent);
	export_ TWO_UI_EXPORT func_ Widget& toolbar(NodeKey id, Widget& parent, bool wrap = false);
}
}
