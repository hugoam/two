#pragma once

#include <math/Types.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/StringConvert.h>
#endif

namespace mud
{
	export_ template <> inline void from_string(const string& str, mud::Axes& val) { val = static_cast<mud::Axes>(enu<mud::Axes>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Axes& val, string& str) { str = enu<mud::Axes>().m_map[size_t(val)]; };
	
	export_ template <> inline void from_string(const string& str, mud::Axis& val) { val = static_cast<mud::Axis>(enu<mud::Axis>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Axis& val, string& str) { str = enu<mud::Axis>().m_map[size_t(val)]; };
	
	export_ template <> inline void from_string(const string& str, mud::Clockwise& val) { val = static_cast<mud::Clockwise>(enu<mud::Clockwise>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Clockwise& val, string& str) { str = enu<mud::Clockwise>().m_map[size_t(val)]; };
	
	export_ template <> inline void from_string(const string& str, mud::Side& val) { val = static_cast<mud::Side>(enu<mud::Side>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Side& val, string& str) { str = enu<mud::Side>().m_map[size_t(val)]; };
	
	export_ template <> inline void from_string(const string& str, mud::SignedAxis& val) { val = static_cast<mud::SignedAxis>(enu<mud::SignedAxis>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::SignedAxis& val, string& str) { str = enu<mud::SignedAxis>().m_map[size_t(val)]; };
	
	export_ template <> inline void from_string(const string& str, mud::Spectrum& val) { val = static_cast<mud::Spectrum>(enu<mud::Spectrum>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Spectrum& val, string& str) { str = enu<mud::Spectrum>().m_map[size_t(val)]; };
	
	export_ template <> inline void from_string(const string& str, mud::TrackMode& val) { val = static_cast<mud::TrackMode>(enu<mud::TrackMode>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::TrackMode& val, string& str) { str = enu<mud::TrackMode>().m_map[size_t(val)]; };
	
	
	export_ template <> inline void from_string(const string& str, mud::Colour& val) { string_to_fixed_vector<mud::Colour, float>(str, val); };
	export_ template <> inline void to_string(const mud::Colour& val, string& str) { fixed_vector_to_string<mud::Colour, 4>(val, str); };
	
	export_ template <> inline void from_string(const string& str, mud::ivec3& val) { string_to_fixed_vector<mud::ivec3, int>(str, val); };
	export_ template <> inline void to_string(const mud::ivec3& val, string& str) { fixed_vector_to_string<mud::ivec3, 3>(val, str); };
	
	export_ template <> inline void from_string(const string& str, mud::quat& val) { string_to_fixed_vector<mud::quat, float>(str, val); };
	export_ template <> inline void to_string(const mud::quat& val, string& str) { fixed_vector_to_string<mud::quat, 4>(val, str); };
	
	export_ template <> inline void from_string(const string& str, mud::uvec2& val) { string_to_fixed_vector<mud::uvec2, uint32_t>(str, val); };
	export_ template <> inline void to_string(const mud::uvec2& val, string& str) { fixed_vector_to_string<mud::uvec2, 2>(val, str); };
	
	export_ template <> inline void from_string(const string& str, mud::uvec3& val) { string_to_fixed_vector<mud::uvec3, uint32_t>(str, val); };
	export_ template <> inline void to_string(const mud::uvec3& val, string& str) { fixed_vector_to_string<mud::uvec3, 3>(val, str); };
	
	export_ template <> inline void from_string(const string& str, mud::uvec4& val) { string_to_fixed_vector<mud::uvec4, uint32_t>(str, val); };
	export_ template <> inline void to_string(const mud::uvec4& val, string& str) { fixed_vector_to_string<mud::uvec4, 4>(val, str); };
	
	export_ template <> inline void from_string(const string& str, mud::vec2& val) { string_to_fixed_vector<mud::vec2, float>(str, val); };
	export_ template <> inline void to_string(const mud::vec2& val, string& str) { fixed_vector_to_string<mud::vec2, 2>(val, str); };
	
	export_ template <> inline void from_string(const string& str, mud::vec3& val) { string_to_fixed_vector<mud::vec3, float>(str, val); };
	export_ template <> inline void to_string(const mud::vec3& val, string& str) { fixed_vector_to_string<mud::vec3, 3>(val, str); };
	
	export_ template <> inline void from_string(const string& str, mud::vec4& val) { string_to_fixed_vector<mud::vec4, float>(str, val); };
	export_ template <> inline void to_string(const mud::vec4& val, string& str) { fixed_vector_to_string<mud::vec4, 4>(val, str); };
	
}
