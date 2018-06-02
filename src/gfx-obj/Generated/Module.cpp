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

#include <gfx-obj/Generated/Module.h>

#ifdef MUD_GFX_OBJ_REFLECT
#include <gfx-obj/Generated/Convert.h>

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
