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
	
	
	export_ template <> inline void to_value(const string& str, mud::Colour& val) { string_to_fixed_vector<mud::Colour, float>(str, val); };
	export_ template <> inline void to_string(const mud::Colour& val, string& str) { fixed_vector_to_string<mud::Colour, 4>(val, str); };
	
	export_ template <> inline void to_value(const string& str, mud::ivec3& val) { string_to_fixed_vector<mud::ivec3, int>(str, val); };
	export_ template <> inline void to_string(const mud::ivec3& val, string& str) { fixed_vector_to_string<mud::ivec3, 3>(val, str); };
	
	export_ template <> inline void to_value(const string& str, mud::quat& val) { string_to_fixed_vector<mud::quat, float>(str, val); };
	export_ template <> inline void to_string(const mud::quat& val, string& str) { fixed_vector_to_string<mud::quat, 4>(val, str); };
	
	export_ template <> inline void to_value(const string& str, mud::uvec2& val) { string_to_fixed_vector<mud::uvec2, uint32_t>(str, val); };
	export_ template <> inline void to_string(const mud::uvec2& val, string& str) { fixed_vector_to_string<mud::uvec2, 2>(val, str); };
	
	export_ template <> inline void to_value(const string& str, mud::uvec3& val) { string_to_fixed_vector<mud::uvec3, uint32_t>(str, val); };
	export_ template <> inline void to_string(const mud::uvec3& val, string& str) { fixed_vector_to_string<mud::uvec3, 3>(val, str); };
	
	export_ template <> inline void to_value(const string& str, mud::uvec4& val) { string_to_fixed_vector<mud::uvec4, uint32_t>(str, val); };
	export_ template <> inline void to_string(const mud::uvec4& val, string& str) { fixed_vector_to_string<mud::uvec4, 4>(val, str); };
	
	export_ template <> inline void to_value(const string& str, mud::vec2& val) { string_to_fixed_vector<mud::vec2, float>(str, val); };
	export_ template <> inline void to_string(const mud::vec2& val, string& str) { fixed_vector_to_string<mud::vec2, 2>(val, str); };
	
	export_ template <> inline void to_value(const string& str, mud::vec3& val) { string_to_fixed_vector<mud::vec3, float>(str, val); };
	export_ template <> inline void to_string(const mud::vec3& val, string& str) { fixed_vector_to_string<mud::vec3, 3>(val, str); };
	
	export_ template <> inline void to_value(const string& str, mud::vec4& val) { string_to_fixed_vector<mud::vec4, float>(str, val); };
	export_ template <> inline void to_string(const mud::vec4& val, string& str) { fixed_vector_to_string<mud::vec4, 4>(val, str); };
	
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

