//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
module two.ui;
#else
#include <stl/algorithm.h>
#include <infra/Vector.h>
#include <tree/Graph.hpp>
#include <math/Vec.hpp>
//#include <ui/Extern.h>
#include <ui/Node.h>
#include <ui/NodeStruct.h>
#include <ui/ContainerStruct.h>
#include <ui/ScrollSheet.h>
#include <ui/Cursor.h>
#include <ui/Style/Paint.h>
#include <ui/UiRenderer.h>
#include <ui/Frame/Solver.h>
#include <ui/Style/Layout.h>
#endif

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
		Frame& plan = canvas.m_plan->m_frame;

		int min_index = 0;
		int max_index = 0;
		for(Node* node : canvas.m_nodes)
		{
			min_index = min(min_index, node->m_order);
			max_index = max(max_index, node->m_order);
		}

		int shift = -min(0, min_index);
		
		static Layout layout_overlay = [](Layout& l) { l.m_space = Preset::Board; };
		static Layout layout_line = [](Layout& l) { l.m_space = Preset::Item; l.m_align = { Align::Center, Align::Center }; l.m_padding = vec4(20.f); l.m_spacing = vec2(100.f); };
		static Layout layout_column = [](Layout& l) { l.m_space = Preset::Unit; l.m_align = { Align::Left, Align::Center }; l.m_padding = vec4(20.f); l.m_spacing = vec2(20.f); };
		static Layout layout_node = [](Layout& l) { l.m_space = Preset::Block; };

		SolverVector solvers;
		
		RowSolver overlay(plan.m_solver.get(), &layout_overlay);
		overlay.m_size = plan.m_size;
		solvers.push_back(&overlay);

		RowSolver line(&overlay, &layout_line);
		//RowSolver line(plan.m_solver.get(), &layout_line);
		solvers.push_back(&line);

		vector<RowSolver> columns; columns.reserve(canvas.m_nodes.size());
		vector<FrameSolver> elements; elements.reserve(canvas.m_nodes.size());

		for(int i = 0; i < max_index + shift + 1; ++i)
		{
			columns.push_back({ &line, &layout_column });
			solvers.push_back(&columns.back());
		}

		for(size_t i = 0; i < canvas.m_nodes.size(); ++i)
		{
			elements.push_back({ &columns[canvas.m_nodes[i]->m_order + shift], &layout_node, &canvas.m_nodes[i]->m_frame });
			elements.back().sync();
			solvers.push_back(&elements.back());
		}

		relayout(solvers);
	}

	void draw_node_cable(vec2 pos_out, vec2 pos_in, const Colour& colour_out, const Colour& colour_in, bool straight, Vg& vg)
	{
		float distance = straight ? 20.f : 100.f;
		Gradient paint = { colour_out, colour_in };
		vg.path_bezier(pos_out, pos_out + vec2(distance, 0.f), pos_in - vec2(distance, 0.f), pos_in, straight);
		vg.stroke_gradient(paint, 1.f, pos_out, pos_in);
	}

	Widget& node_knob(Widget& parent, Style& style, const Colour& colour, bool active, bool connected)
	{
		Widget& self = widget(parent, style);
		static Colour disabled_colour = Colour::DarkGrey;
		self.m_custom_draw = [=](const Frame& frame, const vec4& rect, Vg& vg)
		{
			UNUSED(rect); draw_knob(frame, active ? colour : disabled_colour, connected, vg);
		};
		return self;
	}

	Widget& canvas_cable(Widget& parent, NodeKnob& out, NodeKnob& in, bool straight = false)
	{
		Widget& self = widget(parent, node_styles().cable);
		self.m_frame.m_position = min(out.m_end, in.m_end);
		self.m_frame.m_size = max(out.m_end, in.m_end) - self.m_frame.m_position;
		self.m_custom_draw = [&, straight](const Frame& frame, const vec4& rect, Vg& vg)
		{
			UNUSED(rect); draw_node_cable(out.m_end - frame.m_position, in.m_end - frame.m_position, out.m_colour, in.m_colour, straight, vg);
		};
		return self;
	}

	vec2 plug_at_out(Canvas& canvas, NodePlug& plug)
	{
		Frame& knob = plug.m_knob->m_frame;
		return knob.derive_position({ knob.m_size.x, knob.m_size.y / 2 }, canvas.m_plan->m_frame);
	}

	vec2 plug_at_in(Canvas& canvas, NodePlug& plug)
	{
		Frame& knob = plug.m_knob->m_frame;
		return knob.derive_position({ 0.f, knob.m_size.y / 2 }, canvas.m_plan->m_frame);
	}

	Widget& node_cable(Canvas& canvas, NodePlug& out, NodePlug& in)
	{
		return canvas_cable(*canvas.m_plan, out, in, !canvas.m_rounded_links);
	}

	NodePlug& node_plug(Node& node, cstring name, cstring icon, const Colour& colour, bool input, bool active, bool connected)
	{
		NodePlug& self = input ? twidget<NodePlug>(*node.m_inputs, node_styles().plug)
							   : twidget<NodePlug>(*node.m_outputs, node_styles().plug);
		self.m_node = &node;
		self.m_colour = colour;

		if(input)
			self.m_knob = &node_knob(self, node_styles().knob, colour, active, connected);

		label(self, name).set_state(DISABLED, !active);
		UNUSED(icon);
		//item(self, icon);

		if(!input)
			self.m_knob = &node_knob(self, node_styles().knob_output, colour, active, connected);

		Canvas& canvas = *node.m_canvas;

		self.m_end = input ? plug_at_in(canvas, self) : plug_at_out(canvas, self);

		CanvasConnect& connect = canvas.m_connect;

		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
		{
			Widget* target = static_cast<Widget*>(event.m_target);
			NodePlug* target_plug = nullptr;
			if(target && target->m_frame.d_style == &node_styles().plug && target != &self)
				target_plug = static_cast<NodePlug*>(target);

			connect.m_origin = &self;
			connect.m_in = input ? &self : target_plug;
			connect.m_out = input ? target_plug : &self;
			connect.m_position = event.m_pos;

			if(target_plug)
			{
				connect.m_end = *target_plug;
			}
			else
			{
				connect.m_end.m_end = canvas.m_plan->m_frame.local_position(connect.m_position);
				connect.m_end.m_colour = self.m_colour;
			}
		}

		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::DragEnded))
		{
			canvas.m_connect.m_done = true;
		}

		return self;
	}

	Widget& node_header(Widget& parent, span<cstring> title)
	{
		Widget& self = multi_item(parent, node_styles().header, title);
		spacer(self);
		return self;
	}

	void canvas_clear_select(Canvas& canvas)
	{
		for(Node* selected : canvas.m_selection)
			selected->disable_state(SELECTED);
		canvas.m_selection.clear();
	}

	void canvas_select(Canvas& canvas, Node& node)
	{
		canvas_clear_select(canvas);
		select(canvas.m_selection, &node);
		node.enable_state(SELECTED);
	}

	void canvas_swap_select(Canvas& canvas, Node& node)
	{
		bool selected = select_swap(canvas.m_selection, &node);
		node.set_state(SELECTED, selected);
	}

	template <class T>
	inline T& ttwidget(Widget& parent, Style& style, void* identity)
	{
		T& self = parent.subi<T>(identity); self.init(style); return self;
	}

	Node& node(Canvas& parent, span<cstring> title, int order, Ref identity)
	{
		Node& self = ttwidget<Node>(*parent.m_plan, node_styles().node, identity.m_value);
		self.layer();
		self.m_canvas = &parent;
		self.m_order = order;
		self.m_header = &node_header(self, title);

		Widget& plugs = widget(self, node_styles().plugs);
		self.m_inputs = &widget(plugs, node_styles().inputs);
		self.m_outputs = &widget(plugs, node_styles().outputs);

		self.m_body = &self;

		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::Stroked, InputMod::Shift))
			canvas_swap_select(parent, self);
		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
			canvas_select(parent, self);
		if(MouseEvent event = self.mouse_event(DeviceType::MouseRight, EventType::Stroked))
			canvas_select(parent, self);

		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
		{
			if(!has(parent.m_selection, &self))
				canvas_select(parent, self);

			for(Node* node : parent.m_selection)
				node->m_frame.set_position(node->m_frame.m_position + event.m_delta / node->m_frame.absolute_scale());
		}

		self.m_index = uint32_t(parent.m_nodes.size());
		parent.m_nodes.push_back(&self);

		return self;
	}

	Node& node(Canvas& parent, span<cstring> title, float* position, int order, Ref identity)
	{
		Node& self = node(parent, title, order, identity);
		if(self.once())// && position != vec2(0.f))
			self.m_frame.set_position({ position[0], position[1] });
		else
		{
			position[0] = self.m_frame.m_position.x;
			position[1] = self.m_frame.m_position.y;
		}
		return self;
	}

	Node& node(Canvas& parent, span<cstring> title, vec2& position, int order, Ref identity)
	{
		return node(parent, title, &position[0], order, identity);
	}

	Node& node(Canvas& parent, cstring title, vec2& position, int order, Ref identity)
	{
		return node(parent, { title }, &position[0], order, identity);
	}

	Canvas& canvas(Widget& parent, size_t num_nodes) // , const Callback& context_trigger
	{
		Canvas& self = twidget<Canvas>(parent, canvas_styles().canvas);
		self.layer();

		self.m_scroll_plan = &scroll_plan(self);
		self.m_plan = self.m_scroll_plan->m_body;

		autofit_scroll_plan(*self.m_scroll_plan, to_array_cast<Widget*>(self.m_nodes));

		//if(mouse_click_right(self) && context_trigger)
		//	context_trigger(self);

		if(MouseEvent event = self.m_scroll_plan->mouse_event(DeviceType::MouseLeft, EventType::Dragged))
		{
			for(Node* node : self.m_selection)
				node->m_frame.set_position(node->m_frame.m_position + event.m_delta / node->m_frame.absolute_scale());
		}

		if(MouseEvent event = self.m_scroll_plan->mouse_event(DeviceType::MouseLeft, EventType::Stroked))
			canvas_clear_select(self);

		if(MouseEvent event = self.m_scroll_plan->mouse_event(DeviceType::MouseMiddle, EventType::Stroked))
			canvas_autolayout(self);

		self.m_nodes.reserve(num_nodes);
		self.m_nodes.clear();

		return self;
	}

	NodeConnection canvas_connect(Canvas& canvas)
	{
		NodeConnection connection = {};
		
		CanvasConnect& connect = canvas.m_connect;
		if(connect.m_origin)
		{
			canvas_cable(*canvas.m_plan, connect.m_out ? *connect.m_out : connect.m_end, connect.m_in ?  *connect.m_in : connect.m_end);

			if(connect.m_done)
			{
				if(connect.m_out && connect.m_in)
					connection = { connect.m_out->m_node->m_index, connect.m_out->m_index,
								   connect.m_in->m_node->m_index,  connect.m_in->m_index };

				connect = {};
			}
		}
		else
		{
			static NodeKnob dum = { vec2(0.f), Colour(0.f, 0.f) };
			canvas_cable(*canvas.m_plan, dum, dum);
			connect = {};
		}

		return connection;
	}
}
}
