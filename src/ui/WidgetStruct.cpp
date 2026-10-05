//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.ui;

namespace two
{
	template class PooledNode<Widget>;

	inline bool clip(const Frame& frame) { return frame.d_layout->m_clipping == Clip::Clip; }

	Widget* pinpoint(Widget& self, vec2 pos, const FrameFilter& filter)
	{
		Frame& frame = self.frame();
		if (!frame.d_style || frame.hollow() || (clip(frame) && !frame.inside(pos)))
			return nullptr;

		if (frame.m_layer)
			for (Layer* layer : reverse_adapt(frame.m_layer->d_sublayers))
			{
				vec2 local = layer->m_widget.integrate_position(pos, self);
				if (Widget* target = pinpoint(layer->m_widget, local, filter))
					return target;
			}

		// the last children are on top: the top nodes attached, then the descendants walked backward, keeping the children
		PooledGraph<Widget>& graph = *self.m_graph;
		span<uint32_t> attached = self.attached();
		for (size_t i = attached.size(); i-- > 0;)
		{
			Widget& widget = graph.node(attached[i]);
			vec2 local = widget.integrate_position(pos, self);
			if (Widget* target = pinpoint(widget, local, filter))
				return target;
		}

		span<uint32_t> descendants = self.descendants();
		for (size_t i = descendants.size(); i-- > 0;)
		{
			if (descendants[i] == PooledGraph<Widget>::none || graph.m_parent[descendants[i]] != self.m_index)
				continue;
			Widget& widget = graph.node(descendants[i]);

			vec2 local = widget.integrate_position(pos, self);
			if (Widget* target = pinpoint(widget, local, filter))
				return target;
		}

		if (filter(frame) && frame.inside(pos))
			return &self;
		return nullptr;
	}

	Widget::Widget(PooledGraph<Widget>& graph)
		: PooledNode(graph)
	{
		graph.m_root = this;
	}

	// the index of the widget isn't set yet: its parent is the one given
	Widget::Widget(Widget* parent)
		: PooledNode(parent)
	{
		parent->mark_dirty(DIRTY_LAYOUT);
	}

	Widget::~Widget()
	{
		if(m_events)
			m_events->m_control_node = nullptr;
		if(m_control.m_modal)
			this->set_modal(nullptr, 0);
		if(this->modal())
			this->yield_modal();
		// the press goes back to the root, unless another widget took it over
		if(this->pressed())
			for(MouseButton& button : this->ui().m_mouse.m_buttons)
				if(button.m_pressed == this)
					button.m_pressed = &this->ui();
		this->clear();
		// the nodes are destroyed before their index is freed: the parent is still known
		if(Widget* parent = this->parent())
			parent->mark_dirty(DIRTY_LAYOUT);
	}

	void Widget::reparent(Widget* old)
	{
		// the frame follows the widget in its new parent, so do the layers, its own, or else the ones of its descendants
		Layer* old_layer = old ? &old->draw_layer() : nullptr;
		Widget* parent = this->parent();
		Layer* new_layer = parent ? &parent->draw_layer() : nullptr;

		auto relink = [&](Layer& layer)
		{
			if(layer.d_parentLayer)
				layer.d_parentLayer->removeLayer(layer);
			layer.d_parentLayer = new_layer;
			if(new_layer)
				new_layer->addLayer(layer);
		};

		if(frame().m_layer)
			relink(*frame().m_layer);
		else
			for(uint32_t index : this->descendants())
				if(index != PooledGraph<Widget>::none)
				{
					Widget& widget = m_graph->node(index);
					if(widget.frame().m_layer && widget.frame().m_layer->d_parentLayer == old_layer)
						relink(*widget.frame().m_layer);
				}

		if(old)
			old->mark_dirty(DIRTY_LAYOUT);
		++Frame::s_epoch;
		this->mark_dirty(DIRTY_LAYOUT);
	}

	Widget& Widget::layer()
	{
		if(!frame().m_layer)
			frame().m_layer = oconstruct<Layer>(*this);
		return *this;
	}

	Ui& Widget::ui()
	{
		return static_cast<Ui&>(*m_graph);
	}

	Widget& Widget::parent_modal()
	{
		if(Widget* parent = this->parent())
			return parent->modal() ? *parent : parent->parent_modal();
		else
			return *this;
	}

	UiWindow& Widget::ui_window()
	{
		return this->ui().m_window;
	}

	void Widget::clear()
	{
		PooledNode::clear();
	}

	void Widget::set_content(cstring content)
	{
		string str = content;
		if(!str.empty() && str.front() == '(' && str.back() == ')')
		{
			string name = to_lower(str.substr(1, str.size() - 2));
			Image& icon = *this->ui_window().find_image(name.c_str());
			this->set_icon(&icon);
		}
		else
		{
			this->set_caption(content);
		}
	}

	// a modal widget knows the widget it took its modality from, its parent in the control tree, and yields it back to it:
	// its parents in the widget tree can change, e.g a top node detached from its parent
	void Widget::set_modal(Widget* widget, uint32_t device_filter)
	{
		if(m_control.m_modal)
		{
			Widget& modal = static_cast<Widget&>(*m_control.m_modal);
			modal.set_modal(nullptr, 0);
			modal.disable_state(FOCUSED);
			modal.m_control.m_parent = nullptr;
		}
		if(widget)
		{
			widget->enable_state(FOCUSED);
			widget->m_control.m_parent = this;
		}
		m_control.m_modal = widget;
		m_control.m_mask = device_filter;
	}

	void Widget::yield_modal()
	{
		Widget* parent = static_cast<Widget*>(m_control.m_parent);
		if(parent && parent->m_control.m_modal == this)
			parent->set_modal(nullptr, 0);
		else
			this->parent_modal().set_modal(nullptr, 0);
	}

	void Widget::toggle_state(WidgetState state)
	{
		m_state = static_cast<WidgetState>(m_state ^ state);
		this->update_state(m_state);
	}

	Widget* Widget::pinpoint(vec2 pos)
	{
		return this->pinpoint(pos, [](Frame& frame) { return frame.opaque(); });
	}

	Widget* Widget::pinpoint(vec2 pos, const FrameFilter& filter)
	{
		return two::pinpoint(*this, pos, filter);
	}

	void Widget::transform_event(InputEvent& event)
	{
		if(event.m_deviceType >= DeviceType::Mouse)
		{
			MouseEvent& mouse_event = static_cast<MouseEvent&>(event);
			mouse_event.m_relative = this->local_position(mouse_event.m_pos);
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
