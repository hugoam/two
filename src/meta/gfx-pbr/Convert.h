
#pragma once

#include <gfx-pbr/Types.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/StringConvert.h>
#endif

namespace mud
{
    export_ template <> inline void from_string(const string& str, mud::TonemapMode& val) { val = static_cast<mud::TonemapMode>(enu<mud::TonemapMode>().value(str.c_str())); };
    export_ template <> inline void to_string(const mud::TonemapMode& val, string& str) { str = enu<mud::TonemapMode>().m_map[size_t(val)]; };
    
    
}
