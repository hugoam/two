//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <cstdarg>
#include <infra/Cpp20.h>
module two.ui;

namespace two
{
namespace ui
{
	Widget& spacer(NodeKey id, Widget& parent) { return widget(id, parent, styles().spacer); }
	Widget& separator(NodeKey id, Widget& parent) { return widget(id, parent, styles().separator); }

	Widget& icon(NodeKey id, Widget& parent, cstring icon) { return item(id, parent, styles().item, icon); }
	Widget& label(NodeKey id, Widget& parent, cstring label) { return item(id, parent, styles().label, label); }
	Widget& title(NodeKey id, Widget& parent, cstring label) { return item(id, parent, styles().title, label); }
	Widget& message(NodeKey id, Widget& parent, cstring label) { return item(id, parent, styles().message, label); }
	Widget& selectable(NodeKey id, Widget& parent, cstring label, bool& selected) { UNUSED(selected); return item(id, parent, styles().item, label); }

	Widget& text(NodeKey id, Widget& parent, cstring label)
	{
		Widget& self = item(id, parent, styles().text);

		// @todo optimize (doesn't need to be done on each call)
		Text& text = self.state<Text>();
		text.m_text = label;
		text.update_style(self);
		text.break_text_rows(self);

		return self;
	}

	Widget& bullet(NodeKey id, Widget& parent, cstring label)
	{
		Widget& self = row(id, parent);
		item(key(), self, styles().bullet);
		item(key(), self, styles().text, label);
		return self;
	}

	Widget& icon(NodeKey id, Widget& parent, const string& icon) { return item(id, parent, styles().item, icon); }
	Widget& label(NodeKey id, Widget& parent, const string& label) { return item(id, parent, styles().label, label); }
	Widget& title(NodeKey id, Widget& parent, const string& label) { return item(id, parent, styles().title, label); }
	Widget& message(NodeKey id, Widget& parent, const string& label) { return item(id, parent, styles().message, label); }
	Widget& selectable(NodeKey id, Widget& parent, const string& label, bool& selected) { UNUSED(selected); return item(id, parent, styles().item, label); }
	Widget& text(NodeKey id, Widget& parent, const string& label) { return text(id, parent, label.c_str()); }
	Widget& bullet(NodeKey id, Widget& parent, const string& label) { return bullet(id, parent, label.c_str()); }

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

	Widget& labelfv(NodeKey id, Widget& parent, const char* fmt, va_list args)
	{
		static char buffer[1024];
		int len = format(buffer, 1024, fmt, args);
		return label(id, parent, string(buffer, len));
	}

