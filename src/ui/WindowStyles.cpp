//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ui;
#else
#include <ui/Window.h>
#include <ui/Dock.h>
#include <ui/Node.h>
#include <ui/Container.h>
#include <ui/Cursor.h>
#include <ui/Style/Layout.h>
#include <ui/Style/Skin.h>
#endif

#define CANVAS_MULTI_DRAG 1

namespace mud
{
namespace ui
{
	WindowStyles::WindowStyles()
		: window("Window", styles().overlay, [](Layout& l) { l.m_space = Preset::Block; })
		, body("WindowBody", styles().wedge, [](Layout& l) { l.m_clipping = Clip::Clip; })
		, close_button("CloseButton", styles().button, [](Layout& l) { l.m_align = { Align::Right, Align::Center }; })
		, header("WindowHeader", styles().wrap_control, {}, {})
		, header_movable("WindowHeaderMovable", header, {}, {}) //, [](InkStyle& l) { l.m_hover_cursor = &cursor_styles().move; } })
		, footer("WindowFooter", styles().wrap_control, {}, {}) // , [](Layout& l) { l.m_space = Space{ FlowAxis::Reading, Sizing::Wrap, Sizing::Fixed }; } }
		, sizer("WindowSizer", styles().control, [](Layout& l) { l.m_space = Space{ FlowAxis::Reading, Sizing::Wrap, Sizing::Fixed }; })
		, sizer_left("WindowSizerLeft", sizer, {}, {}) //, [](InkStyle& l) { l.m_hover_cursor = &cursor_styles().resize_diag_left; } })
		, sizer_right("WindowSizerRight", sizer, {}, {}) //, [](InkStyle& l) { l.m_hover_cursor = &cursor_styles().resize_diag_right; } })

		, dock_window("DockWindow", window, [](Layout& l) { l.m_flow = LayoutFlow::Flow; l.m_space = Preset::Sheet; })
		, wrap_window("WrapWindow", window, [](Layout& l) { l.m_space = Preset::Unit; })
	{}

	WindowStyles& window_styles() { static WindowStyles styles; return styles; }

	DockStyles::DockStyles()
		: docktab("Docktab", tabber_styles().tab, {}, {})
		, placeholder("Placeholder", styles().board, {}, [](InkStyle& l) { l.m_background_colour = Colour::Blue; })

		, docksection("Docksection", styles().gridsheet, {}, {})
		, dockline("Dockline", styles().gridsheet, [](Layout& l) { l.m_space = Preset::Sheet; })
		, dockspace("Dockspace", styles().layout, [](Layout& l) { l.m_opacity = Opacity::Opaque; l.m_spacing = vec2(6.f); })

		, docktoggle("DockToggle", styles().toggle, {}, {})
		, dockdiv("Dockzone", styles().wedge, [](Layout& l) { l.m_space = { FlowAxis::Paragraph, Sizing::Wrap, Sizing::Fixed }; })
		//, dockdiv("Dockzone", styles().wedge, [](Layout& l) { l.m_flow = LayoutFlow::Align; l.m_space = Preset::Spacer; l.m_align = { Align::Left, OUT_LEFT }; })
		, docktabs("Docktabs", styles().wedge, [](Layout& l) { l.m_flow = LayoutFlow::Align; l.m_space = Preset::Div; l.m_align = { Align::OutLeft, Align::Left }; })
		, dockbar("Dockbar", styles().wedge, [](Layout& l) { l.m_space = { FlowAxis::Same, Sizing::Shrink, Sizing::Wrap }; })

		//, dockbox("Dockbox", window_styles().window, [](Layout& l) { l.m_flow = LayoutFlow::Flow; l.m_space = { FlowAxis::Paragraph, Sizing::Wrap, Sizing::Shrink }; l.m_size = { 300.f, 0.f }; })
	{}

	DockStyles& dock_styles() { static DockStyles styles; return styles; }

	NodeStyles::NodeStyles()
		: node("Node", styles().overlay, [](Layout& l) { l.m_space = Preset::Unit; })
		, body("NodeBody", styles().sheet, {}, {})
		, plugs("NodePlugs", styles().sheet, [](Layout& l) { l.m_space = { FlowAxis::Reading, Sizing::Wrap, Sizing::Wrap }; })
		, inputs("NodeInputs", styles().div, {}, {})
		, outputs("NodeOutputs", styles().div, [](Layout& l) { l.m_align = { Align::Right, Align::Center }; })
		, knob("NodeKnob", styles().item, [](Layout& l) { l.m_size = { 10.f, 22.f }; }, [](InkStyle& l) { l.m_background_colour = Colour::White; })
		, knob_output("NodeKnobOutput", knob, [](Layout& l) { l.m_align = { Align::Right, Align::Center }; }, [](InkStyle& l) { l.m_background_colour = Colour::White; })
		, knob_proxy("NodeKnobProxy", knob, [](Layout& l) { l.m_flow = LayoutFlow::Free; })
		, plug("NodePlug", styles().wrap_control, {}, {})
		, cable("NodeCable", styles().decal, [](Layout& l) { l.m_space = Preset::Unit; }, [](InkStyle& l) { l.m_background_colour = Colour::White; })
		, header("NodeHeader", styles().row, {}, {})
	{}

	CanvasStyles::CanvasStyles()
		: canvas("Canvas", styles().layout, [](Layout& l) { l.m_clipping = Clip::Clip; }) // l.m_opacity = Opacity::Opaque;
	{}

	NodeStyles& node_styles() { static NodeStyles styles; return styles; }
	CanvasStyles& canvas_styles() { static CanvasStyles styles; return styles; }
}
}
