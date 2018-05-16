//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <ui/Generated/Types.h>
#include <ui/Button.h>
#include <ui/Scrollbar.h>
#include <ui/ScrollSheet.h>
#include <ui/Cursor.h>

#include <obj/Arg.h>
#include <ui/Style/Layout.h>
#include <ui/Style/Skin.h>

namespace mud
{
namespace ui
{
	CursorStyles::CursorStyles()
		: cursor("Cursor", styles().decal, { { { &Layout::m_zorder, -1 } } })
		, resize_x("CursorResizeX", cursor, { { { &InkStyle::m_padding, vec4{ -10.f, -10.f, +10.f, +10.f } } } })
		, resize_y("CursorResizeY", cursor, { { { &InkStyle::m_padding, vec4{ -10.f, -10.f, +10.f, +10.f } } } })
		, move("CursorMove", cursor, { { { &InkStyle::m_padding, vec4{ -10.f, -10.f, +10.f, +10.f } } } })
		, resize_diag_left("CursorResizeDiagLeft", cursor, { { { &InkStyle::m_padding, vec4{ -10.f, -10.f, +10.f, +10.f } } } })
		, resize_diag_right("CursorResizeDiagRight", cursor, { { { &InkStyle::m_padding, vec4{ -10.f, -10.f, +10.f, +10.f } } } })
		, caret("CursorCaret", cursor, { { { &InkStyle::m_padding, vec4{ -4.f, -9.f, +4.f, +9.f } } } })
	{}

	CursorStyles& cursor_styles() { static CursorStyles styles; return styles; }

	ScrollbarStyles::ScrollbarStyles()
		: scrollbar("Scrollbar", styles().row, {})
		, scroll_up("ScrollUp", styles().button, {})
		, scroll_down("ScrollDown", styles().button, {})
		, scroll_left("ScrollLeft", styles().button, {})
		, scroll_right("ScrollRight", styles().button, {})
		, scroller("Scroller", styles().slider, { { { &Layout::m_space, FLEX } } })
		, scroller_knob("ScrollerKnob", styles().slider_knob, { { { &Layout::m_space, FLEX } } })
	{}

	DropdownStyles::DropdownStyles()
		: popdown("Popdown", styles().popup, { { { &Layout::m_flow, FREE }, { &Layout::m_space, BLOCK }, { &Layout::m_size, vec2{ 200.f, 200.f } } } })
		, dropdown("Dropdown", styles().wrap_button, {})
		, toggle("DropdownToggle", styles().button, {})
		, head("DropdownHead", styles().multi_button, {})
		, list("DropdownList", styles().overlay, { { { &Layout::m_flow, ALIGN }, { &Layout::m_clipping, UNCLIP }, { &Layout::m_align, Dim2<Align>{ LEFT, OUT_RIGHT } } } })
		, choice("DropdownChoice", styles().multi_button, {})
		, dropdown_input("DropdownInput", dropdown, {})
		, dropdown_input_compact("DropdownInputCompact", dropdown, { { { &Layout::m_space, ITEM } } })
		, typedown_input("TypedownInput", dropdown, {})
	{}

	MenuStyles::MenuStyles()
		: menubar("Menubar", styles().header, {})
		, menu("Menu", dropdown_styles().dropdown, { { { &Layout::m_space, ITEM } } })
		, list("MenuList", dropdown_styles().list, { { { &Layout::m_align, Dim2<Align>{ LEFT, OUT_RIGHT } } } })
		, sublist("SubMenuList", list, { { { &Layout::m_align, Dim2<Align>{ OUT_RIGHT, LEFT } } } })
	{}

	ToolbarStyles::ToolbarStyles()
		: toolbutton("ToolButton", dropdown_styles().dropdown_input, {})
		, tooldock("Tooldock", styles().div, {})
		, toolbar("Toolbar", styles().wrap_control, {})
		, toolbar_wrap("ToolbarWrap", toolbar, { { { &Layout::m_space, ITEM } } })
		, mover("ToolbarMover", styles().control, {})
	{}

	ScrollbarStyles& scrollbar_styles() { static ScrollbarStyles styles; return styles; }
	DropdownStyles& dropdown_styles() { static DropdownStyles styles; return styles; }
	MenuStyles& menu_styles() { static MenuStyles styles; return styles; }
	ToolbarStyles& toolbar_styles() { static ToolbarStyles styles; return styles; }
}
}
