#pragma once

#include <mud/gltf.h>
#include <mud/refl.h>
#include <mud/infra.h>


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

//#include <gltf/Types.h>

#ifndef MUD_GLTF_REFL_EXPORT
#define MUD_GLTF_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_GLTF_REFL_EXPORT mud_gltf : public mud::Module
	{
	private:
		mud_gltf();
		
	public:
		static mud_gltf& m() { static mud_gltf instance; return instance; }
	};
}

#ifdef MUD_GLTF_MODULE
extern "C"
MUD_GLTF_REFL_EXPORT Module& getModule();
#endif


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

namespace mud
{
	export_ template <> inline void to_value(const string& str, glTFAlphaMode& val) { val = glTFAlphaMode(enu<glTFAlphaMode>().value(str.c_str())); };
	export_ template <> inline void to_string(const glTFAlphaMode& val, string& str) { str = enu<glTFAlphaMode>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, glTFComponentType& val) { val = glTFComponentType(enu<glTFComponentType>().value(str.c_str())); };
	export_ template <> inline void to_string(const glTFComponentType& val, string& str) { str = enu<glTFComponentType>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, glTFInterpolation& val) { val = glTFInterpolation(enu<glTFInterpolation>().value(str.c_str())); };
	export_ template <> inline void to_string(const glTFInterpolation& val, string& str) { str = enu<glTFInterpolation>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, glTFPrimitiveType& val) { val = glTFPrimitiveType(enu<glTFPrimitiveType>().value(str.c_str())); };
	export_ template <> inline void to_string(const glTFPrimitiveType& val, string& str) { str = enu<glTFPrimitiveType>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, glTFType& val) { val = glTFType(enu<glTFType>().value(str.c_str())); };
	export_ template <> inline void to_string(const glTFType& val, string& str) { str = enu<glTFType>().name(uint32_t(val)); };
	
	
}
