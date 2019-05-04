#pragma once

#include <two/geom.h>
#include <two/refl.h>
#include <two/infra.h>


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

//#include <geom/Types.h>

#ifndef TWO_GEOM_REFL_EXPORT
#define TWO_GEOM_REFL_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_GEOM_REFL_EXPORT two_geom : public two::Module
	{
	private:
		two_geom();
		
	public:
		static two_geom& m() { static two_geom instance; return instance; }
	};
}

#ifdef TWO_GEOM_MODULE
extern "C"
TWO_GEOM_REFL_EXPORT Module& getModule();
#endif


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

namespace two
{
	export_ template <> inline void to_value(const string& str, two::CatmullType& val) { val = two::CatmullType(enu<two::CatmullType>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::CatmullType& val, string& str) { str = enu<two::CatmullType>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::DrawMode& val) { val = two::DrawMode(enu<two::DrawMode>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::DrawMode& val, string& str) { str = enu<two::DrawMode>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::PrimitiveType& val) { val = two::PrimitiveType(enu<two::PrimitiveType>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::PrimitiveType& val, string& str) { str = enu<two::PrimitiveType>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::SymbolDetail& val) { val = two::SymbolDetail(enu<two::SymbolDetail>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::SymbolDetail& val, string& str) { str = enu<two::SymbolDetail>().name(uint32_t(val)); };
	
	
}
