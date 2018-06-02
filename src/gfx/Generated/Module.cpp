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

#include <gfx/Generated/Module.h>

#ifdef MUD_GFX_REFLECT
#include <gfx/Generated/Convert.h>

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
        mudmath::m();
        mudgeom::m();

#ifdef MUD_GFX_REFLECT
        // setup reflection meta data
		gfx_meta(*this);
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
