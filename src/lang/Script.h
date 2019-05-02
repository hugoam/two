//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <stl/string.h>
#include <stl/map.h>
#include <stl/span.h>
#include <type/Var.h>
#include <type/Proto.h>
#include <refl/Method.h>
#include <refl/Class.h>
#endif
#include <lang/Forward.h>

namespace two
{
	export_ class refl_ TWO_LANG_EXPORT Script : public Callable
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

	export_ struct refl_ TWO_LANG_EXPORT ScriptError
	{
		size_t m_line;
		size_t m_column;
		string m_message;
	};

	export_ class refl_ TWO_LANG_EXPORT TextScript final : public Script
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

	export_ class refl_ TWO_LANG_EXPORT Interpreter
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

	export_ class refl_ TWO_LANG_EXPORT ScriptClass
	{
	public:
		constr_ ScriptClass(const string& name, span<Type*> parts);

		attr_ string m_name;
		attr_ Type m_class_type;
		attr_ Class m_class;
		attr_ Prototype m_prototype;
	};
}
