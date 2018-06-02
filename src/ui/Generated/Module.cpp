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

#include <ui/Generated/Module.h>

#ifdef MUD_UI_REFLECT
#include <ui/Generated/Convert.h>

#define MUD_UI_REFLECTION_IMPL
#include <ui/Generated/Meta.h>
#endif

namespace mud
{
	mudui::mudui()
		: Module("mud::ui")
	{
        // ensure dependencies are instantiated
        mudobj::m();
        mudmath::m();
        mudctx::m();

#ifdef MUD_UI_REFLECT
        // setup reflection meta data
		ui_meta(*this);
#endif
	}
}

#ifdef MUD_UI_MODULE
extern "C"
MUD_UI_EXPORT Module& getModule()
{
	return mudui::m();
}
#endif
