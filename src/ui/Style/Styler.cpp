//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ui;
#else
#include <tree/Node.inl.h>
#include <refl/Class.h>
#include <infra/StringConvert.h>
#include <ui/Style/Styler.h>
#include <ui/Style/Styles.h>
#include <ui/Style/Skin.h>
#include <ui/Style/Layout.h>
#include <ui/UiWindow.h>
#include <ui/Ui.h>
#include <ui/Structs/Widget.h>
#include <ui/Structs/RootSheet.h>
#include <meta/ui/Convert.h>
#endif

namespace mud
{
	void Options::set(size_t index, const Var& value)
	{
		if(index >= m_fields.size())
			m_fields.resize(index + 1);
		m_fields[index] = value;
	}

	void Options::merge(const Options& other)
	{
		for(size_t i = 0; i < other.m_fields.size(); ++i)
			if(!other.m_fields[i].none())
				set(i, other.m_fields[i]);
	}

	void Options::apply(Ref object)
	{
		for(size_t i = 0; i < m_fields.size(); ++i)
			if(!m_fields[i].none())
				cls(object).m_members[i].set(object, m_fields[i]);
	}

	std::map<string, Style*> Styler::s_styles;

	Styler::Styler(UiWindow& ui_window)
		: m_uiWindow(ui_window)
	{
		styles();

		ui::cursor_styles();
		ui::scrollbar_styles();
		ui::dropdown_styles();
		ui::table_styles();
		ui::expandbox_styles();
		ui::treenode_styles();
		ui::tabber_styles();
		ui::menu_styles();
		ui::toolbar_styles();
		ui::window_styles();
		ui::dock_styles();
		ui::canvas_styles();
		ui::node_styles();
		ui::file_styles();
	}

	void Styler::init()
	{
		styles() = Styles();

		ui::cursor_styles() = ui::CursorStyles();
		ui::scrollbar_styles() = ui::ScrollbarStyles();
		ui::dropdown_styles() = ui::DropdownStyles();
		ui::table_styles() = ui::TableStyles();
		ui::expandbox_styles() = ui::ExpandboxStyles();
		ui::treenode_styles() = ui::TreeNodeStyles();
		ui::tabber_styles() = ui::TabberStyles();
		ui::menu_styles() = ui::MenuStyles();
		ui::toolbar_styles() = ui::ToolbarStyles();
		ui::window_styles() = ui::WindowStyles();
		ui::dock_styles() = ui::DockStyles();
		ui::canvas_styles() = ui::CanvasStyles();
		ui::node_styles() = ui::NodeStyles();
		ui::file_styles() = ui::FileStyles();
	}

	void Styler::clear()
	{
		m_layout_definitions = {};
		m_skin_definitions = {};

		this->init();

		styles().setup(m_uiWindow);
	}

	void Styler::setup()
	{
		for(auto& kv : s_styles)
			this->load(*kv.second, m_layout_definitions, m_skin_definitions);

		visit_node<Widget>(*m_uiWindow.m_root_sheet, [](Widget& widget, bool&) {
			widget.m_frame.update_style(true);
		});
	}

	void Styler::load(Style& style, StyleMap& layout_defs, StyleMap& skin_defs)
	{
		if(style.m_defined) return;

		if(style.m_base)
			this->load(*style.m_base, layout_defs, skin_defs);

		this->define(style, layout_defs, skin_defs);
		style.prepare();

		style.m_defined = true;
	}

	void Styler::define(Style& style, StyleMap& layout_defs, StyleMap& skin_defs)
	{
		//if(style.m_base)
		//	this->load(*style.m_base, layout_defs, skin_defs);

		layout_defs[style.name()].apply(Ref(&style.layout()));
		skin_defs[style.name()].apply(Ref(&style.skin()));

		for(auto& kv : skin_defs)
			if(kv.first.find(string(style.name()) + ":") == 0)
			{
				WidgetState states = flags_from_string<WidgetState>(split_string(kv.first, ":")[1]);
				InkStyle& skin = style.decline_skin(states);
				skin_defs[style.name()].apply(Ref(&skin));
				skin_defs[kv.first].apply(Ref(&skin));
			}
	}

