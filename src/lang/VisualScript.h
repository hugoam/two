//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/vector.h>
#include <type/Unique.h>
#include <type/Var.h>
#endif
#include <lang/Forward.h>
#include <lang/Stream.h>
#include <lang/Script.h>

namespace mud
{
	export_ enum ValveKind : unsigned int
	{
		FLOW_VALVE_IN,
		FLOW_VALVE_OUT,
		INPUT_VALVE,
		OUTPUT_VALVE
	};

	export_ class refl_ MUD_LANG_EXPORT Valve
	{
	public:
		Valve(Process& process, cstring name, ValveKind kind, const Var& value = {}, bool nullable = false, bool reference = false);
		Valve(Process& process, const Param& param);
		~Valve();

		Process& m_process;
		size_t m_index;
		string m_name;
		ValveKind m_kind;

		Stream m_stream;

		vector<Pipe*> m_pipes;

		bool m_edit;

		string error_info();
		string param_info();

		bool check(const StreamLocation& location);
		const Var& read(const StreamLocation& location);

		object<Pipe> try_connect(Valve& output, StreamModifier modifier = SM_NONE);

		void propagate();
	};

	export_ class refl_ MUD_LANG_EXPORT Pipe
	{
	public:
		Pipe(Valve& output, Valve& input, StreamModifier modifier = SM_NONE);
		~Pipe();

		Valve& m_output;
		Valve& m_input;
		StreamModifier m_modifier;
		
		void propagate();
	};

	export_ class refl_ MUD_LANG_EXPORT Process
	{
	public:
		Process(VisualScript& script, cstring title, Type& type);
		virtual ~Process();

		using Callback = void(*)(Process&);

		enum State
		{
			LOCKED = 0,
			UNCOMPUTED = 1,
			COMPUTED = 2
		};

		attr_ Type& m_type;
		VisualScript& m_script;
		size_t m_index;
		string m_title;
		vector<Valve*> m_inputs;
		vector<Valve*> m_outputs;

		State m_state = UNCOMPUTED;

		bool m_edge = true;
		int m_order = 0;
		bool m_dirty = true;

		float m_position[2];

		Callback m_callback = nullptr;

		Valve* m_master_input = nullptr;
		Valve* m_secondary_input = nullptr;

		object<Valve> m_in_flow;
		object<Valve> m_out_flow;

		Stream m_execution_flow;

		bool computed() { return m_state == COMPUTED; }
		bool locked() { return m_state == LOCKED; }

		Valve& output() { return *m_outputs[0]; }

		void invalidate() { if(m_state != LOCKED) m_state = UNCOMPUTED; }
		void recompute();

		Valve& out_flow();
		Valve& in_flow();

		void execution_flow();
		bool validate_inputs(const StreamLocation& branch);
		void process_branch(const StreamLocation& branch);
		void execute();

		virtual void clear() {}
		virtual void process(const StreamLocation& branch) { UNUSED(branch); }

		Valve& find_master_input();

		Process& flow(Valve& valve);
		Valve* pipe(vector<Valve*> params = {}, Process* flow = nullptr, vector<StreamModifier> modifiers = {});
		Process& plug(vector<Valve*> params = {}, Process* flow = nullptr, vector<StreamModifier> modifiers = {});
		Process& combine_flow(size_t masterInput, size_t secondaryInput);

		void connected(Process& output);

		int visit_order();
	};

	export_ class refl_ MUD_LANG_EXPORT VisualScript final : public Script
	{
	public:
		constr_ VisualScript(const string& name, const Signature& signature = {});

		VisualScript(const VisualScript& other) = delete;
		VisualScript& operator=(const VisualScript& other) = delete;

		vector<object<Process>> m_processes;
		vector<object<Pipe>> m_pipes;

		vector<Process*> m_execution;

		vector<ProcessInput*> m_inputs;
		vector<ProcessOutput*> m_outputs;

		using Callable::operator();
		virtual void operator()(span<void*> args, void*& result) const;

		void lock();
		void unlock(bool execute = false);

		void reorder();

		void execute(bool uncomputed = true);

		void connect(Valve& output, Valve& input, StreamModifier modifier = SM_NONE);
		void disconnect(Pipe& pipe);

		Valve& input(const string& name);

		void remove(Process& process);

		template <class T, class... Types>
		T& node(Types&&... args)
		{
			m_processes.push_back(oconstruct<T>(*this, static_cast<Types&&>(args)...)); return as<T>(*m_processes.back());
		}

		template <class T>
		Valve& value(const T& value);

		template <class T>
		Valve& reference(T&& value);
		
		template <class T>
		Valve* function(T func, vector<Valve*> params = {}, Process* flow = nullptr, vector<StreamModifier> modifiers = {});

		template <class T>
		Valve& create(vector<Valve*> params = {}, Process* flow = nullptr, vector<StreamModifier> modifiers = {});

		template <class T_Member>
		Valve& get(T_Member mem, vector<Valve*> params = {}, Process* flow = nullptr, vector<StreamModifier> modifiers = {});
		
		template <class T_Member>
		void set(T_Member mem, vector<Valve*> params = {}, Process* flow = nullptr, vector<StreamModifier> modifiers = {});
		
		template <class T_Method>
		Valve* method(T_Method meth, vector<Valve*> params = {}, Process* flow = nullptr, vector<StreamModifier> modifiers = {});
	};

	export_ class refl_ MUD_LANG_EXPORT ProcessInput : public Process, public Param
	{
	public:
		ProcessInput(VisualScript& script, const Param& param);

		Valve m_output;
	};

	export_ class refl_ MUD_LANG_EXPORT ProcessOutput : public Process, public Param
	{
	public:
		ProcessOutput(VisualScript& script, const Param& param);

		Valve m_input;
	};
}
