#pragma once

#if defined TWO_TYPE_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/StringOps.h>
#endif

namespace two
{
	template <> inline void to_value(const string& str, two::ToolState& val) { val = two::ToolState(enu<two::ToolState>().value(str.c_str())); };
	template <> inline void to_string(const two::ToolState& val, string& str) { str = enu<two::ToolState>().name(uint32_t(val)); };
	
	
}
