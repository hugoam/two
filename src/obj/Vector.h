//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Forward.h>
#include <obj/Type.h>
#include <obj/TypeOf.h>
#include <obj/Types.h>

#ifndef MUD_CPP_20
#include <vector>
#endif

namespace mud // export_ namespace mud// @todo evaluate export at namespace level ?
{
	export_ extern MUD_OBJ_EXPORT std::vector<Type> g_array_types;
	export_ extern MUD_OBJ_EXPORT std::vector<Type> g_vector_types;

	export_ template <class T>
	struct Typed<array<T>>
	{
		static inline Type& type() { return g_array_types[mud::type<typename type_class<T>::type>().m_id]; }
	};

	export_ template <>
	struct Typed<array<cstring>>
	{
		static inline Type& type() { return g_array_types[mud::type<cstring>().m_id]; }
	};

	export_ template <class T>
	struct Typed<std::vector<T>>
	{
		static inline Type& type() { return g_vector_types[mud::type<typename type_class<T>::type>().m_id]; }
	};

	export_ template <class... T_Args>
	inline std::vector<Type*> type_vector()
	{
		return{ &type<T_Args>()... };
	}
}
