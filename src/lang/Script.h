//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <infra/Array.h>
#include <infra/NonCopy.h>
#include <type/Any.h>
#include <refl/Method.h>
#include <refl/Class.h>
#endif
#include <lang/Forward.h>

#ifndef MUD_CPP_20
#include <map>
#include <string>
#endif

namespace mud
{
	using string = std::string;

	export_ class refl_ MUD_LANG_EXPORT Script : public Callable
	{
	public:
		Script(Type& type, cstring name, const Signature& signature = {});
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

	export_ struct refl_ MUD_LANG_EXPORT Error
	{
		size_t m_line;
		size_t m_column;
		string m_message;
	};

	export_ class refl_ MUD_LANG_EXPORT TextScript final : public Script
	{
	public:
		constr_ TextScript(cstring name, Language language, const Signature& signature = {});

		attr_ Language m_language;
		attr_ string m_script;
		attr_ bool m_dirty;

		Interpreter* m_interpreter;

		using Callable::operator();
		virtual void operator()(array<Var> args, Var& result) const;

		mutable std::map<int, Error> m_compile_errors;
		mutable std::map<int, Error> m_runtime_errors;
	};

	export_ class refl_ MUD_LANG_EXPORT Interpreter : public NonCopy
	{
	public:
		Interpreter();
		virtual ~Interpreter() {}

		virtual void declare_types() = 0;

		virtual Var get(cstring name, Type& type) { UNUSED(name); UNUSED(type); return Var(); }
		virtual void set(cstring name, Var value) { UNUSED(name); UNUSED(value); }

		virtual Var getx(array<cstring> path, Type& type) { UNUSED(path); UNUSED(type); return Var(); }
		virtual void setx(array<cstring> path, Var value) { UNUSED(path); UNUSED(value); }

		virtual void call(cstring code, Var* result = nullptr) = 0;
		virtual void virtual_call(Method& method, Ref object, array<Var> args) { UNUSED(method); UNUSED(object); UNUSED(args); }

		void call(const TextScript& script, array<Var> args, Var* result = nullptr);

		string flush();

		template <class T>
		T* tget(cstring name) { Var value = get(name, type<T>()); return try_val<T>(value); }

		template <class T>
		T* tgetx(array<cstring> path) { Var value = getx(path, type<T>()); return try_val<T>(value); }

		template <class T>
		T* tcall(cstring expr) { Var result = call(expr, &type<T>()); return try_val<T>(result); }

		const TextScript* m_script = nullptr;
		string m_output;
	};

	export_ class refl_ MUD_LANG_EXPORT ScriptClass : public NonCopy
	{
	public:
		constr_ ScriptClass(const string& name, const std::vector<Type*>& parts);

		attr_ string m_name;
		attr_ Type m_type;
		attr_ Class m_class;
	};
}
