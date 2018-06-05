
#pragma once

#ifndef MUD_MODULES
#include <gfx-pbr/Generated/Types.h>

#include <obj/Reflect/Meta.h>
#include <obj/Reflect/Enum.h>
#include <obj/String/StringConvert.h>
#endif

namespace mud
{
    template <> inline void from_string(const string& str, mud::TonemapMode& val) { val = static_cast<mud::TonemapMode>(enu<mud::TonemapMode>().value(str.c_str())); };
    template <> inline void to_string(const mud::TonemapMode& val, string& str) { str = enu<mud::TonemapMode>().m_map[size_t(val)]; };
    
    
}
