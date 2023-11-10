#pragma once

#ifndef TWO_MODULES
#include <lang/Types.h>
#endif

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/StringOps.h>
#endif

namespace two
{
	export_ template <> inline void to_value(const string& str, two::Language& val) { val = two::Language(enu<two::Language>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::Language& val, string& str) { str = enu<two::Language>().name(uint32_t(val)); };
	
	
}
