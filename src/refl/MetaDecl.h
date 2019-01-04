//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <refl/Forward.h>
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <refl/Sequence.h>
#include <refl/Convert.h>
#include <refl/Sequence.h>
#include <refl/Namespace.h>
#include <refl/Vector.h>
#include <pool/Pool.h>

namespace mud
{
	export_ template <typename T_Value, typename T_Member, typename T>
	inline auto member_getter(T_Member T::*mem) { return [mem](Ref object, Var& v) { set<T_Value>(v, val<T>(object).*mem); }; }

	export_ template <typename T_Value, typename T_Return, typename T>
	inline auto member_getter(T_Return(T::*func)()) { return [func](Ref object, Var& v) { set<T_Value>(v, (val<T>(object).*func)()); }; }

	export_ template <typename T_Value, typename T_Return, typename T>
	inline auto member_getter(T_Return(T::*func)() const) { return [func](Ref object, Var& v) { set<T_Value>(v, (val<T>(object).*func)()); }; }

	export_ template <typename T_Value, typename T_Member, typename T>
	inline auto member_setter(T_Member T::*mem) { return [mem](Ref object, const Var& v) { val<T>(object).*mem = val<T_Value>(v); }; }

	export_ template <typename T_Value, typename T_Param, typename T>
	inline auto member_setter(void(T::*func)(T_Param)) { return [func](Ref object, const Var& v) { (val<T>(object).*func)(val<T_Value>(v)); }; }

	export_ template <class T>
	void init_store() {}
		
	export_ template <class T, class U>
	void init_vector() { cls<T>().m_iterable = [](Ref value) -> unique_ptr<Iterable> { return make_unique<VectorIterable<U>>(val<std::vector<U>>(value)); };
						 cls<T>().m_sequence = [](Ref value) -> unique_ptr<Sequence> { return make_unique<VectorSequence<U>>(val<std::vector<U>>(value)); }; }
		
	export_ template <class T>
	void init_string() { static Convert convert = { [](const Var& ref, string& str) { to_string<T>(val<T>(ref), str); },
													[](const string& str, Ref ref) { from_string<T>(str, val<T>(ref)); } };
						 g_convert[type<T>().m_id] = &convert; }

	export_ template <>
	MUD_REFL_EXPORT void init_string<void>();

	export_ template <>
	MUD_REFL_EXPORT void init_string<cstring>();

	export_ template <class T>
	void init_pool() { cls<T>().m_make_pool = [] { return make_unique<TPool<T>>(); }; }

	export_ template <class T>
	inline typename std::enable_if<std::is_default_constructible<T>::value, void>::type
		init_default_value() { meta<T>().m_empty_var = var(T()); meta<T>().m_empty_ref = Ref(type<T>()); }

	export_ template <class T>
	inline typename std::enable_if<!std::is_default_constructible<T>::value, void>::type
		init_default_value() { meta<T>().m_empty_var = Ref(type<T>()); meta<T>().m_empty_ref = Ref(type<T>()); }
	
	export_ template <>
	inline void	init_default_value<Ref>() { meta<Ref>().m_empty_var = Ref(); meta<Ref>().m_empty_ref = Ref(); }

	export_ template <class T>
	inline typename std::enable_if<std::is_copy_assignable<T>::value, void>::type
		init_assign() { meta<T>().m_copy_assign = [](Ref first, Ref second) { val<T>(first) = val<T>(second); }; }

	export_ template <class T>
	inline typename std::enable_if<!std::is_copy_assignable<T>::value, void>::type
		init_assign() {}

	export_ template <class T>
		inline typename std::enable_if<std::is_trivially_destructible<T>::value, void>::type
		init_destructor() {}

	export_ template <class T>
		inline typename std::enable_if<!std::is_trivially_destructible<T>::value, void>::type
		init_destructor() { cls<T>().m_destructor.push_back({ type<T>(), [](Ref ref) { val<T>(ref).~T(); } }); }

	export_ template <>
	MUD_REFL_EXPORT void init_assign<cstring>();

	export_ template <class T>
	void meta_type()
	{
		init_default_value<T>();
		init_assign<T>();
	}

	export_ template <class T>
	void meta_basetype()
	{
		meta_type<T>();
		init_string<T>();
	}

	export_ template <class T, class U>
	void meta_sequence()
	{
		meta_type<T>();
		init_vector<T, U>();
	}

	export_ template <class T>
	void meta_class()
	{
		meta_type<T>();
		init_destructor<T>();
		cls<T>().setup_class();
	}

	export_ template <class T>
	void meta_enum()
	{
		meta_type<T>();
		init_string<T>();
	}
}
