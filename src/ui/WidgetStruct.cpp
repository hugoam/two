//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.ui;

namespace two
{
	template class Graph<Widget>;

	inline bool clip(const Frame& frame) { return frame.d_layout->m_clipping == Clip::Clip; }

	Frame* pinpoint(Frame& frame, vec2 pos, const FrameFilter& filter)
	{
		if (!frame.d_style || frame.hollow() || (clip(frame) && !frame.inside(pos)))
			return nullptr;

		if (frame.m_layer)
			for (Layer* layer : reverse_adapt(frame.m_layer->d_sublayers))
			{
				vec2 local = layer->m_frame.integrate_position(pos, frame);
				Frame* target = pinpoint(layer->m_frame, local, filter);
				if (target)
					return target;
			}

		// the last children are on top: the top nodes attached, then the descendants walked backward, keeping the children
		span<Widget*> attached = frame.d_widget.attached();
		for (size_t i = attached.size(); i-- > 0;)
		{
			vec2 local = attached[i]->m_frame.integrate_position(pos, frame);
			Frame* target = pinpoint(attached[i]->m_frame, local, filter);
			if (target)
				return target;
		}

		span<unique<Widget>> descendants = frame.d_widget.descendants();
		for (size_t i = descendants.size(); i-- > 0;)
		{
			if (!descendants[i] || descendants[i]->m_parent != &frame.d_widget)
				continue;
			Widget& widget = *descendants[i];

			vec2 local = widget.m_frame.integrate_position(pos, frame);
			Frame* target = pinpoint(widget.m_frame, local, filter);
			if (target)
				return target;
		}

		if (filter(frame) && frame.inside(pos))
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
	{}

	Widget::~Widget()
	{
		if(m_events)
			m_events->m_control_node = nullptr;
		if(this->modal())
			this->yield_modal();
		// the press goes back to the root, unless another widget took it over
		if(this->pressed())
			for(MouseButton& button : this->ui().m_mouse.m_buttons)
				if(button.m_pressed == this)
					button.m_pressed = &this->ui();
		this->clear();
	}

	void Widget::reparent(Widget* old)
	{
		// the frame follows the widget in its new parent, so do the layers, its own, or else the ones of its descendants
		Layer* old_layer = old ? &old->m_frame.layer() : nullptr;
		Layer* new_layer = m_parent ? &m_parent->m_frame.layer() : nullptr;

		auto relink = [&](Layer& layer)
		{
			if(layer.d_parentLayer)
				layer.d_parentLayer->removeLayer(layer);
			layer.d_parentLayer = new_layer;
			if(new_layer)
				new_layer->addLayer(layer);
		};

		if(m_frame.m_layer)
			relink(*m_frame.m_layer);
		else
			for(unique<Widget>& widget : this->descendants())
				if(widget && widget->m_frame.m_layer && widget->m_frame.m_layer->d_parentLayer == old_layer)
					relink(*widget->m_frame.m_layer);

		if(old)
			old->m_frame.mark_dirty(DIRTY_LAYOUT);
		m_frame.d_parent = m_parent ? &m_parent->m_frame : nullptr;
		++Frame::s_epoch;
		m_frame.mark_dirty(DIRTY_LAYOUT);
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
		Graph::clear();
	}

	void Widget::set_content(cstring content)
	{
		string str = content;
		if(!str.empty() && str.front() == '(' && str.back() == ')')
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

	//ControlNode* Widget::propagate_event(InputEvent& event)
	//{
	//	UNUSED(event);
	//	return m_parent;
	//}

	//KeyEvent Widget::key_event(Key code, EventType event_type, InputMod modifier)
	//{
	//	if(!m_events) return KeyEvent();
	//	KeyEvent* event = static_cast<KeyEvent*>(m_events->m_keyed_events[DeviceType::Keyboard][event_type][int(code)]);
	//	return event && fits_modifier(event->m_modifiers, modifier) ? *event : KeyEvent();
	//}
	//
	//MouseEvent Widget::mouse_event(DeviceType device, EventType event_type, InputMod modifier, bool consume)
	//{
	//	if(!m_events) return MouseEvent();
	//	MouseEvent* event = static_cast<MouseEvent*>(m_events->m_events[device][event_type]);
	//	if(event && fits_modifier(event->m_modifiers, modifier))
	//	{
	//		MouseEvent result = *event;;
	//		if(consume)
	//			event->consume(*this);
	//		return result;
	//	}
	//	return MouseEvent();
	//}
}
