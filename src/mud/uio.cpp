#include <mud/ui.h>
#include <mud/pool.h>
#include <mud/uio.h>
#include <mud/ui.refl.h>
#include <mud/lang.h>
#include <mud/ecs.h>
#include <mud/type.refl.h>
#include <mud/math.h>
#include <mud/refl.refl.h>
#include <mud/refl.h>
#include <mud/infra.h>
#include <mud/type.h>


#ifdef MUD_MODULES
module mud.uio;
#else
#endif

namespace mud
{
#if 0
	Dropper::Dropper(Widget& parent, Type& deviceType)
		: Widget(parent, deviceType)
	{}

	void Dropper::drop(Widget& parent, , size_t index)
	{
		Dropper& source = static_cast<Dropper&>(*node.m_parent);
		Widget* swap = this->swapdrop(node, source);
		size_t swapindex = node.m_index;

		if(!this->candrop(node, source))
			return;

		if(swap)
		{
			if(!source.candrop(*swap, *this))
				return;
		}

		source.dropout(node, *this);
		this->dropin(node, source, index);

		if(swap)
		{
			this->dropout(*swap, source);
			source.dropin(*swap, *this, swapindex);
		}
	}
#endif
}

#ifdef MUD_MODULES
module mud.uio;
#else
#include <stl/tinystl/vector.impl.h>
#include <stl/tinystl/unordered_map.impl.h>
#endif

using namespace mud;
namespace tinystl
{
	template class MUD_UIO_EXPORT vector<EditSpec>;
	template class MUD_UIO_EXPORT unordered_map<Module*, bool>;
}


#ifdef MUD_MODULES
module mud.uio;
#else
#endif

namespace mud
{
	string object_name(Ref object)
	{
		if(!object) return "null";
		//else if(object.m_type->is<Entity>()) return to_name(val<Entity>(object).m_prototype.m_type, object);
		else return to_name(type(object), object);
	}

	string object_icon(Ref object)
	{
		if(!object) return "";
		//else if(type(object).is<Entity>()) return "(" + string(val<Entity>(object).m_prototype.m_type.m_name) + ")";
		else return "(" + string(type(object).m_name) + ")";
	}

	void object_context(Widget& parent, Ref object, uint32_t mode)
	{
		Widget& self = ui::popup(parent, ui::PopupFlags::AutoModal);
		if(!self.m_open)
			parent.m_switch &= ~mode;

		//if(meta(object).m_type_class == TypeClass::Object)
		//	object = val<Entity>(object);

		for(Method* method : cls(object).m_deep_methods)
		{
			Ref component = cls(object).as(object, *method->m_object_type);
			method_hook(self, component, *method);
		}
	}

	Widget& generic_object_item(Widget& parent, Ref object)
	{
		enum Modes { Context = (1 << 0) };

		Widget& self = ui::element(parent, object);
		ui::multi_item(self, { object_icon(object).c_str(), object_name(object).c_str() });
		
		if(MouseEvent event = self.mouse_event(DeviceType::MouseRight, EventType::Stroked))
			self.m_switch |= Context;
		if((self.m_switch & Context) != 0)
			object_context(self, object, Context);

		return self;
	}

	Widget& object_button(Widget& parent, Ref object)
	{
		return generic_object_item(parent, object);
	}

	Widget& object_item(Widget& parent, Ref object)
	{
		if(DispatchItem::me().check(object))
			return DispatchItem::me().dispatch(object, parent);
		else
			return generic_object_item(parent, object);
	}

	bool object_item(Widget& parent, Ref object, Ref& selection)
	{
		Widget& self = object_item(parent, object);
		return ui::select_logic(self, object, selection);
	}

	bool object_item(Widget& parent, Ref object, vector<Ref>& selection)
	{
		Widget& self = object_item(parent, object);
		return ui::multiselect_logic(self, object, selection);
	}
}

#ifdef MUD_MODULES
module mud.uio;
#else
#endif

namespace mud
{
    // Exported types
    template <> MUD_UIO_EXPORT Type& type<mud::EditNestMode>() { static Type ty("mud::EditNestMode", sizeof(mud::EditNestMode)); return ty; }
    template <> MUD_UIO_EXPORT Type& type<mud::EditorHint>() { static Type ty("mud::EditorHint", sizeof(mud::EditorHint)); return ty; }
    
    template <> MUD_UIO_EXPORT Type& type<mud::ScriptEditor>() { static Type ty("ScriptEditor", sizeof(mud::ScriptEditor)); return ty; }
}


#ifdef MUD_MODULES
module mud.uio;
#else
#endif

namespace mud
{
	DispatchItem::DispatchItem()
	{}
}

#ifndef MUD_CPP_20
#include <stl/map.h>
#endif

#ifdef MUD_MODULES
module mud.uio;
#else
#endif

namespace mud
{
	struct TypeColours : public Global<TypeColours>
	{
		TypeColours();

		Colour colour(Type& type, const Colour& fallback) { return m_colours.find(&type) != m_colours.end() ? m_colours[&type] : fallback; }

		map<Type*, Colour> m_colours;
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
		ui::type_in(parent, filter);

		auto add_process = [&](object<Process> process)
		{
			script.m_processes.push_back(move(process));
			vec2 position = canvas.m_plan->m_frame.integrate_position(parent.m_frame.m_position, canvas.m_scroll_plan->m_frame);
			script.m_processes.back()->m_position[0] = position.x;
			script.m_processes.back()->m_position[1] = position.y;
		};

		Widget& board = ui::widget(parent, styles().sheet, false, DIM_X);

		Widget& functions = ui::sheet(board);
		ui::label(functions, "Functions");

		for(Module* m : System::instance().m_modules)
		{
			ui::label(functions, m->m_name).enable_state(DISABLED);
			for(Function* function : m->m_functions)
				if(fits_filter(function->m_name, filter))
					if(ui::multi_button(functions, ui::dropdown_styles().choice, { "(function)", function->m_name }).activated())
					{
						add_process(oconstruct<ProcessFunction>(script, *function));
						parent.m_open = false;
					}
		}

		Widget& values = ui::sheet(board);
		ui::label(values, "Values");

		for(Module* m : System::instance().m_modules)
		{
			ui::label(values, m->m_name).enable_state(DISABLED);
			for(Type* type : m->m_types)
				if(is_struct(*type) || is_base_type(*type))
					if(fits_filter(type->m_name, filter))
						if(ui::multi_button(values, ui::dropdown_styles().choice, { "(value)", type->m_name }).activated())
						{
							add_process(oconstruct<ProcessValue>(script, *type));
							parent.m_open = false;
						}
		}

		Widget& types = ui::sheet(board);
		ui::label(types, "Objects");

