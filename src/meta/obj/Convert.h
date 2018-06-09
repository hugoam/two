
#pragma once

#include <obj/Types.h>

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/StringConvert.h>
#endif

namespace mud
{
    export_ template <> inline void from_string(const string& str, mud::TypeKind& val) { val = static_cast<mud::TypeKind>(enu<mud::TypeKind>().value(str.c_str())); };
    export_ template <> inline void to_string(const mud::TypeKind& val, string& str) { str = enu<mud::TypeKind>().m_map[size_t(val)]; };
    
    
}
