//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <type/Type.h>
#include <type/Ref.h>
//#include <type/Types.h>

namespace two
{
	export_ template <class T>
	inline void type_check(const Ref& ref) { UNUSED(ref); assert(type(ref).is<T>()); }
	
	export_ template <class T>
	inline enable_if<!is_pointer<T> || is_same<T, cstring>, T&>
		val(Ref& ref) { type_check<T>(ref); return *(T*)(ref.m_value); }

	export_ template <class T>
	inline enable_if<is_pointer<T> && !is_same<T, cstring>, T>
		val(Ref& ref) { type_check<remove_pointer<T>>(ref); return (T)(ref.m_value); }

	export_ template <class T>
	inline enable_if<!is_pointer<T> || is_same<T, cstring>, const T&>
		val(const Ref& ref) { type_check<T>(ref); return *(T*)(ref.m_value); }

	export_ template <class T>
	inline enable_if<is_pointer<T> && !is_same<T, cstring>, T>
		val(const Ref& ref) { type_check<remove_pointer<T>>(ref); return (T)(ref.m_value); }

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

	export_ template <class T>
	inline T* try_val(Ref object) { if(object && type(object).template is<T>()) return &val<T>(object); else return nullptr; }
}
