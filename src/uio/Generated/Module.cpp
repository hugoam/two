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

#include <uio/Generated/Module.h>

#ifdef MUD_UIO_REFLECT
#include <uio/Generated/Convert.h>

#define MUD_UIO_REFLECTION_IMPL
#include <uio/Generated/Meta.h>
#endif

namespace mud
{
	muduio::muduio()
		: Module("mud::uio")
	{
        // ensure dependencies are instantiated
        mudobj::m();
        mudlang::m();
        mudui::m();

#ifdef MUD_UIO_REFLECT
        // setup reflection meta data
		uio_meta(*this);
#endif
	}
}

#ifdef MUD_UIO_MODULE
extern "C"
MUD_UIO_EXPORT Module& getModule()
{
	return muduio::m();
}
#endif
