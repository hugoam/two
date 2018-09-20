//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <refl/Forward.h>
#include <obj/Var.h>
#include <obj/Type.h>

#ifndef MUD_CPP_20
#include <vector>
#include <functional>
#endif

namespace mud
{
	using cstring = const char*;

	export_ enum class refl_ TypeClass : unsigned int
	{
		None = 0,
		Object = 1,
		Struct = 2,
		Entity = 3,
		Sequence = 4,
		BaseType = 5,
		Enum = 6
	};

	export_ template<typename T, typename U> constexpr uintptr_t member_offset(U T::*member)
	{
		return (char*)&((T*)nullptr->*member) - (char*)nullptr;
	}

	export_ template<typename T_Object, typename T_Base> uintptr_t base_offset()
	{
		void* mem = malloc(sizeof(T_Object));
		uintptr_t offset = (char*)static_cast<T_Base*>((T_Object*)mem) - (char*)(T_Object*)mem;
		free(mem);
		return offset;
	}

	export_ class refl_ MUD_REFL_EXPORT Meta
	{
	public:
		Meta(Type& type, Namespace* location, cstring name, size_t size, TypeClass type_class);

		Type* m_type;
		Namespace* m_namespace = nullptr;
		cstring m_name;
		size_t m_size;
		TypeClass m_type_class;

		Ref m_empty_ref;
		Var m_empty_var;

		std::function<Var(Ref)> m_copy_construct;
		std::function<void(Ref, Ref)> m_copy_assign;
	};
	
	export_ extern MUD_REFL_EXPORT std::vector<Meta*> g_meta;
	export_ extern MUD_REFL_EXPORT std::vector<Class*> g_class;
	export_ extern MUD_REFL_EXPORT std::vector<Enum*> g_enu;
	export_ extern MUD_REFL_EXPORT std::vector<Convert*> g_convert;

	export_ inline Meta& meta(Type& type) { return *g_meta[type.m_id]; }
	export_ inline Class& cls(Type& type) { return *g_class[type.m_id]; }
	export_ inline Enum& enu(Type& type) { return *g_enu[type.m_id]; }
	export_ inline Convert& convert(Type& type) { return *g_convert[type.m_id]; }

	export_ template <class T>
	inline Meta& meta() { return meta(type<T>()); }

	export_ template <class T>
	inline Class& cls() { return cls(type<T>()); }

	export_ template <class T>
	inline Enum& enu() { return enu(type<T>()); }

	export_ inline bool is_none(Type& ty) { return &ty == &type<None>(); }
	export_ inline bool is_base_type(Type& ty) { return meta(ty).m_type_class == TypeClass::BaseType; }
	export_ inline bool is_enum(Type& ty) { return meta(ty).m_type_class == TypeClass::Enum; }
	export_ inline bool is_basic(Type& ty) { return meta(ty).m_type_class == TypeClass::BaseType || meta(ty).m_type_class == TypeClass::Enum; }
	export_ inline bool is_struct(Type& ty) { return meta(ty).m_type_class == TypeClass::Struct; }
	export_ inline bool is_object(Type& ty) { return meta(ty).m_type_class == TypeClass::Object || meta(ty).m_type_class == TypeClass::Entity; }
	export_ inline bool is_sequence(Type& ty) { return meta(ty).m_type_class == TypeClass::Sequence; }
	export_ inline bool is_class(Type& ty) { return meta(ty).m_type_class < TypeClass::Sequence; }
	
	export_ inline Meta& meta(const Ref& ref) { return meta(type(ref)); }
	export_ inline Meta& meta(const Var& var) { return meta(*var.m_ref.m_type); }

	export_ inline Class& cls(const Ref& ref) { return cls(type(ref)); }
	export_ inline Class& cls(const Var& var) { return cls(*var.m_ref.m_type); }

	export_ inline Enum& enu(const Ref& ref) { return enu(type(ref)); }
	export_ inline Enum& enu(const Var& var) { return enu(*var.m_ref.m_type); }

	export_ MUD_REFL_EXPORT void copy_construct(Ref dest, Ref source);

	export_ inline Var construct(Type& type)
	{
		return meta(type).m_empty_var;
	}

	export_ MUD_REFL_EXPORT void assign(Ref first, Ref second);
	export_ MUD_REFL_EXPORT void assign_pointer(Ref first, Ref second);
	export_ MUD_REFL_EXPORT bool compare(Ref first, Ref second);

	export_ MUD_REFL_EXPORT bool is_related(Type& input, Type& output);

	export_ MUD_REFL_EXPORT bool convert(Var& input, Type& output, Var& result, bool ref = false);
	export_ MUD_REFL_EXPORT bool convert(Ref input, Type& output, Var& result);
	export_ MUD_REFL_EXPORT Var convert(Ref input, Type& output);

	export_ MUD_REFL_EXPORT bool can_convert(Type& input, Type& output);
	export_ MUD_REFL_EXPORT bool can_convert(Ref input, Type& output);
}
