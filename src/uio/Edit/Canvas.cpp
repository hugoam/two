//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>
#ifndef MUD_CPP_20
#include <map>
#endif

#ifdef MUD_MODULES
module mud.uio;
#else
#include <infra/Global.h>
#include <refl/Module.h>
#include <lang/VisualScript.h>
#include <lang/VisualBlocks.h>
#include <ui/Input.h>
#include <ui/Structs/Node.h>
#include <ui/Structs/Container.h>
#include <uio/Types.h>
#include <uio/Edit/Canvas.h>
#include <uio/Unode.h>
#include <uio/Edit/Structure.h>
#include <uio/Edit/Value.h>
#endif

namespace mud
{
	struct TypeColours : public Global<TypeColours>
	{
		TypeColours();

		Colour colour(Type& type, const Colour& fallback) { return m_colours.find(&type) != m_colours.end() ? m_colours[&type] : fallback; }

		std::map<Type*, Colour> m_colours;
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

	enum CanvasModes
	{
		SCRIPT_CANVAS_INSERT = (1 << 0)
	};

	bool fits_filter(const string& name, const string& filter)
	{
		return filter.empty() || name.find(filter) != string::npos;
	}

	void script_canvas_insert(Canvas& canvas, Widget& parent, VisualScript& script)
	{
		static string filter = "";
		ui::type_in(parent, filter);

		auto add_process = [&](object_ptr<Process> process)
		{
			script.m_processes.push_back(std::move(process));
			vec2 position = canvas.m_plan->m_frame.integrate_position(parent.m_frame.m_position, canvas.m_scroll_plan->m_frame);
			script.m_processes.back()->m_position[0] = position.x;
			script.m_processes.back()->m_position[1] = position.y;
		};

		Widget& board = ui::widget(parent, styles().sheet, false, DIM_X);

		Widget& functions = ui::sheet(board);
		ui::label(functions, "Functions");

		for(Module* m : System::instance().m_modules)
		{
			ui::label(functions, m->m_name).enableState(DISABLED);
			for(Function* function : m->m_functions)
				if(fits_filter(function->m_name, filter))
					if(ui::multi_button(functions, ui::dropdown_styles().choice, carray<cstring, 2>{ "(function)", function->m_name }).activated())
					{
						add_process(make_object<ProcessFunction>(script, *function));
						parent.m_open = false;
					}
		}

		Widget& values = ui::sheet(board);
		ui::label(values, "Values");

		for(Module* m : System::instance().m_modules)
		{
			ui::label(values, m->m_name).enableState(DISABLED);
			for(Type* type : m->m_types)
				if(is_struct(*type) || is_base_type(*type))
					if(fits_filter(type->m_name, filter))
						if(ui::multi_button(values, ui::dropdown_styles().choice, carray<cstring, 2>{ "(value)", type->m_name }).activated())
						{
							add_process(make_object<ProcessValue>(script, *type));
							parent.m_open = false;
						}
		}

		Widget& types = ui::sheet(board);
		ui::label(types, "Objects");

		for(Module* m : System::instance().m_modules)
		{
			ui::label(types, m->m_name).enableState(DISABLED);
			for(Type* type : m->m_types)
				if(g_class[type->m_id] && !cls(*type).m_constructors.empty()) //is_struct(*type) || is_base_type(*type))
					if(fits_filter(type->m_name, filter))
						if(ui::multi_button(types, ui::dropdown_styles().choice, carray<cstring, 2>{ "(class)", type->m_name }).activated())
						{
							add_process(make_object<ProcessCreate>(script, *type));
							parent.m_open = false;
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
		string icon = valve.m_stream.m_type ? "(" + string(meta(*valve.m_stream.m_type).m_name) + ")" : "";
		bool input = (valve.m_kind == INPUT_VALVE || valve.m_kind == FLOW_VALVE_IN);

		bool enabled = true;
		if(canvas.m_connect.m_origin)
		{
			size_t connect_node = canvas.m_connect.m_origin->m_node->m_index;
			size_t connect_plug = canvas.m_connect.m_origin->m_index;
			Valve& connecting = node_valve(script, connect_node, connect_plug, canvas.m_connect.m_origin == canvas.m_connect.m_in);

			bool convertible = can_convert(input ? *connecting.m_stream.m_type : *valve.m_stream.m_type,
											input ? *valve.m_stream.m_type : *connecting.m_stream.m_type);
			bool conflicting = connecting.m_kind == valve.m_kind || !convertible;
			if(&valve != &connecting && conflicting)
				enabled = false;
		}

		NodePlug& plug = ui::node_plug(node, valve.m_name.c_str(), icon.c_str(), colour, input, enabled, !valve.m_pipes.empty());
		
		if(Widget* tooltip = ui::tooltip(plug, plug.m_frame))
		{
			string info = valve.error_info() + valve.param_info();
			ui::label(*tooltip, info.c_str());
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
		process.inputValue().m_stream.visit(true, [&](StreamBranch& branch) {
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

		Node& node = ui::node(canvas, carray<cstring, 1>{ process.m_title.c_str() }, &process.m_position[0], process.m_order, &process);
		if(ui::button(*node.m_header, "R").activated())
			process.recompute();
		if(ui::button(*node.m_header, "X").activated())
			destroy = true;

#if 0
		if(Widget* context = ui::context(node, (1 << 0), ui::PopupModal))
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
			return as<NodePlug>(*node.m_inputs->m_nodes[valve.m_process.m_in_flow ? valve.m_index + 1 : valve.m_index]);
		if(valve.m_kind == OUTPUT_VALVE)
			return as<NodePlug>(*node.m_outputs->m_nodes[valve.m_process.m_out_flow ? valve.m_index + 1 : valve.m_index]);
		else if(valve.m_kind == FLOW_VALVE_IN)
			return as<NodePlug>(*node.m_inputs->m_nodes[0]);
		else //if(valve.m_kind == FLOW_VALVE_OUT)
			return as<NodePlug>(*node.m_outputs->m_nodes[0]);

		//Widget& plug = input ? *node.m_inputs->m_nodes[valve.m_index] : *node.m_outputs->m_nodes[valve.m_index];
		//return plug;
	}

	void script_pipe(Canvas& canvas, Pipe& pipe)
	{
		ui::node_cable(canvas, node_plug(canvas, pipe.m_output), node_plug(canvas, pipe.m_input));
		//canvas.autoLayout();
	}

	Canvas& script_canvas(Widget& parent, VisualScript& script)
	{
		Canvas& canvas = ui::canvas(parent, script.m_processes.size());

		if(Widget* popup = ui::context(*canvas.m_scroll_plan, SCRIPT_CANVAS_INSERT, ui::PopupFlags::Modal))
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
		if(connection.m_valid)
		{
			Valve& output = *script.m_processes[connection.m_out_node]->m_outputs[connection.m_out_plug];
			Valve& input = *script.m_processes[connection.m_in_node]->m_inputs[connection.m_in_plug];
			if(can_convert(*output.m_stream.m_type, *input.m_stream.m_type))
				script.connect(output, input);
		}

		if(canvas.once())
		{
			canvas.m_frame.relayout();
			ui::canvas_autolayout(canvas);
		}

		if(destroy)
			script.remove(*destroy);

		return canvas;
	}

	void visual_script_edit(Widget& parent, VisualScript& script, ActionList actions)
	{
		Section& self = section(parent, script.m_name.c_str(), actions);

		Canvas& canvas = script_canvas(*self.m_body, script);

		if(ui::button(*self.m_toolbar, "Autolayout").activated())
			ui::canvas_autolayout(canvas);

		ui::toggle(*self.m_toolbar, canvas.m_rounded_links, "Rounded Links");
	}
}
