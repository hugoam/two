//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/move.h>
#include <type/Type.h>
#include <type/Ref.h>
#include <type/TypeUtils.h>
#include <type/Types.h>

#include <cassert>
#include <new>

namespace mud
{
	export_ template <class T>
	inline void type_check(const Ref& ref) { UNUSED(ref); assert(type(ref).is<T>()); }
	
	export_ template <class T>
	inline typename enable_if<!is_pointer<T>::value, T&>::type
		val(Ref& ref) { type_check<T>(ref); return *(T*)(ref.m_value); }

	export_ template <class T>
	inline typename enable_if<is_pointer<T>::value, T>::type
		val(Ref& ref) { type_check<typename std::remove_pointer<T>::type>(ref); return (T)(ref.m_value); }

	export_ template <class T>
	inline typename enable_if<!is_pointer<T>::value, const T&>::type
		val(const Ref& ref) { type_check<T>(ref); return *(T*)(ref.m_value); }

	export_ template <class T>
	inline typename enable_if<is_pointer<T>::value, T>::type
		val(const Ref& ref) { type_check<typename std::remove_pointer<T>::type>(ref); return (T)(ref.m_value); }

	export_ template <class T>
	inline void setval(Ref& ref, T& value) { ref.m_value = &value; ref.m_type = &type_of<T>(value); }
	
	export_ template <class T>
	inline void setval(Ref& ref, T* value) { ref.m_value = (void*)value; ref.m_type = &type_of<T>(value); }
	
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
	
	export_ inline void setval(Ref& ref, cstring value) { ref.m_value = (void*)value; ref.m_type = &type<cstring>(); }

	template <class T>
	export_ inline T* try_val(Ref object) { if (object && type(object).template is<T>()) return &val<T>(object); else return nullptr; }
}
