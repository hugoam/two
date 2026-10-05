//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.uio;

namespace two
{
	struct TypeColours : public LazyGlobal<TypeColours>
	{
		TypeColours();

		Colour colour(const Type& type, const Colour& fallback) { return m_colours.find(&type) != m_colours.end() ? m_colours[&type] : fallback; }

		map<const Type*, Colour> m_colours;
	};

	TypeColours::TypeColours()
	{
		m_colours[&type<float>()] = Colour::Cyan;
		m_colours[&type<double>()] = Colour::Cyan;
		m_colours[&type<int>()] = Colour::Cyan;
		m_colours[&type<unsigned int>()] = Colour::Cyan;
		m_colours[&type<Colour>()] = Colour::Pink;

		m_colours[&type<Colour>()] = Colour::Pink;
		m_colours[&type<vec2>()] = Colour::Pink;
		m_colours[&type<vec3>()] = Colour::Pink;
		m_colours[&type<quat>()] = Colour::Pink;
	}

	bool fits_filter(const string& name, const string& filter)
	{
		return filter.empty() || name.find(filter) != string::npos;
	}

	void script_canvas_insert(Canvas& canvas, Widget& parent, VisualScript& script)
	{
		static string filter = "";
		ui::type_in(key(), parent, filter);

		auto add_process = [&](object<Process> process)
		{
			script.m_processes.push_back(move(process));
			vec2 position = canvas.m_plan->integrate_position(parent.m_frame.m_position, *canvas.m_scroll_plan);
			script.m_processes.back()->m_position[0] = position.x;
			script.m_processes.back()->m_position[1] = position.y;
		};

		Widget& board = ui::widget(key(), parent, styles().sheet, false, Axis::X);

		Widget& functions = ui::sheet(key(), board);
		ui::label(key(), functions, "Functions");

		for(Module* m : System::instance().m_modules)
		{
			ui::label(key(), functions, m->m_name).enable_state(DISABLED);
			for(Function* function : m->m_functions)
				if(fits_filter(function->m_name, filter))
					if(ui::multi_button(key(), functions, ui::dropdown_styles().choice, { "(function)", function->m_name }).activated())
					{
						add_process(oconstruct<ProcessFunction>(script, *function));
						parent.set_open(false);
					}
		}

		Widget& values = ui::sheet(key(), board);
		ui::label(key(), values, "Values");

		for(Module* m : System::instance().m_modules)
		{
			ui::label(key(), values, m->m_name).enable_state(DISABLED);
			for(Type* type : m->m_types)
				if(is_struct(*type) || is_base_type(*type))
					if(fits_filter(type->m_name, filter))
						if(ui::multi_button(key(), values, ui::dropdown_styles().choice, { "(value)", type->m_name }).activated())
						{
							add_process(oconstruct<ProcessValue>(script, *type));
							parent.set_open(false);
						}
		}

		Widget& types = ui::sheet(key(), board);
		ui::label(key(), types, "Objects");

		for(Module* m : System::instance().m_modules)
		{
			ui::label(key(), types, m->m_name).enable_state(DISABLED);
			for(Type* type : m->m_types)
				if(g_class[type->m_id] && !cls(*type).m_constructors.empty()) //is_struct(*type) || is_base_type(*type))
					if(fits_filter(type->m_name, filter))
						if(ui::multi_button(key(), types, ui::dropdown_styles().choice, { "(class)", type->m_name }).activated())
						{
							add_process(oconstruct<ProcessCreate>(script, *type));
							parent.set_open(false);
						}
		}
	}

	Valve& node_valve(VisualScript& script, size_t node, size_t plug, bool input) //Canvas& canvas, Valve& valve)
	{
		Process& process = *script.m_processes[node];
		return input ? *process.m_inputs[plug] : *process.m_outputs[plug];
	}

	void process_valve(VisualScript& script, Canvas& canvas, Node& node, Valve& valve)
	{
		Colour colour = TypeColours::me().colour(*valve.m_stream.m_type, Colour::Green);
		string icon = valve.m_stream.m_type ? "(" + string(valve.m_stream.m_type->m_name) + ")" : "";
		bool input = (valve.m_kind == INPUT_VALVE || valve.m_kind == FLOW_VALVE_IN);

		bool enabled = true;
		if(canvas.m_connect.m_origin)
		{
			size_t connect_node = canvas.m_connect.m_origin->m_node->m_index;
			size_t connect_plug = canvas.m_connect.m_origin->m_self->sibling();
			Valve& connecting = node_valve(script, connect_node, connect_plug, canvas.m_connect.m_origin == canvas.m_connect.m_in);

			bool convertible = can_convert(input ? *connecting.m_stream.m_type : *valve.m_stream.m_type,
										   input ? *valve.m_stream.m_type : *connecting.m_stream.m_type);
			bool conflicting = connecting.m_kind == valve.m_kind || !convertible;
			if(&valve != &connecting && conflicting)
				enabled = false;
		}

		NodePlug& plug = ui::node_plug(key(), node, valve.m_name.c_str(), icon.c_str(), colour, input, enabled, !valve.m_pipes.empty());
		
		if(Widget* tooltip = ui::tooltip(key(), *plug.m_self, plug.m_self->m_frame))
		{
			string info = valve.error_info() + valve.param_info();
			ui::label(key(), *tooltip, info.c_str());
		}
	}

