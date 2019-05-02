#pragma once

#include <fract/Types.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/StringOps.h>
#endif

namespace two
{
	export_ template <> inline void to_value(const string& str, two::PatternSampling& val) { val = two::PatternSampling(enu<two::PatternSampling>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::PatternSampling& val, string& str) { str = enu<two::PatternSampling>().name(uint32_t(val)); };
	
	
}
