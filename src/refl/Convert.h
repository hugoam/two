//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <refl/Forward.h>
#include <refl/Meta.h>

namespace two
{
	export_ TWO_REFL_EXPORT string to_name(const Type& type, Ref value);
	export_ inline string to_name(Ref value) { return to_name(type(value), value); }

	template <>
	inline void to_string<Ref>(const Ref& object, string& str) { convert(*object.m_type).m_to_string(object.m_value, str); }
}
