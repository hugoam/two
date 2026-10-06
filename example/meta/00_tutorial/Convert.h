
#pragma once

#include <00_tutorial/Types.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/StringConvert.h>
#endif

namespace two
{
    template <> inline void from_string(const string& str, ShapeType& val) { val = static_cast<ShapeType>(enu<ShapeType>().value(str.c_str())); };
    template <> inline void to_string(const ShapeType& val, string& str) { str = enu<ShapeType>().m_map[size_t(val)]; };
    
    
}
