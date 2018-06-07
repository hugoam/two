#include <obj/Cpp20.h>

#ifdef MUD_MODULES
module mud.procgen;
#else
#include <procgen/Generated/Module.h>
#endif

#ifdef MUD_PROCGEN_REFLECT
#ifndef MUD_MODULES
#include <procgen/Generated/Convert.h>
#endif
#define MUD_PROCGEN_REFLECTION_IMPL
#include <procgen/Generated/Meta.h>
#endif

namespace mud
{
	mudprocgen::mudprocgen()
		: Module("mud::procgen")
	{
        // ensure dependencies are instantiated
        mudobj::m();
        mudsrlz::m();
        mudmath::m();
        mudgeom::m();

#ifdef MUD_PROCGEN_REFLECT
        // setup reflection meta data
		mudprocgen_meta(*this);
#endif
	}
}

#ifdef MUD_PROCGEN_MODULE
extern "C"
MUD_PROCGEN_EXPORT Module& getModule()
{
	return mudprocgen::m();
}
#endif
