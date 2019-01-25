#include <mud/ui.h>
#include <mud/tree.h>
#include <mud/math.h>
#include <mud/ctx.h>
#include <mud/infra.h>
#include <mud/type.h>

#ifndef MUD_CPP_20
#include <cstring>
#endif

#ifdef MUD_MODULES
module mud.ui;
#else
#endif

namespace mud
{
namespace ui
{
	Widget& spacer(Widget& parent)
	{
		return widget(parent, styles().spacer);
	}

	Widget& icon(Widget& parent, cstring icon) { return item(parent, styles().item, icon); }
	Widget& label(Widget& parent, cstring label) { return item(parent, styles().label, label); }
	Widget& title(Widget& parent, cstring label) { return item(parent, styles().title, label); }
	Widget& message(Widget& parent, cstring label) { return item(parent, styles().message, label); }
	Widget& text(Widget& parent, cstring label) { return item(parent, styles().text, label); }

	Widget& icon(Widget& parent, const string& icon) { return item(parent, styles().item, icon); }
	Widget& label(Widget& parent, const string& label) { return item(parent, styles().label, label); }
	Widget& title(Widget& parent, const string& label) { return item(parent, styles().title, label); }
	Widget& message(Widget& parent, const string& label) { return item(parent, styles().message, label); }
	Widget& text(Widget& parent, const string& label) { return item(parent, styles().text, label); }

	void button_logic(Widget& self)
	{
		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseLeft, EventType::Pressed))
			self.enable_state(PRESSED);
		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseLeft, EventType::Released))
			self.disable_state(PRESSED);

		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
		{
			self.enable_state(ACTIVATED);
			mouse_event.consume(self);
		}
		else
			self.disable_state(ACTIVATED);
	}

	void toggle_logic(Widget& self, bool& on)
	{
		button_logic(self);
		if(self.activated()) on = !on;
		self.set_state(ACTIVE, on);
	}

	Widget& button(Widget& parent, Style& style, cstring content)
	{
		Widget& self = item(parent, style, content);
		button_logic(self);
		return self;
	}

	Widget& multi_button(Widget& parent, Style& style, array<cstring> elements, Style* element_style)
	{
		Widget& self = multi_item(parent, style, elements, element_style);
		button_logic(self);
		return self;
	}

	Widget& toggle(Widget& parent, Style& style, bool& on, cstring content)
	{
		Widget& self = item(parent, style, content);
		toggle_logic(self, on);
		return self;
	}

	Widget& multi_toggle(Widget& parent, Style& style, bool& on, array<cstring> elements, Style* element_style)
	{
		Widget& self = multi_item(parent, style, elements, element_style);
		toggle_logic(self, on);
		return self;
	}

	Widget& button(Widget& parent, cstring content) { return button(parent, styles().button, content); }
	Widget& toggle(Widget& parent, bool& on, cstring content) { return toggle(parent, styles().toggle, on, content); }

	Widget& button(Widget& parent, const string& content) { return button(parent, styles().button, content.c_str()); }
	Widget& toggle(Widget& parent, bool& on, const string& content) { return toggle(parent, styles().toggle, on, content.c_str()); }

	Widget& multi_button(Widget& parent, array<cstring> elements, Style* element_style)
{
		return multi_button(parent, styles().multi_button, elements, element_style);
	}

	Widget& multi_toggle(Widget& parent, bool& on, array<cstring> elements, Style* element_style)
	{
		return multi_toggle(parent, styles().multi_button, on, elements, element_style);
	}

	bool modal_button(Widget& screen, Widget& parent, cstring content, uint32_t mode)
	{
		if(button(parent, content).activated())
			screen.m_switch |= mode;
		return (screen.m_switch & mode) != 0;
	}

	bool modal_multi_button(Widget& screen, Widget& parent, array<cstring> elements, uint32_t mode)
	{
		if(multi_button(parent, elements).activated())
			screen.m_switch |= mode;
		return (screen.m_switch & mode) != 0;
	}

	Widget& checkbox(Widget& parent, bool& on)
	{
		return toggle(parent, styles().checkbox, on);
	}

	Widget& fill_bar(Widget& parent, float percentage, Dim dim)
	{
		Widget& self = widget(parent, styles().fill_bar);
		spanner(self, styles().filler, dim, percentage);
		spanner(self, styles().spacer, dim, 1.f - percentage);
		item(self, styles().slider_display, to_string(percentage) + "%");
		return self;
	}

	Widget& image256(Widget& parent, Style& style, cstring name, const Image256& source)
	{
		Widget& self = widget(parent, style);
		Image* image = self.ui_window().find_image(name);
		if(!image)
		{
			vector<uint8_t> data = source.read();
			image = &self.ui_window().create_image(name, uvec2{ source.m_width, source.m_height }, &data[0], false);
		}
		self.m_frame.set_icon(image);
		return self;
	}

	Widget& image256(Widget& parent, cstring name, const Image256& source)
	{
		return image256(parent, styles().image, name, source);
	}

	Widget& image256(Widget& parent, cstring name, const Image256& source, const vec2& size)
	{
		Widget& self = image256(parent, styles().image_stretch, name, source);
		//self.m_frame.set_size(size);
		ui::dummy(self, size);
		return self;
	}

	Widget& image256(Widget& parent, const string& name, const Image256& source) { return image256(parent, name.c_str(), source); }
	Widget& image256(Widget& parent, const string& name, const Image256& source, const vec2& size) { return image256(parent, name.c_str(), source, size); }

	Widget& radio_choice(Widget& parent, cstring value, bool active)
	{
		Widget& self = multi_button(parent, styles().radio_choice, carray<cstring, 1>{ value }, &styles().radio_choice_item);
		self.set_state(ACTIVE, active);
		return self;
	}

	bool radio_switch(Widget& parent, array<cstring> labels, uint32_t& value, Dim dim)
	{
		Widget& self = widget(parent, styles().radio_switch, false, dim);
		bool changed = false;
		for(uint32_t index = 0; index < uint32_t(labels.size()); ++index)
		{
			if(radio_choice(self, labels[index], value == index).activated())
			{
				changed = true;
				value = index;
			}
		}
		return changed;
	}

	Widget& dropdown(Widget& parent, Style& style, cstring value, PopupFlags popup_flags, Style* list_style)
	{ 
		Widget& self = widget(parent, style);
		Widget& header = multi_toggle(self, dropdown_styles().head, self.m_open, carray<cstring, 1>{ value });
		Widget& button = toggle(self, dropdown_styles().toggle, self.m_open);

		self.set_state(HOVERED, header.hovered() || button.hovered());
		self.m_body = nullptr;

		if(self.m_open)
		{
			self.m_body = &popup(self, list_style ? *list_style : dropdown_styles().list, popup_flags);
			self.m_open &= self.m_body->m_open;
		}

		return self;
	}

	Widget& dropdown_choice(Widget& parent, array<cstring> elements, bool active)
	{
		Widget& self = multi_button(parent, dropdown_styles().choice, elements);
		self.set_state(ACTIVE, active);
		return self;
	}

	bool popdown(Widget& parent, array<cstring> choices, uint32_t& value, vec2 position, PopupFlags popup_flags)
	{
		Widget& self = popup_at(parent, dropdown_styles().popdown, position, popup_flags);
		ScrollSheet& sheet = scroll_sheet(self);

		for(uint32_t i = 0; i < uint32_t(choices.size()); ++i)
			if(dropdown_choice(*sheet.m_body, carray<cstring, 1>{ choices[i] }, i == value).activated())
			{
				value = i;
				return true;
			}
		return false;
	}

	bool dropdown_input(Widget& parent, array<cstring> choices, uint32_t& value, bool compact)
	{
		if(value >= choices.size())
			value = uint32_t(choices.size()) - 1;
		Style& style = compact ? dropdown_styles().dropdown_input_compact : dropdown_styles().dropdown_input;
		Widget& self = dropdown(parent, style, value == UINT32_MAX ? "" : choices[value], PopupFlags::AutoModal);
		if(!self.m_body) return false;

		for(uint32_t i = 0; i < uint32_t(choices.size()); ++i)
			if(dropdown_choice(*self.m_body, carray<cstring, 1>{ choices[i] }, value == i).activated())
			{
				value = i;
				self.m_open = false;
				return true;
			}

		return false;
	}

	bool typedown_input(Widget& parent, array<cstring> choices, uint32_t& value)
	{
		bool changed = dropdown_input(parent, choices, value); //dropdown_styles().typedown_input
		//if(scope->m_state & ACTIVATED)
		//	filter_input(self);
		return changed;
	}

	Widget& menu_choice(Widget& parent, array<cstring> elements)
	{
		Widget& self = multi_button(parent, elements); //, menu_styles().choice
		if(self.activated())
			self.m_parent->m_parent->m_open = false;
		return self;
	}

	Widget& menu_choice(Widget& parent, cstring content)
	{
		return menu_choice(parent, carray<cstring, 1>{ content });
	}

	Widget& menu(Widget& parent, cstring label, bool submenu)
	{
		Style& list_style = submenu ? menu_styles().sublist : menu_styles().list;
		return dropdown(parent, menu_styles().menu, label, PopupFlags::Modal, &list_style);
	}

	Widget& menubar(Widget& parent)
	{
		return widget(parent, menu_styles().menubar);
	}

	Widget& toolbutton(Widget& parent, cstring icon)
	{
		return button(parent, icon);
		//string value;
		//return dropdown_input(parent, styles().tool_button, {}, value);
	}

	Widget& tooldock(Widget& parent)
	{
		return widget(parent, toolbar_styles().tooldock);//, GRID)
	}

	Widget& toolbar(Widget& parent, bool wrap)
	{
		Widget& self = widget(parent, wrap ? toolbar_styles().toolbar_wrap : toolbar_styles().toolbar);
		widget(self, toolbar_styles().mover);
		return self;
	}
}
}


#ifdef MUD_MODULES
module mud.ui;
#else
#endif

namespace mud
{
namespace ui
{
	CursorStyles::CursorStyles()
		: cursor("Cursor", styles().decal, [](Layout& l) { l.m_zorder = -1; }, {})
		, resize_x("CursorResizeX", cursor, {}, [](InkStyle& s) { s.m_padding = { vec2(-10.f), vec2(10.f) }; })
		, resize_y("CursorResizeY", cursor, {}, [](InkStyle& s) { s.m_padding = { vec2(-10.f), vec2(10.f) }; })
		, move("CursorMove", cursor, {}, [](InkStyle& s) { s.m_padding = { vec2(-10.f), vec2(10.f) }; })
		, resize_diag_left("CursorResizeDiagLeft", cursor, {}, [](InkStyle& s) { s.m_padding = { vec2(-10.f), vec2(10.f) }; })
		, resize_diag_right("CursorResizeDiagRight", cursor, {}, [](InkStyle& s) { s.m_padding = { vec2(-10.f), vec2(10.f) }; })
		, caret("CursorCaret", cursor, {}, [](InkStyle& s) { s.m_padding = { -4.f, -9.f, +4.f, +9.f }; })
	{}

	CursorStyles& cursor_styles() { static CursorStyles styles; return styles; }

	ScrollbarStyles::ScrollbarStyles()
		: scrollbar("Scrollbar", styles().row, {})
		, scroll_up("ScrollUp", styles().button, {})
		, scroll_down("ScrollDown", styles().button, {})
		, scroll_left("ScrollLeft", styles().button, {})
		, scroll_right("ScrollRight", styles().button, {})
		, scroller("Scroller", styles().slider, [](Layout& l) { l.m_space = FLEX; })
		, scroller_knob("ScrollerKnob", styles().slider_knob, [](Layout& l) { l.m_space = FLEX; })
	{}

	DropdownStyles::DropdownStyles()
		: popdown("Popdown", styles().popup, [](Layout& l) { l.m_flow = FREE; l.m_space = BLOCK; l.m_size = { 200.f, 200.f }; })
		, dropdown("Dropdown", styles().wrap_button, {})
		, toggle("DropdownToggle", styles().button, {})
		, head("DropdownHead", styles().multi_button, {})
		, list("DropdownList", styles().overlay, [](Layout& l) { l.m_flow = ALIGN; l.m_clipping = UNCLIP; l.m_align = { Left, OUT_RIGHT }; })
		, choice("DropdownChoice", styles().multi_button, {})
		, dropdown_input("DropdownInput", dropdown, {})
		, dropdown_input_compact("DropdownInputCompact", dropdown, [](Layout& l) { l.m_space = ITEM; })
		, typedown_input("TypedownInput", dropdown, {})
	{}

	MenuStyles::MenuStyles()
		: menubar("Menubar", styles().header, {})
		, menu("Menu", dropdown_styles().dropdown, [](Layout& l) { l.m_space = ITEM; })
		, list("MenuList", dropdown_styles().list, [](Layout& l) { l.m_align = { Left, OUT_RIGHT }; })
		, sublist("SubMenuList", list, [](Layout& l) { l.m_align = { OUT_RIGHT, Left }; })
	{}

	ToolbarStyles::ToolbarStyles()
		: toolbutton("ToolButton", dropdown_styles().dropdown_input, {})
		, tooldock("Tooldock", styles().div, {})
		, toolbar("Toolbar", styles().wrap_control, {})
		, toolbar_wrap("ToolbarWrap", toolbar, [](Layout& l) { l.m_space = ITEM; })
		, mover("ToolbarMover", styles().control, {})
	{}

	ScrollbarStyles& scrollbar_styles() { static ScrollbarStyles styles; return styles; }
	DropdownStyles& dropdown_styles() { static DropdownStyles styles; return styles; }
	MenuStyles& menu_styles() { static MenuStyles styles; return styles; }
	ToolbarStyles& toolbar_styles() { static ToolbarStyles styles; return styles; }
}
}


#ifdef MUD_MODULES
module mud.ui;
#else
#endif

namespace mud
{
	Table::Table(Widget* parent, void* identity, array<float> weights)
		: Widget(parent, identity)
		, m_weights(to_vector(weights))
	{}

	Table::Table(Widget* parent, void* identity, size_t columns)
		: Widget(parent, identity)
		, m_weights(columns, 1.f)
	{}

namespace ui
{
	ScrollSheet& select_list(Widget& parent)
	{
		return scroll_sheet(parent, styles().list);
	}

	Table& columns(Widget& parent, array<float> weights)
	{
		Table& self = parent.suba<Table, array<float>>(weights);
		self.init(styles().table);

		as<TableSolver>(*self.m_frame.m_solver).update(self.m_weights);

		return self;
	}
	
	Table& table(Widget& parent, size_t columns, array<float> weights)
	{
		if(weights.size() > 0)
			return parent.suba<Table, array<float>>(weights);
		else
			return parent.suba<Table, size_t>(columns);
	}

	Table& table(Widget& parent, array<cstring> columns, array<float> weights)
	{
		Table& self = table(parent, columns.size(), weights);
		self.init(styles().table);

		Widget& header = grid_sheet(self, styles().table_head, DIM_X, self.m_weights); // [this](Frame& first, Frame& second) { this->resize(first, second); }

		as<TableSolver>(*self.m_frame.m_solver).update(self.m_weights);

		for(size_t i = 0; i < columns.size(); ++i)
		{
			Widget& column = spanner(header, styles().column_header, DIM_X, self.m_weights[i]);
			label(column, columns[i]);
		}

		return self;
	}

	Widget& table_row(Widget& parent)
	{
		bool odd = parent.m_next % 2 == 1;
		return button(parent, odd ? table_styles().row_odd : table_styles().row_even);
	}

	Widget& table_separator(Widget& parent)
	{
		return widget(parent, table_styles().separator);
	}

	Widget& toggle_header(Widget& parent, Style& header_style, Style& toggle_style, array<cstring> elements, bool& open)
	{
		Widget& self = button(parent, header_style);
		Widget& button = toggle(self, toggle_style, open);
		multi_item(self, styles().row, elements);
		self.set_state(HOVERED, self.hovered() || button.hovered());
		return self;
	}

	Expandbox& expandbox(Widget& parent, array<cstring> elements, bool open)
	{
		Expandbox& self = twidget<Expandbox>(parent, expandbox_styles().expandbox, open);
		self.m_header = &toggle_header(self, expandbox_styles().header, expandbox_styles().toggle, elements, self.m_open);
		self.m_body = nullptr;
		if(self.m_open)
			self.m_body = &widget(self, expandbox_styles().body);
		return self;
	}

	Expandbox& expandbox(Widget& parent, cstring name, bool open)
	{
		return expandbox(parent, { &name, 1 }, open);
	}

	TreeNode& tree_node(Widget& parent, array<cstring> elements, bool leaf, bool open)
	{
		TreeNode& self = twidget<TreeNode>(parent, treenode_styles().treenode, open);
		self.m_header = &toggle_header(self, treenode_styles().header, leaf ? treenode_styles().no_toggle : treenode_styles().toggle, elements, self.m_open);
		self.m_body = nullptr;
		if(!leaf && self.m_open)
			self.m_body = &widget(self, treenode_styles().body);
		return self;
	}

	TreeNode& tree_node(Widget& parent, cstring element, bool leaf, bool open)
	{
		return tree_node(parent, { &element, 1 }, leaf, open);
	}

	Widget& tree(Widget& parent)
	{
		return sheet(parent);// , styles().tree);
	}

	Widget& tab_header(Widget& parent, cstring name)
	{
		return button(parent, tabber_styles().tab_button, name);
	}

	Widget& tab_body(Widget& parent, size_t index)
	{
		return widget(parent, tabber_styles().tab, (void*) index);
	}

	Widget* tab(Tabber& tabber, cstring name)
	{
		size_t index = tabber.m_index++;
		Widget& header = tab_header(*tabber.m_head, name);
		if(header.activated())
			tabber.m_active = index;
		header.set_state(ACTIVE, tabber.m_active == index);
		if(index == tabber.m_active)
			return &tab_body(*tabber.m_body, index);
		return nullptr;
	}

	Tabber& tabber(Widget& parent)
	{
		Tabber& self = twidget<Tabber>(parent, tabber_styles().tabber);
		self.m_head = &widget(self, tabber_styles().head);
		self.m_body = &widget(self, tabber_styles().body);
		self.m_index = 0;
		return self;
	}
}
}


#ifdef MUD_MODULES
module mud.ui;
#else
#endif

namespace mud
{
namespace ui
{
	TableStyles::TableStyles()
		: row("TableRow", styles().wrap_button, {})
		, row_odd("TableRowOdd", row, {}, [](InkStyle& l) { l.m_empty = false; l.m_background_colour = Colour{ 0.1f, 0.1f, 0.1f }; })
		, row_even("TableRowEven", row, {}, [](InkStyle& l) { l.m_empty = false; l.m_background_colour = Colour::Black; })
		, separator("TableSeparator", styles().row, [](Layout& l) { l.m_no_grid = true; })
	{}

	ExpandboxStyles::ExpandboxStyles()
		: expandbox("Expandbox", styles().stack, {})
		, header("ExpandboxHeader", styles().wrap_button, {})
		, toggle("ExpandboxToggle", styles().toggle, {})
		, body("ExpandboxBody", styles().stack, [](Layout& l) { l.m_padding = { 12.f, 2.f, 0.f, 2.f }; l.m_spacing = vec2(6.f); })
	{}

	TreeNodeStyles::TreeNodeStyles()
		: treenode("TreeNode", expandbox_styles().expandbox, {})
		, header("TreeNodeHeader", expandbox_styles().header, {})
		, toggle("TreeNodeToggle", expandbox_styles().toggle, {})
		, no_toggle("TreeNodeNoToggle", toggle, {})
		, body("TreeNodeBody", expandbox_styles().body, [](Layout& l) { l.m_padding = { 18.f, 0.f, 0.f, 0.f }; l.m_spacing = vec2(0.f); })
	{}

	TabberStyles::TabberStyles()
		: tab("Tab", styles().wedge, [](Layout& l) { l.m_clipping = CLIP; })
		, tab_button("TabHeader", styles().button, {})
		, tabber("Tabber", styles().wedge, {})
		, head("TabberHead", styles().row, {})
		, body("TabberBody", styles().sheet, {})
	{}

	FileStyles::FileStyles()
		: dir("Dir", styles().multi_button, {})
		, file("File", styles().multi_button, {})
	{}

	TableStyles& table_styles() { static TableStyles styles; return styles; }
	ExpandboxStyles& expandbox_styles() { static ExpandboxStyles styles; return styles; }
	TreeNodeStyles& treenode_styles() { static TreeNodeStyles styles; return styles; }
	TabberStyles& tabber_styles() { static TabberStyles styles; return styles; }
	FileStyles& file_styles() { static FileStyles styles; return styles; }
}
}


#ifdef MUD_MODULES
module mud.ui;
#else
#endif

namespace mud
{
namespace ui
{
	Widget* hoverbox(Widget& parent, const vec2& position, float delay)
	{
		Ui& ui = parent.ui();

		if(&parent == ui.m_hovered && ui.m_tooltip_clock.read() > delay)
		{
			Widget& self = widget(ui, styles().tooltip).layer();
			self.m_frame.set_position(parent.m_frame.absolute_position() + position);
			return &self;
		}

		return nullptr;
	}

	Widget* hoverbox(Widget& parent, float delay)
	{
		return hoverbox(parent, parent.ui().m_mouse.m_pos + vec2(4.f) - parent.m_frame.absolute_position(), delay);
	}

	Widget* tooltip(Widget& parent, const vec2& position, array<cstring> elements)
	{
		Widget* self = hoverbox(parent, position);
		if(self)
			multi_item(parent, styles().tooltip, elements).layer();
		return self;
	}

	Widget* tooltip(Widget& parent, const vec2& position, cstring content)
	{
		return tooltip(parent, position, { &content, 1 });
	}

	Widget* tooltip(Widget& parent, const Frame& parent_frame)
	{
		return hoverbox(parent, vec2{ 0.f, 0.f + parent_frame.m_size.y });
	}

	Widget* tooltip(Widget& parent, const Frame& parent_frame, array<cstring> elements)
	{
		return tooltip(parent, vec2{ parent_frame.m_position.x, parent_frame.m_position.y + parent_frame.m_size.y }, elements);
	}

	Widget* tooltip(Widget& parent, const Frame& parent_frame, cstring element)
	{
		return tooltip(parent, parent_frame, { &element, 1 });
	}

	Widget& rectangle(Widget& parent, const vec4& rect)
	{
		Widget& self = widget(parent, styles().rectangle).layer();
		self.m_frame.set_position(rect_offset(rect));
		self.m_frame.set_size(rect_size(rect));
		return self;
	}

	Widget& cursor(Widget& parent, const vec2& position, Style& style, bool locked)
	{
		UNUSED(locked);
		Widget& self = widget(parent, style).layer();
		self.m_frame.m_position = position;
		return self;
	}

	Widget& cursor(Widget& parent, const vec2& position, Widget& hovered, bool locked)
	{
		Style* style = hovered.m_frame.d_style->skin().m_hover_cursor ? hovered.m_frame.d_style->skin().m_hover_cursor : &cursor_styles().cursor;
		return cursor(parent, position, *style, locked);
	}
}
}


#ifdef MUD_MODULES
module mud.ui;
#else
#include <stl/string.h>
#include <stl/map.h>
#endif

namespace mud
{
namespace ui
{
	Widget& dockline(Widget& parent, uint16_t index, Dim dim)
	{
		if(parent.m_nodes.size() > index && parent.m_nodes[index]->m_heartbeat == parent.m_heartbeat)
			return *parent.m_nodes[index];
		for(uint16_t i = 0; i < index; ++i)
			parent.subx(i).init(dock_styles().dockline, false, dim);
		Widget& self = parent.subx(index).init(dock_styles().dockline, false, dim);
		grid_sheet_logic(self, dim);
		return self;
	}
	
	Tabber& docksection(Widget& parent)
	{
		if(parent.m_nodes.size() > 0 && parent.m_nodes[0]->m_heartbeat == parent.m_heartbeat)
			return as<Tabber>(*parent.m_nodes[0]);
		//Widget& section = ui::widget(parent, dock_styles().docksection); // dockid.back()
		Tabber& tabber = ui::tabber(parent); // dockspace_styles().docksection, 
		return tabber;
	}

	Dockspace& dockspace(Widget& parent, Docksystem& docksystem)
	{
		Dockspace& self = parent.suba<Dockspace, Docksystem&>(docksystem);
		self.init(dock_styles().dockspace);
		self.m_mainline = &dockline(self, 0, DIM_Y);
		return self;
	}

	Dockbar& dockbar(Widget& parent, Docksystem& docksystem)
	{
		Dockbar& self = parent.suba<Dockbar, Docksystem&>(docksystem);
		self.init(dock_styles().dockbar);

		self.m_togglebar = &widget(self, dock_styles().docktabs);

		static float width = 300.f;

		Widget& drag_handle = widget(self, styles().drag_handle);
		if(MouseEvent mouse_event = drag_handle.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
			width -= mouse_event.m_delta.x;

		self.m_dockzone = &widget(self, dock_styles().dockdiv);
		if(self.m_current_tab == SIZE_MAX)
			self.m_dockzone->m_frame.m_size = { 0.f, 0.f };
		else
			self.m_dockzone->m_frame.m_size = { width, 0.f };

		return self;
	}

	Widget* dockitem(Widget& parent, Docksystem& docksystem, Dock& dock)
	{
		UNUSED(docksystem);
		if(dock.m_dockid.size() > 0)
		{
			return dock.m_docker->docksection(dock);
		}
		else
		{
			Window& container = window(parent, dock.m_name, static_cast<WindowState>(WINDOW_DOCKABLE | WINDOW_DEFAULT), &dock);
			container.m_dock = &dock;
			return &container;
		}
	}

	Widget* dockitem(Docker& docker, cstring name, array<uint16_t> dockid, float span)
	{
		if(docker.m_docksystem->m_docks.find(name) == docker.m_docksystem->m_docks.end())
		{
			docker.m_docksystem->m_docks[name] = { docker, name, to_vector(dockid), span };
			docker.m_docks.push_back(&docker.m_docksystem->m_docks[name]);
		}

		return dockitem(docker, *docker.m_docksystem, docker.m_docksystem->m_docks[name]);
	}
}
}


#ifdef MUD_MODULES
module mud.ui;
#else
#endif

#include <algorithm>

namespace mud
{
namespace ui
{
	bool drag_float(Widget& parent, float& value, float step)
	{
		string text = truncate_number(to_string(value));
		TextEdit& self = type_in(parent, text, 0, "1234567890.");
		self.m_focus_mode = TextFocusMode::Click;
		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
		{
			self.clear_focus();
			value += mouse_event.m_delta.x * step;
			return true;
		}
		else if(self.m_changed)
		{
			value = to_value<float>(text);
			return true;
		}
		return false;
	}

	bool flag_input(Widget& parent, uint32_t& value, uint8_t shift)
	{
		Widget& self = widget(parent, styles().input_bool);
		bool enabled = (value & (1 << shift)) != 0;
		bool changed = checkbox(self, enabled).activated();
		if(enabled)
			value |= (1 << shift);
		else
			value &= ~(1 << shift);
		return changed;
	}
	
	bool vec2_edit(Widget& parent, vec2& vec)
	{
		Widget& self = ui::row(parent);
		StatDef<float> def = { limits<float>::min(), limits<float>::max(), 0.01f };
		bool changed = false;
		changed |= ui::number_input<float>(self, { vec.x, def });
		changed |= ui::number_input<float>(self, { vec.y, def });
		return changed;
	}

	bool vec3_edit(Widget& parent, vec3& vec)
	{
		Widget& self = ui::row(parent);
		StatDef<float> def = { limits<float>::min(), limits<float>::max(), 0.01f };
		bool changed = false;
		changed |= ui::number_input<float>(self, { vec.x, def });
		changed |= ui::number_input<float>(self, { vec.y, def });
		changed |= ui::number_input<float>(self, { vec.z, def });
		return changed;
	}

	bool quat_edit(Widget& parent, quat& quat)
	{
		Widget& self = ui::row(parent);
		StatDef<float> def = { 0.f, 1.f, 0.01f };
		bool changed = false;
		changed |= ui::number_input<float>(self, { quat.x, def });
		changed |= ui::number_input<float>(self, { quat.y, def });
		changed |= ui::number_input<float>(self, { quat.z, def });
		changed |= ui::number_input<float>(self, { quat.w, def });
		return changed;
	}

