#include <gfx/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <gfx/Generated/Module.h>
#endif

#ifdef MUD_GFX_REFLECT
#ifndef MUD_MODULES
#include <gfx/Generated/Convert.h>
#endif
#define MUD_GFX_REFLECTION_IMPL
#include <gfx/Generated/Meta.h>
#endif

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

#ifdef MUD_GFX_REFLECT
        // setup reflection meta data
		mudgfx_meta(*this);
#endif
	}
}

#ifdef MUD_GFX_MODULE
extern "C"
MUD_GFX_EXPORT Module& getModule()
{
	return mudgfx::m();
}
#endif
