//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <obj/Array.h>
#include <obj/Var.h>
#include <obj/NonCopy.h>
#include <obj/Unique.h>
#endif
#include <lang/Generated/Forward.h>

namespace mud
{
	using string = std::string;

	class LuaContext;

	export_ class _refl_ MUD_LANG_EXPORT LuaInterpreter : public NonCopy
	{
	public:
		LuaInterpreter(bool import_symbols = false);
		~LuaInterpreter();

		void declareTypes();

		Var get(cstring name, Type& type);
		void set(cstring name, Var value);

		Var getx(array<cstring> path, Type& type);
		void setx(array<cstring> path, Var value);

		void call(cstring code, Var* result = nullptr);
		string flush();

		template <class T>
		T get(cstring name) { return get(name, type<T>()).template val<T>(); }

		template <class T>
		T getx(array<cstring> path) { return getx(path, type<T>()).template val<T>(); }

		template <class T>
		T call(cstring expr) { return call(expr, &type<T>()).template val<T>(); }

		string m_output;

		unique_ptr<LuaContext> m_context;
	};
}
