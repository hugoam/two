#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfxobj;
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
	mudgfxobj::mudgfxobj()
		: Module("mud::gfxobj")
	{
        // ensure dependencies are instantiated
        mudobj::m();
        mudsrlz::m();
        mudmath::m();
        mudgeom::m();
        mudgfx::m();

        // setup reflection meta data
		mudgfxobj_meta(*this);
	}
}

#ifdef MUD_GFX_OBJ_MODULE
extern "C"
Module& getModule()
{
	return mudgfxobj::m();
}
#endif
