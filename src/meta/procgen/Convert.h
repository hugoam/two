
#pragma once

#include <procgen/Types.h>

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/StringConvert.h>
#endif

namespace mud
{
    export_ template <> inline void from_string(const string& str, mud::Noise::CellularDistanceFunction& val) { val = static_cast<mud::Noise::CellularDistanceFunction>(enu<mud::Noise::CellularDistanceFunction>().value(str.c_str())); };
    export_ template <> inline void to_string(const mud::Noise::CellularDistanceFunction& val, string& str) { str = enu<mud::Noise::CellularDistanceFunction>().m_map[size_t(val)]; };
    
    export_ template <> inline void from_string(const string& str, mud::Noise::CellularReturnType& val) { val = static_cast<mud::Noise::CellularReturnType>(enu<mud::Noise::CellularReturnType>().value(str.c_str())); };
    export_ template <> inline void to_string(const mud::Noise::CellularReturnType& val, string& str) { str = enu<mud::Noise::CellularReturnType>().m_map[size_t(val)]; };
    
    export_ template <> inline void from_string(const string& str, mud::Noise::FractalType& val) { val = static_cast<mud::Noise::FractalType>(enu<mud::Noise::FractalType>().value(str.c_str())); };
    export_ template <> inline void to_string(const mud::Noise::FractalType& val, string& str) { str = enu<mud::Noise::FractalType>().m_map[size_t(val)]; };
    
    export_ template <> inline void from_string(const string& str, mud::Noise::Interp& val) { val = static_cast<mud::Noise::Interp>(enu<mud::Noise::Interp>().value(str.c_str())); };
    export_ template <> inline void to_string(const mud::Noise::Interp& val, string& str) { str = enu<mud::Noise::Interp>().m_map[size_t(val)]; };
    
    export_ template <> inline void from_string(const string& str, mud::Noise::NoiseType& val) { val = static_cast<mud::Noise::NoiseType>(enu<mud::Noise::NoiseType>().value(str.c_str())); };
    export_ template <> inline void to_string(const mud::Noise::NoiseType& val, string& str) { str = enu<mud::Noise::NoiseType>().m_map[size_t(val)]; };
    
    export_ template <> inline void from_string(const string& str, mud::PatternSampling& val) { val = static_cast<mud::PatternSampling>(enu<mud::PatternSampling>().value(str.c_str())); };
    export_ template <> inline void to_string(const mud::PatternSampling& val, string& str) { str = enu<mud::PatternSampling>().m_map[size_t(val)]; };
    
    export_ template <> inline void from_string(const string& str, mud::Result& val) { val = static_cast<mud::Result>(enu<mud::Result>().value(str.c_str())); };
    export_ template <> inline void to_string(const mud::Result& val, string& str) { str = enu<mud::Result>().m_map[size_t(val)]; };
    
    
}
