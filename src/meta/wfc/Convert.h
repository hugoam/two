#pragma once

#include <wfc/Types.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/StringConvert.h>
#endif

namespace mud
{
	export_ template <> inline void from_string(const string& str, mud::Result& val) { val = static_cast<mud::Result>(enu<mud::Result>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Result& val, string& str) { str = enu<mud::Result>().m_map[size_t(val)]; };
	
	
}
