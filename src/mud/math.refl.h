#pragma once

#include <mud/math.h>
#include <mud/refl.h>
#include <mud/infra.h>


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

namespace mud
{
	export_ template <> inline void to_value(const string& str, mud::Axes& val) { val = mud::Axes(enu<mud::Axes>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Axes& val, string& str) { str = enu<mud::Axes>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::Axis& val) { val = mud::Axis(enu<mud::Axis>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Axis& val, string& str) { str = enu<mud::Axis>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::Clockwise& val) { val = mud::Clockwise(enu<mud::Clockwise>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Clockwise& val, string& str) { str = enu<mud::Clockwise>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::Side& val) { val = mud::Side(enu<mud::Side>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Side& val, string& str) { str = enu<mud::Side>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::SignedAxis& val) { val = mud::SignedAxis(enu<mud::SignedAxis>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::SignedAxis& val, string& str) { str = enu<mud::SignedAxis>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::Spectrum& val) { val = mud::Spectrum(enu<mud::Spectrum>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Spectrum& val, string& str) { str = enu<mud::Spectrum>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::TrackMode& val) { val = mud::TrackMode(enu<mud::TrackMode>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::TrackMode& val, string& str) { str = enu<mud::TrackMode>().name(uint32_t(val)); };
	
	
}

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif


#ifndef MUD_MATH_REFL_EXPORT
#define MUD_MATH_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_MATH_REFL_EXPORT mud_math : public Module
	{
	private:
		mud_math();
		
	public:
		static mud_math& m() { static mud_math instance; return instance; }
	};
}

#ifdef MUD_MATH_MODULE
extern "C"
MUD_MATH_REFL_EXPORT Module& getModule();
#endif

