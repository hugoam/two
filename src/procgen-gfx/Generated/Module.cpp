#include <obj/Cpp20.h>

#ifdef MUD_MODULES
module mud.procgen.gfx;
#else
#include <procgen-gfx/Generated/Module.h>
#endif

#ifdef MUD_PROCGEN_GFX_REFLECT
#ifndef MUD_MODULES
#include <procgen-gfx/Generated/Convert.h>
#endif
#define MUD_PROCGEN_GFX_REFLECTION_IMPL
#include <procgen-gfx/Generated/Meta.h>
#endif

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

#ifdef MUD_PROCGEN_GFX_REFLECT
        // setup reflection meta data
		mudprocgen_gfx_meta(*this);
#endif
	}
}

#ifdef MUD_PROCGEN_GFX_MODULE
extern "C"
MUD_PROCGEN_GFX_EXPORT Module& getModule()
{
	return mudprocgen_gfx::m();
}
#endif
