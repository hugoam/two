//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <stl/span.h>
#include <type/Type.h>
#include <type/Ref.h>
#endif
#include <refl/Forward.h>
#include <refl/Meta.h>

namespace two
{
	using MemberGet = void*(*)(void*);

	export_ class refl_ TWO_REFL_EXPORT Static
	{
	public:
		Static();
		Static(Type& parent_type, cstring name, Ref value);

		Type* m_parent_type;
		cstring m_name;
		Ref m_value;
	};

	export_ class refl_ TWO_REFL_EXPORT Member
	{
	public:
		enum Flags
		{
			None = 0,
			Pointer = (1 << 0),
			NonMutable = (1 << 1),
			Structure = (1 << 2),
			Component = (1 << 3),
			Link = (1 << 4),
			Value = (1 << 5),
			Id = (1 << 6),
		};

	public:
		Member();
		Member(Type& object_type, size_t offset, Type& type, cstring name, const void* default_value, Flags flags = Flags::None, MemberGet get = nullptr);
		~Member();

		int m_index;
		Type* m_object_type;
		size_t m_offset;
		Type* m_type;
		cstring m_name;
		Ref m_default_value;
		Flags m_flags;
		MemberGet m_get;

		Meta& meta() const { return two::meta(*m_type); }
		Class& cls() const { return two::cls(*m_type); }

		bool is_pointer() const { return (m_flags & Pointer) != 0; }
		bool is_mutable() const { return (m_flags & NonMutable) == 0; }
		bool is_structure() const { return (m_flags & Structure) != 0; }
		bool is_component() const { return (m_flags & Component) != 0; }
		bool is_link() const { return (m_flags & Link) != 0; }
		bool is_value() const { return (m_flags & Value) != 0; }

		inline Ref ref(Ref object) const { return Ref((void*)((char*)object.m_value + m_offset), *m_type); }

		inline Ref get(Ref object) const
		{
			if(m_get) return Ref(m_get(object.m_value), *m_type);
			Ref ref = this->ref(object);
			if(this->is_pointer())
				return Ref(*(void**)ref.m_value, *m_type);
			else
				return ref;
		}

		/*inline const Var& get_value(Ref object) const;
		{
			Var result = m_default_value;
			result.copy(this->get(object));
			return result;
		}*/

		inline void set(Ref object, Ref value) const
		{
			Ref ref = this->ref(object);
			if(this->is_pointer())
				*(void**)ref.m_value = value.m_value;
			else
				assign(ref, value);
		}

		inline Ref cast(Ref object) const;
		inline Ref cast_get(Ref object) const;
		//inline Var safe_get(Ref object) const;
		inline void cast_set(Ref object, Ref value) const;
	};

	export_ template <class T_Value, class T>
	Member& member(T_Value T::*mem) { return cls<T>().member(member_offset(mem)); }

	export_ template <class T_Return, class T, typename... T_Params>
	Member& member(T_Return(T::*meth)(T_Params...)) { return cls<T>().member(member_address(meth)); }

	export_ template <class T_Return, class T, typename... T_Params>
	Member& member(T_Return(T::*meth)(T_Params...) const) { return cls<T>().member(member_address(meth)); }
}
