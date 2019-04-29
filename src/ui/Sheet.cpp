//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ui;
#else
#include <stl/algorithm.h>
#include <ui/Sheet.h>
#include <ui/WidgetStruct.h>
#include <ui/UiRoot.h>
#include <ui/ContainerStruct.h>
#include <ui/ScrollSheet.h>
#include <ui/Cursor.h>
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
