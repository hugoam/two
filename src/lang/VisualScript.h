//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Var.h>
#include <obj/NonCopy.h>
#include <lang/Generated/Forward.h>
#include <lang/Stream.h>
#include <lang/Script.h>

#include <vector>

namespace mud
{
	enum ValveKind : unsigned int
	{
		FLOW_VALVE_IN,
		FLOW_VALVE_OUT,
		INPUT_VALVE,
		OUTPUT_VALVE
	};

	class _refl_ MUD_LANG_EXPORT Valve
	{
	public:
		Valve(Process& process, cstring name, ValveKind kind, Var value = {}, bool nullable = false, bool reference = false);
		Valve(Process& process, const Param& param);
		~Valve();

		Process& m_process;
		size_t m_index;
		string m_name;
		ValveKind m_kind;

		Stream m_stream;

		std::vector<Pipe*> m_pipes;

		bool m_edit;

		string error_info();
		string param_info();

		bool check(const StreamLocation& location);
		const Var& read(const StreamLocation& location);

		object_ptr<Pipe> try_connect(Valve& output, StreamModifier modifier = SM_NONE);

		void propagate();
	};

	class _refl_ MUD_LANG_EXPORT Pipe
	{
	public:
		Pipe(Valve& output, Valve& input, StreamModifier modifier = SM_NONE);
		~Pipe();

		Valve& m_output;
		Valve& m_input;
		StreamModifier m_modifier;
		
		void propagate();
	};

	class _refl_ MUD_LANG_EXPORT Process
	{
	public:
		Process(VisualScript& script, cstring title, Type& type);
		virtual ~Process();

		typedef std::function<void(Process&)> Callback;

		enum State
		{
			LOCKED = 0,
			UNCOMPUTED = 1,
			COMPUTED = 2
		};

		_attr_ Type& m_type;
		VisualScript& m_script;
		size_t m_index;
		string m_title;
		std::vector<Valve*> m_inputs;
		std::vector<Valve*> m_outputs;

		State m_state = UNCOMPUTED;

		bool m_edge = true;
		int m_order = 0;
		bool m_dirty = true;

		float m_position[2];

		Callback m_callback;

		Valve* m_master_input = nullptr;
		Valve* m_secondary_input = nullptr;

		object_ptr<Valve> m_in_flow;
		object_ptr<Valve> m_out_flow;

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
		Valve* pipe(std::vector<Valve*> params = {}, std::vector<StreamModifier> modifiers = {});
		Process& plug(std::vector<Valve*> params = {}, std::vector<StreamModifier> modifiers = {});
		Process& combine_flow(size_t masterInput, size_t secondaryInput);

		void connected(Process& output);

		int visit_order();
	};

	class _refl_ MUD_LANG_EXPORT VisualScript : public NonCopy, public Script
	{
	public:
		_constr_ VisualScript(cstring name, const Signature& signature = {});

		std::vector<object_ptr<Process>> m_processes;
		std::vector<object_ptr<Pipe>> m_pipes;

		std::vector<Process*> m_execution;

		std::vector<ProcessInput*> m_inputs;
		std::vector<ProcessOutput*> m_outputs;

		using Callable::operator();
		virtual void operator()(array<Var> args, Var& result);

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
			m_processes.push_back(make_object<T>(*this, std::forward<Types>(args)...)); return as<T>(*m_processes.back());
		}

		template <class T>
		Valve& value(const T& value);

		template <class T>
		Valve& reference(T&& value);
		
		template <class T>
		Valve* function(T func, std::vector<Valve*> params = {}, std::vector<StreamModifier> modifiers = {});

		template <class T>
		Valve& create(std::vector<Valve*> params = {}, std::vector<StreamModifier> modifiers = {});

		template <class T_Member>
		Valve& get(T_Member mem, std::vector<Valve*> params = {}, std::vector<StreamModifier> modifiers = {});
		
		template <class T_Member>
		void set(T_Member mem, std::vector<Valve*> params = {}, std::vector<StreamModifier> modifiers = {});
		
		template <class T_Method>
		Valve* method(T_Method meth, std::vector<Valve*> params = {}, std::vector<StreamModifier> modifiers = {});
	};

	class _refl_ MUD_LANG_EXPORT ProcessInput : public Process, public Param
	{
	public:
		ProcessInput(VisualScript& script, const Param& param);

		Valve m_output;
	};

	class _refl_ MUD_LANG_EXPORT ProcessOutput : public Process, public Param
	{
	public:
		ProcessOutput(VisualScript& script, const Param& param);

		Valve m_input;
	};
}
