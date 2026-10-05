//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.ui;

namespace two
{
namespace ui
{
	void window_drag_logic(Widget& widget, Widget& window, WindowState state, Docksystem* docksystem, cstring name)
	{
		if(MouseEvent event = widget.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
		{
			window.enable_state(ACTIVE);
			//if(!window.m_dock) // crashes for some reason
			window.m_frame.layer().moveToTop();
		}

		if(MouseEvent event = widget.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
		{
			window.m_frame.layer().moveToTop();
			window.m_frame.layer().m_frame.m_opacity = Opacity::Hollow;

			if(bit(state, WindowState::Movable))
				window.m_frame.set_position(window.m_frame.m_position + event.m_delta);
		}

		if(MouseEvent event = widget.mouse_event(DeviceType::MouseLeft, EventType::DragEnded))
		{
			if(bit(state, WindowState::Dockable) && docksystem)
				docksystem->dock(name, event.m_pos);

			window.m_frame.layer().m_frame.m_opacity = Opacity::Opaque;
		}
	}

	void window_resize_logic(Widget& widget, Widget& window, bool left)
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

	Widget& window_header(NodeKey id, Widget& parent, Widget& window, WindowState state, Docksystem* docksystem, cstring title)
	{
		Style* style = bit(state, WindowState::Movable) ? &window_styles().header_movable : &window_styles().header;
		Widget& self = widget(id, parent, *style);
		self.set_state(ACTIVE, window.active());

		item(key(), self, styles().title, title);
		if(bit(state, WindowState::Closable))
			if(button(key(), self, window_styles().close_button).activated())
				window.set_open(false);

		tooltip(key(), self, "Drag me");

		window_drag_logic(self, window, state, docksystem, title);

		return self;
	}
	
	Widget& window_sizer(NodeKey id, Widget& parent, Style& style, Widget& window, bool left)
	{
		Widget& self = widget(id, parent, style);
		window_resize_logic(self, window, left);
		return self;
	}

	Widget& window_footer(NodeKey id, Widget& parent, Widget& window)
	{
		Widget& self = widget(id, parent, window_styles().footer);
		window_sizer(key(), self, window_styles().sizer_left, window, true);
		window_sizer(key(), self, window_styles().sizer_right, window, false);
		return self;
	}

	Window window(NodeKey id, Widget& parent, cstring title, WindowState state, Dock* dock, Docksystem* docksystem)
	{
		// a dockable window is a top node: it's the same window, with the same contents, wherever it's docked, or floating
		Widget& self = bit(state, WindowState::Dockable) ? parent.sub_top(id) : parent.sub(id);

		Style& style = dock ? window_styles().dock_window : window_styles().window;
		if(!self.m_frame.d_style)
			self.init(style);
		else if(self.m_frame.d_style != &style)
			self.m_frame.init(style); // a window docked or undocked changes style
		self.layer();

		if(self.once())
		{
			self.set_open(true);

			if(!dock)
				self.m_frame.set_size(vec2(480.f, 350.f));

			if(!dock)
				self.m_frame.set_position((self.m_parent->m_frame.m_size - self.m_frame.m_size) / 2.f);
		}

		Widget* header = bit(state, WindowState::Header) ? &window_header(key(), self, self, state, docksystem, title) : nullptr;
		Widget* menu = bit(state, WindowState::Menu) ? &menubar(key(), self) : nullptr;

		Widget& body = widget(key(), self, window_styles().body);

		if(!dock && bit(state, WindowState::Sizable))
			window_footer(key(), self, self);

		if(!dock && self.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
			self.m_frame.layer().moveToTop();

		return { self, header, menu, self.open() ? &body : nullptr };
	}
}
}
