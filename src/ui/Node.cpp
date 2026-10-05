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
	void draw_knob(const Frame& frame, const Colour& colour, bool connected, Vg& vg)
	{
		float radius = connected ? 5.f : 4.f;
		vg.path_circle(frame.m_size / 2.f, radius);
		if(connected)
			vg.fill({ colour });
		else
			vg.stroke({ colour, 2.f });
	}


	void canvas_autolayout(Canvas& canvas)
	{
		Frame& plan = canvas.m_plan->frame();

		int min_index = 0;
		int max_index = 0;
		for(NodeHandle node : canvas.m_nodes)
		{
			min_index = min(min_index, node->m_order);
			max_index = max(max_index, node->m_order);
		}

		int shift = -min(0, min_index);
		
		static Layout layout_overlay = [](Layout& l) { l.m_space = Preset::Board; };
		static Layout layout_line = [](Layout& l) { l.m_space = Preset::Item; l.m_padding = vec4(20.f); l.m_spacing = vec2(100.f); };
		static Layout layout_column = [](Layout& l) { l.m_space = Preset::Unit; l.m_align = { Align::Left, Align::Center }; l.m_padding = vec4(20.f); l.m_spacing = vec2(20.f); };
		static Layout layout_node = [](Layout& l) { l.m_space = Preset::Block; };

		// the nodes are laid out in columns by order, the columns side by side in a line from the origin of the plan, centered against each other
		LayoutTree tree;
		const uint32_t root = tree.add_root(*plan.d_layout, plan.m_size);
		const uint32_t overlay = tree.add(root, layout_overlay);
		const uint32_t line = tree.add(overlay, layout_line);

		vector<uint32_t> columns;
		for(int i = 0; i < max_index + shift + 1; ++i)
			columns.push_back(tree.add(line, layout_column));

		vector<uint32_t> elements;
		for(NodeHandle node : canvas.m_nodes)
			elements.push_back(tree.add(columns[node->m_order + shift], layout_node, node.self));

		tree.solve();

		for(size_t i = 0; i < canvas.m_nodes.size(); ++i)
			canvas.m_nodes[i].self->set_position(tree.absolute(elements[i]));
	}

	void draw_node_cable(vec2 pos_out, vec2 pos_in, const Colour& colour_out, const Colour& colour_in, bool straight, Vg& vg)
	{
		float distance = straight ? 20.f : 100.f;
		Gradient paint = { colour_out, colour_in };
		vg.path_bezier(pos_out, pos_out + vec2(distance, 0.f), pos_in - vec2(distance, 0.f), pos_in, straight);
		vg.stroke_gradient(paint, 1.f, pos_out, pos_in);
	}

	Widget& node_knob(NodeKey id, Widget& parent, Style& style, const Colour& colour, bool active, bool connected)
	{
		Widget& self = widget(id, parent, style);
		static Colour disabled_colour = Colour::DarkGrey;
		self.custom_draw() = [=](Widget& widget, const vec4& rect, Vg& vg)
		{
			UNUSED(rect); draw_knob(widget.frame(), active ? colour : disabled_colour, connected, vg);
		};
		return self;
	}

	Widget& canvas_cable(NodeKey id, Widget& parent, NodeKnob& out, NodeKnob& in, bool straight = false)
	{
		Widget& self = widget(id, parent, node_styles().cable);
		self.set_position(min(out.m_end, in.m_end));
		self.frame().m_size = max(out.m_end, in.m_end) - self.frame().m_position;
		self.custom_draw() = [=](Widget& widget, const vec4& rect, Vg& vg)
		{
			UNUSED(rect); draw_node_cable(out.m_end - widget.frame().m_position, in.m_end - widget.frame().m_position, out.m_colour, in.m_colour, straight, vg);
		};
		return self;
	}

	vec2 plug_at_out(Canvas& canvas, NodePlug& plug)
	{
		Widget& knob = *plug.m_knob;
		return knob.derive_position({ knob.frame().m_size.x, knob.frame().m_size.y / 2 }, *canvas.m_plan);
	}

	vec2 plug_at_in(Canvas& canvas, NodePlug& plug)
	{
		Widget& knob = *plug.m_knob;
		return knob.derive_position({ 0.f, knob.frame().m_size.y / 2 }, *canvas.m_plan);
	}

	Widget& node_cable(NodeKey id, Canvas& canvas, NodePlug& out, NodePlug& in)
	{
		return canvas_cable(id, *canvas.m_plan, out, in, !canvas.m_rounded_links);
	}

	NodePlugHandle node_plug(NodeKey id, Node& node, cstring name, cstring icon, const Colour& colour, bool input, bool active, bool connected)
	{
		Widget& self = widget(id, input ? *node.m_inputs : *node.m_outputs, node_styles().plug);
		NodePlug& plug = self.state<NodePlug>();
		plug.m_node = &node;
		plug.m_colour = colour;

		if(input)
			plug.m_knob = &node_knob(key(), self, node_styles().knob, colour, active, connected);

		label(key(), self, name).set_state(DISABLED, !active);
		UNUSED(icon);
		//item(key(), self, icon);

		if(!input)
			plug.m_knob = &node_knob(key(), self, node_styles().knob_output, colour, active, connected);

		Canvas& canvas = *node.m_canvas;

		plug.m_end = input ? plug_at_in(canvas, plug) : plug_at_out(canvas, plug);

		NodePlugHandle handle = { &self, &plug };

		CanvasConnect& connect = canvas.m_connect;

		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
		{
			Widget* target = static_cast<Widget*>(event.m_target);
			NodePlugHandle target_plug = {};
			if(target && target->frame().d_style == &node_styles().plug && target != &self)
				target_plug = { target, &target->state<NodePlug>() };

			connect.m_origin = handle;
			connect.m_in = input ? handle : target_plug;
			connect.m_out = input ? target_plug : handle;
			connect.m_position = event.m_pos;

			if(target_plug)
			{
				connect.m_end = *target_plug;
			}
			else
			{
				connect.m_end.m_end = canvas.m_plan->local_position(connect.m_position);
				connect.m_end.m_colour = plug.m_colour;
			}
		}

		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::DragEnded))
		{
			canvas.m_connect.m_done = true;
		}

		return handle;
	}

	Widget& node_header(NodeKey id, Widget& parent, span<cstring> title)
	{
		Widget& self = multi_item(id, parent, node_styles().header, title);
		spacer(key(), self);
		return self;
	}

	void canvas_clear_select(Canvas& canvas)
	{
		for(NodeHandle selected : canvas.m_selection)
			selected.self->disable_state(SELECTED);
		canvas.m_selection.clear();
	}

	void canvas_select(Canvas& canvas, NodeHandle node)
	{
		canvas_clear_select(canvas);
		select(canvas.m_selection, node);
		node.self->enable_state(SELECTED);
	}

	void canvas_swap_select(Canvas& canvas, NodeHandle node)
	{
		bool selected = select_swap(canvas.m_selection, node);
		node.self->set_state(SELECTED, selected);
	}

	Node& node(Canvas& parent, span<cstring> title, float* position, int order, Ref identity)
	{
		Widget& self = widget(key(identity.m_value), *parent.m_plan, node_styles().node).layer();
		Node& node = self.state<Node>();
		node.m_canvas = &parent;
		node.m_order = order;
		node.m_header = &node_header(key(), self, title);

		Widget& plugs = widget(key(), self, node_styles().plugs);
		node.m_inputs = &widget(key(), plugs, node_styles().inputs);
		node.m_outputs = &widget(key(), plugs, node_styles().outputs);

		node.m_body = &self;

		NodeHandle handle = { &self, &node };

		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::Stroked, InputMod::Shift))
			canvas_swap_select(parent, handle);
		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
			canvas_select(parent, handle);
		if(MouseEvent event = self.mouse_event(DeviceType::MouseRight, EventType::Stroked))
			canvas_select(parent, handle);

		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
		{
			if(!has(parent.m_selection, handle))
				canvas_select(parent, handle);

			for(NodeHandle selected : parent.m_selection)
				selected.self->set_position(selected.self->frame().m_position + event.m_delta / selected.self->absolute_scale());
		}

		node.m_index = uint32_t(parent.m_nodes.size());
		parent.m_nodes.push_back(handle);

		if(!position)
			return node;

		if(self.once())// && position != vec2(0.f))
			self.set_position({ position[0], position[1] });
		else
		{
			position[0] = self.frame().m_position.x;
			position[1] = self.frame().m_position.y;
		}
		return node;
	}

	Node& node(Canvas& parent, span<cstring> title, int order, Ref identity)
	{
		return node(parent, title, nullptr, order, identity);
	}

	Node& node(Canvas& parent, span<cstring> title, vec2& position, int order, Ref identity)
	{
		return node(parent, title, &position[0], order, identity);
	}

	Node& node(Canvas& parent, cstring title, vec2& position, int order, Ref identity)
	{
		return node(parent, { title }, &position[0], order, identity);
	}

	CanvasHandle canvas(NodeKey id, Widget& parent, size_t num_nodes) // , const Callback& context_trigger
	{
		Widget& widget = ui::widget(id, parent, canvas_styles().canvas).layer();
		Canvas& self = widget.state<Canvas>();

		ScrollSheet scroll_sheet = scroll_plan(key(), widget);
		self.m_scroll_plan = &scroll_sheet.self;
		self.m_plan = &scroll_sheet.body;

		vector<Widget*> nodes;
		for(NodeHandle node : self.m_nodes)
			nodes.push_back(node.self);
		autofit_scroll_plan(*self.m_plan, nodes);

		//if(mouse_click_right(self) && context_trigger)
		//	context_trigger(self);

		if(MouseEvent event = self.m_scroll_plan->mouse_event(DeviceType::MouseLeft, EventType::Dragged))
		{
			for(NodeHandle node : self.m_selection)
				node.self->set_position(node.self->frame().m_position + event.m_delta / node.self->absolute_scale());
		}

		if(MouseEvent event = self.m_scroll_plan->mouse_event(DeviceType::MouseLeft, EventType::Stroked))
			canvas_clear_select(self);

		if(MouseEvent event = self.m_scroll_plan->mouse_event(DeviceType::MouseMiddle, EventType::Stroked))
			canvas_autolayout(self);

		self.m_nodes.reserve(num_nodes);
		self.m_nodes.clear();

		return { &widget, &self };
	}

	NodeConnection canvas_connect(Canvas& canvas)
	{
		NodeConnection connection = {};
		
		CanvasConnect& connect = canvas.m_connect;
		if(connect.m_origin)
		{
			canvas_cable(key(), *canvas.m_plan, connect.m_out ? *connect.m_out : connect.m_end, connect.m_in ?  *connect.m_in : connect.m_end);

			if(connect.m_done)
			{
				if(connect.m_out && connect.m_in)
					connection = { connect.m_out->m_node->m_index, connect.m_out.self->sibling(),
								   connect.m_in->m_node->m_index,  connect.m_in.self->sibling() };

				connect = {};
			}
		}
		else
		{
			static NodeKnob dum = { vec2(0.f), Colour(0.f, 0.f) };
			canvas_cable(key(), *canvas.m_plan, dum, dum);
			connect = {};
		}

		return connection;
	}
}
}
