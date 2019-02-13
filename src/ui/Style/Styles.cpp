//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ui;
#else
#include <infra/ToString.h>
#include <ui/Style/Styles.h>
#include <ui/Style/Skin.h>
#include <ui/Style/Layout.h>
#include <ui/UiWindow.h>
#include <ui/Ui.h>
#include <ui/WidgetStruct.h>
#include <ui/UiRoot.h>
#endif

namespace mud
{
	Styles::Styles()
		: widget("Widget", nullptr, [](Layout& l) { l.m_solver = Solver::Frame; })
		, wedge("Wedge", widget, [](Layout& l) { l.m_solver = Solver::Row; l.m_space = Preset::Sheet; })
		, ui("Ui", wedge, [](Layout& l) { l.m_space = Preset::Layout; l.m_clipping = Clip::Clip; l.m_opacity = Opacity::Opaque; })

		, unit("Unit", wedge, [](Layout& l) { l.m_space = Preset::Unit; l.m_align = { Align::Left, Align::Center }; },
							  [](InkStyle& o) { o.m_empty = false; o.m_text_colour = Colour::White; o.m_padding = vec4(2.f); })
		, item("Item", widget, [](Layout& l) { l.m_space = Preset::Block; l.m_align = { Align::Left, Align::Center }; },
							   [](InkStyle& o) { o.m_text_colour = Colour::White; o.m_padding = vec4(2.f); })
		, control("Control", item, [](Layout& l) { l.m_opacity = Opacity::Opaque; })
		, wrap_control("WrapControl", wedge, [](Layout& l) { l.m_space = Preset::Line; l.m_opacity = Opacity::Opaque; })

		, spacer("Spacer", item, [](Layout& l) { l.m_space = Preset::Spacer; })
		, filler("Filler", spacer, [](Layout& l) { l.m_space = Preset::Flex; })

		, drag_handle("DragHandle", control, [](Layout& l) { l.m_space = { FlowAxis::Flip, Sizing::Wrap, Sizing::Fixed }; l.m_size = vec2{ 5.f, 5.f }; })

		, div("Div", wedge, [](Layout& l) { l.m_space = Preset::Div; })
		, row("Row", wedge, [](Layout& l) { l.m_space = Preset::Line; })
		, stack("Stack", wedge, [](Layout& l) { l.m_space = Preset::Stack; })
		, sheet("Sheet", wedge, [](Layout& l) { l.m_space = Preset::Sheet; })
		, flex("Flex", wedge, [](Layout& l) { l.m_space = Preset::Flex; })
		, list("List", wedge, {})
		, header("Header", row, {})
		, board("Board", wedge, [](Layout& l) { l.m_space = Preset::Board; l.m_clipping = Clip::Clip; })
		, layout("Layout", board, [](Layout& l) { l.m_space = Preset::Layout; })
		, screen("Screen", wedge, [](Layout& l) { l.m_flow = LayoutFlow::Free; l.m_space = Preset::Layout; })
		, decal("Decal", wedge, [](Layout& l) { l.m_flow = LayoutFlow::Free; l.m_space = Preset::Block; })
		, overlay("Overlay", wedge, [](Layout& l) { l.m_flow = LayoutFlow::Free; l.m_opacity = Opacity::Opaque; })
		, gridsheet("GridSheet", wedge, [](Layout& l) { l.m_opacity = Opacity::Opaque; l.m_spacing = vec2(5.f); })

		, sequence("Sequence", wedge, [](Layout& l) { l.m_space = Preset::Sheet; })
		, element("Element", wedge, [](Layout& l) { l.m_space = Preset::Stack; l.m_opacity = Opacity::Opaque; })

		, label("Label", item, [](Layout& l) { l.m_align = { Align::Left, Align::Center }; })
		, title("Title", label, {}, [](InkStyle& o) { UNUSED(o); }) //o.m_text_size = 18.f; })
		, message("Message", label, {}, [](InkStyle& o) { UNUSED(o); }) //o.m_text_size = 18.f; })
		, text("Text", item, [](Layout& l) { l.m_space = { FlowAxis::Paragraph, Sizing::Fixed, Sizing::Wrap }; },
							 [](InkStyle& o) { o.m_text_break = true; })

		, button("Button", control, {})
		, wrap_button("WrapButton", wrap_control, {})
		, multi_button("MultiButton", wrap_button, {})
		, toggle("Toggle", control, {})
		, checkbox("Checkbox", toggle, [](Layout& l) { l.m_align = { Align::Left, Align::Center }; }) // @todo why doesn't work ?? why u checkbox not aligned ??

		, dummy("Dummy", wedge, [](Layout& l) { l.m_space = Preset::Block; })
		, tooltip("Tooltip", decal, [](Layout& l) { l.m_space = Preset::Unit; l.m_zorder = -2; })
		, rectangle("Rectangle", decal, [](Layout& l) { l.m_space = Preset::Block; l.m_zorder = -3; },
										[](InkStyle& l) { l.m_border_width = vec4(1.f); l.m_border_colour = Colour::White; l.m_background_colour = Colour::AlphaGrey; })

		, type_in("TypeIn", wrap_control, [](Layout& l) { l.m_opacity = Opacity::Opaque; })
		, text_edit("TextEdit", type_in, [](Layout& l) { l.m_space = Preset::Layout; })
		, type_zone("TypeZone", wrap_control, [](Layout& l) { l.m_space = Preset::Sheet; l.m_opacity = Opacity::Opaque; },
											  [](InkStyle& l) { l.m_text_font = "consolas"; l.m_text_break = true; })
		, caret("Caret", item, {}, [](InkStyle& l) { l.m_background_colour = Colour::White; })

