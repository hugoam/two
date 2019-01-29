//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/vector.h>
#include <refl/Forward.h>
#include <type/Var.h>
#include <type/RefVal.h>
#include <refl/Method.h>
#include <refl/Member.h>

namespace mud
{
	export_ using cstring = const char*;

	export_ class refl_ MUD_REFL_EXPORT Class
	{
	public:
		Class(Type& type);
		Class(
			Type& type,
			array<Type*> bases,
			array<size_t> bases_offsets,
			array<Constructor> constructors,
			array<CopyConstructor> copy_constructors,
			array<Member> members,
			array<Method> methods,
			array<Static> static_members
		);
		~Class();

		void inherit(vector<Type*> types);
		void setup_class();

		Ref upcast(Ref object, Type& base);
		Ref downcast(Ref object, Type& derived);

		Member& member(cstring name);
		Method& method(cstring name);
		Static& static_member(cstring name);
		Operator& op(cstring name);

		bool has_member(cstring name);
		bool has_method(cstring name);

		Member& member(size_t offset);
		Method& method(Address address);

		bool has_member(size_t offset);
		bool has_method(Address address);

		template <class T> inline Member& member(T member) { return this->member(member_address(member)); }
		template <class T> inline Method& method(T method) { return this->method(member_address(method)); }

		const Constructor* constructor(ConstructorIndex index) const;
		const Constructor* constructor(size_t arguments) const;

		bool is(Type& component);
		Ref as(Ref object, Type& component);

	public:
		Type* m_type;
		Meta* m_meta;

		// Reflection
		array<Type*> m_bases;
		array<size_t> m_bases_offsets;

		array<Constructor> m_constructors;
		array<CopyConstructor> m_copy_constructors; // in a vector until we update to c++17 optional
		array<Destructor> m_destructor; // in a vector until we update to c++17 optional
		array<Member> m_members;
		array<Method> m_methods;

		array<Static> m_static_members;
		array<Function> m_static_functions;

		vector<Operator> m_operators;

		Member* m_id_member = nullptr;
		Member* m_type_member = nullptr;
		Member* m_name_member = nullptr;

		vector<cstring> m_field_names;
		vector<Var> m_field_values;

		// Deep Reflection
		vector<Member*> m_components;
		vector<Member*> m_deep_members;
		vector<Method*> m_deep_methods;

		// Implementation
		using MakePool = unique<Pool>(*)(); MakePool m_make_pool;

		// Deprecated ??
		Type* m_root = nullptr;
		bool m_nested = false;
	};

	inline Ref Member::cast(Ref object) const
	{
		Ref target = object;
		if(object.m_type != m_object_type && g_class[type(object).m_id])
			target = mud::cls(object).upcast(object, *m_object_type);
		return target;
	}

	inline Ref Member::cast_get(Ref object) const
	{
		return this->get(cast(object));
	}

#if 0
	inline Var Member::safe_get(Ref object) const
	{
		Var result = m_default_value;
		result.copy(this->get(cast(object)));
		return result;
	}
#endif

	inline void Member::cast_set(Ref object, Ref value) const
	{
		this->set(cast(object), value);
	}

	export_ inline bool is_root_type(Type& ty) { return !g_class[ty.m_id] || cls(ty).m_root == &ty; }

	export_ template <class T>
	T& upcast(Ref value) { Ref base = cls(value).upcast(value, type<T>()); return val<T>(base); }

	export_ template<typename T_Return, typename T, typename... T_Params>
	inline Method& method(T_Return(T::*meth)(T_Params...)) { return cls<T>().method(member_address(meth)); }
}
