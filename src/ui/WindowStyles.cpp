//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
module two.ui;
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

namespace two
{
namespace ui
{
	void WindowStyles::reset()
	{
		window = Style("Window", styles().overlay, [](Layout& l) { l.m_space = Preset::Block; });
		body = Style("WindowBody", styles().wedge, [](Layout& l) { l.m_clipping = Clip::Clip; });
		close_button = Style("CloseButton", styles().button, [](Layout& l) { l.m_align = { Align::Right, Align::Center }; });
		header = Style("WindowHeader", styles().wrap_control, {}, {});
		header_movable = Style("WindowHeaderMovable", header, {}, {}); //, [](InkStyle& l) { l.m_hover_cursor = &cursor_styles().move; } })
		footer = Style("WindowFooter", styles().wrap_control, {}, {}); // , [](Layout& l) { l.m_space = Space{ FlowAxis::Reading, Sizing::Wrap, Sizing::Fixed }; } }
		sizer = Style("WindowSizer", styles().control, [](Layout& l) { l.m_space = Space{ FlowAxis::Reading, Sizing::Wrap, Sizing::Fixed }; });
		sizer_left = Style("WindowSizerLeft", sizer, {}, {}); //, [](InkStyle& l) { l.m_hover_cursor = &cursor_styles().resize_diag_left; } })
		sizer_right = Style("WindowSizerRight", sizer, {}, {}); //, [](InkStyle& l) { l.m_hover_cursor = &cursor_styles().resize_diag_right; } })

		dock_window = Style("DockWindow", window, [](Layout& l) { l.m_flow = LayoutFlow::Flow; l.m_space = Preset::Sheet; });
		wrap_window = Style("WrapWindow", window, [](Layout& l) { l.m_space = Preset::Unit; });

		register_styles({ &window, &body, &close_button, &header, &header_movable, &footer, &sizer, &sizer_left, &sizer_right, &dock_window, &wrap_window });
	}

	WindowStyles& window_styles() { static WindowStyles styles; return styles; }

	void DockStyles::reset()
	{
		docktab = Style("Docktab", tabber_styles().tab, {}, {});
		placeholder = Style("Placeholder", styles().board, {}, [](InkStyle& l) { l.m_background_colour = Colour::Blue; });

		docksection = Style("Docksection", styles().gridsheet, {}, {});
		dockline = Style("Dockline", styles().gridsheet, [](Layout& l) { l.m_space = Preset::Sheet; });
		dockspace = Style("Dockspace", styles().layout, [](Layout& l) { l.m_opacity = Opacity::Opaque; l.m_spacing = vec2(6.f); });

		docktoggle = Style("DockToggle", styles().toggle, [](Layout& l) { l.m_align = { Align::Left, Align::Left }; });
		dockdiv = Style("Dockzone", styles().wedge, [](Layout& l) { l.m_space = { FlowAxis::Paragraph, Sizing::Wrap, Sizing::Fixed }; });
		//dockdiv = Style("Dockzone", styles().wedge, [](Layout& l) { l.m_flow = LayoutFlow::Align; l.m_space = Preset::Spacer; l.m_align = { Align::Left, OUT_LEFT }; });
		docktabs = Style("Docktabs", styles().wedge, [](Layout& l) { l.m_flow = LayoutFlow::Align; l.m_space = Preset::Div; l.m_align = { Align::OutLeft, Align::Left }; });
		dockbar = Style("Dockbar", styles().wedge, [](Layout& l) { l.m_space = { FlowAxis::Same, Sizing::Shrink, Sizing::Wrap }; });

		//dockbox = Style("Dockbox", window_styles().window, [](Layout& l) { l.m_flow = LayoutFlow::Flow; l.m_space = { FlowAxis::Paragraph, Sizing::Wrap, Sizing::Shrink }; l.m_size = { 300.f, 0.f }; });

		register_styles({ &docktab, &placeholder, &docksection, &dockline, &dockspace, &docktoggle, &dockdiv, &docktabs, &dockbar });
	}

	DockStyles& dock_styles() { static DockStyles styles; return styles; }

	void NodeStyles::reset()
	{
		node = Style("Node", styles().overlay, [](Layout& l) { l.m_space = Preset::Unit; });
		body = Style("NodeBody", styles().sheet, {}, {});
		plugs = Style("NodePlugs", styles().sheet, [](Layout& l) { l.m_space = { FlowAxis::Reading, Sizing::Wrap, Sizing::Wrap }; });
		inputs = Style("NodeInputs", styles().div, {}, {});
		outputs = Style("NodeOutputs", styles().div, [](Layout& l) { l.m_align = { Align::Right, Align::Center }; });
		knob = Style("NodeKnob", styles().item, [](Layout& l) { l.m_size = vec2(10.f, 10.f); }, [](InkStyle& l) { l.m_background_colour = Colour::White; });
		knob_output = Style("NodeKnobOutput", knob, [](Layout& l) { l.m_align = { Align::Right, Align::Center }; }, [](InkStyle& l) { l.m_background_colour = Colour::White; });
		knob_proxy = Style("NodeKnobProxy", knob, [](Layout& l) { l.m_flow = LayoutFlow::Free; });
		plug = Style("NodePlug", styles().wrap_control, {}, {});
		cable = Style("NodeCable", styles().decal, [](Layout& l) { l.m_space = Preset::Unit; }, [](InkStyle& l) { l.m_background_colour = Colour::White; });
		header = Style("NodeHeader", styles().row, {}, {});

		register_styles({ &node, &body, &plugs, &inputs, &outputs, &knob, &knob_output, &knob_proxy, &plug, &cable, &header });
	}

	void CanvasStyles::reset()
	{
		canvas = Style("Canvas", styles().layout, [](Layout& l) { l.m_clipping = Clip::Clip; }); // l.m_opacity = Opacity::Opaque;

		register_styles({ &canvas });
	}

	NodeStyles& node_styles() { static NodeStyles styles; return styles; }
	CanvasStyles& canvas_styles() { static CanvasStyles styles; return styles; }
}
}
