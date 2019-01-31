//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/vector.h>
#include <stl/string.h>
#include <type/Forward.h>
#include <type/Type.h>
#include <type/TypeOf.h>
//#include <type/Types.h>

namespace mud // export_ namespace mud// @todo evaluate export at namespace level ?
{
#if 1
	export_ template <class T>
	struct Typed<array<T>>
	{
		static inline Type& type() { static string name = "array<" + string(mud::type<type_class<T>>().m_name) + ">"; static Type ty(name.c_str()); return ty; }
	};
	
	export_ template <>
	struct Typed<array<cstring>>
	{
		static inline Type& type() { static Type ty("array<cstring>"); return ty; }
	};

	export_ template <class T>
	struct Typed<vector<T>>
	{
		static inline Type& type() { static string name = "vector<" + string(mud::type<type_class<T>>().m_name) + ">"; static Type ty(name.c_str()); return ty; }
	};
	
	export_ template <>
	struct Typed<vector<cstring>>
	{
		static inline Type& type() { static Type ty("vector<cstring>"); return ty; }
	};
#endif

	export_ template <class... T_Args>
	inline vector<Type*> type_vector()
	{
		return{ &type<T_Args>()... };
	}
}
