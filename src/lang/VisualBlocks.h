//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/vector.h>
#include <type/Any.h>
#include <refl/Class.h>
#include <refl/Injector.h>
#include <refl/System.h>
#endif
#include <lang/Forward.h>
#include <lang/VisualScript.h>

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
	Valve* VisualScript::function(T f, vector<Valve*> params, Process* flow, vector<StreamModifier> modifiers) { return this->node<ProcessFunction>(func(f)).pipe(params, flow, modifiers); }

	template <class T>
	Valve& VisualScript::create(vector<Valve*> params, Process* flow, vector<StreamModifier> modifiers) { return *this->node<ProcessCreate>(type<T>(), params.size()).pipe(params, flow, modifiers); }

	template <class T_Member>
	Valve& VisualScript::get(T_Member mem, vector<Valve*> params, Process* flow, vector<StreamModifier> modifiers) { return *this->node<ProcessGetMember>(member(mem)).pipe(params, flow, modifiers); }

	template <class T_Member>
	void VisualScript::set(T_Member mem, vector<Valve*> params, Process* flow, vector<StreamModifier> modifiers) { this->node<ProcessSetMember>(member(mem)).pipe(params, flow, modifiers); }

	template <class T_Method>
	Valve* VisualScript::method(T_Method meth, vector<Valve*> params, Process* flow, vector<StreamModifier> modifiers) { return this->node<ProcessMethod>(mud::method(meth)).pipe(params, flow, modifiers); }

}
