#pragma once

#include <mud/wfc.h>
#include <mud/refl.h>
#include <mud/infra.h>


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

namespace mud
{
	export_ template <> inline void to_value(const string& str, mud::Result& val) { val = mud::Result(enu<mud::Result>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Result& val, string& str) { str = enu<mud::Result>().name(uint32_t(val)); };
	
	
}

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif


#ifndef MUD_WFC_REFL_EXPORT
#define MUD_WFC_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_WFC_REFL_EXPORT mud_wfc : public Module
	{
	private:
		mud_wfc();
		
	public:
		static mud_wfc& m() { static mud_wfc instance; return instance; }
	};
}

#ifdef MUD_WFC_MODULE
extern "C"
MUD_WFC_REFL_EXPORT Module& getModule();
#endif

