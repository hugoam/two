//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <infra/Array.h>
#include <infra/NonCopy.h>
#include <type/Any.h>
#include <type/Unique.h>
#endif
#include <lang/Forward.h>
#include <lang/Script.h>

#ifndef  MUD_CPP_20
#include <string>
#endif

namespace mud
{
	using string = std::string;

	class LuaContext;

	export_ class refl_ MUD_LANG_EXPORT LuaInterpreter final : public Interpreter
	{
	public:
		LuaInterpreter(bool import_symbols);
		~LuaInterpreter();

		virtual void declare_types() final;

		virtual Var get(cstring name, Type& type) final;
		virtual void set(cstring name, Var value) final;

		virtual Var getx(array<cstring> path, Type& type) final;
		virtual void setx(array<cstring> path, Var value) final;

		virtual void call(cstring code, Var* result = nullptr) final;

		unique_ptr<LuaContext> m_context;
	};
}
