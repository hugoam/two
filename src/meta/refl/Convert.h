
#pragma once

#include <refl/Types.h>

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/StringConvert.h>
#endif

namespace mud
{
    export_ template <> inline void from_string(const string& str, mud::TypeClass& val) { val = static_cast<mud::TypeClass>(enu<mud::TypeClass>().value(str.c_str())); };
    export_ template <> inline void to_string(const mud::TypeClass& val, string& str) { str = enu<mud::TypeClass>().m_map[size_t(val)]; };
    
    
}
