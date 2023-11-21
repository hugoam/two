//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <type/Forward.h>

namespace two
{
	export_ class Type;

	export_ template <class T>
	using unqual_type = remove_cv<remove_reference<T>>;

	export_ template <class T>
	using type_class = remove_pointer<unqual_type<T>>;
	
	inline void sink_type(Type&) {}

	export_ template <class T, typename = int>
	constexpr bool is_typed = false;

	export_ template <class T>
	constexpr bool is_typed<T, decltype(sink_type(declval<T>().m_type), 0)> = true;

	export_ template <class T>
	inline enable_if<!is_typed<T>,
		Type&> type_of(const T& value) { UNUSED(value); return type<T>(); }

	export_ template <class T>
	inline enable_if<is_typed<T>,
		Type&> type_of(const T& value) { return value.m_type; }

	export_ template <class T>
	inline enable_if<!is_typed<T>,
		Type&> type_of(const T* value) { UNUSED(value); return type<T>(); }

	export_ template <class T>
	inline enable_if<is_typed<T>,
		Type&> type_of(const T* value) { if(value) return value->m_type; return type<T>(); }
}
