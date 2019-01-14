//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <type/Type.h>
#include <type/Var.h>
#include <type/TypeOf.h>
#include <type/TypeUtils.h>
#include <type/Unique.h>
#include <type/Types.h>

#include <cassert>

namespace mud
{
	export_ template <class T>
	inline void type_check(const Ref& ref) { UNUSED(ref); assert(type(ref).is<T>()); }
	
	export_ template <class T>
	inline typename std::enable_if<!std::is_pointer<T>::value, T&>::type
		val(Ref& ref) { type_check<T>(ref); return *(T*)(ref.m_value); }

	export_ template <class T>
	inline typename std::enable_if<std::is_pointer<T>::value, T>::type
		val(Ref& ref) { type_check<typename std::remove_pointer<T>::type>(ref); return (T)(ref.m_value); }

	export_ template <class T>
	inline typename std::enable_if<!std::is_pointer<T>::value, const T&>::type
		val(const Ref& ref) { type_check<T>(ref); return *(T*)(ref.m_value); }

	export_ template <class T>
	inline typename std::enable_if<std::is_pointer<T>::value, T>::type
		val(const Ref& ref) { type_check<typename std::remove_pointer<T>::type>(ref); return (T)(ref.m_value); }

	export_ template <class T>
	inline void set(Ref& ref, T& value) { ref.m_value = &value; ref.m_type = &type_of<T>(value); }

	export_ template <class T>
	inline void set(Ref& ref, T* value) { ref.m_value = (void*)value; ref.m_type = &type_of<T>(value); }
	
	export_ template <>
	inline Ref& val<Ref>(Ref& ref) { return ref; }

	export_ template <>
	inline const Ref& val<Ref>(const Ref& ref) { return ref; }
	
	export_ template <>
	inline void* val<void*>(Ref& ref) { return ref.m_value; }

	export_ template <>
	inline void* val<void*>(const Ref& ref) { return ref.m_value; }

	export_ template <>
	inline cstring val<cstring>(Ref& ref) { return (cstring)ref.m_value; }

	export_ template <>
	inline cstring val<cstring>(const Ref& ref) { return (cstring)ref.m_value; }
	
	export_ inline void set(Ref& ref, cstring value) { ref.m_value = (void*)value; ref.m_type = &type<cstring>(); }

	template <class T>
	export_ inline T* try_val(Ref object) { if (object && type(object).template is<T>()) return &val<T>(object); else return nullptr; }

	export_ template <class T, bool onlyref = is_object_pointer<T>::value || !is_copyable<T>::value>
	struct ValueSemantic : std::true_type {};

	export_ template <class T>
	struct ValueSemantic<T, true> : std::false_type {};

	template <class T>
	using IsSmallObject = integral_constant<bool, sizeof(T) <= sizeof(void*)*3>;

	export_ template <class T, bool small = IsSmallObject<T>::value>
	class TAnyHandlerImpl : public AnyHandler
	{
	public:
		template <class U>
		static void create(Any& any, const AnyHandler& handler, U&& value) { any.m_pointer = new T(std::forward<U>(value)); any.m_handler = &handler; }

		static inline T& value(Any& any) { return *static_cast<T*>(any.m_pointer); }
		static inline const T& value(const Any& any) { return *static_cast<const T*>(any.m_pointer); }

		virtual void destroy(Any& any) const { delete static_cast<T*>(any.m_pointer); }
		virtual void copy(Any& any, const Any& other) const { create(any, *this, value(other));  }
		virtual void move(Any& any, Any& other) const { any.swap(other); }
	};

	export_ template <class T>
	class TAnyHandlerImpl<T, true> : public AnyHandler
	{
	public:
		template <class U>
		static void create(Any& any, const AnyHandler& handler, U&& value) { new ((void*)&any.m_storage) T(std::forward<U>(value)); any.m_handler = &handler; }

		static inline T& value(Any& any) { return *static_cast<T*>((void*)&any.m_storage); }
		static inline const T& value(const Any& any) { return *static_cast<const T*>((void*)&any.m_storage); }

		virtual void destroy(Any& any) const { any_destruct<T>(value(any)); }
		virtual void copy(Any& any, const Any& other) const { create(any, *this, value(other)); }
		virtual void move(Any& any, Any& other) const { create(any, *this, std::move(value(other))); destroy(other); }
	};

	export_ template <class T>
	class TAnyHandler : public TAnyHandlerImpl<T>
	{
	public:
		template <class U>
		static Any create(U&& value) { Any any; TAnyHandlerImpl<T>::create(any, me, std::forward<U>(value)); return any; }

		virtual Ref ref(const Any& any) const { return Ref(&const_cast<T&>(this->value(any))); }
		virtual void assign(Any& any, Ref ref) const { any_assign<T>(this->value(any), val<T>(ref)); }
		virtual void assign(Any& any, const Any& other) const { any_assign<T>(this->value(any), this->value(other)); }
		virtual bool compare(const Any& any, const Any& other) const { return any_compare<T>(this->value(any), this->value(other)); }

		static TAnyHandler<T> me;
	};

	template <class T>
	TAnyHandler<T> TAnyHandler<T>::me;

	export_ template <class T>
	inline T& val(Any& v) { return TAnyHandler<T>::value(v); }

	export_ template <class T>
	inline const T& val(const Any& v) { return TAnyHandler<T>::value(v); }

	export_ template <class T, class U>
	inline void set(Any& v, U&& value) { TAnyHandler<T>::value(v) = value; }
	
	export_ template <class T>
	inline T& val(Var& var) { return val<T>(var.m_ref); }

	export_ template <class T>
	inline T val(const Var& var) { return val<T>(var.m_ref); }
	
	export_ template <>
	inline void*& val(Var& var) { return var.m_ref.m_value; }

	export_ template <>
	inline void* val(const Var& var) { return var.m_ref.m_value; }

	export_ template <>
	inline cstring& val(Var& var) { return (cstring&)var.m_ref.m_value; }

	export_ template <>
	inline cstring val(const Var& var) { return (cstring)var.m_ref.m_value; }

	export_ template <class T, class U>
	inline typename std::enable_if<ValueSemantic<T>::value, void>::type
		set(Var& var, U&& value) { if(var.m_mode == VAL) { set<T>(var.m_any, value); set(var.m_ref, val<T>(var.m_any)); } else set<T>(var.m_ref, value); }

	export_ template <class T, class U>
	inline typename std::enable_if<!ValueSemantic<T>::value, void>::type
		set(Var& var, U&& value) { set(var.m_ref, std::forward<U>(value)); }

	export_ template <class T, class U>
	inline Var make_any(U&& value) { return TAnyHandler<T>::create(std::forward<U>(value)); }
	
	export_ template <class T, class U>
	inline typename enable_if<ValueSemantic<T>::value, Var>::type
		var_value(U&& value) { return make_any<T>(std::forward<U>(value)); }

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
