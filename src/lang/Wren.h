//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/string.h>
#include <stl/map.h>
#include <infra/Array.h>
#include <infra/NonCopy.h>
#include <type/Any.h>
#include <type/Unique.h>
#endif
#include <lang/Forward.h>
#include <lang/Script.h>

namespace mud
{
	class WrenContext;

	export_ class refl_ MUD_LANG_EXPORT WrenInterpreter final : public Interpreter
	{
	public:
		WrenInterpreter(bool import_symbols);
		~WrenInterpreter();

		virtual void declare_types() final;

		virtual Var get(cstring name, Type& type) final;
		virtual void set(cstring name, Var value) final;

		virtual Var getx(array<cstring> path, Type& type) final;
		virtual void setx(array<cstring> path, Var value) final;

		virtual void call(cstring code, Var* result = nullptr) final;
		virtual void virtual_call(Method& method, Ref object, array<Var> args) final;

		unique<WrenContext> m_context;

		void create_virtual(Ref object);

		map<void*, const TextScript*> m_virtual_scripts;
	};
}
