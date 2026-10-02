#pragma once

#if defined TWO_TYPE_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/StringOps.h>
#endif

namespace two
{
	template <> inline void to_value(const string& str, two::Language& val) { val = two::Language(enu<two::Language>().value(str.c_str())); };
	template <> inline void to_string(const two::Language& val, string& str) { str = enu<two::Language>().name(uint32_t(val)); };
	
	
}
