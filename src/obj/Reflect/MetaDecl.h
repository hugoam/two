//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Generated/Forward.h>
#include <obj/Reflect/Meta.h>
#include <obj/Reflect/Enum.h>
#include <obj/Reflect/Sequence.h>
#include <obj/Reflect/Convert.h>
#include <obj/Iterable/Sequence.h>
#include <obj/Memory/Pool.h>

namespace mud
{
	template <typename T_Value, typename T_Member, typename T>
	inline auto member_getter(T_Member T::*mem) { return [mem](Ref object, Var& v) { set<T_Value>(v, val<T>(object).*mem); }; }

	template <typename T_Value, typename T_Return, typename T>
	inline auto member_getter(T_Return(T::*func)()) { return [func](Ref object, Var& v) { set<T_Value>(v, (val<T>(object).*func)()); }; }

	template <typename T_Value, typename T_Return, typename T>
	inline auto member_getter(T_Return(T::*func)() const) { return [func](Ref object, Var& v) { set<T_Value>(v, (val<T>(object).*func)()); }; }

	template <typename T_Value, typename T_Member, typename T>
	inline auto member_setter(T_Member T::*mem) { return [mem](Ref object, const Var& v) { val<T>(object).*mem = val<T_Value>(v); }; }

	template <typename T_Value, typename T_Param, typename T>
	inline auto member_setter(void(T::*func)(T_Param)) { return [func](Ref object, const Var& v) { (val<T>(object).*func)(val<T_Value>(v)); }; }

	template <class T>
	void init_store() {}
		
	template <class T, class U>
	void init_vector() { cls<T>().m_iterable = [](Ref value) -> unique_ptr<Iterable> { return make_unique<VectorIterable<U>>(val<std::vector<U>>(value)); };
						 cls<T>().m_sequence = [](Ref value) -> unique_ptr<Sequence> { return make_unique<VectorSequence<U>>(val<std::vector<U>>(value)); }; }
		
	template <class T>
	void init_string() { static Convert convert = { [](const Var& ref, string& str) { to_string<T>(val<T>(ref), str); },
													[](const string& str, Ref ref) { from_string<T>(str, val<T>(ref)); } };
						 type<T>().m_convert = &convert; }

	template <>
	void init_string<void>();

	template <>
	void init_string<cstring>();

	template <class T>
	void init_pool() { cls<T>().m_make_pool = [] { return make_unique<TPool<T>>(); }; }

	template <class T>
	inline typename std::enable_if<std::is_default_constructible<T>::value, void>::type
		init_default_value() { meta<T>().m_empty_var = [] { return var(T()); }; meta<T>().m_empty_ref = [] { return Ref(type<T>()); }; }

	template <class T>
	inline typename std::enable_if<!std::is_default_constructible<T>::value, void>::type
		init_default_value() { meta<T>().m_empty_var = [] { return Ref(type<T>()); }; meta<T>().m_empty_ref = [] { return Ref(type<T>()); }; }

	template <class T>
	inline typename std::enable_if<std::is_copy_assignable<T>::value, void>::type
		init_assign() { meta<T>().m_copy_assign = [](Ref first, Ref second) { val<T>(first) = val<T>(second); }; }

	template <class T>
	inline typename std::enable_if<!std::is_copy_assignable<T>::value, void>::type
		init_assign() {}

	template <>
	void init_assign<cstring>();

	template <class T>
	void meta_type()
	{
		init_default_value<T>();
		init_assign<T>();
	}

	template <class T>
	void meta_basetype()
	{
		meta_type<T>();
		init_string<T>();
	}

	template <class T, class U>
	void meta_sequence()
	{
		meta_type<T>();
		init_vector<T, U>();
	}

	template <class T>
	void meta_class()
	{
		meta_type<T>();
		cls<T>().setup_class();
	}

	template <class T>
	void meta_enum()
	{
		meta_type<T>();
		init_string<T>();
	}

}
