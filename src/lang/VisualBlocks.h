//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Reflect/Class.h>
#include <obj/Reflect/Injector.h>
#include <obj/System/System.h>
#include <lang/Generated/Forward.h>
#include <lang/VisualScript.h>

#include <vector>

namespace mud
{
	class _refl_ MUD_LANG_EXPORT ProcessValue : public Process
	{
	public:
		ProcessValue(VisualScript& script, const Var& value);
		ProcessValue(VisualScript& script, Type& type);

		Valve m_output;
	};

	class _refl_ MUD_LANG_EXPORT ProcessCreate : public Process
	{
	public:
		ProcessCreate(VisualScript& script, Type& type, Meta& meta, const Constructor& constructor);
		ProcessCreate(VisualScript& script, Type& type, ConstructorIndex constructor = ConstructorIndex::Default);
		ProcessCreate(VisualScript& script, Type& type, size_t num_args);

		virtual void clear();
		virtual void process(const StreamLocation& branch);

	protected:
		Type& m_object_type;
		Injector m_injector;
		std::vector<object_ptr<Valve>> m_inputParams;
		Valve m_output;

		Pool* m_pool;
		std::vector<Ref> m_persistentObjects;
	};

	class _refl_ MUD_LANG_EXPORT ProcessCallable : public Process
	{
	public:
		ProcessCallable(VisualScript& script, Callable& callable);

		virtual void process(const StreamLocation& branch) override;

	protected:
		std::vector<Var> m_parameters;
		Callable& m_callable;
		std::vector<object_ptr<Valve>> m_params;
		// @todo : try moving to this
		//std::vector<Valve> m_inputParams;
		//std::vector<Valve> m_outputParams;
		object_ptr<Valve> m_result;
	};

	class _refl_ MUD_LANG_EXPORT ProcessScript : public ProcessCallable
	{
	public:
		ProcessScript(VisualScript& script, VisualScript& target);

		VisualScript& m_target;
	};

	class _refl_ MUD_LANG_EXPORT ProcessFunction : public ProcessCallable
	{
	public:
		ProcessFunction(VisualScript& script, Function& function);

		Function& m_function;
	};

	class _refl_ MUD_LANG_EXPORT ProcessMethod : public ProcessCallable
	{
	public:
		ProcessMethod(VisualScript& script, Method& method);

		virtual void process(const StreamLocation& branch) override;

		Method& m_method;
		Valve m_object;
	};

	class _refl_ MUD_LANG_EXPORT ProcessGetMember : public Process
	{
	public:
		ProcessGetMember(VisualScript& script, Member& member);

		virtual void process(const StreamLocation& branch);

		Member& m_member;
		Valve m_input_object;
		Valve m_output;
	};

	class _refl_ MUD_LANG_EXPORT ProcessSetMember : public Process
	{
	public:
		ProcessSetMember(VisualScript& script, Member& member);

		virtual void process(const StreamLocation& branch);

		Member& m_member;
		Valve m_input_object;
		Valve m_input_value;
		Valve m_output_object;
	};

	class _refl_ MUD_LANG_EXPORT ProcessDisplay : public Process
	{
	public:
		ProcessDisplay(VisualScript& script);

		Valve& inputValue() { return m_input_value; }
		void updateDisplayHandler(const std::function<void(ProcessDisplay&)>& handler) { m_updateDisplay = handler; }

		virtual void process(const StreamLocation& branch);

		Valve m_input_value;
		std::function<void(ProcessDisplay&)> m_updateDisplay;
	};

	template <class T>
	Valve& VisualScript::value(const T& value) { return this->node<ProcessValue>(var(value)).output(); }

	template <class T>
	Valve& VisualScript::reference(T&& value) { return this->node<ProcessValue>(Ref(std::forward<T>(value))).output(); }

	template <class T>
	Valve* VisualScript::function(T func, std::vector<Valve*> params, std::vector<StreamModifier> modifiers) { return this->node<ProcessFunction>(mud::function(func)).pipe(params, modifiers); }

	template <class T>
	Valve& VisualScript::create(std::vector<Valve*> params, std::vector<StreamModifier> modifiers) { return *this->node<ProcessCreate>(type<T>(), params.size()).pipe(params, modifiers); }

	template <class T_Member>
	Valve& VisualScript::get(T_Member mem, std::vector<Valve*> params, std::vector<StreamModifier> modifiers) { return *this->node<ProcessGetMember>(member(mem)).pipe(params, modifiers); }

	template <class T_Member>
	void VisualScript::set(T_Member mem, std::vector<Valve*> params, std::vector<StreamModifier> modifiers) { this->node<ProcessSetMember>(member(mem)).pipe(params, modifiers); }

	template <class T_Method>
	Valve* VisualScript::method(T_Method meth, std::vector<Valve*> params, std::vector<StreamModifier> modifiers) { return this->node<ProcessMethod>(mud::method(meth)).pipe(params, modifiers); }

}
