//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.lang;

namespace two
{
	ProcessValue::ProcessValue(VisualScript& script, const Var& value)
		: Process(script, value == Var(Ref()) ? "Ref" : type(value).m_name, type<ProcessValue>())
		, m_output(*this, "output", OUTPUT_VALVE, value, false, false)
	{
		m_output.m_edit = true;
		m_output.m_stream.write(value);
		m_state = COMPUTED;
	}

	ProcessValue::ProcessValue(VisualScript& script, Type& type)
		: ProcessValue(script, meta(type).m_empty_var)
	{}

	ProcessCreate::ProcessCreate(VisualScript& script, Type& type, const Constructor& constructor)
		: Process(script, meta(type).m_name, two::type<ProcessCreate>())
		, m_object_type(type)
		, m_injector(constructor)
		, m_output(*this, "output", OUTPUT_VALVE, is_struct(type) ? meta(type).m_empty_var : Var(Ref(type)), false, is_struct(type) ? false : true)
		, m_pool(is_struct(type) ? nullptr : g_pools[m_object_type.m_id].get())
	{
		for(const Param& param : m_injector.m_constructor.m_params)
			//if(param.m_mode == INPUT_PARAM)
			if(param.m_index > 0) // skip first, it's the object reference
				m_input_params.push_back(oconstruct<Valve>(*this, param));
	}

	ProcessCreate::ProcessCreate(VisualScript& script, Type& type, ConstructorIndex constructor)
		: ProcessCreate(script, type, *cls(type).constructor(constructor))
	{}

	ProcessCreate::ProcessCreate(VisualScript& script, Type& type, size_t num_args)
		: ProcessCreate(script, type, *cls(type).constructor(num_args))
	{}

	void ProcessCreate::clear()
	{
		for(Ref& object : m_persistent_objects)
			m_pool->destroy(object);
		m_persistent_objects.clear();
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
			m_output.m_stream.write(branch, Var(object));
			m_persistent_objects.push_back(object);
		}
	}

	ProcessCallable::ProcessCallable(VisualScript& script, Callable& callable)
		: Process(script, callable.m_name, type<ProcessCallable>())
		, m_call(callable)
	{
		for(const Param& param : callable.m_params)
			m_params.push_back(oconstruct<Valve>(*this, param));

		if(callable.m_return_type != g_qvoid)
			m_result = oconstruct<Valve>(*this, "result", OUTPUT_VALVE, callable.m_return_type.storage_var(), false, false);
	}

	void ProcessCallable::process(const StreamLocation& branch)
	{
		for(Valve* valve : m_inputs)
			m_call.m_args[valve->m_index] = valve->read(branch);
		for(Valve* valve : m_outputs)
			m_call.m_args[m_inputs.size() + valve->m_index] = valve->m_stream.m_default;

		m_call.prepare();

		if(m_result)
		{
			const Var& value = m_call();
			m_result->m_stream.branch(branch.m_index).write(value);
		}
		else
		{
			m_call();
		}

		for(const Param& param : m_call.m_callable->m_params)
			if(param.output())
			{
				m_params[param.m_index]->m_stream.write(branch, m_call.m_args[param.m_index]);
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
		, m_object(*this, "object", OUTPUT_VALVE, Var(Ref(*method.m_object_type)), false, true)
	{}

	void ProcessMethod::process(const StreamLocation& branch)
	{
		ProcessCallable::process(branch);
		m_object.m_stream.write(branch, m_call.m_args[0]);
	}

	ProcessGetMember::ProcessGetMember(VisualScript& script, Member& member)
		: Process(script, member.m_name, type<ProcessGetMember>())
		, m_member(member)
		, m_input_object(*this, "object", INPUT_VALVE, Var(Ref(*member.m_object_type)), false, true)
		, m_output(*this, member.m_name, OUTPUT_VALVE, Var(member.m_default_value), false, !(member.is_value()))
	{}

	void ProcessGetMember::process(const StreamLocation& branch)
	{
		const Var& object = m_input_object.read(branch);
		Var& value = m_output.m_stream.branch(branch.m_index).m_value;
		m_member.get(object.m_ref, value);
	}

	ProcessSetMember::ProcessSetMember(VisualScript& script, Member& member)
		: Process(script, member.m_name, type<ProcessSetMember>())
		, m_member(member)
		, m_input_object(*this, "object", INPUT_VALVE, Var(Ref(*member.m_object_type)), false, true)
		, m_input_value(*this, member.m_name, INPUT_VALVE, Var(member.m_default_value), false, false)
		, m_output_object(*this, "object", OUTPUT_VALVE, Var(Ref(*member.m_object_type)), false, true)
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
	{}

	void ProcessDisplay::process(const StreamLocation& branch)
	{
		UNUSED(branch);
		if(m_update_display)
			m_update_display(*this);
	}
}
