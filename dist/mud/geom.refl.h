#pragma once

#include <mud/geom.h>
#include <mud/refl.h>
#include <mud/infra.h>


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

//#include <geom/Types.h>

#ifndef MUD_GEOM_REFL_EXPORT
#define MUD_GEOM_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_GEOM_REFL_EXPORT mud_geom : public mud::Module
	{
	private:
		mud_geom();
		
	public:
		static mud_geom& m() { static mud_geom instance; return instance; }
	};
}

#ifdef MUD_GEOM_MODULE
extern "C"
MUD_GEOM_REFL_EXPORT Module& getModule();
#endif


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

namespace mud
{
	export_ template <> inline void to_value(const string& str, mud::DrawMode& val) { val = mud::DrawMode(enu<mud::DrawMode>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::DrawMode& val, string& str) { str = enu<mud::DrawMode>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::PrimitiveType& val) { val = mud::PrimitiveType(enu<mud::PrimitiveType>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::PrimitiveType& val, string& str) { str = enu<mud::PrimitiveType>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::SymbolDetail& val) { val = mud::SymbolDetail(enu<mud::SymbolDetail>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::SymbolDetail& val, string& str) { str = enu<mud::SymbolDetail>().name(uint32_t(val)); };
	
	
}
