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
			window.m_frame.layer().moveToTop();
			window.m_frame.layer().m_frame.m_opacity = Opacity::Hollow;

			if(window.movable())
				window.m_frame.set_position(window.m_frame.m_position + event.m_delta);
		}

		if(MouseEvent event = widget.mouse_event(DeviceType::MouseLeft, EventType::DragEnded))
		{
			if(window.dockable())
				window.m_docksystem->dock(window, event.m_pos);

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

	Widget& window_header(NodeKey id, Widget& parent, Window& window, cstring title)
	{
		Style* style = window.movable() ? &window_styles().header_movable : &window_styles().header;
		Widget& self = widget(id, parent, *style);
		self.set_state(ACTIVE, window.active());

		item(key(), self, styles().title, title);
		if(window.closable())
			if(button(key(), self, window_styles().close_button).activated())
				window.m_open = false;

		tooltip(key(), self, "Drag me");

		window_drag_logic(self, window);

		return self;
	}
	
	Widget& window_sizer(NodeKey id, Widget& parent, Style& style, Window& window, bool left)
	{
		Widget& self = widget(id, parent, style);
		window_resize_logic(self, window, left);
		return self;
	}

	Widget& window_footer(NodeKey id, Widget& parent, Window& window)
	{
		Widget& self = widget(id, parent, window_styles().footer);
		window_sizer(key(), self, window_styles().sizer_left, window, true);
		window_sizer(key(), self, window_styles().sizer_right, window, false);
		return self;
	}

	Window& window(NodeKey id, Widget& parent, cstring title, WindowState state, Dock* dock)
	{
		Window& self = parent.sub<Window>(id);
		self.m_dock = dock;
		self.m_name = title;
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
			self.m_header = &window_header(key(), self, self, title);

		if(self.hasmenu())
			self.m_menu = &menubar(key(), self);

		Widget& body = widget(key(), self, window_styles().body);

		if(!self.m_dock && self.sizable())
			window_footer(key(), self, self);

		if(!self.m_dock && self.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
			self.m_frame.layer().moveToTop();

		self.m_body = self.m_open ? &body : nullptr;

		return self;
	}
}
}
