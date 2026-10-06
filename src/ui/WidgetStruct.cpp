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

		PooledGraph<Widget>& graph = *self.m_graph;
		if (Layer* layer = self.find_state<Layer>())
			for (uint32_t node : reverse_adapt(layer->d_sublayers))
			{
				Widget& widget = graph.node(node);
				vec2 local = widget.integrate_position(pos, self);
				if (Widget* target = pinpoint(widget, local, filter))
					return target;
			}

		// the last children are on top: the top nodes attached, then the descendants walked backward, keeping the children
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
	{}

	// the widget forgets the events it received, gives its modal control up, and the presses it holds back to the root, unless another widget took them over
	// its parent is laid out again without it: the nodes are released before any is destroyed, the parent is still known
	void Widget::release()
	{
		if(Widget* parent = this->parent())
			parent->mark_dirty(DIRTY_LAYOUT);

		this->release_layer();

		Ui& ui = this->ui();
		ui.forget(this->control_id());
		ModalControl* control = this->find_state<ModalControl>();
		if(control && control->m_modal)
			this->set_modal(nullptr, 0);
		if(this->modal())
			this->yield_modal();
		if(this->pressed())
			for(MouseButton& button : ui.m_mouse.m_buttons)
				if(button.m_pressed == this->control_id())
					button.m_pressed = ui.control_id();
	}

	void Widget::reparent(Widget* old)
	{
		// the frame follows the widget in its new parent, so do the layers, its own, or else the ones of its descendants
		Widget* old_layer = old ? &old->layer_widget() : nullptr;
		Widget* parent = this->parent();
		Widget* new_layer = parent ? &parent->layer_widget() : nullptr;

		auto relink = [&](Widget& widget, Layer& layer)
		{
			if(!layer.master() && m_graph->find_state<Layer>(layer.d_parent))
				m_graph->node(layer.d_parent).remove_sublayer(widget, layer);
			layer.d_parent = Layer::none;
			if(new_layer)
				new_layer->add_sublayer(widget, layer);
		};

		if(Layer* layer = this->find_state<Layer>())
			relink(*this, *layer);
		else
			for(uint32_t index : this->descendants())
				if(index != PooledGraph<Widget>::none)
				{
					Widget& widget = m_graph->node(index);
					Layer* layer = widget.find_state<Layer>();
					if(layer && layer->d_parent == (old_layer ? old_layer->m_index : Layer::none))
						relink(widget, *layer);
				}

		if(old)
			old->mark_dirty(DIRTY_LAYOUT);
		++FrameCache::s_epoch;
		this->mark_dirty(DIRTY_LAYOUT);
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
	// the modality is a state of the node, created when it's first set: a widget without one has no parent, no modal widget and no mask
	// a released widget has no states anymore, its modality isn't created again
	void Widget::set_modal(Widget* widget, uint32_t device_filter)
	{
		ModalControl* control = this->find_state<ModalControl>();
		if(control && control->m_modal)
		{
			Widget& modal = this->ui().control(control->m_modal);
			modal.set_modal(nullptr, 0);
			modal.disable_state(FOCUSED);
			if(ModalControl* modal_control = modal.find_state<ModalControl>())
				modal_control->m_parent = {};
		}
		if(widget)
		{
			widget->enable_state(FOCUSED);
			widget->state<ModalControl>().m_parent = this->control_id();
		}
		if(control || widget || device_filter != 0)
		{
			ModalControl& self = control ? *control : this->state<ModalControl>();
			self.m_modal = widget ? widget->control_id() : ControlId();
			self.m_mask = device_filter;
		}
	}

	void Widget::yield_modal()
	{
		ModalControl* control = this->find_state<ModalControl>();
		Widget* parent = control ? this->ui().find_control(control->m_parent) : nullptr;
		ModalControl* parent_control = parent ? parent->find_state<ModalControl>() : nullptr;
		if(parent_control && parent_control->m_modal == this->control_id())
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

	KeyEvent Widget::key_event(Key code, EventType event_type, InputMod modifier)
	{
		KeyEvent* event = static_cast<KeyEvent*>(this->ui().received(this->control_id(), DeviceType::Keyboard, event_type, int(code)));
		return event && fits_modifier(event->m_modifiers, modifier) ? *event : KeyEvent();
	}

	MouseEvent Widget::mouse_event(DeviceType device, EventType event_type, InputMod modifier, bool consume)
	{
		MouseEvent* event = static_cast<MouseEvent*>(this->ui().received(this->control_id(), device, event_type));
		if(event && fits_modifier(event->m_modifiers, modifier))
		{
			MouseEvent result = *event;
			if(consume)
				event->consume(this->control_id());
			return result;
		}
		return MouseEvent();
	}
}
