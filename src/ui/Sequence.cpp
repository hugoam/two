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
	Sequence sequence(NodeKey id, Widget parent)
	{
		Widget self = widget(id, parent, styles().sequence);
		return { self, self };
	}

	Sequence scroll_sequence(NodeKey id, Widget parent)
	{
		Widget self = widget(id, parent, styles().sequence);
		return { self, scroll_sheet(key(), self).body };
	}

	bool multiselect_logic(Widget element, Ref object, vector<Ref>& selection)
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

	bool select_logic(Widget element, Ref object, Ref& selection)
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

	Widget element(NodeKey id, Widget parent, Ref object)
	{
		Widget self = widget(key(object.m_value, id), parent, styles().element);

		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
			parent.ui().m_drop = { parent.ui().find_control(event.m_target), object, DropState::Preview };

		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::DragEnded))
			parent.ui().m_drop = { parent.ui().find_control(event.m_target), object, DropState::Done };

		return self;
	}

	Widget element(NodeKey id, Widget parent, Ref object, vector<Ref>& selection)
	{
		Widget self = element(id, parent, object);
		multiselect_logic(self, object, selection);
		return self;
	}

	Widget sequence_element(Sequence& sequence, Ref object)
	{
		return element(key(), sequence.body, object, *sequence.selection);
	}
}
}
