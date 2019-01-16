#pragma once

#include <refl/Types.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/StringConvert.h>
#endif

namespace mud
{
	export_ template <> inline void to_value(const string& str, mud::TypeClass& val) { val = mud::TypeClass(enu<mud::TypeClass>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::TypeClass& val, string& str) { str = enu<mud::TypeClass>().name(uint32_t(val)); };
	
	
}
