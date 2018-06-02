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

#include <00_tutorial/Generated/Module.h>

#ifdef _00_TUTORIAL_REFLECT
#include <00_tutorial/Generated/Convert.h>

#define _00_TUTORIAL_REFLECTION_IMPL
#include <00_tutorial/Generated/Meta.h>
#endif

	ex_00_tutorial::ex_00_tutorial()
		: Module("ex_00_tutorial")
	{
        // ensure dependencies are instantiated
        mudobj::m();
        mudmath::m();
        mudui::m();
        muduio::m();
        mudgfx::m();
        mudedit::m();
        mudgen::m();

#ifdef _00_TUTORIAL_REFLECT
        // setup reflection meta data
		ex_00_tutorial_meta(*this);
#endif
	}

#ifdef _EX_00_TUTORIAL_MODULE
extern "C"
_00_TUTORIAL_EXPORT Module& getModule()
{
	return ex_00_tutorial::m();
}
#endif
