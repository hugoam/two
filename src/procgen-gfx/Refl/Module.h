
#pragma once

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <obj/Refl/Module.h>
#include <srlz/Refl/Module.h>
#include <math/Refl/Module.h>
#include <geom/Refl/Module.h>
#include <procgen/Refl/Module.h>
#include <ui/Refl/Module.h>
#include <uio/Refl/Module.h>
#include <gfx/Refl/Module.h>
#include <edit/Refl/Module.h>
#endif
        
#include <procgen-gfx/Forward.h>
#include <procgen-gfx/Types.h>
#include <procgen-gfx/Api.h>

#include <procgen-gfx/Refl/Convert.h>

#ifndef MUD_PROCGEN_GFX_REFL_EXPORT
#define MUD_PROCGEN_GFX_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_PROCGEN_GFX_REFL_EXPORT mudprocgen_gfx : public Module
	{
	private:
		mudprocgen_gfx();

	public:
		static mudprocgen_gfx& m() { static mudprocgen_gfx instance; return instance; }
	};
}

#ifdef MUD_PROCGEN_GFX_MODULE
extern "C"
MUD_PROCGEN_GFX_REFL_EXPORT Module& getModule();
#endif
