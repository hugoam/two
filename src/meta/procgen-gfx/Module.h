
#pragma once

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/infra/Module.h>
#include <meta/obj/Module.h>
#include <meta/srlz/Module.h>
#include <meta/math/Module.h>
#include <meta/geom/Module.h>
#include <meta/procgen/Module.h>
#include <meta/ctx/Module.h>
#include <meta/ui/Module.h>
#include <meta/uio/Module.h>
#include <meta/gfx/Module.h>
#include <meta/edit/Module.h>
#endif
        
#include <procgen-gfx/Forward.h>
#include <procgen-gfx/Types.h>
#include <procgen-gfx/Api.h>

#include <meta/procgen-gfx/Convert.h>

#ifndef MUD_PROCGEN_GFX_REFL_EXPORT
#define MUD_PROCGEN_GFX_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_PROCGEN_GFX_REFL_EXPORT mud_procgen_gfx : public Module
	{
	private:
		mud_procgen_gfx();

	public:
		static mud_procgen_gfx& m() { static mud_procgen_gfx instance; return instance; }
	};
}

#ifdef MUD_PROCGEN_GFX_MODULE
extern "C"
MUD_PROCGEN_GFX_REFL_EXPORT Module& getModule();
#endif
