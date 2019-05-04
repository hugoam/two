#pragma once

#include <two/gltf.h>
#include <two/refl.h>
#include <two/infra.h>


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

//#include <gltf/Types.h>

#ifndef TWO_GLTF_REFL_EXPORT
#define TWO_GLTF_REFL_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_GLTF_REFL_EXPORT two_gltf : public two::Module
	{
	private:
		two_gltf();
		
	public:
		static two_gltf& m() { static two_gltf instance; return instance; }
	};
}

#ifdef TWO_GLTF_MODULE
extern "C"
TWO_GLTF_REFL_EXPORT Module& getModule();
#endif


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
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
