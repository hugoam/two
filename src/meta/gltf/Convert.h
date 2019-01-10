#pragma once

#include <gltf/Types.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/StringConvert.h>
#endif

namespace mud
{
	export_ template <> inline void from_string(const string& str, glTFAlphaMode& val) { val = glTFAlphaMode(enu<glTFAlphaMode>().value(str.c_str())); };
	export_ template <> inline void to_string(const glTFAlphaMode& val, string& str) { str = enu<glTFAlphaMode>().name(uint32_t(val)); };
	
	export_ template <> inline void from_string(const string& str, glTFComponentType& val) { val = glTFComponentType(enu<glTFComponentType>().value(str.c_str())); };
	export_ template <> inline void to_string(const glTFComponentType& val, string& str) { str = enu<glTFComponentType>().name(uint32_t(val)); };
	
	export_ template <> inline void from_string(const string& str, glTFInterpolation& val) { val = glTFInterpolation(enu<glTFInterpolation>().value(str.c_str())); };
	export_ template <> inline void to_string(const glTFInterpolation& val, string& str) { str = enu<glTFInterpolation>().name(uint32_t(val)); };
	
	export_ template <> inline void from_string(const string& str, glTFPrimitiveType& val) { val = glTFPrimitiveType(enu<glTFPrimitiveType>().value(str.c_str())); };
	export_ template <> inline void to_string(const glTFPrimitiveType& val, string& str) { str = enu<glTFPrimitiveType>().name(uint32_t(val)); };
	
	export_ template <> inline void from_string(const string& str, glTFType& val) { val = glTFType(enu<glTFType>().value(str.c_str())); };
	export_ template <> inline void to_string(const glTFType& val, string& str) { str = enu<glTFType>().name(uint32_t(val)); };
	
	
}
