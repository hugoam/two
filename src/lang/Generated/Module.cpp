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

#include <lang/Generated/Module.h>

#ifdef MUD_LANG_REFLECT
#include <lang/Generated/Convert.h>

#define MUD_LANG_REFLECTION_IMPL
#include <lang/Generated/Meta.h>
#endif

namespace mud
{
	mudlang::mudlang()
		: Module("mud::lang")
	{
        // ensure dependencies are instantiated
        mudobj::m();

#ifdef MUD_LANG_REFLECT
        // setup reflection meta data
		lang_meta(*this);
#endif
	}
}

#ifdef MUD_LANG_MODULE
extern "C"
MUD_LANG_EXPORT Module& getModule()
{
	return mudlang::m();
}
#endif
