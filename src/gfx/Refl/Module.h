
#pragma once

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <obj/Refl/Module.h>
#include <srlz/Refl/Module.h>
#include <math/Refl/Module.h>
#include <geom/Refl/Module.h>
#endif
        
#include <gfx/Forward.h>
#include <gfx/Types.h>
#include <gfx/Api.h>

#include <gfx/Refl/Convert.h>

#ifndef MUD_GFX_REFL_EXPORT
#define MUD_GFX_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_GFX_REFL_EXPORT mudgfx : public Module
	{
	private:
		mudgfx();

	public:
		static mudgfx& m() { static mudgfx instance; return instance; }
	};
}

#ifdef MUD_GFX_MODULE
extern "C"
MUD_GFX_REFL_EXPORT Module& getModule();
#endif