	void process_tweakers(Widget& parent, Process& process)
	{
		for(Valve* output : process.m_outputs)
			if(output->m_edit)
			{
				Ref value = output->m_stream.value({ 0 });
				if(any_edit(parent, value))
					output->propagate();
			}
	}

	void process_display(Widget& parent, ProcessDisplay& process)
	{
		process.m_input_value.m_stream.visit(true, [&](StreamBranch& branch) {
			Ref value = branch.m_value;
			value_edit(parent, value); // value_display
		});
	}

	cstring node_type(Process& process)
	{
		if(process.m_type.is<ProcessValue>())
			return "(value)";
		else if(process.m_type.is<ProcessCreate>())
			return "(class)";
		else if(process.m_type.is<ProcessCallable>())
			return "(function)";
		else
			return "";
	}

	bool script_process(Canvas& canvas, VisualScript& script, Process& process)
	{
        UNUSED(script);
		bool destroy = false;

		Node& node = ui::node(canvas, { process.m_title.c_str() }, &process.m_position[0], process.m_order, Ref(&process));
		if(ui::button(key(), *node.m_header, "R").activated())
			process.recompute();
		if(ui::button(key(), *node.m_header, "X").activated())
			destroy = true;

#if 0
		if(Widget* context = ui::context(key(), node, (1 << 0), ui::PopupModal))
		{

		}
#endif

		if(process.m_in_flow)
			process_valve(process.m_script, canvas, node, *process.m_in_flow);
		for(Valve* input : process.m_inputs)
			process_valve(process.m_script, canvas, node, *input);

		if(process.m_out_flow)
			process_valve(process.m_script, canvas, node, *process.m_out_flow);
		for(Valve* output : process.m_outputs)
			process_valve(process.m_script, canvas, node, *output);

		process_tweakers(*node.m_body, process);

		if(is<ProcessDisplay>(process))
			process_display(*node.m_body, as<ProcessDisplay>(process));

		return !destroy;
	}

	NodePlug& node_plug(Canvas& canvas, Valve& valve)
	{
		//bool input = (valve.m_kind == INPUT_VALVE || valve.m_kind == FLOW_VALVE_IN);
		
		Node& node = *canvas.m_nodes[valve.m_process.m_index];
		if(valve.m_kind == INPUT_VALVE)
			return node.m_inputs->child(valve.m_process.m_in_flow ? valve.m_index + 1 : valve.m_index).state<NodePlug>();
		if(valve.m_kind == OUTPUT_VALVE)
			return node.m_outputs->child(valve.m_process.m_out_flow ? valve.m_index + 1 : valve.m_index).state<NodePlug>();
		else if(valve.m_kind == FLOW_VALVE_IN)
			return node.m_inputs->child(0).state<NodePlug>();
		else if(valve.m_kind == FLOW_VALVE_OUT || true)
			return node.m_outputs->child(0).state<NodePlug>();

		//Widget& plug = input ? node.m_inputs->child(valve.m_index) : node.m_outputs->child(valve.m_index);
		//return plug;
	}

	void script_pipe(Canvas& canvas, Pipe& pipe)
	{
		ui::node_cable(key(), canvas, node_plug(canvas, pipe.m_output), node_plug(canvas, pipe.m_input));
		//canvas.autoLayout();
	}

	Canvas& script_canvas(Widget& parent, VisualScript& script)
	{
		enum Modes { Insert = 1 << 0 };

		Canvas& canvas = ui::canvas(key(), parent, script.m_processes.size());

		if(Widget* popup = ui::context(key(), *canvas.m_scroll_plan, Insert, ui::PopupFlags::Modal))
			script_canvas_insert(canvas, *popup, script);

		Process* destroy = nullptr;
		for(auto& process : script.m_processes)
		{
			if(!script_process(canvas, script, *process))
				destroy = process.get();
		}

		for(auto& pipe : script.m_pipes)
			script_pipe(canvas, *pipe);

		NodeConnection connection = ui::canvas_connect(canvas);
		if(connection.valid())
		{
			Valve& output = *script.m_processes[connection.m_out_node]->m_outputs[connection.m_out_plug];
			Valve& input = *script.m_processes[connection.m_in_node]->m_inputs[connection.m_in_plug];
			if(can_convert(*output.m_stream.m_type, *input.m_stream.m_type))
				script.connect(output, input);
		}

		if(canvas.m_self->once())
		{
			canvas.m_self->relayout();
			ui::canvas_autolayout(canvas);
		}

		if(destroy)
			script.remove(*destroy);

		return canvas;
	}

	Section visual_script_edit(Widget& parent, VisualScript& script)
	{
		Section self = section(key(), parent, script.m_name.c_str());

		Canvas& canvas = script_canvas(self.body, script);

		if(ui::button(key(), *self.toolbar, "Autolayout").activated())
			ui::canvas_autolayout(canvas);

		ui::toggle(key(), *self.toolbar, canvas.m_rounded_links, "Rounded Links");
		return self;
	}
}
