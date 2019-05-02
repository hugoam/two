//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/vector.h>
#include <stl/string.h>
#include <refl/Forward.h>
#include <type/Ref.h>
#include <type/Var.h>
#include <type/Type.h>

namespace two
{
	using cstring = const char*;

	export_ enum class refl_ TypeClass : unsigned int
	{
		None = 0,
		Object = 1,
		Struct = 2,
		Sequence = 4,
		BaseType = 5,
		Enum = 6
	};

	export_ template <class T_Object, class T_Base> uintptr_t base_offset()
	{
		uintptr_t offset = (char*)static_cast<T_Base*>((T_Object*)0) - (char*)(T_Object*)0;
		return offset;
	}

	export_ class refl_ TWO_REFL_EXPORT Meta
	{
	public:
		Meta(Type& type, Namespace* location, cstring name, size_t size, TypeClass type_class, bool is_array = false);

		Type* m_type;
		Namespace* m_namespace = nullptr;
		cstring m_name;
		size_t m_size;
		TypeClass m_type_class;
		bool m_is_array = false;

		const void* m_empty_value;
		Ref m_empty_ref;
		Var m_empty_var;

		using CopyConstruct = void(*)(void*, void*); CopyConstruct m_copy_construct;
		using CopyAssign = void(*)(void*, void*); CopyAssign m_copy_assign;

		inline void copy_construct(Ref first, Ref other) const { m_copy_construct(first.m_value, other.m_value); }
		inline void copy_assign(Ref first, Ref other) const { m_copy_assign(first.m_value, other.m_value); }
	};

	export_ class refl_ TWO_REFL_EXPORT Convert
	{
	public:
		using ToString = void(*)(void*, string&); ToString m_to_string;
		using ToValue = void(*)(const string&, void*); ToValue m_to_value;

		inline void to_string(Ref object, string& str) const { m_to_string(object.m_value, str); }
		inline void to_value(const string& str, Ref object) const { m_to_value(str, object.m_value); }
	};

	export_ extern TWO_REFL_EXPORT vector<Meta*> g_meta;
	export_ extern TWO_REFL_EXPORT vector<Class*> g_class;
	export_ extern TWO_REFL_EXPORT vector<Enum*> g_enu;
	export_ extern TWO_REFL_EXPORT vector<Convert*> g_convert;
	export_ extern TWO_REFL_EXPORT vector<Iterable*> g_iterable;
	export_ extern TWO_REFL_EXPORT vector<Sequence*> g_sequence;

	export_ inline Meta& meta(const Type& type) { return *g_meta[type.m_id]; }
	export_ inline Class& cls(const Type& type) { return *g_class[type.m_id]; }
	export_ inline Enum& enu(const Type& type) { return *g_enu[type.m_id]; }
	export_ inline Convert& convert(const Type& type) { return *g_convert[type.m_id]; }
	export_ inline Iterable& iter(const Type& type) { return *g_iterable[type.m_id]; }
	export_ inline Sequence& sequence(const Type& type) { return *g_sequence[type.m_id]; }

	export_ template <class T>
	inline Meta& meta() { return meta(type<T>()); }

	export_ template <class T>
	inline Class& cls() { return cls(type<T>()); }

	export_ template <class T>
	inline Enum& enu() { return enu(type<T>()); }

	export_ inline bool is_base_type(const Type& ty) { return meta(ty).m_type_class == TypeClass::BaseType; }
	export_ inline bool is_enum(const Type& ty) { return meta(ty).m_type_class == TypeClass::Enum; }
	export_ inline bool is_basic(const Type& ty) { return meta(ty).m_type_class == TypeClass::BaseType || meta(ty).m_type_class == TypeClass::Enum; }
	export_ inline bool is_struct(const Type& ty) { return meta(ty).m_type_class == TypeClass::Struct; }
	export_ inline bool is_object(const Type& ty) { return meta(ty).m_type_class == TypeClass::Object; }
	export_ inline bool is_sequence(const Type& ty) { return meta(ty).m_type_class == TypeClass::Sequence; }
	export_ inline bool is_class(const Type& ty) { return meta(ty).m_type_class < TypeClass::Sequence; }

	export_ inline bool is_array(const Type& ty) { return meta(ty).m_is_array; }

	export_ inline bool is_iterable(const Type& ty) { return g_iterable[ty.m_id] != nullptr; }
	//export_ inline bool is_sequence(const Type& ty) { return g_sequence[ty.m_id] != nullptr; }

	export_ inline Meta& meta(const Ref& ref) { return meta(type(ref)); }
	export_ inline Class& cls(const Ref& ref) { return cls(type(ref)); }
	export_ inline Enum& enu(const Ref& ref) { return enu(type(ref)); }
	export_ inline Iterable& iter(const Ref& ref) { return iter(type(ref)); }
	export_ inline Sequence& sequence(const Ref& ref) { return sequence(type(ref)); }

	export_ TWO_REFL_EXPORT void copy_construct(Ref dest, Ref source);

	//export_ inline Var construct(Type& type)
	//{
	//	return meta(type).m_empty_var;
	//}

	export_ TWO_REFL_EXPORT void assign(Ref first, Ref second);
	export_ TWO_REFL_EXPORT void assign_pointer(Ref first, Ref second);
	export_ TWO_REFL_EXPORT bool compare(Ref first, Ref second);

	export_ TWO_REFL_EXPORT bool is_related(const Type& input, const Type& output);

	export_ TWO_REFL_EXPORT bool convert(Var& input, const Type& output, Var& result, bool ref = false);
	export_ TWO_REFL_EXPORT bool convert(Ref input, const Type& output, Var& result);
	export_ TWO_REFL_EXPORT Var convert(Ref input, const Type& output);

	export_ TWO_REFL_EXPORT bool can_convert(const Type& input, const Type& output);
	export_ TWO_REFL_EXPORT bool can_convert(Ref input, const Type& output);
}
