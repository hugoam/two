//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/vector.h>
#include <type/Ref.h>
#include <refl/Forward.h>
#include <refl/Method.h>
#include <refl/Member.h>

namespace two
{
	export_ using cstring = const char*;

	export_ class refl_ TWO_REFL_EXPORT Class
	{
	public:
		Class(Type& type);
		Class(
			Type& type,
			span<Type*> bases,
			span<size_t> bases_offsets,
			span<Constructor> constructors,
			span<CopyConstructor> copy_constructors,
			span<Member> members,
			span<Method> methods,
			span<Static> static_members
		);
		~Class();

		void inherit(span<Type*> types);
		void setup_class();

		Ref upcast(Ref object, const Type& base);
		Ref downcast(Ref object, const Type& derived);

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

		template <class T> inline Member& member(T member) { return this->member(member_offset(member)); }
		template <class T> inline Method& method(T method) { return this->method(member_address(method)); }

		const Constructor* constructor(ConstructorIndex index) const;
		const Constructor* constructor(size_t arguments) const;

		bool is(const Type& component);
		Ref as(Ref object, const Type& component);

	public:
		Type* m_type;
		Meta* m_meta;

		// Reflection
		span<Type*> m_bases;
		span<size_t> m_bases_offsets;

		span<Constructor> m_constructors;
		span<CopyConstructor> m_copy_constructors; // in a vector until we update to c++17 optional
		span<Destructor> m_destructor; // in a vector until we update to c++17 optional
		span<Member> m_members;
		span<Method> m_methods;

		span<Static> m_static_members;
		span<Function> m_static_functions;

		vector<Operator> m_operators;

		Member* m_id_member = nullptr;
		Member* m_type_member = nullptr;
		Member* m_name_member = nullptr;

		vector<cstring> m_field_names;
		vector<Ref> m_field_values;

		// Deep Reflection
		vector<Member*> m_components;
		vector<Member*> m_deep_members;
		vector<Method*> m_deep_methods;

		// Implementation
		//using MakePool = unique<Pool>(*)(); MakePool m_make_pool;

		// Deprecated ??
		Type* m_root = nullptr;
		bool m_nested = false;
	};

	inline Ref Member::cast(Ref object) const
	{
		Ref target = object;
		if(object.m_type != m_object_type && g_class[type(object).m_id])
			target = two::cls(object).upcast(object, *m_object_type);
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

	export_ inline bool is_root_type(const Type& ty) { return !g_class[ty.m_id] || cls(ty).m_root == &ty; }
	export_ inline bool is_abstract(const Type& ty) { return g_class[ty.m_id] && cls(ty).m_type_member; }
	//export_ template <class T>
	//T& upcast(Ref value) { Ref base = cls(value).upcast(value, type<T>()); return val<T>(base); }

	export_ template <class T_Return, class T, typename... T_Params>
	inline Method& method(T_Return(T::*meth)(T_Params...)) { return cls<T>().method(member_address(meth)); }
}