	void draw_color_wheel(Vg& vg, const vec2& size, float hue, float s, float l)
	{
		vec2 center = size * 0.5f;
		float r1 = (size.x < size.y ? size.x : size.y) * 0.5f - 5.0f;
		float r0 = r1 - 20.0f;

		vg.draw_color_wheel(center, r0, r1);
		vg.draw_color_triangle(center, r0, hue, s, l);
	}

	bool inside_color_wheel(Widget& self, const MouseEvent& event)
	{
		vec2 center = self.m_frame.m_size * 0.5f;
		float r1 = center.x - 5.0f;
		float r0 = r1 - 20.0f;
		float dist = distance(center, event.m_relative);
		return dist <= r1 && dist >= r0;
	}

	void drag_color_wheel(Widget& self, Colour& hsla, const MouseEvent& event)
	{
		vec2 coord = { event.m_relative.x, self.m_frame.m_size.y - event.m_relative.y };
		vec2 center = self.m_frame.m_size * 0.5f;
		float angle = oriented_angle_2d(normalize(coord - center), { 1.f, 0.f });
		hsla.m_h = angle / (c_pi * 2.f);
	}

	bool color_wheel(Widget& parent, Colour& hsla)
	{
		Widget& self = widget(parent, styles().color_wheel);
		self.m_custom_draw = [&](const Frame& frame, const vec4& rect, Vg& vg)
		{
			UNUSED(rect);
			draw_color_wheel(vg, frame.m_size, hsla.m_h, hsla.m_s, hsla.m_l);
		};
		bool changed = false;

		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseLeft, EventType::Pressed))
		{
			changed = true;
			if(inside_color_wheel(self, mouse_event))
				drag_color_wheel(self, hsla, mouse_event);
		}

		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
		{
			changed = true;
			drag_color_wheel(self, hsla, mouse_event);
		}

		return changed;
	}

	bool color_edit_hsl(Widget& parent, const Colour& colour, Colour& hsla)
	{
		static cstring columns[2] = { "field", "value" };
		Widget& self = table(parent, { columns, 2 }, {}); // , { 0.3f, 0.7f }
		color_display_field(self, "color", colour);

		bool changed = false;
		StatDef<float> def = { 0.f, 1.f, 0.01f };
		changed |= slider_field<float>(self, "hue", { hsla.m_h, def });
		changed |= slider_field<float>(self, "saturation", { hsla.m_s, def });
		changed |= slider_field<float>(self, "lightness", { hsla.m_l, def });

		return changed;
	}

	bool color_edit_simple(Widget& parent, Colour& value)
	{
		Widget& self = widget(parent, styles().input_color);
		color_slab(self, styles().color_slab, value);

		bool changed = false;
		StatDef<float> def = { 0.f, 1.f, 0.01f };
		changed |= slider_input<float>(self, { value.m_r, def });
		changed |= slider_input<float>(self, { value.m_g, def });
		changed |= slider_input<float>(self, { value.m_b, def });

		return changed;
	}

	bool color_edit(Widget& parent, Colour& value)
	{
		Colour hsla = rgba_to_hsla(value);
		Widget& self = stack(parent);
		bool changed = false;
		changed |= color_wheel(self, hsla);
		changed |= color_edit_hsl(self, value, hsla);
		value = hsla_to_rgba(hsla);
		return changed;
	}

	bool color_popup(Widget& parent, Colour& value, bool& open)
	{
		Widget& self = popup(parent, styles().color_popup, PopupFlags(size_t(PopupFlags::Clamp) | size_t(PopupFlags::AutoModal)));
		open &= self.m_open;
		return color_edit(self, value);
	}

	Widget& color_slab(Widget& parent, Style& style, const Colour& value)
	{
		Widget& self = button(parent, style);//styles().color_slab);
		self.m_custom_draw = [&](const Frame& frame, const vec4& rect, Vg& vg)
		{
			UNUSED(rect);
			vg.draw_rect({ Zero2, frame.m_size }, value, frame.d_inkstyle->m_corner_radius);
		};
		return self;
	}

	Widget& color_display(Widget& parent, const Colour& value)
	{
		return color_slab(parent, styles().color_display, value);
	}

	bool color_toggle_edit(Widget& parent, Colour& value)
	{
		Widget& self = color_slab(parent, styles().color_toggle, value);
		if(self.activated())
			self.m_open = !self.m_open;
		if(self.m_open)
			return color_popup(self, value, self.m_open);
		return false;
	}

namespace
{
	struct Curve
	{
		Curve(const vec2& size, float min, float max, array<float> values, array<float> points)
			: m_min(min), m_max(max), m_values(values), m_points(points)
		{
			m_scale = size * vec2{ 1.f, max - min };
		}

		float m_min;
		float m_max;
		array<float> m_values;
		array<float> m_points;
		vec2 m_scale;

		vec2 point(size_t i)
		{
			float t = m_points.size() > 0 ? m_points[i] : i / float(m_values.size() - 1);
			return m_scale * vec2{ t, (m_values[i] - m_min) };
		}

		size_t point_at(vec2 position)
		{
			const float margin = 8.f;
			for(size_t i = 0; i < m_values.size(); ++i)
				if(distance(point(i), position) < margin)
					return i;
			return SIZE_MAX;
		}
	};
}

	void draw_curve(const Colour& colour, Curve& curve, size_t hovered, Vg& vg)
	{
		UNUSED(hovered);
		float distance = 100.f;
		Paint paint = { colour, 1.f };

		for(size_t i = 0; i < curve.m_values.size() - 1; ++i)
		{
			vec2 begin = curve.point(i);
			vec2 end = curve.point(i + 1);
			vg.path_bezier(begin, begin + vec2{ distance, 0.f }, end - vec2{ distance, 0.f }, end, false);
			vg.stroke(paint);
		}
	}

	void draw_points(const Colour& colour, Curve& curve, size_t hovered, Vg& vg)
	{
		Paint paint = { colour, 1.f };

		for(size_t i = 0; i < curve.m_values.size(); ++i)
		{
			vg.path_circle(curve.point(i), 5.f);
			vg.stroke(hovered == i ? Paint{ Colour::White, 1.f } : paint);
		}
	}

	bool curve_graph(Widget& parent, array<float> values, array<float> points)
	{
		const float lowest = 0.f;
		const float highest = 1.f;

		Widget& self = widget(parent, styles().curve_graph);
		Curve curve = { rect_size(self.m_frame.content_rect()), lowest, highest, values, points };
		
		static size_t hovered = SIZE_MAX;
		static size_t dragged = SIZE_MAX;

		if(self.ui().m_hovered == &self)
			hovered = curve.point_at(self.m_frame.local_position(self.ui().m_mouse.m_pos));

		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseLeft, EventType::Pressed))
			dragged = curve.point_at(mouse_event.m_relative);

		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
			if(dragged != SIZE_MAX)
			{
				vec2 delta = mouse_event.m_delta / curve.m_scale;
				curve.m_values[dragged] = clamp(curve.m_values[dragged] + delta.y, lowest, highest);
			}

		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseLeft, EventType::Released))
			dragged = SIZE_MAX;

		self.m_custom_draw = [&](const Frame& frame, const vec4& rect, Vg& vg)
		{
			UNUSED(frame); UNUSED(rect);
			Curve curve = { rect_size(rect), 0.f, 1.f, values, points };
			vg.draw_rect(rect, { Colour::DarkGrey });
			draw_curve(Colour::NeonGreen, curve, hovered, vg);
			draw_points(Colour::NeonGreen, curve, hovered, vg);
		};

		return false;
	}

	bool curve_edit(Widget& parent, array<float> values, array<float> points)
	{
		Widget& self = widget(parent, styles().curve_input);
		curve_graph(self, values, points);
		return false;
	}

	bool curve_edit(Widget& parent, array<Colour> values, array<float> points)
	{
		UNUSED(parent); UNUSED(values); UNUSED(points);
		return false;
	}
}
}


#ifdef MUD_MODULES
module mud.ui;
#else
#endif

namespace mud
{
namespace ui
{
	void draw_knob(const Frame& frame, const Colour& colour, bool connected, Vg& vg)
	{
		float radius = connected ? 5.f : 4.f;
		vg.path_circle(frame.m_size / 2.f, radius);
		if(connected)
			vg.fill({ colour });
		else
			vg.stroke({ colour, 2.f });
	}


	void canvas_autolayout(Canvas& canvas)
	{
		Frame& plan = canvas.m_plan->m_frame;

		int min_index = 0;
		int max_index = 0;
		for(Node* node : canvas.m_nodes)
		{
			min_index = min(min_index, node->m_order);
			max_index = max(max_index, node->m_order);
		}

		int shift = -min(0, min_index);
		
		static Layout layout_overlay = [](Layout& l) { l.m_space = BOARD; };
		static Layout layout_line = [](Layout& l) { l.m_space = ITEM; l.m_align = { CENTER, CENTER }; l.m_padding = vec4(20.f); l.m_spacing = vec2(100.f); };
		static Layout layout_column = [](Layout& l) { l.m_space = UNIT; l.m_align = { Left, CENTER }; l.m_padding = vec4(20.f); l.m_spacing = vec2(20.f); };
		static Layout layout_node = [](Layout& l) { l.m_space = BLOCK; };

		SolverVector solvers;
		
		RowSolver overlay(plan.m_solver.get(), &layout_overlay);
		overlay.m_size = plan.m_size;
		solvers.push_back(&overlay);

		RowSolver line(&overlay, &layout_line);
		//RowSolver line(plan.m_solver.get(), &layout_line);
		solvers.push_back(&line);

		vector<RowSolver> columns; columns.reserve(canvas.m_nodes.size());
		vector<FrameSolver> elements; elements.reserve(canvas.m_nodes.size());

		for(int i = 0; i < max_index + shift + 1; ++i)
		{
			columns.emplace_back(&line, &layout_column);
			solvers.push_back(&columns.back());
		}

		for(size_t i = 0; i < canvas.m_nodes.size(); ++i)
		{
			elements.emplace_back(&columns[canvas.m_nodes[i]->m_order + shift], &layout_node, &canvas.m_nodes[i]->m_frame);
			elements.back().sync();
			solvers.push_back(&elements.back());
		}

		relayout(solvers);
	}

	void draw_node_cable(vec2 pos_out, vec2 pos_in, const Colour& colour_out, const Colour& colour_in, bool straight, Vg& vg)
	{
		float distance = straight ? 20.f : 100.f;
		Gradient paint = { colour_out, colour_in };
		vg.path_bezier(pos_out, pos_out + vec2{ distance, 0.f }, pos_in - vec2{ distance, 0.f }, pos_in, straight);
		vg.stroke_gradient(paint, 1.f, pos_out, pos_in);
	}

	Widget& node_knob(Widget& parent, Style& style, const Colour& colour, bool active, bool connected)
	{
		Widget& self = widget(parent, style);
		static Colour disabled_colour = Colour::DarkGrey;
		self.m_custom_draw = [&](const Frame& frame, const vec4& rect, Vg& vg)
		{
			UNUSED(rect); draw_knob(frame, active ? colour : disabled_colour, connected, vg);
		};
		return self;
	}

	Widget& canvas_cable(Widget& parent, vec2 out, vec2 in, const Colour& colour_out, const Colour& colour_in, bool straight = false)
	{
		Widget& self = widget(parent, node_styles().cable);
		self.m_frame.m_position = min(out, in);
		self.m_frame.m_size = max(out, in) - self.m_frame.m_position;
		self.m_custom_draw = [&](const Frame& frame, const vec4& rect, Vg& vg)
		{
			UNUSED(rect); draw_node_cable(out - frame.m_position, in - frame.m_position, colour_out, colour_in, straight, vg);
		};
		return self;
	}

	vec2 plug_at_out(Canvas& canvas, NodePlug& plug)
	{
		Frame& knob = plug.m_knob->m_frame;
		return knob.derive_position({ knob.m_size.x, knob.m_size.y / 2 }, canvas.m_plan->m_frame);
	}

	vec2 plug_at_in(Canvas& canvas, NodePlug& plug)
	{
		Frame& knob = plug.m_knob->m_frame;
		return knob.derive_position({ 0.f, knob.m_size.y / 2 }, canvas.m_plan->m_frame);
	}

	Widget& node_cable(Canvas& canvas, NodePlug& plug_out, NodePlug& plug_in)
	{
		return canvas_cable(*canvas.m_plan, plug_at_out(canvas, plug_out), plug_at_in(canvas, plug_in), plug_out.m_colour, plug_in.m_colour, !canvas.m_rounded_links);
	}

	NodePlug& node_plug(Node& node, cstring name, cstring icon, const Colour& colour, bool input, bool active, bool connected)
	{
		NodePlug& self = input ? twidget<NodePlug>(*node.m_inputs, node_styles().plug)
							   : twidget<NodePlug>(*node.m_outputs, node_styles().plug);
		self.m_node = &node;
		self.m_colour = colour;

		if(input)
			self.m_knob = &node_knob(self, node_styles().knob, colour, active, connected);

		label(self, name).set_state(DISABLED, !active);
		UNUSED(icon);
		//item(self, icon);

		if(!input)
			self.m_knob = &node_knob(self, node_styles().knob_output, colour, active, connected);

		Canvas& canvas = *node.m_canvas;

		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
		{
			Widget* target = static_cast<Widget*>(mouse_event.m_target);
			NodePlug* target_plug = nullptr;
			if(target && target->m_frame.d_style == &node_styles().plug && target != &self)
				target_plug = static_cast<NodePlug*>(target);

			canvas.m_connect.m_origin = &self;
			canvas.m_connect.m_in = input ? &self : target_plug;
			canvas.m_connect.m_out = input ? target_plug : &self;
			canvas.m_connect.m_position = mouse_event.m_pos;
		}

		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseLeft, EventType::DragEnded))
		{
			canvas.m_connect.m_done = true;
		}

		return self;
	}

	Widget& node_header(Widget& parent, array<cstring> title)
	{
		Widget& self = multi_item(parent, node_styles().header, title);
		spacer(self);
		return self;
	}

	void canvas_clear_select(Canvas& canvas)
	{
		for(Node* selected : canvas.m_selection)
			selected->disable_state(SELECTED);
		canvas.m_selection.clear();
	}

	void canvas_select(Canvas& canvas, Node& node)
	{
		canvas_clear_select(canvas);
		vector_select(canvas.m_selection, &node);
		node.enable_state(SELECTED);
	}

	void canvas_swap_select(Canvas& canvas, Node& node)
	{
		bool selected = vector_swap(canvas.m_selection, &node);
		node.set_state(SELECTED, selected);
	}

	template <class T>
	inline T& ttwidget(Widget& parent, Style& style, void* identity)
	{
		T& self = parent.subi<T>(identity); self.init(style); return self;
	}

	Node& node(Canvas& parent, array<cstring> title, int order, Ref identity)
	{
		Node& self = ttwidget<Node>(*parent.m_plan, node_styles().node, identity.m_value);
		self.layer();
		self.m_canvas = &parent;
		self.m_order = order;
		self.m_header = &node_header(self, title);

		Widget& plugs = widget(self, node_styles().plugs);
		self.m_inputs = &widget(plugs, node_styles().inputs);
		self.m_outputs = &widget(plugs, node_styles().outputs);

		self.m_body = &self;

		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseLeft, EventType::Stroked, InputMod::Shift))
			canvas_swap_select(parent, self);
		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
			canvas_select(parent, self);
		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseRight, EventType::Stroked))
			canvas_select(parent, self);

		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
		{
			if(!vector_has(parent.m_selection, &self))
				canvas_select(parent, self);

			for(Node* node : parent.m_selection)
				node->m_frame.set_position(node->m_frame.m_position + mouse_event.m_delta / node->m_frame.absolute_scale());
		}

		self.m_index = parent.m_nodes.size();
		parent.m_nodes.push_back(&self);

		return self;
	}

	Node& node(Canvas& parent, array<cstring> title, float* position, int order, Ref identity)
	{
		Node& self = node(parent, title, order, identity);
		if(self.once())// && position != Zero2)
			self.m_frame.set_position({ position[0], position[1] });
		else
		{
			position[0] = self.m_frame.m_position.x;
			position[1] = self.m_frame.m_position.y;
		}
		return self;
	}

	Node& node(Canvas& parent, array<cstring> title, vec2& position, int order, Ref identity)
	{
		return node(parent, title, &position[0], order, identity);
	}

	Node& node(Canvas& parent, cstring title, vec2& position, int order, Ref identity)
	{
		return node(parent, carray<cstring, 1>{ title }, &position[0], order, identity);
	}

	Canvas& canvas(Widget& parent, size_t num_nodes) // , const Callback& context_trigger
	{
		Canvas& self = twidget<Canvas>(parent, canvas_styles().canvas);
		self.layer();

		self.m_scroll_plan = &scroll_plan(self);
		self.m_plan = self.m_scroll_plan->m_body;

		autofit_scroll_plan(*self.m_scroll_plan, to_array_cast<Widget*>(self.m_nodes));

		//if(mouse_click_right(self) && context_trigger)
		//	context_trigger(self);

		if(MouseEvent mouse_event = self.m_scroll_plan->mouse_event(DeviceType::MouseLeft, EventType::Dragged))
		{
			for(Node* node : self.m_selection)
				node->m_frame.set_position(node->m_frame.m_position + mouse_event.m_delta / node->m_frame.absolute_scale());
		}

		if(MouseEvent mouse_event = self.m_scroll_plan->mouse_event(DeviceType::MouseLeft, EventType::Stroked))
			canvas_clear_select(self);

		if(MouseEvent mouse_event = self.m_scroll_plan->mouse_event(DeviceType::MouseMiddle, EventType::Stroked))
			canvas_autolayout(self);

		self.m_nodes.reserve(num_nodes);
		self.m_nodes.clear();

		return self;
	}

	NodeConnection canvas_connect(Canvas& canvas)
	{
		NodeConnection connection = {};
		
		CanvasConnect& connect = canvas.m_connect;
		if(connect.m_origin)
		{
			vec2 target = canvas.m_plan->m_frame.local_position(connect.m_position);
			Colour out_colour = connect.m_out ? connect.m_out->m_colour : connect.m_in->m_colour;
			Colour in_colour = connect.m_in ? connect.m_in->m_colour : connect.m_out->m_colour;

			vec2 out = connect.m_out ? plug_at_out(canvas, *connect.m_out) : target;
			vec2 in = connect.m_in ? plug_at_in(canvas, *connect.m_in) : target;

			canvas_cable(*canvas.m_plan, out, in, out_colour, in_colour);

			if(connect.m_done)
			{
				if(connect.m_out && connect.m_in)
					connection = { connect.m_out->m_node->m_index, connect.m_out->m_index,
								   connect.m_in->m_node->m_index,  connect.m_in->m_index };

				connect = {};
			}
		}
		else
		{
			canvas_cable(*canvas.m_plan, Zero2, Zero2, Colour::None, Colour::None);
			connect = {};
		}

		return connection;
	}
}
}


#ifdef MUD_MODULES
module mud.ui;
#else
#endif

namespace mud
{
namespace ui
{
	bool overflow(Frame& frame, Frame& content, Dim dim)
	{
		float visible_size = frame.m_size[dim];
		float content_size = content.m_size[dim] * content.m_scale;
		return content_size - visible_size > 0.f;
	}

	void scroll_to(Frame& content, Dim dim, float offset)
	{
		content.set_position(dim, -offset);
		//content.layer().setForceRedraw();
	}

	bool scroller(Widget& parent, float& cursor, float overflow, float visible_size, Dim dim)
	{
		return slider(parent, scrollbar_styles().scroller, cursor, SliderMetrics{ 0.f, overflow, 1.f, visible_size },
					  dim, true, false, &scrollbar_styles().scroller_knob);
	}

	Widget& scrollbar(Widget& parent, Frame& frame, Frame& content, Dim dim, Dim2<size_t> grid_index)
	{
		Widget& self = widget(parent, styles().row, false, dim, grid_index);

		float visible_size = frame.m_size[dim];
		float content_size = content.m_size[dim] * content.m_scale;
		float overflow = content_size - visible_size;

		if(overflow <= 0.f)
			return self;

		Widget& scrollbar = widget(self, scrollbar_styles().scrollbar, false, dim);

		float cursor = -content.m_position[dim];
		if(cursor > 0.f && content_size - cursor < visible_size)
			cursor = max(content_size - visible_size, 0.f);

		Widget& rewind = button(scrollbar, dim == DIM_Y ? scrollbar_styles().scroll_up
														: scrollbar_styles().scroll_left);

		scroller(scrollbar, cursor, overflow, visible_size, dim);

		Widget& forward = button(scrollbar, dim == DIM_Y ? scrollbar_styles().scroll_down
														 : scrollbar_styles().scroll_right);

		if(rewind.activated())
			cursor -= 22.f;

		if(forward.activated())
			cursor += 22.f;

		scroll_to(content, dim, max(0.f, min(overflow, cursor)));

		return self;
	}
}
}

#include <cfloat>

#ifdef MUD_MODULES
module mud.ui;
#else
#endif

namespace mud
{
namespace ui
{
	void draw_grid(const Frame& frame, float frequency, const Paint& paint, Vg& vg)
	{
		float start = frequency;

		for(float val = start; val < frame.m_size.x; val += frequency)
		{
			vg.path_line({ val, 0.f }, { val, frame.m_size.y });
			vg.stroke(paint);
		}
		for(float val = start; val < frame.m_size.y; val += frequency)
		{
			vg.path_line({ 0.f, val }, { frame.m_size.x, val });
			vg.stroke(paint);
		}

		vg.stroke(paint);
	}

	void draw_grid(const Frame& frame, const vec4& rect, Vg& vg)
	{
		UNUSED(rect);
		Paint main_paint = { Colour(0.162f, 0.162f, 0.162f, 1.f), 1.f };
		Paint second_paint = { Colour(0.094f, 0.094f, 0.094f, 1.f), 0.5f };

		draw_grid(frame, 20.0f, second_paint, vg);
		draw_grid(frame, 100.f, main_paint, vg);
	}

	void scroll_plan_drag(Frame& scroll_zone, Frame& scroll_plan, const MouseEvent& mouse_event)
	{
		vec2 position = scroll_plan.m_position + mouse_event.m_delta;
		vec2 overflow = (scroll_plan.m_size * scroll_plan.m_scale) - scroll_zone.m_size;
		scroll_plan.set_position(min(Zero2, max(position, -overflow)));
		//m_frame.mark_dirty(DIRTY_FORCE_LAYOUT);
	}

	void scroll_plan_drag(ScrollSheet& scroll_sheet, const MouseEvent& mouse_event)
	{
		return scroll_plan_drag(scroll_sheet.m_scroll_zone->m_frame, scroll_sheet.m_body->m_frame, mouse_event);
	}

	void scroll_plan_zoom(Frame& scroll_zone, Frame& scroll_plan, const MouseEvent& mouse_event, bool clamped)
	{
		float delta_scale = mouse_event.m_deltaZ > 0.f ? 1.2f : 0.8333f;
		scroll_plan.m_scale = scroll_plan.m_scale * delta_scale;

		if(clamped)
		{
			vec2 min_scale = scroll_zone.m_size / scroll_plan.m_size;
			scroll_plan.m_scale = max(scroll_plan.m_scale, max(min_scale.x, min_scale.y));
		}

		vec2 relative = mouse_event.m_pos - scroll_plan.absolute_position();
		vec2 offset = relative - relative * delta_scale;
		vec2 position = offset + scroll_plan.m_position;

		if(clamped)
			scroll_plan.set_position(min(vec2(0.f), position));
		else
			scroll_plan.set_position(position);
	}

	void scroll_plan_zoom(ScrollSheet& scroll_sheet, const MouseEvent& mouse_event, bool clamped)
	{
		return scroll_plan_zoom(scroll_sheet.m_scroll_zone->m_frame, scroll_sheet.m_body->m_frame, mouse_event, clamped);
	}

	ScrollSheet& scroll_sheet(Widget& parent, Style& style, Style* surface_style)
	{
		ScrollSheet& self = twidget<ScrollSheet>(parent, style);
		self.m_scroll_zone = &widget(self, styles().scroll_zone, false, DIM_NONE, { 0, 0 });
		self.m_body = &widget(*self.m_scroll_zone, surface_style ? *surface_style : styles().scroll_surface);

		scrollbar(self, self.m_scroll_zone->m_frame, self.m_body->m_frame, DIM_X, { 0, 1 });
		scrollbar(self, self.m_scroll_zone->m_frame, self.m_body->m_frame, DIM_Y, { 1, 0 });

#if 0
		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseMiddle, EventType::Moved))
		{
			self.m_body->m_frame.set_position(DIM_X, self.m_body->m_frame.m_position[DIM_X] - mouse_event.m_delta.x);
			self.m_body->m_frame.set_position(DIM_Y, self.m_body->m_frame.m_position[DIM_Y] - mouse_event.m_delta.y);
			self.m_body->m_frame.set_position(DIM_Y, self.m_body->m_frame.m_position[DIM_Y] - 10.f * mouse_event.m_deltaZ);
		}
#endif

		return self;
	}

	ScrollSheet& scroll_plan(Widget& parent, Style& style)
	{
		bool clamped = true;

		ScrollSheet& self = scroll_sheet(parent, style, &styles().scroll_plan);

		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseMiddle, EventType::Dragged))
			scroll_plan_drag(self, mouse_event);
		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseMiddle, EventType::Moved))
			scroll_plan_zoom(self, mouse_event, clamped);
		
		return self;
	}

	void autofit_scroll_plan(ScrollSheet& scroll_sheet, array<Widget*> elements)
	{
		if(elements.size() == 0)
			return;

		Frame& scroll_plan = scroll_sheet.m_body->m_frame;

		float margin = 1000.f;
		vec2 bounds_min = vec2{ FLT_MAX };
		vec2 bounds_max = vec2{ FLT_MIN };

		for(Widget* widget : elements)
		{
			bounds_min = min(widget->m_frame.m_position, bounds_min);
			bounds_max = max(widget->m_frame.m_position + widget->m_frame.m_size, bounds_max);
			//offset = min(vec2{ widget->m_frame.m_position - margin });
		}

		vec2 offset = vec2(margin) - bounds_min;
		vec2 remainder = mod(offset, vec2(100.f));
		offset = offset - remainder;

		for(Widget* widget : elements)
			widget->m_frame.m_position += offset;

		scroll_plan.m_position += -offset * scroll_plan.m_scale;

		vec2 bounds = bounds_max + 2.f * margin - bounds_min;
		scroll_plan.m_size = bounds;
	}

	Widget& scrollable(Widget& parent)
	{
		return *scroll_sheet(parent).m_body;
	}
}
}


#ifdef MUD_MODULES
module mud.ui;
#else
#endif

namespace mud
{
	Style& section_style()
	{
		// STACK
		static Style style = { "Section", styles().sheet, [](Layout& l) { l.m_padding = vec4{ 2.f }; } };
		return style;
	}

	bool section_action(Section& parent, const string& name)
	{
		return ui::button(*parent.m_toolbar, name).activated();
	}

	Section& section(Widget& parent, const string& name, bool no_toolbar)
	{
		Section& self = ui::twidget<Section>(parent, section_style());
		ui::title_header(self, name.c_str());

		if(!no_toolbar)
			self.m_toolbar = &ui::toolbar(self);

		ScrollSheet& scroll_sheet = ui::scroll_sheet(self);
		self.m_body = &ui::sheet(*scroll_sheet.m_body);
		return self;
	}
}


#ifdef MUD_MODULES
module mud.ui;
#else
#endif

namespace mud
{
namespace ui
{
	Sequence& sequence(Widget& parent)
	{
		return twidget<Sequence>(parent, styles().sequence);
	}

	Sequence& scroll_sequence(Widget& parent)
	{
		Sequence& self = twidget<Sequence>(parent, styles().sequence);
		self.m_body = scroll_sheet(self).m_body;
		return self;
	}

	bool multiselect_logic(Widget& element, Ref object, vector<Ref>& selection)
	{
		bool changed = false;
		if(MouseEvent mouse_event = element.mouse_event(DeviceType::MouseLeft, EventType::Stroked, InputMod::Shift))
		{
			vector_swap(selection, object);
			changed = true;
		}
		if(MouseEvent mouse_event = element.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
		{
			vector_select(selection, object);
			changed = true;
		}
		if(MouseEvent mouse_event = element.mouse_event(DeviceType::MouseRight, EventType::Stroked))
		{
			vector_select(selection, object);
			changed = true;
		}

		element.set_state(SELECTED, vector_has(selection, object));
		return changed;
	}

	bool select_logic(Widget& element, Ref object, Ref& selection)
	{
		bool changed = false;
		if(MouseEvent mouse_event = element.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
		{
			selection = object;
			changed = true;
		}

		element.set_state(SELECTED, object == selection);
		return changed;
	}

	Widget& element(Widget& parent, Ref object)
	{
		Widget& self = widget(parent, styles().element, object.m_value);

		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
			parent.ui().m_drop = { static_cast<Widget*>(mouse_event.m_target), object, DropState::Preview };

		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseLeft, EventType::DragEnded))
			parent.ui().m_drop = { static_cast<Widget*>(mouse_event.m_target), object, DropState::Done };

		return self;
	}

