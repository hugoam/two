#pragma once

#include <two/infra.h>
#include <two/refl.h>


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

#ifndef TWO_NOISE_META_EXPORT
#define TWO_NOISE_META_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_NOISE_META_EXPORT two_noise : public two::Module
	{
	private:
		two_noise();
		
	public:
		static two_noise& m() { static two_noise instance; return instance; }
	};
}

#ifdef TWO_NOISE_MODULE
extern "C"
TWO_NOISE_META_EXPORT Module& getModule();
#endif

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
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
