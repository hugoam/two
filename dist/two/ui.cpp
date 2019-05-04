#include <two/ui.h>
#include <two/tree.h>
#include <two/math.h>
#include <two/ctx.h>
#include <two/infra.h>
#include <two/type.h>


#ifndef TWO_CPP_20
#include <cstring>
#endif

#ifdef TWO_MODULES
module two.ui;
#else
#endif

#include <cstdarg>
#include <cstdio>

namespace two
{
namespace ui
{
	Widget& spacer(Widget& parent) { return widget(parent, styles().spacer); }
	Widget& separator(Widget& parent) { return widget(parent, styles().separator); }

	Widget& icon(Widget& parent, cstring icon) { return item(parent, styles().item, icon); }
	Widget& label(Widget& parent, cstring label) { return item(parent, styles().label, label); }
	Widget& title(Widget& parent, cstring label) { return item(parent, styles().title, label); }
	Widget& message(Widget& parent, cstring label) { return item(parent, styles().message, label); }
	Widget& selectable(Widget& parent, cstring label, bool& selected) { return item(parent, styles().item, label); }

	Widget& text(Widget& parent, cstring label)
	{
		Widget& self = item(parent, styles().text);

		// @todo optimize (doesn't need to be done on each call)
		if(!self.m_frame.m_text)
			self.m_frame.m_text = make_unique<Text>(self.m_frame);
		self.m_frame.m_text->m_text = label;
		self.m_frame.m_text->update_style();
		self.m_frame.m_text->break_text_rows();

		return self;
	}

	Widget& bullet(Widget& parent, cstring label)
	{
		Widget& self = row(parent);
		item(self, styles().bullet);
		item(self, styles().text, label);
		return self;
	}

	Widget& icon(Widget& parent, const string& icon) { return item(parent, styles().item, icon); }
	Widget& label(Widget& parent, const string& label) { return item(parent, styles().label, label); }
	Widget& title(Widget& parent, const string& label) { return item(parent, styles().title, label); }
	Widget& message(Widget& parent, const string& label) { return item(parent, styles().message, label); }
	Widget& selectable(Widget& parent, const string& label, bool& selected) { return item(parent, styles().item, label); }
	Widget& text(Widget& parent, const string& label) { return text(parent, label.c_str()); }
	Widget& bullet(Widget& parent, const string& label) { return bullet(parent, label.c_str()); }

	int format(char* buf, size_t buf_size, const char* fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		int w = vsnprintf(buf, buf_size, fmt, args);
		va_end(args);
		if(w == -1 || w >= (int)buf_size)
			w = (int)buf_size - 1;
		buf[w] = 0;
		return w;
	}

	int format(char* buf, size_t buf_size, const char* fmt, va_list args)
	{
		int w = vsnprintf(buf, buf_size, fmt, args);
		if(w == -1 || w >= (int)buf_size)
			w = (int)buf_size - 1;
		buf[w] = 0;
		return w;
	}

	Widget& labelfv(Widget& parent, const char* fmt, va_list args)
	{
		static char buffer[1024];
		int len = format(buffer, 1024, fmt, args);
		return label(parent, string(buffer, len));
	}

	Widget& labelf(Widget& parent, const char* fmt, ...)
	{
		static char buffer[1024];
		va_list args;
		va_start(args, fmt);
		int len = format(buffer, 1024, fmt, args);
		va_end(args);
		return label(parent, string(buffer, len));
	}

	void button_logic(Widget& self)
	{
		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::Pressed))
			self.enable_state(PRESSED);
		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::Released))
			self.disable_state(PRESSED);

		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
		{
			self.enable_state(ACTIVATED);
			event.consume(self);
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

	Widget& multi_button(Widget& parent, Style& style, span<cstring> elements, Style* element_style)
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

	Widget& multi_toggle(Widget& parent, Style& style, bool& on, span<cstring> elements, Style* element_style)
	{
		Widget& self = multi_item(parent, style, elements, element_style);
		toggle_logic(self, on);
		return self;
	}

	Widget& button(Widget& parent, cstring content) { return button(parent, styles().button, content); }
	Widget& toggle(Widget& parent, bool& on, cstring content) { return toggle(parent, styles().toggle, on, content); }

	Widget& button(Widget& parent, const string& content) { return button(parent, styles().button, content.c_str()); }
	Widget& toggle(Widget& parent, bool& on, const string& content) { return toggle(parent, styles().toggle, on, content.c_str()); }

	Widget& multi_button(Widget& parent, span<cstring> elements, Style* element_style)
{
		return multi_button(parent, styles().multi_button, elements, element_style);
	}

	Widget& multi_toggle(Widget& parent, bool& on, span<cstring> elements, Style* element_style)
	{
		return multi_toggle(parent, styles().multi_button, on, elements, element_style);
	}

	bool modal_button(Widget& screen, Widget& parent, cstring content, uint32_t mode)
	{
		if(button(parent, content).activated())
			screen.m_switch |= mode;
		return (screen.m_switch & mode) != 0;
	}

	bool modal_multi_button(Widget& screen, Widget& parent, span<cstring> elements, uint32_t mode)
	{
		if(multi_button(parent, elements).activated())
			screen.m_switch |= mode;
		return (screen.m_switch & mode) != 0;
	}

	Widget& checkbox(Widget& parent, bool& on)
	{
		Widget& self = toggle(parent, styles().checkbox, on);
		if(on)
			item(parent, styles().checkmark);
		return self;
	}

	Widget& fill_bar(Widget& parent, float percentage, Axis dim)
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
			image = &self.ui_window().create_image(name, source.m_size, data, false);
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

	Widget& radio_button(Widget& parent, cstring label, uint32_t& value, uint32_t index)
	{
		Widget& self = multi_button(parent, styles().radio_choice, { label }, &styles().radio_choice_item);
		self.set_state(ACTIVE, value == index);
		if(self.activated())
			value = index;
		return self;
	}

	Widget& radio_choice(Widget& parent, cstring label, bool active)
	{
		Widget& self = multi_button(parent, styles().radio_choice, { label }, &styles().radio_choice_item);
		self.set_state(ACTIVE, active);
		return self;
	}

	bool radio_switch(Widget& parent, span<cstring> labels, uint32_t& value, Axis dim)
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

	Widget& dropdown(Widget& parent, Style& style, cstring value, PopupFlags popup_flags, bool no_toggle, Style* list_style)
	{
		bool hovered = false;
		Widget& self = widget(parent, style);
		Widget& header = multi_toggle(self, dropdown_styles().head, self.m_open, { value });
		hovered |= header.hovered();
		if(!no_toggle)
		{
			Widget& button = toggle(self, dropdown_styles().toggle, self.m_open);
			hovered |= button.hovered();
		}

		self.set_state(HOVERED, hovered);
		self.m_body = nullptr;

		if(self.m_open)
		{
			self.m_body = &popup(self, list_style ? *list_style : dropdown_styles().list, popup_flags);
			self.m_open &= self.m_body->m_open;
		}

		return self;
	}

	Widget& dropdown_choice(Widget& parent, span<cstring> elements, bool active)
	{
		Widget& self = multi_button(parent, dropdown_styles().choice, elements);
		self.set_state(ACTIVE, active);
		return self;
	}

	bool popdown(Widget& parent, span<cstring> choices, uint32_t& value, vec2 position, PopupFlags popup_flags)
	{
		Widget& self = popup_at(parent, dropdown_styles().popdown, position, popup_flags);
		ScrollSheet& sheet = scroll_sheet(self);

		for(uint32_t i = 0; i < uint32_t(choices.size()); ++i)
			if(dropdown_choice(*sheet.m_body, { choices[i] }, i == value).activated())
			{
				value = i;
				return true;
			}
		return false;
	}

	bool dropdown_input(Widget& parent, span<cstring> choices, uint32_t& value, bool compact)
	{
		if(value >= choices.size())
			value = uint32_t(choices.size()) - 1;
		Style& style = compact ? dropdown_styles().dropdown_input_compact : dropdown_styles().dropdown_input;
		Widget& self = dropdown(parent, style, value == UINT32_MAX ? "" : choices[value], PopupFlags::AutoModal);
		if(!self.m_body) return false;

		for(uint32_t i = 0; i < uint32_t(choices.size()); ++i)
			if(dropdown_choice(*self.m_body, { choices[i] }, value == i).activated())
			{
				value = i;
				self.m_open = false;
				return true;
			}

		return false;
	}

	bool typedown_input(Widget& parent, span<cstring> choices, uint32_t& value)
	{
		bool changed = dropdown_input(parent, choices, value); //dropdown_styles().typedown_input
		//if(scope->m_state & ACTIVATED)
		//	filter_input(self);
		return changed;
	}

	Widget& menu_choice(Widget& parent, span<cstring> elements)
	{
		Widget& self = multi_button(parent, menu_styles().choice, elements);
		if(self.activated())
			self.m_parent->m_parent->m_open = false;
		return self;
	}

	Widget& menu_choice(Widget& parent, cstring content, cstring shortcut)
	{
		UNUSED(shortcut);
		return menu_choice(parent, span<cstring>{ content });
	}

	Widget& menu_option(Widget& parent, cstring content, cstring shortcut, bool enabled)
	{
		UNUSED(shortcut); UNUSED(enabled);
		return menu_choice(parent, span<cstring>{ content });
	}

	Widget& menu(Widget& parent, cstring label, bool submenu)
	{
		Style& list_style = submenu ? menu_styles().sublist : menu_styles().list;
		return dropdown(parent, menu_styles().menu, label, submenu ? PopupFlags::None : PopupFlags::AutoModal, true, &list_style);
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


#ifdef TWO_MODULES
module two.ui;
#else
#endif

namespace two
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


#ifdef TWO_MODULES
module two.ui;
#else
#include <stl/algorithm.h>
#endif

namespace two
{
	Table::Table(Widget* parent, void* identity, span<float> weights)
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

	Table& columns(Widget& parent, span<float> weights)
	{
		Table& self = parent.suba<Table, span<float>>(weights);
		self.init(styles().table);

		as<TableSolver>(*self.m_frame.m_solver).update(self.m_weights);

		return self;
	}
	
	Table& table(Widget& parent, size_t columns, span<float> weights)
	{
		if(weights.size() > 0)
			return parent.suba<Table, span<float>>(weights);
		else
			return parent.suba<Table, size_t>(columns);
	}

	Table& table(Widget& parent, span<cstring> columns, span<float> weights)
	{
		Table& self = table(parent, columns.size(), weights);
		self.init(styles().table);

		Widget& header = grid_sheet(self, styles().table_head, Axis::X, self.m_weights); // [this](Frame& first, Frame& second) { this->resize(first, second); }

		as<TableSolver>(*self.m_frame.m_solver).update(self.m_weights);

		for(size_t i = 0; i < columns.size(); ++i)
		{
			Widget& column = spanner(header, styles().column_header, Axis::X, self.m_weights[i]);
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

	Widget& toggle_header(Widget& parent, Style& header_style, Style& toggle_style, span<cstring> elements, bool& open)
	{
		Widget& self = button(parent, header_style);
		Widget& button = toggle(self, toggle_style, open);
		multi_item(self, styles().row, elements);
		self.set_state(HOVERED, self.hovered() || button.hovered());
		return self;
	}

	Expandbox& expandbox(Widget& parent, span<cstring> elements, bool open)
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

	TreeNode& tree_node(Widget& parent, span<cstring> elements, bool leaf, bool open)
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
		widget(self, tabber_styles().edge);
		//separator(self);
		self.m_body = &widget(self, tabber_styles().body);
		self.m_index = 0;
		return self;
	}
}
}


#ifdef TWO_MODULES
module two.ui;
#else
#endif

namespace two
{
namespace ui
{
	void TableStyles::reset()
	{
		row = Style("TableRow", styles().wrap_button, {});
		row_odd = Style("TableRowOdd", row, {}, [](InkStyle& l) { l.m_empty = false; });
		row_even = Style("TableRowEven", row, {}, [](InkStyle& l) { l.m_empty = false; });
		separator = Style("TableSeparator", styles().row, [](Layout& l) { l.m_no_grid = true; });

		register_styles({ &row, &row_odd, &row_even, &separator });
	}

	void ExpandboxStyles::reset()
	{
		expandbox = Style("Expandbox", styles().stack, {});
		header = Style("ExpandboxHeader", styles().wrap_button, {});
		toggle = Style("ExpandboxToggle", styles().toggle, {});
		body = Style("ExpandboxBody", styles().stack, [](Layout& l) {}); //  l.m_padding = vec4(12.f, 2.f, 0.f, 2.f); l.m_spacing = vec2(0.f); 

		register_styles({ &expandbox, &header, &toggle, &body });
	}

	void TreeNodeStyles::reset()
	{
		treenode = Style("TreeNode", expandbox_styles().expandbox, {});
		header = Style("TreeNodeHeader", expandbox_styles().header, {});
		toggle = Style("TreeNodeToggle", expandbox_styles().toggle, {});
		no_toggle = Style("TreeNodeNoToggle", toggle, {});
		body = Style("TreeNodeBody", expandbox_styles().body, [](Layout& l) {}); // l.m_padding = vec4(18.f, 0.f, 0.f, 0.f); l.m_spacing = vec2(0.f); 

		register_styles({ &treenode, &header, &toggle, &no_toggle, &body });
	}

	void TabberStyles::reset()
	{
		tab = Style("Tab", styles().wedge, [](Layout& l) { l.m_clipping = Clip::Clip; });
		tab_button = Style("TabHeader", styles().button, {});
		tabber = Style("Tabber", styles().wedge, {});
		head = Style("TabberHead", styles().row, {});
		edge = Style("TabberEdge", styles().separator, {});
		body = Style("TabberBody", styles().sheet, {});

		register_styles({ &tab, &tab_button, &tabber, &head, &edge, &body });
	}

	void FileStyles::reset()
	{
		dir = Style("Dir", styles().multi_button, {});
		file = Style("File", styles().multi_button, {});

		register_styles({ &dir, &file });
	}

	TableStyles& table_styles() { static TableStyles styles; return styles; }
	ExpandboxStyles& expandbox_styles() { static ExpandboxStyles styles; return styles; }
	TreeNodeStyles& treenode_styles() { static TreeNodeStyles styles; return styles; }
	TabberStyles& tabber_styles() { static TabberStyles styles; return styles; }
	FileStyles& file_styles() { static FileStyles styles; return styles; }
}
}


#ifdef TWO_MODULES
module two.ui;
#else
#endif

#include <cstdio>

namespace two
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
		const vec2 position = parent.ui().m_mouse.m_pos + vec2(4.f) - parent.m_frame.absolute_position();
		return hoverbox(parent, position, delay);
	}

	Widget* tooltip(Widget& parent, const vec2& position, span<cstring> elements)
	{
		Widget* self = hoverbox(parent, position);
		if(self)
			multi_item(*self, styles().tooltip, elements);
		return self;
	}

	Widget* tooltip(Widget& parent, span<cstring> elements)
	{
		const vec2 position = parent.ui().m_mouse.m_pos + vec2(4.f) - parent.m_frame.absolute_position();
		return tooltip(parent, position, elements);
	}

	Widget* tooltip(Widget& parent, cstring element)
	{
		return tooltip(parent, { &element, 1 });
	}

	Widget* tooltip(Widget& parent, const Frame& parent_frame)
	{
		return hoverbox(parent, vec2(0.f, 0.f + parent_frame.m_size.y));
	}

	Widget* tooltip(Widget& parent, const Frame& parent_frame, span<cstring> elements)
	{
		return tooltip(parent, vec2(parent_frame.m_position.x, parent_frame.m_position.y + parent_frame.m_size.y), elements);
	}

	Widget* tooltip(Widget& parent, const Frame& parent_frame, cstring element)
	{
		return tooltip(parent, parent_frame, { &element, 1 });
	}

	Widget& rectangle(Widget& parent, const vec4& rect)
	{
		Widget& self = widget(parent, styles().rectangle).layer();
		self.m_frame.set_position(rect.pos);
		self.m_frame.set_size(rect.size);
		return self;
	}

	Widget& viewport(Widget& parent, const vec4& rect)
	{
		Widget& self = widget(parent, styles().viewport).layer();
		self.m_frame.set_position(rect.pos);
		self.m_frame.set_size(rect.size);
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
		Style* style = hovered.m_frame.d_style->m_skin.m_hover_cursor ? hovered.m_frame.d_style->m_skin.m_hover_cursor : &cursor_styles().cursor;
		return cursor(parent, position, *style, locked);
	}
}
}


#ifdef TWO_MODULES
module two.ui;
#else
#include <stl/string.h>
#include <stl/map.h>
#include <stl/algorithm.h>
#endif

namespace two
{
namespace ui
{
	Widget& dockline(Widget& parent, uint16_t index, Axis dim)
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
		self.m_mainline = &dockline(self, 0, Axis::Y);
		return self;
	}

	Dockbar& dockbar(Widget& parent, Docksystem& docksystem)
	{
		Dockbar& self = parent.suba<Dockbar, Docksystem&>(docksystem);
		self.init(dock_styles().dockbar).layer();

		self.m_togglebar = &widget(self, dock_styles().docktabs);

		Widget& drag_handle = widget(self, styles().drag_handle);
		if(MouseEvent event = drag_handle.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
			self.width -= event.m_delta.x;

		self.m_dockzone = &widget(self, dock_styles().dockdiv);
		if(self.m_current_tab == SIZE_MAX)
			self.m_dockzone->m_frame.m_size = vec2(0.f);
		else
			self.m_dockzone->m_frame.m_size = vec2(self.width, 0.f);

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
			Window& container = window(parent, dock.m_name, WindowState(uint(WindowState::Dockable) | uint(WindowState::Default)), &dock);
			container.m_dock = &dock;
			return &container;
		}
	}

	Widget* dockitem(Docker& docker, cstring name, span<uint16_t> dockid, float span)
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


#ifdef TWO_MODULES
module two.ui;
#else
#include <stl/algorithm.h>
#endif

namespace two
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
		remove(m_docks, (Dock*)&dockable);

		dockable.m_dock->m_dockid = {};
	}

	void Docker::shift(Dock& start, bool add)
	{
		vector<uint16_t> root = start.m_dockid;
		uint16_t index = pop(root);

		size_t level = root.size();
		for(Dock* dock : m_docks)
			if(contains(dock->m_dockid, root)
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
		return static_cast<Dockable&>(*widget);
	}

	Widget* Dockspace::docksection(Dock& dock)
	{
		vector<uint16_t> dockid = reverse(dock.m_dockid);
		Widget* line = m_mainline;

		Axis dim = Axis::Y;
		while(dockid.size() > 0)
		{
			uint16_t index = pop(dockid);
			dim = flip(dim);
			line = &ui::dockline(*line, index, dim);
			if(dockid.size() == 0 && dock.m_span > 0.f && line->m_frame.m_span[flip(dim)] == 1.f)
				line->m_frame.set_span(flip(dim), dock.m_span);
		}

		Tabber& section = ui::docksection(*line);
		Widget* tab = ui::tab(section, dock.m_name); // dock_styles().docktab, 

		if(tab)
		{
			Window& container = ui::window(*tab, dock.m_name, WindowState::Dockable, nullptr, &dock);
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

		Axis dim = Axis(target.m_dockid.size() % 2);
		Axis ortho = flip(dim);

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


#ifdef TWO_MODULES
module two.ui;
#else
#endif

#include <iostream>

namespace two
{
namespace ui
{
	template bool slider_input(Widget& parent, int& value, StatDef<int> def, Axis dim);
	template bool slider_input(Widget& parent, float& value, StatDef<float> def, Axis dim);

	template bool number_input(Widget& parent, int& value, StatDef<int> def);
	template bool number_input(Widget& parent, float& value, StatDef<float> def);

	//template bool input(Widget& parent, bool& value);
	//template bool input(Widget& parent, string& value);
	template bool input(Widget& parent, int& value, StatDef<int> def);
	template bool input(Widget& parent, float& value, StatDef<float> def);

	bool drag_float(Widget& parent, float& value, float step)
	{
		string text = truncate_number(to_string(value));
		TextEdit& self = type_in(parent, text, 0, "1234567890.");
		self.m_focus_mode = TextFocusMode::Click;
		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
		{
			self.clear_focus();
			value += event.m_delta.x * step;
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

	bool float2_input(Widget& parent, span<cstring> labels, span<float> vals, StatDef<float> def)
	{
		UNUSED(labels); // @todo
		Widget& self = ui::row(parent);
		bool changed = false;
		for(size_t i = 0; i < 2; ++i)
			changed |= ui::number_input<float>(self, vals[i], def);
		return changed;
	}

	bool float3_input(Widget& parent, span<cstring> labels, span<float> vals, StatDef<float> def)
	{
		UNUSED(labels); // @todo
		Widget& self = ui::row(parent);
		bool changed = false;
		for(size_t i = 0; i < 3; ++i)
			changed |= ui::number_input<float>(self, vals[i], def);
		return changed;
	}

	bool float4_input(Widget& parent, span<cstring> labels, span<float> vals, StatDef<float> def)
	{
		UNUSED(labels); // @todo
		Widget& self = ui::row(parent);
		bool changed = false;
		for(size_t i = 0; i < 4; ++i)
			changed |= ui::number_input<float>(self, vals[i], def);
		return changed;
	}

	bool float2_slider(Widget& parent, cstring label, span<cstring> labels, span<float> vals, StatDef<float> def)
	{
		Widget& self = ui::row(parent);
		bool changed = ui::float2_input(self, labels, vals, def);
		ui::label(self, label);
		return changed;
	}

	bool float3_slider(Widget& parent, cstring label, span<cstring> labels, span<float> vals, StatDef<float> def)
	{
		Widget& self = ui::row(parent);
		bool changed = ui::float3_input(self, labels, vals, def);
		ui::label(self, label);
		return changed;
	}

	bool float4_slider(Widget& parent, cstring label, span<cstring> labels, span<float> vals, StatDef<float> def)
	{
		Widget& self = ui::row(parent);
		bool changed = ui::float4_input(self, labels, vals, def);
		ui::label(self, label);
		return changed;
	}

	bool vec2_edit(Widget& parent, vec2& vec)
	{
		return float2_input(parent, {}, vec.f);
	}

	bool vec3_edit(Widget& parent, vec3& vec)
	{
		return float3_input(parent, {}, vec.f);
	}

	bool quat_edit(Widget& parent, quat& quat)
	{
		return float4_input(parent, {}, quat.f, { 0.f, 1.f, 0.01f });
	}

	constexpr float color_wheel_padding = 5.0f;
	constexpr float color_wheel_thickness = 20.0f;

	void draw_color_wheel(Vg& vg, const vec2& size, float hue, float s, float l)
	{
		const vec2 center = size * 0.5f;
		const float r1 = (size.x < size.y ? size.x : size.y) * 0.5f - color_wheel_padding;
		const float r0 = r1 - color_wheel_thickness;

		vg.draw_color_wheel(center, r0, r1);
		vg.draw_color_triangle(center, r0, hue, s, l);
	}

	bool inside_color_wheel(Widget& self, const MouseEvent& event)
	{
		const vec2 center = self.m_frame.m_size * 0.5f;
		const float r1 = center.x - color_wheel_padding;
		const float r0 = r1 - color_wheel_thickness;
		const float dist = distance(center, event.m_relative);
		return dist <= r1 && dist >= r0;
	}

	void drag_color_wheel(Widget& self, ColourHSL& hsla, const MouseEvent& event)
	{
		const vec2 coord = { event.m_relative.x, self.m_frame.m_size.y - event.m_relative.y };
		const vec2 center = self.m_frame.m_size * 0.5f;
		const vec2 vec = normalize(coord - center);
		const float angle = oriented_angle_2d(vec, vec2(1.f, 0.f));
		hsla.h = angle / c_2pi;
	}

	bool color_wheel(Widget& parent, ColourHSL& hsla)
	{
		Widget& self = widget(parent, styles().color_wheel);
		self.m_custom_draw = [=](const Frame& frame, const vec4& rect, Vg& vg)
		{
			UNUSED(rect);
			draw_color_wheel(vg, frame.m_size, hsla.h, hsla.s, hsla.l);
		};
		bool changed = false;

		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::Pressed))
		{
			changed = true;
			if(inside_color_wheel(self, event))
				drag_color_wheel(self, hsla, event);
		}

		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
		{
			changed = true;
			drag_color_wheel(self, hsla, event);
		}

		return changed;
	}

	bool color_edit_hsl(Widget& parent, const Colour& colour, ColourHSL& hsla)
	{
		static cstring columns[2] = { "field", "value" };
		Widget& self = table(parent, { columns, 2 }, {}); // , { 0.3f, 0.7f }
		color_display_field(self, "color", colour);

		bool changed = false;
		StatDef<float> def = { 0.f, 1.f, 0.01f };
		changed |= slider_field(self, "hue", hsla.h, def);
		changed |= slider_field(self, "saturation", hsla.s, def);
		changed |= slider_field(self, "lightness", hsla.l, def);

		return changed;
	}

	bool color_edit_simple(Widget& parent, Colour& value)
	{
		Widget& self = widget(parent, styles().input_color);
		color_slab(self, styles().color_slab, value);

		bool changed = false;
		StatDef<float> def = { 0.f, 1.f, 0.01f };
		changed |= slider_input<float>(self, value.r, def);
		changed |= slider_input<float>(self, value.g, def);
		changed |= slider_input<float>(self, value.b, def);

		return changed;
	}

	bool color_edit(Widget& parent, Colour& value)
	{
		ColourHSL hsla = to_hsla(value);
		Widget& self = stack(parent);
		bool changed = false;
		changed |= color_wheel(self, hsla);
		changed |= color_edit_hsl(self, value, hsla);
		value = to_rgba(hsla);
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
			vg.draw_rect({ vec2(0.f), frame.m_size }, value, frame.d_inkstyle->m_corner_radius);
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
		Curve(const vec2& size, float min, float max, span<float> values, span<float> points)
			: m_min(min), m_max(max), m_values(values), m_points(points)
		{
			m_scale = size * vec2(1.f, max - min);
		}

		float m_min;
		float m_max;
		span<float> m_values;
		span<float> m_points;
		vec2 m_scale;

		vec2 point(size_t i)
		{
			float t = m_points.size() > 0 ? m_points[i] : i / float(m_values.size() - 1);
			return m_scale * vec2(t, (m_values[i] - m_min));
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
			vg.path_bezier(begin, begin + vec2(distance, 0.f), end - vec2(distance, 0.f), end, false);
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

	bool curve_graph(Widget& parent, span<float> values, span<float> points)
	{
		const float lowest = 0.f;
		const float highest = 1.f;

		Widget& self = widget(parent, styles().curve_graph);
		Curve curve = { self.m_frame.content_rect().size, lowest, highest, values, points };
		
		static size_t hovered = SIZE_MAX;
		static size_t dragged = SIZE_MAX;

		if(self.ui().m_hovered == &self)
			hovered = curve.point_at(self.m_frame.local_position(self.ui().m_mouse.m_pos));

		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::Pressed))
			dragged = curve.point_at(event.m_relative);

		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
			if(dragged != SIZE_MAX)
			{
				vec2 delta = event.m_delta / curve.m_scale;
				curve.m_values[dragged] = clamp(curve.m_values[dragged] + delta.y, lowest, highest);
			}

		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::Released))
			dragged = SIZE_MAX;

		self.m_custom_draw = [&](const Frame& frame, const vec4& rect, Vg& vg)
		{
			UNUSED(frame); UNUSED(rect);
			Curve curve = { rect.size, 0.f, 1.f, values, points };
			vg.draw_rect(rect, { Colour::DarkGrey });
			draw_curve(Colour::NeonGreen, curve, hovered, vg);
			draw_points(Colour::NeonGreen, curve, hovered, vg);
		};

		return false;
	}

	bool curve_edit(Widget& parent, span<float> values, span<float> points)
	{
		Widget& self = widget(parent, styles().curve_input);
		curve_graph(self, values, points);
		return false;
	}

	bool curve_edit(Widget& parent, span<Colour> values, span<float> points)
	{
		UNUSED(parent); UNUSED(values); UNUSED(points);
		return false;
	}
}
}


#ifdef TWO_MODULES
module two.ui;
#else
#include <stl/algorithm.h>
//#include <ui/Extern.h>
#endif

namespace two
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
		
		static Layout layout_overlay = [](Layout& l) { l.m_space = Preset::Board; };
		static Layout layout_line = [](Layout& l) { l.m_space = Preset::Item; l.m_align = { Align::Center, Align::Center }; l.m_padding = vec4(20.f); l.m_spacing = vec2(100.f); };
		static Layout layout_column = [](Layout& l) { l.m_space = Preset::Unit; l.m_align = { Align::Left, Align::Center }; l.m_padding = vec4(20.f); l.m_spacing = vec2(20.f); };
		static Layout layout_node = [](Layout& l) { l.m_space = Preset::Block; };

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
			columns.push_back({ &line, &layout_column });
			solvers.push_back(&columns.back());
		}

		for(size_t i = 0; i < canvas.m_nodes.size(); ++i)
		{
			elements.push_back({ &columns[canvas.m_nodes[i]->m_order + shift], &layout_node, &canvas.m_nodes[i]->m_frame });
			elements.back().sync();
			solvers.push_back(&elements.back());
		}

		relayout(solvers);
	}

	void draw_node_cable(vec2 pos_out, vec2 pos_in, const Colour& colour_out, const Colour& colour_in, bool straight, Vg& vg)
	{
		float distance = straight ? 20.f : 100.f;
		Gradient paint = { colour_out, colour_in };
		vg.path_bezier(pos_out, pos_out + vec2(distance, 0.f), pos_in - vec2(distance, 0.f), pos_in, straight);
		vg.stroke_gradient(paint, 1.f, pos_out, pos_in);
	}

	Widget& node_knob(Widget& parent, Style& style, const Colour& colour, bool active, bool connected)
	{
		Widget& self = widget(parent, style);
		static Colour disabled_colour = Colour::DarkGrey;
		self.m_custom_draw = [=](const Frame& frame, const vec4& rect, Vg& vg)
		{
			UNUSED(rect); draw_knob(frame, active ? colour : disabled_colour, connected, vg);
		};
		return self;
	}

	Widget& canvas_cable(Widget& parent, NodeKnob& out, NodeKnob& in, bool straight = false)
	{
		Widget& self = widget(parent, node_styles().cable);
		self.m_frame.m_position = min(out.m_end, in.m_end);
		self.m_frame.m_size = max(out.m_end, in.m_end) - self.m_frame.m_position;
		self.m_custom_draw = [&, straight](const Frame& frame, const vec4& rect, Vg& vg)
		{
			UNUSED(rect); draw_node_cable(out.m_end - frame.m_position, in.m_end - frame.m_position, out.m_colour, in.m_colour, straight, vg);
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

	Widget& node_cable(Canvas& canvas, NodePlug& out, NodePlug& in)
	{
		return canvas_cable(*canvas.m_plan, out, in, !canvas.m_rounded_links);
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

		self.m_end = input ? plug_at_in(canvas, self) : plug_at_out(canvas, self);

		CanvasConnect& connect = canvas.m_connect;

		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
		{
			Widget* target = static_cast<Widget*>(event.m_target);
			NodePlug* target_plug = nullptr;
			if(target && target->m_frame.d_style == &node_styles().plug && target != &self)
				target_plug = static_cast<NodePlug*>(target);

			connect.m_origin = &self;
			connect.m_in = input ? &self : target_plug;
			connect.m_out = input ? target_plug : &self;
			connect.m_position = event.m_pos;

			if(target_plug)
			{
				connect.m_end = *target_plug;
			}
			else
			{
				connect.m_end.m_end = canvas.m_plan->m_frame.local_position(connect.m_position);
				connect.m_end.m_colour = self.m_colour;
			}
		}

		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::DragEnded))
		{
			canvas.m_connect.m_done = true;
		}

		return self;
	}

	Widget& node_header(Widget& parent, span<cstring> title)
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
		select(canvas.m_selection, &node);
		node.enable_state(SELECTED);
	}

	void canvas_swap_select(Canvas& canvas, Node& node)
	{
		bool selected = select_swap(canvas.m_selection, &node);
		node.set_state(SELECTED, selected);
	}

	template <class T>
	inline T& ttwidget(Widget& parent, Style& style, void* identity)
	{
		T& self = parent.subi<T>(identity); self.init(style); return self;
	}

	Node& node(Canvas& parent, span<cstring> title, int order, Ref identity)
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

		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::Stroked, InputMod::Shift))
			canvas_swap_select(parent, self);
		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
			canvas_select(parent, self);
		if(MouseEvent event = self.mouse_event(DeviceType::MouseRight, EventType::Stroked))
			canvas_select(parent, self);

		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
		{
			if(!has(parent.m_selection, &self))
				canvas_select(parent, self);

			for(Node* node : parent.m_selection)
				node->m_frame.set_position(node->m_frame.m_position + event.m_delta / node->m_frame.absolute_scale());
		}

		self.m_index = uint32_t(parent.m_nodes.size());
		parent.m_nodes.push_back(&self);

		return self;
	}

	Node& node(Canvas& parent, span<cstring> title, float* position, int order, Ref identity)
	{
		Node& self = node(parent, title, order, identity);
		if(self.once())// && position != vec2(0.f))
			self.m_frame.set_position({ position[0], position[1] });
		else
		{
			position[0] = self.m_frame.m_position.x;
			position[1] = self.m_frame.m_position.y;
		}
		return self;
	}

	Node& node(Canvas& parent, span<cstring> title, vec2& position, int order, Ref identity)
	{
		return node(parent, title, &position[0], order, identity);
	}

	Node& node(Canvas& parent, cstring title, vec2& position, int order, Ref identity)
	{
		return node(parent, { title }, &position[0], order, identity);
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

		if(MouseEvent event = self.m_scroll_plan->mouse_event(DeviceType::MouseLeft, EventType::Dragged))
		{
			for(Node* node : self.m_selection)
				node->m_frame.set_position(node->m_frame.m_position + event.m_delta / node->m_frame.absolute_scale());
		}

		if(MouseEvent event = self.m_scroll_plan->mouse_event(DeviceType::MouseLeft, EventType::Stroked))
			canvas_clear_select(self);

		if(MouseEvent event = self.m_scroll_plan->mouse_event(DeviceType::MouseMiddle, EventType::Stroked))
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
			canvas_cable(*canvas.m_plan, connect.m_out ? *connect.m_out : connect.m_end, connect.m_in ?  *connect.m_in : connect.m_end);

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
			static NodeKnob dum = { vec2(0.f), Colour(0.f, 0.f) };
			canvas_cable(*canvas.m_plan, dum, dum);
			connect = {};
		}

		return connection;
	}
}
}