		, image("Figure", item, {}, [](InkStyle& l) { l.m_empty = false; })
		, image_stretch("ImageStretch", unit, {}, [](InkStyle& l) { l.m_empty = false; l.m_stretch = { true, true }; })

		, radio_switch("RadioSwitch", wrap_control, {})
		, radio_switch_h("RadioSwitchH", radio_switch, [](Layout& l) { l.m_space = Preset::Stack; })
		, radio_choice("RadioChoice", multi_button, {})
		, radio_choice_item("RadioChoiceItem", item, {})

		, slider("Slider", wrap_control, [](Layout& l) { l.m_space = Preset::Flex; })
		, slider_knob("SliderKnob", control, {}) // [](Layout& l) { l.m_space = Preset::Flex; } }
		, slider_display("SliderDisplay", label, [](Layout& l) { l.m_flow = LayoutFlow::Overlay; l.m_align = { Align::Center, Align::Center }; })

		, fill_bar("Fillbar", row, {})

		, number_input("NumberInput", row, {})
		, slider_input("SliderInput", row, {})
		, field_input("Field", wrap_control, {})
		, curve_graph("CurveGraph", sheet, [](Layout& l) { l.m_opacity = Opacity::Opaque; }, [](InkStyle& l) { l.m_empty = false; })
		, curve_input("CurveInput", sheet, [](Layout& l) { l.m_padding = vec4(6.f); })
		, input_bool("Input<bool>", wedge, [](Layout& l) { l.m_space = Preset::Unit; })
		, input_string("Input<string>", type_in, {})
		, input_color("Input<Colour>", row, {})

		, color_wheel("ColourWheel", control, [](Layout& l) { l.m_size = { 200.f, 200.f }; }, [](InkStyle& l) { l.m_empty = false; })
		, color_slab("ColourSlab", control, [](Layout& l) { l.m_size = { 22.f, 22.f }; }, [](InkStyle& l) { l.m_empty = false; })
		, color_display("ColourDisplay", flex, {}, [](InkStyle& l) { l.m_empty = false; })
		, color_toggle("ColourToggle", color_slab, [](Layout& l) { l.m_solver = Solver::Row; }, [](InkStyle& l) { l.m_empty = false; })

		, scrollsheet("ScrollSheet", wedge, [](Layout& l) { l.m_solver = Solver::Grid; l.m_opacity = Opacity::Opaque; l.m_grid_division = { Preset::Layout, Preset::Line }; })
		, scroll_zone("ScrollZone", layout, [](Layout& l) { l.m_layout = { AutoLayout::Size, AutoLayout::Size }; l.m_clipping = Clip::Clip; })

		, scroll_surface("ScrollSurface", wedge, {})
		, scroll_plan("ScrollPlan", sheet, [](Layout& l) { l.m_space = Preset::Block; }) // { l.m_custom_draw = &draw_grid }

		, table("Table", stack, [](Layout& l) { l.m_solver = Solver::Table; l.m_spacing = vec2(0.f, 2.f); })
		, table_head("TableHead", gridsheet, [](Layout& l) { l.m_space = Preset::Div; })
		, column_header("ColumnHeader", row, [](Layout& l) { l.m_space = Preset::Line; })

		, popup("Popup", overlay, [](Layout& l) { l.m_space = Preset::Unit; l.m_clipping = Clip::Unclip; })
		, modal("Modal", popup, [](Layout& l) { l.m_flow = LayoutFlow::Align; l.m_space = Preset::Unit; l.m_align = { Align::Center, Align::Center }; })

		, color_popup("ColourPopup", overlay, [](Layout& l) { l.m_flow = LayoutFlow::Align; l.m_clipping = Clip::Unclip; l.m_align = { Align::Left, Align::OutRight }; })
	{}

	void Styles::setup(UiWindow& ui_window)
	{
		styles().scroll_plan.skin().m_custom_draw = &ui::draw_grid;

		ui::cursor_styles().cursor.skin().m_image = ui_window.find_image("mousepointer");

		ui::cursor_styles().resize_x.skin().m_image = ui_window.find_image("resize_h_20");
		ui::cursor_styles().resize_y.skin().m_image = ui_window.find_image("resize_v_20");
		ui::cursor_styles().move.skin().m_image = ui_window.find_image("move_20");
		ui::cursor_styles().resize_diag_left.skin().m_image = ui_window.find_image("resize_diag_left_20");
		ui::cursor_styles().resize_diag_right.skin().m_image = ui_window.find_image("resize_diag_right_20");
		ui::cursor_styles().caret.skin().m_image = ui_window.find_image("caret_white");

		ui::scrollbar_styles().scroll_up.skin().m_image = ui_window.find_image("arrow_up_15");
		ui::scrollbar_styles().scroll_down.skin().m_image = ui_window.find_image("arrow_down_15");
		ui::scrollbar_styles().scroll_left.skin().m_image = ui_window.find_image("arrow_left_15");
		ui::scrollbar_styles().scroll_right.skin().m_image = ui_window.find_image("arrow_right_15");

		ui::window_styles().close_button.skin().m_image = ui_window.find_image("close_15");
		ui::toolbar_styles().mover.skin().m_image = ui_window.find_image("handle");

		ui::treenode_styles().no_toggle.skin().m_image = ui_window.find_image("empty_15");

		ui::treenode_styles().toggle.skin().m_image = ui_window.find_image("toggle_closed");
		ui::treenode_styles().toggle.decline_skin(ACTIVE).m_image = ui_window.find_image("toggle_open");
		ui::treenode_styles().toggle.decline_skin(DISABLED).m_image = ui_window.find_image("empty_15");
	}
}
