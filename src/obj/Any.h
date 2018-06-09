//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Type.h>
#include <obj/Var.h>
#include <obj/TypeOf.h>
#include <obj/TypeUtils.h>
#include <obj/Unique.h>
#include <obj/Types.h>

namespace mud
{
	export_ template <class T>
	inline typename std::enable_if<!std::is_pointer<T>::value, T&>::type
		val(Ref& ref) { return *(T*)(ref.m_value); } // return *static_cast<T*>(m_value); }

	export_ template <class T>
	inline typename std::enable_if<std::is_pointer<T>::value, T>::type
		val(Ref& ref) { return (T)(ref.m_value); } // static_cast<T>(m_value); }

	export_ template <class T>
	inline typename std::enable_if<!std::is_pointer<T>::value, const T&>::type
		val(const Ref& ref) { return *(T*)(ref.m_value); } // static_cast<T*>(m_value); }

	export_ template <class T>
	inline typename std::enable_if<std::is_pointer<T>::value, T>::type
		val(const Ref& ref) { return (T)(ref.m_value); } // static_cast<T>(m_value); }

	export_ template <class T>
	inline void set(Ref& ref, T& value) { ref.m_value = &value; ref.m_type = &typeof<T>(value); }

	export_ template <class T>
	inline void set(Ref& ref, T* value) { ref.m_value = (void*)value; ref.m_type = &typeof<T>(value); }

	export_ inline void set(Ref& ref, cstring value) { ref.m_value = (void*)value; ref.m_type = &type<cstring>(); }

	export_ template <class T, bool onlyref = is_object_pointer<T>::value || !is_copyable<T>::value>
	struct ValueSemantic : std::true_type {};

	export_ template <class T>
	struct ValueSemantic<T, true> : std::false_type {};

	export_ template <class T>
	class TAny : public Any
	{
	public:
		template <class U>
		TAny(U&& value) : m_content(any_copy<T>(std::forward<U>(value))) {}
		TAny() : m_content() {}

		virtual Ref ref() const { return Ref(const_cast<T*>(&m_content)); }
		virtual void assign(Ref ref) { any_assign<T>(m_content, val<T>(ref)); }
		virtual void assign(const Any& other) { any_assign<T>(m_content, static_cast<const TAny<T>&>(other).m_content); }
		virtual bool compare(const Any& other) const { return any_compare<T>(m_content, static_cast<const TAny<T>&>(other).m_content); }
		virtual unique_ptr<Any> clone() const { return make_unique<TAny<T>>(any_copy<T>(m_content)); }

		T m_content;
	};

	export_ template <class T>
	inline T& val(Val& v) { return static_cast<TAny<T>&>(*v.m_any).m_content; }

	export_ template <class T>
	inline const T& val(const Val& v) { return static_cast<const TAny<T>&>(*v.m_any).m_content; }

	export_ template <class T, class U>
	inline void set(Val& v, U&& value) { static_cast<TAny<T>&>(*v.m_any).m_content = value; }
	
	export_ template <class T>
	inline T& val(Var& var) { return val<T>(var.m_ref); }

	export_ template <class T>
	inline T val(const Var& var) { return val<T>(var.m_ref); }

	export_ template <>
	inline cstring& val(Var& var) { return (cstring&)var.m_ref.m_value; }

	export_ template <>
	inline cstring val(const Var& var) { return (cstring) var.m_ref.m_value; }

	export_ template <class T, class U>
	inline typename std::enable_if<ValueSemantic<T>::value, void>::type
		set(Var& var, U&& value) { if(var.m_mode == VAL) { set<T>(var.m_val, value); set(var.m_ref, val<T>(var.m_val)); } else set<T>(var.m_ref, value); }

	export_ template <class T, class U>
	inline typename std::enable_if<!ValueSemantic<T>::value, void>::type
		set(Var& var, U&& value) { set(var.m_ref, std::forward<U>(value)); }

	export_ template <class T, class U>
	inline Var make_val(U&& value) { return Val{ type<T>(), make_unique<TAny<T>>(std::forward<U>(value)) }; }

	export_ template <class T, class U>
	inline typename enable_if<ValueSemantic<T>::value, Var>::type
		var_value(U&& value) { return make_val<T>(std::forward<U>(value)); }

	export_ template <class T, class U>
	inline typename enable_if<!ValueSemantic<T>::value, Var>::type
		var_value(U&& value) { return Ref(&value); }

	export_ template <class T, class U>
	inline typename enable_if<!is_object_pointer<T>::value, Var>::type
		make_var(U&& value) { return var_value<typename unqual_type<T>::type>(std::forward<T>(value)); }

	export_ template <class T, class U>
	inline typename enable_if<is_object_pointer<T>::value, Var>::type
		make_var(U&& value) { return Ref(value); }

	export_ template <class T>
	inline Var var(T&& value) { return make_var<T>(std::forward<T>(value)); }

	export_ template <>
	inline Var var(Ref&& ref) { return Var(ref); }

	export_ inline Var var(cstring value) { return Ref(const_cast<char*>(value), type<cstring>()); }
}
