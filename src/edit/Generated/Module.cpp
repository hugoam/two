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

#include <edit/Generated/Module.h>

#ifdef MUD_EDIT_REFLECT
#include <edit/Generated/Convert.h>

#define MUD_EDIT_REFLECTION_IMPL
#include <edit/Generated/Meta.h>
#endif

namespace mud
{
	mudedit::mudedit()
		: Module("mud::edit")
	{
        // ensure dependencies are instantiated
        mudobj::m();
        mudmath::m();
        mudgeom::m();
        mudlang::m();
        mudui::m();
        muduio::m();
        mudgfx::m();
        mudgfxpbr::m();

#ifdef MUD_EDIT_REFLECT
        // setup reflection meta data
		edit_meta(*this);
#endif
	}
}

#ifdef MUD_EDIT_MODULE
extern "C"
MUD_EDIT_EXPORT Module& getModule()
{
	return mudedit::m();
}
#endif
