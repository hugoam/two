
#pragma once

#ifndef MUD_MODULES
#include <00_tutorial/Generated/Types.h>

#include <obj/Reflect/Meta.h>
#include <obj/Reflect/Enum.h>
#include <obj/String/StringConvert.h>
#endif

namespace mud
{
    export_ template <> inline void from_string(const string& str, ShapeType& val) { val = static_cast<ShapeType>(enu<ShapeType>().value(str.c_str())); };
    export_ template <> inline void to_string(const ShapeType& val, string& str) { str = enu<ShapeType>().m_map[size_t(val)]; };
    
    
}
