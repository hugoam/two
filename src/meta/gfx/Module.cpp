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