	Styles::Styles()
		: widget("Widget", nullptr, [](Layout& l) { l.m_solver = FRAME_SOLVER; })
		, wedge("Wedge", widget, [](Layout& l) { l.m_solver = ROW_SOLVER; l.m_space = SHEET; })
		, ui("Ui", wedge, [](Layout& l) { l.m_space = LAYOUT; l.m_clipping = CLIP; l.m_opacity = OPAQUE; })

		, unit("Unit", wedge, [](Layout& l) { l.m_space = UNIT; l.m_align = { LEFT, CENTER }; },
							  [](InkStyle& o) { o.m_empty = false; o.m_text_colour = Colour::White; o.m_padding = vec4(2.f); })
		, item("Item", widget, [](Layout& l) { l.m_space = BLOCK; l.m_align = { LEFT, CENTER }; },
							   [](InkStyle& o) { o.m_text_colour = Colour::White; o.m_padding = vec4(2.f); })
		, control("Control", item, [](Layout& l) { l.m_opacity = OPAQUE; })
		, wrap_control("WrapControl", wedge, [](Layout& l) { l.m_space = LINE; l.m_opacity = OPAQUE; })

		, spacer("Spacer", item, [](Layout& l) { l.m_space = SPACER; })
		, filler("Filler", spacer, [](Layout& l) { l.m_space = FLEX; })

		, drag_handle("DragHandle", control, [](Layout& l) { l.m_space = { ORTHOGONAL, WRAP, FIXED }; l.m_size = vec2{ 5.f, 5.f }; })

		, div("Div", wedge, [](Layout& l) { l.m_space = DIV; })
		, row("Row", wedge, [](Layout& l) { l.m_space = LINE; })
		, stack("Stack", wedge, [](Layout& l) { l.m_space = STACK; })
		, sheet("Sheet", wedge, [](Layout& l) { l.m_space = SHEET; })
		, flex("Flex", wedge, [](Layout& l) { l.m_space = FLEX; })
		, list("List", wedge, {})
		, header("Header", row, {})
		, board("Board", wedge, [](Layout& l) { l.m_space = BOARD; l.m_clipping = CLIP; })
		, layout("Layout", board, [](Layout& l) { l.m_space = LAYOUT; })
		, screen("Screen", wedge, [](Layout& l) { l.m_flow = FREE; l.m_space = LAYOUT; })
		, decal("Decal", wedge, [](Layout& l) { l.m_flow = FREE; l.m_space = BLOCK; })
		, overlay("Overlay", wedge, [](Layout& l) { l.m_flow = FREE; l.m_opacity = OPAQUE; })
		, gridsheet("GridSheet", wedge, [](Layout& l) { l.m_opacity = OPAQUE; l.m_spacing = vec2(5.f); })

		, sequence("Sequence", wedge, [](Layout& l) { l.m_space = SHEET; })
		, element("Element", wedge, [](Layout& l) { l.m_space = STACK; l.m_opacity = OPAQUE; })

		, label("Label", item, [](Layout& l) { l.m_align = { LEFT, CENTER }; })
		, title("Title", label, {}, [](InkStyle& o) {}) //o.m_text_size = 18.f; })
		, message("Message", label, {}, [](InkStyle& o) {}) //o.m_text_size = 18.f; })
		, text("Text", item, [](Layout& l) { l.m_space = { PARAGRAPH, FIXED, WRAP }; },
							 [](InkStyle& o) { o.m_text_break = true; })

		, button("Button", control, {})
		, wrap_button("WrapButton", wrap_control, {})
		, multi_button("MultiButton", wrap_button, {})
		, toggle("Toggle", control, {})
		, checkbox("Checkbox", toggle, [](Layout& l) { l.m_align = { LEFT, CENTER }; }) // @todo why doesn't work ?? why u checkbox not aligned ??

		, dummy("Dummy", wedge, [](Layout& l) { l.m_space = BLOCK; })
		, tooltip("Tooltip", decal, [](Layout& l) { l.m_space = UNIT; l.m_zorder = -2; })
		, rectangle("Rectangle", decal, [](Layout& l) { l.m_space = BLOCK; l.m_zorder = -3; },
										[](InkStyle& l) { l.m_border_width = vec4(1.f); l.m_border_colour = Colour::White; l.m_background_colour = Colour::AlphaGrey; })

