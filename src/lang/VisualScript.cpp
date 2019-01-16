//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.lang;
#else
#include <infra/Vector.h>
#include <refl/Convert.h>
#include <infra/ToString.h>
#include <infra/Reverse.h>
#include <lang/Types.h>
#include <lang/VisualScript.h>
#endif

#include <algorithm>

#define MUD_DEBUG_SCRIPT

namespace mud
{
	using std::min;

	template <> void to_value<StreamIndex>(const string& str, StreamIndex& val) { UNUSED(str); UNUSED(val); }
	template <> void to_string<StreamIndex>(const StreamIndex& val, string& str) { str += "{"; for(size_t i : val) str += to_string(i) + ","; str.pop_back(); str += "}"; }

	Valve::Valve(Process& process, cstring name, ValveKind kind, Var value, bool nullable, bool reference)
		: m_process(process)
		, m_index(kind == INPUT_VALVE ? process.m_inputs.size() : process.m_outputs.size())
		, m_name(name)
		, m_kind(kind)
		, m_stream(value, nullable, reference)
		, m_edit(false)
	{
		if(kind == INPUT_VALVE)
			process.m_inputs.push_back(this);
		if(kind == OUTPUT_VALVE)
			process.m_outputs.push_back(this);

		if(kind == INPUT_VALVE)
		{
			m_stream.write(value, false);
			m_stream.validate();
			// @todo merge these two operations ? should we validate every time we write ?
		}
	}

	Valve::Valve(Process& process, const Param& param)
		: Valve(process, param.m_name, param.output() ? OUTPUT_VALVE : INPUT_VALVE, param.m_value, param.nullable(), param.reference())
	{}

	Valve::~Valve()
	{
		for(Pipe* pipe : m_pipes)
			m_process.m_script.disconnect(*pipe);
	}

	string Valve::error_info()
	{
		string errors;
		m_stream.visit(true, [&](StreamBranch& branch)
		{
			if(!branch.m_valid)
			{
				//errors += "";
				//errors += "\n";
			}
		});
		if(m_stream.m_num_invalid > 0)
			return to_string(m_stream.m_num_invalid) + " errors\n" + errors;
		else
			return "";
	}

	string Valve::param_info()
	{
		string info;

		info += to_string(m_stream.m_size);
		info += " elements\n";

		m_stream.visit(true, [&](StreamBranch& branch)
		{
			info += to_string(branch.m_index);
			if(branch.m_value == Ref())
				info += "null";
			else
			{
				info += "(" + string(meta(branch.m_value).m_name) + ") ";
				if(g_convert[type(branch.m_value).m_id])
					info += to_string(branch.m_value);
				info += "\n";
			}
		});
		if(info.size() > 1000)
			info.resize(1000);
		return info;
	}

	bool Valve::check(const StreamLocation& location)
	{
		//if(!m_stream.m_type || m_stream.m_type->is(type<Ref>())) return true;
		StreamBranch* stream_branch = m_stream.match_branch(location);
		return stream_branch ? stream_branch->m_valid : false;
	}

	const Var& Valve::read(const StreamLocation& location)
	{
		StreamBranch* stream_branch = m_stream.match_branch(location);
		assert(stream_branch);
		return stream_branch->m_value;
	}

	object<Pipe> Valve::try_connect(Valve& output, StreamModifier modifier)
	{
		if(!m_pipes.empty())
			m_process.m_script.disconnect(*m_pipes[0]);

		return make_object<Pipe>(output, *this, modifier);
	}

	void Valve::propagate()
	{
		for(Pipe* pipe : m_pipes)
			pipe->propagate();
	}

	Pipe::Pipe(Valve& output, Valve& input, StreamModifier modifier)
		: m_output(output)
		, m_input(input)
		, m_modifier(modifier)
	{
		// the output plug is actually the input of the pipe itself
		// conversely the input plug receives what gets out of the pipe

		m_output.m_pipes.push_back(this);
		m_input.m_pipes.push_back(this);

		m_output.m_process.connected(input.m_process);

		if(!input.m_process.m_script.m_locked)
			this->propagate();
	}

	Pipe::~Pipe()
	{
		vector_remove(m_output.m_pipes, this);
		vector_remove(m_input.m_pipes, this);
	}
	
	void dump_stream(Stream& stream, const string& name)
	{
		printf("INFO: Dump tree %s\n", name.c_str());
		stream.visit(true, [&](StreamBranch& branch)
		{
			for(size_t d = 0; d < branch.m_depth; ++d)
				printf("    ");
			printf("Branch %s value %s\n", to_string(branch.m_index).c_str(), convert(type(branch.m_value)).m_to_string ? to_string(branch.m_value).c_str()
																														: to_name(type(branch.m_value), branch.m_value.m_ref).c_str());
		});
	}

