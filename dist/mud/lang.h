#pragma once

#include <mud/pool.h>
#include <mud/refl.h>
#include <mud/infra.h>
#include <mud/type.h>




#ifndef MUD_LANG_EXPORT
#define MUD_LANG_EXPORT MUD_IMPORT
#endif

namespace mud
{
    enum class Language : unsigned int;
    enum StreamModifier : unsigned int;
    enum ValveKind : unsigned int;
    
    class Script;
    class TextScript;
	struct ScriptError;
    class Interpreter;
    class ScriptClass;
    class LuaInterpreter;
    struct StreamLocation;
    class StreamBranch;
    class Stream;
    class Valve;
    class Pipe;
    class Process;
    class VisualScript;
    class ProcessInput;
    class ProcessOutput;
    class ProcessValue;
    class ProcessCreate;
    class ProcessCallable;
    class ProcessScript;
    class ProcessFunction;
    class ProcessMethod;
    class ProcessGetMember;
    class ProcessSetMember;
    class ProcessDisplay;
    class WrenInterpreter;
}

#ifdef MUD_META_GENERATOR
#include <stl/vector.h>
namespace stl
{
}
#endif


#ifndef MUD_MODULES
#include <stl/string.h>
#include <stl/memory.h>
#endif


#ifndef MUD_MODULES
#include <stl/string.h>
#include <stl/map.h>
#include <stl/span.h>
#endif

namespace mud
{
	export_ class refl_ MUD_LANG_EXPORT Script : public Callable
	{
	public:
		Script(Type& type, const string& name, const Signature& signature = {});
		virtual ~Script();

		attr_ uint32_t m_index;
		attr_ Type& m_type;
		attr_ string m_name;
		attr_ bool m_locked;

		Signature m_signature;
	};

	enum class refl_ Language : unsigned int
	{
		Cpp,
		Lua,
		Wren
	};

	export_ struct refl_ MUD_LANG_EXPORT ScriptError
	{
		size_t m_line;
		size_t m_column;
		string m_message;
	};

	export_ class refl_ MUD_LANG_EXPORT TextScript final : public Script
	{
	public:
		constr_ TextScript(const string& name, Language language, const Signature& signature = {});

		attr_ Language m_language;
		attr_ string m_script;
		attr_ bool m_dirty;

		Interpreter* m_interpreter;

		using Callable::operator();
		virtual void operator()(span<void*> args, void*& result) const override;

		mutable map<int, ScriptError> m_compile_errors;
		mutable map<int, ScriptError> m_runtime_errors;
	};

	export_ class refl_ MUD_LANG_EXPORT Interpreter
	{
	public:
		Interpreter();
		virtual ~Interpreter() {}

		virtual void declare_types() = 0;

		virtual Var get(const string& name, const Type& type);
		virtual void set(const string& name, const Var& value);

		virtual Var getx(span<cstring> path, const Type& type);
		virtual void setx(span<cstring> path, const Var& value);

		virtual void call(const string& code, Var* result = nullptr) = 0;
		virtual void virtual_call(Method& method, Ref object, span<Var> args) { UNUSED(method); UNUSED(object); UNUSED(args); }

		//void call(const TextScript& script, span<Var> args, Var* result = nullptr);
		void call(const TextScript& script, span<void*> args, void*& result);

		string flush();

		template <class T>
		T* tget(const string& name);

		template <class T>
		T* tgetx(span<cstring> path);

		template <class T>
		T* tcall(const string& expr);

		const TextScript* m_script = nullptr;
		string m_output;
	};

	export_ class refl_ MUD_LANG_EXPORT ScriptClass
	{
	public:
		constr_ ScriptClass(const string& name, span<Type*> parts);

		attr_ string m_name;
		attr_ Type m_class_type;
		attr_ Class m_class;
		attr_ Prototype m_prototype;
	};
}

namespace mud
{
	class LuaContext;

	export_ class refl_ MUD_LANG_EXPORT LuaInterpreter final : public Interpreter
	{
	public:
		LuaInterpreter(bool import_symbols);
		~LuaInterpreter();

		virtual void declare_types() final;

		virtual Var get(const string& name, const Type& type) final;
		virtual void set(const string& name, const Var& value) final;

		virtual Var getx(span<cstring> path, const Type& type) final;
		virtual void setx(span<cstring> path, const Var& value) final;

		virtual void call(const string& code, Var* result = nullptr) final;

		unique<LuaContext> m_context;
	};
}


#ifndef MUD_MODULES
#include <stl/vector.h>
#endif

namespace mud
{
	typedef vector<size_t> StreamIndex;
	typedef vector<size_t> Topology;

	/*export_ struct MUD_LANG_EXPORT StreamBranch : public StreamIndex
	{
		StreamBranch(StreamIndex index);

		Flow* flow;
		bool empty;
	};

	export_ struct MUD_LANG_EXPORT Flow
	{
		vector<StreamBranch> branches;
		Topology topology;
	};*/

	struct StreamLocation
	{
		const StreamIndex& m_index;
		const Topology& m_topology;
	};

