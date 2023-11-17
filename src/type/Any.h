//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <type/RefVal.h>
#include <type/TypeUtils.h>
#include <type/Var.h>
#include <type/TypeOf.h>
#include <type/Types.h>

namespace two
{
	export_ template <class T, bool onlyref = is_object_pointer<T> || !is_copyable<T>>
	constexpr bool ValueSemantic = true;

	export_ template <class T>
	constexpr bool ValueSemantic<T, true> = false;

	template <class T>
	constexpr bool IsSmallObject = sizeof(T) <= sizeof(void*)*3;

	export_ template <class T, bool small = IsSmallObject<T>>
	class TAnyHandlerImpl : public AnyHandler
	{
	public:
		template <class U>
		static void create(Any& any, const AnyHandler& handler, U&& value) { any.m_pointer = new T(static_cast<U&&>(value)); any.m_handler = &handler; }

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
		static void create(Any& any, const AnyHandler& handler, U&& value) { new (stl::placeholder(), (void*)&any.m_storage) T(static_cast<U&&>(value)); any.m_handler = &handler; }

		static inline T& value(Any& any) { return *static_cast<T*>((void*)&any.m_storage); }
		static inline const T& value(const Any& any) { return *static_cast<const T*>((void*)&any.m_storage); }

		virtual void destroy(Any& any) const { any_destruct<T>(value(any)); }
		virtual void copy(Any& any, const Any& other) const { create(any, *this, value(other)); }
		virtual void move(Any& any, Any& other) const
		{
			using two::move;
			create(any, *this, move(value(other)));
			destroy(other);
		}
	};

	export_ template <class T>
	class TAnyHandler : public TAnyHandlerImpl<T>
	{
	public:
		template <class U>
		static Any create(U&& value) { Any any; TAnyHandlerImpl<T>::create(any, me, static_cast<U&&>(value)); return any; }

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
	inline void setval(Any& v, U&& value) { TAnyHandler<T>::value(v) = value; }
	
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
	inline enable_if<ValueSemantic<T>, void>
		setval(Var& var, U&& value) { if(var.m_mode == VarMode::Val) { setval<T>(var.m_any, value); /*setval(var.m_ref, val<T>(var.m_any));*/ } else setval<T>(var.m_ref, value); }

	export_ template <class T, class U>
	inline enable_if<!ValueSemantic<T>, void>
		setval(Var& var, U&& value) { setval(var.m_ref, static_cast<U&&>(value)); }

	export_ template <class T, class U>
	inline Var make_any(U&& value) { return TAnyHandler<T>::create(static_cast<U&&>(value)); }
	
	export_ template <class T, class U>
	inline enable_if<ValueSemantic<T>, Var>
		var_value(U&& value) { return make_any<T>(static_cast<U&&>(value)); }

	export_ template <class T, class U>
	inline enable_if<!ValueSemantic<T>, Var>
		var_value(U&& value) { return Ref(&value); }

	export_ template <class T, class U>
	inline enable_if<!is_object_pointer<T>, Var>
		make_var(U&& value) { return var_value<unqual_type<T>>(static_cast<T&&>(value)); }

	export_ template <class T, class U>
	inline enable_if<is_object_pointer<T>, Var>
		make_var(U&& value) { return Ref(value); }

	export_ template <class T>
	inline Var var(T&& value) { return make_var<T>(static_cast<T&&>(value)); }

	export_ template <>
	inline Var var(Ref&& ref) { return Var(ref); }

	export_ inline Var var(cstring value) { return Ref(const_cast<char*>(value), type<cstring>()); }
}