	void Pipe::propagate()
	{
		if(m_modifier == SM_FLATTEN)
			m_input.m_stream.flatten(m_output.m_stream);
		else if(m_modifier == SM_GRAFT)
			m_input.m_stream.graft(m_output.m_stream);
		else
			m_input.m_stream.read(m_output.m_stream);

		m_input.m_process.invalidate();

		//dump_stream(m_input.m_stream, m_input.m_process.m_title + " " + m_input.m_name);
	}

	Process::Process(VisualScript& script, cstring title, Type& type)
		: m_type(type)
		, m_script(script)
		, m_index(script.m_processes.size())
		, m_title(title)
		, m_position{ 0, 0 }
	{}

	Process::~Process()
	{}

	Valve& Process::out_flow()
	{
		if(!m_out_flow)
			m_out_flow = make_object<Valve>(*this, "out", FLOW_VALVE_OUT);
		return *m_out_flow;
	}

	Valve& Process::in_flow()
	{
		if(!m_in_flow)
			m_in_flow = make_object<Valve>(*this, "in", FLOW_VALVE_IN);
		return *m_in_flow;
	}

	void Process::recompute()
	{
		//printf("DEBUG: Process %s executing\n", m_title.c_str());
		this->execute();
		m_state = COMPUTED;

		if(m_callback)
			m_callback(*this);

		for(Valve* output : m_outputs)
			output->propagate();

		if(m_out_flow)
			m_out_flow->propagate();
	}

	void Process::execute()
	{
		//printf("execute process %s\n", m_title.c_str());
		this->clear();

		this->execution_flow();

		m_execution_flow.visit(true, [this](StreamBranch& branch) {
			this->process_branch({ branch.m_index, m_execution_flow.m_topology });
		});

		for(Valve* output : m_outputs)
		{
			output->m_stream.compute();
		}

		if(m_out_flow)
			m_out_flow->m_stream = m_execution_flow;
	}

	Valve& Process::find_master_input()
	{
		Valve* masterInput = m_inputs[0];

		// Process stream flow is the flow of the input with most branches
		for(Valve* input : m_inputs)
			if(input->m_stream.m_size > masterInput->m_stream.m_size)
				masterInput = input;

		if(m_in_flow && m_in_flow->m_stream.m_size > masterInput->m_stream.m_size)
			masterInput = m_in_flow.get();

		return *masterInput;
	}

	void Process::execution_flow()
	{
		if(m_inputs.empty())
			return;

		Valve& masterInput = m_master_input ? *m_master_input : this->find_master_input();
		
		m_execution_flow.copy(masterInput.m_stream);

		if(m_secondary_input != nullptr)
			m_execution_flow.visit(true, [&](StreamBranch& branch) {
				branch.copy(m_secondary_input->m_stream);
			});

		m_execution_flow.compute();
	}

	bool Process::validate_inputs(const StreamLocation& branch)
	{
		bool valid = true;
		for(Valve* input : m_inputs)
		{
			bool check = input->check(branch);
			valid = valid && check;
#ifdef MUD_DEBUG_SCRIPT
			if(!check)
				printf("WARNING: Wrong parameter for process %s, input %s, branch %s\n", m_title.c_str(), input->m_name.c_str(), to_string(branch.m_index).c_str());
#endif
		}
		return valid;
	}

	void Process::process_branch(const StreamLocation& branch)
	{
		if(!this->validate_inputs(branch))
		{
#ifdef MUD_DEBUG_SCRIPT
			//if(!branch.empty()) // @todo this doesn't work (branches are never empty :/
				printf("WARNING: Process %s failed for branch %s\n", m_title.c_str(), to_string(branch.m_index).c_str());
#endif
			for(Valve* valve : m_outputs)
				valve->m_stream.write(branch, Var());
			return;
		}

		this->process(branch);
	}

	Process& Process::flow(Valve& valve)
	{
		m_script.connect(valve, this->in_flow());
		return *this;
	}

	Valve* Process::pipe(vector<Valve*> outputParams, Process* flow, vector<StreamModifier> modifiers)
	{
		this->plug(outputParams, flow, modifiers);
		return m_outputs.size() > 0 ? &this->output() : nullptr;
	}

