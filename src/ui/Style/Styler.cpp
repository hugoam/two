//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <ui/Generated/Types.h>
#include <ui/Style/Styler.h>

#include <obj/Graph/Node.inl.h>

#include <obj/Arg.h>
#include <obj/String/StringConvert.h>
#include <ui/Style/Styles.h>
#include <ui/Style/Skin.h>
#include <ui/Style/Layout.h>
#include <ui/UiWindow.h>
#include <ui/Ui.h>
#include <ui/Structs/Widget.h>
#include <ui/Structs/RootSheet.h>

#include <ui/Generated/Convert.h>

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

		layout_defs[style.name()].apply(&style.layout());
		skin_defs[style.name()].apply(&style.skin());

		for(auto& kv : skin_defs)
			if(kv.first.find(string(style.name()) + ":") == 0)
			{
				WidgetState states = flags_from_string<WidgetState>(split_string(kv.first, ":")[1]);
				InkStyle& skin = style.decline_skin(states);
				skin_defs[style.name()].apply(&skin);
				skin_defs[kv.first].apply(&skin);
			}
	}

	Styles::Styles()
		: widget("Widget", nullptr, { { { &Layout::m_solver, FRAME_SOLVER } } })
		, wedge("Wedge", widget, { { { &Layout::m_solver, ROW_SOLVER }, { &Layout::m_space, SHEET } } })
		, root_sheet("RootSheet", wedge, { { { &Layout::m_space, LAYOUT }, { &Layout::m_clipping, CLIP }, { &Layout::m_opacity, OPAQUE } } })

		, item("Item", widget, { { { &Layout::m_space, BLOCK }, { &Layout::m_align, Dim2<Align>{ LEFT, CENTER } }, { &InkStyle::m_text_colour, Colour::White }, { &InkStyle::m_padding, vec4(2.f) } } })
		, control("Control", item, { { { &Layout::m_opacity, OPAQUE } } })

		, spacer("Spacer", item, { { { &Layout::m_space, SPACER } } })
		, filler("Filler", spacer, { { { &Layout::m_space, FLEX } } })

		, drag_handle("DragHandle", control, { { { &Layout::m_space, Space{ ORTHOGONAL, WRAP, FIXED } }, { &Layout::m_size, vec2{ 5.f, 5.f } } } })

		, div("Div", wedge, { { { &Layout::m_space, DIV } } })
		, row("Row", wedge, { { { &Layout::m_space, LINE } } })
		, stack("Stack", wedge, { { { &Layout::m_space, STACK } } })
		, sheet("Sheet", wedge, { { { &Layout::m_space, SHEET } } })
		, flex("Flex", wedge, { { { &Layout::m_space, FLEX } } })
		, list("List", wedge, {})
		, header("Header", row, {})
		, board("Board", wedge, { { { &Layout::m_space, BOARD }, { &Layout::m_clipping, CLIP } } })
		, layout("Layout", board, { { { &Layout::m_space, LAYOUT } } })
		, screen("Screen", wedge, { { { &Layout::m_flow, FREE }, { &Layout::m_space, LAYOUT } } })
		, decal("Decal", wedge, { { { &Layout::m_flow, FREE }, { &Layout::m_space, BLOCK } } })
		, overlay("Overlay", wedge, { { { &Layout::m_flow, FREE }, { &Layout::m_opacity, OPAQUE } } })
		, gridsheet("GridSheet", wedge, { { { &Layout::m_opacity, OPAQUE }, { &Layout::m_spacing, vec2(5.f) } } })

		, wrap_control("WrapControl", wedge, { { { &Layout::m_space, LINE }, { &Layout::m_opacity, OPAQUE } } })

		, label("Label", item, { { { &Layout::m_align, Dim2<Align>{ LEFT, CENTER } } } })
		, title("Title", item, {})
		, text("Text", item, { { { &Layout::m_space, Space{ PARAGRAPH, FIXED, WRAP } }, { &InkStyle::m_text_wrap, true } } })

		, button("Button", control, {})
		, wrap_button("WrapButton", wrap_control, {})
		, multi_button("MultiButton", wrap_button, {})
		, toggle("Toggle", control, {})
		, checkbox("Checkbox", toggle, { { { &Layout::m_align, Dim2<Align>{ LEFT, CENTER } } } }) // @todo why doesn't work ?? why u checkbox not aligned ??

		, dummy("Dummy", wedge, { { { &Layout::m_space, BLOCK } } })
		, tooltip("Tooltip", decal, { { { &Layout::m_space, UNIT }, { &Layout::m_zorder, -2 } } })
		, rectangle("Rectangle", decal, { { { &Layout::m_space, BLOCK }, { &Layout::m_zorder, -3 }, { &InkStyle::m_border_width, 1.f }, { &InkStyle::m_border_colour, Colour::White }, { &InkStyle::m_background_colour, Colour::AlphaGrey } } })

		, type_in("TypeIn", wrap_control, { { { &Layout::m_opacity, OPAQUE } } })
		, type_zone("TypeZone", wrap_control, { { { &Layout::m_space, SHEET }, { &Layout::m_opacity, OPAQUE } } })
		, text_edit("TextEdit", type_in, { { { &Layout::m_space, LAYOUT }, { &InkStyle::m_text_font, "consolas" }, { &InkStyle::m_text_wrap, true } } })
		, caret("Caret", item, { { { &InkStyle::m_background_colour, Colour::White } } })

		, figure("Figure", item, { { { &InkStyle::m_empty, false } } })

		, radio_switch("RadioSwitch", wrap_control, {})
		, radio_switch_h("RadioSwitchH", radio_switch, { { { &Layout::m_space, STACK } } })
		, radio_choice("RadioChoice", multi_button, {})
		, radio_choice_item("RadioChoiceItem", item, {})

		, slider("Slider", wrap_control, { { { &Layout::m_space, FLEX } } })
		, slider_knob("SliderKnob", control, { { /*{ &Layout::m_space, FLEX }*/ } })
		, slider_display("SliderDisplay", label, { { { &Layout::m_flow, OVERLAY }, { &Layout::m_align, Dim2<Align>{ CENTER, CENTER } } } })

		, fill_bar("Fillbar", row, {})

		, number_input("NumberInput", row, {})
		, slider_input("SliderInput", row, {})
		, field_input("Field", wrap_control, {})
		, input_bool("Input<bool>", wedge, { { { &Layout::m_space, UNIT } } })
		, input_string("Input<string>", type_in, {})
		, input_color("Input<Colour>", row, {})

		, color_wheel("ColourWheel", control, { { { &Layout::m_size, vec2{ 200.f, 200.f } }, { &InkStyle::m_empty, false } } })
		, color_slab("ColourSlab", control, { { { &Layout::m_size, vec2{ 22.f, 22.f } }, { &InkStyle::m_empty, false } } })
		, color_display("ColourDisplay", flex, { { { &InkStyle::m_empty, false } } })
		, color_toggle("ColourToggle", color_slab, { { { &Layout::m_solver, ROW_SOLVER }, { &InkStyle::m_empty, false } } })

		, scrollsheet("ScrollSheet", wedge, { { { &Layout::m_solver, GRID_SOLVER }, { &Layout::m_opacity, OPAQUE }, { &Layout::m_grid_division, std::vector<Space>{ LAYOUT, LINE } } } })
		, scroll_zone("ScrollZone", layout, { { { &Layout::m_layout, Dim2<AutoLayout>{ AUTO_SIZE, AUTO_SIZE } }, { &Layout::m_clipping, CLIP } } })

		, scroll_surface("ScrollSurface", wedge, {})
		, scroll_plan("ScrollPlan", sheet, { { { &Layout::m_space, BLOCK }/*, { &InkStyle::m_custom_draw, &draw_grid }*/ } })

		, table("Table", stack, { { { &Layout::m_solver, TABLE_SOLVER }, { &Layout::m_spacing, vec2(0.f, 2.f) } } })
		, table_head("TableHead", gridsheet, { { { &Layout::m_space, DIV } } })
		, column_header("ColumnHeader", row, { { { &Layout::m_space, LINE } } })

		, popup("Popup", overlay, { { { &Layout::m_space, UNIT }, { &Layout::m_clipping, UNCLIP } } })
		, modal("Modal", popup, { { { &Layout::m_flow, ALIGN }, { &Layout::m_space, UNIT }, { &Layout::m_align, Dim2<Align>{ CENTER, CENTER } } } })

		, color_popup("ColourPopup", overlay, { { { &Layout::m_flow, ALIGN }, { &Layout::m_clipping, UNCLIP }, { &Layout::m_align, Dim2<Align>{ LEFT, OUT_RIGHT } } } })
	{}

	void Styles::setup(UiWindow& ui_window)
	{
		styles().scroll_plan.skin().m_custom_draw = &ui::draw_grid;

		ui::cursor_styles().cursor.skin().m_image = &ui_window.find_image("mousepointer");

		ui::cursor_styles().resize_x.skin().m_image = &ui_window.find_image("resize_h_20");
		ui::cursor_styles().resize_y.skin().m_image = &ui_window.find_image("resize_v_20");
		ui::cursor_styles().move.skin().m_image = &ui_window.find_image("move_20");
		ui::cursor_styles().resize_diag_left.skin().m_image = &ui_window.find_image("resize_diag_left_20");
		ui::cursor_styles().resize_diag_right.skin().m_image = &ui_window.find_image("resize_diag_right_20");
		ui::cursor_styles().caret.skin().m_image = &ui_window.find_image("caret_white");

		ui::scrollbar_styles().scroll_up.skin().m_image = &ui_window.find_image("arrow_up_15");
		ui::scrollbar_styles().scroll_down.skin().m_image = &ui_window.find_image("arrow_down_15");
		ui::scrollbar_styles().scroll_left.skin().m_image = &ui_window.find_image("arrow_left_15");
		ui::scrollbar_styles().scroll_right.skin().m_image = &ui_window.find_image("arrow_right_15");

		ui::window_styles().close_button.skin().m_image = &ui_window.find_image("close_15");
		ui::toolbar_styles().mover.skin().m_image = &ui_window.find_image("handle");

		ui::treenode_styles().no_toggle.skin().m_image = &ui_window.find_image("empty_15");
	}
}
