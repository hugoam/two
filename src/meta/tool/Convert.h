
#pragma once

#include <tool/Types.h>

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/StringConvert.h>
#endif

namespace mud
{
    export_ template <> inline void from_string(const string& str, mud::ToolState& val) { val = static_cast<mud::ToolState>(enu<mud::ToolState>().value(str.c_str())); };
    export_ template <> inline void to_string(const mud::ToolState& val, string& str) { str = enu<mud::ToolState>().m_map[size_t(val)]; };
    
    
}
