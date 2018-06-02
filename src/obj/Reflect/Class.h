//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Generated/Forward.h>
#include <obj/Var.h>
#include <obj/Strung.h>
#include <obj/Reflect/Method.h>
#include <obj/Reflect/Member.h>

#ifndef MUD_CPP_20
#include <vector>
#include <functional>
#endif

namespace mud
{
	export_ class _refl_ MUD_OBJ_EXPORT Class
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

		Member& member(cstring name);
		Method& method(cstring name);

		bool has_member(cstring name);
		bool has_method(cstring name);

		Member& member(Address address);
		Method& method(Address address);

		bool has_member(Address address);
		bool has_method(Address address);

		const Constructor* constructor(ConstructorIndex index) const;
		const Constructor* constructor(size_t arguments) const;

		Complex& get_stem(Ref object);
		bool is_related(Ref object, Type& type);
		Ref get_related(Ref object, Type& type);

	public:
		Type* m_type;
		Meta* m_meta;
		Type* m_root;
		Type* m_content = nullptr;

		std::vector<Type*> m_bases;
		std::vector<size_t> m_bases_offsets;

		bool m_nested = false;

		// Reflection
		std::vector<Constructor> m_constructors;
		std::vector<CopyConstructor> m_copy_constructors; // in a vector until we update to c++17 optional
		std::vector<Destructor> m_destructor; // in a vector until we update to c++17 optional
		std::vector<Member> m_members;
		std::vector<Method> m_methods;

		std::vector<Static> m_static_members;
		std::vector<Function> m_static_functions;

		Member* m_id_member = nullptr;
		Member* m_type_member = nullptr;
		Member* m_name_member = nullptr;

		std::vector<cstring> m_field_names;
		std::vector<Var> m_field_values;

		// Deep Reflection
		std::vector<Member*> m_deep_members;
		std::vector<Method*> m_deep_methods;

		// Complex
		Prototype* m_prototype;
		std::vector<Prototype*> m_prototypes;
		std::vector<Type*> m_components;

		// Implementation
		std::function<unique_ptr<Pool>()> m_make_pool;

		std::function<unique_ptr<Sequence>(Ref)> m_sequence;
		std::function<unique_ptr<Iterable>(Ref)> m_iterable;
	};

	export_ inline bool is_root_type(Type& ty) { return !ty.m_class || ty.m_class->m_root == &ty; }

	export_ template <class T>
	T& upcast(Ref value) { Ref base = cls(value).upcast(value, type<T>()); return val<T>(base); }

	export_ template<typename T_Return, typename T, typename... T_Params>
	inline Method& method(T_Return(T::*meth)(T_Params...)) { return cls<T>().method(member_address(meth)); }
}
