
#pragma once

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <obj/System/System.h>
#endif

#ifndef MUD_MODULES
#include <obj/Generated/Module.h>
#include <srlz/Generated/Module.h>
#include <math/Generated/Module.h>
#include <geom/Generated/Module.h>
#include <procgen/Generated/Module.h>
#include <ui/Generated/Module.h>
#include <uio/Generated/Module.h>
#include <gfx/Generated/Module.h>
#include <edit/Generated/Module.h>
#endif
        
#include <procgen-gfx/Generated/Forward.h>
#include <procgen-gfx/Generated/Types.h>
#include <procgen-gfx/Api.h>

#include <procgen-gfx/Generated/Convert.h>

namespace mud
{
	export_ class MUD_PROCGEN_GFX_EXPORT mudprocgen_gfx : public Module
	{
	private:
		mudprocgen_gfx();

	public:
		static mudprocgen_gfx& m() { static mudprocgen_gfx instance; return instance; }
	};
}

#ifdef MUD_PROCGEN_GFX_MODULE
extern "C"
MUD_PROCGEN_GFX_EXPORT Module& getModule();
#endif
