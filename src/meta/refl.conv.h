#pragma once

#include <refl/Types.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/StringOps.h>
#endif

namespace two
{
	export_ template <> inline void to_value(const string& str, two::TypeClass& val) { val = two::TypeClass(enu<two::TypeClass>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::TypeClass& val, string& str) { str = enu<two::TypeClass>().name(uint32_t(val)); };
	
	
}
