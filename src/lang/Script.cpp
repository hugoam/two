//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.lang;
#else
#include <type/Indexer.h>
#include <type/Var.h>
#include <type/Any.h>
#include <ecs/Proto.h>
#include <lang/Types.h>
#include <lang/Script.h>
#include <lang/Lua.h>
#endif

namespace mud
{
	Script::Script(Type& type, const string& name, const Signature& signature)
		: Callable(name.c_str(), signature.m_params, signature.m_return_type)
		, m_index(index(mud::type<Script>(), Ref(this, type)))
		, m_type(type)
		, m_name(name)
		, m_signature(signature)
	{
		Callable::m_name = m_name.c_str();
		m_signature.m_params = m_params;
	}

	Script::~Script()
	{
		unindex(type<Script>(), m_index);
	}

	Interpreter::Interpreter()
	{}

	const Var& Interpreter::get(const string& name, Type& type) { UNUSED(name); UNUSED(type); return Var(); }
	void Interpreter::set(const string& name, const Var& value) { UNUSED(name); UNUSED(value); }

	const Var& Interpreter::getx(array<cstring> path, Type& type) { UNUSED(path); UNUSED(type); return Var(); }
	void Interpreter::setx(array<cstring> path, const Var& value) { UNUSED(path); UNUSED(value); }

	template <class T>
	T* tget(const string& name) { Var value = get(name, type<T>()); return try_val<T>(value); }

	template <class T>
	T* tgetx(array<cstring> path) { Var value = getx(path, type<T>()); return try_val<T>(value); }

	template <class T>
	T* tcall(const string& expr) { Var result = call(expr, &type<T>()); return try_val<T>(result); }

	void Interpreter::call(const TextScript& script, array<Var> args, Var* result)
	{
		m_script = &script;
		script.m_runtime_errors.clear();
		script.m_compile_errors.clear();

		for(const Param& param : script.m_signature.m_params)
		{
			this->set(param.m_name, args[param.m_index]);
		}

		this->call(script.m_script, result);
	}

	string Interpreter::flush()
	{
		string output = m_output;
		m_output = "";
		return output;
	}

	TextScript::TextScript(const string& name, Language language, const Signature& signature)
		: Script(type<TextScript>(), name, signature)
		, m_language(language)
	{}

	void TextScript::operator()(array<Var> args, Var& result) const
	{
		m_interpreter->call(*this, args, result.none() ? nullptr : &result);
	}

	ScriptClass::ScriptClass(const string& name, const vector<Type*>& parts)
		: m_name(name)
		, m_class_type(m_name.c_str())
		, m_class(m_class_type)
		, m_prototype(m_class_type, parts)
	{}
}
