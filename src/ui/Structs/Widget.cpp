//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <ui/Structs/Widget.h>

#include <obj/Graph/Node.inl.h>
#include <obj/String/String.h>

#include <obj/Iterable/Reverse.h>
#include <ui/Structs/RootSheet.h>
#include <ui/Frame/Layer.h>
#include <ui/Style/Layout.h>

#include <ui/Style/Styler.h>
#include <ui/UiWindow.h>

#include <ctx/InputDevice.h>

namespace mud
{
	inline bool flow(const Frame& frame) { return frame.d_style->layout().m_flow == FLOW; }
	inline bool clip(const Frame& frame) { return frame.d_style->layout().m_clipping == CLIP; }
	inline bool unclip(const Frame& frame) { return frame.d_style->layout().m_clipping == UNCLIP; }

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
		this->root_sheet().destroy(*this);
		if(this->modal())
			this->yield_modal();
		m_nodes.clear();
	}

	Widget& Widget::begin()
	{
		return begin_node(*this);
	}

	Widget& Widget::layer()
	{
		if(!m_frame.m_layer)
			m_frame.m_layer = make_object<Layer>(m_frame);
		return *this;
	}

	RootSheet& Widget::root_sheet()
	{
		return as<RootSheet>(this->root());
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
		return as<RootSheet>(this->root()).m_window;
	}

	VgRenderer& Widget::renderer()
	{
		return *as<RootSheet>(this->root()).m_window.m_renderer;
	}

	void Widget::setContent(cstring content)
	{
		string str = content;
		if(str.front() == '(' && str.back() == ')')
		{
			string name = to_lower(string(str.begin() + 1, str.end() - 1));
			Image& icon = this->ui_window().find_image(name.c_str());
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
			static_cast<Widget*>(m_control.m_modal)->disableState(FOCUSED);
			m_control.m_modal->m_control = {};
		}
		if(widget)
			widget->enableState(FOCUSED);
		m_control = { m_control.m_parent, widget, device_filter };
	}

	void Widget::toggleState(WidgetState state)
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

	void Widget::transformEvent(InputEvent& event)
	{
		if(event.m_deviceType >= DeviceType::Mouse)
		{
			MouseEvent& mouse_event = static_cast<MouseEvent&>(event);
			mouse_event.m_relative = m_frame.local_position(mouse_event.m_pos);
		}
	}

	ControlNode* Widget::controlEvent(InputEvent& event)
	{
		this->transformEvent(event);

		if((m_control.m_mask & device_mask(event.m_deviceType)) != 0)
			return m_control.m_modal->controlEvent(event);

		if(event.m_deviceType >= DeviceType::Mouse)
		{
			MouseEvent& mouse_event = static_cast<MouseEvent&>(event);
			Widget* pinned = this->pinpoint(mouse_event.m_relative);
			return (pinned && pinned != this) ? pinned->controlEvent(event) : this;
		}

		return this;
	}

	void Widget::receiveEvent(InputEvent& event)
	{
		if(event.m_consumer) return;
		this->transformEvent(event);
	}

	ControlNode* Widget::propagateEvent(InputEvent& event)
	{
		UNUSED(event);
		return m_parent;
	}

	KeyEvent Widget::key_event(KeyCode code, EventType event_type, InputModifier modifier)
	{
		if(!m_events) return KeyEvent();
		KeyEvent* event = static_cast<KeyEvent*>(m_events->event(DeviceType::Keyboard, event_type, int(code)));
		return event && fits_modifier(event->m_modifiers, modifier) ? *event : KeyEvent();
	}

	MouseEvent Widget::mouse_event(DeviceType device, EventType event_type, InputModifier modifier, bool consume)
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