		, type_in("TypeIn", wrap_control, [](Layout& l) { l.m_opacity = OPAQUE; })
		, text_edit("TextEdit", type_in, [](Layout& l) { l.m_space = LAYOUT; })
		, type_zone("TypeZone", wrap_control, [](Layout& l) { l.m_space = SHEET; l.m_opacity = OPAQUE; },
											  [](InkStyle& l) { l.m_text_font = "consolas"; l.m_text_break = true; })
		, caret("Caret", item, {}, [](InkStyle& l) { l.m_background_colour = Colour::White; })

		, image("Figure", item, {}, [](InkStyle& l) { l.m_empty = false; })
		, image_stretch("ImageStretch", unit, {}, [](InkStyle& l) { l.m_empty = false; l.m_stretch = { true, true }; })

		, radio_switch("RadioSwitch", wrap_control, {})
		, radio_switch_h("RadioSwitchH", radio_switch, [](Layout& l) { l.m_space = STACK; })
		, radio_choice("RadioChoice", multi_button, {})
		, radio_choice_item("RadioChoiceItem", item, {})

		, slider("Slider", wrap_control, [](Layout& l) { l.m_space = FLEX; })
		, slider_knob("SliderKnob", control, {}) // [](Layout& l) { l.m_space = FLEX; } }
		, slider_display("SliderDisplay", label, [](Layout& l) { l.m_flow = OVERLAY; l.m_align = { CENTER, CENTER }; })

		, fill_bar("Fillbar", row, {})

		, number_input("NumberInput", row, {})
		, slider_input("SliderInput", row, {})
		, field_input("Field", wrap_control, {})
		, curve_graph("CurveGraph", sheet, [](Layout& l) { l.m_opacity = OPAQUE; }, [](InkStyle& l) { l.m_empty = false; })
		, curve_input("CurveInput", sheet, [](Layout& l) { l.m_padding = vec4(6.f); })
		, input_bool("Input<bool>", wedge, [](Layout& l) { l.m_space = UNIT; })
		, input_string("Input<string>", type_in, {})
		, input_color("Input<Colour>", row, {})

		, color_wheel("ColourWheel", control, [](Layout& l) { l.m_size = { 200.f, 200.f }; }, [](InkStyle& l) { l.m_empty = false; })
		, color_slab("ColourSlab", control, [](Layout& l) { l.m_size = { 22.f, 22.f }; }, [](InkStyle& l) { l.m_empty = false; })
		, color_display("ColourDisplay", flex, {}, [](InkStyle& l) { l.m_empty = false; })
		, color_toggle("ColourToggle", color_slab, [](Layout& l) { l.m_solver = ROW_SOLVER; }, [](InkStyle& l) { l.m_empty = false; })

		, scrollsheet("ScrollSheet", wedge, [](Layout& l) { l.m_solver = GRID_SOLVER; l.m_opacity = OPAQUE; l.m_grid_division = { LAYOUT, LINE }; })
		, scroll_zone("ScrollZone", layout, [](Layout& l) { l.m_layout = { AUTO_SIZE, AUTO_SIZE }; l.m_clipping = CLIP; })

		, scroll_surface("ScrollSurface", wedge, {})
		, scroll_plan("ScrollPlan", sheet, [](Layout& l) { l.m_space = BLOCK; }) // { l.m_custom_draw = &draw_grid }

		, table("Table", stack, [](Layout& l) { l.m_solver = TABLE_SOLVER; l.m_spacing = vec2(0.f, 2.f); })
		, table_head("TableHead", gridsheet, [](Layout& l) { l.m_space = DIV; })
		, column_header("ColumnHeader", row, [](Layout& l) { l.m_space = LINE; })

		, popup("Popup", overlay, [](Layout& l) { l.m_space = UNIT; l.m_clipping = UNCLIP; })
		, modal("Modal", popup, [](Layout& l) { l.m_flow = ALIGN; l.m_space = UNIT; l.m_align = { CENTER, CENTER }; })

		, color_popup("ColourPopup", overlay, [](Layout& l) { l.m_flow = ALIGN; l.m_clipping = UNCLIP; l.m_align = { LEFT, OUT_RIGHT }; })
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
	}
}
