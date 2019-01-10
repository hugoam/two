#pragma once

#include <noise/Types.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/StringConvert.h>
#endif

namespace mud
{
	export_ template <> inline void from_string(const string& str, mud::Noise::CellularDistanceFunction& val) { val = mud::Noise::CellularDistanceFunction(enu<mud::Noise::CellularDistanceFunction>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Noise::CellularDistanceFunction& val, string& str) { str = enu<mud::Noise::CellularDistanceFunction>().name(uint32_t(val)); };
	
	export_ template <> inline void from_string(const string& str, mud::Noise::CellularReturnType& val) { val = mud::Noise::CellularReturnType(enu<mud::Noise::CellularReturnType>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Noise::CellularReturnType& val, string& str) { str = enu<mud::Noise::CellularReturnType>().name(uint32_t(val)); };
	
	export_ template <> inline void from_string(const string& str, mud::Noise::FractalType& val) { val = mud::Noise::FractalType(enu<mud::Noise::FractalType>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Noise::FractalType& val, string& str) { str = enu<mud::Noise::FractalType>().name(uint32_t(val)); };
	
	export_ template <> inline void from_string(const string& str, mud::Noise::Interp& val) { val = mud::Noise::Interp(enu<mud::Noise::Interp>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Noise::Interp& val, string& str) { str = enu<mud::Noise::Interp>().name(uint32_t(val)); };
	
	export_ template <> inline void from_string(const string& str, mud::Noise::NoiseType& val) { val = mud::Noise::NoiseType(enu<mud::Noise::NoiseType>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Noise::NoiseType& val, string& str) { str = enu<mud::Noise::NoiseType>().name(uint32_t(val)); };
	
	
}
