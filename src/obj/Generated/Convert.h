
#pragma once

#ifndef MUD_MODULES
#include <obj/Generated/Types.h>

#include <obj/Reflect/Meta.h>
#include <obj/Reflect/Enum.h>
#include <obj/String/StringConvert.h>
#endif

namespace mud
{
    export_ template <> inline void from_string(const string& str, mud::TypeClass& val) { val = static_cast<mud::TypeClass>(enu<mud::TypeClass>().value(str.c_str())); };
    export_ template <> inline void to_string(const mud::TypeClass& val, string& str) { str = enu<mud::TypeClass>().m_map[size_t(val)]; };
    
    export_ template <> inline void from_string(const string& str, mud::TypeKind& val) { val = static_cast<mud::TypeKind>(enu<mud::TypeKind>().value(str.c_str())); };
    export_ template <> inline void to_string(const mud::TypeKind& val, string& str) { str = enu<mud::TypeKind>().m_map[size_t(val)]; };
    
    
}
