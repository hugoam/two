#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfxpbr;
#else
#include <meta/gfx-pbr/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/gfx-pbr/Convert.h>
#endif
#define MUD_GFX_PBR_REFLECTION_IMPL
#include <meta/gfx-pbr/Meta.h>

namespace mud
{
	mudgfxpbr::mudgfxpbr()
		: Module("mud::gfxpbr")
	{
        // ensure dependencies are instantiated
        mudobj::m();
        mudsrlz::m();
        mudmath::m();
        mudgeom::m();
        mudgfx::m();

        // setup reflection meta data
		mudgfxpbr_meta(*this);
	}
}

#ifdef MUD_GFX_PBR_MODULE
extern "C"
Module& getModule()
{
	return mudgfxpbr::m();
}
#endif
