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

#include <geom/Generated/Module.h>

#ifdef MUD_GEOM_REFLECT
#include <geom/Generated/Convert.h>

#define MUD_GEOM_REFLECTION_IMPL
#include <geom/Generated/Meta.h>
#endif

namespace mud
{
	mudgeom::mudgeom()
		: Module("mud::geom")
	{
        // ensure dependencies are instantiated
        mudobj::m();
        mudmath::m();

#ifdef MUD_GEOM_REFLECT
        // setup reflection meta data
		geom_meta(*this);
#endif
	}
}

#ifdef MUD_GEOM_MODULE
extern "C"
MUD_GEOM_EXPORT Module& getModule()
{
	return mudgeom::m();
}
#endif
