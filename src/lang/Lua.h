//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/string.h>
#include <infra/Array.h>
#include <infra/NonCopy.h>
#include <type/Var.h>
#include <type/Unique.h>
#endif
#include <lang/Forward.h>
#include <lang/Script.h>

namespace mud
{
	class LuaContext;

	export_ class refl_ MUD_LANG_EXPORT LuaInterpreter final : public Interpreter
	{
	public:
		LuaInterpreter(bool import_symbols);
		~LuaInterpreter();

		virtual void declare_types() final;

		virtual Var get(const string& name, Type& type) final;
		virtual void set(const string& name, Var value) final;

		virtual Var getx(array<cstring> path, Type& type) final;
		virtual void setx(array<cstring> path, Var value) final;

		virtual void call(const string& code, Var* result = nullptr) final;

		unique<LuaContext> m_context;
	};
}
