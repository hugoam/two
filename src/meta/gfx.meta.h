#pragma once

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Module.h>
#endif

#include <gfx/Forward.h>
//#include <gfx/Types.h>

#ifndef MUD_GFX_REFL_EXPORT
#define MUD_GFX_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_GFX_REFL_EXPORT mud_gfx : public Module
	{
	private:
		mud_gfx();
		
	public:
		static mud_gfx& m() { static mud_gfx instance; return instance; }
	};
}

#ifdef MUD_GFX_MODULE
extern "C"
MUD_GFX_REFL_EXPORT Module& getModule();
#endif
