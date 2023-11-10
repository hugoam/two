#pragma once

#ifndef TWO_MODULES
#include <gltf/Types.h>
#endif

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/StringOps.h>
#endif

namespace two
{
	export_ template <> inline void to_value(const string& str, glTFComponentType& val) { val = glTFComponentType(enu<glTFComponentType>().value(str.c_str())); };
	export_ template <> inline void to_string(const glTFComponentType& val, string& str) { str = enu<glTFComponentType>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, glTFType& val) { val = glTFType(enu<glTFType>().value(str.c_str())); };
	export_ template <> inline void to_string(const glTFType& val, string& str) { str = enu<glTFType>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, glTFPrimitiveType& val) { val = glTFPrimitiveType(enu<glTFPrimitiveType>().value(str.c_str())); };
	export_ template <> inline void to_string(const glTFPrimitiveType& val, string& str) { str = enu<glTFPrimitiveType>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, glTFInterpolation& val) { val = glTFInterpolation(enu<glTFInterpolation>().value(str.c_str())); };
	export_ template <> inline void to_string(const glTFInterpolation& val, string& str) { str = enu<glTFInterpolation>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, glTFAlphaMode& val) { val = glTFAlphaMode(enu<glTFAlphaMode>().value(str.c_str())); };
	export_ template <> inline void to_string(const glTFAlphaMode& val, string& str) { str = enu<glTFAlphaMode>().name(uint32_t(val)); };
	
	
}
