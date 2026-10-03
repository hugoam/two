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
	
	// a pointer Ref is typed with its pointee type, except a cstring which is its own type, and void* which is untyped
	export_ template <class T>
	inline void type_check_pointer(const Ref& ref)
	{
		if constexpr(is_same<T, cstring>) type_check<T>(ref);
		else if constexpr(!is_same<T, void*>) type_check<remove_pointer<T>>(ref);
		else UNUSED(ref);
	}

	// a Ref to a value points to the value, whereas a Ref to a pointer (including a cstring) holds the pointer itself:
	// accessing a pointer through a Ref reads or replaces the pointer, it never writes to the memory it points to

	export_ template <class T>
	inline enable_if<!is_pointer<T>, T&>
		val(Ref& ref) { type_check<T>(ref); return *(T*)(ref.m_value); }

	export_ template <class T>
	inline enable_if<is_pointer<T>, T&>
		val(Ref& ref) { type_check_pointer<T>(ref); return (T&)(ref.m_value); }

	export_ template <class T>
	inline enable_if<!is_pointer<T>, const T&>
		val(const Ref& ref) { type_check<T>(ref); return *(T*)(ref.m_value); }

	export_ template <class T>
	inline enable_if<is_pointer<T>, T>
		val(const Ref& ref) { type_check_pointer<T>(ref); return (T)(ref.m_value); }

	export_ template <class T>
	inline void setval(Ref& ref, T& value) { ref.m_value = &value; ref.m_type = &type_of<T>(value); }
	
	export_ template <class T>
	inline void setval(Ref& ref, T* value) { ref.m_value = (void*)value; ref.m_type = &type_of<T>(value); }
	
	template <>
	inline Ref& val<Ref>(Ref& ref) { return ref; }

	template <>
	inline const Ref& val<Ref>(const Ref& ref) { return ref; }

	export_ template <class T>
	inline T* try_val(Ref object) { if(object && type(object).template is<T>()) return &val<T>(object); else return nullptr; }
}