	Widget& labelf(NodeKey id, Widget& parent, const char* fmt, ...)
	{
		static char buffer[1024];
		va_list args;
		va_start(args, fmt);
		int len = format(buffer, 1024, fmt, args);
		va_end(args);
		return label(id, parent, string(buffer, len));
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
			event.consume(self.control_id());
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

	Widget& button(NodeKey id, Widget& parent, Style& style, cstring content)
	{
		Widget& self = item(id, parent, style, content);
		button_logic(self);
		return self;
	}

	Widget& multi_button(NodeKey id, Widget& parent, Style& style, span<cstring> elements, Style* element_style)
	{
		Widget& self = multi_item(id, parent, style, elements, element_style);
		button_logic(self);
		return self;
	}

	Widget& toggle(NodeKey id, Widget& parent, Style& style, bool& on, cstring content)
	{
		Widget& self = item(id, parent, style, content);
		toggle_logic(self, on);
		return self;
	}

	Widget& multi_toggle(NodeKey id, Widget& parent, Style& style, bool& on, span<cstring> elements, Style* element_style)
	{
		Widget& self = multi_item(id, parent, style, elements, element_style);
		toggle_logic(self, on);
		return self;
	}

	Widget& button(NodeKey id, Widget& parent, cstring content) { return button(id, parent, styles().button, content); }
	Widget& toggle(NodeKey id, Widget& parent, bool& on, cstring content) { return toggle(id, parent, styles().toggle, on, content); }

	Widget& button(NodeKey id, Widget& parent, const string& content) { return button(id, parent, styles().button, content.c_str()); }
	Widget& toggle(NodeKey id, Widget& parent, bool& on, const string& content) { return toggle(id, parent, styles().toggle, on, content.c_str()); }

	Widget& multi_button(NodeKey id, Widget& parent, span<cstring> elements, Style* element_style)
{
		return multi_button(id, parent, styles().multi_button, elements, element_style);
	}

	Widget& multi_toggle(NodeKey id, Widget& parent, bool& on, span<cstring> elements, Style* element_style)
	{
		return multi_toggle(id, parent, styles().multi_button, on, elements, element_style);
	}

	bool modal_button(NodeKey id, Widget& screen, Widget& parent, cstring content, uint32_t mode)
	{
		if(button(id, parent, content).activated())
			screen.data().m_switch |= mode;
		return (screen.data().m_switch & mode) != 0;
	}

	bool modal_multi_button(NodeKey id, Widget& screen, Widget& parent, span<cstring> elements, uint32_t mode)
	{
		if(multi_button(id, parent, elements).activated())
			screen.data().m_switch |= mode;
		return (screen.data().m_switch & mode) != 0;
	}

	Widget& checkbox(NodeKey id, Widget& parent, bool& on)
	{
		Widget& self = toggle(id, parent, styles().checkbox, on);
		if(on)
			item(key(1, id), parent, styles().checkmark);
		return self;
	}

	Widget& fill_bar(NodeKey id, Widget& parent, float percentage, Axis dim)
	{
		Widget& self = widget(id, parent, styles().fill_bar);
		spanner(key(), self, styles().filler, dim, percentage);
		spanner(key(), self, styles().spacer, dim, 1.f - percentage);
		item(key(), self, styles().slider_display, to_string(percentage) + "%");
		return self;
	}

	Widget& image256(NodeKey id, Widget& parent, Style& style, cstring name, const Image256& source)
	{
		Widget& self = widget(id, parent, style);
		Image* image = self.ui_window().find_image(name);
		if(!image)
		{
			vector<uint8_t> data = source.read();
			image = &self.ui_window().create_image(name, source.m_size, data, false);
		}
		self.set_icon(image);
		return self;
	}

	Widget& image256(NodeKey id, Widget& parent, cstring name, const Image256& source)
	{
		return image256(id, parent, styles().image, name, source);
	}

	Widget& image256(NodeKey id, Widget& parent, cstring name, const Image256& source, const vec2& size)
	{
		Widget& self = image256(id, parent, styles().image_stretch, name, source);
		//self.set_size(size);
		ui::dummy(key(), self, size);
		return self;
	}

	Widget& image256(NodeKey id, Widget& parent, const string& name, const Image256& source) { return image256(id, parent, name.c_str(), source); }
	Widget& image256(NodeKey id, Widget& parent, const string& name, const Image256& source, const vec2& size) { return image256(id, parent, name.c_str(), source, size); }

	Widget& radio_button(NodeKey id, Widget& parent, cstring label, uint32_t& value, uint32_t index)
	{
		Widget& self = multi_button(id, parent, styles().radio_choice, { label }, &styles().radio_choice_item);
		self.set_state(ACTIVE, value == index);
		if(self.activated())
			value = index;
		return self;
	}

	Widget& radio_choice(NodeKey id, Widget& parent, cstring label, bool active)
	{
		Widget& self = multi_button(id, parent, styles().radio_choice, { label }, &styles().radio_choice_item);
		self.set_state(ACTIVE, active);
		return self;
	}

	bool radio_switch(NodeKey id, Widget& parent, span<cstring> labels, uint32_t& value, Axis dim)
	{
		Widget& self = widget(id, parent, styles().radio_switch, false, dim);
		bool changed = false;
		for(uint32_t index = 0; index < uint32_t(labels.size()); ++index)
		{
			if(radio_choice(key(), self, labels[index], value == index).activated())
			{
				changed = true;
				value = index;
			}
		}
		return changed;
	}

	Dropdown dropdown(NodeKey id, Widget& parent, Style& style, cstring value, PopupFlags popup_flags, bool no_toggle, Style* list_style)
	{
		bool hovered = false;
		Widget& self = widget(id, parent, style);
		bool open = self.open();
		Widget& header = multi_toggle(key(), self, dropdown_styles().head, open, { value });
		hovered |= header.hovered();
		if(!no_toggle)
		{
			Widget& button = toggle(key(), self, dropdown_styles().toggle, open);
			hovered |= button.hovered();
		}

		self.set_state(HOVERED, hovered);
		Widget* body = nullptr;

		if(open)
		{
			body = &popup(key(), self, list_style ? *list_style : dropdown_styles().list, popup_flags);
			open &= body->open();
		}
		self.set_open(open);

		return { self, body };
	}

	Widget& dropdown_choice(NodeKey id, Widget& parent, span<cstring> elements, bool active)
	{
		Widget& self = multi_button(id, parent, dropdown_styles().choice, elements);
		self.set_state(ACTIVE, active);
		return self;
	}

	bool popdown(NodeKey id, Widget& parent, span<cstring> choices, uint32_t& value, vec2 position, PopupFlags popup_flags)
	{
		Widget& self = popup_at(id, parent, dropdown_styles().popdown, position, popup_flags);
		ScrollSheet sheet = scroll_sheet(key(), self);

		for(uint32_t i = 0; i < uint32_t(choices.size()); ++i)
			if(dropdown_choice(key(), sheet.body, { choices[i] }, i == value).activated())
			{
				value = i;
				return true;
			}
		return false;
	}

	bool dropdown_input(NodeKey id, Widget& parent, span<cstring> choices, uint32_t& value, bool compact)
	{
		if(value >= choices.size())
			value = uint32_t(choices.size()) - 1;
		Style& style = compact ? dropdown_styles().dropdown_input_compact : dropdown_styles().dropdown_input;
		Dropdown self = dropdown(id, parent, style, value == UINT32_MAX ? "" : choices[value], PopupFlags::AutoModal);
		if(!self.body) return false;

		for(uint32_t i = 0; i < uint32_t(choices.size()); ++i)
			if(dropdown_choice(key(), *self.body, { choices[i] }, value == i).activated())
			{
				value = i;
				self.self.set_open(false);
				return true;
			}

		return false;
	}

	bool typedown_input(NodeKey id, Widget& parent, span<cstring> choices, uint32_t& value)
	{
		bool changed = dropdown_input(id, parent, choices, value); //dropdown_styles().typedown_input
		//if(scope->m_state & ACTIVATED)
		//	filter_input(self);
		return changed;
	}

	Widget& menu_choice(NodeKey id, Widget& parent, span<cstring> elements)
	{
		Widget& self = multi_button(id, parent, menu_styles().choice, elements);
		if(self.activated())
			self.parent()->parent()->set_open(false);
		return self;
	}

	Widget& menu_choice(NodeKey id, Widget& parent, cstring content, cstring shortcut)
	{
		UNUSED(shortcut);
		return menu_choice(id, parent, span<cstring>{ content });
	}

	Widget& menu_option(NodeKey id, Widget& parent, cstring content, cstring shortcut, bool enabled)
	{
		UNUSED(shortcut); UNUSED(enabled);
		return menu_choice(id, parent, span<cstring>{ content });
	}

	Dropdown menu(NodeKey id, Widget& parent, cstring label, bool submenu)
	{
		Style& list_style = submenu ? menu_styles().sublist : menu_styles().list;
		return dropdown(id, parent, menu_styles().menu, label, submenu ? PopupFlags::None : PopupFlags::AutoModal, true, &list_style);
	}

	Widget& menubar(NodeKey id, Widget& parent)
	{
		return widget(id, parent, menu_styles().menubar);
	}

	Widget& toolbutton(NodeKey id, Widget& parent, cstring icon)
	{
		return button(id, parent, icon);
		//string value;
		//return dropdown_input(id, parent, styles().tool_button, {}, value);
	}

	Widget& tooldock(NodeKey id, Widget& parent)
	{
		return widget(id, parent, toolbar_styles().tooldock);//, GRID)
	}

	Widget& toolbar(NodeKey id, Widget& parent, bool wrap)
	{
		Widget& self = widget(id, parent, wrap ? toolbar_styles().toolbar_wrap : toolbar_styles().toolbar);
		widget(key(), self, toolbar_styles().mover);
		return self;
	}
}
}
