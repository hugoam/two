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
