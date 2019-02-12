#pragma once

#include <mud/gfx.pbr.h>
#include <mud/refl.h>
#include <mud/infra.h>


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

//#include <gfx-pbr/Types.h>

#ifndef MUD_GFX_PBR_REFL_EXPORT
#define MUD_GFX_PBR_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_GFX_PBR_REFL_EXPORT mud_gfx_pbr : public mud::Module
	{
	private:
		mud_gfx_pbr();
		
	public:
		static mud_gfx_pbr& m() { static mud_gfx_pbr instance; return instance; }
	};
}

#ifdef MUD_GFX_PBR_MODULE
extern "C"
MUD_GFX_PBR_REFL_EXPORT Module& getModule();
#endif


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

namespace mud
{
	export_ template <> inline void to_value(const string& str, mud::TonemapMode& val) { val = mud::TonemapMode(enu<mud::TonemapMode>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::TonemapMode& val, string& str) { str = enu<mud::TonemapMode>().name(uint32_t(val)); };
	
	
}
