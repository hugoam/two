//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Generated/Forward.h>
#include <obj/Type.h>
#include <obj/Var.h>
#include <obj/Any.h>
#include <obj/Array.h>
#include <obj/Reflect/Meta.h>

#ifndef MUD_CPP_20
#include <functional>
#endif

namespace mud
{
	export_ class refl_ MUD_OBJ_EXPORT Static
	{
	public:
		Static(Type& parent_type, cstring name, Ref value);

		Type* m_parent_type;
		cstring m_name;
		Ref m_value;
	};

	export_ class refl_ MUD_OBJ_EXPORT Member
	{
	public:
		enum Flags
		{
			None = 0,
			Pointer = (1 << 0),
			Mutable = (1 << 1),
			Structure = (1 << 2),
			Link = (1 << 3),
			Value = (1 << 4),
			Id = (1 << 5),
		};

	public:
		Member(Type& object_type, Address address, Type& type, cstring name, Var default_value, Flags flags = Flags::None);
		~Member();

		int m_index;
		Type* m_object_type;
		Address m_address;
		size_t m_offset;
		Type* m_type;
		cstring m_name;
		Var m_default_value;
		Flags m_flags;

		Meta& meta() { return *m_type->m_meta; }
		Class& cls() { return *m_type->m_class; }

		bool is_pointer() const { return (m_flags & Pointer) != 0; }
		bool is_mutable() const { return (m_flags & Mutable) != 0; }
		bool is_structure() const { return (m_flags & Structure) != 0; }
		bool is_link() const { return (m_flags & Link) != 0; }
		bool is_value() const { return (m_flags & Value) != 0; }

		inline Ref ref(Ref object) const { return Ref((void*)((char*)object.m_value + m_offset), *m_type); }

		inline Ref get(Ref object) const
		{
			Ref ref = this->ref(object);
			if(this->is_pointer())
				return Ref(*(void**)ref.m_value, *m_type);
			else
				return ref;
		}

		inline void set(Ref object, Ref value) const
		{
			Ref ref = this->ref(object);
			if(this->is_pointer())
				*(void**)ref.m_value = value.m_value;
			else
				assign(ref, value);
		}
	};

	export_ template <typename T_Value, typename T>
	Member& member(T_Value T::*mem) { return type<T>().m_class->member(member_address(mem)); }

	export_ template <typename T_Return, typename T, typename... T_Params>
	Member& member(T_Return(T::*meth)(T_Params...)) { return type<T>().m_class->member(member_address(meth)); }

	export_ template <typename T_Return, typename T, typename... T_Params>
	Member& member(T_Return(T::*meth)(T_Params...) const) { return type<T>().m_class->member(member_address(meth)); }
}
