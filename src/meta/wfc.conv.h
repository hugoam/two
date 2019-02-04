#pragma once

#include <wfc/Types.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/StringOps.h>
#endif

namespace mud
{
	export_ template <> inline void to_value(const string& str, mud::Result& val) { val = mud::Result(enu<mud::Result>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Result& val, string& str) { str = enu<mud::Result>().name(uint32_t(val)); };
	
	
}
