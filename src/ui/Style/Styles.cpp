//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
module two.ui;
#else
#include <math/Vec.hpp>
#include <infra/ToString.h>
#include <ui/Style/Styles.h>
#include <ui/Style/Skin.h>
#include <ui/Style/Layout.h>
#include <ui/UiWindow.h>
#include <ui/Ui.h>
#include <ui/WidgetStruct.h>
#include <ui/UiRoot.h>
#endif

namespace two
{
	void render_bullet(const Frame& frame, const vec4& rect, Vg& vg)
	{
		static auto render_bullet = [](Vg& vg, vec2 pos, float fontsize, Colour colour)
		{
			vg.path_circle(pos, fontsize * 0.20f);
			vg.fill(Paint(colour));
		};

		const InkStyle& ink = *frame.d_inkstyle;
		render_bullet(vg, rect.pos + vec2(ink.m_text_size * 0.5f), ink.m_text_size, Colour(1.f));
	}
	
	map<string, Style*> g_styles;

	void Styles::reset()
	{
		widget = Style("Widget", nullptr, [](Layout& l) { l.m_solver = Solver::Frame; });
		wedge = Style("Wedge", widget, [](Layout& l) { l.m_solver = Solver::Row; l.m_space = Preset::Sheet; });
		ui = Style("Ui", wedge, [](Layout& l) { l.m_space = Preset::Layout; l.m_clipping = Clip::Clip; l.m_opacity = Opacity::Opaque; });

		unit = Style("Unit", wedge, [](Layout& l) { l.m_space = Preset::Unit; l.m_align = { Align::Left, Align::Center }; },
						  [](InkStyle& o) { o.m_empty = false; o.m_text_colour = Colour::White; }); // o.m_padding = vec4(2.f);
		item = Style("Item", widget, [](Layout& l) { l.m_space = Preset::Block; l.m_align = { Align::Left, Align::Center }; },
						   [](InkStyle& o) { o.m_text_colour = Colour::White; }); // o.m_padding = vec4(2.f);
		control = Style("Control", item, [](Layout& l) { l.m_opacity = Opacity::Opaque; });
		wrap_control = Style("WrapControl", wedge, [](Layout& l) { l.m_space = Preset::Line; l.m_opacity = Opacity::Opaque; });

		spacer = Style("Spacer", item, [](Layout& l) { l.m_space = Preset::Spacer; });
		filler = Style("Filler", spacer, [](Layout& l) { l.m_space = Preset::Flex; });

		separator = Style("Separator", item, [](Layout& l) { l.m_space = { FlowAxis::Flip, Sizing::Wrap, Sizing::Fixed }; l.m_size = vec2(1.f); });

		drag_handle = Style("DragHandle", control, [](Layout& l) { l.m_space = { FlowAxis::Flip, Sizing::Wrap, Sizing::Fixed }; l.m_size = vec2(5.f); });

		div = Style("Div", wedge, [](Layout& l) { l.m_space = Preset::Div; });
		row = Style("Row", wedge, [](Layout& l) { l.m_space = Preset::Line; });
		stack = Style("Stack", wedge, [](Layout& l) { l.m_space = Preset::Stack; });
		sheet = Style("Sheet", wedge, [](Layout& l) { l.m_space = Preset::Sheet; });
		flex = Style("Flex", wedge, [](Layout& l) { l.m_space = Preset::Flex; });
		list = Style("List", wedge, {});
		header = Style("Header", row, {});
		board = Style("Board", wedge, [](Layout& l) { l.m_space = Preset::Board; l.m_clipping = Clip::Clip; });
		layout = Style("Layout", board, [](Layout& l) { l.m_space = Preset::Layout; });
		indent = Style("IndentBlock", wedge, [](Layout& l) { l.m_space = Preset::Sheet; l.m_padding = vec4(12.f, 0.f, 0.f, 0.f); });
		screen = Style("Screen", wedge, [](Layout& l) { l.m_flow = LayoutFlow::Free; l.m_space = Preset::Layout; });
		decal = Style("Decal", wedge, [](Layout& l) { l.m_flow = LayoutFlow::Free; l.m_space = Preset::Block; });
		overlay = Style("Overlay", wedge, [](Layout& l) { l.m_flow = LayoutFlow::Free; l.m_opacity = Opacity::Opaque; });
		gridsheet = Style("GridSheet", wedge, [](Layout& l) { l.m_opacity = Opacity::Opaque; l.m_spacing = vec2(5.f); });

		sequence = Style("Sequence", wedge, [](Layout& l) { l.m_space = Preset::Sheet; });
		element = Style("Element", wedge, [](Layout& l) { l.m_space = Preset::Stack; l.m_opacity = Opacity::Opaque; });

		label = Style("Label", item, [](Layout& l) { l.m_align = { Align::Left, Align::Center }; });
		title = Style("Title", label, {}, [](InkStyle& o) { UNUSED(o); }); //o.m_text_size = 18.f; });
		message = Style("Message", label, {}, [](InkStyle& o) { UNUSED(o); }); //o.m_text_size = 18.f; });
		text = Style("Text", item, [](Layout& l) { l.m_space = { FlowAxis::Paragraph, Sizing::Fixed, Sizing::Wrap }; },
								   [](InkStyle& o) { o.m_text_break = true; o.m_text_wrap = true; });

		bullet = Style("Bullet", item, [](Layout& l) { l.m_size = vec2(15.f); }, [](InkStyle& o) { o.m_empty = false; o.m_custom_draw = render_bullet; });
		button = Style("Button", control, {});
		wrap_button = Style("WrapButton", wrap_control, {});
		multi_button = Style("MultiButton", wrap_button, {});
		toggle = Style("Toggle", control, {});
		checkbox = Style("Checkbox", toggle, [](Layout& l) { l.m_align = { Align::Left, Align::Center }; }); // @todo why doesn't work ?? why u checkbox not aligned ??
		checkmark = Style("Checkmark", screen, [](Layout& l) { UNUSED(l); });

		dummy = Style("Dummy", wedge, [](Layout& l) { l.m_space = Preset::Block; });
		tooltip = Style("Tooltip", decal, [](Layout& l) { l.m_space = Preset::Unit; l.m_zorder = -2; });
		rectangle = Style("Rectangle", decal, [](Layout& l) { l.m_space = Preset::Block; l.m_zorder = -3; },
											  [](InkStyle& l) { l.m_border_width = vec4(1.f); l.m_border_colour = Colour::White; l.m_background_colour = Colour::AlphaGrey; });
		
		viewport = Style("Viewport", wedge, [](Layout& l) { l.m_space = Preset::Block; l.m_opacity = Opacity::Opaque; });

		type_in = Style("TypeIn", wrap_control, [](Layout& l) { l.m_opacity = Opacity::Opaque; });
		text_edit = Style("TextEdit", type_in, [](Layout& l) { l.m_space = Preset::Layout; });
		type_zone = Style("TypeZone", wrap_control, [](Layout& l) { l.m_space = Preset::Sheet; l.m_opacity = Opacity::Opaque; },
												    [](InkStyle& l) { l.m_text_font = "consolas"; l.m_text_break = true; });
		caret = Style("Caret", item, {}, [](InkStyle& l) { l.m_background_colour = Colour::White; });

		image = Style("Figure", item, {}, [](InkStyle& l) { l.m_empty = false; });
		image_stretch = Style("ImageStretch", unit, {}, [](InkStyle& l) { l.m_empty = false; l.m_stretch = { true, true }; });

		radio_switch = Style("RadioSwitch", wrap_control, {});
		radio_switch_h = Style("RadioSwitchH", radio_switch, [](Layout& l) { l.m_space = Preset::Stack; });
		radio_choice = Style("RadioChoice", multi_button, {});
		radio_choice_item = Style("RadioChoiceItem", item, [](Layout& l) { l.m_align = { Align::Center, Align::Center }; });

		slider = Style("Slider", wrap_control, [](Layout& l) { l.m_space = Preset::Flex; });
		slider_knob = Style("SliderKnob", control, {}); // [](Layout& l) { l.m_space = Preset::Flex; } }
		slider_display = Style("SliderDisplay", label, [](Layout& l) { l.m_flow = LayoutFlow::Overlay; l.m_align = { Align::Center, Align::Center }; });

		fill_bar = Style("Fillbar", row, {});

		number_input = Style("NumberInput", row, {});
		slider_input = Style("SliderInput", row, {});
		field_input = Style("Field", wrap_control, {});
		curve_graph = Style("CurveGraph", sheet, [](Layout& l) { l.m_opacity = Opacity::Opaque; }, [](InkStyle& l) { l.m_empty = false; });
		curve_input = Style("CurveInput", sheet, [](Layout& l) { l.m_padding = vec4(6.f); });
		input_bool = Style("Input<bool>", wedge, [](Layout& l) { l.m_space = Preset::Unit; });
		input_string = Style("Input<string>", type_in, {});
		input_color = Style("Input<Colour>", row, {});

		color_wheel = Style("ColourWheel", control, [](Layout& l) { l.m_size = vec2(200.f); }, [](InkStyle& l) { l.m_empty = false; });
		color_slab = Style("ColourSlab", control, [](Layout& l) { l.m_size = vec2(22.f); }, [](InkStyle& l) { l.m_empty = false; });
		color_display = Style("ColourDisplay", flex, {}, [](InkStyle& l) { l.m_empty = false; });
		color_toggle = Style("ColourToggle", color_slab, [](Layout& l) { l.m_solver = Solver::Row; }, [](InkStyle& l) { l.m_empty = false; });

		scrollsheet = Style("ScrollSheet", wedge, [](Layout& l) { l.m_solver = Solver::Grid; l.m_opacity = Opacity::Opaque; l.m_grid_division = { Preset::Layout, Preset::Line }; });
		scroll_zone = Style("ScrollZone", layout, [](Layout& l) { l.m_layout = { AutoLayout::Size, AutoLayout::Size }; l.m_clipping = Clip::Clip; });

		scroll_surface = Style("ScrollSurface", wedge, {});
		scroll_plan = Style("ScrollPlan", sheet, [](Layout& l) { l.m_space = Preset::Block; }); // { l.m_custom_draw = &draw_grid }

		table = Style("Table", stack, [](Layout& l) { l.m_solver = Solver::Table; l.m_spacing = vec2(0.f, 2.f); });
		table_head = Style("TableHead", gridsheet, [](Layout& l) { l.m_space = Preset::Div; });
		column_header = Style("ColumnHeader", row, [](Layout& l) { l.m_space = Preset::Line; });

		popup = Style("Popup", overlay, [](Layout& l) { l.m_space = Preset::Unit; l.m_clipping = Clip::Unclip; });
		modal = Style("Modal", popup, [](Layout& l) { l.m_flow = LayoutFlow::Align; l.m_space = Preset::Unit; l.m_align = { Align::Center, Align::Center }; });

		color_popup = Style("ColourPopup", overlay, [](Layout& l) { l.m_flow = LayoutFlow::Align; l.m_clipping = Clip::Unclip; l.m_align = { Align::Left, Align::OutRight }; });
	
		register_styles({
			&widget, &wedge, &ui, &unit, &item, &control, &wrap_control, &spacer, &separator, &filler, &drag_handle,
			&div, &row, &stack, &sheet, &flex, &list, &header, &board, &layout, &indent,
			&screen, &decal, &overlay, &gridsheet, &sequence, &element,
			&label, &title, &message, &text, &bullet, &button, &wrap_button, &multi_button, &toggle, &checkbox, &checkmark,
			&dummy, &tooltip, &rectangle, &viewport, &type_in, &text_edit, &type_zone, &caret, &image, &image_stretch,
			&radio_switch, &radio_switch_h, &radio_choice, &radio_choice_item,
			&slider, &slider_knob, &slider_display, &fill_bar, &number_input,
			&slider_input, &field_input, &curve_graph, &curve_input, &input_bool, &input_string, &input_color,
			&color_wheel, &color_slab, &color_display, &color_toggle,
			&scrollsheet, &scroll_zone, &scroll_surface, &scroll_plan, &table, &table_head, &column_header,
			&popup, &modal, &color_popup
		});
	}

	void Styles::setup(UiWindow& ui_window)
	{
		styles().scroll_plan.m_skin.m_custom_draw = &ui::draw_grid;

		ui::cursor_styles().cursor.m_skin.m_image = ui_window.find_image("mousepointer");

		ui::cursor_styles().resize_x.m_skin.m_image = ui_window.find_image("resize_h_20");
		ui::cursor_styles().resize_y.m_skin.m_image = ui_window.find_image("resize_v_20");
		ui::cursor_styles().move.m_skin.m_image = ui_window.find_image("move_20");
		ui::cursor_styles().resize_diag_left.m_skin.m_image = ui_window.find_image("resize_diag_left_20");
		ui::cursor_styles().resize_diag_right.m_skin.m_image = ui_window.find_image("resize_diag_right_20");
		ui::cursor_styles().caret.m_skin.m_image = ui_window.find_image("caret_white");
	}
}
