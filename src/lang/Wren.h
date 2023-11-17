//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <lang/Forward.h>
#include <lang/Script.h>

namespace two
{
	class WrenContext;

	struct WrenFunctionDecl
	{
		string functions;
		string bind;
	};

	export_ class refl_ TWO_LANG_EXPORT WrenInterpreter final : public Interpreter
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