	Widget& element(Widget& parent, Ref object, vector<Ref>& selection)
	{
		Widget& self = element(parent, object);
		multiselect_logic(self, object, selection);
		return self;
	}

	Widget& sequence_element(Sequence& sequence, Ref object)
	{
		return element(sequence.m_body ? *sequence.m_body : sequence, object, *sequence.m_selection);
	}
}
}


#ifdef MUD_MODULES
module mud.ui;
#else
#endif

namespace mud
{
namespace ui
{
	Widget& dummy(Widget& parent, const vec2& size)
	{
		Widget& self = widget(parent, styles().dummy);
		if(size != self.m_frame.m_content)
		{
			self.m_frame.m_content = size;
			self.m_frame.mark_dirty(DIRTY_LAYOUT);
		}
		return self;
	}

	Widget& layout_span(Widget& parent, float span)
	{
		Widget& self = ui::layout(parent);
		self.m_frame.set_span(DIM_X, span);
		self.m_frame.set_span(DIM_Y, span);
		return self;
	}

	Widget& popup(Widget& parent, Style& style, PopupFlags flags)
	{
		Widget& self = widget(parent, style, true).layer();

		if(!self.modal() && popup_flag(flags, PopupFlags::Modal))
			self.take_modal();

		if(popup_flag(flags, PopupFlags::Clamp))
			self.m_frame.clamp_to_parent();

		if(popup_flag(flags, PopupFlags::AutoClose))
		{
			// @todo change to Pressed, but causes a crash because InputDevice is holding to the pressed element
			if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
				self.m_open = false;
		}

		return self;
	}

	Widget& popup(Widget& parent, Style& style, const vec2& size, PopupFlags flags)
	{
		Widget& self = popup(parent, style, flags);
		self.m_body = &dummy(self, size);
		return self;
	}

	Widget& popup_at(Widget& parent, Style& style, const vec2& position, PopupFlags flags)
	{
		Widget& self = popup(parent, style, flags);
		self.m_frame.set_position(position);
		return self;
	}

	Widget& auto_modal(Widget& parent, uint32_t mode)
	{
		Widget& self = ui::modal(parent.parent_modal());
		if(!self.m_open)
			parent.m_switch &= ~mode;
		return self;
	}

	Widget& auto_modal(Widget& parent, uint32_t mode, const vec2& size)
	{
		Widget& self = ui::modal(parent.parent_modal(), size);
		if(!self.m_open)
			parent.m_switch &= ~mode;
		return self;
	}

	Widget* context(Widget& parent, uint32_t mode, PopupFlags flags)
	{
		if(MouseEvent mouse_event = parent.mouse_event(DeviceType::MouseRight, EventType::Stroked))
			parent.m_switch |= mode;

		if((parent.m_switch & mode) != 0)
		{
			Widget& self = popup(parent, flags);

			if(self.once())
			{
				vec2 mouse_pos = self.ui().m_mouse.m_pos;
				vec2 local = parent.m_frame.local_position(mouse_pos);
				self.m_frame.set_position(local);
			}

			parent.m_switch &= self.m_open ? mode : 0;
			return &self;
		}

		return nullptr;
	}


	DragPoint grid_sheet_drag(Widget& self, MouseEvent& mouse_event, Dim dim, bool start_drag)
	{
		// If not dragging already we take the position BEFORE the mouse moved as a reference
		DragPoint drag_point;
		vec2 local = !start_drag ? mouse_event.m_relative : self.m_frame.local_position(mouse_event.m_pressed);

		for(auto& widget : self.m_nodes)
		{
			if(widget->m_frame.m_position[dim] >= local[dim])
			{
				drag_point.next = &widget->m_frame;
				break;
			}
			drag_point.prev = &widget->m_frame;
		}

		return drag_point;
	}

	DragPoint grid_sheet_logic(Widget& self, Dim dim, bool& dragging)
	{
		// @todo we need to store the drag point only when the drag starts
		static DragPoint drag_point;

		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseLeft, EventType::DragStarted))
		{
			drag_point = grid_sheet_drag(self, mouse_event, dim, false);
		}

		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
		{
			dragging = true;
			if(drag_point.next && drag_point.prev)
				self.m_frame.transfer_pixel_span(*drag_point.prev, *drag_point.next, dim, mouse_event.m_delta[dim]);
		}

		if(&self == self.ui().m_hovered)
			self.ui().m_cursor_style = dim == DIM_X ? &cursor_styles().resize_x
															: &cursor_styles().resize_x;

		return drag_point;
	}

	DragPoint grid_sheet_logic(Widget& self, Dim dim)
	{
		bool dragging = false;
		return grid_sheet_logic(self, dim, dragging);
	}

	Widget& grid_sheet(Widget& parent, Style& style, Dim dim)
	{
		Widget& self = widget(parent, style, false, dim);
		grid_sheet_logic(self, dim);
		return self;
	}

	Widget& grid_sheet(Widget& parent, Style& style, Dim dim, array<float> spans)
	{
		Widget& self = widget(parent, style, false, dim);

		bool dragging = false;
		DragPoint drag_point = grid_sheet_logic(self, dim, dragging);
		if(dragging)
			if(drag_point.next && drag_point.prev)
			{
				spans[drag_point.prev->d_widget.m_index] = drag_point.prev->m_span[dim];
				spans[drag_point.next->d_widget.m_index] = drag_point.next->m_span[dim];
			}

		return self;
	}
}
}


#ifdef MUD_MODULES
module mud.ui;
#else
#endif

namespace mud
{
namespace ui
{
	SliderMetrics::SliderMetrics(float min, float max, float step_length, float knob_length)
		: m_min(min)
		, m_max(max)
		, m_step_length(step_length)
		, m_knob_length(knob_length)
	{
		m_range = m_max + m_knob_length - m_min;
		m_num_steps = m_range / m_step_length + 1;
	}

	float SliderMetrics::offset(float cursor) const
	{
		return cursor / m_range;
	}

	float SliderMetrics::cursor(float value, float offset) const
	{
		int prev_step = int((value - m_min) / m_step_length);
		int step = int(round(offset * (m_num_steps - 1.f)));
		if(step != prev_step)
			return m_min + step * m_step_length;
		return value;
	}

	SliderState SliderMetrics::compute(float value)
	{
		SliderState state;
		state.m_knob_span = m_knob_length / m_range;
		state.m_pre_span = (value - m_min) / m_range;
		state.m_post_span = 1.f - state.m_pre_span - state.m_knob_span;
		return state;
	}

	bool slider_cursor(Frame& slider, Frame& knob, Dim dim, const MouseEvent& mouse_event, float& value, const SliderMetrics& metrics, bool relative)
	{
		if(relative)
		{
			float delta = mouse_event.m_delta[dim] / slider.m_size[dim];
			float cursor = min(1.f, max(0.f, metrics.offset(value) + delta));
			value = metrics.cursor(value, cursor);
		}
		else
		{
			vec2 position = slider.local_position(mouse_event.m_pos);
			float offset = -knob.m_size[dim] / 2.f;
			float cursor = min(slider.m_size[dim]/* - knob.m_size[dim]*/, max(0.f, position[dim] + offset)) / slider.m_size[dim];
			value = metrics.cursor(value, cursor);
		}
		return true;
	}

	bool slider_logic(Widget& self, Frame& slider, Frame& filler, Frame& knob, float& value, const SliderMetrics& metrics, Dim dim, bool relative)
	{
        UNUSED(filler);
		bool changed = false;

		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
			changed |= slider_cursor(slider, knob, dim, mouse_event, value, metrics, relative);

		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseLeft, EventType::DragStarted))
			self.enable_state(PRESSED);

		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
			changed |= slider_cursor(slider, knob, dim, mouse_event, value, metrics, relative);

		if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseLeft, EventType::DragEnded))
			self.disable_state(PRESSED);

		return changed;
	}

	bool slider(Widget& parent, Style& style, float& value, SliderMetrics metrics, Dim dim, bool relative, bool fill, Style* knob_style)
	{
		Widget& self = widget(parent, style, false, dim);

		SliderState state = metrics.compute(value);
		Widget& filler = spanner(self, fill ? styles().filler : styles().spacer, dim, state.m_pre_span);
		Widget& button = spanner(self, knob_style ? *knob_style : styles().slider_knob, dim, state.m_knob_span);
		spanner(self, styles().spacer, dim, state.m_post_span);
		
		bool changed = false;
		changed |= slider_logic(self, self.m_frame, filler.m_frame, button.m_frame, value, metrics, dim, false);
		changed |= slider_logic(button, self.m_frame, filler.m_frame, button.m_frame, value, metrics, dim, relative);
		return changed;
	}

	bool slider(Widget& parent, float& value, SliderMetrics metrics, Dim dim, bool relative, bool fill, Style* knob_style)
	{
		return slider(parent, styles().slider, value, metrics, dim, relative, fill, knob_style);
	}
}
}

#ifdef MUD_MODULES
module mud.ui;
#else
#endif

