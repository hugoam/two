
#pragma once

#include <ctx/Types.h>

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/StringConvert.h>
#endif

namespace mud
{
    export_ template <> inline void from_string(const string& str, mud::Key& val) { val = static_cast<mud::Key>(enu<mud::Key>().value(str.c_str())); };
    export_ template <> inline void to_string(const mud::Key& val, string& str) { str = enu<mud::Key>().m_map[size_t(val)]; };
    
    
}
