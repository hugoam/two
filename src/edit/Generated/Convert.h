
#pragma once

#include <edit/Generated/Types.h>

#include <obj/Reflect/Meta.h>
#include <obj/Reflect/Enum.h>
#include <obj/String/StringConvert.h>

namespace mud
{
    template <> inline void from_string(const string& str, mud::ToolState& val) { val = static_cast<mud::ToolState>(enu<mud::ToolState>().value(str.c_str())); };
    template <> inline void to_string(const mud::ToolState& val, string& str) { str = enu<mud::ToolState>().m_map[size_t(val)]; };
    
    
}