namespace mud
{
    // Exported types
    template <> MUD_UI_EXPORT Type& type<mud::Align>() { static Type ty("mud::Align", sizeof(mud::Align)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::AutoLayout>() { static Type ty("mud::AutoLayout", sizeof(mud::AutoLayout)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Clipping>() { static Type ty("mud::Clipping", sizeof(mud::Clipping)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Dim>() { static Type ty("mud::Dim", sizeof(mud::Dim)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Flow>() { static Type ty("mud::Flow", sizeof(mud::Flow)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::FlowAxis>() { static Type ty("mud::FlowAxis", sizeof(mud::FlowAxis)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::LayoutSolver>() { static Type ty("mud::LayoutSolver", sizeof(mud::LayoutSolver)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Opacity>() { static Type ty("mud::Opacity", sizeof(mud::Opacity)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Pivot>() { static Type ty("mud::Pivot", sizeof(mud::Pivot)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::ui::PopupFlags>() { static Type ty("mud::ui::PopupFlags", sizeof(mud::ui::PopupFlags)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Sizing>() { static Type ty("mud::Sizing", sizeof(mud::Sizing)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::SpacePreset>() { static Type ty("mud::SpacePreset", sizeof(mud::SpacePreset)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::WidgetState>() { static Type ty("mud::WidgetState", sizeof(mud::WidgetState)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::WindowState>() { static Type ty("mud::WindowState", sizeof(mud::WindowState)); return ty; }
    
    template <> MUD_UI_EXPORT Type& type<mud::CanvasConnect>() { static Type ty("CanvasConnect", sizeof(mud::CanvasConnect)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Clipboard>() { static Type ty("Clipboard", sizeof(mud::Clipboard)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Dim2<bool>>() { static Type ty("Dim2<bool>", sizeof(mud::Dim2<bool>)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Dim2<mud::Align>>() { static Type ty("Dim2<mud::Align>", sizeof(mud::Dim2<mud::Align>)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Dim2<mud::AutoLayout>>() { static Type ty("Dim2<mud::AutoLayout>", sizeof(mud::Dim2<mud::AutoLayout>)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Dim2<mud::Pivot>>() { static Type ty("Dim2<mud::Pivot>", sizeof(mud::Dim2<mud::Pivot>)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Dim2<mud::Sizing>>() { static Type ty("Dim2<mud::Sizing>", sizeof(mud::Dim2<mud::Sizing>)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Dim2<size_t>>() { static Type ty("Dim2<size_t>", sizeof(mud::Dim2<size_t>)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Dock>() { static Type ty("Dock", sizeof(mud::Dock)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Docksystem>() { static Type ty("Docksystem", sizeof(mud::Docksystem)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Gradient>() { static Type ty("Gradient", sizeof(mud::Gradient)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::GridSolver>() { static Type ty("GridSolver", sizeof(mud::GridSolver)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::ImageSkin>() { static Type ty("ImageSkin", sizeof(mud::ImageSkin)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::InkStyle>() { static Type ty("InkStyle", sizeof(mud::InkStyle)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Layer>() { static Type ty("Layer", sizeof(mud::Layer)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Layout>() { static Type ty("Layout", sizeof(mud::Layout)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::NodeConnection>() { static Type ty("NodeConnection", sizeof(mud::NodeConnection)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Paint>() { static Type ty("Paint", sizeof(mud::Paint)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Shadow>() { static Type ty("Shadow", sizeof(mud::Shadow)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Space>() { static Type ty("Space", sizeof(mud::Space)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Style>() { static Type ty("Style", sizeof(mud::Style)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::TableSolver>() { static Type ty("TableSolver", sizeof(mud::TableSolver)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Text>() { static Type ty("Text", sizeof(mud::Text)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::TextCursor>() { static Type ty("TextCursor", sizeof(mud::TextCursor)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::TextMarker>() { static Type ty("TextMarker", sizeof(mud::TextMarker)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::TextPaint>() { static Type ty("TextPaint", sizeof(mud::TextPaint)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::TextSelection>() { static Type ty("TextSelection", sizeof(mud::TextSelection)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::UiRect>() { static Type ty("UiRect", sizeof(mud::UiRect)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::UiWindow>() { static Type ty("UiWindow", sizeof(mud::UiWindow)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::User>() { static Type ty("User", sizeof(mud::User)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Vg>() { static Type ty("Vg", sizeof(mud::Vg)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Frame>() { static Type ty("Frame", type<mud::UiRect>(), sizeof(mud::Frame)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::FrameSolver>() { static Type ty("FrameSolver", type<mud::UiRect>(), sizeof(mud::FrameSolver)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::LineSolver>() { static Type ty("LineSolver", type<mud::RowSolver>(), sizeof(mud::LineSolver)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Widget>() { static Type ty("Widget", type<mud::ControlNode>(), sizeof(mud::Widget)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Canvas>() { static Type ty("Canvas", type<mud::Widget>(), sizeof(mud::Canvas)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Dockable>() { static Type ty("Dockable", type<mud::Widget>(), sizeof(mud::Dockable)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Docker>() { static Type ty("Docker", type<mud::Widget>(), sizeof(mud::Docker)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Dockbar>() { static Type ty("Dockbar", type<mud::Docker>(), sizeof(mud::Dockbar)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Dockspace>() { static Type ty("Dockspace", type<mud::Docker>(), sizeof(mud::Dockspace)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Expandbox>() { static Type ty("Expandbox", type<mud::Widget>(), sizeof(mud::Expandbox)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Node>() { static Type ty("Node", type<mud::Widget>(), sizeof(mud::Node)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::NodePlug>() { static Type ty("NodePlug", type<mud::Widget>(), sizeof(mud::NodePlug)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::RowSolver>() { static Type ty("RowSolver", type<mud::FrameSolver>(), sizeof(mud::RowSolver)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::ScrollSheet>() { static Type ty("ScrollSheet", type<mud::Widget>(), sizeof(mud::ScrollSheet)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::ui::Sequence>() { static Type ty("Sequence", type<mud::Widget>(), sizeof(mud::ui::Sequence)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Tabber>() { static Type ty("Tabber", type<mud::Widget>(), sizeof(mud::Tabber)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Table>() { static Type ty("Table", type<mud::Widget>(), sizeof(mud::Table)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::TextEdit>() { static Type ty("TextEdit", type<mud::Widget>(), sizeof(mud::TextEdit)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::TreeNode>() { static Type ty("TreeNode", type<mud::Widget>(), sizeof(mud::TreeNode)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Ui>() { static Type ty("Ui", type<mud::Widget>(), sizeof(mud::Ui)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Window>() { static Type ty("Window", type<mud::Dockable>(), sizeof(mud::Window)); return ty; }
}


#ifdef MUD_MODULES
module mud.ui;
#else
#endif

namespace mud
{
	map<string, Style*> UiWindow::s_styles;

	UiWindow::UiWindow(Context& context, Vg& vg, User* user)
		: m_resource_path(context.m_resource_path)
		, m_context(context)
		, m_vg(vg)
		, m_renderer(vg)
		, m_atlas(uvec2(1024U))
		, m_width(float(context.m_width))
		, m_height(float(context.m_height))
		, m_user(user)
	{
		this->init();
	}

	UiWindow::~UiWindow()
	{
		for(auto& image : m_images)
			if(image->d_handle != -1)
			{
				m_vg.unload_image(*image);
			}
	}

	void UiWindow::init()
	{
		this->init_styles();

		printf("INFO: Initializing UiWindow: resource path %s\n", m_resource_path.c_str());
		m_vg.setup_context();

		this->init_resources();
		this->load_resources();

		styles().setup(*this);

		m_root_sheet = make_object<Ui>(*this);

		m_context.init_input(m_root_sheet->m_mouse, m_root_sheet->m_keyboard);

		this->resize(uint16_t(m_width), uint16_t(m_height));
	}

	void UiWindow::init_styles()
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

	void UiWindow::reset_styles()
	{
		styles() = {};

		ui::cursor_styles() = {};
		ui::scrollbar_styles() = {};
		ui::dropdown_styles() = {};
		ui::table_styles() = {};
		ui::expandbox_styles() = {};
		ui::treenode_styles() = {};
		ui::tabber_styles() = {};
		ui::menu_styles() = {};
		ui::toolbar_styles() = {};
		ui::window_styles() = {};
		ui::dock_styles() = {};
		ui::canvas_styles() = {};
		ui::node_styles() = {};
		ui::file_styles() = {};
	}

	void UiWindow::init_resources()
	{
		string sprite_path = m_resource_path + "/interface/uisprites";

		printf("INFO: Loading Images in path %s\n", sprite_path.c_str());

		vector<Image> images;
		load_folder_images(images, sprite_path, "");

		auto visit_folder = [&](const string& folder)
		{
			load_folder_images(images, sprite_path + folder + "/", string(folder) + "/");
		};

		visit_folders(sprite_path.c_str(), visit_folder);

		m_images = vector_convert<object<Image>>(images, [](const Image& image) { return make_object<Image>(image); });
	}

	void UiWindow::load_resources()
	{
		m_vg.load_default_font();

		vector<Image*> images;
		for(auto& image : m_images) images.push_back(image.get());

		vector<unsigned char> atlas = m_atlas.generate_atlas(images);
		m_vg.load_image_RGBA(m_atlas.m_image, atlas.data());
	}

	Image& UiWindow::create_image(cstring name, uvec2 size, uint8_t* data, bool filtering)
	{
		m_images.emplace_back(make_object<Image>(name, name, size));
		Image& image = *m_images.back();
		image.d_filtering = filtering;
		m_vg.load_image_RGBA(image, data);
		return image;
	}

	void UiWindow::remove_image(Image& image)
	{
		vector_remove_if(m_images, [&](object<Image>& current) { return current.get() == &image; });
		m_vg.unload_image(image);
	}

	Image* UiWindow::find_image(cstring name)
	{
		for(auto& image : m_images)
			if(image->d_name == name)
				return image.get();
		return nullptr;
	}

	void UiWindow::resize(uint16_t width, uint16_t height)
	{
		m_width = float(width);
		m_height = float(height);

		m_context.reset(width, height);

		printf("INFO: UiWindow :: resize %i, %i\n", int(width), int(height));
		m_root_sheet->m_frame.set_size({ m_width, m_height });
	}

	bool UiWindow::input_frame()
	{
		bool pursue = !m_shutdown;
		pursue &= m_context.next_frame();

		if(m_context.m_width != uint(m_width) || m_context.m_height != uint(m_height))
			this->resize(uint16_t(m_context.m_width), uint16_t(m_context.m_height));

		m_root_sheet->input_frame();

		m_root_sheet->m_frame.relayout();

		return pursue;
	}

	void UiWindow::render_frame()
	{
		//m_root_sheet->render_frame();

		if(m_context.m_render_system.m_manual_render)
		{
			m_renderer.render(*m_root_sheet->m_frame.m_layer);
			// add sub layers
		}

		m_root_sheet->clear_events();
	}

	void UiWindow::shutdown()
	{
		m_shutdown = true;
	}
}


#ifdef MUD_MODULES
module mud.ui;
#else
#include <stl/string.h>
#endif

namespace mud
{
namespace ui
{
	void widget_logic(Widget& self)
	{
		if(MouseEvent mouse_event = self.mouse_event(DeviceType::Mouse, EventType::Heartbeat))
			self.enable_state(HOVERED);
		else
			self.disable_state(HOVERED);
	}

	Widget& widget(Widget& parent, Style& style, void* identity)
	{
		Widget& self = parent.subi(identity).init(style);
		assert(self.m_frame.d_style);
		widget_logic(self);
		return self;
	}

	Widget& widget(Widget& parent, Style& style, bool open, Dim length, Dim2<size_t> index)
	{
		Widget& self = parent.subi(&style).init(style, open, length, index);
		assert(self.m_frame.d_style);
		widget_logic(self);
		return self;
	}

	Widget& item(Widget& parent, Style& style, cstring content)
	{
		Widget& self = widget(parent, style);
		if(content != nullptr)
			self.set_content(content);
		return self;
	}

	Widget& item(Widget& parent, Style& style, const string& content)
	{
		return item(parent, style, content.c_str());
	}

	Widget& multi_item(Widget& parent, Style& style, array<cstring> elements, Style* element_style)
	{
		Widget& self = widget(parent, style);
		for(cstring value : elements)
			item(self, element_style ? *element_style : styles().item, value);
		return self;
	}

	Widget& multi_item(Widget& parent, array<cstring> elements, Style* element_style)
	{
		return multi_item(parent, styles().row, elements, element_style);
	}

	Widget& spanner(Widget& parent, Style& style, Dim dim, float span)
	{
		Widget& self = widget(parent, style);
		self.m_frame.set_span(dim, span);
		return self;
	}
}
}


#ifdef MUD_MODULES
module mud.ui;
#else
#endif

namespace mud
{
namespace ui
{
	void window_drag_logic(Widget& widget, Window& window)
	{
		if(MouseEvent mouse_event = widget.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
		{
			window.enable_state(ACTIVATED);
			//if(!window.m_dock) // crashes for some reason
			window.m_frame.layer().moveToTop();
		}

		if(MouseEvent mouse_event = widget.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
		{
			if(window.m_dock)
				window.m_dock->m_docker->undock(window);

			window.m_frame.layer().moveToTop();
			window.m_frame.layer().m_frame.m_opacity = HOLLOW;

			if(window.movable())
				window.m_frame.set_position(window.m_frame.m_position + mouse_event.m_delta);
		}

		if(MouseEvent mouse_event = widget.mouse_event(DeviceType::MouseLeft, EventType::DragEnded))
		{
			//if(window.dockable())
			//	window.m_dock->m_docksystem->dock(window, mouse_event.m_pos);

			window.m_frame.layer().m_frame.m_opacity = OPAQUE;
		}
	}

	void window_resize_logic(Widget& widget, Window& window, bool left)
	{
		if(MouseEvent mouse_event = widget.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
		{
			window.m_frame.layer().moveToTop();

			if(left)
				window.m_frame.set_position(DIM_X, window.m_frame.m_position.x + mouse_event.m_delta.x);
			if(left)
				window.m_frame.set_size({ max(50.f, window.m_frame.m_size.x - mouse_event.m_delta.x), max(50.f, window.m_frame.m_size.y + mouse_event.m_delta.y) });
			else
				window.m_frame.set_size({ max(50.f, window.m_frame.m_size.x + mouse_event.m_delta.x), max(50.f, window.m_frame.m_size.y + mouse_event.m_delta.y) });
		}
	}

	Widget& window_header(Widget& parent, Window& window, cstring title)
	{
		Style* style = window.movable() ? &window_styles().header_movable : &window_styles().header;
		Widget& self = widget(parent, *style);

		item(self, styles().title, title);
		if(window.closable())
			if(button(self, window_styles().close_button).activated())
				window.m_open = false;

		tooltip(self, self.ui().m_mouse.m_pos, "Drag me");

		window_drag_logic(self, window);

		return self;
	}
	
	Widget& window_sizer(Widget& parent, Style& style, Window& window, bool left)
	{
		Widget& self = widget(parent, style);
		window_resize_logic(self, window, left);
		return self;
	}

	Widget& window_footer(Widget& parent, Window& window)
	{
		Widget& self = widget(parent, window_styles().footer);
		window_sizer(self, window_styles().sizer_left, window, true);
		window_sizer(self, window_styles().sizer_right, window, false);
		return self;
	}

	Window& window(Widget& parent, cstring title, WindowState state, void* identity, Dock* dock)
	{
		Window& self = parent.subi<Window>(identity);
		self.m_dock = dock;
		self.init(dock ? window_styles().dock_window : window_styles().window).layer();

		if(self.once())
		{
			self.m_open = true;
			self.m_window_state = state;

			if(!self.m_dock)
				self.m_frame.set_size({ 480.f, 350.f });

			if(!self.m_dock)
				self.m_frame.set_position((self.m_parent->m_frame.m_size - self.m_frame.m_size) / 2.f);
		}

		if(self.header())
			window_header(self, self, title);

		Widget& body = widget(self, window_styles().body);

		if(!self.m_dock && self.sizable())
			window_footer(self, self);

		if(!self.m_dock && self.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
			self.m_frame.layer().moveToTop();

		self.m_body = self.m_open ? &body : nullptr;

		return self;
	}

	Window& window(Widget& parent, cstring title, WindowState state)
	{
		return window(parent, title, state, nullptr, nullptr);
	}
}
}


#ifdef MUD_MODULES
module mud.ui;
#else
#endif

#define CANVAS_MULTI_DRAG 1

namespace mud
{
namespace ui
{
	WindowStyles::WindowStyles()
		: window("Window", styles().overlay, [](Layout& l) { l.m_space = BLOCK; })
		, body("WindowBody", styles().wedge, [](Layout& l) { l.m_clipping = CLIP; })
		, close_button("CloseButton", styles().button, [](Layout& l) { l.m_align = { Right, CENTER }; })
		, header("WindowHeader", styles().wrap_control, {}, {})
		, header_movable("WindowHeaderMovable", header, {}, {}) //, [](InkStyle& l) { l.m_hover_cursor = &cursor_styles().move; } })
		, footer("WindowFooter", styles().wrap_control, {}, {}) // , [](Layout& l) { l.m_space = Space{ READING, WRAP, FIXED }; } }
		, sizer("WindowSizer", styles().control, [](Layout& l) { l.m_space = Space{ READING, WRAP, FIXED }; })
		, sizer_left("WindowSizerLeft", sizer, {}, {}) //, [](InkStyle& l) { l.m_hover_cursor = &cursor_styles().resize_diag_left; } })
		, sizer_right("WindowSizerRight", sizer, {}, {}) //, [](InkStyle& l) { l.m_hover_cursor = &cursor_styles().resize_diag_right; } })

		, dock_window("DockWindow", window, [](Layout& l) { l.m_flow = FLOW; l.m_space = SHEET; })
		, wrap_window("WrapWindow", window, [](Layout& l) { l.m_space = UNIT; })
	{}

	WindowStyles& window_styles() { static WindowStyles styles; return styles; }

	DockStyles::DockStyles()
		: docktab("Docktab", tabber_styles().tab, {}, {})
		, placeholder("Placeholder", styles().board, {}, [](InkStyle& l) { l.m_background_colour = Colour::Blue; })

		, docksection("Docksection", styles().gridsheet, {}, {})
		, dockline("Dockline", styles().gridsheet, [](Layout& l) { l.m_space = SHEET; })
		, dockspace("Dockspace", styles().layout, [](Layout& l) { l.m_opacity = OPAQUE; l.m_spacing = vec2(6.f); })

		, docktoggle("DockToggle", styles().toggle, {}, {})
		, dockdiv("Dockzone", styles().wedge, [](Layout& l) { l.m_space = { PARAGRAPH, WRAP, FIXED }; })
		//, dockdiv("Dockzone", styles().wedge, [](Layout& l) { l.m_flow = ALIGN; l.m_space = SPACER; l.m_align = { Left, OUT_LEFT }; })
		, docktabs("Docktabs", styles().wedge, [](Layout& l) { l.m_flow = ALIGN; l.m_space = DIV; l.m_align = { OUT_LEFT, Left }; })
		, dockbar("Dockbar", styles().wedge, [](Layout& l) { l.m_space = { PARALLEL, SHRINK, WRAP }; })

		//, dockbox("Dockbox", window_styles().window, [](Layout& l) { l.m_flow = FLOW; l.m_space = { PARAGRAPH, WRAP, SHRINK }; l.m_size = vec2{ 300.f, 0.f }; })
	{}

	DockStyles& dock_styles() { static DockStyles styles; return styles; }

	NodeStyles::NodeStyles()
		: node("Node", styles().overlay, [](Layout& l) { l.m_space = UNIT; })
		, body("NodeBody", styles().sheet, {}, {})
		, plugs("NodePlugs", styles().sheet, [](Layout& l) { l.m_space = { READING, WRAP, WRAP }; })
		, inputs("NodeInputs", styles().div, {}, {})
		, outputs("NodeOutputs", styles().div, [](Layout& l) { l.m_align = { Right, CENTER }; })
		, knob("NodeKnob", styles().item, [](Layout& l) { l.m_size = { 10.f, 22.f }; }, [](InkStyle& l) { l.m_background_colour = Colour::White; })
		, knob_output("NodeKnobOutput", knob, [](Layout& l) { l.m_align = { Right, CENTER }; }, [](InkStyle& l) { l.m_background_colour = Colour::White; })
		, knob_proxy("NodeKnobProxy", knob, [](Layout& l) { l.m_flow = FREE; })
		, plug("NodePlug", styles().wrap_control, {}, {})
		, cable("NodeCable", styles().decal, [](Layout& l) { l.m_space = UNIT; }, [](InkStyle& l) { l.m_background_colour = Colour::White; })
		, header("NodeHeader", styles().row, {}, {})
	{}

	CanvasStyles::CanvasStyles()
		: canvas("Canvas", styles().layout, [](Layout& l) { l.m_clipping = CLIP; }) // l.m_opacity = OPAQUE;
	{}

	NodeStyles& node_styles() { static NodeStyles styles; return styles; }
	CanvasStyles& canvas_styles() { static CanvasStyles styles; return styles; }
}
}


#ifdef MUD_MODULES
module mud.ui;
#else
#endif

namespace mud
{
	EventDispatch::EventDispatch()
	{}

	void EventDispatch::process(Widget& widget)
	{
		if(!widget.m_events) return;

		KeyEvent* key_down_event = static_cast<KeyEvent*>(widget.m_events->m_events[size_t(DeviceType::Keyboard)][size_t(EventType::Pressed)]);
		if(key_down_event)
		{
			if(m_key_down_handlers.find(key_down_event->m_code) != m_key_down_handlers.end())
				m_key_down_handlers[key_down_event->m_code]();
		}

		KeyEvent* key_up_event = static_cast<KeyEvent*>(widget.m_events->m_events[size_t(DeviceType::Keyboard)][size_t(EventType::Released)]);
		if(key_up_event)
		{
			if(m_key_up_handlers.find(key_up_event->m_code) != m_key_up_handlers.end())
				m_key_up_handlers[key_up_event->m_code]();
		}
	}
}


#ifdef MUD_MODULES
module mud.ui;
#else
#endif

namespace mud
{
namespace ui
{
	Widget& command_line(Widget& parent, string& text, string& command)
	{
		string console_chars = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ .,:;+-*=~!()[]{}'\"\t";
		Widget& self = ui::type_in(parent, text, 1, console_chars);

		if(self.key_stroke(Key::Return))
		{
			command = text;
			text = "";
			self.key_stroke(Key::Return).consume(self);
		}

		return self;
	}

	Widget& console(Widget& parent, string& feed, string& line, string& command, size_t num_lines)
	{
		//ui::stack(self);
		Widget& self = ui::sheet(parent);
		ui::text_edit(self, feed, num_lines);
		ui::command_line(self, line, command);
		
		if(command != "")
			feed += "\n>> " + command;

		return self;
	}
}
}


#ifdef MUD_MODULES
module mud.ui;
#else
#endif

namespace mud
{
namespace ui
{
	Widget& dir_item(Widget& parent, cstring name)
	{
		carray<cstring, 2> elements = { "(folder_20)" , name };
		return multi_button(parent, file_styles().dir, elements);
	}

	Widget& file_item(Widget& parent, cstring name)
	{
		carray<cstring, 2> elements = { "(file_20)" , name };
		return multi_button(parent, file_styles().file, elements);
	}

	Widget& file_list(Widget& parent, string& path)
	{
		Widget& self = widget(parent, styles().wedge);//file_styles().directory);

		auto on_dir = [&](const string& dir)
		{
			if(string(dir) == ".") return;
			Widget& item = dir_item(self, dir.c_str());
			if(item.activated())
			{
				if(string(dir) == "..")
					path = path.substr(0, path.rfind("/"));
				else
					path = path + "/" + dir;
			}
		};

		auto on_file = [&](const string& file)
		{
			file_item(self, file.c_str());
		};

		visit_folders(path, on_dir);
		visit_files(path, on_file);
		return self;
	}

	Widget& file_browser(Widget& parent, string& path)
	{
		Widget& self = widget(parent, styles().wedge);// styles().file_browser);
		file_list(self, path);
		return self;
	}

	Widget& dir_node(Widget& parent, cstring path, cstring name, bool open)
	{
		carray<cstring, 2> elements = { "(folder_20)", name };
		Widget& self = tree_node(parent, elements, false, open);
		if(!self.m_body) return self;

		auto on_dir = [&](const string& dir)
		{
			dir_node(*self.m_body, (string(path) + "/" + dir).c_str(), dir.c_str(), false);
		};

		auto on_file = [&](const string& file)
		{
			file_node(*self.m_body, file.c_str());
		};

		visit_folders(path, on_dir);
		visit_files(path, on_file);
		return self;
	}

	Widget& file_node(Widget& parent, cstring name)
	{
		carray<cstring, 2> elements = { "(file_20)", name };
		Widget& self = tree_node(parent, elements, true, false);
		return self;
	}
	
	Widget& file_tree(Widget& parent, cstring path)
	{
		Widget& self = tree(parent);
		dir_node(self, path, path, false);
		return self;
	}
}
}


#ifdef MUD_MODULES
module mud.ui;
#else
#endif

namespace mud
{
	template<class T, size_t N>
	constexpr size_t size(T(&)[N]) { return N; }

	vector<uint32_t>& TextEdit::OkaidaPalette()
	{
		static vector<uint32_t> palette = vector<uint32_t>(size_t(CodePalette::Count));

		palette[Text::Default] = 0xffffffff;
		palette[Text::Background] = 0x000000ff;
		//palette[Text::Background] = 0x1e1e1eff;
		//palette[Text::Background] = 0x1f1f1fff;
		palette[Text::Cursor] = 0xe0e0e0ff;
		palette[Text::Selection] = 0x264f78ff;
		palette[Text::LineNumber] = 0x2b91afff;
		palette[Text::CurrentLineFill] = 0x0f0f0fff;
		palette[Text::CurrentLineFillInactive] = 0x242424ff;
		palette[Text::CurrentLineEdge] = 0x282828ff;

		palette[size_t(CodePalette::Word)] = 0xf8f8f2ff;
		palette[size_t(CodePalette::Keyword)] = 0xF92672ff;
		palette[size_t(CodePalette::Number)] = 0xae81ffff;
		palette[size_t(CodePalette::String)] = 0xa6e22eff;
		palette[size_t(CodePalette::CharLiteral)] = 0xa6e22eff;
		palette[size_t(CodePalette::Punctuation)] = 0xbebec5ff;
		palette[size_t(CodePalette::Operator)] = 0xF92672ff;
		palette[size_t(CodePalette::Preprocessor)] = 0x9b9b9bff;
		palette[size_t(CodePalette::Variable)] = 0x9b9b9bff;
		palette[size_t(CodePalette::Identifier)] = 0x7fc6efff;
		palette[size_t(CodePalette::Function)] = 0xe6db74ff;
		palette[size_t(CodePalette::Parameter)] = 0x7d7d7dff;
		palette[size_t(CodePalette::Field)] = 0x7d7d7dff;
		palette[size_t(CodePalette::PreprocIdentifier)] = 0xc040a0ff;
		palette[size_t(CodePalette::Comment)] = 0x708090ff;
		palette[size_t(CodePalette::Error)] = 0xffffffff;
		palette[size_t(CodePalette::ErrorMarker)] = 0xa30100ff;
		palette[size_t(CodePalette::Breakpoint)] = 0xf0800040;

		return palette;
	}

	vector<uint32_t>& TextEdit::DarkPalette()
	{
		static vector<uint32_t> palette = vector<uint32_t>(size_t(CodePalette::Count));

		palette[Text::Default]                 = 0xffffffff;
		palette[Text::Background]              = 0x1e1e1eff;
		//palette[Text::Background]              = 0x000000ff;
		palette[Text::Cursor]                  = 0xe0e0e0ff;
		palette[Text::Selection]               = 0x264f78ff;
		palette[Text::LineNumber]              = 0x2b91afff;
		palette[Text::CurrentLineFill]         = 0x0f0f0fff;
		palette[Text::CurrentLineFillInactive] = 0x242424ff;
		palette[Text::CurrentLineEdge]         = 0x282828ff;

		palette[size_t(CodePalette::Word)]				= 0xc8c8c8ff;
		palette[size_t(CodePalette::Keyword)]           = 0x569cd6ff;
		palette[size_t(CodePalette::Number)]            = 0xb5cea8ff;
		palette[size_t(CodePalette::String)]            = 0xd69d85ff;
		palette[size_t(CodePalette::CharLiteral)]       = 0xd69d85ff; //0xff70a0e0
		palette[size_t(CodePalette::Punctuation)]       = 0xbebec5ff;
		palette[size_t(CodePalette::Operator)]			= 0xffffffff;
		palette[size_t(CodePalette::Preprocessor)]      = 0x9b9b9bff;
		palette[size_t(CodePalette::Variable)]			= 0x9b9b9bff;
		palette[size_t(CodePalette::Identifier)]		= 0x4ec9b0ff;
		palette[size_t(CodePalette::Function)]			= 0xffffffff;
		palette[size_t(CodePalette::Parameter)]			= 0x7d7d7dff;
		palette[size_t(CodePalette::Field)]				= 0x9b9b9bff;
		palette[size_t(CodePalette::PreprocIdentifier)] = 0xc040a0ff;
		palette[size_t(CodePalette::Comment)]           = 0x494949ff;
		palette[size_t(CodePalette::Error)]				= 0xffffffff;
		palette[size_t(CodePalette::ErrorMarker)]       = 0xa30100ff;
		palette[size_t(CodePalette::Breakpoint)]        = 0xf0800040;

		return palette;
	}

	void builtin_keywords(LanguageDefinition& language, array<cstring> keywords)
	{
		for(cstring i : keywords)
			language.m_keywords.insert(string(i));
	}

	void builtin_identifiers(LanguageDefinition& language, array<cstring> identifiers)
	{
		for (cstring k : identifiers)
		{
			Identifier id = { {}, "Built-in identifier" };
			language.m_identifiers.insert({ string(k), id });
		}
	}

	void builtin_functions(LanguageDefinition& language, array<cstring> functions)
	{
		for (cstring k : functions)
		{
			Identifier id = { {}, "Built-in function" };
			language.m_functions.insert({ string(k), id });
		}
	}

	void add_token_regex(LanguageDefinition& lang, const string& token, CodePalette index)
	{
		lang.m_regex_string_tokens.push_back({ token, PaletteIndex(index) });
		lang.m_regex_tokens.push_back({ std::regex(token.c_str(), std::regex_constants::optimize), PaletteIndex(index) });
	}

	string list_regex(const vector<string>& tokens)
	{
		string r = "[";
		for(const string& token : tokens)
			r += "\\" + token;
		r += "]";
		return r;
	}

	LanguageDefinition& LanguageCpp()
	{
		static bool inited = false;
		static LanguageDefinition lang;
		if(!inited)
		{
			lang.m_punctuation = { "[", "]", "{", "}", "(", ")", ";", "," };

			lang.m_operators = { "+", "-", "*", "/", "=", "~", "|", "<", ">", "?", "/", ".", "!", "%", "^", "&" };

			static cstring keywords[] =
			{
				"alignas", "alignof", "and", "and_eq", "asm", "atomic_cancel", "atomic_commit", "atomic_noexcept", "auto", "bitand", "bitor", "bool", "break", "case", "catch", "char", "char16_t", "char32_t", "class",
				"compl", "concept", "const", "constexpr", "const_cast", "continue", "decltype", "default", "delete", "do", "double", "dynamic_cast", "else", "enum", "explicit", "export_", "extern", "false", "float",
				"for", "friend", "goto", "if", "import", "inline", "int", "long", "m", "mutable", "namespace", "new", "noexcept", "not", "not_eq", "nullptr", "operator", "or", "or_eq", "private", "protected", "public",
				"register", "reinterpret_cast", "requires", "return", "short", "signed", "sizeof", "static", "static_assert", "static_cast", "struct", "switch", "synchronized", "template", "this", "thread_local",
				"throw", "true", "try", "typedef", "typeid", "typename", "union", "unsigned", "using", "virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq"
			};

			static cstring identifiers[] =
			{
				"abort", "abs", "acos", "asin", "atan", "atexit", "atof", "atoi", "atol", "ceil", "clock", "cosh", "ctime", "div", "exit", "fabs", "floor", "fmod", "getchar", "getenv", "isalnum", "isalpha", "isdigit", "isgraph",
				"ispunct", "isspace", "isupper", "kbhit", "log10", "log2", "log", "memcmp", "modf", "pow", "printf", "sprintf", "snprintf", "putchar", "putenv", "puts", "rand", "remove", "rename", "sinh", "sqrt", "srand", "strcat", "strcmp", "strerror", "time", "tolower", "toupper",
				"std", "string", "vector", "map", "unordered_map", "set", "unordered_set", "min", "max"
			};

			builtin_keywords(lang, { keywords, size(keywords) });
			builtin_identifiers(lang, { identifiers, size(identifiers) });

			add_token_regex(lang, "//.*", CodePalette::Comment);
			add_token_regex(lang, "[ \t]*#[ \\t]*[a-zA-Z_]+", CodePalette::Preprocessor);
			add_token_regex(lang, "L?\\\"(\\\\.|[^\\\"])*\\\"", CodePalette::String);
			add_token_regex(lang, "\\'\\\\?[^\\']\\'", CodePalette::CharLiteral);
			add_token_regex(lang, "0[xX][0-9a-fA-F]+[uU]?[lL]?[lL]?", CodePalette::Number);
			add_token_regex(lang, "[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)([eE][+-]?[0-9]+)?[fF]?", CodePalette::Number);
			add_token_regex(lang, "0[0-7]+[Uu]?[lL]?[lL]?", CodePalette::Number);
			add_token_regex(lang, "[+-]?[0-9]+[Uu]?[lL]?[lL]?", CodePalette::Number);
			add_token_regex(lang, "[a-zA-Z_][a-zA-Z0-9_]*", CodePalette::Word);
			add_token_regex(lang, list_regex(lang.m_punctuation), CodePalette::Punctuation);
			add_token_regex(lang, list_regex(lang.m_operators), CodePalette::Operator);

			lang.m_comment_start = "/*";
			lang.m_comment_end = "*/";

			lang.m_case_sensitive = true;

			lang.m_name = "C++";

			inited = true;
		}
		return lang;
	}

	LanguageDefinition& LanguageHLSL()
	{
		static bool inited = false;
		static LanguageDefinition lang;
		if(!inited)
		{
			lang.m_punctuation = { "[", "]", "{", "}", "!", "%", "^", "&", "*", "(", ")", "-", "+", "=", "~", "|", "<", ">", "?", "/", ";", ",", ".]" };

			lang.m_operators = {};

			static cstring keywords[] =
			{
				"AppendStructuredBuffer", "asm", "asm_fragment", "BlendState", "bool", "break", "Buffer", "ByteAddressBuffer", "case", "cbuffer", "centroid", "class", "column_major", "compile", "compile_fragment",
				"CompileShader", "const", "continue", "ComputeShader", "ConsumeStructuredBuffer", "default", "DepthStencilState", "DepthStencilView", "discard", "do", "double", "DomainShader", "dword", "else",
				"export_", "extern", "false", "float", "for", "fxgroup", "GeometryShader", "groupshared", "half", "Hullshader", "if", "in", "inline", "inout", "InputPatch", "int", "interface", "line", "lineadj",
				"linear", "LineStream", "matrix", "min16float", "min10float", "min16int", "min12int", "min16uint", "namespace", "nointerpolation", "noperspective", "NULL", "out", "OutputPatch", "packoffset",
				"pass", "pixelfragment", "PixelShader", "point", "PointStream", "precise", "RasterizerState", "RenderTargetView", "return", "register", "row_major", "RWBuffer", "RWByteAddressBuffer", "RWStructuredBuffer",
				"RWTexture1D", "RWTexture1DArray", "RWTexture2D", "RWTexture2DArray", "RWTexture3D", "sample", "sampler", "SamplerState", "SamplerComparisonState", "shared", "snorm", "stateblock", "stateblock_state",
				"static", "string", "struct", "switch", "StructuredBuffer", "tbuffer", "technique", "technique10", "technique11", "texture", "Texture1D", "Texture1DArray", "Texture2D", "Texture2DArray", "Texture2DMS",
				"Texture2DMSArray", "Texture3D", "TextureCube", "TextureCubeArray", "true", "typedef", "triangle", "triangleadj", "TriangleStream", "uint", "uniform", "unorm", "unsigned", "vector", "vertexfragment",
				"VertexShader", "void", "volatile", "while",
				"bool1","bool2","bool3","bool4","double1","double2","double3","double4", "float1", "float2", "float3", "float4", "int1", "int2", "int3", "int4", "in", "out", "inout",
				"uint1", "uint2", "uint3", "uint4", "dword1", "dword2", "dword3", "dword4", "half1", "half2", "half3", "half4",
				"float1x1","float2x1","float3x1","float4x1","float1x2","float2x2","float3x2","float4x2",
				"float1x3","float2x3","float3x3","float4x3","float1x4","float2x4","float3x4","float4x4",
				"half1x1","half2x1","half3x1","half4x1","half1x2","half2x2","half3x2","half4x2",
				"half1x3","half2x3","half3x3","half4x3","half1x4","half2x4","half3x4","half4x4",
			};

			static cstring identifiers[] =
			{
				"abort", "abs", "acos", "all", "AllMemoryBarrier", "AllMemoryBarrierWithGroupSync", "any", "asdouble", "asfloat", "asin", "asint", "asint", "asuint",
				"asuint", "atan", "atan2", "ceil", "CheckAccessFullyMapped", "clamp", "clip", "cos", "cosh", "countbits", "cross", "D3DCOLORtoUBYTE4", "ddx",
				"ddx_coarse", "ddx_fine", "ddy", "ddy_coarse", "ddy_fine", "degrees", "determinant", "DeviceMemoryBarrier", "DeviceMemoryBarrierWithGroupSync",
				"distance", "dot", "dst", "errorf", "EvaluateAttributeAtCentroid", "EvaluateAttributeAtSample", "EvaluateAttributeSnapped", "exp", "exp2",
				"f16tof32", "f32tof16", "faceforward", "firstbithigh", "firstbitlow", "floor", "fma", "fmod", "frac", "frexp", "fwidth", "GetRenderTargetSampleCount",
				"GetRenderTargetSamplePosition", "GroupMemoryBarrier", "GroupMemoryBarrierWithGroupSync", "InterlockedAdd", "InterlockedAnd", "InterlockedCompareExchange",
				"InterlockedCompareStore", "InterlockedExchange", "InterlockedMax", "InterlockedMin", "InterlockedOr", "InterlockedXor", "isfinite", "isinf", "isnan",
				"ldexp", "length", "lerp", "lit", "log", "log10", "log2", "mad", "max", "min", "modf", "msad4", "mul", "noise", "normalize", "pow", "printf",
				"Process2DQuadTessFactorsAvg", "Process2DQuadTessFactorsMax", "Process2DQuadTessFactorsMin", "ProcessIsolineTessFactors", "ProcessQuadTessFactorsAvg",
				"ProcessQuadTessFactorsMax", "ProcessQuadTessFactorsMin", "ProcessTriTessFactorsAvg", "ProcessTriTessFactorsMax", "ProcessTriTessFactorsMin",
				"radians", "rcp", "reflect", "refract", "reversebits", "round", "rsqrt", "saturate", "sign", "sin", "sincos", "sinh", "smoothstep", "sqrt", "step",
				"tan", "tanh", "tex1D", "tex1D", "tex1Dbias", "tex1Dgrad", "tex1Dlod", "tex1Dproj", "tex2D", "tex2D", "tex2Dbias", "tex2Dgrad", "tex2Dlod", "tex2Dproj",
				"tex3D", "tex3D", "tex3Dbias", "tex3Dgrad", "tex3Dlod", "tex3Dproj", "texCUBE", "texCUBE", "texCUBEbias", "texCUBEgrad", "texCUBElod", "texCUBEproj", "transpose", "trunc"
			};

			builtin_keywords(lang, { keywords, size(keywords) });
			builtin_identifiers(lang, { identifiers, size(identifiers) });

			add_token_regex(lang, "//.*", CodePalette::Comment);
			add_token_regex(lang, "[ \t]*#[ \\t]*[a-zA-Z_]+", CodePalette::Preprocessor);
			add_token_regex(lang, "L?\\\"(\\\\.|[^\\\"])*\\\"", CodePalette::String);
			add_token_regex(lang, "\\'\\\\?[^\\']\\'", CodePalette::CharLiteral);
			add_token_regex(lang, "[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)([eE][+-]?[0-9]+)?[fF]?", CodePalette::Number);
			add_token_regex(lang, "[+-]?[0-9]+[Uu]?[lL]?[lL]?", CodePalette::Number);
			add_token_regex(lang, "0[0-7]+[Uu]?[lL]?[lL]?", CodePalette::Number);
			add_token_regex(lang, "0[xX][0-9a-fA-F]+[uU]?[lL]?[lL]?", CodePalette::Number);
			add_token_regex(lang, "[a-zA-Z_][a-zA-Z0-9_]*", CodePalette::Word);
			add_token_regex(lang, list_regex(lang.m_punctuation), CodePalette::Punctuation);
			add_token_regex(lang, list_regex(lang.m_operators), CodePalette::Operator);

			lang.m_comment_start = "/*";
			lang.m_comment_end = "*/";

			lang.m_case_sensitive = true;

			lang.m_name = "HLSL";

			inited = true;
		}
		return lang;
	}

	LanguageDefinition& LanguageGLSL()
	{
		static bool inited = false;
		static LanguageDefinition lang;
		if(!inited)
		{
			lang.m_punctuation = { "[", "]", "{", "}", "!", "%", "^", "&", "*", "(", ")", "-", "+", "=", "~", "|", "<", ">", "?", "/", ";", ",", "." };

			static cstring keywords[] =
			{
				"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long", "register", "restrict", "return", "short",
				"signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while", "_Alignas", "_Alignof", "_Atomic", "_Bool", "_Complex", "_Generic", "_Imaginary",
				"_Noreturn", "_Static_assert", "_Thread_local"
			};

			static cstring identifiers[] =
			{
				"abort", "abs", "acos", "asin", "atan", "atexit", "atof", "atoi", "atol", "ceil", "clock", "cosh", "ctime", "div", "exit", "fabs", "floor", "fmod", "getchar", "getenv", "isalnum", "isalpha", "isdigit", "isgraph",
				"ispunct", "isspace", "isupper", "kbhit", "log10", "log2", "log", "memcmp", "modf", "pow", "putchar", "putenv", "puts", "rand", "remove", "rename", "sinh", "sqrt", "srand", "strcat", "strcmp", "strerror", "time", "tolower", "toupper"
			};

			builtin_keywords(lang, { keywords, size(keywords) });
			builtin_identifiers(lang, { identifiers, size(identifiers) });

			add_token_regex(lang, "//.*", CodePalette::Comment);
			add_token_regex(lang, "[ \t]*#[ \\t]*[a-zA-Z_]+", CodePalette::Preprocessor);
			add_token_regex(lang, "L?\\\"(\\\\.|[^\\\"])*\\\"", CodePalette::String);
			add_token_regex(lang, "\\'\\\\?[^\\']\\'", CodePalette::CharLiteral);
			add_token_regex(lang, "[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)([eE][+-]?[0-9]+)?[fF]?", CodePalette::Number);
			add_token_regex(lang, "[+-]?[0-9]+[Uu]?[lL]?[lL]?", CodePalette::Number);
			add_token_regex(lang, "0[0-7]+[Uu]?[lL]?[lL]?", CodePalette::Number);
			add_token_regex(lang, "0[xX][0-9a-fA-F]+[uU]?[lL]?[lL]?", CodePalette::Number);
			add_token_regex(lang, "[a-zA-Z_][a-zA-Z0-9_]*", CodePalette::Word);
			add_token_regex(lang, list_regex(lang.m_punctuation), CodePalette::Punctuation);
			add_token_regex(lang, list_regex(lang.m_operators), CodePalette::Operator);

			lang.m_comment_start = "/*";
			lang.m_comment_end = "*/";

			lang.m_case_sensitive = true;

			lang.m_name = "GLSL";

			inited = true;
		}
		return lang;
	}

	LanguageDefinition& LanguageC()
	{
		static bool inited = false;
		static LanguageDefinition lang;
		if(!inited)
		{
			lang.m_punctuation = { "[", "]", "{", "}", "!", "%", "^", "&", "*", "(", ")", "-", "+", "=", "~", "|", "<", ">", "?", "/", ";", ",", "." };

			static cstring keywords[] =
			{
				"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long", "register", "restrict", "return", "short",
				"signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while", "_Alignas", "_Alignof", "_Atomic", "_Bool", "_Complex", "_Generic", "_Imaginary",
				"_Noreturn", "_Static_assert", "_Thread_local"
			};

			static cstring identifiers[] =
			{
				"abort", "abs", "acos", "asin", "atan", "atexit", "atof", "atoi", "atol", "ceil", "clock", "cosh", "ctime", "div", "exit", "fabs", "floor", "fmod", "getchar", "getenv", "isalnum", "isalpha", "isdigit", "isgraph",
				"ispunct", "isspace", "isupper", "kbhit", "log10", "log2", "log", "memcmp", "modf", "pow", "putchar", "putenv", "puts", "rand", "remove", "rename", "sinh", "sqrt", "srand", "strcat", "strcmp", "strerror", "time", "tolower", "toupper"
			};

			builtin_keywords(lang, { keywords, size(keywords) });
			builtin_identifiers(lang, { identifiers, size(identifiers) });

			add_token_regex(lang, "//.*", CodePalette::Comment);
			add_token_regex(lang, "[ \t]*#[ \\t]*[a-zA-Z_]+", CodePalette::Preprocessor);
			add_token_regex(lang, "L?\\\"(\\\\.|[^\\\"])*\\\"", CodePalette::String);
			add_token_regex(lang, "\\'\\\\?[^\\']\\'", CodePalette::CharLiteral);
			add_token_regex(lang, "[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)([eE][+-]?[0-9]+)?[fF]?", CodePalette::Number);
			add_token_regex(lang, "[+-]?[0-9]+[Uu]?[lL]?[lL]?", CodePalette::Number);
			add_token_regex(lang, "0[0-7]+[Uu]?[lL]?[lL]?", CodePalette::Number);
			add_token_regex(lang, "0[xX][0-9a-fA-F]+[uU]?[lL]?[lL]?", CodePalette::Number);
			add_token_regex(lang, "[a-zA-Z_][a-zA-Z0-9_]*", CodePalette::Word);
			add_token_regex(lang, list_regex(lang.m_punctuation), CodePalette::Punctuation);
			add_token_regex(lang, list_regex(lang.m_operators), CodePalette::Operator);

			lang.m_comment_start = "/*";
			lang.m_comment_end = "*/";

			lang.m_case_sensitive = true;

			lang.m_name = "C";

			inited = true;
		}
		return lang;
	}

	LanguageDefinition& LanguageLua()
	{
		static bool inited = false;
		static LanguageDefinition lang;
		if(!inited)
		{
			lang.m_punctuation = { "[", "]", "{", "}", "!", "%", "^", "&", "*", "(", ")", "-", "+", "=", "~", "|", "<", ">", "?", "/", ";", ",", "." };

			static cstring keywords[] =
			{
				"and", "break", "do", "", "else", "elseif", "end", "false", "for", "function", "if", "in", "", "local", "nil", "not", "or", "repeat", "return", "then", "true", "until", "while"
			};

			static cstring identifiers[] =
			{
				"_G",  "_VERSION", "coroutine", "table", "io", "os", "string", "utf8", "bit32", "math", "debug", "package"
			};

			static cstring functions[] =
			{
				"assert", "collectgarbage", "dofile", "error", "getmetatable", "ipairs", "loadfile", "load", "loadstring",  "next",  "pairs",  "pcall",  "print",  "rawequal",  "rawlen",  "rawget",  "rawset",
				"select",  "setmetatable",  "tonumber",  "tostring",  "type",  "xpcall", "arshift", "band", "bnot", "bor", "bxor", "btest", "extract", "lrotate", "lshift", "replace",
				"rrotate", "rshift", "create", "resume", "running", "status", "wrap", "yield", "isyieldable", "debug","getuservalue", "gethook", "getinfo", "getlocal", "getregistry", "getmetatable",
				"getupvalue", "upvaluejoin", "upvalueid", "setuservalue", "sethook", "setlocal", "setmetatable", "setupvalue", "traceback", "close", "flush", "input", "lines", "open", "output", "popen",
				"read", "tmpfile", "type", "write", "close", "flush", "lines", "read", "seek", "setvbuf", "write", "__gc", "__tostring", "abs", "acos", "asin", "atan", "ceil", "cos", "deg", "exp", "tointeger",
				"floor", "fmod", "ult", "log", "max", "min", "modf", "rad", "random", "randomseed", "sin", "sqrt", "string", "tan", "type", "atan2", "cosh", "sinh", "tanh",
				"pow", "frexp", "ldexp", "log10", "pi", "huge", "maxinteger", "mininteger", "loadlib", "searchpath", "seeall", "preload", "cpath", "path", "searchers", "loaded", "m", "require", "clock",
				"date", "difftime", "execute", "exit", "getenv", "remove", "rename", "setlocale", "time", "tmpname", "byte", "char", "dump", "find", "format", "gmatch", "gsub", "len", "lower", "match", "rep",
				"reverse", "sub", "upper", "pack", "packsize", "unpack", "concat", "maxn", "insert", "pack", "unpack", "remove", "move", "sort", "offset", "codepoint", "char", "len", "codes", "charpattern"
			};

			builtin_keywords(lang, { keywords, size(keywords) });
			builtin_identifiers(lang, { identifiers, size(identifiers) });
			builtin_functions(lang, { functions, size(functions) });

			add_token_regex(lang, "\\-\\-.*", CodePalette::Comment);
			add_token_regex(lang, "L?\\\"(\\\\.|[^\\\"])*\\\"", CodePalette::String);
			add_token_regex(lang, "\\\'[^\\\']*\\\'", CodePalette::String);
			add_token_regex(lang, "0[xX][0-9a-fA-F]+[uU]?[lL]?[lL]?", CodePalette::Number);
			add_token_regex(lang, "[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)([eE][+-]?[0-9]+)?[fF]?", CodePalette::Number);
			add_token_regex(lang, "[+-]?[0-9]+[Uu]?[lL]?[lL]?", CodePalette::Number);
			add_token_regex(lang, "[a-zA-Z_][a-zA-Z0-9_]*", CodePalette::Word);
			add_token_regex(lang, list_regex(lang.m_punctuation), CodePalette::Punctuation);
			add_token_regex(lang, list_regex(lang.m_operators), CodePalette::Operator);

			lang.m_comment_start = "\\-\\-\\[\\[";
			lang.m_comment_end = "\\]\\]";

			lang.m_case_sensitive = true;

			lang.m_name = "Lua";

			inited = true;
		}
		return lang;
	}

	LanguageDefinition& LanguageWren()
	{
		static bool inited = false;
		static LanguageDefinition lang;
		if(!inited)
		{
			lang.m_punctuation = { "{", "}", "(", ")", ",", "." };

			lang.m_operators = { "[", "]", "!", "%", "^", "&", "*", "-", "+", "=", "~", "|", "<", ">", "?", "/", ":", ";" };

			static cstring keywords[] =
			{
				"class", "construct", "continue", "else", "false", "for", "foreign", "if", "import", "in", "is", "new", "null", "return", "static", "this", "true", "var", "while"
			};

			builtin_keywords(lang, { keywords, size(keywords) });

			add_token_regex(lang, "//.*", CodePalette::Comment);
			add_token_regex(lang, "[A-Z][a-zA-Z0-9_]*", CodePalette::Identifier);
			add_token_regex(lang, "[_][a-zA-Z0-9_]*", CodePalette::Field);
			add_token_regex(lang, "[a-z0-9_]+(?=\\()", CodePalette::Function);
			add_token_regex(lang, "[a-zA-Z_][a-zA-Z0-9_]*", CodePalette::Word);
			add_token_regex(lang, list_regex(lang.m_punctuation), CodePalette::Punctuation);
			add_token_regex(lang, list_regex(lang.m_operators), CodePalette::Operator);
			add_token_regex(lang, "L?\\\"(\\\\.|[^\\\"])*\\\"", CodePalette::String);
			add_token_regex(lang, "\\'\\\\?[^\\']\\'", CodePalette::CharLiteral);
			add_token_regex(lang, "0[xX][0-9a-fA-F]+[uU]?[lL]?[lL]?", CodePalette::Number);
			add_token_regex(lang, "[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)([eE][+-]?[0-9]+)?[fF]?", CodePalette::Number);
			add_token_regex(lang, "0[0-7]+[Uu]?[lL]?[lL]?", CodePalette::Number);
			add_token_regex(lang, "[+-]?[0-9]+[Uu]?[lL]?[lL]?", CodePalette::Number);

			lang.m_comment_start = "/*";
			lang.m_comment_end = "*/";

			lang.m_case_sensitive = true;

			lang.m_name = "Wren";

			inited = true;
		}
		return lang;
	}
}

#ifndef MUD_CPP_20
#include <cctype>
#include <locale>
#include <chrono>
#include <stl/string.h>
#include <regex>
#include <cmath>
#endif

#ifdef MUD_MODULES
module mud.ui;
#else
#endif

namespace mud
{
	inline TextPaint style_text_paint(InkStyle& inkstyle)
	{
		return { inkstyle.m_text_font.c_str(), inkstyle.m_text_colour, inkstyle.m_text_size, inkstyle.m_align, inkstyle.m_text_break, inkstyle.m_text_wrap };
	}

	bool is_separator(char c)
	{
		string separators = " .,:;+-*=~!()[]{}'\"\t\n";
		return separators.find(c) != string::npos;
	}

	size_t word_begin(const string& text, size_t index)
	{
		size_t begin = SIZE_MAX;
		for(int pos = int(index); pos >= 0 && !is_separator(text[pos]); --pos)
			begin = size_t(pos);
		return begin;
	}

	size_t word_end(const string& text, size_t index)
	{
		size_t end = SIZE_MAX;
		for(size_t pos = index; pos < text.size() && !is_separator(text[pos]); ++pos)
			end = pos;
		return end;
	}

	string word_at(const string& text, size_t index)
	{
		size_t begin = word_begin(text, index);
		size_t end = word_end(text, index);
		return (begin != SIZE_MAX && end != SIZE_MAX) ? text.substr(begin, end + 1 - begin) : "";
	}

	size_t line_begin(const string& text, size_t index)
	{
		size_t begin = index;
		for(; text[begin - 1] != '\n' && begin > 0; --begin)
			;
		return begin;

	}

	size_t line_end(const string& text, size_t index)
	{
		size_t end = index;
		for(; text[end] != '\n' && end < text.size() - 1; ++end)
			;
		return end;
	}

	string text_line(const string& text, size_t index)
	{
		size_t begin = line_begin(text, index);
		size_t end = line_end(text, index);
		return text.substr(begin, end + 1 - begin);
	}

	size_t text_column(const string& text, size_t index)
	{
		return index - line_begin(text, index);
	}

	void replace_tabs(string& text, size_t tab_size)
	{
		for(size_t i = 0; i < text.size(); ++i)
			if(text[i] == '\t')
			{
				size_t num = tab_size - i % tab_size;
				for(size_t j = num; j > 0; --j)
					text.push_back(' ');
				i += num;
			}
	}

	Vg* Text::s_vg = nullptr;

	Text::Text(Frame& frame)
		: m_frame(frame)
		, m_text()
		, m_num_lines(0)
	{}

	void Text::set_lines(size_t lines)
	{
		m_num_lines = lines;
		//d_frame.mark_dirty(DIRTY_LAYOUT);
	}

	void Text::set_text(const string& text)
	{
		if(m_text == text) return;
		m_text = text;
		this->break_text_rows();
	}

	float Text::line_height() const
	{
		return s_vg->line_height(m_text_paint);
	}

	vec2 Text::compute_text_size()
	{
		return { compute_width(), compute_height() };
	}
	
	float Text::compute_height() const
	{
		if(m_num_lines)
			return line_height() * m_num_lines;
		else if(!m_text_rows.empty())
			return m_text_rows.back().m_rect.y + rect_h(m_text_rows.back().m_rect);
		else
			return 0.f;
	}

	float Text::compute_width() const
	{
		float result = 0.f;
		for(const TextRow& row : m_text_rows)
			result = max(result, rect_w(row.m_rect));
		return result;
	}

	void Text::break_text_rows()
	{
		vec2 padded_size = floor(m_frame.m_size - rect_sum(m_frame.d_inkstyle->m_padding));

		if(!m_text.empty())
			s_vg->break_text(m_text.c_str(), m_text.size(), padded_size, m_text_paint, m_text_rows);
		else
			m_text_rows.clear();
	}

	size_t Text::char_at(const vec2& pos) const
	{
		const char* start = m_text.c_str();
		const char* end = start + m_text.size();// - 1;

		size_t imarker = 0;
		size_t line = 0;
		float offset = 0.f;
		float line_height = s_vg->line_height(m_text_paint);

		for(const TextRow& row : m_text_rows)
		{
			if(imarker < m_markers.size() && m_markers[imarker].m_line == line)
			{
				offset += line_height;
				imarker++;
			}

			if(pos.y < offset + row.m_rect.y + rect_h(row.m_rect)) // pos.y >= row.m_rect.y && 
			{
				for(const TextGlyph& glyph : row.m_glyphs)
					if(pos.x < glyph.m_rect.x + rect_w(glyph.m_rect) * 0.5f) // pos.x >= glyph.m_rect.x &&
						return glyph.m_position - start;

				return row.m_end - start;
			}

			line++;
		}

		return end - start - 1;
	}

	vec4 Text::interval_rect(const TextRow& row, size_t start, size_t end) const
	{
		const TextGlyph& start_glyph = row.m_glyphs[start - row.m_start_index];
		const TextGlyph& end_glyph = row.m_glyphs[end - row.m_start_index];

		return { start_glyph.m_rect.x, row.m_rect.y, end_glyph.m_rect.x + rect_w(end_glyph.m_rect) - start_glyph.m_rect.x, rect_h(row.m_rect) };
	}

	vec4 Text::interval_rect(size_t start, size_t end) const
	{
		const TextRow& row = this->text_row_at(start);
		return this->interval_rect(row, start, end);
	}

	TextCursor Text::cursor_at(const vec2& pos) const
	{
		size_t index = this->char_at(pos);
		return this->to_cursor(index);
	}

	vec4 Text::cursor_rect(size_t index) const
	{
		const TextRow& row = text_row_at(index);

		if(index != row.m_end_index)
		{
			size_t offset = row.m_start - m_text.c_str();
			return row.m_glyphs[index - offset].m_rect;
		}
		else
		{
			return { vec2{ row.m_rect.x + rect_w(row.m_rect), row.m_rect.y }, vec2{ 1.f, line_height() } };
		}
	}

	size_t Text::text_row_index(size_t index) const
	{
		for(size_t i = 0; i < m_text_rows.size(); ++i)
			if(index <= m_text_rows[i].m_end_index)
				return i;
		return 0;
	}

	const TextRow& Text::text_row_at(size_t index) const
	{
		return m_text_rows[text_row_index(index)];
	}

	TextCursor Text::to_cursor(size_t index) const
	{
		size_t row = this->text_row_index(index);
		size_t column = m_text_rows.empty() ? 0U : index - m_text_rows[row].m_start_index;
		return { index, { uint(column), uint(row) } };
	}

	TextCursor Text::to_cursor(const uvec2& grid_index) const
	{
		size_t index = m_text_rows[grid_index.y].m_start_index + grid_index.x;
		return { index, grid_index };
	}

	TextCursor Text::clamp_cursor(int index) const
	{
		int clamped = max(0, min(int(m_text.size()) - 1, index));
		return to_cursor(clamped);
	}

	TextCursor Text::clamp_cursor(const ivec2& grid_index) const
	{
		int line = max(0, min(int(m_text_rows.size()) - 1, grid_index.y));
		int column = m_text_rows.empty() ? 0 : min(int(m_text_rows[line].m_glyphs.size()), grid_index.x);
		size_t index = m_text_rows[line].m_start_index + column;
		return { index, uvec2(grid_index) };
		//return to_cursor({ uint(column), uint(line) });
	}

	TextEdit::TextEdit(Widget* parent, void* identity, bool editor, string allowed_chars)
		: Widget(parent, identity)
		, m_editor(editor)
		, m_text(m_frame)
		, m_string(m_text.m_text)
		, m_dirty(0, uint(m_string.size()))
		, m_allowed_chars(allowed_chars)
	{
		m_palette = to_array(OkaidaPalette());
	}

	TextEdit::~TextEdit()
	{}

	size_t TextEdit::visible_lines() const
	{
		const Frame& scroll_frame = m_frame;
		float height = scroll_frame.m_size.y - 20.0f;
		return size_t(floor(height / m_text.line_height()));
	}

	vec2 TextEdit::frame_size()
	{
		auto count_digits = [](int number) { int digits = 0; do { number /= 10; digits++; } while(number != 0); return digits; };
		int digits = count_digits(int(m_text.m_text_rows.size()));
		vec2 offset = { m_text.line_height() * float(digits) * 0.7f, 0.f };

		return offset + m_text.compute_text_size() + rect_sum(m_frame.d_inkstyle->m_padding);
	}

	void TextEdit::update_style()
	{
		m_text.m_text_paint = style_text_paint(*m_frame.d_inkstyle);

		if(m_editor)
		{
			m_text.m_text_paint.m_font = "consolas";
			m_text.m_text_paint.m_size = 14.f;
		}

		auto count_digits = [](int number) { int digits = 0; do { number /= 10; digits++; } while (number != 0); return digits; };
		int digits = count_digits(int(m_text.m_text_rows.size()));

		vec2 padding = floor(rect_offset(m_frame.d_inkstyle->m_padding));
		if(m_editor)
			m_text_offset = padding + vec2{ m_text.line_height() * float(digits) * 0.7f, 0.f };
		else
			m_text_offset = padding;
	}

	void TextEdit::set_text(const string& text)
	{
		if(m_string == text) return;

		m_text.set_text(text);

		m_selection.m_cursor = m_text.to_cursor(min(size_t(m_selection.m_cursor), text.size()));
		m_selection.m_start = min(size_t(m_selection.m_start), text.size());
		m_selection.m_end = min(size_t(m_selection.m_end), text.size());

		printf("WARNING: undo/redo won't work after this\n");
		//mUndoBuffer.clear();

		mark_dirty(0, m_string.size());
	}

	void TextEdit::changed()
	{
		m_changed = true;
	}

	void TextEdit::mark_dirty(size_t start, size_t end)
	{
		m_dirty[0] = min<uint>(m_dirty[0], uint(start));
		m_dirty[1] = max<uint>(m_dirty[1], uint(end));
		m_text.break_text_rows();
		this->changed();
	}

	void TextEdit::clear(size_t start, size_t end)
	{
		vector_remove_if(m_text.m_sections, [&](Text::ColorSection& section) { return section.m_end >= start && section.m_start <= end; });
	}

	void TextEdit::shift(size_t start, int offset)
	{
		for(Text::ColorSection& section : m_text.m_sections)
		{
			if(section.m_start > start)
				section.m_start += offset;
			if(section.m_end > start)
				section.m_end += offset;
		}
	}

	void TextEdit::insert(size_t index, const string& text)
	{
		this->shift(index, int(text.size()));
		m_string.insert(index, text);
		this->mark_dirty(line_begin(m_string, index), line_end(m_string, index + text.size()));
		m_follow_cursor = true;
	}

	void TextEdit::insert(size_t index, const string& text, size_t cursor, Action& action)
	{
		action.mAdded = text;
		action.mAddedStart = index;
		action.mAddedEnd = index + text.size();

		this->insert(index, text);
		this->cursor(cursor);
	}

	void TextEdit::erase(size_t start, size_t end)
	{
		if(end == start) return;
		this->clear(start, end);
		this->shift(start, int(start - end));
		m_string.erase(start, end - start);
		this->mark_dirty(line_begin(m_string, start), line_end(m_string, start));
		m_follow_cursor = true;
	}

	void TextEdit::erase(size_t start, size_t end, size_t cursor, Action& action)
	{
		action.mRemoved = m_string.substr(start, end - start);
		action.mRemovedStart = start;
		action.mRemovedEnd = end;

		this->erase(start, end);
		this->cursor(cursor);
	}

	void TextEdit::enter()
	{
		if(allowed('\n'))
		{
			this->insert('\n');
			m_entered = true;
		}
	}

	void TextEdit::escape()
	{
		if(m_completing)
			m_completing = false;
		else
			this->yield_focus();
	}

	void TextEdit::erase_selected(Action& action)
	{
		erase(m_selection.m_start, m_selection.m_end, m_selection.m_start, action);
	}

	void TextEdit::erase()
	{
		if(m_string.empty()) return;

		CommitAction([&](Action& action)
		{
			if(has_selection())
				erase_selected(action);
			else
				erase(m_selection.m_cursor, m_selection.m_cursor + 1, m_selection.m_cursor, action);
		});
	}

	void TextEdit::backspace()
	{
		if(m_string.empty()) return;

		CommitAction([&](Action& action)
		{
			if(has_selection())
				erase_selected(action);
			else if(m_selection.m_cursor > 0)
				erase(m_selection.m_cursor - 1, m_selection.m_cursor, m_selection.m_cursor - 1, action);
		});

		m_completing = m_completing && !is_separator(m_string[m_selection.m_cursor - 1]);
	}

	void TextEdit::insert(unsigned char c)
	{
		if(c == 0 || (!isprint(c) && !isspace(c)) || !allowed(c)) return;
		if(c == '\r') c = '\n';

		char last = m_selection.m_cursor < m_string.size() ? m_string[m_selection.m_cursor - 1] : 0;
		m_completing &= !is_separator(c);
		m_completing |= (last == 0 || is_separator(last)) && !is_separator(c);

		CommitAction([&](Action& action)
		{
			if(has_selection())
				erase_selected(action);

			char cc = c;
			insert(m_selection.m_cursor, string(&cc, 1), m_selection.m_cursor + 1, action);
		});
	}

	void TextEdit::insert(const string& text)
	{
		CommitAction([&](Action& action)
		{
			if(has_selection())
				erase_selected(action);

			insert(m_selection.m_cursor, text, m_selection.m_cursor + text.size(), action);
		});
	}

	string TextEdit::selected_text() const
	{
		return m_string.substr(m_selection.m_start, m_selection.m_end - m_selection.m_start);
	}

	void TextEdit::copy()
	{
		Clipboard& clipboard = this->ui_window().m_clipboard;
		if(has_selection())
			clipboard = { selected_text(), false };
		else
			clipboard = { text_line(m_string, m_selection.m_cursor), true };
	}

	void TextEdit::cut()
	{
		if(m_read_only) return;

		CommitAction([&](Action& action)
		{
			copy();
			if(has_selection())
				erase_selected(action);
			else
				erase(line_begin(m_string, m_selection.m_cursor), line_end(m_string, m_selection.m_cursor) + 1, m_selection.m_cursor, action);
		});
	}

	void TextEdit::paste()
	{
		Clipboard& clipboard = this->ui_window().m_clipboard;
		if(clipboard.m_text.empty()) return;

		CommitAction([&](Action& action)
		{
			if(has_selection())
				erase_selected(action);

			if(clipboard.m_line_mode)
				insert(line_begin(m_string, m_selection.m_cursor), clipboard.m_text, m_selection.m_cursor + clipboard.m_text.size(), action);
			else
				insert(m_selection.m_cursor, clipboard.m_text, m_selection.m_cursor + clipboard.m_text.size(), action);
		});

		m_entered = true;
	}

	void TextEdit::select(size_t first, size_t second, bool word_mode)
	{
		m_selection.m_start = min(first, second);
		m_selection.m_end = max(first, second);

		m_completing = false;
		m_follow_cursor = true;

		if(word_mode)
		{
			m_selection.m_start = word_begin(m_string, m_selection.m_start);
			m_selection.m_end = word_end(m_string, m_selection.m_end);
		}
	}

	void TextEdit::cursor(size_t caret, bool word_mode)
	{
		this->select(caret, caret, word_mode);
		m_selection.m_cursor = m_text.to_cursor(word_mode ? m_selection.m_end : caret);
	}

	void TextEdit::move_select(TextCursor dest, bool select, bool word_mode)
	{
		if(select)
		{
			if(m_select_from.m_index == SIZE_MAX)
				m_select_from = m_selection.m_cursor;
			this->select(m_select_from, dest, select && word_mode);
		}
		else
		{
			m_select_from = {};
			this->select(dest, dest, select && word_mode);
		}

		m_selection.m_cursor = dest;
		m_follow_cursor = true;
	}

	void TextEdit::move_up(bool select)
	{
		this->move_select(m_text.clamp_cursor(ivec2(m_selection.m_cursor.m_grid_index) - ivec2(0, 1)), select);
	}

	void TextEdit::move_down(bool select)
	{
		this->move_select(m_text.clamp_cursor(ivec2(m_selection.m_cursor.m_grid_index) + ivec2(0, 1)), select);
	}

	void TextEdit::move_page_up(bool select)
	{
		this->move_select(m_text.clamp_cursor(ivec2(m_selection.m_cursor.m_grid_index) - ivec2(0, int(visible_lines()) - 4)), select);
	}

	void TextEdit::move_page_down(bool select)
	{
		this->move_select(m_text.clamp_cursor(ivec2(m_selection.m_cursor.m_grid_index) + ivec2(0, int(visible_lines()) - 4)), select);
	}

	void TextEdit::move_left(size_t count, bool select, bool word_mode)
	{
		this->move_select(m_text.clamp_cursor(int(m_selection.m_cursor - count)), select, select && word_mode);
	}

	void TextEdit::move_right(size_t count, bool select, bool word_mode)
	{
		this->move_select(m_text.clamp_cursor(int(m_selection.m_cursor + count)), select, select && word_mode);
	}
	
	void TextEdit::move_top(bool select)
	{
		this->move_select(m_text.to_cursor(0U), select);
	}

	void TextEdit::move_bottom(bool select)
	{
		this->move_select(m_text.to_cursor(m_string.size()), select);
	}

	void TextEdit::move_home(bool select)
	{
		this->move_select(m_text.to_cursor(line_begin(m_string, m_selection.m_cursor)), select);
	}

	void TextEdit::move_end(bool select)
	{
		this->move_select(m_text.to_cursor(line_end(m_string, m_selection.m_cursor)), select);
	}

	void TextEdit::select_none()
	{
		this->cursor(0U);
	}

	void TextEdit::select_all()
	{
		this->select(0U, m_string.size());
	}

	void TextEdit::select_word()
	{
		this->select(word_begin(m_string, m_selection.m_cursor), word_end(m_string, m_selection.m_cursor));
	}

	void TextEdit::AddUndo(Action& aValue)
	{
		m_undo_stack.resize(m_undo_index + 1);
		m_undo_stack.back() = aValue;
		++m_undo_index;
	}

	void TextEdit::update()
	{
		m_changed = false;
		m_entered = false;

		EventType event_focus = m_focus_mode == TextFocusMode::Press ? EventType::Pressed
																	 : EventType::Stroked;
		if(!this->focused())
			if(MouseEvent mouse_event = this->mouse_event(DeviceType::MouseLeft, event_focus, InputMod::None, false))
			{
				take_focus();
				this->cursor(0);
			}

		bool shift = this->ui().m_keyboard.m_shift;
		bool ctrl = this->ui().m_keyboard.m_ctrl;
		bool alt = this->ui().m_keyboard.m_alt;
		
		if(MouseEvent mouse_event = this->mouse_event(DeviceType::Mouse, EventType::Heartbeat))
		{
			size_t index = m_text.char_at(mouse_event.m_relative - m_text_offset);
			m_hovered_word = word_at(m_string, index);
			if(m_hovered_word != "")
			{
				m_hovered_word_rect = m_text.interval_rect(word_begin(m_string, index), word_end(m_string, index));
				m_hovered_word_rect = { rect_offset(m_hovered_word_rect) + m_text_offset, rect_size(m_hovered_word_rect) };
			}

			this->ui().m_cursor_style = &ui::cursor_styles().caret;
		}
		
		if(!m_completing && !ctrl && !alt && this->key_stroke(Key::Up))
			move_up(shift);
		else if(!m_completing && !ctrl && !alt && this->key_stroke(Key::Down))
			move_down(shift);
		else if(!alt && this->key_stroke(Key::Left))
			move_left(1U, shift, ctrl);
		else if(!alt && this->key_stroke(Key::Right))
			move_right(1U, shift, ctrl);
		else if(!alt && this->key_stroke(Key::PageUp))
			move_page_up(shift);
		else if(!alt && this->key_stroke(Key::PageDown))
			move_page_down(shift);
		else if(ctrl && !alt && this->key_stroke(Key::Home))
			move_top(shift);
		else if(ctrl && !alt && this->key_stroke(Key::End))
			move_bottom(shift);
		else if(!ctrl && !alt && this->key_stroke(Key::Home))
			move_home(shift);
		else if(!ctrl && !alt && this->key_stroke(Key::End))
			move_end(shift);
		else if(!m_read_only && this->key_stroke(Key::Delete))
			erase();
		else if(!m_read_only && this->key_stroke(Key::Back))
			backspace();
		else if(this->key_stroke(Key::Insert, InputMod::None))
			m_selection.m_insert_mode = !m_selection.m_insert_mode;
		else if(this->key_stroke(Key::Insert, InputMod::Ctrl)
			 || this->char_stroke(Key::C, InputMod::Ctrl))
			copy();
		else if(!m_read_only && (this->key_stroke(Key::Insert, InputMod::Shift)
							  || this->char_stroke(Key::V, InputMod::Ctrl)))
			paste();
		else if(this->char_stroke(Key::X, InputMod::Ctrl)
			 || this->key_stroke(Key::Delete, InputMod::Shift))
			cut();
		else if(this->char_stroke(Key::A, InputMod::Ctrl))
			select_all();
		else if(key_stroke(Key::Return))
			enter();
		else if(key_stroke(Key::Escape))
			escape();
		else if(key_stroke(Key::Tab) && !m_completing)
			insert(string(m_tab_size, ' '));
		else if(!m_read_only && (!ctrl || alt))
		{
			KeyEvent stroke = key_stroke(Key::Unassigned);
			if(stroke)
				insert(stroke.m_char);
		}
		
		if(!m_read_only && (this->char_stroke(Key::Z, InputMod::Ctrl)
						 || this->key_stroke(Key::Back, InputMod::Alt)))
			undo();
		if(!m_read_only && this->char_stroke(Key::Y, InputMod::Ctrl))
			redo();

		Clipboard& clipboard = this->ui_window().m_clipboard;
		if(clipboard.m_pasted.size() > 0)
		{
			clipboard.m_text = pop(clipboard.m_pasted);
			clipboard.m_line_mode = false;
			this->paste();
		}

		if(this->focused() && !shift && !alt)
		{
			if(MouseEvent mouse_event = this->mouse_event(DeviceType::MouseLeft, EventType::Pressed))
			{
				m_select_from = m_text.cursor_at(mouse_event.m_relative - m_text_offset);
				this->cursor(m_select_from, ctrl);
			}
			if(MouseEvent mouse_event = this->mouse_event(DeviceType::MouseLeft, EventType::Pressed, InputMod::Ctrl))
			{
				m_select_from = m_text.cursor_at(mouse_event.m_relative - m_text_offset);
				m_word_selection_mode = true;
				this->cursor(m_select_from, true);
			}
			if(MouseEvent mouse_event = this->mouse_event(DeviceType::MouseLeft, EventType::Released))
			{
				if(!focused())
					this->select_all();
			}
			if(MouseEvent mouse_event = this->mouse_event(DeviceType::MouseLeft, EventType::DoubleStroked))
			{
				TextCursor cursor = m_text.cursor_at(mouse_event.m_relative - m_text_offset);
				this->cursor(cursor, true);
			}
			if(MouseEvent mouse_event = this->mouse_event(DeviceType::MouseLeft, EventType::Dragged))
			{
				TextCursor cursor = m_text.cursor_at(mouse_event.m_relative - m_text_offset);
				this->select(m_select_from, cursor, m_word_selection_mode);
				m_selection.m_cursor = cursor;
			}
		}

		if(!this->mouse_event(DeviceType::MouseLeft, EventType::Pressed))
			m_word_selection_mode = false;

		m_frame.layer().setForceRedraw(); // TextEdit must redraw each frame
	}

	void TextEdit::update_scroll(Frame& frame, Frame& content)
	{
		if(MouseEvent mouse_event = this->mouse_event(DeviceType::MouseMiddle, EventType::Moved))
		{
			float overflow = content.m_size.y - frame.m_size.y;
			content.m_position.y += mouse_event.m_deltaZ * 22.f * 3.f;
			content.m_position.y = min(0.f, max(content.m_position.y, -overflow));
		}

		if(m_follow_cursor)
		{
			scroll_to_cursor(frame, content);
			m_follow_cursor = false;
		}
	}
	
	Colour palette_colour(const ColourPalette& palette, PaletteIndex color_index)
	{
		return from_rgba(palette[color_index]);
	}

	Paint palette_paint(const ColourPalette& palette, PaletteIndex color_index)
	{
		return { from_rgba(palette[color_index]) };
	}

	TextPaint palette_text_paint(const Text& text, const ColourPalette& palette, PaletteIndex color_index)
	{
		TextPaint paint = text.m_text_paint;
		paint.m_colour = from_rgba(palette[color_index]);
		return paint;
	}

	void draw_text(Vg& vg, const vec2& padding, const Text& text)
	{
		for(const TextRow& row : text.m_text_rows)
			vg.draw_text(padding + rect_offset(row.m_rect), row.m_start, row.m_end, text.m_text_paint);
	}

	void draw_editor_text(Vg& vg, const Frame& frame, const vec2& padding, const vec2& text_offset, const Text& text, const ColourPalette& palette)
	{
		char line_number[16];

		size_t line = 0;
		size_t isection = 0;
		size_t imarker = 0;

		vec2 offset = vec2(0.f);
		float line_height = vg.line_height(text.m_text_paint);

		for(const TextRow& row : text.m_text_rows)
		{
			while(isection < text.m_sections.size() && text.m_sections[isection].m_start < row.m_start_index)
				isection++;

			snprintf(line_number, 16, "%6d", int(++line));
			vg.draw_text(padding + offset + rect_offset(row.m_rect), line_number, nullptr, palette_text_paint(text, palette, Text::LineNumber));

			while(isection < text.m_sections.size() && text.m_sections[isection].m_start < row.m_end_index)
			{
				const Text::ColorSection& section = text.m_sections[isection];

				vec2 position = offset + text_offset + rect_offset(row.m_glyphs[section.m_start - row.m_start_index].m_rect);
				const char* front = &text.m_text.front();
				vg.draw_text(floor(position) + vec2(0.f, 0.5f), front + section.m_start, front + section.m_end, palette_text_paint(text, palette, section.m_colour));

				isection++;
			}

			if(imarker < text.m_markers.size() && text.m_markers[imarker].m_line == line)
			{
				vec4 rect = { offset + padding + vec2{ 0.f, row.m_rect.y + line_height }, vec2{ frame.m_size.x, text.line_height() } };
				vec2 position = offset + text_offset + rect_offset(row.m_rect) + line_height;

				vg.draw_rect(rect, palette_paint(palette, text.m_markers[imarker].m_highlight));
				vg.draw_text(floor(position) + vec2(0.f, 2.5f), text.m_markers[imarker].m_message.c_str(), nullptr, palette_text_paint(text, palette, text.m_markers[imarker].m_colour));
				
				offset += vec2(0.f, line_height);

				imarker++;
			}
		}
	}

	void draw_text_selection(Vg& vg, const Frame& frame, const vec2& padding, const vec2& text_offset, const Text& text, const TextSelection& selection, const ColourPalette& palette, bool current_line)
	{
		if(text.m_text_rows.empty())
			return;

		size_t line = 0;
		size_t imarker = 0;

		vec2 offset = vec2(0.f);
		float line_height = vg.line_height(text.m_text_paint);

		for(const TextRow& row : text.m_text_rows)
		{
			line++;

			if(selection.m_start != selection.m_end && row.m_end_index > selection.m_start && row.m_start_index < selection.m_end)
			{
				if(row.m_glyphs.empty())
				{
					vg.draw_rect({ offset + text_offset + rect_offset(row.m_rect), vec2{ 5.f, rect_h(row.m_rect) } }, palette_paint(palette, Text::Selection));
					continue;
				}

				size_t select_start = max(row.m_start_index, size_t(selection.m_start));
				size_t select_end = min(row.m_end_index, size_t(selection.m_end));

				vec4 row_rect = text.interval_rect(row, select_start, select_end - 1);
				vg.draw_rect({ offset + text_offset + rect_offset(row_rect), rect_size(row_rect) }, palette_paint(palette, Text::Selection));
			}

			if(selection.m_cursor >= row.m_start_index && selection.m_cursor <= row.m_end_index)
			{
				if(current_line && selection.m_start == selection.m_end)
				{
					bool focused = false;
					vec4 rect = { offset + padding + vec2{ 0.f, row.m_rect.y }, vec2{ frame.m_size.x, text.line_height() } };
					vg.draw_rect(rect, { palette_colour(palette, focused ? Text::CurrentLineFill : Text::CurrentLineFillInactive),
										 palette_colour(palette, Text::CurrentLineEdge), 1.0f });
				}

				static Clock blink_clock;
				static bool caret_visible = true;
				if(blink_clock.read() > 0.4f)
				{
					caret_visible = !caret_visible;
					blink_clock.step();
				}

				if(caret_visible)
				{
					vec4 cursor_rect = text.cursor_rect(selection.m_cursor);
					if(!selection.m_insert_mode)
					{
						cursor_rect.x -= 1.f;
						cursor_rect.z = 1.f;
					}
					vg.draw_rect({ offset + text_offset + rect_offset(cursor_rect), rect_size(cursor_rect) }, palette_paint(palette, Text::Cursor));
				}
			}

			if(imarker < text.m_markers.size() && text.m_markers[imarker].m_line == line)
			{	
				offset += vec2(0.f, line_height);
				imarker++;
			}
		}
	}

	void TextEdit::render(Vg& vg)
	{
		if(m_editor)
			recolorize();

		if(m_editor)
			vg.draw_rect({ m_frame.m_position, m_frame.m_size }, { palette_paint(m_palette, Text::Background) });
		//else
		//	vg.draw_background(m_frame, { m_frame.m_position, m_frame.m_size }, {}, {});

		vec2 padding = floor(rect_offset(m_frame.d_inkstyle->m_padding));

		if(this->focused())
			draw_text_selection(vg, m_frame, padding, m_text_offset, m_text, m_selection, m_palette, m_editor);
		if(m_editor)
			draw_editor_text(vg, m_frame, padding, m_text_offset, m_text, m_palette);
		else
			draw_text(vg, padding, m_text);
	}

	void TextEdit::undo()
	{
		if(CanUndo())
			m_undo_stack[--m_undo_index].Undo(this);
	}

	void TextEdit::redo()
	{
		if(CanRedo())
			m_undo_stack[m_undo_index++].Redo(this);
	}

	void TextEdit::recolorize()
	{
		if(m_dirty[0] == UINT32_MAX) return;
		//colorize(0, m_string.size());
		colorize(m_dirty[0], m_dirty[1]);
		m_dirty = { UINT32_MAX, 0 };
	}

	void TextEdit::colorize(size_t from, size_t to)
	{
		if(m_string.empty() || m_language == nullptr)
			return;

		std::match_results<const char*> results;

		size_t begin = line_begin(m_string, from);
		size_t end = line_end(m_string, to);

		bool preproc = false;

		const char* first = &m_string.front();
		const char* start = first + begin;
		const char* last = first + end;

		// remove all sections that overlap range to colorize, and get iterator to insert the new ones
		vector_remove_if(m_text.m_sections, [=](Text::ColorSection& section) { return section.m_start >= begin && section.m_end <= end; });
		auto start_section = vector_find_if(m_text.m_sections, [=](const Text::ColorSection& section) { return section.m_start >= begin; });

		for(const char* current = start; current != last; ++current)
		{
			for(auto& token_color : m_language->m_regex_tokens)
			{
				if(std::regex_search<const char*>(current, last, results, token_color.first, std::regex_constants::match_continuous))
				{
					auto match = *results.begin();
					string name = m_string.substr(match.first - first, match.second - match.first);
					PaletteIndex color = token_color.second;

					//if(color == uint16_t(CodePalette::Word))
					{
						if(!m_language->m_case_sensitive)
							std::transform(name.begin(), name.end(), name.begin(), [](char c) { return char(toupper(c)); });
						
						if(!preproc)
						{
							if(m_language->m_keywords.find(name) != m_language->m_keywords.end())
								color = uint16_t(CodePalette::Keyword);
							else if(m_language->m_identifiers.find(name) != m_language->m_identifiers.end())
								color = uint16_t(CodePalette::Identifier);
							else if(m_language->m_preproc_identifiers.find(name) != m_language->m_preproc_identifiers.end())
								color = uint16_t(CodePalette::PreprocIdentifier);
						}
						else
						{
							if(m_language->m_preproc_identifiers.find(name) != m_language->m_preproc_identifiers.end())
								color = uint16_t(CodePalette::PreprocIdentifier);
							else
								color = uint16_t(CodePalette::Word);
						}
					}
					//else
					if(color == uint16_t(CodePalette::Preprocessor))
					{
						preproc = true;
					}

					Text::ColorSection section = { size_t(match.first - first), size_t(match.second - first), color };
					start_section = m_text.m_sections.insert(start_section, section);
					start_section++;

					current += name.size() - 1;
					break;
				}
			}

			if(*current == '\n')
				preproc = false;
		}
	}

	void TextEdit::scroll_to_cursor(Frame& frame, Frame& content)
	{
		vec2 margin = vec2(0.f);

		vec4 cursor_rect = m_text.cursor_rect(m_selection.m_cursor);
		vec2 cursor_min = rect_offset(cursor_rect) - margin;
		vec2 cursor_max = cursor_min + rect_size(cursor_rect) + margin;

		vec2 frame_min = -content.m_position;
		vec2 frame_max = -content.m_position + frame.m_size;

		vec2 delta_neg = max(vec2(0.f), frame_min - cursor_min);
		vec2 delta_pos = min(vec2(0.f), frame_max - cursor_max);

		content.set_position(content.m_position + delta_neg);
		content.set_position(content.m_position + delta_pos);
	}

	void TextEdit::Action::Undo(TextEdit * aEditor)
	{
		if(!mAdded.empty())
			aEditor->erase(mAddedStart, mAddedEnd);

		if(!mRemoved.empty())
			aEditor->insert(mRemovedStart, mRemoved);
		
		aEditor->m_selection = mBefore;
		aEditor->m_follow_cursor = true;

	}

	void TextEdit::Action::Redo(TextEdit * aEditor)
	{
		if(!mRemoved.empty())
			aEditor->erase(mRemovedStart, mRemovedEnd);

		if(!mAdded.empty())
			aEditor->insert(mAddedStart, mAdded);

		aEditor->m_selection = mAfter;
		aEditor->m_follow_cursor = true;
	}


namespace ui
{
	bool filter(const string& filter, const string& value)
	{
		for(size_t i = 0; i < filter.size(); ++i)
			if(std::tolower(filter[i], std::locale()) != std::tolower(value[i], std::locale()))
				return false;
		return true;
	}

	TextEdit& text_box(Widget& parent, Style& style, string& text, bool editor, size_t lines, const string& allowed_chars)
	{
		TextEdit& self = parent.suba<TextEdit, bool, string>(editor, allowed_chars);
		self.init(style);

		if(lines > 0)
			self.m_text.set_lines(lines);

		self.update_style();

		self.set_text(text);
		self.update();
		text = self.m_string;

		vec2 size = self.frame_size();
		ui::dummy(self, size);

		self.m_custom_draw = [&](const Frame& frame, const vec4& rect, Vg& vg) { UNUSED(frame); UNUSED(rect); self.render(vg); };

		return self;
	}

	TextEdit& type_in(Widget& parent, string& text, size_t lines, const string& allowed_chars)
	{
		Widget& self = widget(parent, styles().type_in);
		TextEdit& edit = text_box(self, styles().type_in, text, false, lines, allowed_chars);
		return edit;
	}

	void autocomplete_popup(TextEdit& edit, string& text, const string& current_word, size_t cursor, size_t word_start, array<cstring> completions)
	{
		vec4 word_rect = edit.m_text.interval_rect(word_start, cursor - 1);
		vec2 popup_position = edit.m_text_offset + rect_offset(word_rect) + vec2(0.f, rect_h(word_rect));

		static uint32_t current = 0;

		bool selected = ui::popdown(edit, completions, current, popup_position, PopupFlags::None); //auto_complete_style

		if(edit.key_stroke(Key::Up))
			current = max(current - 1, uint32_t(0));

		if(edit.key_stroke(Key::Down))
			current = min(current + 1, uint32_t(completions.size()) - 1);

		if(edit.key_stroke(Key::Tab) || selected)
		{
			edit.insert(string(completions[current]).substr(current_word.size()));
			edit.m_text.break_text_rows();
			edit.m_completing = false;
			text = edit.m_string;
		}
	}

	TextEdit& text_edit(Widget& parent, string& text, size_t lines, vector<string>* vocabulary)
	{
		Widget& self = widget(parent, styles().text_edit);
		ScrollSheet& scroll_sheet = ui::scroll_sheet(self);
		TextEdit& edit = text_box(*scroll_sheet.m_body, styles().type_zone, text, true, lines);

		edit.update_scroll(scroll_sheet.m_scroll_zone->m_frame, scroll_sheet.m_body->m_frame);

		if(vocabulary && edit.m_completing && !edit.has_selection())
		{
			size_t cursor = edit.m_selection.m_cursor;
			size_t begin = word_begin(edit.m_string, cursor - 1);

			string current_word = begin == SIZE_MAX ? "" : edit.m_string.substr(begin, cursor - begin);
			if(current_word != "")
			{
				vector<cstring> completions;
				for(const string& word : *vocabulary)
				{
					//if(word.find(current_word) != string::npos)
					// if current word is fits the beginning of word
					if(word.substr(0, current_word.size()).compare(current_word) == 0)
						completions.push_back(word.c_str());
					//if(word.compare(0, current_word.size(), current_word) == 0)
					//	completions.push_back(word.c_str());
				}

				if(!completions.empty())
					autocomplete_popup(edit, text, current_word, cursor, begin, to_array(completions));
			}
		}

		return edit;
	}

	TextEdit& code_edit(Widget& parent, string& text, size_t lines, vector<string>* vocabulary)
	{
		return text_edit(parent, text, lines, vocabulary);
	}

	string auto_indent(TextEdit& edit)
	{
		string text = edit.m_string;
		text.reserve(text.size() * 2);

		int level = 0;
		size_t row = 0;
		size_t cursor_row = edit.m_selection.m_cursor.m_grid_index.y;
		int cursor_offset  = 0;

		auto process_line = [&](const char* line, size_t i)
		{
			const char* c = line;
			while(*c == ' ')
				c++;

			int current = *c == '}' ? level - 1 : level;
			for(; c - line > current * 4; c--)
			{
				text.erase(c - 1 - &text.front(), 1);
				if(cursor_row == i)
					cursor_offset--;
			}
			for(; c - line < current * 4; c++)
			{
				text.insert(c - &text.front(), " ");
				if(cursor_row == i)
					cursor_offset++;
			}

			for(; *c != '\n'; ++c)
			{
				if(*c == '{') level++;
				if(*c == '}') level--;
			}
			return c;
		};

		for(const char* c = &text.front(); c < &text.back(); ++c)
		{
			c = process_line(c, row++);
		}

		edit.cursor(edit.m_selection.m_cursor + cursor_offset);

		return text;
	}
}
}


#ifdef MUD_MODULES
module mud.ui;
#else
#endif

namespace mud
{
}


#ifdef MUD_MODULES
module mud.ui;
#else
#endif

#include <cstdio>

namespace mud
{
	template <> string to_string<DirtyLayout>(const DirtyLayout& dirty) { if(dirty == CLEAN) return "CLEAN"; else if(dirty == DIRTY_REDRAW) return "DIRTY_REDRAW"; else if(dirty == DIRTY_PARENT) return "DIRTY_PARENT"; else if(dirty == DIRTY_LAYOUT) return "DIRTY_LAYOUT"; else if(dirty == DIRTY_FORCE_LAYOUT) return "DIRTY_FORCE_LAYOUT"; else /*if(dirty == DIRTY_STRUCTURE)*/ return "DIRTY_STRUCTURE"; }

	Vg* Frame::s_vg = nullptr;

	struct Frame::Content
	{
		string d_caption = "";
		Image* d_icon = nullptr;
	};

	Frame::Frame(Frame* parent, Widget& widget)
		: UiRect()
		, d_widget(widget)
		, d_parent(parent)
	{
		if(parent)
		{
			parent->mark_dirty(DIRTY_FORCE_LAYOUT);
			//d_index[d_parent->d_length] = d_widget.d_index;
		}
	}

	Frame::~Frame()
	{
		if(d_parent)
		{
			d_parent->mark_dirty(DIRTY_FORCE_LAYOUT);
			d_parent = nullptr;
		}
	}

	bool Frame::empty() const
	{
		return !d_content || (d_content->d_caption == "" && d_content->d_icon == nullptr);
	}

	Image* Frame::icon() const
	{
		return d_content->d_icon;
	}

	cstring Frame::caption() const
	{
		return d_content->d_caption.c_str();
	}

	FrameSolver& Frame::solver(Style& style, Dim length, Dim2<size_t> index)
	{
		d_style = &style;
		d_layout = &style.layout();
		d_index = index;

		this->update_style();

		LayoutSolver type = d_layout->m_solver;
		FrameSolver* solver = d_parent ? d_parent->m_solver.get() : nullptr;

		if(type == FRAME_SOLVER)
			m_solver = make_object<FrameSolver>(solver, d_layout, this);
		else if(type == ROW_SOLVER)
			m_solver = make_object<RowSolver>(solver, d_layout, this);
		else if(type == GRID_SOLVER)
			m_solver = make_object<GridSolver>(solver, d_layout, this);
		else if(type == TABLE_SOLVER)
			m_solver = make_object<TableSolver>(solver, d_layout, this);

		m_solver->applySpace(length);
		return *m_solver;
	}

	Frame& Frame::root()
	{
		return d_parent ? d_parent->root() : *this;
	}

	Layer& Frame::layer()
	{
		return m_layer ? *m_layer : d_parent->layer();
	}

	void Frame::mark_dirty(DirtyLayout dirty)
	{
		this->set_dirty(dirty);
		if(dirty == DIRTY_FORCE_LAYOUT)
			dirty = DIRTY_LAYOUT;
		Frame* parent = this->d_parent;
		while(parent)
		{
			parent->set_dirty(dirty);
			parent = parent->d_parent;
		}
	}

	void Frame::update_style(bool reset)
	{
		d_layout = &d_style->layout();
		m_opacity = d_layout->m_opacity;
		m_size = d_layout->m_size == Zero2 ? m_size : d_layout->m_size;

		this->update_inkstyle(d_style->state_skin(d_widget.m_state));

		reset ? this->mark_dirty(DIRTY_FORCE_LAYOUT) : this->mark_dirty(DIRTY_LAYOUT);
	}

	void Frame::update_state(WidgetState state)
	{
		InkStyle& inkstyle = d_style->state_skin(state);
		this->update_inkstyle(inkstyle);
	}

	void Frame::update_inkstyle(InkStyle& inkstyle)
	{
		bool skin_image = d_inkstyle && d_inkstyle->m_image;
		if(d_inkstyle == &inkstyle) return;
		//printf("INFO: Update inkstyle %s\n", inkstyle.m_name.c_str());
		d_inkstyle = &inkstyle;
		this->mark_dirty(DIRTY_REDRAW);

		if(d_inkstyle->m_image || skin_image)
			this->set_icon(d_inkstyle->m_image);
	}

	void Frame::set_caption(cstring text)
	{
		if(!d_content)
			d_content = make_unique<Content>();
		if(d_content->d_caption == text)
			return;
		d_content->d_caption = text;
		if(d_content->d_caption != "")
		{
			TextPaint paint = text_paint(*d_inkstyle);
			m_content = s_vg->text_size(d_content->d_caption.c_str(), d_content->d_caption.size(), paint);
		}
		else
			m_content = Zero2;
		mark_dirty(DIRTY_LAYOUT);
	}

	void Frame::set_icon(Image* image)
	{
		if(!d_content)
			d_content = make_unique<Content>();
		if(d_content->d_icon == image)
			return;
		d_content->d_icon = image;
		m_content = image ? vec2{ image->d_size } : Zero2;
		mark_dirty(DIRTY_LAYOUT);
	}

	void Frame::set_size(Dim dim, float size)
	{
		if(m_size[dim] == size) return;
		m_size[dim] = size;
		this->mark_dirty(DIRTY_FORCE_LAYOUT);
	}

	void Frame::set_span(Dim dim, float span)
	{
		if(m_span[dim] == span) return;
		m_span[dim] = span;
		this->mark_dirty(DIRTY_FORCE_LAYOUT);
	}

	void Frame::set_position(Dim dim, float position)
	{
		if(m_position[dim] == position) return;
		m_position[dim] = position;
		this->mark_dirty(DIRTY_REDRAW);
	}

	void Frame::integrate_position(Frame& root, vec2& global)
	{
		if(this == &root) return;
		d_parent->integrate_position(root, global);
		global = (global - m_position) / m_scale;
	}

	void Frame::derive_position(Frame& root, vec2& local)
	{
		if(this == &root) return;
		local = m_position + local * m_scale;
		d_parent->derive_position(root, local);
	}

	float Frame::derive_scale(Frame& root)
	{
		if(this == &root)
			return m_scale;
		else 
			return d_parent->derive_scale(root) * m_scale;
	}

	Frame* clip_parent(Frame& frame)
	{
		Frame* parent = frame.d_parent;
		while(parent->d_layout->m_clipping != CLIP)
			parent = parent->d_parent;
		return parent;
	}

	void Frame::clamp_to_parent()
	{
		//Frame* clip = clip_parent(*this);
		Frame* clip = &this->root();
		vec2 position = this->derive_position(Zero2, *clip);

		for(Dim dim : { DIM_X, DIM_Y })
		{
			m_size[dim] = min(clip->m_size[dim], m_size[dim]);

			float overflow = position[dim] + m_size[dim] - clip->m_size[dim];
			m_position[dim] -= max(0.f, overflow);
		}
	}

	vec4 Frame::content_rect() const
	{
		return { floor(rect_offset(d_inkstyle->m_margin)),
				 floor(m_size - rect_sum(d_inkstyle->m_margin)) };
	}

	bool Frame::inside(const vec2& pos)
	{
		return (pos.x >= 0.f && pos.x <= m_size.x
			 && pos.y >= 0.f && pos.y <= m_size.y);
	}

	bool Frame::first(const Frame& frame)
	{
		return frame.d_widget.m_index == 0;
	}

	bool Frame::last(const Frame& frame)
	{
		return frame.d_widget.m_index == d_widget.m_nodes.size() - 1;
	}

	void Frame::transfer_pixel_span(Frame& prev, Frame& next, Dim dim, float pixelSpan)
	{
		float pixspan = 1.f / this->m_size[dim];
		float offset = pixelSpan * pixspan;

		prev.set_span(dim, max(0.01f, prev.m_span[dim] + offset));
		next.set_span(dim, max(0.01f, next.m_span[dim] - offset));
		this->mark_dirty(DIRTY_FORCE_LAYOUT);
	}

	void Frame::relayout()
	{
		DirtyLayout dirty = this->clearDirty();
		if(!dirty) return;

		SolverVector solvers;
		for(auto& widget : d_widget.m_nodes)
			collect_solvers(widget->m_frame, solvers, dirty);

		m_solver->reset();
		m_solver->m_size = m_size;

		mud::relayout(solvers);
	}

	void Frame::sync_solver(FrameSolver& solver)
	{
		vec2 content = m_content + rect_sum(d_inkstyle->m_padding);
		solver.setup(m_position, m_size, m_span, m_content != Zero2 ? &content : nullptr);

		if(d_dirty == DIRTY_PARENT)
		{
			// @bug this causes a bug in the relayout if we want to implement scarce behavior for wrap frames, since here the content is instead just the unpadded size
			solver.d_content = m_size - rect_sum(solver.d_layout->m_padding);
		}
	}

	void fix_position(Frame& frame, Dim dim, FrameSolver* solver)
	{
		// @todo should be while but it causes a bug with nested tables
		if(solver->m_solvers[dim] && solver->m_solvers[dim]->d_frame != frame.d_parent)
		{
			if(!solver->m_solvers[dim]->d_frame)
				frame.m_position[dim] += solver->m_solvers[dim]->m_position[dim];
			solver = solver->m_solvers[dim];
		}
	}

	void Frame::read_solver(FrameSolver& solver)
	{
		this->set_position(solver.m_position);
		this->set_size(solver.m_size);
		m_span = solver.m_span;

		fix_position(*this, DIM_X, &solver);
		fix_position(*this, DIM_Y, &solver);
	}

	void Frame::debug_print(bool commit)
	{
		Frame* parent = this->d_parent;
		while(parent)
		{
			printf("  ");
			parent = parent->d_parent;
		}
		printf("FRAME: %s ", d_style->name());
		if(commit)
			printf("\n");
	}
}


#ifdef MUD_MODULES
module mud.ui;
#else
#endif

#include <algorithm>

namespace mud
{
	Layer::Layer(Frame& frame)
		: m_frame(frame)
		, d_parentLayer(frame.d_parent ? &frame.d_parent->layer() : nullptr)
	{
		if(d_parentLayer)
			d_parentLayer->addLayer(*this);
	}

	Layer::~Layer()
	{
		if(d_parentLayer)
			d_parentLayer->removeLayer(*this);
	}

	size_t Layer::z() const
	{
		return m_frame.d_layout->m_zorder ? m_frame.d_layout->m_zorder : d_z;
	}

	void Layer::reindex()
	{
		for(size_t i = 0; i < d_sublayers.size(); ++i)
			d_sublayers[i]->d_index = i;
	}

	void Layer::reorder()
	{
		std::sort(d_sublayers.begin(), d_sublayers.end(), [](Layer* first, Layer* second) { if(first->z() < second->z()) return true; else if(first->z() > second->z()) return false; return first->d_index < second->d_index; });
		this->reindex();
	}
	
	void Layer::addLayer(Layer& layer)
	{
		layer.d_index = d_sublayers.size();
		d_sublayers.push_back(&layer);
		this->reorder();
	}

	void Layer::removeLayer(Layer& layer)
	{
		vector_remove(d_sublayers, &layer);
		this->reindex();
		this->reorder();
	}

	void Layer::moveToTop()
	{
		d_parentLayer->removeLayer(*this);
		d_parentLayer->addLayer(*this);
	}
}


#ifdef MUD_MODULES
module mud.ui;
#else
#endif

namespace mud
{
	void collect_solvers(Frame& frame, SolverVector& solvers, DirtyLayout dirtyTop)
	{
		if(dirtyTop >= DIRTY_FORCE_LAYOUT)
			frame.set_dirty(DIRTY_FORCE_LAYOUT);
		else if(dirtyTop >= DIRTY_LAYOUT)
			//frame.set_dirty(DIRTY_PARENT);
			frame.set_dirty(DIRTY_LAYOUT); // @kludge because relayout with DIRTY_PARENT isn't always correct due to size / content issue

		if(!frame.d_dirty)
			return;

		//this->debugPrintDepth();
		//printf(" >> %s %s\n", d_style->m_name.c_str(), to_string(d_dirty).c_str());

		if(frame.d_dirty >= DIRTY_PARENT)
		{
			frame.m_solver->collect(solvers);
		}

		if(frame.d_dirty >= DIRTY_REDRAW)
		{
			frame.layer().setRedraw();
			frame.layer().setForceRedraw(); // @ kludge for nodes in canvas when moving the canvas window
		}

		for(auto& widget : frame.d_widget.m_nodes)
			collect_solvers(widget->m_frame, solvers, frame.d_dirty);

		frame.clearDirty();
	}

	void relayout(SolverVector& solvers)
	{
		//for(FrameSolver* solver : solvers)
		//	solver->sync();

		for(FrameSolver* solver : reverse_adapt(solvers))
			solver->compute();

		for(FrameSolver* solver : solvers)
			solver->layout();

		for(FrameSolver* solver : solvers)
			solver->read();
	}

	Space Space::preset(SpacePreset preset)
	{
		if     (preset == SHEET)  return { PARAGRAPH,  WRAP,   WRAP };
		else if(preset == FLEX)	  return { PARALLEL,   WRAP,   WRAP };
		else if(preset == ITEM)   return { READING,    SHRINK, SHRINK };
		else if(preset == UNIT)   return { PARAGRAPH,  SHRINK, SHRINK };
		else if(preset == BLOCK)  return { PARAGRAPH,  FIXED,  FIXED };
		else if(preset == LINE)   return { READING,    WRAP,   SHRINK };
		else if(preset == STACK)  return { PARAGRAPH,  SHRINK, WRAP };
		else if(preset == DIV)    return { ORTHOGONAL, WRAP,   SHRINK };
		else if(preset == SPACER) return { PARALLEL,   WRAP,   SHRINK };
		else if(preset == BOARD)  return { READING,    EXPAND, EXPAND };
		else if(preset == LAYOUT) return { PARAGRAPH,  EXPAND, EXPAND };
		else 					  return { PARAGRAPH,  WRAP,   WRAP };
	}

	float AlignSpace[5] = { 0.f, 0.5f, 1.f, 0.f, 1.f };
	float AlignExtent[5] = { 0.f, 0.5f, 1.f, 1.f, 0.f };

	FrameSolver::FrameSolver(FrameSolver* solver, Layout* layout, Frame* frame)
		: d_frame(frame)
		, d_parent(solver)
		, d_layout(layout)
		, m_solvers{ solver ? &solver->solver(*this, DIM_X) : nullptr, solver ? &solver->solver(*this, DIM_Y) : nullptr }
		, d_grid(solver ? solver->grid() : nullptr)
	{
		if(d_layout)
			this->applySpace();
	}

	FrameSolver& FrameSolver::solver(FrameSolver& frame, Dim dim)
	{
		if(dim == d_length && d_grid && frame.d_frame && frame.d_parent != d_grid) // && !d_layout->m_no_grid
			return d_grid->solver(frame, dim);
		return *this;
	}

	void FrameSolver::applySpace(Dim length)
	{
		const Space& space = d_layout->m_space;

		if(length != DIM_NONE)
			d_length = length;
		else if(space.direction == ORTHOGONAL)
			d_length = flip_dim(d_parent->d_length);
		else if(space.direction == PARALLEL)
			d_length = d_parent->d_length;
		else if(space.direction == READING)
			d_length = DIM_X;
		else if(space.direction == PARAGRAPH)
			d_length = DIM_Y;

		d_depth = flip_dim(d_length);

		d_sizing[d_length] = space.sizingLength;
		d_sizing[d_depth] = space.sizingDepth;
	}

	void FrameSolver::collect(SolverVector& solvers)
	{
		this->reset();
		this->sync();
		solvers.push_back(this);
	}

	void FrameSolver::sync()
	{
		if(d_frame)
			d_frame->sync_solver(*this);
	}

	void FrameSolver::compute()
	{
		if(!d_parent) return;
		m_solvers[DIM_X]->compute(*this, DIM_X);
		m_solvers[DIM_Y]->compute(*this, DIM_Y);

#if 0 // DEBUG
		if(!d_frame) return;
		d_frame->debug_print(false);
		printf(" LAYOUT measured content size %i , %i\n", int(d_content.x), int(d_content.y));
#endif
	}

	void FrameSolver::layout()
	{
		if(!d_parent) return;
		m_solvers[DIM_X]->layout(*this, DIM_X);
		m_solvers[DIM_Y]->layout(*this, DIM_Y);

#if 0 // DEBUG
		if(!d_frame) return;
		d_frame->debug_print(false);
		printf(" size %i , %i ", int(m_size.x), int(m_size.y));
		printf(" position %i , %i\n", int(m_position.x), int(m_position.y));
#endif
	}

	void FrameSolver::read()
	{
		if(d_frame)
			d_frame->read_solver(*this);
	}

	void FrameSolver::compute(FrameSolver& frame, Dim dim)
	{
		UNUSED(frame); UNUSED(dim);
	}

	void FrameSolver::layout(FrameSolver& frame, Dim dim)
	{
		UNUSED(frame); UNUSED(dim);
	}

	RowSolver::RowSolver(FrameSolver* solver, Layout* layout, Frame* frame)
		: FrameSolver(solver, layout, frame)
	{}

	void RowSolver::compute(FrameSolver& frame, Dim dim)
	{
		if(dim == d_length && frame.flow() && frame.d_sizing[d_length] >= WRAP)
			d_totalSpan += frame.m_span[d_length];

		if(!frame.sizeflow())
			return;

		if(frame.d_sizing[dim] <= WRAP)
			this->measure(frame, dim);

		if(frame.d_sizing[dim] <= SHRINK && frame.flow() && dim == d_length)
			m_spaceContent[dim] += frame.dbounds(dim);

		if(dim == d_length && frame.d_sizing[d_length] >= WRAP)
			d_contentExpand = true;
	}

	void RowSolver::measure(FrameSolver& frame, Dim dim)
	{
		if(dim == d_length && frame.flow())
		{
			d_content[dim] += frame.dbounds(dim) + (d_count++ ? this->spacing() : 0.f);
			d_spacing[dim] += frame.dmargin(dim) * 2.f + (d_count++ ? this->spacing() : 0.f);
		}
		else
			d_content[dim] = max(d_content[dim], frame.dbounds(dim));
	}

	void RowSolver::layout(FrameSolver& frame, Dim dim)
	{
		if(dim == d_length && frame.flow() && frame.d_sizing[d_length] >= WRAP)
			frame.m_span[d_length] = frame.m_span[d_length] / d_totalSpan;

		this->resize(frame, dim);

		if(frame.posflow())
			this->position(frame, dim);
	}

	void RowSolver::resize(FrameSolver& frame, Dim dim)
	{
		if(d_layout->m_layout[dim] < AUTO_SIZE)
			return;

		float space = this->dspace(dim);
		//bool hasSpace = space > d_content[dim]; // @todo: implement scarcity check, current behavior when scarce is wrong
		if(dim == d_length && frame.flow())
		{
			float spacings = d_spacing[dim];
			space -= (m_spaceContent[dim] + spacings);
			space *= frame.m_span[d_length];
		}
		else
		{
			space -= frame.dmargin(dim) * 2.f;
		}

		float content = frame.dcontent(dim);

		Sizing sizing = frame.d_sizing[dim];
		if(sizing == SHRINK)
			frame.m_size[dim] = content;
		else if(sizing == WRAP)
			frame.m_size[dim] = max(content, space);
		else if(sizing == EXPAND)
			frame.m_size[dim] = space;
	}

	void RowSolver::position(FrameSolver& frame, Dim dim)
	{
		if(d_layout->m_layout[dim] < AUTO_LAYOUT)
			return;

		float space = this->dspace(dim);

		if(dim == d_length && frame.flow())
			frame.m_position[dim] = this->positionSequence(frame, d_contentExpand ? 0.f : space - d_content[d_length]);
		else
			frame.m_position[dim] = this->positionFree(frame, dim, space);

		if(dim == d_length && frame.flow())
			d_prev = &frame;
	}

	float RowSolver::positionFree(FrameSolver& frame, Dim dim, float space)
	{
		Align align = frame.dalign(dim);// == d_length ? DIM_X : DIM_Y);
		float alignOffset = space * AlignSpace[align] - frame.dextent(dim) * AlignExtent[align];
		return (frame.flow() ? dpadding(dim) + frame.dmargin(dim) : 0.f) + alignOffset;
	}

	float RowSolver::positionSequence(FrameSolver& frame, float space)
	{
		auto alignSequence = [&](FrameSolver& frame, float space) { return space * AlignSpace[frame.dalign(d_length)]; };
		if(d_prev)
			return d_prev->doffset(d_length) - alignSequence(*d_prev, space) + this->spacing() + alignSequence(frame, space);
		else
			return dpadding(d_length) + frame.dmargin(d_length) + alignSequence(frame, space);
	}

	CustomSolver::CustomSolver(FrameSolver* solver, Layout* layout, Frame* frame)
		: RowSolver(solver, layout, frame)
	{}

	void CustomSolver::collect(SolverVector& solvers)
	{
		FrameSolver::collect(solvers);

		for(auto& solver : m_solvers)
			solver->collect(solvers);
	}

	static Layout& gridOverlayStyle()
	{
		static Layout style;
		//style.m_space = { READING, EXPAND, EXPAND };
		style.m_space = { READING, WRAP, WRAP };
		style.m_flow = OVERLAY;
		style.m_spacing = { 2.f, 2.f };
		return style;
	}

	static Layout& columnSolverStyle()
	{
		static Layout style;
		//style.m_space = { PARAGRAPH, EXPAND, EXPAND };
		style.m_space = { PARAGRAPH, WRAP, WRAP };
		style.m_layout = { AUTO_LAYOUT, NO_LAYOUT };
		return style;
	}

	TableSolver::TableSolver(FrameSolver* solver, Layout* layout, Frame* frame)
		: CustomSolver(solver, layout, frame)
	{
		this->divide(layout->m_table_division);
	}

	void TableSolver::divide(const vector<float>& columns)
	{
		m_solvers.clear();
		m_solvers.emplace_back(make_unique<RowSolver>(this, &gridOverlayStyle()));
		for(size_t i = 0; i < columns.size(); ++i)
		{
			m_solvers.emplace_back(make_unique<RowSolver>(m_solvers.front().get(), &columnSolverStyle()));
			m_solvers.back()->m_span = { columns[i], 0.f };
		}
	}

	void TableSolver::update(const vector<float>& columns)
	{
		if(m_solvers.size() != columns.size() + 1)
			return divide(columns);

		for(size_t i = 0; i < columns.size(); ++i)
			m_solvers[1 + i]->m_span[d_depth] = columns[i];
	}

	FrameSolver& TableSolver::solver(FrameSolver& frame, Dim dim)
	{
		UNUSED(dim);
		if(frame.d_frame && frame.d_parent != this && !frame.d_parent->d_layout->m_no_grid)
		{
			//size_t column0 = frame.d_frame->dindex(d_depth);
			size_t column = frame.d_frame->d_widget.m_index;
			frame.d_frame->d_index[d_depth] = column;
			return 1 + column < m_solvers.size() ? *m_solvers[1 + column] : *this;
		}
		return *this;
	}

	LineSolver::LineSolver(FrameSolver* solver, Space space)
		: RowSolver(solver, nullptr)
		, d_layout()
	{
		d_layout.m_space = space;
		d_layout.m_space.direction = READING;
		FrameSolver::d_layout = &d_layout;
		this->applySpace();
	}

	GridSolver::GridSolver(FrameSolver* solver, Layout* layout, Frame* frame)
		: CustomSolver(solver, layout, frame)
	{
		this->divide(layout->m_grid_division);
	}

	void GridSolver::divide(vector<Space> lines)
	{
		m_solvers.clear();
		for(size_t i = 0; i < lines.size(); ++i)
			m_solvers.emplace_back(make_unique<LineSolver>(this, lines[i]));
	}

	FrameSolver& GridSolver::solver(FrameSolver& frame, Dim dim)
	{
		UNUSED(dim);
		if(frame.d_frame)
		{
			size_t row = frame.d_frame->d_index[d_length];
			return *m_solvers[row];
		}
		return *this;
	}
}

#ifndef MUD_CPP_20
#include <stl/map.h>
#include <stl/string.h>
#endif

#ifdef MUD_MODULES
module mud.ui;
#else
#endif

#include <algorithm>
#include <cstdio>

namespace mud
{
	inline Colour offset_colour(const Colour& colour, float delta)
	{
		float offset = delta / 255.0f;
		return Colour(clamp(colour.m_r + offset, 0.f, 1.f),
					  clamp(colour.m_g + offset, 0.f, 1.f),
					  clamp(colour.m_b + offset, 0.f, 1.f),
					  colour.m_a);
	}

	struct Vg::Impl
	{
		string m_resource_path;
		map<string, string> m_font_sources;
	};

	Vg::Vg(cstring resource_path)
		: m_impl(make_unique<Impl>())
	{
		m_impl->m_resource_path = resource_path;

		Frame::s_vg = this;
		Text::s_vg = this;

		m_impl->m_font_sources["dejavu"] = string(resource_path) + "/interface/fonts/DejaVuSans.ttf";
		m_impl->m_font_sources["consolas"] = string(resource_path) + "/interface/fonts/Consolas.ttf";
		//m_impl->m_font_sources["consolas-bold"] = string(resource_path) + "/interface/fonts/Consolas-Bold.ttf";
		//m_impl->m_font_sources["inconsolata"] = string(resource_path) + "/interface/fonts/Inconsolata-Regular.ttf";
		//m_impl->m_font_sources["inconsolata-bold"] = string(resource_path) + "/interface/fonts/Inconsolata-Bold.ttf";
		//m_impl->m_font_sources["veramono"] = string(resource_path) + "/interface/fonts/VeraMono.ttf";
		//m_impl->m_font_sources["veramono-bold"] = string(resource_path) + "/interface/fonts/VeraMono-Bold.ttf";
	}

	Vg::~Vg()
	{}

	cstring Vg::font_path(cstring font)
	{
		return m_impl->m_font_sources[string(font)].c_str();
	}

	void Vg::draw_rect(const vec4& rect, const Paint& paint, const vec4& corners)
	{
		this->path_rect(rect, corners, paint.m_stroke_width);

		if(!paint.m_fill_colour.null())
			this->fill(paint);
		if(paint.m_stroke_width > 0.f)
			this->stroke(paint);
	}

	void Vg::debug_rect(const vec4& rect, const Colour& colour)
	{
		Paint paint = { Colour::None, colour, 1.f };
		this->draw_rect(rect, paint);
	}

	void Vg::fill_text(cstring text, size_t len, const vec4& rect, const TextPaint& paint, TextRow& row)
	{
		row = text_row(text, text, text + len, { rect.x, rect.y, this->text_size(text, len, DIM_X, paint), line_height(paint) });
		this->break_glyphs(rect, paint, row);
	}

	void Vg::break_text_width(const char* text, const char* first, const char* end, const vec4& rect, const TextPaint& paint, TextRow& row)
	{
		this->break_next_row(text, first, end, rect, paint, row);

		if(row.m_start != row.m_end)
			this->break_glyphs(rect, paint, row);
	}

	void Vg::break_text_returns(const char* text, const char* first, const char* end, const vec4& rect, const TextPaint& paint, TextRow& row)
	{
		const char* iter = first;

		while(*iter != '\n' && iter < end)
			++iter;

		row = text_row(text, first, iter, vec4{ rect.x, rect.y, this->text_size(first, iter - first, DIM_X, paint), line_height(paint) });
		this->break_glyphs(rect, paint, row);

		// @kludge because text_size doesn't report the correct size when there is a space at the end : investigate (vg-renderer, nanovg)
		if(!row.m_glyphs.empty())
			row.m_rect = vec4{ rect.x, rect.y, row.m_glyphs.back().m_rect.x + rect_w(row.m_glyphs.back().m_rect), line_height(paint) };
	}

	void Vg::break_text(cstring text, size_t len, const vec2& space, const TextPaint& paint, vector<TextRow>& textRows)
	{
		float line_height = this->line_height(paint);

		textRows.clear();

		if(!paint.m_text_break)
		{
			textRows.resize(1);

			vec4 rect(0.f, 0.f, space.x, line_height);
			this->fill_text(text, len, rect, paint, textRows[0]);
			return;
		}

		const char* first = text;
		const char* end = first + len;

		while(first < end)
		{
			size_t index = textRows.size();
			textRows.resize(index + 1);
			TextRow& row = textRows.back();

			vec4 rect(0.f, index * line_height, space.x, 0.f);
			if(paint.m_text_wrap)
				this->break_text_width(text, first, end, rect, paint, row);
			else
				this->break_text_returns(text, first, end, rect, paint, row);

			first = row.m_end + 1;
		}
	}

	struct UiRenderer::Impl
	{
		string m_debug_filter = "";
		bool m_debug_frame_rect = false;
		bool m_debug_fadded_rect = false;
		bool m_debug_fontent_rect = false;
		bool m_debug_flip_rect = false;
	};

	UiRenderer::UiRenderer(Vg& vg)
		: m_vg(vg)
		, m_impl(make_unique<Impl>())
	{
		Frame::s_vg = &m_vg;
		Text::s_vg = &m_vg;
	}

	UiRenderer::~UiRenderer()
	{}

	void UiRenderer::render(Layer& target)
	{
		this->log_FPS();

		m_debug_batch = 0;
		static size_t prevBatch = 0;

		m_vg.begin_frame({ vec2(0.f), target.m_frame.m_size });

#ifdef MUD_UI_DRAW_CACHE
		target.visit([&](Layer& layer) {
			if(layer.redraw() || layer.forceRedraw())
				this->render_layer(layer);
		});

		target.visit([&](Layer& layer) {
			m_vg.draw_layer(layer, Zero2, 1.f);
		});
#else
		target.visit([&](Layer& layer)
		{
			this->render_layer(layer);
		});
#endif

		if(m_debug_batch > 1 && m_debug_batch != prevBatch)
		{
			prevBatch = m_debug_batch;
			//printf("DEBUG: Render Frame : %i frames redrawn\n", m_debug_batch);
		}

		m_vg.end_frame();
	}

	void UiRenderer::render_layer(Layer& layer)
	{
		if(layer.master())
			m_vg.begin_target();

#ifdef MUD_UI_DRAW_CACHE
		m_vg.begin_cached(layer);
#endif

		if(layer.m_frame.d_parent)
			this->begin_layer(*layer.m_frame.d_parent);

		m_vg.begin_layer(layer);

		this->render_frame(layer.m_frame);

		m_vg.end_layer();
		layer.endRedraw();

		if(layer.m_frame.d_parent)
			this->end_layer(*layer.m_frame.d_parent);

#ifdef MUD_UI_DRAW_CACHE
		m_vg.end_cached();
#endif

		if(layer.master())
			m_vg.end_target();
	}

	void UiRenderer::begin_frame(Frame& frame)
	{
		m_vg.begin_update(floor(frame.m_position), frame.m_scale);

		if(frame.d_layout->m_clipping == CLIP)
		{
			m_vg.clip(frame.content_rect());
		}

		if(frame.d_layout->m_clipping == UNCLIP)
			m_vg.unclip();
	}

	void UiRenderer::end_frame(Frame& frame)
	{
		UNUSED(frame);
		m_vg.end_update();
	}

	void UiRenderer::begin_layer(Frame& frame)
	{
		if(frame.d_parent)
			this->begin_layer(*frame.d_parent);

		this->begin_frame(frame);
	}

	void UiRenderer::end_layer(Frame& frame)
	{
		this->end_frame(frame);

		if(frame.d_parent)
			this->end_layer(*frame.d_parent);
	}

	void UiRenderer::render_frame(Frame& frame)
	{
		this->begin_frame(frame);

		this->draw_frame(frame);

		for(auto& widget : frame.d_widget.m_nodes)
			if(!widget->m_frame.m_layer)
				this->render_frame(widget->m_frame);

		this->end_frame(frame);
	}

	void UiRenderer::draw_frame(const Frame& frame)
	{
		vec4 rect = frame.content_rect();

		if(m_vg.clipped(rect))
			return;

		if(frame.d_inkstyle->m_empty)
			return;

		if(frame.d_widget.m_custom_draw)
			return frame.d_widget.m_custom_draw(frame, rect, m_vg);

		if(frame.d_inkstyle->m_custom_draw)
			return frame.d_inkstyle->m_custom_draw(frame, rect, m_vg);
	
		this->draw_frame(frame, rect);
	}

	void UiRenderer::draw_frame(const Frame& frame, const vec4& rect)
	{
		vec4 padded_rect = { floor(rect_offset(frame.d_inkstyle->m_padding)),
							 floor(frame.m_size - rect_sum(frame.d_inkstyle->m_padding)) };

		vec2 content = frame.m_content;
		if(frame.d_inkstyle->m_stretch.x)
			content.x = rect_w(padded_rect);
		if(frame.d_inkstyle->m_stretch.y)
			content.y = rect_h(padded_rect);

		vec2 content_pos = { this->content_pos(frame, content, padded_rect, DIM_X), this->content_pos(frame, content, padded_rect, DIM_Y) };
		vec4 content_rect = { content_pos, content };

		//m_vg.debug_rect(rect, Colour::Red);
		//m_vg.debug_rect(padded_rect, Colour::Green);
		//m_vg.debug_rect(content_rect, Colour::Blue);

		this->draw_background(frame, rect, padded_rect, content_rect);
		this->draw_content(frame, rect, padded_rect, content_rect);
	}

	float UiRenderer::content_pos(const Frame& frame, const vec2& content, const vec4& padded_rect, Dim dim)
	{
		if(frame.d_inkstyle->m_align[dim] == CENTER)
			return padded_rect[dim] + padded_rect[dim + 2] / 2.f - content[dim] / 2.f;
		else if(frame.d_inkstyle->m_align[dim] == Right)
			return padded_rect[dim] + padded_rect[dim + 2] - content[dim];
		else
			return padded_rect[dim];
	}

	vec4 UiRenderer::select_corners(const Frame& frame)
	{
		Frame& parent = *frame.d_parent;

		const vec4& corners = parent.d_inkstyle->m_corner_radius;
		if(parent.first(frame))
			return parent.m_solver->d_length == DIM_X ? vec4(corners[0], 0.f, 0.f, corners[3]) : vec4(corners[0], corners[1], 0.f, 0.f);
		else if(parent.last(frame))
			return parent.m_solver->d_length == DIM_X ? vec4(0.f, corners[1], corners[2], 0.f) : vec4(0.f, 0.f, corners[2], corners[3]);
		else
			return vec4();
	}

	void UiRenderer::draw_background(const Frame& frame, const vec4& rect, const vec4& padded_rect, const vec4& content_rect)
	{
		m_debug_batch++;

		InkStyle& inkstyle = *frame.d_inkstyle;

		// Shadow
		if(!inkstyle.m_shadow.d_null)
		{
			m_vg.draw_shadow(rect, inkstyle.m_corner_radius, inkstyle.m_shadow);
		}

		// Rect
		if(inkstyle.m_border_width.x || !inkstyle.m_background_colour.null())
		{
			vec4 corners = inkstyle.m_weak_corners ? this->select_corners(frame) : inkstyle.m_corner_radius;
			this->draw_rect(rect, corners, inkstyle);
		}

		// ImageSkin
		ImageSkin& image_skin = inkstyle.m_image_skin;
		if(!image_skin.null())
		{
			float margin = image_skin.m_margin * 2.f;
			vec4 skin_rect = { rect_offset(rect), rect_size(rect) + margin };

			if(image_skin.d_stretch == DIM_X)
				skin_rect = { rect.x, content_rect.y + margin, rect.z + margin, image_skin.d_size.y };
			else if(image_skin.d_stretch == DIM_Y)
				skin_rect = { content_rect.x + image_skin.m_margin, rect.y, image_skin.d_size.x, rect.w + margin };

			vec4 sections[ImageSkin::Count];
			image_skin.stretch_coords(rect_offset(skin_rect), rect_size(skin_rect), { sections, ImageSkin::Count });

			for(int s = 0; s < ImageSkin::Count; ++s)
				this->draw_skin_image(frame, s, sections[s]);
		}

		// Image
		if(inkstyle.m_overlay)
			this->draw_image(*inkstyle.m_overlay, padded_rect);
		if(inkstyle.m_tile)
			this->draw_image(*inkstyle.m_tile, rect);
	}

	void UiRenderer::draw_image(const Image& image, const vec4& rect)
	{
		if(image.d_atlas)
		{
			vec4 image_rect = { rect_offset(rect) - vec2(image.d_coord), vec2(image.d_atlas->m_image.d_size) };
			m_vg.draw_texture(uint16_t(image.d_atlas->m_image.d_handle), rect, image_rect);
		}
		else
		{
			m_vg.draw_texture(uint16_t(image.d_handle), rect, rect);
		}
	}

	void UiRenderer::draw_image_stretch(const Image& image, const vec4& rect, const vec2& stretch)
	{
		if(image.d_atlas)
		{
			vec4 image_rect = { rect_offset(rect) - vec2(image.d_coord) * stretch, vec2(image.d_atlas->m_image.d_size) * stretch };
			m_vg.draw_texture(uint16_t(image.d_atlas->m_image.d_handle), rect, image_rect);
		}
		else
		{
			vec4 image_rect = { rect_offset(rect), vec2(image.d_size) * stretch };
			m_vg.draw_texture(uint16_t(image.d_handle), rect, image_rect);
		}
	}

	void UiRenderer::draw_skin_image(const Frame& frame, int section, vec4 rect)
	{
		ImageSkin& imageSkin = frame.d_inkstyle->m_image_skin;
		rect.x = rect.x - imageSkin.m_margin;
		rect.y = rect.y - imageSkin.m_margin;

		vec2 divided = rect_size(rect) / imageSkin.d_fill_size;
		vec2 ratio = { 1.f, 1.f };

		if(section == ImageSkin::Top || section == ImageSkin::Bottom || section == ImageSkin::Fill)
			ratio.x = divided.x;
		if(section == ImageSkin::Left || section == ImageSkin::Right || section == ImageSkin::Fill)
			ratio.y = divided.y;

		this->draw_image_stretch(imageSkin.d_images[section], rect, ratio);
	}

	void UiRenderer::draw_content(const Frame& frame, const vec4& rect, const vec4& padded_rect, const vec4& content_rect)
	{
		UNUSED(rect);

		if(frame.empty() || padded_rect.z <= 0.f || padded_rect.w <= 0.f)
			return;

		//this->clip(rect);

		if(frame.icon())
			this->draw_image(*frame.icon(), content_rect);

		if(frame.caption())
			m_vg.draw_text(rect_offset(padded_rect), frame.caption(), nullptr, text_paint(*frame.d_inkstyle));
	}

	void UiRenderer::draw_rect(const vec4& rect, const vec4& corners, const InkStyle& inkstyle)
	{
		m_vg.path_rect(rect, corners, inkstyle.m_border_width.x);

		if(!inkstyle.m_background_colour.null())
		{
			if(inkstyle.m_linear_gradient == Zero2)
			{
				m_vg.fill({ inkstyle.m_background_colour, inkstyle.m_border_colour, inkstyle.m_border_width.x });
			}
			else
			{
				Colour first = offset_colour(inkstyle.m_background_colour, inkstyle.m_linear_gradient.x);
				Colour second = offset_colour(inkstyle.m_background_colour, inkstyle.m_linear_gradient.y);
				if(inkstyle.m_linear_gradient_dim == DIM_X)
					m_vg.fill({ first, second }, { rect.x, rect.y }, { rect.x + rect_w(rect), rect.y });
				else
					m_vg.fill({ first, second }, { rect.x, rect.y }, { rect.x, rect.y + rect_h(rect) });
			}

		}
		if(inkstyle.m_border_width.x > 0.f)
			m_vg.stroke({ inkstyle.m_background_colour, inkstyle.m_border_colour, inkstyle.m_border_width.x });
	}

	void UiRenderer::log_FPS()
	{
		static size_t frames = 0;
		static double prevtime;

		double time = m_clock.read();
		if(time - prevtime >= 4.f)
		{
			printf("INFO: frame %.2f\n", ((time - prevtime) / frames) * 1000.f);
			printf("INFO: fps %f\n", (frames / (time - prevtime)));
			prevtime = time;
			frames = 0;
		}

		++frames;
	}
}


#ifdef MUD_MODULES
module mud.ui;
#else
#endif

namespace mud
{
	Dock::Dock()
	{}

	Dock::Dock(Docker& docker, cstring name, vector<uint16_t> dockid, float span)
		: m_docker(&docker)
		, m_name(name)
		, m_dockid(dockid)
		, m_span(span)
	{}

	Dockable::Dockable(Widget* parent, void* identity)
		: Widget(parent, identity)
	{}

	Docker::Docker(Widget* parent, void* identity, Docksystem& docksystem)
		: Widget(parent, identity)
		, m_docksystem(&docksystem)
	{}

	void Docker::dock_split(Dock& dock, Dock& target, bool after)
	{
		m_docks.push_back(&dock);
		dock.m_dockid = target.m_dockid;
		dock.m_dockid.push_back(after ? 0 : 1);
		target.m_dockid.push_back(after ? 1 : 0);
	}

	void Docker::dock_insert(Dock& dock, Dock& target, bool after)
	{
		m_docks.push_back(&dock);
		dock.m_dockid = target.m_dockid;
		after ? dock.m_dockid.back()++
			  : target.m_dockid.back()++;
		this->shift(after ? dock : target, true);
	}

	void Docker::undock(Dockable& dockable)
	{
		vec2 absolute = dockable.m_frame.absolute_position();
		dockable.m_frame.set_position(absolute);
		dockable.m_frame.m_layer->moveToTop();

		this->shift(*dockable.m_dock, false);
		vector_remove(m_docks, (Dock*)&dockable);

		dockable.m_dock->m_dockid = {};
	}

	void Docker::shift(Dock& start, bool add)
	{
		vector<uint16_t> root = start.m_dockid;
		uint16_t index = pop(root);

		size_t level = root.size();
		for(Dock* dock : m_docks)
			if(vector_contains(dock->m_dockid, root)
				&& dock->m_dockid[level] > index)
			{
				dock->m_dockid[level] += (add ? 1 : -1);
			}
	}

	Docksystem::Docksystem()
	{}

	void Docksystem::dock(Dockable& item, const vec2& pos)
	{
		for(Docker* docker : m_dockers)
			if(docker->m_frame.inside_abs(pos))
				docker->dock(item, pos);
	}

	Dockspace::Dockspace(Widget* parent, void* identity, Docksystem& docksystem)
		: Docker(parent, identity, docksystem)
	{}

	Dockspace::~Dockspace()
	{
		for(Dock* dock : m_docks)
		{
			m_docksystem->m_docks.erase(dock->m_name);
		}
	}

	Dockable& Dockspace::pinpoint_dock(const vec2& pos)
	{
		Widget* widget = this->pinpoint(pos, [](Frame& frame) { return frame.d_style == &ui::dock_styles().docksection; });
		return as<Dockable>(*widget);
	}

	Widget* Dockspace::docksection(Dock& dock)
	{
		vector<uint16_t> dockid = vector_reverse(dock.m_dockid);
		Widget* line = m_mainline;

		Dim dim = DIM_Y;
		while(dockid.size() > 0)
		{
			uint16_t index = pop(dockid);
			dim = flip_dim(dim);
			line = &ui::dockline(*line, index, dim);
			if(dockid.size() == 0 && dock.m_span > 0.f && line->m_frame.m_span[flip_dim(dim)] == 1.f)
				line->m_frame.set_span(flip_dim(dim), dock.m_span);
		}

		Tabber& section = ui::docksection(*line);
		Widget* tab = ui::tab(section, dock.m_name); // dock_styles().docktab, 

		if(tab)
		{
			Window& container = ui::window(*tab, dock.m_name, WindowState(WINDOW_DOCKABLE), nullptr, &dock);
			return container.m_body;
		}

		return tab;
	}

	void Dockspace::dock(Dockable& widget, const vec2& pos)
	{
		Dockable& target = pinpoint_dock(pos);
		this->dock(*widget.m_dock, *target.m_dock, target.m_frame, pos);
	}

	void Dockspace::dock(Dock& dock, Dock& target, Frame& frame, const vec2& pos)
	{
		vec2 local = frame.local_position(pos);

		Dim dim = Dim(target.m_dockid.size() % 2);
		Dim ortho = flip_dim(dim);

		if(local[dim] < frame.m_size[dim] * 0.25f)
			this->dock_split(dock, target, false); // dock split first
		else if(local[dim] > frame.m_size[dim] * 0.75f)
			this->dock_split(dock, target, true); // dock split second
		else if(local[ortho] < frame.m_size[ortho] * 0.25f)
			this->dock_insert(dock, target, false); // dock before
		else if(local[ortho] > frame.m_size[ortho] * 0.75f)
			this->dock_insert(dock, target, true); // dock after
		else
			dock.m_dockid = target.m_dockid; // dock on
	}

	Dockbar::Dockbar(Widget* parent, void* identity, Docksystem& docksystem)
		: Docker(parent, identity, docksystem)
	{}

	Widget* Dockbar::docksection(Dock& dock)
	{
		string icon = "(" + to_lower(replace(dock.m_name, " ", "")) + ")";
		Widget& toggle = ui::button(*m_togglebar, ui::dock_styles().docktoggle, icon.c_str());
		if(toggle.activated())
			m_current_tab = m_current_tab == dock.m_dockid.back() ? SIZE_MAX : dock.m_dockid.back();
		toggle.set_state(ACTIVE, m_current_tab == dock.m_dockid.back());

		if(m_current_tab == dock.m_dockid.back())
			return ui::window(*m_dockzone, dock.m_name, static_cast<WindowState>(0), &dock, &dock).m_body; // dock_styles().dockbox
		else
			return nullptr;
	}

	void Dockbar::dock(Dockable& widget, const vec2& pos)
	{
		UNUSED(widget); UNUSED(pos);
#if 0
		Dock* target = m_docks[0];
		for(Dock* dock : m_docks)
			if(pos.y < dock->m_frame->absolute_position().y)
			{
				target = dock;
				break;
			}

		this->dock_insert(*widget.m_dock, *target, false);
#endif
	}
}


#ifdef MUD_MODULES
module mud.ui;
#else
#endif

namespace mud
{
	Ui::Ui(UiWindow& window)
		: Widget()//{ params, &type<Ui>(), MASTER_LAYER })
		, EventDispatcher(this)
		, m_window(window)
		, m_keyboard(*this)
		, m_mouse(*this, m_keyboard)
	{
		this->init(styles().ui);
		this->layer();

		//if(!params.m_parent)
			m_frame.update_style(true);
	}

	Ui::~Ui()
	{}

	Widget& Ui::begin()
	{
		return begin_node<Widget>(*this);
	}

	void Ui::input_frame()
	{
		Widget* hovered = static_cast<Widget*>(m_mouse.heartbeat().m_receiver);
		if(hovered != m_hovered)
		{
			m_tooltip_clock.step();
			m_hovered = hovered;
		}

		m_drop = {};
	}

	void Ui::render_frame()
	{
		if (!m_window.m_context.m_mouse_lock)
		{
			Widget& cursor = ui::cursor(*this, m_mouse.m_pos, m_cursor_style ? *m_cursor_style : ui::cursor_styles().cursor);
			cursor.m_frame.layer().setForceRedraw();
		}

		m_cursor_style = &ui::cursor_styles().cursor;

		m_frame.relayout();
	}

	void Ui::clear_events()
	{
		m_mouse.m_events.clear();
		m_keyboard.m_events.clear();

		EventDispatcher::update();
	}
}


#ifdef MUD_MODULES
module mud.ui;
#else
#endif

namespace mud
{
	inline bool clip(const Frame& frame) { return frame.d_layout->m_clipping == CLIP; }

	Frame* pinpoint(Frame& frame, vec2 pos, const FrameFilter& filter)
	{
		if(!frame.d_style || frame.hollow() || (clip(frame) && !frame.inside(pos)))
			return nullptr;

		if(frame.m_layer)
			for(Layer* layer : reverse_adapt(frame.m_layer->d_sublayers))
			{
				vec2 local = layer->m_frame.integrate_position(pos, frame);
				Frame* target = pinpoint(layer->m_frame, local, filter);
				if(target)
					return target;
			}

		for(auto& widget : reverse_adapt(frame.d_widget.m_nodes))
		{
			vec2 local = widget->m_frame.integrate_position(pos, frame);
			Frame* target = pinpoint(widget->m_frame, local, filter);
			if(target)
				return target;
		}

		if(filter(frame) && frame.inside(pos))
			return &frame;
		return nullptr;
	}

	Widget::Widget()
		: Graph()
		, m_frame(nullptr, *this)
	{}

	Widget::Widget(Widget* parent, void* identity)
		: Graph(parent, identity)
		, m_frame(&m_parent->m_frame, *this)
	{
		m_index = parent->m_nodes.size();
	}

	Widget::~Widget()
	{
		if(m_events)
			m_events->m_control_node = nullptr;
		if(this->modal())
			this->yield_modal();
		if(this->pressed())
			this->ui().m_mouse.fix_press(this->ui());
		m_nodes.clear();
	}

	Widget& Widget::layer()
	{
		if(!m_frame.m_layer)
			m_frame.m_layer = make_object<Layer>(m_frame);
		return *this;
	}

	Ui& Widget::ui()
	{
		return as<Ui>(this->root());
	}

	Widget& Widget::parent_modal()
	{
		if(m_parent)
			return m_parent->modal() ? *m_parent : m_parent->parent_modal();
		else
			return *this;
	}

	UiWindow& Widget::ui_window()
	{
		return as<Ui>(this->root()).m_window;
	}

	void Widget::set_content(cstring content)
	{
		string str = content;
		if(str.front() == '(' && str.back() == ')')
		{
			string name = to_lower(str.substr(1, str.size() - 2));
			Image& icon = *this->ui_window().find_image(name.c_str());
			m_frame.set_icon(&icon);
		}
		else
		{
			m_frame.set_caption(content);
		}
	}

	void Widget::set_modal(Widget* widget, uint32_t device_filter)
	{
		if(m_control.m_modal)
		{
			static_cast<Widget*>(m_control.m_modal)->set_modal(nullptr, 0);
			static_cast<Widget*>(m_control.m_modal)->disable_state(FOCUSED);
			m_control.m_modal->m_control = {};
		}
		if(widget)
			widget->enable_state(FOCUSED);
		m_control = { m_control.m_parent, widget, device_filter };
	}

	void Widget::toggle_state(WidgetState state)
	{
		m_state = static_cast<WidgetState>(m_state ^ state);
		m_frame.update_state(m_state);
	}

	Widget* Widget::pinpoint(vec2 pos)
	{
		return this->pinpoint(pos, [](Frame& frame) { return frame.opaque(); });
	}

	Widget* Widget::pinpoint(vec2 pos, const FrameFilter& filter)
	{
		Frame* frame = mud::pinpoint(m_frame, pos, filter);
		return frame ? &frame->d_widget : nullptr;
	}

	void Widget::transform_event(InputEvent& event)
	{
		if(event.m_deviceType >= DeviceType::Mouse)
		{
			MouseEvent& mouse_event = static_cast<MouseEvent&>(event);
			mouse_event.m_relative = m_frame.local_position(mouse_event.m_pos);
		}
	}

	ControlNode* Widget::control_event(InputEvent& event)
	{
		this->transform_event(event);

		if((m_control.m_mask & device_mask(event.m_deviceType)) != 0)
			return m_control.m_modal->control_event(event);

		if(event.m_deviceType >= DeviceType::Mouse)
		{
			MouseEvent& mouse_event = static_cast<MouseEvent&>(event);
			Widget* pinned = this->pinpoint(mouse_event.m_relative);
			return (pinned && pinned != this) ? pinned->control_event(event) : this;
		}

		return this;
	}

	void Widget::receive_event(InputEvent& event)
	{
		if(event.m_consumer) return;
		this->transform_event(event);
	}

	ControlNode* Widget::propagate_event(InputEvent& event)
	{
		UNUSED(event);
		return m_parent;
	}

	KeyEvent Widget::key_event(Key code, EventType event_type, InputMod modifier)
	{
		if(!m_events) return KeyEvent();
		KeyEvent* event = static_cast<KeyEvent*>(m_events->event(DeviceType::Keyboard, event_type, int(code)));
		return event && fits_modifier(event->m_modifiers, modifier) ? *event : KeyEvent();
	}

	MouseEvent Widget::mouse_event(DeviceType device, EventType event_type, InputMod modifier, bool consume)
	{
		if(!m_events) return MouseEvent();
		MouseEvent* event = static_cast<MouseEvent*>(m_events->event(device, event_type));
		if(event && fits_modifier(event->m_modifiers, modifier))
		{
			MouseEvent result = *event;;
			if(consume)
				event->consume(*this);
			return result;
		}
		return MouseEvent();
	}
}


#ifdef MUD_MODULES
module mud.ui;
#else
#endif

namespace mud
{
	struct StyleSelector
	{
		template <class T_Decl>
		StyleSelector& declare(T_Decl decl);

		template <class T_Decl>
		StyleSelector& decline(const vector<uint32_t>& states, T_Decl decl);

		vector<Style*> styles;
	};

	template <class T_Decl>
	StyleSelector& StyleSelector::declare(T_Decl decl)
	{
		for(Style* style : styles)
			decl(style->layout(), style->skin());
		return *this;
	}

	template <class T_Decl>
	StyleSelector& StyleSelector::decline(const vector<uint32_t>& states, T_Decl decl)
	{
		for(Style* style : styles)
			for(uint32_t state : states)
			{
				decl(style->decline_skin(WidgetState(state)));
			}
		return *this;
	}

	StyleSelector select(const vector<string> styles)
	{
		StyleSelector selector;
		for(const string& name : styles)
			if(UiWindow::s_styles.find(name) != UiWindow::s_styles.end())
				selector.styles.push_back(UiWindow::s_styles[name]);
			else
				printf("WARNING: style %s not found\n", name.c_str());
		return selector;
	}

	void layout_minimal(UiWindow& ui_window)
	{
		UNUSED(ui_window);

		select({ "Label", "Title", "Message", "Tooltip", "TextEdit", "TypeLabel", "TypeZone", "SliderDisplay", "RadioChoiceItem" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_padding = vec4(4.f);
		});

		select({ "Title" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_padding = vec4(8.f);
		});

		select({ "Element", "Button", "WrapButton", "MultiButton", "Toggle", "ToolButton", "TabHeader", "DockToggle", "RadioChoice", "DropdownChoice", "SliderKnob", "ScrollerKnob", "DragHandle", "DropdownInput", "DropdownInputCompact", "TypedownInput", "Menu", "TypeIn", "Input<string>", "TreeNodeHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_padding = vec4(4.f);
		});

		select({ "Item", "DropdownToggle", "ExpandboxToggle", "TreeNodeToggle", "TreeNodeNoToggle" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_padding = vec4(4.f);
		});

		select({ "TabHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_padding = vec4(6.f);
		});

		select({ "Tooltip", "ToolButton", "ExpandboxBody" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(4.f);
		});

		select({ "Dockspace", "Toolbar", "Header", "Popup" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(6.f);
		});

		select({ "Modal" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(12.f);
		});

		select({ "ExpandboxBody" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(ivec4(32, 6, 8, 6));
		});

		select({ "ExpandboxBody", "WindowBody" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_spacing = vec2(4.f);
		});

		select({ "Dockbar", "Toolbar", "Menubar", "Header" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_spacing = vec2(6.f);
		});
		
		select({ "NodePlugs" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_padding = vec4(ivec4(-5, 0, -5, 0));
		});
		
		select({ "RadioChoiceItem" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_align = { CENTER, CENTER };
		});
	}

	void style_minimal(UiWindow& ui_window)
	{
		layout_minimal(ui_window);

		Colour white = { 1.f };
		Colour black = { 0.f };
		Colour transparent = { 0.f, 0.f };
		Colour clearGreyText = { 0.627f };
		Colour grey600 = { 0.600f };
		Colour grey400 = { 0.400f };
		Colour grey312 = { 0.312f };
		Colour grey248 = { 0.248f };
		Colour grey204 = { 0.204f };
		Colour grey176 = { 0.176f };
		Colour grey145 = { 0.145f };
		Colour grey117 = { 0.117f };
		Colour grey86  = { 0.086f };
		Colour grey69  = { 0.069f };
		Colour grey52  = { 0.052f };
		Colour activeBlue = { 0.145f, 0.5f, 1.f, 1.f };

		select({ "Label", "Title", "Message", "Tooltip", "TextEdit", "TypeLabel", "TypeZone", "SliderDisplay", "RadioChoiceItem" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_text_colour = white;
		})
		.decline({ DISABLED }, [&](InkStyle& i) {
			i.m_text_colour = grey248;
		});

		select({ "Element", "Button", "WrapButton", "MultiButton", "Toggle", "ToolButton", "TabHeader", "DockToggle", "RadioChoice", "DropdownChoice", "SliderKnob", "ScrollerKnob", "DragHandle", "DropdownInput", "DropdownInputCompact", "TypedownInput", "Menu", "TypeIn", "Input<string>", "TreeNodeHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i = styles().label.skin();
			i.m_background_colour = grey204;
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = grey312;
		})
		.decline({ ACTIVE, SELECTED, PRESSED, FOCUSED, ACTIVE|HOVERED, PRESSED|HOVERED, ACTIVE|PRESSED }, [&](InkStyle& i) {
			i.m_background_colour = activeBlue;
		});

		select({ "CloseButton", "Checkbox" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i = styles().button.skin();
		});

		select({ "Element", "TreeNodeHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = grey86;
		});

		select({ "SliderKnob", "ScrollerKnob" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i = styles().button.skin();
			i.m_background_colour = grey176;
		});

		select({ "SliderKnob" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = grey312;
			l.m_size = vec2(8, 22);
		});

		select({ "ScrollUp", "ScrollDown" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_image = ui_window.find_image("null");
			l.m_size = vec2(10, 0);
		});

		select({ "ScrollLeft", "ScrollRight" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_image = ui_window.find_image("null");
			l.m_size = vec2(0, 10);
		});

		/*select({ "ExpandboxToggle", "TreeNodeToggle" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_image = ui_window.find_image("toggle_closed");
		})
		.decline({ ACTIVE }, [&](InkStyle& i) {
			i.m_image = ui_window.find_image("toggle_open");
		})
		.decline({ DISABLED }, [&](InkStyle& i) {
			i.m_image = ui_window.find_image("empty_15");
		});*/

		select({ "DropdownToggle" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_image = ui_window.find_image("drop_down");
		});

		select({  "Checkbox" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			l.m_size = vec2(15.f);
			i.m_padding = vec4(1.f);
		})
		.decline({ ACTIVE }, [&](InkStyle& i) {
			i.m_image = ui_window.find_image("check_15");
		});

		select({ "Slider", "Fillbar", "TypeIn", "Input<string>"  })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = grey145;
			i.m_border_colour = grey312;
			i.m_border_width = vec4(1.f);
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = grey204;
			i.m_border_colour = grey400;
			i.m_border_width = vec4(1.f);
		})
		.decline({ FOCUSED }, [&](InkStyle& i) {
			i.m_background_colour = activeBlue;
		})
		.decline({ SELECTED }, [&](InkStyle& i) {
			i.m_border_colour = activeBlue;
		});

		select({ "Filler" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = grey248;
		});

		select({ "List", "Tree", "TabberHead", "TableHead", "Dockbar", "Header", "Menubar" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = grey117;
		});

		select({ "Window", "WindowFooter", "DockWindow", "Dockbox", "Tab", "TextEdit", "Node", "Section", "Popup", "Modal", "ColourPopup" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = grey52;
			i.m_border_colour = grey204;
			i.m_border_width = vec4(1.f);
		});

		select({ "Window", "Dockbox", "Node" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_shadow = { 2, 2, 7, 2 };
		})
		.decline({ SELECTED }, [&](InkStyle& i) {
			i.m_shadow = { 0, 0, 0, 1, grey600 };
		});

		select({ "WindowHeader", "WindowHeaderMovable", "NodeHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = grey204;
		});

		select({  "WindowSizer", "WindowSizerLeft", "WindowSizerRight"  })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_image = ui_window.find_image("handle_x");
			i.m_padding = vec4(2.f);
		});

		select({ "WindowSizerRight" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_align = { Right, Right };
		});

		select({  "Toolbar", "Tooldock"  })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = grey145;
		});

		select({ "Canvas" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = black;
		});

		select({  "Tooltip", "Popdown", "DropdownList", "MenuList", "SubMenuList"  })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = { 0.098f, 0.802f };
			i.m_text_colour = clearGreyText;
		});

		select({ "DropdownChoice" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = transparent;
		});

		select({ "TableRow", "TableRowOdd", "TableRowEven"  })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l); UNUSED(i);
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_border_colour = grey312;
			i.m_border_width = vec4(1.f);
		})
		.decline({ SELECTED }, [&](InkStyle& i) {
			i.m_border_colour = activeBlue;
			i.m_border_width = vec4(1.f);
		});

		select({ "TableRowOdd" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = grey117;
		});

		select({ "TableRowEven" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = black;
		});

		for(auto name_style : UiWindow::s_styles)
			name_style.second->prepare();
	}
}


#ifdef MUD_MODULES
module mud.ui;
#else
#endif

namespace mud
{
	ImageSkin::ImageSkin(Image& image, int left, int top, int right, int bottom, int margin, Dim stretch)
		: d_image(&image)
		, d_left(left), d_top(top), d_right(right), d_bottom(bottom)
		, m_margin(margin)
		, d_stretch(stretch)
		, d_size(image.d_size)
		, d_solid_size(image.d_size - uvec2(uint(margin + margin)))
		, d_fill_size(uvec2(image.d_size.x - d_left - d_right, image.d_size.y - d_top - d_bottom))
		, d_images()
	{
		for(Image& subimage : d_images)
			subimage = *d_image;

		m_min_size.x = d_stretch == DIM_X ? float(d_solid_size.x) : 0.f;
		m_min_size.y = d_stretch == DIM_Y ? float(d_solid_size.y) : 0.f;

		vec4 coords[Count] = {};
		this->stretch_coords(Zero2, vec2(image.d_size), array<vec4>{ coords, Count });
		for(size_t s = 0; s < Count; ++s)
		{
			this->d_images[s].d_coord = this->d_image->d_coord + uvec2(rect_offset(coords[s]));
			this->d_images[s].d_size = uvec2(rect_size(coords[s]));
		}
	}

	ImageSkin::ImageSkin(Image& image, const ImageSkin& ref)
		: ImageSkin(image, ref.d_left, ref.d_top, ref.d_right, ref.d_bottom, ref.m_margin, ref.d_stretch)
	{}

	ImageSkin::ImageSkin()
		: d_image(nullptr)
	{}

	void ImageSkin::stretch_coords(vec2 offset, vec2 size, array<vec4> coords) const
	{
		vec2 fill = { size.x - d_left - d_right, size.y - d_top - d_bottom };

		coords[TopLeft] = { offset.x, offset.y, float(d_left), float(d_top) };
		coords[TopRight] = { offset.x + fill.x + d_left, offset.y, float(d_right), float(d_top) };
		coords[BottomRight] = { offset.x + fill.x + d_left, offset.y + fill.y + d_top, float(d_right), float(d_bottom) };
		coords[BottomLeft] = { offset.x, offset.y + fill.y + d_top, float(d_left), float(d_bottom) };

		coords[Top] = { offset.x + d_left, offset.y, fill.x, float(d_top) };
		coords[Right] = { offset.x + fill.x + d_left, offset.y + d_top, float(d_right), fill.y };
		coords[Bottom] = { offset.x + d_left, offset.y + fill.y + d_top, fill.x, float(d_bottom) };
		coords[Left] = { offset.x, offset.y + d_top, float(d_left), fill.y };

		coords[Fill] = { offset.x + d_left, offset.y + d_top, fill.x, fill.y };
	}

	Styles& styles() { static Styles styles; return styles; }

	struct Style::Impl
	{
		string m_name;
		Layout m_layout;
		InkStyle m_skin;
		vector<InkStyle> m_skins;
	};

	Style::Style(cstring name, Style* base, LayoutDef layout, InkStyleDef skin, StyleDef style)
		: m_base(base)
		, m_impl(make_unique<Impl>())
	{
		if(UiWindow::s_styles[name] == nullptr)
			UiWindow::s_styles[name] = this;

		m_impl->m_name = name;
		m_impl->m_layout = { name };
		m_impl->m_skin = { name };
		m_impl->m_skins = {};

		if(m_base)
		{
			m_impl->m_layout = m_base->m_impl->m_layout;
			m_impl->m_layout.m_name = name;
		}

		if(layout)
			layout(m_impl->m_layout);
		if(skin)
			skin(m_impl->m_skin);
		if(style)
			style(*this);
	}

	Style::~Style()
	{}

	Style::Style(const Style& other)
		: m_base(other.m_base)
		, m_impl(make_unique<Impl>())
	{
		*this = other;
	}

	Style& Style::operator=(const Style& other)
	{
		m_impl->m_layout = other.m_impl->m_layout;
		m_impl->m_skin = other.m_impl->m_skin;
		m_impl->m_skins = other.m_impl->m_skins;
		return *this;
	}

	cstring Style::name() { return m_impl->m_name.c_str(); }
	Layout& Style::layout() { return m_impl->m_layout; }
	InkStyle& Style::skin() { return m_impl->m_skin; }

	void Style::prepare()
	{
		m_impl->m_skin.prepare();
		for(InkStyle& skin : m_impl->m_skins)
			skin.prepare();
	}

	InkStyle& Style::state_skin(WidgetState state)
	{
		// turn off non-skinnable state flags
		state = static_cast<WidgetState>(state & ~(CREATED | ACTIVATED | CLOSED));
		for(InkStyle& skin : reverse_adapt(m_impl->m_skins))
			if(state == skin.m_state) // exact match
				return skin;
		for(InkStyle& skin : reverse_adapt(m_impl->m_skins))
			if(state & skin.m_state) // partial match
				return skin;
		return m_impl->m_skin;
	}

	InkStyle& Style::decline_skin(WidgetState state)
	{
		for(InkStyle& skin : m_impl->m_skins)
			if(state == skin.m_state)
				return skin;

		m_impl->m_skins.emplace_back(m_impl->m_skin);
		m_impl->m_skins.back().m_name = m_impl->m_name + ":" + to_lower(flags_to_string<WidgetState, 9>(state));
		m_impl->m_skins.back().m_state = state;
		return m_impl->m_skins.back();
	}
}


#ifdef MUD_MODULES
module mud.ui;
#else
#endif

namespace mud
{
	Styles::Styles()
		: widget("Widget", nullptr, [](Layout& l) { l.m_solver = FRAME_SOLVER; })
		, wedge("Wedge", widget, [](Layout& l) { l.m_solver = ROW_SOLVER; l.m_space = SHEET; })
		, ui("Ui", wedge, [](Layout& l) { l.m_space = LAYOUT; l.m_clipping = CLIP; l.m_opacity = OPAQUE; })

		, unit("Unit", wedge, [](Layout& l) { l.m_space = UNIT; l.m_align = { Left, CENTER }; },
							  [](InkStyle& o) { o.m_empty = false; o.m_text_colour = Colour::White; o.m_padding = vec4(2.f); })
		, item("Item", widget, [](Layout& l) { l.m_space = BLOCK; l.m_align = { Left, CENTER }; },
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

		, label("Label", item, [](Layout& l) { l.m_align = { Left, CENTER }; })
		, title("Title", label, {}, [](InkStyle& o) { UNUSED(o); }) //o.m_text_size = 18.f; })
		, message("Message", label, {}, [](InkStyle& o) { UNUSED(o); }) //o.m_text_size = 18.f; })
		, text("Text", item, [](Layout& l) { l.m_space = { PARAGRAPH, FIXED, WRAP }; },
							 [](InkStyle& o) { o.m_text_break = true; })

		, button("Button", control, {})
		, wrap_button("WrapButton", wrap_control, {})
		, multi_button("MultiButton", wrap_button, {})
		, toggle("Toggle", control, {})
		, checkbox("Checkbox", toggle, [](Layout& l) { l.m_align = { Left, CENTER }; }) // @todo why doesn't work ?? why u checkbox not aligned ??

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

		, color_popup("ColourPopup", overlay, [](Layout& l) { l.m_flow = ALIGN; l.m_clipping = UNCLIP; l.m_align = { Left, OUT_RIGHT }; })
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
