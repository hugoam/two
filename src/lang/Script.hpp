//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <type/Any.h>
#endif
#include <lang/Forward.h>
#include <lang/Script.h>

namespace mud
{
	template <class T>
	T* Interpreter::tget(const string& name) { Var value = get(name, type<T>()); return try_val<T>(value); }

	template <class T>
	T* Interpreter::tgetx(span<cstring> path) { Var value = getx(path, type<T>()); return try_val<T>(value); }

	template <class T>
	T* Interpreter::tcall(const string& expr) { Var result = call(expr, &type<T>()); return try_val<T>(result); }

}
