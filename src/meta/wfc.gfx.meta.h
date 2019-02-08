#pragma once

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Module.h>
#endif

#include <wfc-gfx/Forward.h>
//#include <wfc-gfx/Types.h>

#ifndef MUD_WFC_GFX_REFL_EXPORT
#define MUD_WFC_GFX_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_WFC_GFX_REFL_EXPORT mud_wfc_gfx : public mud::Module
	{
	private:
		mud_wfc_gfx();
		
	public:
		static mud_wfc_gfx& m() { static mud_wfc_gfx instance; return instance; }
	};
}

#ifdef MUD_WFC_GFX_MODULE
extern "C"
MUD_WFC_GFX_REFL_EXPORT Module& getModule();
#endif