#ifdef TWO_MODULES
module two.ui;
#else
#endif

namespace two
{
namespace ui
{
	bool overflow(Frame& frame, Frame& content, Axis dim)
	{
		float visible_size = frame.m_size[dim];
		float content_size = content.m_size[dim] * content.m_scale;
		return content_size - visible_size > 0.f;
	}

	void scroll_to(Frame& content, Axis dim, float offset)
	{
		content.set_position(dim, -offset);
		//content.layer().setForceRedraw();
	}

	bool scroller(Widget& parent, float& cursor, float overflow, float visible_size, Axis dim)
	{
		return slider(parent, scrollbar_styles().scroller, cursor, SliderMetrics{ 0.f, overflow, 1.f, visible_size },
					  dim, true, false, &scrollbar_styles().scroller_knob);
	}

	Widget& scrollbar(Widget& parent, Frame& frame, Frame& content, Axis dim, v2<size_t> grid_index)
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

		Widget& rewind = button(scrollbar, dim == Axis::Y ? scrollbar_styles().scroll_up
														: scrollbar_styles().scroll_left);

		scroller(scrollbar, cursor, overflow, visible_size, dim);

		Widget& forward = button(scrollbar, dim == Axis::Y ? scrollbar_styles().scroll_down
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

#ifdef TWO_MODULES
module two.ui;
#else
#endif

namespace two
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
		static const Paint main_paint = Paint(Colour(0.162f), 1.f);
		static const Paint second_paint = Paint(Colour(0.094f), 0.5f);

		draw_grid(frame, 20.0f, second_paint, vg);
		draw_grid(frame, 100.f, main_paint, vg);
	}

	void scroll_plan_drag(Frame& scroll_zone, Frame& scroll_plan, const MouseEvent& event)
	{
		const vec2 position = scroll_plan.m_position + event.m_delta;
		const vec2 overflow = (scroll_plan.m_size * scroll_plan.m_scale) - scroll_zone.m_size;
		scroll_plan.set_position(min(vec2(0.f), max(position, -overflow)));
		//m_frame.mark_dirty(DIRTY_FORCE_LAYOUT);
	}

	void scroll_plan_drag(ScrollSheet& scroll_sheet, const MouseEvent& mouse_event)
	{
		return scroll_plan_drag(scroll_sheet.m_scroll_zone->m_frame, scroll_sheet.m_body->m_frame, mouse_event);
	}

	void scroll_plan_zoom(Frame& scroll_zone, Frame& scroll_plan, const MouseEvent& mouse_event, bool clamped)
	{
		const float delta_scale = mouse_event.m_deltaZ > 0.f ? 1.2f : 0.8333f;
		scroll_plan.m_scale = scroll_plan.m_scale * delta_scale;

		if(clamped)
		{
			const vec2 min_scale = scroll_zone.m_size / scroll_plan.m_size;
			scroll_plan.m_scale = max(scroll_plan.m_scale, max(min_scale.x, min_scale.y));
		}

		const vec2 relative = mouse_event.m_pos - scroll_plan.absolute_position();
		const vec2 offset = relative - relative * delta_scale;
		const vec2 position = offset + scroll_plan.m_position;

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
		self.m_scroll_zone = &widget(self, styles().scroll_zone, false, Axis::None, { 0, 0 });
		self.m_body = &widget(*self.m_scroll_zone, surface_style ? *surface_style : styles().scroll_surface);

		scrollbar(self, self.m_scroll_zone->m_frame, self.m_body->m_frame, Axis::X, { 0, 1 });
		scrollbar(self, self.m_scroll_zone->m_frame, self.m_body->m_frame, Axis::Y, { 1, 0 });

#if 0
		if(MouseEvent event = self.mouse_event(DeviceType::MouseMiddle, EventType::Moved))
		{
			self.m_body->m_frame.set_position(Axis::X, self.m_body->m_frame.m_position[Axis::X] - event.m_delta.x);
			self.m_body->m_frame.set_position(Axis::Y, self.m_body->m_frame.m_position[Axis::Y] - event.m_delta.y);
			self.m_body->m_frame.set_position(Axis::Y, self.m_body->m_frame.m_position[Axis::Y] - 10.f * mouse_event.m_deltaZ);
		}
#endif

		return self;
	}

	ScrollSheet& scroll_plan(Widget& parent, Style& style)
	{
		static const bool clamped = true;

		ScrollSheet& self = scroll_sheet(parent, style, &styles().scroll_plan);

		if(MouseEvent event = self.mouse_event(DeviceType::MouseMiddle, EventType::Dragged))
			scroll_plan_drag(self, event);
		if(MouseEvent event = self.mouse_event(DeviceType::MouseMiddle, EventType::Moved))
			scroll_plan_zoom(self, event, clamped);
		
		return self;
	}

	void autofit_scroll_plan(ScrollSheet& scroll_sheet, span<Widget*> elements)
	{
		if(elements.size() == 0)
			return;

		Frame& scroll_plan = scroll_sheet.m_body->m_frame;

		const float margin = 1000.f;
		vec2 bounds_min = vec2(FLT_MAX);
		vec2 bounds_max = vec2(FLT_MIN);

		for(Widget* widget : elements)
		{
			bounds_min = min(widget->m_frame.m_position, bounds_min);
			bounds_max = max(widget->m_frame.m_position + widget->m_frame.m_size, bounds_max);
			//offset = min(vec2(widget->m_frame.m_position - margin));
		}

		vec2 offset = vec2(margin) - bounds_min;
		const vec2 remainder = mod(offset, vec2(100.f));
		offset = offset - remainder;

		for(Widget* widget : elements)
			widget->m_frame.m_position += offset;

		scroll_plan.m_position += -offset * scroll_plan.m_scale;

		const vec2 bounds = bounds_max + 2.f * margin - bounds_min;
		scroll_plan.m_size = bounds;
	}

	Widget& scrollable(Widget& parent)
	{
		return *scroll_sheet(parent).m_body;
	}
}
}


#ifdef TWO_MODULES
module two.ui;
#else
#endif

namespace two
{
	Style& section_style()
	{
		// Preset::Stack
		static Style style = { "Section", styles().sheet, [](Layout& l) { l.m_padding = vec4(2.f); } };
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


#ifdef TWO_MODULES
module two.ui;
#else
#include <stl/algorithm.h>
#endif

namespace two
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
		if(MouseEvent event = element.mouse_event(DeviceType::MouseLeft, EventType::Stroked, InputMod::Shift))
		{
			select_swap(selection, object);
			changed = true;
		}
		if(MouseEvent event = element.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
		{
			select(selection, object);
			changed = true;
		}
		if(MouseEvent event = element.mouse_event(DeviceType::MouseRight, EventType::Stroked))
		{
			select(selection, object);
			changed = true;
		}

		element.set_state(SELECTED, has(selection, object));
		return changed;
	}

	bool select_logic(Widget& element, Ref object, Ref& selection)
	{
		bool changed = false;
		if(MouseEvent event = element.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
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

		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
			parent.ui().m_drop = { static_cast<Widget*>(event.m_target), object, DropState::Preview };

		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::DragEnded))
			parent.ui().m_drop = { static_cast<Widget*>(event.m_target), object, DropState::Done };

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


#ifdef TWO_MODULES
module two.ui;
#else
#include <stl/algorithm.h>
#endif

namespace two
{
namespace ui
{
	Widget& dummy(Widget& parent, const vec2& size)
	{
		Widget& self = widget(parent, styles().dummy);
		//if(size != self.m_frame.m_content)
		if(size != self.m_frame.m_size)
		{
			self.m_frame.set_size(size);
			//self.m_frame.m_content = size;
			self.m_frame.mark_dirty(DIRTY_LAYOUT);
		}
		return self;
	}

	Widget& layout_span(Widget& parent, float span)
	{
		Widget& self = ui::layout(parent);
		self.m_frame.set_span(Axis::X, span);
		self.m_frame.set_span(Axis::Y, span);
		return self;
	}

	Widget& popup(Widget& parent, Style& style, PopupFlags flags)
	{
		Widget& self = widget(parent, style, true).layer();

		if(!self.modal() && bit(flags, PopupFlags::Modal))
			self.take_modal();

		if(bit(flags, PopupFlags::Clamp))
			self.m_frame.clamp_to_parent();

		if(bit(flags, PopupFlags::AutoClose))
		{
			// @todo change to Pressed, but causes a crash because InputDevice is holding to the pressed element
			if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
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
		if(MouseEvent event = parent.mouse_event(DeviceType::MouseRight, EventType::Stroked))
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


	DragPoint grid_sheet_drag(Widget& self, MouseEvent& event, Axis dim, bool start_drag)
	{
		// If not dragging already we take the position BEFORE the mouse moved as a reference
		DragPoint drag_point;
		vec2 local = !start_drag ? event.m_relative : self.m_frame.local_position(event.m_pressed);

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

	DragPoint grid_sheet_logic(Widget& self, Axis dim, bool& dragging)
	{
		// @todo we need to store the drag point only when the drag starts
		static DragPoint drag_point;

		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::DragStarted))
		{
			drag_point = grid_sheet_drag(self, event, dim, false);
		}

		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
		{
			dragging = true;
			if(drag_point.next && drag_point.prev)
				self.m_frame.transfer_pixel_span(*drag_point.prev, *drag_point.next, dim, event.m_delta[size_t(dim)]);
		}

		if(&self == self.ui().m_hovered)
			self.ui().m_cursor_style = dim == Axis::X ? &cursor_styles().resize_x
													  : &cursor_styles().resize_x;

		return drag_point;
	}

	DragPoint grid_sheet_logic(Widget& self, Axis dim)
	{
		bool dragging = false;
		return grid_sheet_logic(self, dim, dragging);
	}

	Widget& grid_sheet(Widget& parent, Style& style, Axis dim)
	{
		Widget& self = widget(parent, style, false, dim);
		grid_sheet_logic(self, dim);
		return self;
	}

	Widget& grid_sheet(Widget& parent, Style& style, Axis dim, span<float> spans)
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


#ifdef TWO_MODULES
module two.ui;
#else
#endif

namespace two
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

	bool slider_cursor(Frame& slider, Frame& knob, Axis dim, const MouseEvent& event, float& value, const SliderMetrics& metrics, bool relative)
	{
		if(relative)
		{
			float delta = event.m_delta[dim] / slider.m_size[dim];
			float cursor = min(1.f, max(0.f, metrics.offset(value) + delta));
			value = metrics.cursor(value, cursor);
		}
		else
		{
			vec2 position = slider.local_position(event.m_pos);
			float offset = -knob.m_size[dim] / 2.f;
			float cursor = min(slider.m_size[dim]/* - knob.m_size[dim]*/, max(0.f, position[dim] + offset)) / slider.m_size[dim];
			value = metrics.cursor(value, cursor);
		}
		return true;
	}

	bool slider_logic(Widget& self, Frame& slider, Frame& filler, Frame& knob, float& value, const SliderMetrics& metrics, Axis dim, bool relative)
	{
        UNUSED(filler);
		bool changed = false;

		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
			changed |= slider_cursor(slider, knob, dim, event, value, metrics, relative);

		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::DragStarted))
			self.enable_state(PRESSED);

		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
			changed |= slider_cursor(slider, knob, dim, event, value, metrics, relative);

		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::DragEnded))
			self.disable_state(PRESSED);

		return changed;
	}

	bool slider(Widget& parent, Style& style, float& value, SliderMetrics metrics, Axis dim, bool relative, bool fill, Style* knob_style)
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

	bool slider(Widget& parent, float& value, SliderMetrics metrics, Axis dim, bool relative, bool fill, Style* knob_style)
	{
		return slider(parent, styles().slider, value, metrics, dim, relative, fill, knob_style);
	}
}
}
#ifndef USE_STL
#ifdef TWO_MODULES
module two.math;
#else
#include <stl/vector.hpp>
#include <stl/unordered_set.hpp>
#include <stl/unordered_map.hpp>
#endif

namespace stl
{
	using namespace two;
	template class TWO_UI_EXPORT vector<TextGlyph>;
	template class TWO_UI_EXPORT vector<TextRow>;
	template class TWO_UI_EXPORT vector<Text::ColorSection>;
	template class TWO_UI_EXPORT vector<TextMarker>;
	template class TWO_UI_EXPORT vector<TextEdit::Action>;
	template class TWO_UI_EXPORT vector<Space>;
	template class TWO_UI_EXPORT vector<FrameSolver*>;
	template class TWO_UI_EXPORT vector<Image*>;
	template class TWO_UI_EXPORT vector<Style*>;
	template class TWO_UI_EXPORT vector<Layer*>;
	template class TWO_UI_EXPORT vector<Docker*>;
	template class TWO_UI_EXPORT vector<Dock*>;
	template class TWO_UI_EXPORT vector<Node*>;
	template class TWO_UI_EXPORT vector<EventBatch>;
	template class TWO_UI_EXPORT vector<KeyEvent>;
	template class TWO_UI_EXPORT vector<MouseEvent>;
	template class TWO_UI_EXPORT vector<InkStyle>;
	template class TWO_UI_EXPORT vector<Subskin>;
	template class TWO_UI_EXPORT vector<FrameSolver>;
	template class TWO_UI_EXPORT vector<RowSolver>;
	template class TWO_UI_EXPORT vector<unique<Widget>>;
	template class TWO_UI_EXPORT vector<unique<FrameSolver>>;
	template class TWO_UI_EXPORT vector<unique<Image>>;
	template class TWO_UI_EXPORT unordered_map<int, InputEvent*>;
	template class TWO_UI_EXPORT unordered_map<KeyCombo, KeyHandler>;
	template class TWO_UI_EXPORT unordered_map<string, Dock>;
	template class TWO_UI_EXPORT unordered_map<string, Style*>;

	template class TWO_UI_EXPORT unordered_set<string>;
	template class TWO_UI_EXPORT vector<LanguageDefinition::StringToken>;
	template class TWO_UI_EXPORT vector<LanguageDefinition::RegexToken>;
	template class TWO_UI_EXPORT unordered_map<string, Identifier>;
}
#endif

#ifdef TWO_MODULES
module two.ui;
#else
#endif

