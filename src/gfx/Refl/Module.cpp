#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <gfx/Refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <gfx/Refl/Convert.h>
#endif
#define MUD_GFX_REFLECTION_IMPL
#include <gfx/Refl/Meta.h>

namespace mud
{
	mudgfx::mudgfx()
		: Module("mud::gfx")
	{
        // ensure dependencies are instantiated
        mudobj::m();
        mudsrlz::m();
        mudmath::m();
        mudgeom::m();

        // setup reflection meta data
		mudgfx_meta(*this);
	}
}

#ifdef MUD_GFX_MODULE
extern "C"
Module& getModule()
{
	return mudgfx::m();
}
#endif
