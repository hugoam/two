#pragma once

#include <tool/Types.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/String.h>
#endif

namespace mud
{
	export_ template <> inline void to_value(const string& str, mud::ToolState& val) { val = mud::ToolState(enu<mud::ToolState>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::ToolState& val, string& str) { str = enu<mud::ToolState>().name(uint32_t(val)); };
	
	
}