namespace two
{
    // Exported types
    template <> TWO_UI_EXPORT Type& type<two::FlowAxis>() { static Type ty("FlowAxis", sizeof(two::FlowAxis)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Pivot>() { static Type ty("Pivot", sizeof(two::Pivot)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Align>() { static Type ty("Align", sizeof(two::Align)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Solver>() { static Type ty("Solver", sizeof(two::Solver)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::AutoLayout>() { static Type ty("AutoLayout", sizeof(two::AutoLayout)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::LayoutFlow>() { static Type ty("LayoutFlow", sizeof(two::LayoutFlow)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Sizing>() { static Type ty("Sizing", sizeof(two::Sizing)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Preset>() { static Type ty("Preset", sizeof(two::Preset)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Clip>() { static Type ty("Clip", sizeof(two::Clip)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Opacity>() { static Type ty("Opacity", sizeof(two::Opacity)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::WidgetState>() { static Type ty("WidgetState", sizeof(two::WidgetState)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::ui::PopupFlags>() { static Type ty("PopupFlags", sizeof(two::ui::PopupFlags)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::WindowState>() { static Type ty("WindowState", sizeof(two::WindowState)); return ty; }
    
    template <> TWO_UI_EXPORT Type& type<stl::span<const char*>>() { static Type ty("span<const char*>", sizeof(stl::span<const char*>)); return ty; }
    template <> TWO_UI_EXPORT Type& type<stl::vector<two::Space>>() { static Type ty("vector<two::Space>", sizeof(stl::vector<two::Space>)); return ty; }
    template <> TWO_UI_EXPORT Type& type<stl::vector<two::Subskin>>() { static Type ty("vector<two::Subskin>", sizeof(stl::vector<two::Subskin>)); return ty; }
    
    template <> TWO_UI_EXPORT Type& type<two::Space>() { static Type ty("Space", sizeof(two::Space)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::v2<size_t>>() { static Type ty("v2<size_t>", sizeof(two::v2<size_t>)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::v2<two::AutoLayout>>() { static Type ty("v2<two::AutoLayout>", sizeof(two::v2<two::AutoLayout>)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::v2<two::Sizing>>() { static Type ty("v2<two::Sizing>", sizeof(two::v2<two::Sizing>)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::v2<two::Align>>() { static Type ty("v2<two::Align>", sizeof(two::v2<two::Align>)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::v2<two::Pivot>>() { static Type ty("v2<two::Pivot>", sizeof(two::v2<two::Pivot>)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::ImageSkin>() { static Type ty("ImageSkin", sizeof(two::ImageSkin)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Shadow>() { static Type ty("Shadow", sizeof(two::Shadow)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Paint>() { static Type ty("Paint", sizeof(two::Paint)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::TextPaint>() { static Type ty("TextPaint", sizeof(two::TextPaint)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Gradient>() { static Type ty("Gradient", sizeof(two::Gradient)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::InkStyle>() { static Type ty("InkStyle", sizeof(two::InkStyle)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Layout>() { static Type ty("Layout", sizeof(two::Layout)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Subskin>() { static Type ty("Subskin", sizeof(two::Subskin)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Style>() { static Type ty("Style", sizeof(two::Style)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::UiRect>() { static Type ty("UiRect", sizeof(two::UiRect)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Frame>() { static Type ty("Frame", type<two::UiRect>(), sizeof(two::Frame)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Widget>() { static Type ty("Widget", type<two::ControlNode>(), sizeof(two::Widget)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::TextCursor>() { static Type ty("TextCursor", sizeof(two::TextCursor)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::TextSelection>() { static Type ty("TextSelection", sizeof(two::TextSelection)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::TextMarker>() { static Type ty("TextMarker", sizeof(two::TextMarker)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Text>() { static Type ty("Text", sizeof(two::Text)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::TextEdit>() { static Type ty("TextEdit", type<two::Widget>(), sizeof(two::TextEdit)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::NodeConnection>() { static Type ty("NodeConnection", sizeof(two::NodeConnection)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Vg>() { static Type ty("Vg", sizeof(two::Vg)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Clipboard>() { static Type ty("Clipboard", sizeof(two::Clipboard)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::UiWindow>() { static Type ty("UiWindow", sizeof(two::UiWindow)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::User>() { static Type ty("User", sizeof(two::User)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Layer>() { static Type ty("Layer", sizeof(two::Layer)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::FrameSolver>() { static Type ty("FrameSolver", type<two::UiRect>(), sizeof(two::FrameSolver)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::RowSolver>() { static Type ty("RowSolver", type<two::FrameSolver>(), sizeof(two::RowSolver)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::TableSolver>() { static Type ty("TableSolver", sizeof(two::TableSolver)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::LineSolver>() { static Type ty("LineSolver", type<two::RowSolver>(), sizeof(two::LineSolver)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::GridSolver>() { static Type ty("GridSolver", sizeof(two::GridSolver)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::ScrollSheet>() { static Type ty("ScrollSheet", type<two::Widget>(), sizeof(two::ScrollSheet)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::ui::Sequence>() { static Type ty("Sequence", type<two::Widget>(), sizeof(two::ui::Sequence)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Tabber>() { static Type ty("Tabber", type<two::Widget>(), sizeof(two::Tabber)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Expandbox>() { static Type ty("Expandbox", type<two::Widget>(), sizeof(two::Expandbox)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::TreeNode>() { static Type ty("TreeNode", type<two::Widget>(), sizeof(two::TreeNode)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Table>() { static Type ty("Table", type<two::Widget>(), sizeof(two::Table)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Dock>() { static Type ty("Dock", sizeof(two::Dock)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Docksystem>() { static Type ty("Docksystem", sizeof(two::Docksystem)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Dockable>() { static Type ty("Dockable", type<two::Widget>(), sizeof(two::Dockable)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Docker>() { static Type ty("Docker", type<two::Widget>(), sizeof(two::Docker)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Dockspace>() { static Type ty("Dockspace", type<two::Docker>(), sizeof(two::Dockspace)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Dockbar>() { static Type ty("Dockbar", type<two::Docker>(), sizeof(two::Dockbar)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::NodePlug>() { static Type ty("NodePlug", type<two::Widget>(), sizeof(two::NodePlug)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Node>() { static Type ty("Node", type<two::Widget>(), sizeof(two::Node)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::CanvasConnect>() { static Type ty("CanvasConnect", sizeof(two::CanvasConnect)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Canvas>() { static Type ty("Canvas", type<two::Widget>(), sizeof(two::Canvas)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Ui>() { static Type ty("Ui", type<two::Widget>(), sizeof(two::Ui)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Window>() { static Type ty("Window", type<two::Dockable>(), sizeof(two::Window)); return ty; }
}


#ifdef TWO_MODULES
module two.ui;
#else
#include <stl/string.h>
#include <stl/map.h>
#endif

#include <cstdio>

namespace two
{
	inline Colour offset_colour(const Colour& colour, float delta)
	{
		float offset = delta / 255.0f;
		return Colour(clamp(colour.r + offset, 0.f, 1.f),
					  clamp(colour.g + offset, 0.f, 1.f),
					  clamp(colour.b + offset, 0.f, 1.f),
					  colour.a);
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
		m_impl->m_font_sources["proggy"] = string(resource_path) + "/interface/fonts/ProggyClean.ttf";
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
		row = text_row(text, text, text + len, { rect.x, rect.y, this->text_size(text, len, Axis::X, paint), line_height(paint) });
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

		row = text_row(text, first, iter, { rect.x, rect.y, this->text_size(first, iter - first, Axis::X, paint), line_height(paint) });
		this->break_glyphs(rect, paint, row);

		// @kludge because text_size doesn't report the correct size when there is a space at the end : investigate (vg-renderer, nanovg)
		if(!row.m_glyphs.empty())
			row.m_rect = { rect.x, rect.y, row.m_glyphs.back().m_rect.x + row.m_glyphs.back().m_rect.width, line_height(paint) };
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

	void UiRenderer::render(Layer& target, uint16_t view, float pixel_ratio, const Colour& colour)
	{
		this->log_FPS();

		m_debug_batch = 0;
		static size_t prevBatch = 0;

		m_vg.begin_frame(view, vec4(vec2(0.f), target.m_frame.m_size), pixel_ratio, colour);

#ifdef TWO_UI_DRAW_CACHE
		target.visit([&](Layer& layer) {
			if(layer.redraw() || layer.forceRedraw())
				this->render_layer(layer);
		});

		target.visit([&](Layer& layer) {
			m_vg.draw_layer(layer, vec2(0.f), 1.f);
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
			//printf("[debug] Render Frame : %i frames redrawn\n", m_debug_batch);
		}

		m_vg.end_frame(view);
	}

	void UiRenderer::render_layer(Layer& layer)
	{
		if(layer.master())
			m_vg.begin_target();

#ifdef TWO_UI_DRAW_CACHE
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

#ifdef TWO_UI_DRAW_CACHE
		m_vg.end_cached();
#endif

		if(layer.master())
			m_vg.end_target();
	}

	void UiRenderer::begin_frame(Frame& frame)
	{
		m_vg.begin_update(floor(frame.m_position), frame.m_scale);

		if(frame.d_layout->m_clipping == Clip::Clip)
		{
			m_vg.clip(frame.content_rect());
		}

		if(frame.d_layout->m_clipping == Clip::Unclip)
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

		//m_vg.debug_rect(rect, Colour::Red);

		if(frame.d_inkstyle->m_empty)
			return;

		if(frame.d_widget.m_custom_draw)
			return frame.d_widget.m_custom_draw(frame, rect, m_vg);

		if(frame.d_inkstyle->m_custom_draw)
			return frame.d_inkstyle->m_custom_draw(frame, rect, m_vg);
	
		two::draw_frame(m_vg, frame, rect);
	}

	void draw_frame(Vg& vg, const Frame& frame, const vec4& rect)
	{
		const vec2 padded_pos = floor(frame.d_inkstyle->m_padding.pos);
		const vec2 padded_size = floor(frame.m_size - rect_sum(frame.d_inkstyle->m_padding));
		const vec4 padded_rect = { padded_pos, padded_size };

		vec2 content = frame.m_content;
		if(frame.d_inkstyle->m_stretch.x)
			content.x = padded_size.x;
		if(frame.d_inkstyle->m_stretch.y)
			content.y = padded_size.y;

		const vec2 content_pos = { content_position(frame, content, padded_pos, padded_size, Axis::X), content_position(frame, content, padded_pos, padded_size, Axis::Y) };
		const vec4 content_rect = { content_pos, content };

		draw_background(vg, frame, rect, padded_rect, content_rect);
		draw_content(vg, frame, rect, padded_rect, content_rect);

		//vg.debug_rect(rect, Colour::Red);
		//vg.debug_rect(padded_rect, Colour::Green);
		//vg.debug_rect(content_rect, Colour::Blue);
	}

	float content_position(const Frame& frame, const vec2& content, const vec2& padded_pos, const vec2& padded_size, Axis dim)
	{
		if(frame.d_inkstyle->m_align[dim] == Align::Center)
			return padded_pos[dim] + padded_size[dim] / 2.f - content[dim] / 2.f;
		else if(frame.d_inkstyle->m_align[dim] == Align::Right)
			return padded_pos[dim] + padded_size[dim] - content[dim];
		else
			return padded_pos[dim];
	}

	vec4 select_corners(const Frame& frame)
	{
		Frame& parent = *frame.d_parent;

		const vec4& corners = parent.d_inkstyle->m_corner_radius;
		if(parent.first(frame))
			return parent.m_solver->d_length == Axis::X ? vec4(corners[0], 0.f, 0.f, corners[3]) : vec4(corners[0], corners[1], 0.f, 0.f);
		else if(parent.last(frame))
			return parent.m_solver->d_length == Axis::X ? vec4(0.f, corners[1], corners[2], 0.f) : vec4(0.f, 0.f, corners[2], corners[3]);
		else
			return vec4();
	}

	void draw_background(Vg& vg, const Frame& frame, const vec4& rect, const vec4& padded_rect, const vec4& content_rect)
	{
		//m_debug_batch++;

		InkStyle& inkstyle = *frame.d_inkstyle;

		// Shadow
		if(!inkstyle.m_shadow.d_null)
		{
			vg.draw_shadow(rect, inkstyle.m_corner_radius, inkstyle.m_shadow);
		}

		// Rect
		if(inkstyle.m_border_width.x || !inkstyle.m_background_colour.null())
		{
			vec4 corners = inkstyle.m_weak_corners ? select_corners(frame) : inkstyle.m_corner_radius;
			draw_rect(vg, rect, corners, inkstyle);
		}

		// ImageSkin
		ImageSkin& image_skin = inkstyle.m_image_skin;
		if(!image_skin.null())
		{
			const float margin = image_skin.m_margin * 2.f;
			vec4 skin_rect = { rect.pos, rect.size + margin };

			if(image_skin.d_stretch == Axis::X)
				skin_rect = { rect.x, content_rect.y + margin, rect.z + margin, image_skin.d_size.y };
			else if(image_skin.d_stretch == Axis::Y)
				skin_rect = { content_rect.x + image_skin.m_margin, rect.y, image_skin.d_size.x, rect.w + margin };

			vec4 sections[ImageSkin::Count];
			image_skin.stretch_coords(skin_rect.pos, skin_rect.size, { sections, ImageSkin::Count });

			for(int s = 0; s < ImageSkin::Count; ++s)
				draw_skin_image(vg, frame, s, sections[s]);
		}

		// Image
		if(inkstyle.m_overlay)
			draw_image(vg, *inkstyle.m_overlay, padded_rect);
		if(inkstyle.m_tile)
			draw_image(vg, *inkstyle.m_tile, rect);
	}

	void draw_image(Vg& vg, const Image& image, const vec4& rect)
	{
		if(image.d_atlas)
		{
			vec4 image_rect = { rect.pos - vec2(image.d_coord), vec2(image.d_atlas->m_image.d_size) };
			vg.draw_texture(uint16_t(image.d_atlas->m_image.d_handle), rect, image_rect);
		}
		else
		{
			vg.draw_texture(uint16_t(image.d_handle), rect, rect);
		}
	}

	void draw_image_stretch(Vg& vg, const Image& image, const vec4& rect, const vec2& stretch)
	{
		if(image.d_atlas)
		{
			const vec4 image_rect = { rect.pos - vec2(image.d_coord) * stretch, vec2(image.d_atlas->m_image.d_size) * stretch };
			vg.draw_texture(uint16_t(image.d_atlas->m_image.d_handle), rect, image_rect);
		}
		else
		{
			const vec4 image_rect = { rect.pos, vec2(image.d_size) * stretch };
			vg.draw_texture(uint16_t(image.d_handle), rect, image_rect);
		}
	}

	void draw_skin_image(Vg& vg, const Frame& frame, int section, vec4 rect)
	{
		ImageSkin& imageSkin = frame.d_inkstyle->m_image_skin;
		rect.x = rect.x - imageSkin.m_margin;
		rect.y = rect.y - imageSkin.m_margin;

		const vec2 divided = rect.size / imageSkin.d_fill_size;
		vec2 ratio = { 1.f, 1.f };

		if(section == ImageSkin::Top || section == ImageSkin::Bottom || section == ImageSkin::Fill)
			ratio.x = divided.x;
		if(section == ImageSkin::Left || section == ImageSkin::Right || section == ImageSkin::Fill)
			ratio.y = divided.y;

		draw_image_stretch(vg, imageSkin.d_images[section], rect, ratio);
	}

	void draw_content(Vg& vg, const Frame& frame, const vec4& rect, const vec4& padded_rect, const vec4& content_rect)
	{
		UNUSED(rect);

		if(frame.empty() || padded_rect.z <= 0.f || padded_rect.w <= 0.f)
			return;

		//this->clip(rect);

		if(frame.icon())
			draw_image(vg, *frame.icon(), content_rect);

		if(frame.caption())
			vg.draw_text(padded_rect.pos, frame.caption(), nullptr, text_paint(*frame.d_inkstyle));

		if(frame.m_text)
		{
			const vec2 padding = floor(frame.d_inkstyle->m_padding.pos);
			draw_text(vg, padding, *frame.m_text);
		}
	}

	void draw_rect(Vg& vg, const vec4& rect, const vec4& corners, const InkStyle& inkstyle)
	{
		vg.path_rect(rect, corners, inkstyle.m_border_width.x);

		if(!inkstyle.m_background_colour.null())
		{
			if(inkstyle.m_linear_gradient == vec2(0.f))
			{
				vg.fill({ inkstyle.m_background_colour, inkstyle.m_border_colour, inkstyle.m_border_width.x });
			}
			else
			{
				Colour first = offset_colour(inkstyle.m_background_colour, inkstyle.m_linear_gradient.x);
				Colour second = offset_colour(inkstyle.m_background_colour, inkstyle.m_linear_gradient.y);
				if(inkstyle.m_linear_gradient_dim == Axis::X)
					vg.fill({ first, second }, { rect.x, rect.y }, { rect.x + rect.width, rect.y });
				else
					vg.fill({ first, second }, { rect.x, rect.y }, { rect.x, rect.y + rect.height });
			}

		}
		if(inkstyle.m_border_width.x > 0.f)
			vg.stroke({ inkstyle.m_background_colour, inkstyle.m_border_colour, inkstyle.m_border_width.x });
	}

	void UiRenderer::log_FPS()
	{
		static size_t frames = 0;
		static double prevtime;

		double time = m_clock.read();
		if(time - prevtime >= 4.f)
		{
			printf("[info] frame %.2f\n", ((time - prevtime) / frames) * 1000.f);
			printf("[info] fps %f\n", (frames / (time - prevtime)));
			prevtime = time;
			frames = 0;
		}

		++frames;
	}
}


#ifdef TWO_MODULES
module two.ui;
#else
#include <stl/algorithm.h>
#endif

namespace two
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
		return Widget::begin();
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
		if(!m_window.m_context.m_mouse_lock)
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

	void Ui::reset_styles()
	{
		visit([](Widget& widget, bool& visit)
		{
			widget.m_frame.update_style(true);
		});
	}
}


#ifdef TWO_MODULES
module two.ui;
#else
#include <stl/algorithm.h>
#include <stl/unordered_map.hpp>
#endif

#include <cstdio>

namespace two
{
	UiWindow::UiWindow(Context& context, Vg& vg, User* user)
		: m_resource_path(context.m_resource_path)
		, m_context(context)
		, m_vg(vg)
		, m_renderer(vg)
		, m_atlas(uvec2(1024U))
		, m_size(context.m_size)
		, m_user(user)
	{
		//this->init();
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
		this->reset_styles();

		printf("[info] ui - window init - resource path %s\n", m_resource_path.c_str());

		this->init_resources();
		this->load_resources();

		styles().setup(*this);

		m_ui = oconstruct<Ui>(*this);

		printf("[info] ui - init input\n");
		m_context.init_input(m_ui->m_mouse, m_ui->m_keyboard);

		this->resize(m_context.m_size, m_context.m_fb_size);
	}

	void UiWindow::reset_styles()
	{
		styles().reset();

		ui::cursor_styles().reset();
		ui::scrollbar_styles().reset();
		ui::dropdown_styles().reset();
		ui::table_styles().reset();
		ui::expandbox_styles().reset();
		ui::treenode_styles().reset();
		ui::tabber_styles().reset();
		ui::menu_styles().reset();
		ui::toolbar_styles().reset();
		ui::window_styles().reset();
		ui::dock_styles().reset();
		ui::canvas_styles().reset();
		ui::node_styles().reset();
		ui::file_styles().reset();
	}

	void UiWindow::init_resources()
	{
		string sprite_path = m_resource_path + "/interface/uisprites";

		printf("[info] ui - loading images from path %s\n", sprite_path.c_str());

		vector<Image> images;
		load_folder_images(images, sprite_path, "");

		auto visit_folder = [&](const string& folder)
		{
			load_folder_images(images, sprite_path + folder + "/", string(folder) + "/");
		};

		visit_folders(sprite_path.c_str(), visit_folder);

		m_images = convert<object<Image>, Image>(images, [](const Image& image) { return oconstruct<Image>(image); });
	}

	void UiWindow::load_resources()
	{
		printf("[info] ui - loading resources\n");

		m_vg.load_default_font();

		vector<Image*> images;
		for(auto& image : m_images) images.push_back(image.get());

		vector<unsigned char> atlas = m_atlas.generate_atlas(images);
		m_vg.load_image_RGBA(m_atlas.m_image, atlas.data());
	}

	Image& UiWindow::create_image(cstring name, const uvec2& size, span<uint8_t> data, bool filtering)
	{
		m_images.push_back(construct<Image>(name, name, size));
		Image& image = *m_images.back();
		image.d_filtering = filtering;
		m_vg.load_image_RGBA(image, data.data());
		return image;
	}

	void UiWindow::remove_image(Image& image)
	{
		remove_if(m_images, [&](object<Image>& current) { return current.get() == &image; });
		m_vg.unload_image(image);
	}

	Image* UiWindow::find_image(cstring name)
	{
		for(auto& image : m_images)
			if(image->d_name == name)
				return image.get();
		return nullptr;
	}

	void UiWindow::resize(const uvec2& size, const uvec2& fb_size)
	{
		printf("[info] ui window - resize to (%i, %i) - pixel size (%i, %i)\n", int(size.x), int(size.y), int(fb_size.x), int(fb_size.y));
		m_size = size;
		m_context.reset_fb(fb_size);
		m_ui->m_frame.set_size(vec2(fb_size));
	}

	bool UiWindow::input_frame()
	{
		if(m_size != m_context.m_size)
			this->resize(m_context.m_size, m_context.m_fb_size);

		m_ui->input_frame();

		m_ui->m_frame.relayout();

		return !m_shutdown;
	}

	void UiWindow::render_frame(uint16_t view)
	{
		//m_ui->render_frame();

		if(m_context.m_render_system.m_manual_render)
		{
			m_renderer.render(*m_ui->m_frame.m_layer, view, m_context.m_pixel_ratio, m_colour);
			// add sub layers
		}

		m_ui->clear_events();
	}

	void UiWindow::shutdown()
	{
		m_shutdown = true;
	}
}


#ifdef TWO_MODULES
module two.ui;
#else
#include <stl/string.h>
#endif

#include <cassert>

namespace two
{
namespace ui
{
	void widget_logic(Widget& self)
	{
		if(MouseEvent event = self.mouse_event(DeviceType::Mouse, EventType::Heartbeat))
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

	Widget& widget(Widget& parent, Style& style, bool open, Axis length, v2<size_t> index)
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

	Widget& multi_item(Widget& parent, Style& style, span<cstring> elements, Style* element_style)
	{
		Widget& self = widget(parent, style);
		for(cstring value : elements)
			item(self, element_style ? *element_style : styles().item, value);
		return self;
	}

	Widget& multi_item(Widget& parent, span<cstring> elements, Style* element_style)
	{
		return multi_item(parent, styles().row, elements, element_style);
	}

	Widget& spanner(Widget& parent, Style& style, Axis dim, float span)
	{
		Widget& self = widget(parent, style);
		self.m_frame.set_span(dim, span);
		return self;
	}
}
}


#ifdef TWO_MODULES
module two.ui;
#else
#endif

namespace two
{
	template class Graph<Widget>;

	inline bool clip(const Frame& frame) { return frame.d_layout->m_clipping == Clip::Clip; }

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
		m_index = uint32_t(parent->m_nodes.size());
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
			m_frame.m_layer = oconstruct<Layer>(m_frame);
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

	void Widget::clear()
	{
		m_nodes.clear();
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
		Frame* frame = two::pinpoint(m_frame, pos, filter);
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
			return (pinned && pinned != this) ? pinned->control_event(mouse_event) : this;
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
		KeyEvent* event = static_cast<KeyEvent*>(m_events->m_keyed_events[DeviceType::Keyboard][event_type][int(code)]);
		return event && fits_modifier(event->m_modifiers, modifier) ? *event : KeyEvent();
	}

	MouseEvent Widget::mouse_event(DeviceType device, EventType event_type, InputMod modifier, bool consume)
	{
		if(!m_events) return MouseEvent();
		MouseEvent* event = static_cast<MouseEvent*>(m_events->m_events[device][event_type]);
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


#ifdef TWO_MODULES
module two.ui;
#else
#endif

namespace two
{
namespace ui
{
	void window_drag_logic(Widget& widget, Window& window)
	{
		if(MouseEvent event = widget.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
		{
			window.enable_state(ACTIVE);
			//if(!window.m_dock) // crashes for some reason
			window.m_frame.layer().moveToTop();
		}

		if(MouseEvent event = widget.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
		{
			if(window.m_dock)
				window.m_dock->m_docker->undock(window);

			window.m_frame.layer().moveToTop();
			window.m_frame.layer().m_frame.m_opacity = Opacity::Hollow;

			if(window.movable())
				window.m_frame.set_position(window.m_frame.m_position + event.m_delta);
		}

		if(MouseEvent event = widget.mouse_event(DeviceType::MouseLeft, EventType::DragEnded))
		{
			//if(window.dockable())
			//	window.m_dock->m_docksystem->dock(window, mouse_event.m_pos);

			window.m_frame.layer().m_frame.m_opacity = Opacity::Opaque;
		}
	}

	void window_resize_logic(Widget& widget, Window& window, bool left)
	{
		if(MouseEvent event = widget.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
		{
			window.m_frame.layer().moveToTop();

			if(left)
				window.m_frame.set_position(Axis::X, window.m_frame.m_position.x + event.m_delta.x);
			if(left)
				window.m_frame.set_size(max(vec2(50.f), window.m_frame.m_size - event.m_delta));
			else
				window.m_frame.set_size(max(vec2(50.f), window.m_frame.m_size + event.m_delta));
		}
	}

	Widget& window_header(Widget& parent, Window& window, cstring title)
	{
		Style* style = window.movable() ? &window_styles().header_movable : &window_styles().header;
		Widget& self = widget(parent, *style);
		self.set_state(ACTIVE, window.active());

		item(self, styles().title, title);
		if(window.closable())
			if(button(self, window_styles().close_button).activated())
				window.m_open = false;

		tooltip(self, "Drag me");

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
				self.m_frame.set_size(vec2(480.f, 350.f));

			if(!self.m_dock)
				self.m_frame.set_position((self.m_parent->m_frame.m_size - self.m_frame.m_size) / 2.f);
		}

		if(self.header())
			window_header(self, self, title);

		if(self.hasmenu())
			self.m_menu = &menubar(self);

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


#ifdef TWO_MODULES
module two.ui;
#else
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


#ifdef TWO_MODULES
module two.ui;
#else
#endif

namespace two
{
	EventDispatch::EventDispatch()
	{}

	void EventDispatch::process(Widget& widget)
	{
		if(!widget.m_events) return;

		KeyEvent* key_down_event = static_cast<KeyEvent*>(widget.m_events->m_events[DeviceType::Keyboard][EventType::Pressed]);
		if(key_down_event)
		{
			if(m_key_down_handlers.find(key_down_event->m_code) != m_key_down_handlers.end())
				m_key_down_handlers[key_down_event->m_code]();
		}

		KeyEvent* key_up_event = static_cast<KeyEvent*>(widget.m_events->m_events[DeviceType::Keyboard][EventType::Released]);
		if(key_up_event)
		{
			if(m_key_up_handlers.find(key_up_event->m_code) != m_key_up_handlers.end())
				m_key_up_handlers[key_up_event->m_code]();
		}
	}
}


#ifdef TWO_MODULES
module two.ui;
#else
#endif

namespace two
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


#ifdef TWO_MODULES
module two.ui;
#else
#include <stl/algorithm.h>
#endif

namespace two
{
namespace ui
{
	Widget& dir_item(Widget& parent, const string& name)
	{
		return multi_button(parent, file_styles().dir, { "(folder_20)" , name.c_str() });
	}

	Widget& file_item(Widget& parent, const string& name)
	{
		return multi_button(parent, file_styles().file, { "(file_20)" , name.c_str() });
	}

	Widget& file_list(Widget& parent, string& path)
	{
		Widget& self = widget(parent, styles().wedge);//file_styles().directory);

		auto on_dir = [&](const string& dir)
		{
			if(dir == ".") return;
			Widget& item = dir_item(self, dir.c_str());
			if(item.activated())
			{
				if(dir == "..")
					path = path.substr(0, path.rfind("/"));
				else
					path = path + "/" + dir;
			}
		};

		auto on_file = [&](const string& file)
		{
			file_item(self, file.c_str());
		};

		visit_folders(path, on_dir, false);
		visit_files(path, on_file);
		return self;
	}

	Widget& file_browser(Widget& parent, string& path)
	{
		Widget& self = widget(parent, styles().wedge);// styles().file_browser);
		file_list(self, path);
		return self;
	}

	Widget& dir_node(Widget& parent, const string& path, const string& name, bool open)
	{
		cstring elements[] = { "(folder_20)", name.c_str() };
		Widget& self = tree_node(parent, elements, false, open);
		if(!self.m_body) return self;

		auto on_dir = [&](const string& dir)
		{
			dir_node(*self.m_body, path + "/" + dir, dir, false);
		};

		auto on_file = [&](const string& file)
		{
			file_node(*self.m_body, file.c_str());
		};

		visit_folders(path, on_dir);
		visit_files(path, on_file);
		return self;
	}

	Widget& file_node(Widget& parent, const string& name)
	{
		Widget& self = tree_node(parent, { "(file_20)", name.c_str() }, true, false);
		return self;
	}
	
	Widget& file_tree(Widget& parent, const string& path)
	{
		Widget& self = tree(parent);
		dir_node(self, path, path, false);
		return self;
	}
}
}


#ifdef TWO_MODULES
module two.ui;
#else
#endif

#include <stl/hash_base.hpp>

namespace two
{
	template <class T, size_t N>
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

	void builtin_keywords(LanguageDefinition& language, span<cstring> keywords)
	{
		for(cstring i : keywords)
			language.m_keywords.insert(string(i));
	}

	void builtin_identifiers(LanguageDefinition& language, span<cstring> identifiers)
	{
		for(cstring k : identifiers)
		{
			Identifier id = { {}, "Built-in identifier" };
			language.m_identifiers.insert({ string(k), id });
		}
	}

	void builtin_functions(LanguageDefinition& language, span<cstring> functions)
	{
		for(cstring k : functions)
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

	string list_regex(span<string> tokens)
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

#ifndef TWO_CPP_20
#include <cctype>
#include <locale>
#include <chrono>
#include <regex>
#include <cmath>
#endif

#ifdef TWO_MODULES
module two.ui;
#else
#include <stl/string.h>
#include <stl/algorithm.h>
#endif

namespace two
{
	TextEdit::TextEdit(Widget* parent, void* identity, bool editor, string allowed_chars)
		: Widget(parent, identity)
		, m_editor(editor)
		, m_text(m_frame)
		, m_string(m_text.m_text)
		, m_dirty(0, uint(m_string.size()))
		, m_allowed_chars(allowed_chars)
	{
		m_palette = OkaidaPalette();
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
		const int digits = count_digits(int(m_text.m_text_rows.size()));
		const vec2 offset = { m_text.line_height() * float(digits) * 0.7f, 0.f };

		return offset + m_text.compute_text_size() + rect_sum(m_frame.d_inkstyle->m_padding);
	}

	void TextEdit::update_style()
	{
		m_text.update_style();

		if(m_editor)
		{
			m_text.m_text_paint.m_font = "consolas";
			m_text.m_text_paint.m_size = 14.f;
		}

		auto count_digits = [](int number) { int digits = 0; do { number /= 10; digits++; } while (number != 0); return digits; };
		int digits = count_digits(int(m_text.m_text_rows.size()));

		vec2 padding = floor(m_frame.d_inkstyle->m_padding.pos);
		if(m_editor)
			m_text_offset = padding + vec2(m_text.line_height() * float(digits) * 0.7f, 0.f);
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

		printf("[warning] undo/redo won't work after this\n");
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
		remove_if(m_text.m_sections, [&](Text::ColorSection& section) { return section.m_end >= start && section.m_start <= end; });
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
			if(MouseEvent event = this->mouse_event(DeviceType::MouseLeft, event_focus, InputMod::None, false))
			{
				take_focus();
				this->cursor(0);
			}

		bool shift = this->ui().m_keyboard.m_shift;
		bool ctrl = this->ui().m_keyboard.m_ctrl;
		bool alt = this->ui().m_keyboard.m_alt;
		
		if(MouseEvent event = this->mouse_event(DeviceType::Mouse, EventType::Heartbeat))
		{
			size_t index = m_text.char_at(event.m_relative - m_text_offset);
			m_hovered_word = word_at(m_string, index);
			if(m_hovered_word != "")
			{
				m_hovered_word_rect = m_text.interval_rect(word_begin(m_string, index), word_end(m_string, index));
				m_hovered_word_rect = { m_hovered_word_rect.pos + m_text_offset, m_hovered_word_rect.size };
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
			if(MouseEvent event = this->mouse_event(DeviceType::MouseLeft, EventType::Pressed))
			{
				m_select_from = m_text.cursor_at(event.m_relative - m_text_offset);
				this->cursor(m_select_from, ctrl);
			}
			if(MouseEvent event = this->mouse_event(DeviceType::MouseLeft, EventType::Pressed, InputMod::Ctrl))
			{
				m_select_from = m_text.cursor_at(event.m_relative - m_text_offset);
				m_word_selection_mode = true;
				this->cursor(m_select_from, true);
			}
			if(MouseEvent event = this->mouse_event(DeviceType::MouseLeft, EventType::Released))
			{
				if(!focused())
					this->select_all();
			}
			if(MouseEvent event = this->mouse_event(DeviceType::MouseLeft, EventType::DoubleStroked))
			{
				TextCursor cursor = m_text.cursor_at(event.m_relative - m_text_offset);
				this->cursor(cursor, true);
			}
			if(MouseEvent event = this->mouse_event(DeviceType::MouseLeft, EventType::Dragged))
			{
				TextCursor cursor = m_text.cursor_at(event.m_relative - m_text_offset);
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
		if(MouseEvent event = this->mouse_event(DeviceType::MouseMiddle, EventType::Moved))
		{
			float overflow = content.m_size.y - frame.m_size.y;
			content.m_position.y += event.m_deltaZ * 22.f * 3.f;
			content.m_position.y = min(0.f, max(content.m_position.y, -overflow));
		}

		if(m_follow_cursor)
		{
			scroll_to_cursor(frame, content);
			m_follow_cursor = false;
		}
	}

	void TextEdit::render(Vg& vg)
	{
		if(m_editor)
			recolorize();

		if(m_editor)
			vg.draw_rect(vec4(vec2(0.f), m_frame.m_size), palette_paint(m_palette, Text::Background));
		//else
		//	vg.draw_background(m_frame, { m_frame.m_position, m_frame.m_size }, {}, {});

		const vec2 padding = floor(m_frame.d_inkstyle->m_padding.pos);

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
		if(m_string.empty())
			return;

		if(m_language == nullptr)
		{
			m_text.m_sections.clear();
			m_text.m_sections.push_back({ 0, m_string.size(), Text::Default });
			return;
		}

		std::match_results<const char*> results;

		const size_t begin = line_begin(m_string, from);
		const size_t end = line_end(m_string, to);

		bool preproc = false;

		const char* first = &m_string.front();
		const char* start = first + begin;
		const char* last = first + end;

		// remove all sections that overlap range to colorize, and get iterator to insert the new ones
		remove_if(m_text.m_sections, [=](Text::ColorSection& section) { return section.m_start >= begin && section.m_end <= end; });
		auto start_section = find_if(m_text.m_sections, [=](const Text::ColorSection& section) { return section.m_start >= begin; });

		for(const char* current = start; current != last; ++current)
		{
			for(auto& token_color : m_language->m_regex_tokens)
			{
				if(std::regex_search<const char*>(current, last, results, token_color.token, std::regex_constants::match_continuous))
				{
					auto match = *results.begin();
					string name = m_string.substr(match.first - first, match.second - match.first);
					PaletteIndex color = token_color.color;

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

					const Text::ColorSection section = { size_t(match.first - first), size_t(match.second - first), color };
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
		const vec2 margin = vec2(0.f);

		const vec4 cursor_rect = m_text.cursor_rect(m_selection.m_cursor);
		const vec2 cursor_min = cursor_rect.pos - margin;
		const vec2 cursor_max = cursor_min + cursor_rect.size + margin;

		const vec2 frame_min = -content.m_position;
		const vec2 frame_max = -content.m_position + frame.m_size;

		const vec2 delta_neg = max(vec2(0.f), frame_min - cursor_min);
		const vec2 delta_pos = min(vec2(0.f), frame_max - cursor_max);

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

		const vec2 size = self.frame_size();
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

	void autocomplete_popup(TextEdit& edit, string& text, const string& current_word, size_t cursor, size_t word_start, span<cstring> completions)
	{
		const vec4 word_rect = edit.m_text.interval_rect(word_start, cursor - 1);
		const vec2 popup_position = edit.m_text_offset + word_rect.pos + vec2(0.f, word_rect.height);

		static uint32_t current = 0;

		const bool selected = ui::popdown(edit, completions, current, popup_position, PopupFlags::None); //auto_complete_style

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
			const size_t cursor = edit.m_selection.m_cursor;
			const size_t begin = word_begin(edit.m_string, cursor - 1);

			const string current_word = begin == SIZE_MAX ? "" : edit.m_string.substr(begin, cursor - begin);
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
					autocomplete_popup(edit, text, current_word, cursor, begin, completions);
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


#ifdef TWO_MODULES
module two.ui;
#else
#include <stl/math.h>
#endif

#include <cstdio>

namespace two
{
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

	inline TextPaint style_text_paint(InkStyle& inkstyle)
	{
		return { inkstyle.m_text_font.c_str(), inkstyle.m_text_colour, inkstyle.m_text_size, inkstyle.m_align, inkstyle.m_text_break, inkstyle.m_text_wrap };
	}

	void Text::update_style()
	{
		m_text_paint = style_text_paint(*m_frame.d_inkstyle);
	}

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
			return m_text_rows.back().m_rect.y + m_text_rows.back().m_rect.height;
		else
			return 0.f;
	}

	float Text::compute_width() const
	{
		float result = 0.f;
		for(const TextRow& row : m_text_rows)
			result = max(result, row.m_rect.width);
		return result;
	}

	void Text::break_text_rows()
	{
		const vec2 padded_size = floor(m_frame.m_size - rect_sum(m_frame.d_inkstyle->m_padding));

		if(!m_text.empty())
			s_vg->break_text(m_text.c_str(), m_text.size(), padded_size, m_text_paint, m_text_rows);
		else
			m_text_rows.clear();

		//return offset +  + rect_sum(m_frame.d_inkstyle->m_padding);
		m_frame.m_content = this->compute_text_size();
		m_frame.mark_dirty(DIRTY_LAYOUT);
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

			if(pos.y < offset + row.m_rect.y + row.m_rect.height) // pos.y >= row.m_rect.y && 
			{
				for(const TextGlyph& glyph : row.m_glyphs)
					if(pos.x < glyph.m_rect.x + glyph.m_rect.width * 0.5f) // pos.x >= glyph.m_rect.x &&
						return glyph.m_position - start;

				return row.m_end - start;
			}

			line++;
		}

		return end - start;
	}

	vec4 Text::interval_rect(const TextRow& row, size_t start, size_t end) const
	{
		const TextGlyph& start_glyph = row.m_glyphs[start - row.m_start_index];
		const TextGlyph& end_glyph = row.m_glyphs[end - row.m_start_index];

		return { start_glyph.m_rect.x, row.m_rect.y, end_glyph.m_rect.x + end_glyph.m_rect.width - start_glyph.m_rect.x, row.m_rect.height };
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
			return { vec2(row.m_rect.x + row.m_rect.width, row.m_rect.y), vec2(1.f, line_height()) };
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

	Colour palette_colour(const ColourPalette& palette, PaletteIndex color_index)
	{
		return rgba(palette[color_index]);
	}

	Paint palette_paint(const ColourPalette& palette, PaletteIndex color_index)
	{
		return { rgba(palette[color_index]) };
	}

	TextPaint palette_text_paint(const Text& text, const ColourPalette& palette, PaletteIndex color_index)
	{
		TextPaint paint = text.m_text_paint;
		paint.m_colour = rgba(palette[color_index]);
		return paint;
	}

	void draw_text(Vg& vg, const vec2& padding, const Text& text)
	{
		for(const TextRow& row : text.m_text_rows)
			vg.draw_text(padding + row.m_rect.pos, row.m_start, row.m_end, text.m_text_paint);
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
			if(row.m_start == row.m_end)
				continue;

			while(isection < text.m_sections.size() && text.m_sections[isection].m_end < row.m_start_index)
				isection++;

			snprintf(line_number, 16, "%6d", int(++line));
			vg.draw_text(padding + offset + row.m_rect.pos, line_number, nullptr, palette_text_paint(text, palette, Text::LineNumber));

			while(isection < text.m_sections.size() && text.m_sections[isection].m_start < row.m_end_index)
			{
				const Text::ColorSection& section = text.m_sections[isection];

				const size_t start = max(section.m_start, row.m_start_index);
				const size_t end = min(section.m_end, row.m_end_index);
				const vec2 position = offset + text_offset + row.m_glyphs[start - row.m_start_index].m_rect.pos;
				vg.draw_text(floor(position) + vec2(0.f, 0.5f), &text.m_text.front() + start, &text.m_text.front() + end, palette_text_paint(text, palette, section.m_colour));

				if(section.m_end <= row.m_end_index)
					isection++;
				else
					break;
			}

			if(imarker < text.m_markers.size() && text.m_markers[imarker].m_line == line)
			{
				const vec4 rect = { offset + padding + vec2(0.f, row.m_rect.y + line_height), vec2(frame.m_size.x, text.line_height()) };
				const vec2 position = offset + text_offset + row.m_rect.pos + line_height;

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

		const float line_height = vg.line_height(text.m_text_paint);

		size_t line = 0;
		size_t imarker = 0;
		vec2 offset = vec2(0.f);

		for(const TextRow& row : text.m_text_rows)
		{
			line++;

			if(selection.m_start != selection.m_end && row.m_end_index > selection.m_start && row.m_start_index < selection.m_end)
			{
				if(row.m_glyphs.empty())
				{
					vg.draw_rect({ offset + text_offset + row.m_rect.pos, vec2(5.f, row.m_rect.height) }, palette_paint(palette, Text::Selection));
					continue;
				}

				const size_t select_start = max(row.m_start_index, size_t(selection.m_start));
				const size_t select_end = min(row.m_end_index, size_t(selection.m_end));

				const vec4 row_rect = text.interval_rect(row, select_start, select_end - 1);
				vg.draw_rect({ offset + text_offset + row_rect.pos, row_rect.size }, palette_paint(palette, Text::Selection));
			}

			if(selection.m_cursor >= row.m_start_index && selection.m_cursor <= row.m_end_index)
			{
				if(current_line && selection.m_start == selection.m_end)
				{
					bool focused = false;
					vec4 rect = { offset + padding + vec2(0.f, row.m_rect.y), vec2(frame.m_size.x, text.line_height()) };
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
					vg.draw_rect({ offset + text_offset + cursor_rect.pos, cursor_rect.size }, palette_paint(palette, Text::Cursor));
				}
			}

			if(imarker < text.m_markers.size() && text.m_markers[imarker].m_line == line)
			{
				offset += vec2(0.f, line_height);
				imarker++;
			}
		}
	}
}


#ifdef TWO_MODULES
module two.ui;
#else
#endif

#include <cstdio>

namespace two
{
	template struct v2<bool>;
	template struct v2<size_t>;
	template struct v2<AutoLayout>;
	template struct v2<Sizing>;
	template struct v2<Align>;
	template struct v2<Pivot>;

	template <> string to_string<DirtyLayout>(const DirtyLayout& dirty) { if(dirty == CLEAN) return "CLEAN"; else if(dirty == DIRTY_REDRAW) return "DIRTY_REDRAW"; else if(dirty == DIRTY_PARENT) return "DIRTY_PARENT"; else if(dirty == DIRTY_LAYOUT) return "DIRTY_LAYOUT"; else if(dirty == DIRTY_FORCE_LAYOUT) return "DIRTY_FORCE_LAYOUT"; else /*if(dirty == DIRTY_STRUCTURE)*/ return "DIRTY_STRUCTURE"; }

	Vg* Frame::s_vg = nullptr;

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
		return d_caption == "" && d_icon == nullptr && !m_text;
	}

	Image* Frame::icon() const
	{
		return d_icon;
	}

	cstring Frame::caption() const
	{
		return d_caption.c_str();
	}

	FrameSolver& Frame::solver(Style& style, Axis length, v2<size_t> index)
	{
		d_style = &style;
		d_layout = &style.m_layout;
		d_index = index;

		this->update_style();

		Solver type = d_layout->m_solver;
		FrameSolver* solver = d_parent ? d_parent->m_solver.get() : nullptr;

		if(type == Solver::Frame)
			m_solver = construct<FrameSolver>(solver, d_layout, this);
		else if(type == Solver::Row)
			m_solver = construct<RowSolver>(solver, d_layout, this);
		else if(type == Solver::Grid)
			m_solver = construct<GridSolver>(solver, d_layout, this);
		else if(type == Solver::Table)
			m_solver = construct<TableSolver>(solver, d_layout, this);

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
		d_layout = &d_style->m_layout;

		InkStyle& inkstyle = d_style->state_skin(d_widget.m_state);
		this->update_inkstyle(inkstyle, reset);

		m_opacity = d_layout->m_opacity;
		m_size = d_layout->m_size == vec2(0.f) ? m_size : d_layout->m_size;

		reset ? this->mark_dirty(DIRTY_FORCE_LAYOUT) : this->mark_dirty(DIRTY_LAYOUT);
	}

	void Frame::update_state(WidgetState state)
	{
		InkStyle& inkstyle = d_style->state_skin(state);
		this->update_inkstyle(inkstyle);
	}

	void Frame::update_inkstyle(InkStyle& inkstyle, bool reset)
	{
		if(d_inkstyle == &inkstyle && !reset) return;
		//printf("[debug] Update inkstyle %s\n", inkstyle.m_name.c_str());
		d_inkstyle = &inkstyle;
		this->mark_dirty(DIRTY_REDRAW);
		this->set_icon(d_inkstyle->m_image);
		if(d_caption != "")
			this->size_caption();
	}

	void Frame::size_caption()
	{
		if(d_caption != "")
		{
			TextPaint paint = text_paint(*d_inkstyle);
			m_content = s_vg->text_size(d_caption.c_str(), d_caption.size(), paint);
		}
		else
			m_content = vec2(0.f);
	}

	void Frame::set_caption(cstring text)
	{
		if(d_caption == text)
			return;
		d_caption = text;
		m_size = vec2(0.f);
		this->size_caption();
		mark_dirty(DIRTY_LAYOUT);
	}

	void Frame::set_icon(Image* image)
	{
		if(d_icon == image)
			return;
		d_icon = image;
		m_size = vec2(0.f);
		m_content = image ? vec2(image->d_size) : vec2(0.f);
		mark_dirty(DIRTY_LAYOUT);
	}

	void Frame::set_size(Axis dim, float size)
	{
		if(m_size[dim] == size) return;
		m_size[dim] = size;
		this->mark_dirty(DIRTY_FORCE_LAYOUT);
	}

	void Frame::set_span(Axis dim, float span)
	{
		if(m_span[dim] == span) return;
		m_span[dim] = span;
		this->mark_dirty(DIRTY_FORCE_LAYOUT);
	}

	void Frame::set_position(Axis dim, float position)
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
		while(parent->d_layout->m_clipping != Clip::Clip)
			parent = parent->d_parent;
		return parent;
	}

	void Frame::clamp_to_parent()
	{
		//Frame* clip = clip_parent(*this);
		Frame* clip = &this->root();
		vec2 position = this->derive_position(vec2(0.f), *clip);

		for(Axis dim : { Axis::X, Axis::Y })
		{
			m_size[dim] = min(clip->m_size[dim], m_size[dim]);

			float overflow = position[dim] + m_size[dim] - clip->m_size[dim];
			m_position[dim] -= max(0.f, overflow);
		}
	}

	vec4 Frame::content_rect() const
	{
		return { floor(d_inkstyle->m_margin.pos),
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

	void Frame::transfer_pixel_span(Frame& prev, Frame& next, Axis dim, float pixelSpan)
	{
		float pixspan = 1.f / this->m_size[dim];
		float offset = pixelSpan * pixspan;

		prev.set_span(dim, max(0.01f, prev.m_span[dim] + offset));
		next.set_span(dim, max(0.01f, next.m_span[dim] - offset));
		this->mark_dirty(DIRTY_FORCE_LAYOUT);
	}

	void Frame::relayout()
	{
		const DirtyLayout dirty = this->clearDirty();
		if(!dirty) return;

		SolverVector solvers;
		for(auto& widget : d_widget.m_nodes)
			collect_solvers(widget->m_frame, solvers, dirty);

		m_solver->reset();
		m_solver->m_size = m_size;

		two::relayout(solvers);
	}

	void Frame::sync_solver(FrameSolver& solver)
	{
		if(d_style->m_name == "Text")
			int i = 0;
		const vec2 content = m_content + rect_sum(d_inkstyle->m_padding);
		solver.setup(m_position, m_size, m_span, !empty() ? &content : nullptr);

		if(d_dirty == DIRTY_PARENT)
		{
			// @bug this causes a bug in the relayout if we want to implement scarce behavior for wrap frames, since here the content is instead just the unpadded size
			solver.d_content = m_size - rect_sum(solver.d_layout->m_padding);
		}
	}

	void fix_position(Frame& frame, Axis dim, FrameSolver* solver)
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

		fix_position(*this, Axis::X, &solver);
		fix_position(*this, Axis::Y, &solver);
	}

	void Frame::debug_print(bool commit)
	{
		Frame* parent = this->d_parent;
		while(parent)
		{
			printf("  ");
			parent = parent->d_parent;
		}
		printf("FRAME: %s ", d_style->m_name.c_str());
		if(commit)
			printf("\n");
	}
}


#ifdef TWO_MODULES
module two.ui;
#else
#include <stl/algorithm.h>
#endif

#include <algorithm>

namespace two
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
		auto lower = [](Layer* first, Layer* second)
		{
			if(first->z() == second->z())
				return first->d_index < second->d_index;
			else
				return first->z() < second->z();
		};

		std::sort(d_sublayers.begin(), d_sublayers.end(), lower);
		//quicksort<Layer*>(d_sublayers, lower);
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
		remove(d_sublayers, &layer);
		this->reindex();
		this->reorder();
	}

	void Layer::moveToTop()
	{
		d_parentLayer->removeLayer(*this);
		d_parentLayer->addLayer(*this);
	}
}


#ifdef TWO_MODULES
module two.ui;
#else
#endif

#include <cstdio>

#define DEBUG_BOUNDS 0
#define DEBUG_LAYOUT 0

namespace two
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

	Space Space::preset(Preset preset)
	{
		if     (preset == Preset::Sheet)  return { FlowAxis::Paragraph,	Sizing::Wrap,   Sizing::Wrap };
		else if(preset == Preset::Flex)	  return { FlowAxis::Same,	    Sizing::Wrap,   Sizing::Wrap };
		else if(preset == Preset::Item)   return { FlowAxis::Reading,   Sizing::Shrink, Sizing::Shrink };
		else if(preset == Preset::Unit)   return { FlowAxis::Paragraph, Sizing::Shrink, Sizing::Shrink };
		else if(preset == Preset::Block)  return { FlowAxis::Paragraph, Sizing::Fixed,  Sizing::Fixed };
		else if(preset == Preset::Line)   return { FlowAxis::Reading,   Sizing::Wrap,   Sizing::Shrink };
		else if(preset == Preset::Stack)  return { FlowAxis::Paragraph, Sizing::Shrink, Sizing::Wrap };
		else if(preset == Preset::Div)    return { FlowAxis::Flip,      Sizing::Wrap,   Sizing::Shrink };
		else if(preset == Preset::Spacer) return { FlowAxis::Same,      Sizing::Wrap,   Sizing::Shrink };
		else if(preset == Preset::Board)  return { FlowAxis::Reading,   Sizing::Expand, Sizing::Expand };
		else if(preset == Preset::Layout) return { FlowAxis::Paragraph, Sizing::Expand, Sizing::Expand };
		else 							  return { FlowAxis::Paragraph, Sizing::Wrap,   Sizing::Wrap };
	}

	table<Align, float> c_align_space = { 0.f, 0.5f, 1.f, 0.f, 1.f };
	table<Align, float> c_align_extent = { 0.f, 0.5f, 1.f, 1.f, 0.f };

	FrameSolver::FrameSolver()
	{}

	FrameSolver::FrameSolver(FrameSolver* solver, Layout* layout, Frame* frame)
		: d_frame(frame)
		, d_parent(solver)
		, d_layout(layout)
		, m_solvers{ solver ? &solver->solver(*this, Axis::X) : nullptr, solver ? &solver->solver(*this, Axis::Y) : nullptr }
		, d_grid(solver ? solver->grid() : nullptr)
	{
		if(d_layout)
			this->applySpace();
	}

	FrameSolver& FrameSolver::solver(FrameSolver& frame, Axis dim)
	{
		if(dim == d_length && d_grid && frame.d_frame && frame.d_parent != d_grid) // && !d_layout->m_no_grid
			return d_grid->solver(frame, dim);
		return *this;
	}

	void FrameSolver::applySpace(Axis length)
	{
		const Space& space = d_layout->m_space;

		if(length != Axis::None)
			d_length = length;
		else if(space.direction == FlowAxis::Flip)
			d_length = flip(d_parent->d_length);
		else if(space.direction == FlowAxis::Same)
			d_length = d_parent->d_length;
		else if(space.direction == FlowAxis::Reading)
			d_length = Axis::X;
		else if(space.direction == FlowAxis::Paragraph)
			d_length = Axis::Y;

		d_depth = flip(d_length);

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
		m_solvers[Axis::X]->compute(*this, Axis::X);
		m_solvers[Axis::Y]->compute(*this, Axis::Y);

#if DEBUG_BOUNDS
		if(!d_frame) return;
		d_frame->debug_print(false);
		printf(" layout measured content size %i , %i\n", int(d_content.x), int(d_content.y));
#endif
	}

	void FrameSolver::layout()
	{
		if(!d_parent) return;
		m_solvers[Axis::X]->layout(*this, Axis::X);
		m_solvers[Axis::Y]->layout(*this, Axis::Y);

#if DEBUG_LAYOUT
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

	void FrameSolver::compute(FrameSolver& frame, Axis dim)
	{
		UNUSED(frame); UNUSED(dim);
	}

	void FrameSolver::layout(FrameSolver& frame, Axis dim)
	{
		UNUSED(frame); UNUSED(dim);
	}

	RowSolver::RowSolver()
	{}

	RowSolver::RowSolver(FrameSolver* solver, Layout* layout, Frame* frame)
		: FrameSolver(solver, layout, frame)
	{}

	void RowSolver::compute(FrameSolver& frame, Axis dim)
	{
		if(dim == d_length && frame.flow() && frame.d_sizing[d_length] >= Sizing::Wrap)
			d_total_span += frame.m_span[d_length];

		if(!frame.sizeflow())
			return;

		if(frame.d_sizing[dim] <= Sizing::Wrap)
			this->measure(frame, dim);

		if(frame.d_sizing[dim] <= Sizing::Shrink && frame.flow() && dim == d_length)
			m_space_content[dim] += frame.dbounds(dim);

		if(dim == d_length && frame.d_sizing[d_length] >= Sizing::Wrap)
			d_content_expand = true;
	}

	void RowSolver::measure(FrameSolver& frame, Axis dim)
	{
		if(dim == d_length && frame.flow())
		{
			d_content[dim] += frame.dbounds(dim) + (d_count++ ? this->spacing() : 0.f);
			d_spacing[dim] += frame.dmargin(dim) * 2.f + (d_count++ ? this->spacing() : 0.f);
		}
		else
			d_content[dim] = max(d_content[dim], frame.dbounds(dim));
	}

	void RowSolver::layout(FrameSolver& frame, Axis dim)
	{
		if(dim == d_length && frame.flow() && frame.d_sizing[d_length] >= Sizing::Wrap)
			frame.m_span[d_length] = frame.m_span[d_length] / d_total_span;

		this->resize(frame, dim);

		if(frame.posflow())
			this->position(frame, dim);
	}

	void RowSolver::resize(FrameSolver& frame, Axis dim)
	{
		if(d_layout->m_layout[dim] < AutoLayout::Size)
			return;

		float space = this->dspace(dim);
		//bool hasSpace = space > d_content[dim]; // @todo: implement scarcity check, current behavior when scarce is wrong
		if(dim == d_length && frame.flow())
		{
			float spacings = d_spacing[dim];
			space -= (m_space_content[dim] + spacings);
			space *= frame.m_span[d_length];
		}
		else
		{
			space -= frame.dmargin(dim) * 2.f;
		}

		float content = frame.dcontent(dim);

		Sizing sizing = frame.d_sizing[dim];
		if(sizing == Sizing::Shrink)
			frame.m_size[dim] = content;
		else if(sizing == Sizing::Wrap)
			frame.m_size[dim] = max(content, space);
		else if(sizing == Sizing::Expand)
			frame.m_size[dim] = space;
	}

	void RowSolver::position(FrameSolver& frame, Axis dim)
	{
		if(d_layout->m_layout[dim] < AutoLayout::Layout)
			return;

		float space = this->dspace(dim);

		if(dim == d_length && frame.flow())
			frame.m_position[dim] = this->positionSequence(frame, d_content_expand ? 0.f : space - d_content[d_length]);
		else
			frame.m_position[dim] = this->positionFree(frame, dim, space);

		if(dim == d_length && frame.flow())
			d_prev = &frame;
	}

	float RowSolver::positionFree(FrameSolver& frame, Axis dim, float space)
	{
		Align align = frame.dalign(dim);// == d_length ? Axis::X : Axis::Y);
		float alignOffset = space * c_align_space[align] - frame.dextent(dim) * c_align_extent[align];
		return (frame.flow() ? dpadding(dim) + frame.dmargin(dim) : 0.f) + alignOffset;
	}

	float RowSolver::positionSequence(FrameSolver& frame, float space)
	{
		auto alignSequence = [&](FrameSolver& frame, float space) { return space * c_align_space[frame.dalign(d_length)]; };
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
		//style.m_space = { FlowAxis::Reading, Sizing::Expand, Sizing::Expand };
		style.m_space = { FlowAxis::Reading, Sizing::Wrap, Sizing::Wrap };
		style.m_flow = LayoutFlow::Overlay;
		style.m_spacing = { 2.f, 2.f };
		return style;
	}

	static Layout& columnSolverStyle()
	{
		static Layout style;
		//style.m_space = { FlowAxis::Paragraph, Sizing::Expand, Sizing::Expand };
		style.m_space = { FlowAxis::Paragraph, Sizing::Wrap, Sizing::Wrap };
		style.m_layout = { AutoLayout::Layout, AutoLayout::None };
		return style;
	}

	TableSolver::TableSolver(FrameSolver* solver, Layout* layout, Frame* frame)
		: CustomSolver(solver, layout, frame)
	{
		this->divide(layout->m_table_division);
	}

	void TableSolver::divide(span<float> columns)
	{
		m_solvers.clear();
		m_solvers.push_back(construct<RowSolver>(this, &gridOverlayStyle()));
		for(size_t i = 0; i < columns.size(); ++i)
		{
			m_solvers.push_back(construct<RowSolver>(m_solvers.front().get(), &columnSolverStyle()));
			m_solvers.back()->m_span = { columns[i], 0.f };
		}
	}

	void TableSolver::update(span<float> columns)
	{
		if(m_solvers.size() != columns.size() + 1)
			return divide(columns);

		for(size_t i = 0; i < columns.size(); ++i)
			m_solvers[1 + i]->m_span[d_depth] = columns[i];
	}

	FrameSolver& TableSolver::solver(FrameSolver& frame, Axis dim)
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
		d_layout.m_space.direction = FlowAxis::Reading;
		FrameSolver::d_layout = &d_layout;
		this->applySpace();
	}

	GridSolver::GridSolver(FrameSolver* solver, Layout* layout, Frame* frame)
		: CustomSolver(solver, layout, frame)
	{
		this->divide(layout->m_grid_division);
	}

	void GridSolver::divide(span<Space> lines)
	{
		m_solvers.clear();
		for(size_t i = 0; i < lines.size(); ++i)
			m_solvers.push_back(construct<LineSolver>(this, lines[i]));
	}

	FrameSolver& GridSolver::solver(FrameSolver& frame, Axis dim)
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

#ifdef TWO_MODULES
module two.ui;
#else
#include <stl/hash_base.hpp>
#endif

namespace two
{
	void style_blender_dark(UiWindow& ui_window)
	{
		layout_minimal(ui_window);

		const Colour active_blue_alpha = rgba(0x5680c2e6);
		const Colour active_blue = rgb(0x5680c2);
		const Colour grey_37 = rgb(0x373737);
		const Colour grey_44 = rgb(0x444444);
		const Colour grey_58 = rgb(0x585858);
		const Colour grey_59 = rgb(0x595959);
		const Colour white_d9 = rgb(0xd9d9d9);
		const Colour white_e6 = rgb(0xe6e6e6);
		const Colour white = rgb(0xffffff);

		auto wcol_regular = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = grey_37;
			i.m_background_colour = grey_58;
			s.m_background_colour = active_blue_alpha;
			//.item = RGBA(0x3e3e3eff),
			i.m_text_colour = white_d9;
			s.m_text_colour = white;
			//.shadedown = -5,
			//.roundness = 0.2f,
		};
		auto wcol_tool = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = grey_37;
			i.m_background_colour = grey_58;
			s.m_background_colour = active_blue;
			//.item = RGBA(0xffffffff);
			i.m_text_colour = white_e6;
			s.m_text_colour = white;
			//.shadedown = -5,
			//.roundness = 0.2f,
		};
		auto wcol_toolbar_item = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = grey_37;
			i.m_background_colour = rgb(0x313131);
			s.m_background_colour = active_blue;
			//.item = RGBA(0xffffff8f);
			i.m_text_colour = white_e6;
			s.m_text_colour = white;
			//.roundness = 0.2f,
		};
		auto wcol_text = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = grey_44;
			i.m_background_colour = rgb(0x1f1f1f);
			s.m_background_colour = rgba(0xb3b3b333);
			//.item = RGBA(0x191919ff);
			i.m_text_colour = white_e6;
			s.m_text_colour = white;
			//.shaded = 1,
			//.shadetop = -3,
			//.roundness = 0.2f,
		};
		auto wcol_radio = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = grey_37;
			i.m_background_colour = grey_59;
			s.m_background_colour = active_blue_alpha;
			//.item = RGBA(0xffffffff);
			i.m_text_colour = white_e6;
			s.m_text_colour = white;
			//.shadetop = 5,
			//.shadedown = -5,
			//.roundness = 0.2f,
		};
		auto wcol_option = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = grey_37;
			i.m_background_colour = rgb(0x666666);
			s.m_background_colour = active_blue_alpha;
			//.item = RGBA(0xffffffff);
			i.m_text_colour = white_e6;
			s.m_text_colour = white;
			//.shadedown = -15,
			//.roundness = 0.2f,
		};
		auto wcol_toggle = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = grey_37;
			i.m_background_colour = grey_59;
			s.m_background_colour = active_blue_alpha;
			//.item = RGBA(0x191919ff);
			i.m_text_colour = white_e6;
			s.m_text_colour = white;
			//.roundness = 0.2f,
		};
		auto wcol_num = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = grey_44;
			i.m_background_colour = grey_59;
			s.m_background_colour = rgba(0xb3b3b333);
			//.item = RGBA(0x191919ff);
			i.m_text_colour = white_e6;
			s.m_text_colour = white;
			//.roundness = 0.2f,
		};
		auto wcol_numslider = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = grey_44;
			i.m_background_colour = grey_59;
			s.m_background_colour = rgba(0xb3b3b333);
			//.item = RGBA(0x5680c2e6);
			i.m_text_colour = white_e6;
			s.m_text_colour = white;
			//.shaded = 1,
			//.shadetop = -4,
			//.roundness = 0.2f,
		};
		auto wcol_tab = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = rgb(0x202020);
			i.m_background_colour = rgb(0x2b2b2b);
			s.m_background_colour = rgb(0x424242);
			//.item = RGBA(0x2d2d2dff);
			i.m_text_colour = rgb(0x989898);
			s.m_text_colour = white;
			//.roundness = 0.2f,
		};
		auto wcol_menu = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = grey_44;
			i.m_background_colour = rgb(0x2c2c2c);
			s.m_background_colour = rgb(0x696e76);
			//.item = RGBA(0xe6e6e6ff);
			i.m_text_colour = white_d9;
			s.m_text_colour = white;
			//.shadetop = 10,
			//.shadedown = -10,
			//.roundness = 0.2f,
		};
		auto wcol_pulldown = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = rgb(0x4d4d4d);
			i.m_background_colour = rgba(0x2e2e2ecc);
			s.m_background_colour = active_blue_alpha;
			//.item = RGBA(0x727272ff);
			i.m_text_colour = white_d9;
			s.m_text_colour = white;
			//.shadetop = 25,
			//.shadedown = -20,
			//.roundness = 0.2f,
		};
		auto wcol_menu_back = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = rgb(0x19191a);
			i.m_background_colour = rgba(0x1f1f1fef);
			s.m_background_colour = rgb(0x585858);
			//.item = RGBA(0x727272ff);
			i.m_text_colour = rgb(0xa5a5a5);
			s.m_text_colour = white;
			//.shadetop = 25,
			//.shadedown = -20,
			//.roundness = 0.2f,
		};
		auto wcol_menu_item = [=](InkStyle& i, InkStyle& s)
		{
			s.m_background_colour = active_blue_alpha;
			//.item = RGBA(0xffffff8f);
			i.m_text_colour = white_e6;
			s.m_text_colour = white;
			//.shadetop = 38,
			//.roundness = 0.2f,
		};
		auto wcol_tooltip = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = rgb(0x19191a);
			i.m_background_colour = rgba(0x19191aef);
			s.m_background_colour = rgba(0x19191aef);
			//.item = RGBA(0x19191aef);
			i.m_text_colour = white_e6;
			s.m_text_colour = white;
			//.shadetop = 25,
			//.shadedown = -20,
			//.roundness = 0.2f,
		};
		auto wcol_box = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = grey_44;
			i.m_background_colour = rgba(0x00000033);
			s.m_background_colour = rgb(0x696e76);
			//.item = RGBA(0x191919ff);
			i.m_text_colour = white_e6;
			s.m_text_colour = white;
			//.roundness = 0.2f,
		};
		auto wcol_scroll = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = rgb(0x424242);
			i.m_background_colour = rgba(0x67676700);
			s.m_background_colour = rgb(0xb3b3b3);
			//.item = RGBA(0x676767ff);
			i.m_text_colour = white_e6;
			s.m_text_colour = white;
			//.shadetop = 5,
			//.shadedown = -5,
			//.roundness = 0.5f,
		};
		auto wcol_progress = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = rgb(0x585858);
			i.m_background_colour = rgb(0x2c2c2c);
			s.m_background_colour = active_blue;
			//.item = RGBA(0x5680c2ff);
			i.m_text_colour = white_e6;
			s.m_text_colour = white;
			//.roundness = 0.2f,
		};
		auto wcol_list_item = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = rgb(0x2d2d2d);
			i.m_background_colour = rgba(0x2d2d2d00);
			s.m_background_colour = rgb(0x696e76);
			//.item = RGBA(0xb3b3b3ff);
			i.m_text_colour = white_e6;
			s.m_text_colour = white;
			//.roundness = 0.2f,
		};
		auto wcol_pie_menu = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = rgb(0x333333);
			i.m_background_colour = rgba(0x212121ef);
			s.m_background_colour = active_blue_alpha;
			//.item = RGBA(0x585858ff);
			i.m_text_colour = white_d9;
			s.m_text_colour = white;
			//.shadetop = 10,
			//.shadedown = -10,
			//.roundness = 0.2f,
		};

		/*.tdefaults = {
			.back = RGBA(0x42424200),
			.title = RGBA(0xffffffff),
			.text = RGBA(0xe6e6e6ff),
			.text_hi = RGBA(0xffffffff),
			.header = RGBA(0x424242ff),
			.header_text = RGBA(0xeeeeeeff),
			.header_text_hi = RGBA(0xffffffff),
			.tab_active = RGBA(0x4b4b4bff),
			.tab_inactive = RGBA(0x2b2b2bff),
			.tab_back = RGBA(0x232323ff),
			.tab_outline = RGBA(0x232323ff),
			.button = RGBA(0x424242ff),
			.button_title = RGBA(0xffffffff),
			.button_text = RGBA(0xe5e5e5ff),
			.button_text_hi = RGBA(0xffffffff),
			.panelcolors = {
				.header = RGBA(0x424242cc),
				.back = RGBA(0x333333b3),
				.sub_back = RGBA(0x0000003e),
			},
		};*/

#if 0
		select({ "Label", "Title", "Message", "Tooltip", "TextEdit", "TypeLabel", "TypeZone", "SliderDisplay", "RadioChoiceItem" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_text_colour = white;
		})
		.decline({ DISABLED }, [&](InkStyle& i) {
			i.m_text_colour = grey248;
		});

		select({ "Element", "Button", "WrapButton", "MultiButton", "Toggle", "ToolButton", "TabHeader", "DockToggle", "RadioChoice", "DropdownChoice", "SliderKnob", "ScrollerKnob", "DragHandle", "DropdownInput", "DropdownInputCompact", "TypedownInput", "Menu", "TypeIn", "Input<string>", "TreeNodeHeader" })
		.declare([&](Layout& l, InkStyle& i) {
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
		.declare([&](Layout& l, InkStyle& i) {
			i = styles().button.skin();
		});

		select({ "Element", "TreeNodeHeader" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = grey86;
		});

		select({ "RadioChoiceItem" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_align = { CENTER, CENTER };
		});

		select({ "SliderKnob", "ScrollerKnob" })
		.declare([&](Layout& l, InkStyle& i) {
			i = styles().button.skin();
			i.m_background_colour = grey176;
		});

		select({ "SliderKnob" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = grey312;
			l.m_size = vec2(8, 22);
		});

		select({ "ScrollUp", "ScrollDown" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_image = ui_window.find_image("null");
			l.m_size = vec2(10, 0);
		});

		select({ "ScrollLeft", "ScrollRight" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_image = ui_window.find_image("null");
			l.m_size = vec2(0, 10);
		});

		select({ "DropdownToggle" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_image = ui_window.find_image("drop_down");
		});

		select({  "Checkbox" })
		.declare([&](Layout& l, InkStyle& i) {
			l.m_size = vec2(15.f);
			i.m_padding = vec4(1);
		})
		.decline({ ACTIVE }, [&](InkStyle& i) {
			i.m_image = ui_window.find_image("check_15");
		});

		select({ "Slider", "Fillbar", "TypeIn", "Input<string>"  })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = grey145;
			i.m_border_colour = grey312;
			i.m_border_width = vec4(1);
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = grey204;
			i.m_border_colour = grey400;
			i.m_border_width = vec4(1);
		})
		.decline({ FOCUSED }, [&](InkStyle& i) {
			i.m_background_colour = activeBlue;
		})
		.decline({ SELECTED }, [&](InkStyle& i) {
			i.m_border_colour = activeBlue;
		});

		select({ "Filler" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = grey248;
		});

		select({ "List", "Tree", "TabberHead", "TableHead", "Dockbar", "Header", "Menubar" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = grey117;
		});

		select({ "Window", "WindowFooter", "DockWindow", "Dockbox", "Tab", "TextEdit", "Node", "Section", "Popup", "Modal", "ColourPopup" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = grey52;
			i.m_border_colour = grey204;
			i.m_border_width = vec4(1);
		});

		select({ "Window", "Dockbox", "Node" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_shadow = { 2, 2, 7, 2 };
		})
		.decline({ SELECTED }, [&](InkStyle& i) {
			i.m_shadow = { 0, 0, 0, 1, grey600 };
		});

		select({ "WindowHeader", "WindowHeaderMovable", "NodeHeader" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = grey204;
		});

		select({  "WindowSizer", "WindowSizerLeft", "WindowSizerRight"  })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_image = ui_window.find_image("handle_x");
			i.m_padding = vec4(2);
		});

		select({ "WindowSizerRight" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_align = { Right, Right };
		});

		select({  "Toolbar", "Tooldock"  })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = grey145;
		});

		select({ "Canvas" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = black;
		});

		select({  "Tooltip", "Popdown", "DropdownList", "MenuList", "SubMenuList"  })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = { 0.098, 0.098, 0.098, 0.802 };
			i.m_text_colour = clearGreyText;
		});

		select({ "DropdownChoice" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = transparent;
		});

		select({ "TableRow", "TableRowOdd", "TableRowEven"  })
		.declare([&](Layout& l, InkStyle& i) {
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_border_colour = grey312;
			i.m_border_width = vec4(1);
		})
		.decline({ SELECTED }, [&](InkStyle& i) {
			i.m_border_colour = activeBlue;
			i.m_border_width = vec4(1);
		});
#endif

#if 0
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
		.declare([&](Layout& l, InkStyle& i) {
			i.m_text_colour = white;
		})
		.decline({ DISABLED }, [&](InkStyle& i) {
			i.m_text_colour = grey248;
		});

		select({ "Element", "Button", "WrapButton", "MultiButton", "Toggle", "ToolButton", "TabHeader", "DockToggle", "RadioChoice", "DropdownChoice", "SliderKnob", "ScrollerKnob", "DragHandle", "DropdownInput", "DropdownInputCompact", "TypedownInput", "Menu", "TypeIn", "Input<string>", "TreeNodeHeader" })
		.declare([&](Layout& l, InkStyle& i) {
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
		.declare([&](Layout& l, InkStyle& i) {
			i = styles().button.skin();
		});

		select({ "Element", "TreeNodeHeader" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = grey86;
		});

		select({ "RadioChoiceItem" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_align = { CENTER, CENTER };
		});

		select({ "SliderKnob", "ScrollerKnob" })
		.declare([&](Layout& l, InkStyle& i) {
			i = styles().button.skin();
			i.m_background_colour = grey176;
		});

		select({ "SliderKnob" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = grey312;
			l.m_size = vec2(8, 22);
		});

		select({ "ScrollUp", "ScrollDown" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_image = ui_window.find_image("null");
			l.m_size = vec2(10, 0);
		});

		select({ "ScrollLeft", "ScrollRight" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_image = ui_window.find_image("null");
			l.m_size = vec2(0, 10);
		});

		select({ "ExpandboxToggle", "TreeNodeToggle" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_image = ui_window.find_image("toggle_closed");
		})
		.decline({ ACTIVE }, [&](InkStyle& i) {
			i.m_image = ui_window.find_image("toggle_open");
		})
		.decline({ DISABLED }, [&](InkStyle& i) {
			i.m_image = ui_window.find_image("empty_15");
		});

		select({ "DropdownToggle" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_image = ui_window.find_image("drop_down");
		});

		select({  "Checkbox" })
		.declare([&](Layout& l, InkStyle& i) {
			l.m_size = vec2(15.f);
			i.m_padding = vec4(1);
		})
		.decline({ ACTIVE }, [&](InkStyle& i) {
			i.m_image = ui_window.find_image("check_15");
		});

		select({ "Slider", "Fillbar", "TypeIn", "Input<string>"  })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = grey145;
			i.m_border_colour = grey312;
			i.m_border_width = vec4(1);
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = grey204;
			i.m_border_colour = grey400;
			i.m_border_width = vec4(1);
		})
		.decline({ FOCUSED }, [&](InkStyle& i) {
			i.m_background_colour = activeBlue;
		})
		.decline({ SELECTED }, [&](InkStyle& i) {
			i.m_border_colour = activeBlue;
		});

		select({ "Filler" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = grey248;
		});

		select({ "List", "Tree", "TabberHead", "TableHead", "Dockbar", "Header", "Menubar" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = grey117;
		});

		select({ "Window", "WindowFooter", "DockWindow", "Dockbox", "Tab", "TextEdit", "Node", "Section", "Popup", "Modal", "ColourPopup" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = grey52;
			i.m_border_colour = grey204;
			i.m_border_width = vec4(1);
		});

		select({ "Window", "Dockbox", "Node" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_shadow = { 2, 2, 7, 2 };
		})
		.decline({ SELECTED }, [&](InkStyle& i) {
			i.m_shadow = { 0, 0, 0, 1, grey600 };
		});

		select({ "WindowHeader", "WindowHeaderMovable", "NodeHeader" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = grey204;
		});

		select({  "WindowSizer", "WindowSizerLeft", "WindowSizerRight"  })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_image = ui_window.find_image("handle_x");
			i.m_padding = vec4(2);
		});

		select({ "WindowSizerRight" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_align = { Right, Right };
		});

		select({  "Toolbar", "Tooldock"  })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = grey145;
		});

		select({ "Canvas" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = black;
		});

		select({  "Tooltip", "Popdown", "DropdownList", "MenuList", "SubMenuList"  })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = { 0.098, 0.098, 0.098, 0.802 };
			i.m_text_colour = clearGreyText;
		});

		select({ "DropdownChoice" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = transparent;
		});

		select({ "TableRow", "TableRowOdd", "TableRowEven"  })
		.declare([&](Layout& l, InkStyle& i) {
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_border_colour = grey312;
			i.m_border_width = vec4(1);
		})
		.decline({ SELECTED }, [&](InkStyle& i) {
			i.m_border_colour = activeBlue;
			i.m_border_width = vec4(1);
		});

		select({ "TableRowOdd" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = grey117;
		});

		select({ "TableRowEven" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = black;
		});
#endif
	}
}

/*
const bTheme U_theme_default = {
	.name = "Default",
	.tui = {
		.wcol_regular = {
			.outline = RGBA(0x373737ff),
			.inner = RGBA(0x585858ff),
			.inner_sel = RGBA(0x5680c2e6),
			.item = RGBA(0x3e3e3eff),
			.text = RGBA(0xd9d9d9ff),
			.text_sel = RGBA(0xffffffff),
			.shadedown = -5,
			.roundness = 0.2f,
		},
		.wcol_tool = {
			.outline = RGBA(0x373737ff),
			.inner = RGBA(0x585858ff),
			.inner_sel = RGBA(0x5680c2ff),
			.item = RGBA(0xffffffff),
			.text = RGBA(0xe6e6e6ff),
			.text_sel = RGBA(0xffffffff),
			.shadedown = -5,
			.roundness = 0.2f,
		},
		.wcol_toolbar_item = {
			.outline = RGBA(0x373737ff),
			.inner = RGBA(0x313131ff),
			.inner_sel = RGBA(0x5680c2ff),
			.item = RGBA(0xffffff8f),
			.text = RGBA(0xe6e6e6ff),
			.text_sel = RGBA(0xffffffff),
			.roundness = 0.2f,
		},
		.wcol_text = {
			.outline = RGBA(0x444444ff),
			.inner = RGBA(0x1f1f1fff),
			.inner_sel = RGBA(0xb3b3b333),
			.item = RGBA(0x191919ff),
			.text = RGBA(0xe6e6e6ff),
			.text_sel = RGBA(0xffffffff),
			.shaded = 1,
			.shadetop = -3,
			.roundness = 0.2f,
		},
		.wcol_radio = {
			.outline = RGBA(0x373737ff),
			.inner = RGBA(0x595959ff),
			.inner_sel = RGBA(0x5680c2e6),
			.item = RGBA(0xffffffff),
			.text = RGBA(0xe6e6e6ff),
			.text_sel = RGBA(0xffffffff),
			.shadetop = 5,
			.shadedown = -5,
			.roundness = 0.2f,
		},
		.wcol_option = {
			.outline = RGBA(0x373737ff),
			.inner = RGBA(0x666666ff),
			.inner_sel = RGBA(0x5680c2e6),
			.item = RGBA(0xffffffff),
			.text = RGBA(0xe6e6e6ff),
			.text_sel = RGBA(0xffffffff),
			.shadedown = -15,
			.roundness = 0.2f,
		},
		.wcol_toggle = {
			.outline = RGBA(0x373737ff),
			.inner = RGBA(0x595959ff),
			.inner_sel = RGBA(0x5680c2e6),
			.item = RGBA(0x191919ff),
			.text = RGBA(0xe6e6e6ff),
			.text_sel = RGBA(0xffffffff),
			.roundness = 0.2f,
		},
		.wcol_num = {
			.outline = RGBA(0x444444ff),
			.inner = RGBA(0x595959ff),
			.inner_sel = RGBA(0xb3b3b333),
			.item = RGBA(0x191919ff),
			.text = RGBA(0xe6e6e6ff),
			.text_sel = RGBA(0xffffffff),
			.roundness = 0.2f,
		},
		.wcol_numslider = {
			.outline = RGBA(0x444444ff),
			.inner = RGBA(0x595959ff),
			.inner_sel = RGBA(0xb3b3b333),
			.item = RGBA(0x5680c2e6),
			.text = RGBA(0xe6e6e6ff),
			.text_sel = RGBA(0xffffffff),
			.shaded = 1,
			.shadetop = -4,
			.roundness = 0.2f,
		},
		.wcol_tab = {
			.outline = RGBA(0x202020ff),
			.inner = RGBA(0x2b2b2bff),
			.inner_sel = RGBA(0x424242ff),
			.item = RGBA(0x2d2d2dff),
			.text = RGBA(0x989898ff),
			.text_sel = RGBA(0xffffffff),
			.roundness = 0.2f,
		},
		.wcol_menu = {
			.outline = RGBA(0x444444ff),
			.inner = RGBA(0x2c2c2cff),
			.inner_sel = RGBA(0x696e76ff),
			.item = RGBA(0xe6e6e6ff),
			.text = RGBA(0xd9d9d9ff),
			.text_sel = RGBA(0xffffffff),
			.shadetop = 10,
			.shadedown = -10,
			.roundness = 0.2f,
		},
		.wcol_pulldown = {
			.outline = RGBA(0x4d4d4dff),
			.inner = RGBA(0x2e2e2ecc),
			.inner_sel = RGBA(0x5680c2e6),
			.item = RGBA(0x727272ff),
			.text = RGBA(0xd9d9d9ff),
			.text_sel = RGBA(0xffffffff),
			.shadetop = 25,
			.shadedown = -20,
			.roundness = 0.2f,
		},
		.wcol_menu_back = {
			.outline = RGBA(0x19191aff),
			.inner = RGBA(0x1f1f1fef),
			.inner_sel = RGBA(0x585858ff),
			.item = RGBA(0x727272ff),
			.text = RGBA(0xa5a5a5ff),
			.text_sel = RGBA(0xffffffff),
			.shadetop = 25,
			.shadedown = -20,
			.roundness = 0.2f,
		},
		.wcol_menu_item = {
			.inner_sel = RGBA(0x5680c2e6),
			.item = RGBA(0xffffff8f),
			.text = RGBA(0xe6e6e6ff),
			.text_sel = RGBA(0xffffffff),
			.shadetop = 38,
			.roundness = 0.2f,
		},
		.wcol_tooltip = {
			.outline = RGBA(0x19191aff),
			.inner = RGBA(0x19191aef),
			.inner_sel = RGBA(0x19191aef),
			.item = RGBA(0x19191aef),
			.text = RGBA(0xe6e6e6ff),
			.text_sel = RGBA(0xffffffff),
			.shadetop = 25,
			.shadedown = -20,
			.roundness = 0.2f,
		},
		.wcol_box = {
			.outline = RGBA(0x444444ff),
			.inner = RGBA(0x00000033),
			.inner_sel = RGBA(0x696e76ff),
			.item = RGBA(0x191919ff),
			.text = RGBA(0xe6e6e6ff),
			.text_sel = RGBA(0xffffffff),
			.roundness = 0.2f,
		},
		.wcol_scroll = {
			.outline = RGBA(0x424242ff),
			.inner = RGBA(0x67676700),
			.inner_sel = RGBA(0xb3b3b3ff),
			.item = RGBA(0x676767ff),
			.text = RGBA(0xe6e6e6ff),
			.text_sel = RGBA(0xffffffff),
			.shadetop = 5,
			.shadedown = -5,
			.roundness = 0.5f,
		},
		.wcol_progress = {
			.outline = RGBA(0x585858ff),
			.inner = RGBA(0x2c2c2cff),
			.inner_sel = RGBA(0x5680c2ff),
			.item = RGBA(0x5680c2ff),
			.text = RGBA(0xe6e6e6ff),
			.text_sel = RGBA(0xffffffff),
			.roundness = 0.2f,
		},
		.wcol_list_item = {
			.outline = RGBA(0x2d2d2dff),
			.inner = RGBA(0x2d2d2d00),
			.inner_sel = RGBA(0x696e76ff),
			.item = RGBA(0xb3b3b3ff),
			.text = RGBA(0xe6e6e6ff),
			.text_sel = RGBA(0xffffffff),
			.roundness = 0.2f,
		},
		.wcol_pie_menu = {
			.outline = RGBA(0x333333ff),
			.inner = RGBA(0x212121ef),
			.inner_sel = RGBA(0x5680c2e6),
			.item = RGBA(0x585858ff),
			.text = RGBA(0xd9d9d9ff),
			.text_sel = RGBA(0xffffffff),
			.shadetop = 10,
			.shadedown = -10,
			.roundness = 0.2f,
		},
		.wcol_state = {
			.inner_anim = RGBA(0x53992eff),
			.inner_anim_sel = RGBA(0x5aa633ff),
			.inner_key = RGBA(0xb3ae36ff),
			.inner_key_sel = RGBA(0xd7d34bff),
			.inner_driven = RGBA(0x9000ccff),
			.inner_driven_sel = RGBA(0x9900e6ff),
			.inner_overridden = RGBA(0x19c3c300),
			.inner_overridden_sel = RGBA(0x118f8f00),
			.inner_changed = RGBA(0xcc7529ff),
			.inner_changed_sel = RGBA(0xe6852dff),
			.blend = 0.5f,
		},
		.widget_emboss = RGBA(0x00000005),
		.menu_shadow_fac = 0.3f,
		.menu_shadow_width = 4,
		.editor_outline = RGBA(0x1f1f1fff),
		.icon_alpha = 1.0f,
		.icon_saturation = 0.5f,
		.xaxis = RGBA(0xff3352ff),
		.yaxis = RGBA(0x8bdc00ff),
		.zaxis = RGBA(0x2890ffff),
		.gizmo_hi = RGBA(0xffffffff),
		.gizmo_primary = RGBA(0xf5f14dff),
		.gizmo_secondary = RGBA(0x63ffffff),
		.gizmo_a = RGBA(0x4da84dff),
		.gizmo_b = RGBA(0xa33535ff),
		.icon_collection = RGBA(0xe6e6e6ff),
		.icon_object = RGBA(0xe49759ff),
		.icon_object_data = RGBA(0x89e689ff),
		.icon_modifier = RGBA(0x84b8ffff),
		.icon_shading = RGBA(0xff6060ff),
	},
	.tdefaults = {
		.back = RGBA(0x42424200),
		.title = RGBA(0xffffffff),
		.text = RGBA(0xe6e6e6ff),
		.text_hi = RGBA(0xffffffff),
		.header = RGBA(0x424242ff),
		.header_text = RGBA(0xeeeeeeff),
		.header_text_hi = RGBA(0xffffffff),
		.tab_active = RGBA(0x4b4b4bff),
		.tab_inactive = RGBA(0x2b2b2bff),
		.tab_back = RGBA(0x232323ff),
		.tab_outline = RGBA(0x232323ff),
		.button = RGBA(0x424242ff),
		.button_title = RGBA(0xffffffff),
		.button_text = RGBA(0xe5e5e5ff),
		.button_text_hi = RGBA(0xffffffff),
		.panelcolors = {
			.header = RGBA(0x424242cc),
			.back = RGBA(0x333333b3),
			.sub_back = RGBA(0x0000003e),
		},
	},
	.tbuts = {
		.title = RGBA(0xd4d4d4ff),
		.navigation_bar = RGBA(0x232323ff),
		.panelcolors = {
			.header = RGBA(0x42424200),
			.back = RGBA(0x00000028),
			.sub_back = RGBA(0x00000024),
		},
		.vertex_size = 3,
		.outline_width = 1,
		.facedot_size = 4,
	},
	.tv3d = {
		.title = RGBA(0xeeeeeeff),
		.button = RGBA(0x35353500),
		.button_text = RGBA(0xe5e5e5ff),
		.panelcolors = {
			.header = RGBA(0x424242e6),
			.back = RGBA(0x333333f0),
			.sub_back = RGBA(0x0000003e),
		},
		.gradients = {
			.gradient = RGBA(0x39393900),
			.high_gradient = RGBA(0x393939ff),
		},
		.grid = RGBA(0xa7a7a733),
		.wire = RGBA(0x000000ff),
		.wire_edit = RGBA(0x111111ff),
		.select = RGBA(0xed5700ff),
		.lamp = RGBA(0x00000028),
		.speaker = RGBA(0x000000ff),
		.empty = RGBA(0x000000ff),
		.camera = RGBA(0x000000ff),
		.active = RGBA(0xffa028ff),
		.transform = RGBA(0xffffffff),
		.vertex = RGBA(0x000000ff),
		.vertex_select = RGBA(0xff8500ff),
		.vertex_bevel = RGBA(0x00a5ffff),
		.edge = RGBA(0x000000ff),
		.edge_select = RGBA(0xffa000ff),
		.edge_seam = RGBA(0xdb2512ff),
		.edge_sharp = RGBA(0x00ffffff),
		.edge_facesel = RGBA(0x4b4b4bff),
		.edge_crease = RGBA(0xcc0099ff),
		.edge_bevel = RGBA(0x00a5ffff),
		.face = RGBA(0x00000012),
		.face_select = RGBA(0xff85004d),
		.face_dot = RGBA(0xff8500ff),
		.extra_edge_len = RGBA(0x150806ff),
		.extra_edge_angle = RGBA(0x4d4d00ff),
		.extra_face_angle = RGBA(0x0000ccff),
		.extra_face_area = RGBA(0x004d00ff),
		.normal = RGBA(0x22ddddff),
		.vertex_normal = RGBA(0x2361ddff),
		.loop_normal = RGBA(0xdd23ddff),
		.bone_solid = RGBA(0xc8c8c8ff),
		.bone_pose = RGBA(0x50c8ff50),
		.bone_pose_active = RGBA(0x8cffff50),
		.cframe = RGBA(0x60c040ff),
		.time_keyframe = RGBA(0xddd700ff),
		.time_gp_keyframe = RGBA(0xb5e61dff),
		.freestyle_edge_mark = RGBA(0x7fff7fff),
		.freestyle_face_mark = RGBA(0x7fff7f33),
		.nurb_uline = RGBA(0x909000ff),
		.nurb_vline = RGBA(0x803060ff),
		.act_spline = RGBA(0xdb2512ff),
		.nurb_sel_uline = RGBA(0xf0ff40ff),
		.nurb_sel_vline = RGBA(0xf090a0ff),
		.lastsel_point = RGBA(0xffffffff),
		.handle_free = RGBA(0x000000ff),
		.handle_auto = RGBA(0x909000ff),
		.handle_vect = RGBA(0x409030ff),
		.handle_align = RGBA(0x803060ff),
		.handle_sel_free = RGBA(0x000000ff),
		.handle_sel_auto = RGBA(0xf0ff40ff),
		.handle_sel_vect = RGBA(0x40c030ff),
		.handle_sel_align = RGBA(0xf090a0ff),
		.vertex_size = 3,
		.outline_width = 1,
		.facedot_size = 3,
		.editmesh_active = RGBA(0xffffff80),
		.clipping_border_3d = RGBA(0x313131ff),
		.bundle_solid = RGBA(0xc8c8c8ff),
		.camera_path = RGBA(0x000000ff),
		.gp_vertex_size = 3,
		.gp_vertex = RGBA(0x000000ff),
		.gp_vertex_select = RGBA(0xff8500ff),
		.skin_root = RGBA(0xb44d4dff),
		.paint_curve_pivot = RGBA(0xff7f7f7f),
		.paint_curve_handle = RGBA(0x7fff7f7f),
	},
	.tfile = {
		.back = RGBA(0x35353500),
		.header = RGBA(0x2e2e2eff),
		.hilite = RGBA(0x4f76b3ff),
		.vertex_size = 3,
		.outline_width = 1,
		.facedot_size = 4,
	},
	.tipo = {
		.text = RGBA(0x000000ff),
		.header = RGBA(0x2e2e2eff),
		.list = RGBA(0x333333ff),
		.list_title = RGBA(0xffffffff),
		.list_text = RGBA(0xb8b8b8ff),
		.list_text_hi = RGBA(0xffffffff),
		.shade1 = RGBA(0x96969600),
		.shade2 = RGBA(0x33333364),
		.grid = RGBA(0x2a2a2aff),
		.group = RGBA(0x16330fff),
		.group_active = RGBA(0x368024ff),
		.vertex = RGBA(0x000000ff),
		.vertex_select = RGBA(0xff8500ff),
		.cframe = RGBA(0x5680c2ff),
		.lastsel_point = RGBA(0xffffffff),
		.handle_auto = RGBA(0x909000ff),
		.handle_vect = RGBA(0x409030ff),
		.handle_align = RGBA(0x803060ff),
		.handle_auto_clamped = RGBA(0x994030ff),
		.handle_sel_auto = RGBA(0xf0ff40ff),
		.handle_sel_vect = RGBA(0x40c030ff),
		.handle_sel_align = RGBA(0xf090a0ff),
		.handle_sel_auto_clamped = RGBA(0xf0af90ff),
		.ds_channel = RGBA(0x0f2c4dff),
		.ds_subchannel = RGBA(0x143e66ff),
		.vertex_size = 6,
		.outline_width = 1,
		.facedot_size = 4,
		.handle_vertex_select = RGBA(0xff8500ff),
		.handle_vertex_size = 5,
		.anim_preview_range = RGBA(0xa14d0066),
	},
	.tinfo = {
		.title = RGBA(0xeeeeeeff),
		.vertex_size = 3,
		.outline_width = 1,
		.facedot_size = 4,
		.info_selected = RGBA(0x6080ffff),
		.info_selected_text = RGBA(0xffffffff),
		.info_error = RGBA(0x990000ff),
		.info_error_text = RGBA(0xffffffff),
		.info_warning = RGBA(0xb36a00ff),
		.info_warning_text = RGBA(0xffffffff),
		.info_info = RGBA(0x668000ff),
		.info_info_text = RGBA(0xffffffff),
		.info_debug = RGBA(0xd3d3d3ff),
	},
	.tact = {
		.title = RGBA(0xeeeeeeff),
		.text = RGBA(0x000000ff),
		.list = RGBA(0x333333ff),
		.list_title = RGBA(0xffffffff),
		.list_text = RGBA(0xb8b8b8ff),
		.list_text_hi = RGBA(0xffffffff),
		.shade1 = RGBA(0xc0c0c000),
		.shade2 = RGBA(0x333333ff),
		.hilite = RGBA(0x60c04044),
		.grid = RGBA(0x2a2a2aff),
		.group = RGBA(0x16330f37),
		.group_active = RGBA(0x36802455),
		.strip = RGBA(0x1a151580),
		.strip_select = RGBA(0xff8c00cc),
		.cframe = RGBA(0x5680c2ff),
		.ds_channel = RGBA(0x0f2c4d24),
		.ds_subchannel = RGBA(0x143e6624),
		.ds_ipoline = RGBA(0x94e575cc),
		.keytype_keyframe = RGBA(0xe8e8e8ff),
		.keytype_extreme = RGBA(0xe8b3ccff),
		.keytype_breakdown = RGBA(0xb3dbe8ff),
		.keytype_jitter = RGBA(0x94e575ff),
		.keytype_movehold = RGBA(0x5c5656ff),
		.keytype_keyframe_select = RGBA(0xffbe33ff),
		.keytype_extreme_select = RGBA(0xf28080ff),
		.keytype_breakdown_select = RGBA(0x54bfedff),
		.keytype_jitter_select = RGBA(0x61c042ff),
		.keytype_movehold_select = RGBA(0xffaf23ff),
		.keyborder = RGBA(0x000000ff),
		.keyborder_select = RGBA(0x000000ff),
		.vertex_size = 3,
		.outline_width = 1,
		.facedot_size = 4,
		.keyframe_scale_fac = 1.0f,
		.handle_vertex_size = 4,
		.anim_active = RGBA(0x4d250066),
		.anim_preview_range = RGBA(0xa14d0066),
	},
	.tnla = {
		.text = RGBA(0x000000ff),
		.list = RGBA(0x333333ff),
		.list_title = RGBA(0xffffffff),
		.list_text = RGBA(0xb8b8b8ff),
		.list_text_hi = RGBA(0xccccccff),
		.shade1 = RGBA(0x96969600),
		.grid = RGBA(0x2a2a2aff),
		.strip = RGBA(0x0c0a0a80),
		.strip_select = RGBA(0xff8c00ff),
		.cframe = RGBA(0x5680c2ff),
		.ds_channel = RGBA(0x5a85b2ff),
		.ds_subchannel = RGBA(0x7d98b3ff),
		.keyborder = RGBA(0x000000ff),
		.keyborder_select = RGBA(0x000000ff),
		.vertex_size = 3,
		.outline_width = 1,
		.facedot_size = 4,
		.handle_vertex_size = 4,
		.anim_active = RGBA(0xcc701a66),
		.anim_non_active = RGBA(0x9987614d),
		.anim_preview_range = RGBA(0xa14d0066),
		.nla_tweaking = RGBA(0x4df31a4d),
		.nla_tweakdupli = RGBA(0xd90000ff),
		.nla_transition = RGBA(0x1c2630ff),
		.nla_transition_sel = RGBA(0x2e75dbff),
		.nla_meta = RGBA(0x332642ff),
		.nla_meta_sel = RGBA(0x692196ff),
		.nla_sound = RGBA(0x2b3d3dff),
		.nla_sound_sel = RGBA(0x1f7a7aff),
	},
	.tseq = {
		.title = RGBA(0xeeeeeeff),
		.text = RGBA(0x000000ff),
		.shade1 = RGBA(0xa0a0a000),
		.grid = RGBA(0x404040ff),
		.vertex_select = RGBA(0xff8500ff),
		.bone_pose = RGBA(0x50c8ff50),
		.cframe = RGBA(0x5680c2ff),
		.vertex_size = 3,
		.outline_width = 1,
		.facedot_size = 4,
		.movie = RGBA(0x516987ff),
		.movieclip = RGBA(0x20208fff),
		.image = RGBA(0x6d5881ff),
		.scene = RGBA(0x4e983eff),
		.audio = RGBA(0x2e8f8fff),
		.effect = RGBA(0xa9547cff),
		.transition = RGBA(0xa25f6fff),
		.meta = RGBA(0x6d9183ff),
		.text_strip = RGBA(0xa29700ff),
		.gp_vertex_size = 3,
		.gp_vertex_select = RGBA(0xff8500ff),
		.metadatatext = RGBA(0xffffffff),
	},
	.tima = {
		.back = RGBA(0x44444400),
		.title = RGBA(0xeeeeeeff),
		.button = RGBA(0x35353500),
		.button_text = RGBA(0xe5e5e5ff),
		.wire_edit = RGBA(0xc0c0c0ff),
		.vertex_select = RGBA(0xff8500ff),
		.edge_select = RGBA(0xff8500ff),
		.face = RGBA(0xffffff0a),
		.face_select = RGBA(0xff85003c),
		.face_dot = RGBA(0xff8500ff),
		.cframe = RGBA(0x60c040ff),
		.freestyle_face_mark = RGBA(0x7fff7f33),
		.handle_auto = RGBA(0x909000ff),
		.handle_align = RGBA(0x803060ff),
		.handle_sel_auto = RGBA(0xf0ff40ff),
		.handle_sel_align = RGBA(0xf090a0ff),
		.vertex_size = 3,
		.outline_width = 1,
		.facedot_size = 3,
		.editmesh_active = RGBA(0xffffff80),
		.handle_vertex_select = RGBA(0xffff00ff),
		.handle_vertex_size = 5,
		.gp_vertex_size = 3,
		.gp_vertex_select = RGBA(0xff8500ff),
		.preview_back = RGBA(0x727272ff),
		.preview_stitch_face = RGBA(0x7f7f0033),
		.preview_stitch_edge = RGBA(0xff00ff33),
		.preview_stitch_vert = RGBA(0x0000ff33),
		.preview_stitch_stitchable = RGBA(0x00ff00ff),
		.preview_stitch_unstitchable = RGBA(0xff0000ff),
		.preview_stitch_active = RGBA(0xe1d2c323),
		.uv_shadow = RGBA(0x707070ff),
		.uv_others = RGBA(0x606060ff),
		.paint_curve_pivot = RGBA(0xff7f7f7f),
		.paint_curve_handle = RGBA(0x7fff7f7f),
		.metadatatext = RGBA(0xffffffff),
	},
	.text = {
		.back = RGBA(0x30303000),
		.title = RGBA(0xeeeeeeff),
		.panelcolors = {
			.header = RGBA(0x42424200),
			.back = RGBA(0x333333b3),
			.sub_back = RGBA(0x0000003e),
		},
		.shade2 = RGBA(0x19191aff),
		.hilite = RGBA(0xff0000ff),
		.grid = RGBA(0x313133ff),
		.vertex_size = 3,
		.outline_width = 1,
		.facedot_size = 4,
		.syntaxl = RGBA(0xf6e162ff),
		.syntaxs = RGBA(0xff734dff),
		.syntaxb = RGBA(0xff1961ff),
		.syntaxn = RGBA(0x50dbffff),
		.syntaxv = RGBA(0x95d600ff),
		.syntaxc = RGBA(0x939393ff),
		.syntaxd = RGBA(0xad80ffff),
		.syntaxr = RGBA(0xc4753bff),
	},
	.toops = {
		.back = RGBA(0x28282800),
		.text = RGBA(0xc3c3c3ff),
		.header = RGBA(0x454545ff),
		.vertex_size = 3,
		.outline_width = 1,
		.facedot_size = 4,
		.match = RGBA(0x337f334c),
		.selected_highlight = RGBA(0x314e784c),
	},
	.ttime = {
		.vertex_size = 3,
		.outline_width = 1,
		.facedot_size = 4,
	},
	.tnode = {
		.back = RGBA(0x23232300),
		.title = RGBA(0xeeeeeeff),
		.list = RGBA(0x2e2e2eff),
		.list_title = RGBA(0xffffffff),
		.list_text = RGBA(0xccccccff),
		.list_text_hi = RGBA(0xffffffff),
		.shade2 = RGBA(0x7f707064),
		.wire = RGBA(0x808080ff),
		.select = RGBA(0xed5700ff),
		.active = RGBA(0xffffffff),
		.edge_select = RGBA(0xffffffff),
		.console_output = RGBA(0x1a1a1aff),
		.vertex_size = 3,
		.outline_width = 1,
		.facedot_size = 4,
		.syntaxl = RGBA(0x565656ff),
		.syntaxs = RGBA(0x975b5bff),
		.syntaxb = RGBA(0xccb83dff),
		.syntaxn = RGBA(0xe64555ff),
		.syntaxv = RGBA(0x66c4ffff),
		.syntaxc = RGBA(0x426628ff),
		.syntaxd = RGBA(0x749797ff),
		.syntaxr = RGBA(0x808080ff),
		.nodeclass_output = RGBA(0xb33641ff),
		.nodeclass_filter = RGBA(0x584d80ff),
		.nodeclass_vector = RGBA(0x9b80ffff),
		.nodeclass_texture = RGBA(0xe68745ff),
		.nodeclass_shader = RGBA(0x39c884ff),
		.nodeclass_script = RGBA(0x084d4dff),
		.nodeclass_pattern = RGBA(0x6c696fff),
		.nodeclass_layout = RGBA(0x6c696fff),
		.movie = RGBA(0x1a1a1acc),
		.gp_vertex_size = 3,
		.gp_vertex = RGBA(0x97979700),
		.gp_vertex_select = RGBA(0xff8500ff),
	},
	.tuserpref = {
		.title = RGBA(0xeeeeeeff),
		.navigation_bar = RGBA(0x373737ff),
		.panelcolors = {
			.header = RGBA(0x42424200),
			.back = RGBA(0x333333b3),
			.sub_back = RGBA(0x0000003e),
		},
		.vertex_size = 3,
		.outline_width = 1,
		.facedot_size = 4,
	},
	.tconsole = {
		.back = RGBA(0x30303000),
		.title = RGBA(0xeeeeeeff),
		.console_output = RGBA(0x71a8ffff),
		.console_input = RGBA(0xf2f2f2ff),
		.console_info = RGBA(0x95d600ff),
		.console_error = RGBA(0xff4d84ff),
		.console_cursor = RGBA(0xff0000ff),
		.console_select = RGBA(0xffffff30),
		.vertex_size = 3,
		.outline_width = 1,
		.facedot_size = 4,
	},
	.tclip = {
		.title = RGBA(0xeeeeeeff),
		.list = RGBA(0x666666ff),
		.list_text = RGBA(0x000000ff),
		.list_text_hi = RGBA(0xffffffff),
		.strip = RGBA(0x0c0a0a80),
		.strip_select = RGBA(0xff8c00ff),
		.cframe = RGBA(0x5680c2ff),
		.handle_auto = RGBA(0x909000ff),
		.handle_align = RGBA(0x803060ff),
		.handle_sel_auto = RGBA(0xf0ff40ff),
		.handle_sel_align = RGBA(0xf090a0ff),
		.vertex_size = 3,
		.outline_width = 1,
		.facedot_size = 4,
		.handle_vertex_select = RGBA(0xffff00ff),
		.handle_vertex_size = 5,
		.marker = RGBA(0x7f7f00ff),
		.act_marker = RGBA(0xffffffff),
		.sel_marker = RGBA(0xffff00ff),
		.dis_marker = RGBA(0x7f0000ff),
		.lock_marker = RGBA(0x7f7f7fff),
		.path_before = RGBA(0xff0000ff),
		.path_after = RGBA(0x0000ffff),
		.gp_vertex_size = 1,
		.metadatatext = RGBA(0xffffffff),
	},
	.ttopbar = {
		.header = RGBA(0x232323ff),
		.vertex_size = 3,
		.outline_width = 1,
		.facedot_size = 4,
		.gp_vertex_size = 3,
	},
	.tstatusbar = {
		.back = RGBA(0x2e2e2e00),
		.text = RGBA(0x838383ff),
		.header = RGBA(0x303030ff),
		.header_text = RGBA(0xaaaaaaff),
		.button = RGBA(0x353535ff),
		.button_text_hi = RGBA(0xffffffff),
		.vertex_size = 3,
		.outline_width = 1,
		.facedot_size = 4,
		.gp_vertex_size = 3,
	},
	.tarm = {
		{
			.solid = RGBA(0x9a0000ff),
			.select = RGBA(0xbd1111ff),
			.active = RGBA(0xf70a0aff),
		},
		{
			.solid = RGBA(0xf74018ff),
			.select = RGBA(0xf66913ff),
			.active = RGBA(0xfa9900ff),
		},
		{
			.solid = RGBA(0x1e9109ff),
			.select = RGBA(0x59b70bff),
			.active = RGBA(0x83ef1dff),
		},
		{
			.solid = RGBA(0x0a3694ff),
			.select = RGBA(0x3667dfff),
			.active = RGBA(0x5ec1efff),
		},
		{
			.solid = RGBA(0xa9294eff),
			.select = RGBA(0xc1416aff),
			.active = RGBA(0xf05d91ff),
		},
		{
			.solid = RGBA(0x430c78ff),
			.select = RGBA(0x543aa3ff),
			.active = RGBA(0x8764d5ff),
		},
		{
			.solid = RGBA(0x24785aff),
			.select = RGBA(0x3c9579ff),
			.active = RGBA(0x6fb6abff),
		},
		{
			.solid = RGBA(0x4b707cff),
			.select = RGBA(0x6a8691ff),
			.active = RGBA(0x9bc2cdff),
		},
		{
			.solid = RGBA(0xf4c90cff),
			.select = RGBA(0xeec236ff),
			.active = RGBA(0xf3ff00ff),
		},
		{
			.solid = RGBA(0x1e2024ff),
			.select = RGBA(0x484c56ff),
			.active = RGBA(0xffffffff),
		},
		{
			.solid = RGBA(0x6f2f6aff),
			.select = RGBA(0x9845beff),
			.active = RGBA(0xd330d6ff),
		},
		{
			.solid = RGBA(0x6c8e22ff),
			.select = RGBA(0x7fb022ff),
			.active = RGBA(0xbbef5bff),
		},
		{
			.solid = RGBA(0x8d8d8dff),
			.select = RGBA(0xb0b0b0ff),
			.active = RGBA(0xdededeff),
		},
		{
			.solid = RGBA(0x834326ff),
			.select = RGBA(0x8b5811ff),
			.active = RGBA(0xbd6a11ff),
		},
		{
			.solid = RGBA(0x08310eff),
			.select = RGBA(0x1c430bff),
			.active = RGBA(0x34622bff),
		},
		{
			.solid = RGBA(0x000000ff),
			.select = RGBA(0x000000ff),
			.active = RGBA(0x000000ff),
		},
		{
			.solid = RGBA(0x000000ff),
			.select = RGBA(0x000000ff),
			.active = RGBA(0x000000ff),
		},
		{
			.solid = RGBA(0x000000ff),
			.select = RGBA(0x000000ff),
			.active = RGBA(0x000000ff),
		},
		{
			.solid = RGBA(0x000000ff),
			.select = RGBA(0x000000ff),
			.active = RGBA(0x000000ff),
		},
		{
			.solid = RGBA(0x000000ff),
			.select = RGBA(0x000000ff),
			.active = RGBA(0x000000ff),
		},
	},
};
*/

#ifdef TWO_MODULES
module two.ui;
#else
#include <stl/hash_base.hpp>
#endif

#include <cstdio>

namespace two
{
	void style_blendish(UiWindow& ui_window)
	{
		//layout_minimal(ui_window);

		const Colour white = Colour(1.f);
		const Colour black = Colour(0.f);
		const Colour activeBlue = Colour(0.337f, 0.502f, 0.761f);
		const Colour alphaGrey = Colour(1.f, 0.3f);
		const Colour greyOverlay = Colour(0.098f, 0.902f);
		const Colour grey706 = Colour(0.706f);
		const Colour grey650 = Colour(0.650f);
		const Colour grey600 = Colour(0.600f);
		const Colour grey392 = Colour(0.392f);
		const Colour grey335 = Colour(0.335f);
		const Colour grey275 = Colour(0.275f);
		const Colour grey146 = Colour(0.146f);
		const Colour grey090 = Colour(0.090f);

		auto blendish_text = [&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_text_colour = white;
			i.m_padding = vec4(4.f);
		};

        auto blendish = [&](Layout& l, InkStyle& i) { UNUSED(l);
			blendish_text(l, i);
			i.m_border_colour = grey146;
			i.m_border_width = vec4(1.f);
			i.m_corner_radius = vec4(4.f);
			i.m_linear_gradient = vec2(15.f, -15.f);
		};

        auto blendish_dark = [&](Layout& l, InkStyle& i) { UNUSED(l);
			blendish(l, i);
			i.m_background_colour = grey275;
		};
		
        auto blendish_clear = [&](Layout& l, InkStyle& i) { UNUSED(l);
			blendish(l, i);
			i.m_background_colour = grey600;
		};
		
		select({ "Item", "Label", "Text", "Title", "TextEdit", "TypeLabel", "TypeZone", "SliderDisplay", "RadioChoiceItem" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			blendish_text(l, i);
		});

        select({ "Dockbar", "Menubar", "WindowHeader", "WindowHeaderMovable", "WindowFooter", "NodeBody", "NodeHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			blendish_dark(l, i);
		});
		
        select({ "Menubar", "WindowHeader", "WindowHeaderMovable", "WindowFooter", "NodeHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_border_width = vec4(0.f);
		});

        select({ "Filler", "Slider", "Scroller", "ScrollerKnob", "NumberField" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			blendish(l, i);
		});

        select({ "Checkbox", "Toggle", "DockToggle", "ToolButton", "CloseButton", "RadioChoice", "Dropdown", "DropdownInput", "TabHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			blendish_dark(l, i);
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = grey335;
		});

        select({ "Button", "Slider", "TypeIn", "Input<string>", "NumberField", "TypedownInput" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			blendish_clear(l, i);
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
            i.m_background_colour = grey650;
		});

		select({ "NumberField", "Slider", "TypeIn", "Input<string>", "TypedownInput" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_linear_gradient = vec2(0.f, 25.f);
		})
		.decline({ FOCUSED }, [&](InkStyle& i) {
            i.m_background_colour = grey600;
		});

        select({ "Button", "Toggle", "DockToggle", "ToolButton", "RadioChoice", "Dropdown", "DropdownInput", "TabHeader" })
		.decline({ PRESSED, SELECTED, ACTIVE, PRESSED|ACTIVE }, [&](InkStyle& i) {
			i.m_linear_gradient = vec2(-15.f, 15.f);
		});

        select({ "Toggle", "DockToggle", "ToolButton", "RadioChoice", "TabHeader" })
		.decline({ ACTIVE, ACTIVE|HOVERED, PRESSED|HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = activeBlue;
        })
		.decline({ ACTIVE }, [&](InkStyle& i) {
			i.m_text_colour = black;
		});
		
        select({ "TabberEdge" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = activeBlue;
		});

        select({ "DropdownChoice", "Menu", "MenuChoice" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_text_colour = white;
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = activeBlue;
			i.m_linear_gradient = vec2(-15.f, 15.f);
            i.m_text_colour = black;
		});

        select({ "TabHeader" })
		.style([&](InkStyle& i) {
			i.m_border_width = vec4(0.f);
			i.m_corner_radius = vec4(4.f, 4.f, 0.f, 0.f);
		});

        select({ "MultiButton", "ExpandboxHeader", "TreeNodeHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			blendish_text(l, i);
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_border_colour = alphaGrey;
			i.m_border_width = vec4(2.f);
		})
		.decline({ SELECTED }, [&](InkStyle& i) {
			i.m_background_colour = alphaGrey;
		});

        select({ "Checkbox" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_size = vec2(16.f);
		})
		.decline({ ACTIVE, ACTIVE|HOVERED }, [&](InkStyle& i) {
			i.m_overlay = ui_window.find_image("blendish_check");
			i.m_padding = vec4(2.f, 2.f, 0.f, 0.f);
		});

        select({ "RadioSwitch", "ColourSlab", "ColourDisplay", "ColourToggle" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_corner_radius = vec4(4.f);
		});

        select({ "RadioChoice" })
		.style([&](InkStyle& i) {
			i.m_weak_corners = true;
		});

        select({ "Slider" })
		.style([&](InkStyle& i) {
			i.m_corner_radius = vec4(10.f);
		});

        select({ "SliderKnob" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_flow = LayoutFlow::Overlay;
		});

        select({ "Filler" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = Colour(0.447f);
			i.m_linear_gradient = vec2(15.f, -5.f);
			i.m_weak_corners = true;
		});

        select({ "Menubar", "WindowHeader", "WindowHeaderMovable", "WindowFooter", "NodeBody", "NodeHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			l.m_padding = vec4(4.f, 2.f, 4.f, 2.f);
			i.m_weak_corners = true;
		});

        select({ "Tab" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_corner_radius = vec4(0.f, 0.f, 4.f, 4.f);
		});

        select({ "DockWindow" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_corner_radius = vec4(3.f);
		});

        select({ "Window", "Node", "Popup", "ColourPopup" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = black;
			i.m_corner_radius = vec4(10.f);
			i.m_shadow = Shadow(2.f, 2.f, 7.f, 2.f);
		})
		.decline({ SELECTED }, [&](InkStyle& i) {
			i.m_shadow = Shadow(0.f, 0.f, 0.f, 1.f, grey600);
        });
		
		select({ "NodePlugs" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(-5.f, 0.f, -5.f, 0.f);
		});

        select({ "WindowBody" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(10.f, 4.f, 4.f, 4.f);
		});
		
		select({ "TreeNodeBody" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(12, 0, 0, 0);
		});

		select({ "ExpandboxBody" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(12, 6, 8, 6);
		});

        select({ "WindowSizerLeft", "WindowSizerRight" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_size = vec2(0.f, 8.f);
		});

        select({ "CloseButton" })
		.style([&](InkStyle& i) {
			i.m_border_width = vec4(0.f);
			i.m_padding = vec4(2.f);
		});

        select({ "Scroller", "ScrollerKnob" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_corner_radius = vec4(6.f);
		});

        select({ "Scroller" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = Colour(0.314f, 0.706f);
			i.m_linear_gradient = vec2(-15.f, 15.f);
		});

        select({ "ScrollerKnob" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = Colour(0.502f);
			i.m_linear_gradient = vec2(5.f, -5.f);
		})
		.decline({ HOVERED, PRESSED }, [&](InkStyle& i) {
			i.m_background_colour = Colour(0.542f);
        });

        select({ "DropdownToggle" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_image = ui_window.find_image("blendish_updown");
		});

        select({ "ExpandboxToggle", "TreeNodeToggle" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_image = ui_window.find_image("arrow_right_15");
		})
		.decline({ ACTIVE }, [&](InkStyle& i) {
			i.m_image = ui_window.find_image("arrow_down_15");
		})
		.decline({ DISABLED }, [&](InkStyle& i) {
			i.m_image = ui_window.find_image("empty_15");
		});

        select({ "Tooltip", "DropdownList", "MenuList", "SubMenuList", "Popup", "ColourPopup" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = greyOverlay;
			i.m_text_colour = Colour(0.627f);
		});

        select({ "Menubar" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(8.f, 2.f, 8.f, 2.f);
		});

        select({ "Toolbar", "Tab", "Header", "Scrollbar", "Popup", "ColourPopup" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(6.f);
		});

        select({ "Dockbar", "Toolbar", "Menubar", "Header" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_spacing = vec2(6.f);
		});

		ui::scrollbar_styles().scroll_up.m_skin.m_image = ui_window.find_image("arrow_up_15");
		ui::scrollbar_styles().scroll_down.m_skin.m_image = ui_window.find_image("arrow_down_15");
		ui::scrollbar_styles().scroll_left.m_skin.m_image = ui_window.find_image("arrow_left_15");
		ui::scrollbar_styles().scroll_right.m_skin.m_image = ui_window.find_image("arrow_right_15");
		
        select({ "CloseButton" })
		.style([&](InkStyle& i) {
			i.m_image = ui_window.find_image("close_15");
		});
		
        select({ "Canvas"})
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = black;
		});

		//ui::toolbar_styles().mover.m_skin.m_image = ui_window.find_image("handle");

		//ui::treenode_styles().no_toggle.m_skin.m_image = ui_window.find_image("empty_15");

		//ui::treenode_styles().toggle.m_skin.m_image = ui_window.find_image("toggle_closed");
		//ui::treenode_styles().toggle.decline_skin(ACTIVE).m_image = ui_window.find_image("toggle_open");
		//ui::treenode_styles().toggle.decline_skin(DISABLED).m_image = ui_window.find_image("empty_15");
	}

	void style_blendish_light(UiWindow& ui_window)
	{
		style_blendish(ui_window);

		const Colour black = Colour(0.f);
		const Colour white = Colour(1.f);
		const Colour none = Colour(0.f, 0.f);
		const Colour grey600 = Colour(0.600f);
		const Colour grey447 = Colour(0.447f);
		const Colour grey407 = Colour(0.407f);
		const Colour grey367 = Colour(0.367f);
		const Colour grey275 = Colour(0.275f);
		const Colour grey146 = Colour(0.146f);

        select({ "Label", "Text", "Title", "SliderDisplay", "ExpandboxHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_text_colour = black;
			i.m_padding = vec4(4.f);
		});

        select({ "Tab" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = grey407;
			i.m_border_colour = grey275;
		});

        select({ "Window", "DockWindow", "Expandbox", "Tree", "Header", "Popup", "ColourPopup" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = grey447;
		});

        select({ "Title", "WindowHeader", "WindowHeaderMovable" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_text_colour = white;
		});

        select({ "WindowFooter" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = grey600;
		});
		
        select({ "ColumnHeader", "Popup", "ColourPopup" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_border_colour = grey275;
			i.m_border_width = vec4(1.f);
		});

		//select({ "CloseButton" });

        select({ "Expandbox" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_linear_gradient = vec2(5.f, 0.f);
		});

		select({ "TableRowOdd" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = grey447; // grey117;
		});

		select({ "TableRowEven" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = none;
		});

		for(auto name_style : g_styles)
			name_style.second->prepare();
	}

	void style_blendish_dark(UiWindow& ui_window)
	{
		style_blendish(ui_window);

		const Colour black = Colour(0.f);
		const Colour grey275 = Colour(0.275f);
		const Colour grey090 = Colour(0.090f);

        select({ "Tab", "DockWindow" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = grey090;
		});

        select({ "Window", "Node", "Tab", "List", "ColumnHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_border_colour = grey275;
			i.m_border_width = vec4(1.f);
		});

        select({ "Window", "Node" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = black;
		});

		select({ "TableRowOdd" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = Colour(0.1f);
		});

		select({ "TableRowEven" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = Colour(0.f);
		});

		for(auto name_style : g_styles)
			name_style.second->prepare();
	}
}

#ifdef TWO_MODULES
module two.ui;
#else
#include <stl/hash_base.hpp>
#endif

#include <cstdio>

namespace two
{
	void layout_imgui(UiWindow& ui_window, const ImguiLook& look)
	{
		UNUSED(ui_window);

		select({ "Button", "Toggle", "ToolButton", "TabHeader", "DockToggle", "RadioChoiceItem", "TypeIn", "Input<string>" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_padding = vec4(look.FramePadding, look.FramePadding);
		});
		
		select({ "DropdownHead", "DropdownChoice", "MenuChoice" }) // "DropdownInput", "DropdownInputCompact", "TypedownInput", 
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			l.m_padding = vec4(look.FramePadding, look.FramePadding);
		});

		select({ "Header", "ExpandboxHeader", "WindowHeader", "WindowHeaderMovable", "Scrollbar", "NodePlug" }) // , "Menu"
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(look.FramePadding, look.FramePadding);
		});
		
		select({ "Slider" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(look.FramePadding - 1.f, look.FramePadding - 1.f);
		});

		select({ "Menubar" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(look.FramePadding.x, 0.f, look.FramePadding.x, 0.f);
		});

		select({ "TreeNodeBody", "IndentBlock" }) // , "ExpandboxBody"
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(look.IndentSpacing, look.FramePadding.y, look.FramePadding);
		});

		select({ "Row", "ExpandboxHeader", "TreeNodeHeader", "WrapButton", "MultiButton" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_spacing = vec2(look.ItemSpacing.x, 0.f);
		});
		
		select({ "ExpandboxBody", "TreeNodeBody", "WindowBody", "Table", "Tab", "Dockbar", "Toolbar", "Header", "TabberHead", "ScrollSurface", "IndentBlock" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_spacing = vec2(look.ItemSpacing);
		});
		
		select({ "TabberHead", "NumberInput" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_spacing.x = look.ItemInnerSpacing.x;
		});

		select({ "ExpandboxBody", "Dockbar", "Toolbar", "Header", "Tab" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			//l.m_padding = vec4(look.ItemSpacing, look.ItemSpacing);
			l.m_padding = vec4(look.FramePadding, look.FramePadding);
		});
		
		select({ "Header", "Modal", "Popup", "ColourPopup", "Tooltip", "Popdown", "DropdownList", "MenuList", "SubMenuList", "ScrollSurface" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(look.WindowPadding, look.WindowPadding);
		});

		select({ "DropdownList", "MenuList", "SubMenuList" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			const vec2 padding = vec2(look.FramePadding.x, look.WindowPadding.y);
			l.m_padding = vec4(padding, padding);
		});
		
		select({ "NodePlugs" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(-5.f - look.FramePadding.x, 0.f, -5.f - look.FramePadding.x, 0.f);
		});
	}

	void style_imgui(UiWindow& ui_window, const ImguiLook& look, const ImguiColours& style)
	{
		//layout_minimal(ui_window);
		layout_imgui(ui_window, look);

		const Colour none = Colour(0.f, 0.f);

		// Render an arrow aimed to be aligned with text (offset is a position in the same space text would be positioned). To e.g. denote expanded/collapsed state
		static auto render_arrow = [](Vg& vg, vec2 offset, SignedAxis dir, float fontsize, float scale, Colour colour)
		{
			const float h = fontsize * 1.00f;
			float r = h * 0.40f * scale;
			vec2 center = offset + vec2(h * 0.50f, h * 0.50f * scale);

			vec2 a, b, c;
			switch(dir)
			{
			case SignedAxis::PlusY:
			case SignedAxis::MinusY:
				if(dir == SignedAxis::PlusY) r = -r;
				a = vec2(+0.000f, +0.750f) * r;
				b = vec2(-0.866f, -0.750f) * r;
				c = vec2(+0.866f, -0.750f) * r;
				break;
			case SignedAxis::PlusX:
			case SignedAxis::MinusX:
				if(dir == SignedAxis::MinusX) r = -r;
				a = vec2(+0.750f, +0.000f) * r;
				b = vec2(-0.750f, +0.866f) * r;
				c = vec2(-0.750f, -0.866f) * r;
				break;
			default:
				break;
			}

			vg.begin_path();
			vg.move_to(center + a);
			vg.line_to(center + b);
			vg.line_to(center + c);
			vg.close_path();
			vg.fill(Paint(colour));
		};

		static auto render_bullet = [](Vg& vg, vec2 pos, float fontsize, Colour colour)
		{
			vg.path_circle(pos, fontsize * 0.20f);
			vg.fill(Paint(colour));
		};

		static auto render_checkmark = [](Vg& vg, vec2 pos, Colour colour, float sz)
		{
			float thickness = max(sz / 5.0f, 1.0f);
			sz -= thickness * 0.5f;
			pos += vec2(thickness * 0.25f);

			float third = sz / 3.0f;
			float bx = pos.x + third;
			float by = pos.y + sz - third * 0.5f;

			vg.begin_path();
			vg.move_to(vec2(bx - third, by - third));
			//vg.line_to(vec2(bx - third, by - third));
			vg.line_to(vec2(bx, by));
			vg.line_to(vec2(bx + third * 2, by - third * 2));
			vg.stroke(Paint(colour, thickness));
		};
		
		select({ "Label", "Text", "Title", "Message", "Control", "Tooltip", "TextEdit", "TypeLabel", "TypeZone", "SliderDisplay", "RadioChoiceItem",
				 "Element", "Button", "WrapButton", "MultiButton", "Toggle", "ToolButton", "TabHeader", "DockToggle", "RadioChoice", "DropdownChoice", "SliderKnob", "ScrollerKnob", "DragHandle", "DropdownInput", "DropdownInputCompact", "TypedownInput", "Menu", "TypeIn", "Input<string>", "TreeNodeHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_text_colour = style.Text;
		})
		.decline({ DISABLED }, [&](InkStyle& i) {
			i.m_text_colour = style.TextDisabled;
		});
		
		select({ "Separator" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = style.Separator;
		});

		select({ "Element", "Button", "WrapButton", "MultiButton", "Toggle", "ToolButton", "DockToggle", "RadioChoice", "DropdownChoice", "SliderKnob", "ScrollerKnob", "DragHandle", "DropdownInput", "DropdownInputCompact", "TypedownInput", "Menu", "TypeIn", "Input<string>" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_border_width = vec4(look.FrameBorderSize);
			i.m_corner_radius = vec4(look.FrameRounding);
		});
		
		//"Menu",
		select({ "Element", "Button", "WrapButton", "MultiButton", "Toggle", "ToolButton", "DockToggle", "SliderKnob", "DragHandle", "DropdownToggle" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = style.Button;
			i.m_border_colour = style.Border;
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = style.ButtonHovered;
		})
		.decline({ ACTIVE, SELECTED, PRESSED, FOCUSED, ACTIVE|HOVERED, PRESSED|HOVERED, ACTIVE|PRESSED }, [&](InkStyle& i) {
			i.m_background_colour = style.ButtonActive;
		});
		
		select({ "Checkbox", "TypeIn", "Input<string>", "Slider", "Fillbar", "DropdownInput", "DropdownInputCompact", "TypedownInput" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = style.FrameBg;
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = style.FrameBgHovered;
		});

		select({ "ExpandboxHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = style.Header;
			i.m_border_colour = style.Border;
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = style.HeaderHovered;
		})
		.decline({ ACTIVE, SELECTED, PRESSED, FOCUSED, ACTIVE|HOVERED, PRESSED|HOVERED, ACTIVE|PRESSED }, [&](InkStyle& i) {
			i.m_background_colour = style.HeaderActive;
		});

		select({ "TreeNodeHeader", "RadioChoice", "DropdownChoice", "Menu", "MenuChoice" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l); UNUSED(i);
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = style.HeaderHovered;
		})
		.decline({ ACTIVE, SELECTED, PRESSED, FOCUSED, ACTIVE|HOVERED, PRESSED|HOVERED, ACTIVE|PRESSED }, [&](InkStyle& i) {
			i.m_background_colour = style.Header;
		});

		select({ "TabberEdge" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = style.TabActive;
			l.m_size = vec2(2.f);
		});

		select({ "TabHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = style.Tab;
			i.m_border_colour = style.Border;
			i.m_corner_radius = vec4(look.TabRounding, look.TabRounding, 0.f, 0.f);
			i.m_border_width = vec4(look.TabBorderSize);
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = style.TabHovered;
		})
		.decline({ ACTIVE, SELECTED, PRESSED, FOCUSED, ACTIVE|HOVERED, PRESSED|HOVERED, ACTIVE|PRESSED }, [&](InkStyle& i) {
			i.m_background_colour = style.TabActive;
		});

		Style& dropdown_toggle = ui::dropdown_styles().toggle;

		dropdown_toggle.m_layout.m_size = vec2(13.f + 6.f);
		dropdown_toggle.m_skin.m_custom_draw = [](const Frame& frame, const vec4& rect, Vg& vg)
		{
			draw_frame(vg, frame, rect);
			render_arrow(vg, rect.pos + vec2(3.f), SignedAxis::MinusY, 13.f, 1.f, Colour(1.f));
		};
		
		for(Subskin& subskin : dropdown_toggle.m_skins)
		{
			subskin.skin.m_custom_draw = [](const Frame& frame, const vec4& rect, Vg& vg)
			{
				draw_frame(vg, frame, rect);
				render_arrow(vg, rect.pos + vec2(3.f), SignedAxis::MinusY, 13.f, 1.f, Colour(1.f));
			};
		}

		Style& treenode_header = ui::treenode_styles().header;

		select({ "ExpandboxToggle" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_custom_draw = [](const Frame& frame, const vec4& rect, Vg& vg) { render_arrow(vg, rect.pos, SignedAxis::PlusX, 13.f, 1.f, Colour(1.f)); };
			l.m_size = vec2(13.f);
		})
		.decline({ ACTIVE }, [&](InkStyle& i) {
			i.m_custom_draw = [](const Frame& frame, const vec4& rect, Vg& vg) { render_arrow(vg, rect.pos, SignedAxis::MinusY, 13.f, 1.f, Colour(1.f)); };
		})
		.decline({ DISABLED }, [&](InkStyle& i) {
			i.m_custom_draw = [](const Frame& frame, const vec4& rect, Vg& vg) {};
		});
		
		select({ "TreeNodeNoToggle" })
		.declare([&](Layout& l, InkStyle& i) {
			l.m_size = vec2(13.f) * 0.7f;
		});

		select({ "TreeNodeToggle" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_custom_draw = [](const Frame& frame, const vec4& rect, Vg& vg) { render_arrow(vg, rect.pos, SignedAxis::PlusX, 13.f, 0.7f, Colour(1.f)); };
			l.m_size = vec2(13.f) * 0.7f;
		})
		.decline({ ACTIVE }, [&](InkStyle& i) {
			i.m_custom_draw = [](const Frame& frame, const vec4& rect, Vg& vg) { render_arrow(vg, rect.pos, SignedAxis::MinusY, 13.f, 0.7f, Colour(1.f)); };
		})
		.decline({ DISABLED }, [&](InkStyle& i) {
			i.m_custom_draw = [](const Frame& frame, const vec4& rect, Vg& vg) {};
		});
#if 0
		select({ "Element", "TreeNodeHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = grey86;
		});

#endif
		
		select({ "SliderKnob" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = style.SliderGrab;
		})
		.decline({ ACTIVE, SELECTED, PRESSED, FOCUSED, ACTIVE|HOVERED, PRESSED|HOVERED, ACTIVE|PRESSED }, [&](InkStyle& i) {
			i.m_background_colour = style.SliderGrabActive;
		});
		
		select({ "SliderKnob" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_size = vec2(8, 15);
		});

		select({ "Scrollbar" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = style.ScrollbarBg;
		});

		select({ "ScrollerKnob" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			//i = styles().button.m_skin;
			i.m_background_colour = style.ScrollbarGrab;
			i.m_corner_radius = vec4(look.ScrollbarRounding);
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = style.ScrollbarGrabHovered;
		})
		.decline({ ACTIVE, SELECTED, PRESSED, FOCUSED, ACTIVE|HOVERED, PRESSED|HOVERED, ACTIVE|PRESSED }, [&](InkStyle& i) {
			i.m_background_colour = style.ScrollbarGrabActive;
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
		
		select({  "Checkbox" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			l.m_size = vec2(13.f + 6.f);
		});
		
		static Colour Checkmark = style.CheckMark;
		select({  "Checkmark" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_custom_draw = [](const Frame& frame, const vec4& rect, Vg& vg) { render_checkmark(vg, rect.pos + vec2(3.f), Checkmark, 13.f); };
		});
		
		select({ "Menubar" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = style.MenuBarBg;
		});

		select({ "Popup", "Modal" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = style.PopupBg;
		});
		
		select({  "Tooltip", "Popdown", "DropdownList", "MenuList", "SubMenuList"  })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			//i.m_background_colour = style.PopupBg;
			i.m_background_colour = style.WindowBg;
			i.m_border_colour = style.Border;
			i.m_border_width = vec4(1.f);
		});


		select({ "Window", "DockWindow", "Dockbox", "Node", "Section", "Popup", "Modal", "ColourPopup" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			//i.m_background_colour = grey52;
			i.m_border_colour = style.Border;
			i.m_border_width = vec4(1.f);
		});

		select({ "Window", "DockWindow", "Dockbox", "Node", "ColourPopup", "Header", "Tab" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = style.WindowBg;
		});

		select({ "Window", "Dockbox", "Node" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_corner_radius = vec4(look.WindowRounding);
		});
		
		select({ "WindowHeader", "WindowHeaderMovable" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_corner_radius = vec4(look.WindowRounding, look.WindowRounding, 0.f, 0.f);
		});
		
		select({ "WindowHeader", "WindowHeaderMovable", "NodeHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = style.TitleBg;
		})
		.decline({ ACTIVE, FOCUSED }, [&](InkStyle& i) {
			i.m_background_colour = style.TitleBgActive;
		});

		
		select({  "WindowSizer", "WindowSizerLeft", "WindowSizerRight" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = style.ResizeGrip;
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = style.ResizeGripHovered;
		})
		.decline({ ACTIVE, SELECTED, PRESSED, FOCUSED, ACTIVE|HOVERED, PRESSED|HOVERED, ACTIVE|PRESSED }, [&](InkStyle& i) {
			i.m_background_colour = style.ResizeGripActive;
		});

		select({ "WindowSizerRight" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_align = { Align::Right, Align::Right };
		});
		
		select({ "ColumnHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = style.FrameBg;
		});

		select({ "TableRowOdd" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = none;
		});

		select({ "TableRowEven" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = style.FrameBg;
		});
#if 0
		select({ "Canvas" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = black;
		});
#endif

		for(auto name_style : g_styles)
		{
			Style& s = *name_style.second;

			s.m_skin.m_text_font = "proggy";
			s.m_skin.m_text_size = 13.f;
			s.m_skin.m_text_colour = style.Text;

			for(Subskin& subskin : s.m_skins)
			{
				subskin.skin.m_text_font = "proggy";
				subskin.skin.m_text_size = 13.f;
				s.m_skin.m_text_colour = style.Text;
			}

			s.prepare();
		}
	}

	void style_imgui_dark(UiWindow& ui_window)
	{
		ImguiLook look;
		ImguiColours dark;

		dark.Text = Colour(1.00f, 1.00f, 1.00f, 1.00f);
		dark.TextDisabled = Colour(0.50f, 0.50f, 0.50f, 1.00f);
		dark.WindowBg = Colour(0.06f, 0.06f, 0.06f, 0.94f);
		dark.ChildBg = Colour(0.00f, 0.00f, 0.00f, 0.00f);
		dark.PopupBg = Colour(0.08f, 0.08f, 0.08f, 0.94f);
		dark.Border = Colour(0.43f, 0.43f, 0.50f, 0.50f);
		dark.BorderShadow = Colour(0.00f, 0.00f, 0.00f, 0.00f);
		dark.FrameBg = Colour(0.16f, 0.29f, 0.48f, 0.54f);
		dark.FrameBgHovered = Colour(0.26f, 0.59f, 0.98f, 0.40f);
		dark.FrameBgActive = Colour(0.26f, 0.59f, 0.98f, 0.67f);
		dark.TitleBg = Colour(0.04f, 0.04f, 0.04f, 1.00f);
		dark.TitleBgActive = Colour(0.16f, 0.29f, 0.48f, 1.00f);
		dark.TitleBgCollapsed = Colour(0.00f, 0.00f, 0.00f, 0.51f);
		dark.MenuBarBg = Colour(0.14f, 0.14f, 0.14f, 1.00f);
		dark.ScrollbarBg = Colour(0.02f, 0.02f, 0.02f, 0.53f);
		dark.ScrollbarGrab = Colour(0.31f, 0.31f, 0.31f, 1.00f);
		dark.ScrollbarGrabHovered = Colour(0.41f, 0.41f, 0.41f, 1.00f);
		dark.ScrollbarGrabActive = Colour(0.51f, 0.51f, 0.51f, 1.00f);
		dark.CheckMark = Colour(0.26f, 0.59f, 0.98f, 1.00f);
		dark.SliderGrab = Colour(0.24f, 0.52f, 0.88f, 1.00f);
		dark.SliderGrabActive = Colour(0.26f, 0.59f, 0.98f, 1.00f);
		dark.Button = Colour(0.26f, 0.59f, 0.98f, 0.40f);
		dark.ButtonHovered = Colour(0.26f, 0.59f, 0.98f, 1.00f);
		dark.ButtonActive = Colour(0.06f, 0.53f, 0.98f, 1.00f);
		dark.Header = Colour(0.26f, 0.59f, 0.98f, 0.31f);
		dark.HeaderHovered = Colour(0.26f, 0.59f, 0.98f, 0.80f);
		dark.HeaderActive = Colour(0.26f, 0.59f, 0.98f, 1.00f);
		dark.Separator = dark.Border;
		dark.SeparatorHovered = Colour(0.10f, 0.40f, 0.75f, 0.78f);
		dark.SeparatorActive = Colour(0.10f, 0.40f, 0.75f, 1.00f);
		dark.ResizeGrip = Colour(0.26f, 0.59f, 0.98f, 0.25f);
		dark.ResizeGripHovered = Colour(0.26f, 0.59f, 0.98f, 0.67f);
		dark.ResizeGripActive = Colour(0.26f, 0.59f, 0.98f, 0.95f);
		dark.Tab = lerp(dark.Header, dark.TitleBgActive, 0.80f);
		dark.TabHovered = dark.HeaderHovered;
		dark.TabActive = lerp(dark.HeaderActive, dark.TitleBgActive, 0.60f);
		dark.TabUnfocused = lerp(dark.Tab, dark.TitleBg, 0.80f);
		dark.TabUnfocusedActive = lerp(dark.TabActive, dark.TitleBg, 0.40f);
		dark.PlotLines = Colour(0.61f, 0.61f, 0.61f, 1.00f);
		dark.PlotLinesHovered = Colour(1.00f, 0.43f, 0.35f, 1.00f);
		dark.PlotHistogram = Colour(0.90f, 0.70f, 0.00f, 1.00f);
		dark.PlotHistogramHovered = Colour(1.00f, 0.60f, 0.00f, 1.00f);
		dark.TextSelectedBg = Colour(0.26f, 0.59f, 0.98f, 0.35f);
		dark.DragDropTarget = Colour(1.00f, 1.00f, 0.00f, 0.90f);
		dark.NavHighlight = Colour(0.26f, 0.59f, 0.98f, 1.00f);
		dark.NavWindowingHighlight = Colour(1.00f, 1.00f, 1.00f, 0.70f);
		dark.NavWindowingDimBg = Colour(0.80f, 0.80f, 0.80f, 0.20f);
		dark.ModalWindowDimBg = Colour(0.80f, 0.80f, 0.80f, 0.35f);

		style_imgui(ui_window, look, dark);
	}

	void style_imgui_classic(UiWindow& ui_window)
	{
		ImguiLook look;
		ImguiColours classic;

		classic.Text = Colour(0.90f, 0.90f, 0.90f, 1.00f);
		classic.TextDisabled = Colour(0.60f, 0.60f, 0.60f, 1.00f);
		classic.WindowBg = Colour(0.00f, 0.00f, 0.00f, 0.70f);
		classic.ChildBg = Colour(0.00f, 0.00f, 0.00f, 0.00f);
		classic.PopupBg = Colour(0.11f, 0.11f, 0.14f, 0.92f);
		classic.Border = Colour(0.50f, 0.50f, 0.50f, 0.50f);
		classic.BorderShadow = Colour(0.00f, 0.00f, 0.00f, 0.00f);
		classic.FrameBg = Colour(0.43f, 0.43f, 0.43f, 0.39f);
		classic.FrameBgHovered = Colour(0.47f, 0.47f, 0.69f, 0.40f);
		classic.FrameBgActive = Colour(0.42f, 0.41f, 0.64f, 0.69f);
		classic.TitleBg = Colour(0.27f, 0.27f, 0.54f, 0.83f);
		classic.TitleBgActive = Colour(0.32f, 0.32f, 0.63f, 0.87f);
		classic.TitleBgCollapsed = Colour(0.40f, 0.40f, 0.80f, 0.20f);
		classic.MenuBarBg = Colour(0.40f, 0.40f, 0.55f, 0.80f);
		classic.ScrollbarBg = Colour(0.20f, 0.25f, 0.30f, 0.60f);
		classic.ScrollbarGrab = Colour(0.40f, 0.40f, 0.80f, 0.30f);
		classic.ScrollbarGrabHovered = Colour(0.40f, 0.40f, 0.80f, 0.40f);
		classic.ScrollbarGrabActive = Colour(0.41f, 0.39f, 0.80f, 0.60f);
		classic.CheckMark = Colour(0.90f, 0.90f, 0.90f, 0.50f);
		classic.SliderGrab = Colour(1.00f, 1.00f, 1.00f, 0.30f);
		classic.SliderGrabActive = Colour(0.41f, 0.39f, 0.80f, 0.60f);
		classic.Button = Colour(0.35f, 0.40f, 0.61f, 0.62f);
		classic.ButtonHovered = Colour(0.40f, 0.48f, 0.71f, 0.79f);
		classic.ButtonActive = Colour(0.46f, 0.54f, 0.80f, 1.00f);
		classic.Header = Colour(0.40f, 0.40f, 0.90f, 0.45f);
		classic.HeaderHovered = Colour(0.45f, 0.45f, 0.90f, 0.80f);
		classic.HeaderActive = Colour(0.53f, 0.53f, 0.87f, 0.80f);
		classic.Separator = Colour(0.50f, 0.50f, 0.50f, 1.00f);
		classic.SeparatorHovered = Colour(0.60f, 0.60f, 0.70f, 1.00f);
		classic.SeparatorActive = Colour(0.70f, 0.70f, 0.90f, 1.00f);
		classic.ResizeGrip = Colour(1.00f, 1.00f, 1.00f, 0.16f);
		classic.ResizeGripHovered = Colour(0.78f, 0.82f, 1.00f, 0.60f);
		classic.ResizeGripActive = Colour(0.78f, 0.82f, 1.00f, 0.90f);
		classic.Tab = lerp(classic.Header, classic.TitleBgActive, 0.80f);
		classic.TabHovered = classic.HeaderHovered;
		classic.TabActive = lerp(classic.HeaderActive, classic.TitleBgActive, 0.60f);
		classic.TabUnfocused = lerp(classic.Tab, classic.TitleBg, 0.80f);
		classic.TabUnfocusedActive = lerp(classic.TabActive, classic.TitleBg, 0.40f);
		classic.PlotLines = Colour(1.00f, 1.00f, 1.00f, 1.00f);
		classic.PlotLinesHovered = Colour(0.90f, 0.70f, 0.00f, 1.00f);
		classic.PlotHistogram = Colour(0.90f, 0.70f, 0.00f, 1.00f);
		classic.PlotHistogramHovered = Colour(1.00f, 0.60f, 0.00f, 1.00f);
		classic.TextSelectedBg = Colour(0.00f, 0.00f, 1.00f, 0.35f);
		classic.DragDropTarget = Colour(1.00f, 1.00f, 0.00f, 0.90f);
		classic.NavHighlight = classic.HeaderHovered;
		classic.NavWindowingHighlight = Colour(1.00f, 1.00f, 1.00f, 0.70f);
		classic.NavWindowingDimBg = Colour(0.80f, 0.80f, 0.80f, 0.20f);
		classic.ModalWindowDimBg = Colour(0.20f, 0.20f, 0.20f, 0.35f);

		style_imgui(ui_window, look, classic);
	}

	void style_imgui_light(UiWindow& ui_window)
	{
		ImguiLook look;
		ImguiColours light;

		// Those light colors are better suited with a thicker font than the default one + FrameBorder

		light.Text = Colour(0.00f, 0.00f, 0.00f, 1.00f);
		light.TextDisabled = Colour(0.60f, 0.60f, 0.60f, 1.00f);
		light.WindowBg = Colour(0.94f, 0.94f, 0.94f, 1.00f);
		light.ChildBg = Colour(0.00f, 0.00f, 0.00f, 0.00f);
		light.PopupBg = Colour(1.00f, 1.00f, 1.00f, 0.98f);
		light.Border = Colour(0.00f, 0.00f, 0.00f, 0.30f);
		light.BorderShadow = Colour(0.00f, 0.00f, 0.00f, 0.00f);
		light.FrameBg = Colour(1.00f, 1.00f, 1.00f, 1.00f);
		light.FrameBgHovered = Colour(0.26f, 0.59f, 0.98f, 0.40f);
		light.FrameBgActive = Colour(0.26f, 0.59f, 0.98f, 0.67f);
		light.TitleBg = Colour(0.96f, 0.96f, 0.96f, 1.00f);
		light.TitleBgActive = Colour(0.82f, 0.82f, 0.82f, 1.00f);
		light.TitleBgCollapsed = Colour(1.00f, 1.00f, 1.00f, 0.51f);
		light.MenuBarBg = Colour(0.86f, 0.86f, 0.86f, 1.00f);
		light.ScrollbarBg = Colour(0.98f, 0.98f, 0.98f, 0.53f);
		light.ScrollbarGrab = Colour(0.69f, 0.69f, 0.69f, 0.80f);
		light.ScrollbarGrabHovered = Colour(0.49f, 0.49f, 0.49f, 0.80f);
		light.ScrollbarGrabActive = Colour(0.49f, 0.49f, 0.49f, 1.00f);
		light.CheckMark = Colour(0.26f, 0.59f, 0.98f, 1.00f);
		light.SliderGrab = Colour(0.26f, 0.59f, 0.98f, 0.78f);
		light.SliderGrabActive = Colour(0.46f, 0.54f, 0.80f, 0.60f);
		light.Button = Colour(0.26f, 0.59f, 0.98f, 0.40f);
		light.ButtonHovered = Colour(0.26f, 0.59f, 0.98f, 1.00f);
		light.ButtonActive = Colour(0.06f, 0.53f, 0.98f, 1.00f);
		light.Header = Colour(0.26f, 0.59f, 0.98f, 0.31f);
		light.HeaderHovered = Colour(0.26f, 0.59f, 0.98f, 0.80f);
		light.HeaderActive = Colour(0.26f, 0.59f, 0.98f, 1.00f);
		light.Separator = Colour(0.39f, 0.39f, 0.39f, 1.00f);
		light.SeparatorHovered = Colour(0.14f, 0.44f, 0.80f, 0.78f);
		light.SeparatorActive = Colour(0.14f, 0.44f, 0.80f, 1.00f);
		light.ResizeGrip = Colour(0.80f, 0.80f, 0.80f, 0.56f);
		light.ResizeGripHovered = Colour(0.26f, 0.59f, 0.98f, 0.67f);
		light.ResizeGripActive = Colour(0.26f, 0.59f, 0.98f, 0.95f);
		light.Tab = lerp(light.Header, light.TitleBgActive, 0.90f);
		light.TabHovered = light.HeaderHovered;
		light.TabActive = lerp(light.HeaderActive, light.TitleBgActive, 0.60f);
		light.TabUnfocused = lerp(light.Tab, light.TitleBg, 0.80f);
		light.TabUnfocusedActive = lerp(light.TabActive, light.TitleBg, 0.40f);
		light.PlotLines = Colour(0.39f, 0.39f, 0.39f, 1.00f);
		light.PlotLinesHovered = Colour(1.00f, 0.43f, 0.35f, 1.00f);
		light.PlotHistogram = Colour(0.90f, 0.70f, 0.00f, 1.00f);
		light.PlotHistogramHovered = Colour(1.00f, 0.45f, 0.00f, 1.00f);
		light.TextSelectedBg = Colour(0.26f, 0.59f, 0.98f, 0.35f);
		light.DragDropTarget = Colour(0.26f, 0.59f, 0.98f, 0.95f);
		light.NavHighlight = light.HeaderHovered;
		light.NavWindowingHighlight = Colour(0.70f, 0.70f, 0.70f, 0.70f);
		light.NavWindowingDimBg = Colour(0.20f, 0.20f, 0.20f, 0.20f);
		light.ModalWindowDimBg = Colour(0.20f, 0.20f, 0.20f, 0.35f);

		style_imgui(ui_window, look, light);
	}

	void style_imgui(UiWindow& ui_window, ImguiStyle style)
	{
		if(style == ImguiStyle::Dark)
			style_imgui_dark(ui_window);
		else if(style == ImguiStyle::Light)
			style_imgui_light(ui_window);
		else if(style == ImguiStyle::Classic)
			style_imgui_classic(ui_window);
	}
}

#ifdef TWO_MODULES
module two.ui;
#else
#include <stl/hash_base.hpp>
#endif

#include <cstdio>

namespace two
{
	StyleSelector& StyleSelector::declare(StyleDecl decl)
	{
		for(Style* style : styles)
			decl(style->m_layout, style->m_skin);
		return *this;
	}

	StyleSelector& StyleSelector::decline(span<uint32_t> states, InkDecl decl)
	{
		for(Style* style : styles)
			for(uint32_t state : states)
			{
				InkStyle& i = style->decline_skin(WidgetState(state));
				decl(i);
			}
		return *this;
	}

	StyleSelector& StyleSelector::style(InkDecl decl)
	{
		for(Style* style : styles)
		{
			decl(style->m_skin);
			for(Subskin& subskin : style->m_skins)
			{
				decl(subskin.skin);
			}
		}
		return *this;
	}

	StyleSelector select(span<string> styles)
	{
		StyleSelector selector;
		for(const string& name : styles)
			if(g_styles.find(name) != g_styles.end())
				selector.styles.push_back(g_styles[name]);
			else
				printf("[warning] ui - style %s not found\n", name.c_str());
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

		select({ "Dockspace", "Toolbar", "Header", "Popup", "ScrollSurface" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(6.f);
		});

		select({ "Menubar" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(6.f, 0.f, 6.f, 0.f);
		});

		select({ "Modal" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(12.f);
		});
		
		select({ "TreeNodeBody" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(12.f, 0.f, 0.f, 0.f);
		});

		select({ "ExpandboxBody" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(12.f, 6.f, 8.f, 6.f);
		});

		select({ "ExpandboxBody", "WindowBody" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_spacing = vec2(4.f);
		});

		select({ "Dockbar", "Toolbar", "Header" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_spacing = vec2(6.f);
		});
		
		select({ "NodePlugs" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(-5.f, 0.f, -5.f, 0.f);
		});
	}

	void style_minimal(UiWindow& ui_window, bool vector)
	{
		layout_minimal(ui_window);

		const Colour white = Colour(1.f);
		const Colour black = Colour(0.f);
		const Colour transparent = Colour(0.f, 0.f);
		const Colour clearGreyText = Colour(0.627f);
		const Colour grey600 = Colour(0.600f);
		const Colour grey400 = Colour(0.400f);
		const Colour grey312 = Colour(0.312f);
		const Colour grey248 = Colour(0.248f);
		const Colour grey204 = Colour(0.204f);
		const Colour grey176 = Colour(0.176f);
		const Colour grey145 = Colour(0.145f);
		const Colour grey117 = Colour(0.117f);
		const Colour grey86  = Colour(0.086f);
		const Colour grey69  = Colour(0.069f);
		const Colour grey52  = Colour(0.052f);
		const Colour activeBlue = Colour(0.145f, 0.5f, 1.f, 1.f);

		auto colour = [&](InkStyle& i, Colour colour)
		{
			if(vector)
				i.m_border_colour = colour;
			else
				i.m_background_colour = colour;
		};

		select({ "Label", "Text", "Title", "Message", "Control", "Tooltip", "TextEdit", "TypeLabel", "TypeZone", "SliderDisplay", "RadioChoiceItem" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_text_colour = white;
		})
		.decline({ DISABLED }, [&](InkStyle& i) {
			i.m_text_colour = grey248;
		});

		select({ "Element", "Button", "WrapButton", "MultiButton", "Toggle", "ToolButton", "TabHeader", "ColumnHeader", "DockToggle", "RadioChoice", "DropdownChoice", "MenuChoice", "SliderKnob", "ScrollerKnob", "DragHandle", "DropdownInput", "DropdownInputCompact", "TypedownInput", "Menu", "TypeIn", "Input<string>", "TreeNodeHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i = styles().label.m_skin;
			colour(i, grey204);
			if(vector)
				i.m_border_width = vec4(1.f);
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			colour(i, grey312);
		})
		.decline({ ACTIVE, SELECTED, PRESSED, FOCUSED, ACTIVE|HOVERED, PRESSED|HOVERED, ACTIVE|PRESSED }, [&](InkStyle& i) {
			i.m_background_colour = activeBlue;
		});

		select({ "CloseButton", "Checkbox" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i = styles().button.m_skin;
		});

		select({ "Element", "TreeNodeHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			colour(i, grey86);
		});

		select({ "SliderKnob", "ScrollerKnob" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i = styles().button.m_skin;
			colour(i, grey176);
		});

		select({ "SliderKnob" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			colour(i, grey312);
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

		select({ "ExpandboxToggle", "TreeNodeToggle" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_image = ui_window.find_image("toggle_closed");
		})
		.decline({ ACTIVE }, [&](InkStyle& i) {
			i.m_image = ui_window.find_image("toggle_open");
		})
		.decline({ DISABLED }, [&](InkStyle& i) {
			i.m_image = ui_window.find_image("empty_15");
		});

		select({ "DropdownToggle" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_image = ui_window.find_image("drop_down");
		});

		select({ "Checkbox" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			l.m_size = vec2(15.f);
			i.m_padding = vec4(1.f);
		})
		.decline({ ACTIVE }, [&](InkStyle& i) {
			i.m_image = ui_window.find_image("check_15");
		});

		select({ "Slider", "Fillbar", "TypeIn", "Input<string>"  })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			colour(i, grey145);
			if(!vector)
				i.m_border_colour = grey312;
			i.m_border_width = vec4(1.f);
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			colour(i, grey204);
			if(!vector)
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
			colour(i, grey248);
		});
		
		select({ "TabberEdge" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = activeBlue;
		});

		select({ "List", "Tree", "TabberHead", "TableHead", "Dockbar", "Header", "Menubar" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			colour(i, grey117);
		});

		select({ "Window", "WindowFooter", "DockWindow", "Dockbox", "Tab", "TextEdit", "Node", "Section", "Popup", "Modal", "ColourPopup" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = vector ? black : grey52;
			i.m_border_colour = grey204;
			i.m_border_width = vec4(1.f);
		});

		select({ "Window", "Dockbox", "Node", "Popup", "ColourPopup" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_shadow = { 2, 2, 7, 2 };
		})
		.decline({ SELECTED }, [&](InkStyle& i) {
			i.m_shadow = { 0, 0, 0, 1, grey600 };
		});

		select({ "WindowHeader", "WindowHeaderMovable", "NodeHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			colour(i, grey204);
			if(vector)
				i.m_border_width = vec4(1.f);
		});

		select({  "WindowSizer", "WindowSizerLeft", "WindowSizerRight"  })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_image = ui_window.find_image("handle_x");
			i.m_padding = vec4(2.f);
		});

		select({ "WindowSizerRight" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_align = { Align::Right, Align::Right };
		});

		select({ "Toolbar", "Tooldock"  })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			colour(i, grey145);
		});

		select({ "Canvas" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = black;
		});

		select({ "Tooltip", "Popdown", "DropdownList", "MenuList", "SubMenuList"  })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = Colour(0.098f, 0.802f);
			i.m_text_colour = clearGreyText;
		});

		select({ "DropdownChoice", "MenuChoice" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = transparent;
			i.m_border_colour = transparent;
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

		ui::window_styles().close_button.m_skin.m_image = ui_window.find_image("close_15");

		for(auto name_style : g_styles)
			name_style.second->prepare();
	}

	void style_minimal(UiWindow& ui_window)
	{
		style_minimal(ui_window, false);
	}

	void style_vector(UiWindow& ui_window)
	{
		style_minimal(ui_window, true);
	}
}


#ifdef TWO_MODULES
module two.ui;
#else
#include <stl/algorithm.h>
#endif

#include <cstdio>

namespace two
{
	template <> inline void to_string(const two::WidgetState& val, string& str)
	{
		if(val == NOSTATE) str = "NOSTATE";
		else if(val == CREATED) str = "CREATED";
		else if(val == HOVERED) str = "HOVERED";
		else if(val == PRESSED) str = "PRESSED";
		else if(val == ACTIVATED) str = "ACTIVATED";
		else if(val == ACTIVE) str = "ACTIVE";
		else if(val == SELECTED) str = "SELECTED";
		else if(val == DISABLED) str = "DISABLED";
		else if(val == DRAGGED) str = "DRAGGED";
		else if(val == FOCUSED) str = "FOCUSED";
		else if(val == CLOSED) str = "CLOSED";
	};

	ImageSkin::ImageSkin(Image& image, int left, int top, int right, int bottom, int margin, Axis stretch)
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

		m_min_size.x = d_stretch == Axis::X ? float(d_solid_size.x) : 0.f;
		m_min_size.y = d_stretch == Axis::Y ? float(d_solid_size.y) : 0.f;

		vec4 coords[Count] = {};
		this->stretch_coords(vec2(0.f), vec2(image.d_size), span<vec4>{ coords, Count });
		for(size_t s = 0; s < Count; ++s)
		{
			this->d_images[s].d_coord = this->d_image->d_coord + uvec2(coords[s].pos);
			this->d_images[s].d_size = uvec2(coords[s].size);
		}
	}

	ImageSkin::ImageSkin(Image& image, const ImageSkin& ref)
		: ImageSkin(image, ref.d_left, ref.d_top, ref.d_right, ref.d_bottom, ref.m_margin, ref.d_stretch)
	{}

	ImageSkin::ImageSkin()
		: d_image(nullptr)
	{}

	void ImageSkin::stretch_coords(vec2 offset, vec2 size, span<vec4> coords) const
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

	void register_styles(span<Style*> styles)
	{
		for(Style* style : styles)
			g_styles[style->m_name] = style;
	}

	Style::Style()
		: Style("Unnamed", nullptr, {})
	{}

	Style::Style(const string& name, Style* base, LayoutDef layout, InkStyleDef skin, StyleDef style)
		: m_base(base)
		, m_name(name)
		, m_layout(name)
		, m_skin(name)
	{
		if(m_base)
		{
			m_layout = m_base->m_layout;
			m_layout.m_name = name;
		}

		if(layout)
			layout(m_layout);
		if(skin)
			skin(m_skin);
		if(style)
			style(*this);
	}

	Style::~Style()
	{}

	void Style::prepare()
	{
		m_skin.prepare();
		for(Subskin& subskin : m_skins)
		{
			subskin.skin.prepare();
			subskin.skin.m_name = m_name + ":" + to_lower(flags_to_string<WidgetState, 9>(subskin.state));
		}
	}

	InkStyle& Style::state_skin(WidgetState state)
	{
		// turn off non-skinnable state flags
		state = static_cast<WidgetState>(state & ~(CREATED | ACTIVATED | CLOSED));
		for(Subskin& subskin : reverse_adapt(m_skins))
			if(state == subskin.state) // exact match
				return subskin.skin;
		for(Subskin& subskin : reverse_adapt(m_skins))
			if(state & subskin.state) // partial match
				return subskin.skin;
		return m_skin;
	}

	InkStyle& Style::decline_skin(WidgetState state, bool inherit)
	{
		for(Subskin& subskin : m_skins)
			if(state == subskin.state)
			{
				return subskin.skin;
			}

		Subskin& subskin = push(m_skins);
		subskin.state = state;
		subskin.skin = m_skin;
		subskin.skin.m_name = m_name + ":" + to_lower(flags_to_string<WidgetState, 9>(state));
		return subskin.skin;
	}
}


#ifdef TWO_MODULES
module two.ui;
#else
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
		checkmark = Style("Checkmark", screen, [](Layout& l) {});

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
