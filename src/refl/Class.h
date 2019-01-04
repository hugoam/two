//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <refl/Forward.h>
#include <type/Var.h>
#include <infra/Strung.h>
#include <refl/Method.h>
#include <refl/Member.h>

#ifndef MUD_CPP_20
#include <vector>
#include <functional>
#endif

namespace mud
{
	export_ class refl_ MUD_REFL_EXPORT Class
	{
	public:
		Class(Type& type);
		Class(
			Type& type,
			std::vector<Type*> bases,
			std::vector<size_t> bases_offsets,
			std::vector<Constructor> constructors,
			std::vector<CopyConstructor> copy_constructors,
			std::vector<Member> members,
			std::vector<Method> methods,
			std::vector<Static> static_members
		);
		~Class();

		void inherit(std::vector<Type*> types);
		void setup_class();

		Ref upcast(Ref object, Type& base);
		Ref downcast(Ref object, Type& derived);

		Member& member(cstring name);
		Method& method(cstring name);
		Static& static_member(cstring name);
		Operator& op(cstring name);

		bool has_member(cstring name);
		bool has_method(cstring name);

		Member& member(Address address);
		Method& method(Address address);

		bool has_member(Address address);
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
		Type* m_root;

		std::vector<Type*> m_bases;
		std::vector<size_t> m_bases_offsets;

		bool m_nested = false;

		// Reflection
		std::vector<Constructor> m_constructors;
		std::vector<CopyConstructor> m_copy_constructors; // in a vector until we update to c++17 optional
		std::vector<Destructor> m_destructor; // in a vector until we update to c++17 optional
		std::vector<Member> m_members;
		std::vector<Method> m_methods;

		std::vector<Operator> m_operators;

		std::vector<Static> m_static_members;
		std::vector<Function> m_static_functions;

		Member* m_id_member = nullptr;
		Member* m_type_member = nullptr;
		Member* m_name_member = nullptr;

		std::vector<cstring> m_field_names;
		std::vector<Var> m_field_values;

		// Deep Reflection
		std::vector<Member*> m_components;
		std::vector<Member*> m_deep_members;
		std::vector<Method*> m_deep_methods;

		// Sequence
		Type* m_content = nullptr;
		bool m_content_pointer = false;

		// Implementation
		std::function<unique_ptr<Pool>()> m_make_pool;

		std::function<unique_ptr<Sequence>(Ref)> m_sequence;
		std::function<unique_ptr<Iterable>(Ref)> m_iterable;

		bool m_is_sequence = false;
		bool m_is_iterable = false;
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

	inline Var Member::safe_get(Ref object) const
	{
		Var result = m_default_value;
		result.copy(this->get(cast(object)));
		return result;
	}

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