	export_ class refl_ MUD_LANG_EXPORT StreamBranch
	{
	public:
		StreamBranch();
		StreamBranch(Stream* stream, const Var& value, StreamIndex index);

		Var& value(const StreamIndex& index) { return this->branch(index).m_value; }

		StreamBranch& add_branch();
		void resize(size_t size);

		void clear();

		void copy(const StreamBranch& branch);

		template <class Visitor>
		void visit(bool leafs, const Visitor& visitor)
		{
			for(auto& branch : m_branches)
				branch.visit(leafs, visitor);

			if(!leafs || m_branches.size() == 0)
				visitor(*this);
		}

		StreamBranch& branch(const StreamIndex& index);

		StreamBranch* find_branch(const StreamIndex& branch, size_t depth);
		StreamBranch* find_branch(const StreamIndex& branch) { return this->find_branch(branch, m_depth); }

		void write(const Var& value, bool multiplex = true);
		bool read(Var& value, const Type* expected_type, bool ref);

		void write(const StreamLocation& location, const Var& value, bool multiplex = true) { this->branch(location.m_index).write(value, multiplex); }
		//void write(const Var& value, bool multiplex = true) { this->branch({ 0 }).write(value, multiplex); }

		Stream* m_stream;
		StreamIndex m_index;
		size_t m_depth;
		Var m_value = {};
		bool m_valid = true;
		//bool m_empty = false;

		vector<StreamBranch> m_branches;
	};


	enum StreamModifier : unsigned int
	{
		SM_NONE,
		SM_FLATTEN,
		SM_GRAFT
	};

	export_ class refl_ MUD_LANG_EXPORT Stream : public StreamBranch
	{
	public:
		Stream();
		Stream(const Var& value, bool nullable, bool reference);
		Stream(const Stream& stream);
		Stream& operator=(const Stream& stream);

		StreamBranch* match_branch(const StreamLocation& source_location);

		void flatten(Stream& source);
		void graft(Stream& source);
		void read(Stream& source);
		void validate();

		size_t m_size = 1;
		Topology m_topology;
		size_t m_num_invalid = 0;

		Var m_default;
		const Type* m_type = nullptr;
		bool m_nullable = false;
		bool m_reference = false;

		void compute();
	};
}

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

#ifndef MUD_MODULES
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_LANG_EXPORT Type& type<mud::Language>();
    
    
    export_ template <> MUD_LANG_EXPORT Type& type<mud::Interpreter>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::Pipe>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::Process>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::ScriptClass>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::ScriptError>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::StreamBranch>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::Valve>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::LuaInterpreter>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::ProcessCallable>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::ProcessCreate>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::ProcessDisplay>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::ProcessFunction>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::ProcessGetMember>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::ProcessInput>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::ProcessMethod>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::ProcessOutput>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::ProcessScript>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::ProcessSetMember>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::ProcessValue>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::Script>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::Stream>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::TextScript>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::VisualScript>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::WrenInterpreter>();
}


#ifndef MUD_MODULES
#include <stl/vector.h>
#endif


#ifndef MUD_MODULES
#include <stl/vector.h>
#endif

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
		Valve* pipe(span<Valve*> params = {}, Process* flow = nullptr, span<StreamModifier> modifiers = {});
		Process& plug(span<Valve*> params = {}, Process* flow = nullptr, span<StreamModifier> modifiers = {});
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
		Valve* function(T func, span<Valve*> params = {}, Process* flow = nullptr, span<StreamModifier> modifiers = {});

		template <class T>
		Valve& create(span<Valve*> params = {}, Process* flow = nullptr, span<StreamModifier> modifiers = {});

		template <class T_Member>
		Valve& get(T_Member mem, span<Valve*> params = {}, Process* flow = nullptr, span<StreamModifier> modifiers = {});
		
		template <class T_Member>
		void set(T_Member mem, span<Valve*> params = {}, Process* flow = nullptr, span<StreamModifier> modifiers = {});
		
		template <class T_Method>
		Valve* method(T_Method meth, span<Valve*> params = {}, Process* flow = nullptr, span<StreamModifier> modifiers = {});
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

namespace mud
{
	export_ class refl_ MUD_LANG_EXPORT ProcessValue : public Process
	{
	public:
		constr_ ProcessValue(VisualScript& script, const Var& value);
		ProcessValue(VisualScript& script, Type& type);

		Valve m_output;
	};

	export_ class refl_ MUD_LANG_EXPORT ProcessCreate : public Process
	{
	public:
		constr_ ProcessCreate(VisualScript& script, Type& type, const Constructor& constructor);
		ProcessCreate(VisualScript& script, Type& type, ConstructorIndex constructor = ConstructorIndex::Default);
		ProcessCreate(VisualScript& script, Type& type, size_t num_args);

		virtual void clear();
		virtual void process(const StreamLocation& branch);

	protected:
		Type& m_object_type;
		Injector m_injector;
		vector<object<Valve>> m_input_params;
		Valve m_output;

		Pool* m_pool;
		vector<Ref> m_persistent_objects;
	};

