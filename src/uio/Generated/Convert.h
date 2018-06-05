
#pragma once

#ifndef MUD_MODULES
#include <uio/Generated/Types.h>

#include <obj/Reflect/Meta.h>
#include <obj/Reflect/Enum.h>
#include <obj/String/StringConvert.h>
#endif

namespace mud
{
    template <> inline void from_string(const string& str, mud::EditorHint& val) { val = static_cast<mud::EditorHint>(enu<mud::EditorHint>().value(str.c_str())); };
    template <> inline void to_string(const mud::EditorHint& val, string& str) { str = enu<mud::EditorHint>().m_map[size_t(val)]; };
    
    
}
