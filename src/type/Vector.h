//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <stl/vector.h>
#include <stl/string.h>
#endif
#include <type/Forward.h>
#include <type/Type.h>
#include <type/TypeOf.h>
//#include <type/Types.h>

namespace two // export_ namespace two// @todo evaluate export at namespace level ?
{
#if 1
	export_ template <class T>
	struct Typed<span<T>>
	{
		static inline Type& type() { static string name = "span<" + string(two::type<type_class<T>>().m_name) + ">"; static Type ty(name.c_str()); return ty; }
	};
	
	export_ template <>
	struct Typed<span<cstring>>
	{
		static inline Type& type() { static Type ty("span<cstring>"); return ty; }
	};

	export_ template <class T>
	struct Typed<vector<T>>
	{
		static inline Type& type() { static string name = "vector<" + string(two::type<type_class<T>>().m_name) + ">"; static Type ty(name.c_str()); return ty; }
	};
	
	export_ template <>
	struct Typed<vector<cstring>>
	{
		static inline Type& type() { static Type ty("vector<cstring>"); return ty; }
	};
#endif

	export_ template <class... Args>
	inline vector<Type*> type_vector()
	{
		return{ &type<Args>()... };
	}
}
