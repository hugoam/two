
#pragma once

#include <geom/Types.h>

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/StringConvert.h>
#endif

namespace mud
{
    export_ template <> inline void from_string(const string& str, mud::DrawMode& val) { val = static_cast<mud::DrawMode>(enu<mud::DrawMode>().value(str.c_str())); };
    export_ template <> inline void to_string(const mud::DrawMode& val, string& str) { str = enu<mud::DrawMode>().m_map[size_t(val)]; };
    
    export_ template <> inline void from_string(const string& str, mud::PrimitiveType& val) { val = static_cast<mud::PrimitiveType>(enu<mud::PrimitiveType>().value(str.c_str())); };
    export_ template <> inline void to_string(const mud::PrimitiveType& val, string& str) { str = enu<mud::PrimitiveType>().m_map[size_t(val)]; };
    
    export_ template <> inline void from_string(const string& str, mud::SymbolDetail& val) { val = static_cast<mud::SymbolDetail>(enu<mud::SymbolDetail>().value(str.c_str())); };
    export_ template <> inline void to_string(const mud::SymbolDetail& val, string& str) { str = enu<mud::SymbolDetail>().m_map[size_t(val)]; };
    
    
}
