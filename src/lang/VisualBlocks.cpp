//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.lang;
#else
#include <obj/Indexer.h>
#include <refl/System.h>
#include <pool/ObjectPool.h>
#include <lang/Types.h>
#include <lang/VisualBlocks.h>
#endif

namespace mud
{
	ProcessValue::ProcessValue(VisualScript& script, const Var& value)
		: Process(script, value == Ref() ? "Ref" : value.type().m_name, type<ProcessValue>())
		, m_output(*this, "output", OUTPUT_VALVE, value, false, false)
	{
		m_output.m_edit = true;
		m_output.m_stream.write(value);
		m_state = COMPUTED;
	}

	ProcessValue::ProcessValue(VisualScript& script, Type& type)
		: ProcessValue(script, meta(type).m_empty_var())
	{}

	ProcessCreate::ProcessCreate(VisualScript& script, Type& type, Meta& meta, const Constructor& constructor)
		: Process(script, meta.m_name, mud::type<ProcessCreate>())
		, m_object_type(type)
		, m_injector(type, constructor)
		, m_inputParams()
		, m_output(*this, "output", OUTPUT_VALVE, is_struct(type) ? meta.m_empty_var() : Var(meta.m_empty_ref()), false, is_struct(type) ? false : true)
		, m_pool(is_struct(type) ? nullptr : &GlobalPool::me().pool(m_object_type))
	{
		for(const Param& param : m_injector.m_constructor.m_params)
			//if(param.m_mode == INPUT_PARAM)
			if(param.m_index > 0) // skip first, it's the object reference
				m_inputParams.emplace_back(make_object<Valve>(*this, param));
	}

	ProcessCreate::ProcessCreate(VisualScript& script, Type& type, ConstructorIndex constructor)
		: ProcessCreate(script, type, meta(type), *cls(type).constructor(constructor))
	{}

	ProcessCreate::ProcessCreate(VisualScript& script, Type& type, size_t num_args)
		: ProcessCreate(script, type, meta(type), *cls(type).constructor(num_args))
	{}

	void ProcessCreate::clear()
	{
		for(Ref& object : m_persistentObjects)
			m_pool->destroy(object);
		m_persistentObjects.clear();
	}

	void ProcessCreate::process(const StreamLocation& branch)
	{
		for(size_t i = 1; i < m_injector.m_args.size(); ++i)
			m_injector.m_args[i] = m_inputs[i - 1]->read(branch);

		if(is_struct(m_object_type))
		{
			Var& value = m_output.m_stream.branch(branch.m_index).m_value;
			m_injector.inject(value);
		}
		else
		{
			Ref object = m_injector.inject(*m_pool);
			m_output.m_stream.write(branch, object);
			m_persistentObjects.push_back(object);
		}
	}

	ProcessCallable::ProcessCallable(VisualScript& script, Callable& callable)
		: Process(script, callable.m_name, type<ProcessCallable>())
		, m_parameters(callable.m_params.size() + (callable.m_returnval.none() ? 0 : 1))
		, m_callable(callable)
	{
		for(const Param& param : callable.m_params)
			m_params.emplace_back(make_object<Valve>(*this, param));

		if(!callable.m_returnval.none())
			m_result = make_object<Valve>(*this, "result", OUTPUT_VALVE, callable.m_returnval, false, false);
	}

	void ProcessCallable::process(const StreamLocation& branch)
	{
		for(Valve* valve : m_inputs)
			m_parameters[valve->m_index] = valve->read(branch);
		for(Valve* valve : m_outputs)
			m_parameters[m_inputs.size() + valve->m_index] = valve->m_stream.m_default;

		if(m_result)
		{
			Var& value = m_result->m_stream.branch(branch.m_index).m_value;
			m_callable(to_array(m_parameters), value);
		}
		else
		{
			static Var unused;
			m_callable(to_array(m_parameters), unused);
		}

		for(const Param& param : m_callable.m_params)
			if(param.output())
			{
				m_params[param.m_index]->m_stream.write(branch, m_parameters[param.m_index]);
			}
	}

	ProcessScript::ProcessScript(VisualScript& script, VisualScript& target)
		: ProcessCallable(script, target)
		, m_target(target)
	{}

	ProcessFunction::ProcessFunction(VisualScript& script, Function& function)
		: ProcessCallable(script, function)
		, m_function(function)
	{}

	ProcessMethod::ProcessMethod(VisualScript& script, Method& method)
		: ProcessCallable(script, method)
		, m_method(method)
		, m_object(*this, "object", OUTPUT_VALVE, meta(*method.m_object_type).m_empty_ref(), false, true)
	{
		m_parameters.resize(m_parameters.size() + 1);
	}

	void ProcessMethod::process(const StreamLocation& branch)
	{
		ProcessCallable::process(branch);
		m_object.m_stream.write(branch, m_parameters[0]);
	}

	ProcessGetMember::ProcessGetMember(VisualScript& script, Member& member)
		: Process(script, member.m_name, type<ProcessGetMember>())
		, m_member(member)
		, m_input_object(*this, "object", INPUT_VALVE, meta(*member.m_object_type).m_empty_ref(), false, true)
		, m_output(*this, member.m_name, OUTPUT_VALVE, member.m_default_value, false, !(member.is_value()))
	{}

	void ProcessGetMember::process(const StreamLocation& branch)
	{
		const Var& object = m_input_object.read(branch);
		Var& value = m_output.m_stream.branch(branch.m_index).m_value;
		//m_member.get(object.m_ref, value);
		value = m_member.get(object.m_ref);
	}

	ProcessSetMember::ProcessSetMember(VisualScript& script, Member& member)
		: Process(script, member.m_name, type<ProcessSetMember>())
		, m_member(member)
		, m_input_object(*this, "object", INPUT_VALVE, meta(*member.m_object_type).m_empty_ref(), false, true)
		, m_input_value(*this, member.m_name, INPUT_VALVE, member.m_default_value, false, false)
		, m_output_object(*this, "object", OUTPUT_VALVE, meta(*member.m_object_type).m_empty_ref(), false, true)
	{}

	void ProcessSetMember::process(const StreamLocation& branch)
	{
		const Var& object = m_input_object.read(branch);
		const Var& value = m_input_value.read(branch);
		m_member.set(object.m_ref, value.m_ref);

		m_output_object.m_stream.write(branch, object);
	}

	ProcessDisplay::ProcessDisplay(VisualScript& script)
		: Process(script, "Display", type<ProcessDisplay>())
		, m_input_value(*this, "input", INPUT_VALVE)
		, m_updateDisplay()
	{}

	void ProcessDisplay::process(const StreamLocation& branch)
	{
		UNUSED(branch);
		if(m_updateDisplay)
			m_updateDisplay(*this);
	}
}
