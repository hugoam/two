#ifdef MUD_CPP_20
#include <cassert>
#include <cstdint>
#include <climits>
#include <cfloat>
import std.core;
import std.memory;
import std.threading;
import std.regex;
#endif

#include <gfx-pbr/Generated/Module.h>

#ifdef MUD_GFX_PBR_REFLECT
#include <gfx-pbr/Generated/Convert.h>

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
        mudmath::m();
        mudgeom::m();
        mudgfx::m();

#ifdef MUD_GFX_PBR_REFLECT
        // setup reflection meta data
		gfxpbr_meta(*this);
#endif
	}
}

#ifdef MUD_GFXPBR_MODULE
extern "C"
MUD_GFX_PBR_EXPORT Module& getModule()
{
	return mudgfxpbr::m();
}
#endif
