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

#include <gen/Generated/Module.h>

#ifdef MUD_GEN_REFLECT
#include <gen/Generated/Convert.h>

#define MUD_GEN_REFLECTION_IMPL
#include <gen/Generated/Meta.h>
#endif

namespace mud
{
	mudgen::mudgen()
		: Module("mud::gen")
	{
        // ensure dependencies are instantiated
        mudobj::m();
        mudmath::m();
        mudgeom::m();
        mudui::m();
        mudgfx::m();
        mudedit::m();

#ifdef MUD_GEN_REFLECT
        // setup reflection meta data
		gen_meta(*this);
#endif
	}
}

#ifdef MUD_GEN_MODULE
extern "C"
MUD_GEN_EXPORT Module& getModule()
{
	return mudgen::m();
}
#endif
