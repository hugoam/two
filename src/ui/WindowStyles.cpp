//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <ui/Generated/Types.h>
#include <ui/Window.h>
#include <ui/Dock.h>
#include <ui/Node.h>
#include <ui/Container.h>
#include <ui/Cursor.h>

#include <obj/Arg.h>
#include <ui/Style/Layout.h>
#include <ui/Style/Skin.h>

#define CANVAS_MULTI_DRAG 1

namespace mud
{
namespace ui
{
	WindowStyles::WindowStyles()
		: window("Window", styles().overlay, { { { &Layout::m_space, BLOCK } } })
		, body("WindowBody", styles().wedge, { { { &Layout::m_clipping, CLIP } } })
		, close_button("CloseButton", styles().button, { { { &Layout::m_align, Dim2<Align>{ RIGHT, CENTER } } } })
		, header("WindowHeader", styles().wrap_control, {})
		, header_movable("WindowHeaderMovable", header, {}) //{ { &InkStyle::m_hover_cursor, &cursor_styles().move } } })
		, footer("WindowFooter", styles().wrap_control, { /*{ &Layout::m_space, Space{ READING, WRAP, FIXED } }*/ })
		, sizer("WindowSizer", styles().control, { { { &Layout::m_space, Space{ READING, WRAP, FIXED } } } })
		, sizer_left("WindowSizerLeft", sizer, {}) //{ { &InkStyle::m_hover_cursor, &cursor_styles().resize_diag_left } } })
		, sizer_right("WindowSizerRight", sizer, {}) // { { &InkStyle::m_hover_cursor, &cursor_styles().resize_diag_right } } })

		, dock_window("DockWindow", window, { { { &Layout::m_flow, FLOW }, { &Layout::m_space, SHEET } } })
		, wrap_window("WrapWindow", window, { { { &Layout::m_space, UNIT } } })
	{}

	WindowStyles& window_styles() { static WindowStyles styles; return styles; }

	DockStyles::DockStyles()
		: docktab("Docktab", tabber_styles().tab, {})
		, placeholder("Placeholder", styles().board, { { { &InkStyle::m_background_colour, Colour::Blue } } })

		, docksection("Docksection", styles().gridsheet, {})
		, dockline("Dockline", styles().gridsheet, { { { &Layout::m_space, SHEET } } })
		, dockspace("Dockspace", styles().layout, { { { &Layout::m_opacity, OPAQUE }, { &Layout::m_spacing, vec2(6.f) } } })

		, docktoggle("DockToggle", styles().toggle, {})
		, dockdiv("Dockzone", styles().wedge, { { { &Layout::m_space, Space{ PARAGRAPH, WRAP, FIXED } } } })
		//, dockdiv("Dockzone", styles().wedge, { { { &Layout::m_flow, ALIGN }, { &Layout::m_space, SPACER }, { &Layout::m_align, Dim2<Align>{ LEFT, OUT_LEFT } } })
		, docktabs("Docktabs", styles().wedge, { { { &Layout::m_flow, ALIGN }, { &Layout::m_space, DIV }, { &Layout::m_align, Dim2<Align>{ OUT_LEFT, LEFT } } } })
		, dockbar("Dockbar", styles().wedge, { { { &Layout::m_space, Space{ PARALLEL, SHRINK, WRAP } } } })

		//, dockbox("Dockbox", window_styles().window, Args{ { &Layout::m_flow, FLOW }, { &Layout::m_space, Space{ PARAGRAPH, WRAP, SHRINK } }, { &Layout::m_size, vec2{ 300.f, 0.f } } })
	{}

	DockStyles& dock_styles() { static DockStyles styles; return styles; }

	NodeStyles::NodeStyles()
		: node("Node", styles().overlay, { { { &Layout::m_space, UNIT } } })
		, body("NodeBody", styles().sheet, {})
		, plugs("NodePlugs", styles().sheet, { { { &Layout::m_space, Space{ READING, WRAP, WRAP } } } })
		, inputs("NodeInputs", styles().div, {})
		, outputs("NodeOutputs", styles().div, { { { &Layout::m_align, Dim2<Align>{ RIGHT, CENTER } } } })
		, knob("NodeKnob", styles().item, { { { &Layout::m_size, vec2{ 10.f, 22.f } }, { &InkStyle::m_background_colour, Colour::White } } })
		, knob_output("NodeKnobOutput", knob, { { { &Layout::m_align, Dim2<Align>{ RIGHT, CENTER } }, { &InkStyle::m_background_colour, Colour::White } } })
		, knob_proxy("NodeKnobProxy", knob, { { { &Layout::m_flow, FREE } } })
		, plug("NodePlug", styles().wrap_control, {})
		, cable("NodeCable", styles().decal, { { { &Layout::m_space, UNIT }, { &InkStyle::m_background_colour, Colour::White } } })
		, header("NodeHeader", styles().row, {})
	{}

	CanvasStyles::CanvasStyles()
		: canvas("Canvas", styles().layout, { { /*{ &Layout::m_opacity, OPAQUE },*/{ &Layout::m_clipping, CLIP } } })
	{}

	NodeStyles& node_styles() { static NodeStyles styles; return styles; }
	CanvasStyles& canvas_styles() { static CanvasStyles styles; return styles; }
}
}
