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
	mud_procgen_gfx::mud_procgen_gfx()
		: Module("mud::procgen-gfx")
	{
        // ensure dependencies are instantiated
        mud_infra::m();
        mud_tree::m();
        mud_type::m();
        mud_srlz::m();
        mud_math::m();
        mud_geom::m();
        mud_procgen::m();
        mud_ctx::m();
        mud_ui::m();
        mud_uio::m();
        mud_gfx::m();
        mud_gfx_ui::m();

        // setup reflection meta data
		mud_procgen_gfx_meta(*this);
	}
}

#ifdef MUD_PROCGEN_GFX_MODULE
extern "C"
Module& getModule()
{
	return mud_procgen_gfx::m();
}
#endif
