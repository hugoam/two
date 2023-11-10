//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
module two.ui;
#else
#include <tree/Graph.hpp>
#include <math/Vec.hpp>
#include <ui/Window.h>
#include <ui/Cursor.h>
#include <ui/Frame/Layer.h>
#include <ui/WindowStruct.h>
#include <ui/UiRoot.h>
#include <ui/Dock.h>
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