	Process& Process::plug(vector<Valve*> outputParams, Process* flow, vector<StreamModifier> modifiers)
	{
		if(flow)
			this->flow(flow->out_flow());
		size_t num_inputs = min(m_inputs.size(), outputParams.size());
		for(size_t i = 0; i < num_inputs; ++i)
			m_script.connect(*outputParams[i], *m_inputs[i], modifiers.size() > i ? modifiers[i] : SM_NONE);
		return *this;
	}

	Process& Process::combine_flow(size_t masterInput, size_t secondaryInput)
	{
		m_master_input = m_inputs[masterInput];
		m_secondary_input = m_inputs[secondaryInput];
		return *this;
	}

	void Process::connected(Process& output)
	{
		output.m_edge = false;
		output.m_state = UNCOMPUTED;
	}

	int Process::visit_order()
	{
		if(!m_dirty)
			return m_order;

		m_order = 0;
		m_dirty = false;

		if(m_out_flow)
			for(Pipe* pipe : m_out_flow->m_pipes)
			{
				Process& process = pipe->m_input.m_process;
				m_order = std::min(m_order, process.visit_order() - 1);
			}

		for(Valve* valve : m_outputs)
			for(Pipe* pipe : valve->m_pipes)
			{
				Process& process = pipe->m_input.m_process;
				m_order = std::min(m_order, process.visit_order() - 1);
			}

		return m_order;
	}

	VisualScript::VisualScript(cstring name, const Signature& signature)
		: Script(type<VisualScript>(), name, signature)
	{
		if(!signature.m_returnval.none())
			this->node<ProcessOutput>(Param("return", signature.m_returnval));

		for(const Param& param : signature.m_params)
			if(!param.output())
				this->node<ProcessInput>(param);
			else if(param.output())
				this->node<ProcessOutput>(param);
	}

	void VisualScript::remove(Process& process)
	{
		vector_remove_pt(m_processes, process);

		size_t index = 0;
		for(auto& element : m_processes)
			element->m_index = index++;
	}

	void VisualScript::lock()
	{
		m_locked = true;
	}

	void VisualScript::unlock(bool execute)
	{
		m_locked = false;
		if(execute)
		{
			this->reorder();
			this->execute();
		}
	}

	void VisualScript::reorder()
	{
		for(auto& process : m_processes)
			process->m_dirty = true;

		for(auto& process : m_processes)
			if(process->m_edge)
				process->visit_order();

		m_execution.clear();
		for(auto& process : m_processes)
			m_execution.push_back(process.get());

		std::sort(m_execution.begin(), m_execution.end(),
			[](Process* lhs, Process* rhs) { return lhs->m_order < rhs->m_order; });
	}

	void VisualScript::connect(Valve& output, Valve& input, StreamModifier modifier)
	{
		object<Pipe> pipe = input.try_connect(output, modifier);
		if(pipe)
			m_pipes.push_back(std::move(pipe));
		if(!m_locked)
			this->execute();
	}

	void VisualScript::disconnect(Pipe& pipe)
	{
		vector_remove_pt(m_pipes, pipe);
	}

	Valve& VisualScript::input(const string& name)
	{
		for(ProcessInput* input : m_inputs)
			if(input->m_name == name)
				return input->m_output;
		return m_inputs[0]->m_output;
	}

	void VisualScript::execute(bool uncomputed)
	{
		for(Process* process : m_execution)
			if(!uncomputed || (!process->computed() && !process->locked()))
			{
				process->recompute();
			}
	}

	void VisualScript::operator()(array<Var> args, Var& result) const
	{
		// @kludge: ugly cast until we decide something on this callable constness mess
		VisualScript& self = const_cast<VisualScript&>(*this);
		self.lock();
		for(size_t i = 0; i < m_inputs.size(); ++i)
			m_inputs[i]->m_output.m_stream.write(args[i]);
		self.unlock(false);

		self.reorder();
		self.execute(false);
		UNUSED(result);
	}

	ProcessInput::ProcessInput(VisualScript& script, const Param& param)
		: Process(script, param.m_name, type<ProcessInput>())
		, Param(param)
		, m_output(*this, param.m_name, OUTPUT_VALVE, param.m_value, param.nullable(), param.reference())
	{
		script.m_inputs.push_back(this);
	}

	ProcessOutput::ProcessOutput(VisualScript& script, const Param& param)
		: Process(script, param.m_name, type<ProcessOutput>())
		, Param(param)
		, m_input(*this, param.m_name, INPUT_VALVE, param.m_value, param.nullable(), param.reference())
	{
		script.m_outputs.push_back(this);
	}
}