		for(Module* m : System::instance().m_modules)
		{
			ui::label(types, m->m_name).enable_state(DISABLED);
			for(Type* type : m->m_types)
				if(g_class[type->m_id] && !cls(*type).m_constructors.empty()) //is_struct(*type) || is_base_type(*type))
					if(fits_filter(type->m_name, filter))
						if(ui::multi_button(types, ui::dropdown_styles().choice, { "(class)", type->m_name }).activated())
						{
							add_process(oconstruct<ProcessCreate>(script, *type));
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
		Colour colour = TypeColours::me.colour(*valve.m_stream.m_type, Colour::Green);
		string icon = valve.m_stream.m_type ? "(" + string(valve.m_stream.m_type->m_name) + ")" : "";
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
		enum Modes { Insert = 1 << 0 };

		Canvas& canvas = ui::canvas(parent, script.m_processes.size());

		if(Widget* popup = ui::context(*canvas.m_scroll_plan, Insert, ui::PopupFlags::Modal))
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

	Section& visual_script_edit(Widget& parent, VisualScript& script)
	{
		Section& self = section(parent, script.m_name.c_str());

		Canvas& canvas = script_canvas(*self.m_body, script);

		if(ui::button(*self.m_toolbar, "Autolayout").activated())
			ui::canvas_autolayout(canvas);

		ui::toggle(*self.m_toolbar, canvas.m_rounded_links, "Rounded Links");
		return self;
	}
}

#ifndef MUD_CPP_20
#include <stl/string.h>
#endif

#ifdef MUD_MODULES
module mud.uio;
#else
#endif

namespace mud
{
	DispatchSelector::DispatchSelector()
	{}

	void complex_indexer(Widget& parent, Indexer& indexer, vector<Ref>* selection)
	{
		Member& complex = cls(indexer.m_type).member("complex");

		Widget& self = ui::sheet(parent);
		for(Ref component : indexer.m_objects)
			if(component)
			{
				Ref object = complex.cast_get(component);
				Widget& item = object_item(self, object);
				if(selection)
					ui::multiselect_logic(item, object, *selection);
			}
	}

	void object_indexer(Widget& parent, Indexer& indexer, vector<Ref>* selection)
	{
		Widget& self = ui::sheet(parent);
		for(Ref object : indexer.m_objects)
			if(object)
			{
				Widget& item = object_item(self, object);
				if(selection)
					ui::multiselect_logic(item, object, *selection);
			}
	}

	bool generic_object_selector(Widget& parent, Indexer& indexer, Ref& result)
	{
		bool changed = false;
		Widget& self = ui::sheet(parent);
		for(size_t id = 0; id < indexer.m_objects.size(); ++id)
			if(indexer.m_objects[id].m_value)
			{
				if(object_item(self, indexer.m_objects[id], result))
				{
					result = indexer.m_objects[id];
					changed = true;
				}
			}
		return changed;
	}

	bool object_selector(Widget& parent, Indexer& indexer, Ref& result)
	{
		if(DispatchSelector::me().check(result))
			return DispatchSelector::me().dispatch(result, parent);
		else
			return generic_object_selector(parent, indexer, result);
	}

	void object_indexer_modal(Widget& parent, Indexer& indexer)
	{
		Widget& self = ui::select_list(parent);
		object_indexer(self, indexer);
	}

	bool object_selector(Widget& parent, Ref& result)
	{
		Widget& self = ui::sheet(parent);
		return object_selector(self, indexer(type(result)), result);
	}

	bool object_selector_modal(Widget& screen, Widget& parent, Ref& result)
	{
		enum Modes { PICK = 1 << 0 };

		bool changed = false;
		if(ui::modal_button(screen, parent, ".", PICK))
		{
			string title = "Select " + string(type(result).m_name);
			Widget& modal = ui::auto_modal(parent, PICK, { 600, 400 });
			
			Widget& self = *ui::scroll_sheet(*modal.m_body).m_body;
			changed = object_selector(self, indexer(type(result)), result);
			if(ui::button(*modal.m_body, "Done").activated())
				screen.m_switch &= ~PICK;
		}
		return changed;
	}
}


#ifdef MUD_MODULES
module mud.uio;
#else
#endif

namespace mud
{
	void object_injector(Widget& parent, Injector& injector)
	{
		Widget& self = ui::sheet(parent);
		call_edit(self, injector);
	}

	struct CreatorState : public NodeState
	{
		CreatorState(Type& type) : m_type(0), m_injector(make_unique<Injector>(type)) {}
		uint32_t m_type;
		unique<Injector> m_injector;
	};

	bool object_creator(Widget& parent, Injector& injector)
	{
		Widget& self = ui::widget(parent, styles().sheet, &injector);
		
		Table& fields = ui::columns(self, { 0.4f, 0.6f });
		call_edit(fields, injector);

		if(ui::button(self, "Create").activated())
		{
			if(false)//injector.m_constructor.validate(injector.m_arguments, 1))
			{
				injector.injectpool();
				return true;
			}
		}

		return false;
	}

	bool object_switch_creator(Widget& parent, array<Type*> types)
	{
		Widget& self = ui::sheet(parent);
		ui::title(self, "Create Object");

		CreatorState& state = self.state<CreatorState>(*types[0]);

		if(type_selector(self, state.m_type, types))
			state.m_injector = make_unique<Injector>(*types[state.m_type]);

		return object_creator(self, *state.m_injector);
	}

	bool object_creator(Widget& parent, Creator& creator)
	{
		Widget& self = ui::sheet(parent);

		ui::title(self, creator.m_prototype ? creator.m_prototype->m_name : creator.m_type.m_name);

		Table& fields = ui::table(self, { "field", "value" }, { 0.3f, 0.7f });
		call_edit(fields, creator.injector());

		if(ui::button(self, "Create").activated())
		{
			creator.m_injector->injectpool();
			return true;
		}

		return false;
	}

	struct ObjectCreatorState : public NodeState
	{
		ObjectCreatorState(Type& type) : m_creator(type) {}
		Creator m_creator;
	};

	bool object_creator(Widget& parent, Type& type)
	{
		Widget& self = ui::sheet(parent);
		ObjectCreatorState& state = self.state<ObjectCreatorState>(type);
		return object_creator(self, state.m_creator);
	}

	struct MetaObjectCreatorState : public NodeState
	{
		Type* m_type = nullptr;
	};

	void meta_object_creator(Widget& parent)
	{
		Widget& self = ui::sheet(parent);
		MetaObjectCreatorState& state = self.state<MetaObjectCreatorState>();

		for(Type* type : System::instance().m_types)
			if(is_root_type(*type) && !cls(*type).m_constructors.empty())
			{
				if(object_item(self, Ref(type)).activated())
					state.m_type = type;
			}

		if(state.m_type)
			object_creator(self, *state.m_type);
	}
}


#ifdef MUD_MODULES
module mud.uio;
#else
#endif

//#define EDIT_MEMBER_REF

namespace mud
{
	vector<EditSpec> g_edit_specs = vector<EditSpec>(c_max_types);

	EditSpec::EditSpec(Class& cls)
		: m_setup(true)
	{
		bool big_struct = is_struct(*cls.m_type) && cls.m_members.size() > 4;
		if(big_struct || is_object(*cls.m_type))
			m_nest_mode[0] = EditNestMode::Embed;
		else
			m_nest_mode[0] = EditNestMode::Inline;

		//bool custom_edit = DispatchInput::me.check(*cls.m_type);
		//m_row_mode = big_struct || is_object(*cls.m_type) ? EditNestMode::Embed : EditNestMode::Inline;
	}

	struct EditState : public NodeState
	{
		Ref object = {};
	};

	bool member_edit(Widget& parent, Ref object, Member& member, EditorHint hint = EditorHint::Inline)
	{
#ifdef EDIT_MEMBER_REF
		Ref value = member.cast_get(object);
		bool changed = any_edit(parent, value, member.is_link() | member.is_pointer(), hint);
#else
		//Var value = member.safe_get(object);
		Var value = member.get(object);
		bool changed = any_edit(parent, value.m_ref, member.is_link() | member.is_pointer(), hint);

		if(changed && member.is_mutable() && !member.is_component())
			member.cast_set(object, value);
#endif
		
		return changed;
	}

	bool member_edit_row(Widget& parent, Ref object, Member& member)
	{
		Widget& self = ui::table_row(parent);
		ui::label(self, member.m_name);
		return member_edit(self, object, member);
	}

	bool member_edit_toggle(Widget& parent, Ref object, Member& member)
	{
		Widget& self = ui::row(parent);
		if(ui::modal_button(self, self, "Edit", 1))
		{
			Widget& modal = ui::modal(self.parent_modal());
			return member_edit(modal, object, member, EditorHint::Table);
		}
		return false;
	}

	bool member_edit_embed(Widget& parent, Ref object, Member& member)
	{
		return member_edit(parent, object, member, EditorHint::Rows);
	}

	bool member_edit_nested(Widget& parent, Ref object, Member& member)
	{
		//Widget& row = ui::table_row(parent);
		Widget& row = ui::table_separator(parent);
		Widget* body = ui::tree_node(row, member.m_name, false, true).m_body;
		if(body)
			return member_edit(*body, object, member, EditorHint::Rows);
		return false;
	}

	EditNestMode nest_edit_mode(Member& member, size_t mode)
	{
		if(member.is_component()) return EditNestMode::Embed;
		if(member.is_link() || is_basic(*member.m_type)) return EditNestMode::Inline;

		if(!g_edit_specs[member.m_type->m_id].m_setup)
			g_edit_specs[member.m_type->m_id] = { cls(*member.m_type) };

		return g_edit_specs[member.m_type->m_id].m_nest_mode[mode];
	}

	bool object_edit_rows(Widget& parent, Table& table, Ref object)
	{
		UNUSED(parent);
		bool changed = false;

		auto member_edit = [&](Member& member)
		{
			EditNestMode mode = nest_edit_mode(member, 0);
			if(mode == EditNestMode::Embed)
				changed |= member_edit_nested(table, object, member);
			else if(mode == EditNestMode::Modal)
				changed |= member_edit_toggle(table, object, member);
			else
				changed |= member_edit_row(table, object, member);
		};

		for(Member& member : cls(object).m_members)
			if(!member.is_component() && member.is_mutable())
				member_edit(member);

		for(Member& member : cls(object).m_members)
			if(member.is_component() && member.is_mutable())
				member_edit(member);

		return changed;
	}

	bool object_edit_rows(Widget& parent, Ref object)
	{
		return object_edit_rows(parent, as<Table>(parent), object);
	}

	bool object_edit_inrow(Widget& row, Ref object)
	{
		bool changed = false;

		auto member_edit = [&](Member& member)
		{
			EditNestMode mode = nest_edit_mode(member, 1);
			if(mode == EditNestMode::Embed)
				changed |= member_edit_embed(row, object, member);
			else if(mode == EditNestMode::Modal)
				changed |= member_edit_toggle(row, object, member);
			else
				changed |= mud::member_edit(row, object, member);
		};

		for(Member& member : cls(object).m_members)
			if(!member.is_component() && member.is_mutable())
				member_edit(member);

		for(Member& member : cls(object).m_members)
			if(member.is_component() && member.is_mutable())
				member_edit(member);

		return changed;
	}

	bool object_edit_inline(Widget& parent, Ref object)
	{
		Widget& row = ui::widget(parent, styles().wrap_button);
		return object_edit_inrow(row, object);
	}

	Widget& object_edit_inline_item(Widget& parent, Ref object)
	{
		Widget& row = ui::table_row(parent);
		object_edit_inrow(row, object);
		return row;
	}

	bool object_edit_columns(Widget& parent, Ref object)
	{
		static float columns[2] = { 0.33f, 0.67f };
		Table& self = ui::columns(parent, { columns, 2 });
		return object_edit_rows(parent, self, object);
	}

	bool object_edit_table(Widget& parent, Ref object)
	{
		static cstring columns[2] = { "field", "value" };
		static float spans[2] = { 0.4f, 0.6f };
		Table& self = ui::table(parent, { columns, 2 }, { spans, 2 });
		return object_edit_rows(parent, self, object);
	}

	bool object_edit_expandbox(Widget& parent, Ref object)
	{
		Widget* body = ui::expandbox(parent, object.m_type->m_name, true).m_body;
		if(body)
			return object_edit_columns(*body, object);
		return false;
	}

	bool object_edit(Widget& parent, Ref object, EditorHint hint)
	{
		if(hint == EditorHint::Table)
			return object_edit_columns(parent, object);
		else if(hint == EditorHint::Rows)
			return object_edit_columns(parent, object);
		else //if(hint == EditorHint::Inline)
			return object_edit_inline(parent, object);
	}

	bool entity_edit(Widget& parent, Entity entity, EditorHint hint)
	{
		UNUSED(hint);
		bool changed = false;

		static cstring columns[2] = { "field", "value" };
		static float spans[2] = { 0.4f, 0.6f };
		Table& self = ui::table(parent, { columns, 2 }, { spans, 2 });

		EntityStream& stream = s_ecs[entity.m_ecs]->stream(entity);
		uint32_t index = stream.m_handles[entity];
		for(auto& buffer : stream.m_buffers)
		{
			Widget& row = ui::table_separator(self);
			Widget* body = ui::tree_node(row, buffer->m_type->m_name, false, true).m_body;
			if(body)
				changed |= object_edit_columns(*body, buffer->get(index));
		}

		return changed;
	}

	bool inspector(Widget& parent, Entity entity)
	{
		Section& self = section(parent, "Entity Inspector", true);
		return entity_edit(*self.m_body, entity);
	}

	bool inspector(Widget& parent, Ref object)
	{
		Section& self = section(parent, "Inspector", true);
		if(object.m_type->is<EntityRef>())
			return inspector(parent, { as_ent(object), 0 });
		else
			return object_edit_columns(*self.m_body, object);
	}

	bool inspector(Widget& parent)
	{
		Section& self = section(parent, "Inspector", true);
		EditState& state = self.state<EditState>();
		if(state.object)
			return object_edit_columns(*self.m_body, state.object);
		return false;
	}

	void multi_object_edit(Widget& parent, Type& type, vector<Ref> objects)
	{
		ScrollSheet& scroll_sheet = ui::scroll_sheet(parent);
		Widget& table = ui::table(*scroll_sheet.m_body, to_array(cls(type).m_field_names), {});

		for(Ref object : objects)
			object_edit_inline(table, object);
	}

	void multi_inspector(Widget& parent, Type& type, vector<Var>& objects, size_t& selected)
	{
		enum Modes { CREATE = 1 << 0, TYPE_INFO = 1 << 1 };

		Section& self = section(parent, (string(type.m_name) + " Library").c_str());

		if(ui::modal_button(self, *self.m_toolbar, "Type Info", TYPE_INFO))
		{
			Widget& modal = ui::auto_modal(self, TYPE_INFO, { 600, 400 });
			meta_edit(*modal.m_body, type);
		}

		if(ui::button(*self.m_toolbar, "Add").activated())
			objects.push_back(meta(type).m_empty_var);

		if(ui::modal_button(self, *self.m_toolbar, "Create", CREATE))
		{
			Widget& modal = ui::auto_modal(self, CREATE);
			bool done = object_creator(modal, type);
			UNUSED(done);
		}

		Widget& board = ui::board(*self.m_body);

		ScrollSheet& scroll_sheet = ui::scroll_sheet(board);
		Widget& table = ui::table(*scroll_sheet.m_body, to_array(cls(type).m_field_names), {});

		for(size_t i = 0; i < objects.size(); ++i)
		{
			Widget& row = object_edit_inline_item(table, objects[i]);
			row.set_state(SELECTED, selected == i);
			if(row.activated())
				selected = i;
		}
	}
}

#ifndef MUD_CPP_20
#include <stl/string.h>
#endif

#ifdef MUD_MODULES
module mud.uio;
#else
#endif

#include <cstring>

namespace mud
{
	struct CallableEditState : public NodeState
	{
		CallableEditState(Callable& callable) : m_call(callable) {}
		CallableEditState(Callable& callable, Ref object) : m_call(callable, object) {}
		Call m_call;
	};

	bool call_edit(Widget& parent, Call& call)
	{
		bool method = strcmp(call.m_callable->m_params[0].m_name, "self") == 0;
		uint16_t offset = method ? 1 : 0;
		for(uint16_t i = offset; i < call.m_callable->m_params.size(); ++i)
		{
			const Param& param = call.m_callable->m_params[i];
			bool link = is_object(type(param.default_val())) || param.nullable();
			field_edit(parent, param.m_name, call.m_arguments[i].m_ref, link);
		}

		/*uint16_t offset = call.m_arguments.size() - call.m_callable->m_params.size();
		for(Param& param : call.m_callable->m_params)
			field_edit(parent, param.m_name, call.m_arguments[param.m_index + offset], param.nullable());*/
		return false;
	}

	void callable_edit(Widget& parent, Callable& callable)
	{
		Widget& self = ui::row(parent);
		CallableEditState& state = self.state<CallableEditState>(callable);
		call_edit(self, state.m_call);
	}

	void function_edit(Widget& parent, Function& function)
	{
		callable_edit(parent, function);
	}

	void method_edit(Widget& parent, Ref object, Method& method)
	{
		Widget& self = ui::row(parent);
		CallableEditState& state = self.state<CallableEditState>(method, object);
		if(ui::button(self, method.m_name).activated())
			state.m_call();
		call_edit(self, state.m_call);
	}

	void method_edit_modal(Widget& parent, Ref object, Method& method)
	{
		enum Modes { CALL = 1 << 0 };
		string name = "Call method " + string(method.m_object_type->m_name) + "::" + method.m_name;
		
		if(ui::modal_button(parent, parent, "Call", CALL))
		{
			Widget& modal = ui::auto_modal(parent, CALL, { 600, 400 });
			method_edit(modal, object, method);
		}
	}

	void method_trigger(Widget& parent, Ref object, Method& method)
	{
		if(ui::modal_button(parent, parent, method.m_name, uint32_t(1 << 0)))
			method_edit_modal(parent, object, method);
	}

	void method_hook(Widget& parent, Ref object, Method& method)
	{
		method_edit(parent, object, method);
	}
}


#ifdef MUD_MODULES
module mud.uio;
#else
//#include <type/Entity.h>
#endif

namespace mud
{
	static void text_skin(InkStyle& style, const Colour& colour)
	{
		static float text_size = 15.f;
		style.m_empty = false;
		//style.m_text_font = "veramono-bold";
		style.m_text_colour = colour;
		style.m_text_size = text_size;
	}

	struct MetaStyles
	{
		Style element = { "Element", styles().row, [](Layout& l) { l.m_spacing = vec2{ 5.f, 0.f }; } };

		Style sheet = { "Frame", styles().stack, [](Layout& l) { l.m_padding = vec4(20.f); l.m_spacing = vec2(10.f); } };
		Style frame = { "Frame", styles().stack, [](Layout& l) { l.m_padding = vec4(5.f); l.m_spacing = vec2(10.f); }, [](InkStyle& l) { l.m_empty = false; l.m_background_colour = to_colour(25, 26, 31); } };
		
		Style label			= { "Syntax", styles().label,{}, [](InkStyle& l) { text_skin(l, Colour::White); } };
		Style type			= { "Type", styles().label, {}, [](InkStyle& l) { text_skin(l, to_colour(255, 0, 78)); } }; // to_colour(125, 125, 125)
		Style function		= { "Function", styles().label,{}, [](InkStyle& l) { text_skin(l, to_colour(255, 0, 78)); } }; // to_colour(106, 176, 255)
		Style identifier	= { "Word", styles().label, {}, [](InkStyle& l) { text_skin(l, to_colour(106, 176, 255)); } };
		Style syntax		= { "Syntax", styles().label, {}, [](InkStyle& l) { text_skin(l, Colour::White); } }; // Colour::White
		Style argument		= { "Argument", styles().label, {}, [](InkStyle& l) { text_skin(l, to_colour(227, 131, 228)); } }; // Colour::White
		Style field			= { "Field", styles().label, {}, [](InkStyle& l) { text_skin(l, to_colour(227, 131, 228)); } }; // Colour::White
		Style number		= { "Number", styles().label, {}, [](InkStyle& l) { text_skin(l, to_colour(227, 131, 228)); } }; // Colour::White
	};

	MetaStyles& meta_styles() { static MetaStyles styles; return styles; }

	void set_meta_palette(const vector<uint32_t>& palette)
	{
		meta_styles().label.skin().m_text_colour		= from_rgba(palette[size_t(CodePalette::Word)]);
		meta_styles().type.skin().m_text_colour			= from_rgba(palette[size_t(CodePalette::Identifier)]);
		meta_styles().function.skin().m_text_colour		= from_rgba(palette[size_t(CodePalette::Function)]);
		meta_styles().identifier.skin().m_text_colour	= from_rgba(palette[size_t(CodePalette::Identifier)]);
		meta_styles().syntax.skin().m_text_colour		= from_rgba(palette[size_t(CodePalette::Punctuation)]);
		meta_styles().argument.skin().m_text_colour		= from_rgba(palette[size_t(CodePalette::Parameter)]);
		meta_styles().field.skin().m_text_colour		= from_rgba(palette[size_t(CodePalette::Field)]);
		meta_styles().number.skin().m_text_colour		= from_rgba(palette[size_t(CodePalette::Number)]);
	}

	void meta_type(Widget& parent, Meta& meta)
	{
		Widget& row = ui::widget(parent, meta_styles().element);
		ui::item(row, meta_styles().syntax, to_string(meta.m_type_class).c_str());
		if(!meta.m_namespace->is_root())
		{
			ui::item(row, meta_styles().type, meta.m_namespace->m_name);
			ui::item(row, meta_styles().syntax, "::");
		}
		ui::item(row, meta_styles().type, meta.m_name);

		Widget& size = ui::widget(parent, meta_styles().element);
		ui::item(size, meta_styles().type, "size");
		ui::item(size, meta_styles().number, to_string(meta.m_size).c_str());
	}

	void meta_description(Widget& parent, Meta& meta)
	{
		static float columns[2] = { 0.2f, 0.8f };
		Table& self = ui::columns(parent, { columns, 2 });
		ui::field_label(self, "name", meta.m_name);
		ui::field_label(self, "namespace", meta.m_namespace->m_name);
		ui::enum_field<TypeClass>(self, "type class", meta.m_type_class);
		ui::input_field<size_t>(self, "size", meta.m_size);
	}

	void meta_description(Widget& parent, Type& type)
	{
		return meta_description(parent, meta(type));
	}

	void meta_callable(Widget& parent, Callable& callable, bool skip_first = false, bool returns = true)
	{
		Widget& sheet = ui::widget(parent, styles().sheet, &callable);

		Widget& row = ui::widget(sheet, meta_styles().element);
		//ui::item(row, meta_styles().syntax, "Function");
		if(returns)
		{
			ui::item(row, meta_styles().type, callable.m_return_type.m_type->m_name);
		}
		ui::item(row, meta_styles().function, callable.m_name);
		ui::item(row, meta_styles().syntax, "(");
		for(Param& param : callable.m_params)
		{
			if(skip_first && param.m_index == 0)
				continue;
			ui::item(row, meta_styles().type, param.default_val() == Ref() ? "Ref" : param.m_type->m_name);
			ui::item(row, meta_styles().argument, param.m_name);
			if(&param != &callable.m_params.back())
				ui::item(row, meta_styles().syntax, ",");
		}
		ui::item(row, meta_styles().syntax, ")");
	}

	void meta_function(Widget& parent, Function& function)
	{
		return meta_callable(parent, function);
	}

	void meta_method(Widget& parent, Method& method)
	{
		return meta_callable(parent, method, true);
	}

	void meta_constructors(Widget& parent, Class& cls)
	{
		Widget& self = ui::widget(parent, meta_styles().frame);

		for(Constructor& constructor : cls.m_constructors)
			meta_callable(self, constructor, true, false);
	}

	void meta_methods(Widget& parent, Class& cls)
	{
		Widget& self = ui::widget(parent, meta_styles().frame);

		for(Method& method : cls.m_methods)
			meta_method(self, method);
	}

	void meta_fields(Widget& parent, Class& cls)
	{
		Widget& self = ui::widget(parent, meta_styles().frame);
		Widget& table = self;
		//Widget& table = ui::columns(self, { 0.3f, 0.7f });

		for(Member& member : cls.m_members)
		{
			Widget& row = ui::widget(table, meta_styles().element);
			ui::item(row, meta_styles().type, member.m_type->m_name);
			ui::item(row, meta_styles().field, member.m_name);
		}
	}

	void meta_synopsis(Widget& parent, Function& function)
	{
		return meta_function(parent, function);
	}

	void meta_synopsis(Widget& parent, Method& method)
	{
		return meta_method(parent, method);
	}

	void meta_enum(Widget& parent, Enum& enu)
	{
		Widget& self = ui::widget(parent, meta_styles().frame);
		
		for(size_t i = 0; i < enu.m_names.size(); ++i)
		{
			Widget& row = ui::widget(self, meta_styles().element);
			ui::item(row, meta_styles().identifier, enu.m_names[i]);
			ui::item(row, meta_styles().syntax, "=");
			ui::item(row, meta_styles().number, to_string(enu.m_values[i]).c_str());
		}
	}

	void meta_class(Widget& parent, Class& cls)
	{
		//meta_description(parent, type);
		if (!cls.m_constructors.empty())
		{
			ui::item(parent, meta_styles().label, "constructors:");
			meta_constructors(parent, cls);
		}
		if (!cls.m_methods.empty())
		{
			ui::item(parent, meta_styles().label, "methods:");
			meta_methods(parent, cls);
		}
		if (!cls.m_members.empty())
		{
			ui::item(parent, meta_styles().label, "fields:");
			meta_fields(parent, cls);
		}
	}

	void meta_synopsis(Widget& parent, Type& type)
	{
		Widget& self = ui::widget(parent, meta_styles().frame, &type);

		Widget& row = ui::widget(self, meta_styles().element);
		ui::item(row, meta_styles().syntax, to_string(meta(type).m_type_class).c_str());
		ui::item(row, meta_styles().type, type.m_name);
		if(g_enu[type.m_id])
			meta_enum(self, enu(type));
		if (g_class[type.m_id])
			meta_class(self, cls(type));
	}

	bool type_browser(Widget& parent, Type*& selected)
	{
		Widget& list = *ui::scroll_sheet(parent).m_body;

		for(Module* m : system().m_modules)
			for(Type* type : m->m_types)
			{
				cstring elements[1] = { type->m_name };
				if(ui::multi_button(list, { elements, 1 }).activated())
				{		
					selected = type;
					return true;
				}
			}
		return false;
	}

	struct MetaEditState : public NodeState
	{
		MetaEditState() {}
		MetaEditState(Type& type) : m_type(&type) {}
		Type* m_type = nullptr;
	};

	void class_edit(Widget& parent, Class& cls)
	{
		Widget& self = ui::widget(parent, meta_styles().frame);

		meta_type(self, meta(*cls.m_type));
		meta_class(self, cls);
	}

	void meta_edit(Widget& parent, Type& type)
	{
		enum Modes { Browse = 1 << 0 };

		Section& self = section(parent, ("Type Info : " + string(type.m_name)).c_str());
		MetaEditState& state = self.state<MetaEditState>(type);

		if (ui::modal_button(self, *self.m_toolbar, "Browse", Browse))
		{
			Widget& modal = ui::modal(parent.parent_modal(), { 400, 800 });
			bool done = type_browser(*modal.m_body, state.m_type);
			if (done || !modal.m_open)
				self.m_switch &= ~Browse;
		}

		class_edit(*self.m_body, cls(*state.m_type));
	}

	void meta_browser(Widget& parent, Module& m)
	{
		UNUSED(parent); UNUSED(m);
	}

	void meta_browser(Widget& parent)
	{
		enum Mode : uint32_t { Basetypes = 0, Enums, Classes, Functions };

		static Ref selected = {};

		//Widget& self = ui::dockspace(parent);
		Widget& self = ui::board(parent);

		Widget& left = ui::layout_span(self, 0.3f);
		Widget& right = ui::layout_span(self, 0.7f);

		Widget& table = ui::columns(left, { 0.3f, 0.7f });

		static Mode mode = Classes;
		ui::dropdown_field(table, "Browse:", { "Basetypes", "Enums", "Classes", "Functions" }, (uint32_t&) mode);

		static map<Module*, bool> modules;

		Widget& row = ui::row(table);
		ui::label(row, "Modules");
		Widget& drop = ui::dropdown(row, ui::dropdown_styles().dropdown_input, "...", ui::PopupFlags::AutoModal);
		if(drop.m_body)
		{
			for(Module* m : System::instance().m_modules)
			{
				Widget& droprow = ui::row(*drop.m_body);
				ui::checkbox(droprow, modules[m]);
				ui::label(droprow, m->m_name);
			}
		}

		Widget& sheet = ui::widget(left, styles().sheet, (void*) mode);
		Widget& meta_list = *ui::scroll_sheet(sheet).m_body;

		auto choice = [](Widget& parent, Ref object, cstring name, Ref& selected) -> Widget&
		{
			Widget& element = ui::element(parent, object);
			ui::select_logic(element, object, selected);
			return ui::multi_item(element, { name });
		};

		for(Module* m : System::instance().m_modules)
			if(modules[m])
			{
				if(mode < Functions)
				{
					for(Type* type : m->m_types)
					{
						if((is_base_type(*type) && mode == Basetypes) || (is_enum(*type) && mode == Enums) || (is_class(*type) && mode == Classes))
							choice(meta_list, Ref(type), type->m_name, selected);
					}
				}
				else
				{
					for(Function* function : m->m_functions)
						choice(meta_list, Ref(function), function->m_name, selected);
				}
			}

		Widget& info = ui::widget(right, meta_styles().sheet, (void*)mode);
		if(Type* type = try_val<Type>(selected))
		{
			//if(is_basetype(*type))
			//	type_edit(right, *type);
			if(is_enum(*type))
				meta_enum(info, enu(*type));
			if(is_class(*type))
				class_edit(info, cls(*type));
		}
		if(Function* function = try_val<Function>(selected))
			meta_function(info, *function);
	}

	void type_browser(Widget& parent)
	{
		static Type* selected = nullptr;

		Widget& self = ui::board(parent);
		Widget& list = *ui::scroll_sheet(self).m_body;

		for(Module* m : system().m_modules)
			for(Type* type : m->m_types)
			{
				if(ui::button(list, type->m_name).activated())
					selected = type;
			}

		if(selected)
			meta_edit(self, *selected);
	}
}


#ifdef MUD_MODULES
module mud.uio;
#else
#endif

namespace mud
{
	ScriptEditor::ScriptEditor()
	{
		set_meta_palette(TextEdit::OkaidaPalette());
	}

	ScriptEditor::~ScriptEditor()
	{}

	void ScriptEditor::reset_interpreters(LuaInterpreter& lua, WrenInterpreter& wren)
	{
		m_lua = &lua;
		m_wren = &wren;

		for(Script* script : m_scripts)
			if(TextScript* text_script = try_as<TextScript>(*script))
			{
				if(text_script->m_language == Language::Lua)
					text_script->m_interpreter = m_lua;
				else if(text_script->m_language == Language::Wren)
					text_script->m_interpreter = m_wren;
			}
	}

	void ScriptEditor::open(Script& script)
	{
		vector_add(m_scripts, &script);
	}

	void ScriptEditor::close(Script& script)
	{
		vector_remove(m_scripts, &script);
	}

	TextScript& ScriptEditor::create_script(cstring name, Language language, Signature signature)
	{
		TextScript& script = global_pool<TextScript>().construct(name, language, signature);
		if(language == Language::Lua)
			script.m_interpreter = m_lua;
		else if(language == Language::Wren)
			script.m_interpreter = m_wren;
		this->open(script);
		return script;
	}

	VisualScript& ScriptEditor::create_visual(cstring name, Signature signature)
	{
		VisualScript& script = global_pool<VisualScript>().construct(name, signature);
		this->open(script);
		return script;
	}

	vector<string> lua_words()
	{
		return { "print" };
	}

	vector<string> meta_words()
	{
		vector<string> symbols = vector_convert<string>(System::instance().meta_symbols());
		vector_extend(symbols, lua_words());
		return symbols;
	}

	void script_edit_output(Widget& parent, Interpreter& interpreter)
	{
		Widget& self = ui::sheet(parent);
		ui::title_header(self, "Output");

		static string output = "";
		output = interpreter.flush();

		ui::text_box(self, styles().type_in, output, true, 5);
	}

	void script_edit_hover(TextEdit& edit)
	{
		if(edit.m_hovered_word != "")
		{
			vec2 hover_at = rect_offset(edit.m_hovered_word_rect) + vec2{ 0.f, rect_h(edit.m_hovered_word_rect) };

			//ui::rectangle(edit, edit.m_hovered_word_rect);
			
			Function* function = system().find_function(edit.m_hovered_word.c_str());
			Type* type = system().find_type(edit.m_hovered_word.c_str());
			Type* lowertype = system().find_type(to_lower(edit.m_hovered_word).c_str());

			if(function || type || lowertype)
			{
				if(Widget* popup = ui::hoverbox(edit, hover_at))
				{
					if(function)
						meta_synopsis(*popup, *function);
					else if(type || lowertype)
						meta_synopsis(*popup, type ? *type : *lowertype);
				}
			}
		
			if(MouseEvent mouse_event = edit.mouse_event(DeviceType::MouseRight, EventType::Stroked))
			{
			}
		}
	}

#if 0
	Widget& error_tooltip(Widget& parent)
	{
		Widget* tooltip = ui::tooltip();
		ui::label("Error at line %d:", errorIt->first); // Colour(1.0f, 0.2f, 0.2f, 1.0f)
		ui::label("%s", errorIt->second.c_str()); // Colour(1.0f, 1.0f, 0.2f, 1.0f)
	}
#endif

	Section& script_edit_code(Widget& parent, TextScript& script)
	{
		//auto run = [&] { script({}); };
		auto reload = [&] { script.m_dirty = true; };
		//actions.push_back({ "Run",  });
		Section& self = section(parent, script.m_name.c_str());

		if(section_action(self, "Reload"))
			reload();

		vector<string> known_words = meta_words();
		TextEdit& edit = ui::code_edit(*self.m_body, script.m_script, 0, &known_words);
		
		if(script.m_language == Language::Lua)
			edit.m_language = &LanguageLua();
		else if(script.m_language == Language::Wren)
			edit.m_language = &LanguageWren();
		
		if(edit.char_stroke(Key::S, InputMod::Ctrl))
			reload();

		if(edit.m_entered)
			script.m_script = ui::auto_indent(edit);

		edit.m_text.m_markers.clear();
		for(const auto& line_error : script.m_compile_errors)
		{
			const ScriptError& error = line_error.second;
			edit.m_text.m_markers.push_back({ TextMarkerKind::Error, error.m_line, error.m_column, error.m_message, uint16_t(CodePalette::Error), uint16_t(CodePalette::ErrorMarker) });
		}

		for(const auto& line_error : script.m_runtime_errors)
		{
			const ScriptError& error = line_error.second;
			edit.m_text.m_markers.push_back({ TextMarkerKind::Error, error.m_line, error.m_column, error.m_message, uint16_t(CodePalette::Error), uint16_t(CodePalette::ErrorMarker) });
		}

		script_edit_hover(edit);

		return self;
	}

	Section& script_edit(Widget& parent, TextScript& script)
	{
		return script_edit_code(parent, script);
		//Widget& span_0 = ui::layout_span(parent, 0.8f);
		//script_edit_code(span_0, script, actions);
		//Widget& span_1 = ui::layout_span(parent, 0.2f);
		//script_edit_output(span_1, *script.m_interpreter);
	}

	void script_tab(Tabber& parent, ScriptEditor& editor, Script& script)
	{
		if(Widget* tab = ui::tab(parent, script.m_name.c_str()))
		{
			Section& edit = script.m_type.is<VisualScript>()
				? visual_script_edit(*tab, as<VisualScript>(script))
				: script_edit(*tab, as<TextScript>(script));

			if(section_action(edit, "Close"))
				editor.close(script);
		}
	}

	void script_editor(Widget& parent, ScriptEditor& editor)
	{
		enum Modes { Open = 1 << 0, Browse = 1 << 1 };

		Section& self = section(parent, "Script Editor");

		if(section_action(self, "New Script"))
			editor.create_script(("Untitled " + to_string(editor.m_scripts.size())).c_str(), Language::Lua);
		if(section_action(self, "New Visual Script"))
			editor.create_visual(("Untitled " + to_string(editor.m_scripts.size())).c_str());

		if(ui::modal_button(self, *self.m_toolbar, "Open Script", Open))
		{
			Widget& modal = ui::auto_modal(self, Open, { 600, 400 });
			Ref result = Ref(type<Script>());
			if(object_selector(*modal.m_body, result))
			{
				editor.open(val<Script>(result));
				self.m_switch &= ~Open;
			}
		}

		if (ui::modal_button(self, *self.m_toolbar, "Browse API", Browse))
		{
			Widget& modal = ui::auto_modal(self, Browse, { 600, 600 });
			meta_browser(*modal.m_body);
			if(ui::button(*modal.m_body, "Close").activated())
				self.m_switch &= ~Browse;
		}

		Tabber& tabber = ui::tabber(*self.m_body);
		for(Script* script : editor.m_scripts)
			script_tab(tabber, editor, *script);
	}

}


#ifdef MUD_MODULES
module mud.uio;
#else
#include <stl/string.h>
#endif

namespace mud
{
	void structure_node(Widget& parent, Ref object, vector<Ref>& selection)
	{
		TreeNode& self = ui::tree_node(parent, { object_icon(object).c_str(), object_name(object).c_str() }, false, false);
		
		self.set_state(SELECTED, vector_has(selection, object));
		
		if(self.m_header->activated())
			vector_select(selection, object);
		
		//object_item(self, object);

		for(auto& member : cls(object).m_members)
			if(member.is_structure() && is_iterable(*member.m_type))
			{
				Var value = member.get(object);
				iter(value).iterate(value, [&](Ref element) {
					structure_node(self, element, selection);
				});
			}
	}

	void structure_view(Widget& parent, Ref object, vector<Ref>& selection)
	{
		ScrollSheet& sheet = ui::scroll_sheet(parent);
		Widget& tree = ui::tree(*sheet.m_body);
		structure_node(tree, object, selection);
	}
}


#ifdef MUD_MODULES
module mud.uio;
#else
#endif

namespace mud
{
	void ui_debug_modal(Widget& parent, Widget& target)
	{
		Widget* current_node = &parent;
		Widget* current_target = &target.ui();
		while(current_target && current_node)
		{
			string elements[2] = { current_target->m_frame.d_style->name(), to_string(current_target->m_control.m_mask) };
			current_node = ui::tree_node(*current_node, { elements[0].c_str(), elements[1].c_str() }).m_body;
			current_target = static_cast<Widget*>(current_target->m_control.m_modal);
		}
	}

	void ui_debug_layout_node(Widget& parent, Widget& target, Widget*& selected)
	{
		for(auto& widget : target.m_nodes)
		{
			string size = "size : " + truncate_number(to_string(widget->m_frame.m_size.x)) + ", " + truncate_number(to_string(widget->m_frame.m_size.y));
			TreeNode& node = ui::tree_node(parent, { widget->m_frame.d_style->name(), size.c_str() });
			node.m_header->set_state(SELECTED, selected == widget.get());
			if(node.m_header->activated())
				selected = widget.get();
			if(node.m_body)
				ui_debug_layout_node(*node.m_body, *widget, selected);
		}
	}

	void ui_debug_layout(Widget& parent, Widget& target, Widget*& selected)
	{
		ScrollSheet& scroll_sheet = ui::scroll_sheet(parent);
		ui_debug_layout_node(*scroll_sheet.m_body, target, selected);
	}

	void ui_debug(Widget& parent, Widget& target)
	{
		static Widget* selected = nullptr;
		static bool selecting = false;

		Section& self = section(parent, "Ui Edit");
		ui::toggle(*self.m_toolbar, selecting, "Select Mode");

		Tabber& tabber = ui::tabber(*self.m_body);
		if(Widget* tab = ui::tab(tabber, "Modal"))
			ui_debug_modal(*tab, target);
		if(Widget* tab = ui::tab(tabber, "Layout"))
			ui_debug_layout(*tab, target, selected);

		if(selected)
			ui::rectangle(parent.ui(), { selected->m_frame.absolute_position(), selected->m_frame.m_size });

		if(selecting)
		{
			Widget* highlighted = target.pinpoint(target.ui().m_mouse.m_pos);
			if(highlighted)
				ui::rectangle(parent.ui(), { highlighted->m_frame.absolute_position(), highlighted->m_frame.m_size });
		}

		if(selected)
		{
			if(Widget* tab = ui::tab(tabber, "Widget"))
				object_edit(*tab, Ref(selected));

			if(Widget* tab = ui::tab(tabber, "Style"))
				object_edit(*tab, Ref(selected->m_frame.d_layout));
			if(Widget* tab = ui::tab(tabber, "Skin"))
				object_edit(*tab, Ref(&selected->m_frame.d_style->skin()));
		}
	}
}


#ifdef MUD_MODULES
module mud.uio;
#else
#endif

namespace mud
{
	template <class T>
	bool range_edit(Widget& parent, Range<T>& value)
	{
		Widget& self = ui::row(parent);
		StatDef<T> def = { T(0), T(100), T(1) };
		bool changed = false;
		changed |= ui::slider_field<T>(self, "min", { value.m_min, def });
		changed |= ui::slider_field<T>(self, "max", { value.m_max, def });
		return changed;
	}

	template <class T>
	bool curve_edit(Widget& parent, vector<T>& keys)
	{
		bool changed = false;
		for(T& key : keys)
			changed |= ui::input<T>(parent, key);
		if(ui::button(parent, "+").activated())
		{
			changed = true;
			keys.push_back(keys.back());
		}
		if(ui::button(parent, "-").activated() && keys.size() > 1)
		{
			changed = true;
			pop(keys);
		}
		return changed;
	}

	template <>
	bool curve_edit(Widget& parent, vector<float>& keys)
	{
		enum Modes { EDIT_CURVE = 1 << 0 };

		if(ui::modal_button(parent, parent, "+", EDIT_CURVE))
		{
			Widget& widget = ui::auto_modal(parent, EDIT_CURVE, { 300.f, 120.f });
			ui::label(*widget.m_body, "Curve Editor");
			return ui::curve_edit(*widget.m_body, array<float>(keys));
		}

		return false;
	}

	template <class T>
	bool value_track_edit(Widget& parent, ValueTrack<T>& track)
	{
		Widget& self = ui::row(parent);
		static cstring modes[4] = { "Constant", "ConstantRandom", "Curve", "CurveRandom" };

		bool changed = false;
		TrackMode mode = track.m_mode;
		changed |= ui::dropdown_input(self, { modes, 4 }, (uint32_t&)mode, true);
		if(changed)
			track.set_mode(mode);

		if(track.m_mode == TrackMode::Constant)
			changed |= ui::input<T>(self, track.m_value);
		else if(track.m_mode == TrackMode::ConstantRandom)
		{
			changed |= ui::input<T>(self, track.m_min);
			changed |= ui::input<T>(self, track.m_max);
		}
		else if(track.m_mode == TrackMode::Curve)
		{
			curve_edit<T>(self, track.m_curve.m_keys);
		}
		return changed;
	}

	template <class T_Val, bool(*Input)(Widget&, T_Val&)>
	bool value_input(T_Val& value, Widget& parent) { return Input(parent, value); }

	template <class T_Val, bool(*Input)(Widget&, AutoStat<T_Val>)>
	bool stat_value_input(T_Val& value, Widget& parent) { return Input(parent, AutoStat<T_Val>(value, { limits<T_Val>::min(), limits<T_Val>::max(), T_Val(1) })); }

	template <class T_Val, bool(*Input)(Widget&, AutoStat<T_Val>), int decimal>
	bool stat_value_input(T_Val& value, Widget& parent) { return Input(parent, AutoStat<T_Val>(value, { limits<T_Val>::min(), limits<T_Val>::max(), T_Val(1) / T_Val(decimal) })); }

	DispatchInput::DispatchInput()
	{
		dispatch_branch<bool>(*this, value_input<bool, ui::input<bool>>);
		dispatch_branch<uint8_t>(*this, stat_value_input<uint8_t, ui::number_input<uint8_t>>);
		dispatch_branch<uint16_t>(*this, stat_value_input<uint16_t, ui::number_input<uint16_t>>);
		dispatch_branch<unsigned int>(*this, stat_value_input<unsigned int, ui::number_input<unsigned int>>);
		dispatch_branch<uint64_t>(*this, stat_value_input<uint64_t, ui::number_input<uint64_t>>);
		dispatch_branch<int>(*this, stat_value_input<int, ui::number_input<int>>);
		dispatch_branch<float>(*this, stat_value_input<float, ui::number_input<float>, 10>);
		dispatch_branch<double>(*this, stat_value_input<double, ui::number_input<double>, 100>);
		// @todo : how to do with cstrings ?
		dispatch_branch<string>(*this, value_input<string, ui::input<string>>);

		dispatch_branch<Colour>(*this, value_input<Colour, ui::color_toggle_edit>);
		dispatch_branch<vec2>(*this, value_input<vec2, ui::vec2_edit>);
		dispatch_branch<vec3>(*this, value_input<vec3, ui::vec3_edit>);
		dispatch_branch<quat>(*this, value_input<quat, ui::quat_edit>);

		dispatch_branch<Range<uint32_t>>(*this, value_input<Range<uint32_t>, range_edit<uint32_t>>);
		dispatch_branch<Range<float>>(*this, value_input<Range<float>, range_edit<float>>);

		dispatch_branch<ValueTrack<float>>(*this, value_input<ValueTrack<float>, value_track_edit<float>>);
		dispatch_branch<ValueTrack<uint32_t>>(*this, value_input<ValueTrack<uint32_t>, value_track_edit<uint32_t>>);
		dispatch_branch<ValueTrack<vec3>>(*this, value_input<ValueTrack<vec3>, value_track_edit<vec3>>);
		dispatch_branch<ValueTrack<quat>>(*this, value_input<ValueTrack<quat>, value_track_edit<quat>>);
		dispatch_branch<ValueTrack<Colour>>(*this, value_input<ValueTrack<Colour>, value_track_edit<Colour>>);

		//dispatch_branch<AutoStat<int>>(valueWidget<AutoStat<int>, ui::slider_input<int>>);
		//dispatch_branch<AutoStat<float>>(valueWidget<AutoStat<float>, ui::slider_input<float>>);

		//dispatch_branch<Image256>([](Image256& image, Wedge& parent) -> object<Widget> { return oconstruct<Figure>(Widget::Input{ &parent }, image); });
	}

	bool type_selector(Widget& parent, uint32_t& type, array<Type*> types)
	{
		vector<cstring> type_names;
		for(size_t i = 0; i < types.size(); ++i)
			type_names.push_back(types[i]->m_name);

		return ui::dropdown_input(parent, to_array(type_names), type);
	}

	bool value_edit(Widget& parent, Ref& value)
	{
		// @kludge ? fix all value == Ref() in the code
		if(!(value == Ref()) && DispatchInput::me.check(value))
			return DispatchInput::me.dispatch(value, parent);
		return false;
	}

	bool none_edit(Widget& parent, Ref& value)
	{
		UNUSED(value);
		ui::label(parent, "None");
		return false;
	}

	bool enum_edit(Widget& parent, Ref& value)
	{
		Enum& e = enu(value);
		uint32_t index = e.index(value);
		//ui::radio_switch(parent, e.m_names, index);
		if(ui::dropdown_input(parent, e.m_names, index))
		{
			e.varn(index, value);
			return true;
		}
		return false;
	}

	bool object_link_edit(Widget& parent, Ref& value)
	{
		Widget& self = ui::row(parent);
		object_button(self, value);
		return object_selector_modal(self, self, value);
	}

	bool sequence_element_edit(Widget& parent, Ref seq, Ref& value)
	{
		object_item(parent, value);
		if(ui::button(parent, "remove").activated())
			sequence(seq).remove(seq, value);
		return false;
	}

	bool sequence_edit(Widget& parent, Ref& value, EditorHint hint)
	{
		enum Modes { Add = 1 << 0 };

		Widget& self = hint == EditorHint::Inline ? ui::row(parent)
												  : ui::sheet(parent);
		bool changed = false;
		iter(value).iterate(value, [&](Ref element) { changed |= value_edit(self, element); });
		if(ui::modal_button(self, self, "add", Add))
		{
			if(meta(*iter(value).m_element_type).m_empty_var)
			{
				sequence(value).add(value, meta(*iter(value).m_element_type).m_empty_var);
				self.m_switch &= ~Add;
				changed |= true;
			}
			else
			{
				Ref selected = Ref(*value.m_type);
				if(object_selector(self, selected))
				{
					sequence(value).add(value, selected);
					self.m_switch &= ~Add;
					changed |= true;
				}
			}
		}
		return changed;
	}

	bool any_edit(Widget& parent, Ref& value, bool link, EditorHint hint)
	{
		//if(is_struct(*value.m_type) && !nullable && !value)
		//	return object_creator(parent, *value.m_type);

		if(value == Ref() || value == Var() || type(value).is<Type>())
			return false;
		else if(DispatchInput::me.check(value))
			return DispatchInput::me.dispatch(value, parent);
		else if(type(value).is<Creator>())
			return object_creator(parent, val<Creator>(value));
		else if(type(value).is<Call>())
			return call_edit(parent, val<Call>(value));
		else if(is_base_type(type(value)))
			return value_edit(parent, value);
		else if(is_sequence(type(value)))
			return sequence_edit(parent, value, hint);
		else if(is_enum(type(value)))
			return enum_edit(parent, value);
		else if(link || value.m_value == nullptr)
			return object_link_edit(parent, value);
		else
			return object_edit(parent, value, hint);
	}

	bool field_edit(Widget& parent, cstring name, Ref& value, bool nullable)
	{
		Widget& self = ui::row(parent);
		ui::label(self, name);
		return any_edit(self, value, nullable);
	}

	bool modal_edit(Widget& parent, uint32_t mode, cstring name, Ref& value, bool nullable, bool confirm)
	{
		Widget& self = ui::modal(parent.parent_modal());
		bool changed = field_edit(self, name, value, nullable);
		bool done = confirm ? ui::button(self, "Done").activated() || !self.m_open
							: changed || !self.m_open;
		if(done)
			parent.m_switch &= ~mode;
		return done;
	}
}
