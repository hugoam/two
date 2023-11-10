#pragma once

#ifndef TWO_MODULES
#include <tool/Types.h>
#endif

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/StringOps.h>
#endif

namespace two
{
	export_ template <> inline void to_value(const string& str, two::ToolState& val) { val = two::ToolState(enu<two::ToolState>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::ToolState& val, string& str) { str = enu<two::ToolState>().name(uint32_t(val)); };
	
	
}
