//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ui;
#else
#include <infra/StringOps.h>
#include <infra/Reverse.h>
#include <tree/Graph.hpp>
#include <ctx/InputDevice.h>
#include <ui/WidgetStruct.h>
#include <ui/UiRoot.h>
#include <ui/Frame/Layer.h>
#include <ui/Style/Layout.h>
#include <ui/Style/Style.h>
#include <ui/UiWindow.h>
#endif

namespace mud
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
