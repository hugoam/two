
#pragma once

#include <uio/Types.h>

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/StringConvert.h>
#endif

namespace mud
{
    export_ template <> inline void from_string(const string& str, mud::EditNestMode& val) { val = static_cast<mud::EditNestMode>(enu<mud::EditNestMode>().value(str.c_str())); };
    export_ template <> inline void to_string(const mud::EditNestMode& val, string& str) { str = enu<mud::EditNestMode>().m_map[size_t(val)]; };
    
    export_ template <> inline void from_string(const string& str, mud::EditorHint& val) { val = static_cast<mud::EditorHint>(enu<mud::EditorHint>().value(str.c_str())); };
    export_ template <> inline void to_string(const mud::EditorHint& val, string& str) { str = enu<mud::EditorHint>().m_map[size_t(val)]; };
    
    
}
