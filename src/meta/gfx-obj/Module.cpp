#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx-obj;
#else
#include <meta/gfx-obj/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/gfx-obj/Convert.h>
#endif
#define MUD_GFX_OBJ_REFLECTION_IMPL
#include <meta/gfx-obj/Meta.h>

namespace mud
{
	mud_gfx_obj::mud_gfx_obj()
		: Module("mud::gfx-obj")
	{
        // ensure dependencies are instantiated
        mud_infra::m();
        mud_type::m();
        mud_srlz::m();
        mud_math::m();
        mud_geom::m();
        mud_gfx::m();

        // setup reflection meta data
		mud_gfx_obj_meta(*this);
	}
}

#ifdef MUD_GFX_OBJ_MODULE
extern "C"
Module& getModule()
{
	return mud_gfx_obj::m();
}
#endif
