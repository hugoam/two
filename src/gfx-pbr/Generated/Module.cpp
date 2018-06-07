#include <gfx/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
#include <gfx-pbr/Generated/Module.h>
#endif

#ifdef MUD_GFX_PBR_REFLECT
#ifndef MUD_MODULES
#include <gfx-pbr/Generated/Convert.h>
#endif
#define MUD_GFX_PBR_REFLECTION_IMPL
#include <gfx-pbr/Generated/Meta.h>
#endif

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

#ifdef MUD_GFX_PBR_REFLECT
        // setup reflection meta data
		mudgfxpbr_meta(*this);
#endif
	}
}

#ifdef MUD_GFX_PBR_MODULE
extern "C"
MUD_GFX_PBR_EXPORT Module& getModule()
{
	return mudgfxpbr::m();
}
#endif
