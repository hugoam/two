//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ui;
#else
#include <ui/Button.h>
#include <ui/Scrollbar.h>
#include <ui/ScrollSheet.h>
#include <ui/Cursor.h>
#include <ui/Style/Layout.h>
#include <ui/Style/Skin.h>
#endif

namespace mud
{
namespace ui
{
	void CursorStyles::reset()
	{
		cursor = Style("Cursor", styles().decal, [](Layout& l) { l.m_zorder = -1; }, {});
		resize_x = Style("CursorResizeX", cursor, {}, [](InkStyle& s) { s.m_padding = { vec2(-10.f), vec2(10.f) }; });
		resize_y = Style("CursorResizeY", cursor, {}, [](InkStyle& s) { s.m_padding = { vec2(-10.f), vec2(10.f) }; });
		move = Style("CursorMove", cursor, {}, [](InkStyle& s) { s.m_padding = { vec2(-10.f), vec2(10.f) }; });
		resize_diag_left = Style("CursorResizeDiagLeft", cursor, {}, [](InkStyle& s) { s.m_padding = { vec2(-10.f), vec2(10.f) }; });
		resize_diag_right = Style("CursorResizeDiagRight", cursor, {}, [](InkStyle& s) { s.m_padding = { vec2(-10.f), vec2(10.f) }; });
		caret = Style("CursorCaret", cursor, {}, [](InkStyle& s) { s.m_padding = { -4.f, -9.f, +4.f, +9.f }; });

		register_styles({ &cursor, &resize_x, &resize_y, &move, &resize_diag_left, &resize_diag_right, &caret });
	}

	CursorStyles& cursor_styles() { static CursorStyles styles; return styles; }

	void ScrollbarStyles::reset()
	{
		scrollbar = Style("Scrollbar", styles().row, {});
		scroll_up = Style("ScrollUp", styles().button, {});
		scroll_down = Style("ScrollDown", styles().button, {});
		scroll_left = Style("ScrollLeft", styles().button, {});
		scroll_right = Style("ScrollRight", styles().button, {});
		scroller = Style("Scroller", styles().slider, [](Layout& l) { l.m_space = Preset::Flex; });
		scroller_knob = Style("ScrollerKnob", styles().slider_knob, [](Layout& l) { l.m_space = Preset::Flex; });

		register_styles({ &scrollbar, &scroll_up, &scroll_down, &scroll_left, &scroll_right, &scroller, &scroller_knob });
	}

	void DropdownStyles::reset()
	{
		popdown = Style("Popdown", styles().popup, [](Layout& l) { l.m_flow = LayoutFlow::Free; l.m_space = Preset::Block; l.m_size = { 200.f, 200.f }; });
		dropdown = Style("Dropdown", styles().wrap_button, {});
		toggle = Style("DropdownToggle", styles().button, {});
		head = Style("DropdownHead", styles().multi_button, {});
		list = Style("DropdownList", styles().overlay, [](Layout& l) { l.m_flow = LayoutFlow::Align; l.m_clipping = Clip::Unclip; l.m_align = { Align::Left, Align::OutRight }; });
		choice = Style("DropdownChoice", styles().multi_button, {});
		dropdown_input = Style("DropdownInput", dropdown, {});
		dropdown_input_compact = Style("DropdownInputCompact", dropdown, [](Layout& l) { l.m_space = Preset::Item; });
		typedown_input = Style("TypedownInput", dropdown, {});

		register_styles({ &popdown, &dropdown, &toggle, &head, &list, &choice, &dropdown_input, &dropdown_input_compact, &typedown_input});
	}

	void MenuStyles::reset()
	{
		menubar = Style("Menubar", styles().header, {});
		menu = Style("Menu", dropdown_styles().dropdown, [](Layout& l) { l.m_space = Preset::Item; });
		list = Style("MenuList", dropdown_styles().list, [](Layout& l) { l.m_align = { Align::Left, Align::OutRight }; });
		sublist = Style("SubMenuList", list, [](Layout& l) { l.m_align = { Align::OutRight, Align::Left }; });
		choice = Style("MenuChoice", styles().multi_button, {});

		register_styles({ &menubar, &menu, &list, &sublist, &choice });
	}

	void ToolbarStyles::reset()
	{
		toolbutton = Style("ToolButton", dropdown_styles().dropdown_input, {});
		tooldock = Style("Tooldock", styles().div, {});
		toolbar = Style("Toolbar", styles().wrap_control, {});
		toolbar_wrap = Style("ToolbarWrap", toolbar, [](Layout& l) { l.m_space = Preset::Item; });
		mover = Style("ToolbarMover", styles().control, {});

		register_styles({ &toolbutton, &tooldock, &toolbar, &toolbar_wrap, &mover });
	}

	ScrollbarStyles& scrollbar_styles() { static ScrollbarStyles styles; return styles; }
	DropdownStyles& dropdown_styles() { static DropdownStyles styles; return styles; }
	MenuStyles& menu_styles() { static MenuStyles styles; return styles; }
	ToolbarStyles& toolbar_styles() { static ToolbarStyles styles; return styles; }
}
}
