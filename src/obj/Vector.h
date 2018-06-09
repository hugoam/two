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
#include <string>
#endif

#define MUD_CONTAINER_TYPES_1
namespace mud // export_ namespace mud// @todo evaluate export at namespace level ?
{
#ifdef MUD_CONTAINER_TYPES_1
	export_ template <class T>
	struct Typed<array<T>>
	{
		static inline Type& type() { static string name = "array<" + string(mud::type<typename type_class<T>::type>().m_name) + ">"; static Type ty(name.c_str()); return ty; }
	};
	
	export_ template <>
	struct Typed<array<cstring>>
	{
		static inline Type& type() { static Type ty("array<cstring>"); return ty; }
	};

	export_ template <class T>
	struct Typed<std::vector<T>>
	{
		static inline Type& type() { static string name = "std::vector<" + string(mud::type<typename type_class<T>::type>().m_name) + ">"; static Type ty(name.c_str()); return ty; }
	};
#else
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
#endif

	export_ template <class... T_Args>
	inline std::vector<Type*> type_vector()
	{
		return{ &type<T_Args>()... };
	}
}
