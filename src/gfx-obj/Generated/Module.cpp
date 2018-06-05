#include <obj/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfxobj;
#else
#include <gfx-obj/Generated/Module.h>
#endif

#ifdef MUD_GFX_OBJ_REFLECT
#ifndef MUD_MODULES
#include <gfx-obj/Generated/Convert.h>
#endif
#define MUD_GFX_OBJ_REFLECTION_IMPL
#include <gfx-obj/Generated/Meta.h>
#endif

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

#ifdef MUD_GFX_OBJ_REFLECT
        // setup reflection meta data
		gfxobj_meta(*this);
#endif
	}
}

#ifdef MUD_GFXOBJ_MODULE
extern "C"
MUD_GFX_OBJ_EXPORT Module& getModule()
{
	return mudgfxobj::m();
}
#endif
