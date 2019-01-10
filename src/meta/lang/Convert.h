#pragma once

#include <lang/Types.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/StringConvert.h>
#endif

namespace mud
{
	export_ template <> inline void from_string(const string& str, mud::Language& val) { val = static_cast<mud::Language>(enu<mud::Language>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Language& val, string& str) { str = enu<mud::Language>().m_map[size_t(val)]; };
	
	
}
