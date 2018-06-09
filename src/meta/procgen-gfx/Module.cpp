#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.procgen-gfx;
#else
#include <meta/procgen-gfx/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/procgen-gfx/Convert.h>
#endif
#define MUD_PROCGEN_GFX_REFLECTION_IMPL
#include <meta/procgen-gfx/Meta.h>

namespace mud
{
	mudprocgen_gfx::mudprocgen_gfx()
		: Module("mud::procgen-gfx")
	{
        // ensure dependencies are instantiated
        mudobj::m();
        mudsrlz::m();
        mudmath::m();
        mudgeom::m();
        mudprocgen::m();
        mudui::m();
        muduio::m();
        mudgfx::m();
        mudedit::m();

        // setup reflection meta data
		mudprocgen_gfx_meta(*this);
	}
}

#ifdef MUD_PROCGEN_GFX_MODULE
extern "C"
Module& getModule()
{
	return mudprocgen_gfx::m();
}
#endif