	export_ class refl_ MUD_LANG_EXPORT ProcessCallable : public Process
	{
	public:
		constr_ ProcessCallable(VisualScript& script, Callable& callable);

		virtual void process(const StreamLocation& branch) override;

	protected:
		vector<Var> m_parameters;
		Callable& m_callable;
		vector<object<Valve>> m_params;
		// @todo : try moving to this
		//vector<Valve> m_inputParams;
		//vector<Valve> m_outputParams;
		object<Valve> m_result;
	};

	export_ class refl_ MUD_LANG_EXPORT ProcessScript : public ProcessCallable
	{
	public:
		constr_ ProcessScript(VisualScript& script, VisualScript& target);

		VisualScript& m_target;
	};

	export_ class refl_ MUD_LANG_EXPORT ProcessFunction : public ProcessCallable
	{
	public:
		constr_ ProcessFunction(VisualScript& script, Function& function);

		Function& m_function;
	};

	export_ class refl_ MUD_LANG_EXPORT ProcessMethod : public ProcessCallable
	{
	public:
		constr_ ProcessMethod(VisualScript& script, Method& method);

		virtual void process(const StreamLocation& branch) override;

		Method& m_method;
		Valve m_object;
	};

	export_ class refl_ MUD_LANG_EXPORT ProcessGetMember : public Process
	{
	public:
		constr_ ProcessGetMember(VisualScript& script, Member& member);

		virtual void process(const StreamLocation& branch);

		Member& m_member;
		Valve m_input_object;
		Valve m_output;
	};

	export_ class refl_ MUD_LANG_EXPORT ProcessSetMember : public Process
	{
	public:
		constr_ ProcessSetMember(VisualScript& script, Member& member);

		virtual void process(const StreamLocation& branch);

		Member& m_member;
		Valve m_input_object;
		Valve m_input_value;
		Valve m_output_object;
	};

	export_ class refl_ MUD_LANG_EXPORT ProcessDisplay : public Process
	{
	public:
		ProcessDisplay(VisualScript& script);

		virtual void process(const StreamLocation& branch);

		Valve m_input_value;
		using Handler = void(*)(ProcessDisplay&); Handler m_update_display;
	};

	template <class T>
	Valve& VisualScript::value(const T& value) { return this->node<ProcessValue>(var(value)).output(); }

	template <class T>
	Valve& VisualScript::reference(T&& value) { return this->node<ProcessValue>(Ref(static_cast<T&&>(value))).output(); }

	template <class T>
	Valve* VisualScript::function(T f, span<Valve*> params, Process* flow, span<StreamModifier> modifiers) { return this->node<ProcessFunction>(func(f)).pipe(params, flow, modifiers); }

	template <class T>
	Valve& VisualScript::create(span<Valve*> params, Process* flow, span<StreamModifier> modifiers) { return *this->node<ProcessCreate>(type<T>(), params.size()).pipe(params, flow, modifiers); }

	template <class T_Member>
	Valve& VisualScript::get(T_Member mem, span<Valve*> params, Process* flow, span<StreamModifier> modifiers) { return *this->node<ProcessGetMember>(member(mem)).pipe(params, flow, modifiers); }

	template <class T_Member>
	void VisualScript::set(T_Member mem, span<Valve*> params, Process* flow, span<StreamModifier> modifiers) { this->node<ProcessSetMember>(member(mem)).pipe(params, flow, modifiers); }

	template <class T_Method>
	Valve* VisualScript::method(T_Method meth, span<Valve*> params, Process* flow, span<StreamModifier> modifiers) { return this->node<ProcessMethod>(mud::method(meth)).pipe(params, flow, modifiers); }

}


#ifndef MUD_MODULES
#include <stl/string.h>
#include <stl/memory.h>
#include <stl/map.h>
#endif

namespace mud
{
	class WrenContext;

	struct WrenFunctionDecl
	{
		string functions;
		string bind;
	};

	export_ class refl_ MUD_LANG_EXPORT WrenInterpreter final : public Interpreter
	{
	public:
		WrenInterpreter(bool import_symbols);
		~WrenInterpreter();

		virtual void declare_types() final;

		virtual Var get(const string& name, const Type& type) final;
		virtual void set(const string& name, const Var& value) final;

		virtual Var getx(span<cstring> path, const Type& type) final;
		virtual void setx(span<cstring> path, const Var& value) final;

		virtual void call(const string& code, Var* result = nullptr) final;
		virtual void virtual_call(Method& method, Ref object, span<Var> args) final;

		unique<WrenContext> m_context;

		void create_virtual(Ref object);

		map<void*, const TextScript*> m_virtual_scripts;
	};
}



#ifndef MUD_MODULES
#endif

namespace mud
{
	template <class T>
	T* Interpreter::tget(const string& name) { Var value = get(name, type<T>()); return try_val<T>(value); }

	template <class T>
	T* Interpreter::tgetx(span<cstring> path) { Var value = getx(path, type<T>()); return try_val<T>(value); }

	template <class T>
	T* Interpreter::tcall(const string& expr) { Var result = call(expr, &type<T>()); return try_val<T>(result); }

}
