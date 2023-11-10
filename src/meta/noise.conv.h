#pragma once

#ifndef TWO_MODULES
#include <noise/Types.h>
#endif

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/StringOps.h>
#endif

namespace two
{
	export_ template <> inline void to_value(const string& str, two::Noise::NoiseType& val) { val = two::Noise::NoiseType(enu<two::Noise::NoiseType>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::Noise::NoiseType& val, string& str) { str = enu<two::Noise::NoiseType>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::Noise::Interp& val) { val = two::Noise::Interp(enu<two::Noise::Interp>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::Noise::Interp& val, string& str) { str = enu<two::Noise::Interp>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::Noise::FractalType& val) { val = two::Noise::FractalType(enu<two::Noise::FractalType>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::Noise::FractalType& val, string& str) { str = enu<two::Noise::FractalType>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::Noise::CellularDistanceFunction& val) { val = two::Noise::CellularDistanceFunction(enu<two::Noise::CellularDistanceFunction>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::Noise::CellularDistanceFunction& val, string& str) { str = enu<two::Noise::CellularDistanceFunction>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::Noise::CellularReturnType& val) { val = two::Noise::CellularReturnType(enu<two::Noise::CellularReturnType>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::Noise::CellularReturnType& val, string& str) { str = enu<two::Noise::CellularReturnType>().name(uint32_t(val)); };
	
	
}
