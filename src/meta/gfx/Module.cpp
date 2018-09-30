#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <meta/gfx/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/gfx/Convert.h>
#endif
#define MUD_GFX_REFLECTION_IMPL
#include <meta/gfx/Meta.h>

namespace mud
{
	mud_gfx::mud_gfx()
		: Module("mud::gfx")
	{
        // ensure dependencies are instantiated
        mud_infra::m();
        mud_type::m();
        mud_pool::m();
        mud_refl::m();
        mud_srlz::m();
        mud_math::m();
        mud_geom::m();
        mud_ctx::m();
        //mud_ctx_glfw::m();
        mud_bgfx::m();

        // setup reflection meta data
		mud_gfx_meta(*this);
	}
}

#ifdef MUD_GFX_MODULE
extern "C"
Module& getModule()
{
	return mud_gfx::m();
}
#endif
