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

#include <15_script/Generated/Module.h>

#ifdef _15_SCRIPT_REFLECT
#include <15_script/Generated/Convert.h>

#define _15_SCRIPT_REFLECTION_IMPL
#include <15_script/Generated/Meta.h>
#endif

	ex_15_script::ex_15_script()
		: Module("ex_15_script")
	{
        // ensure dependencies are instantiated
        mudobj::m();
        mudmath::m();
        mudui::m();
        muduio::m();
        mudgfx::m();
        mudedit::m();
        mudgen::m();

#ifdef _15_SCRIPT_REFLECT
        // setup reflection meta data
		ex_15_script_meta(*this);
#endif
	}

#ifdef _EX_15_SCRIPT_MODULE
extern "C"
_15_SCRIPT_EXPORT Module& getModule()
{
	return ex_15_script::m();
}
#endif
