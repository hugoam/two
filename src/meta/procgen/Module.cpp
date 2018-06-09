#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.procgen;
#else
#include <meta/procgen/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/procgen/Convert.h>
#endif
#define MUD_PROCGEN_REFLECTION_IMPL
#include <meta/procgen/Meta.h>

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

        // setup reflection meta data
		mudprocgen_meta(*this);
	}
}

#ifdef MUD_PROCGEN_MODULE
extern "C"
Module& getModule()
{
	return mudprocgen::m();
}
#endif
