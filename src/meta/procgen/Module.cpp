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
	mud_procgen::mud_procgen()
		: Module("mud::procgen")
	{
        // ensure dependencies are instantiated
        mud_infra::m();
        mud_obj::m();
        mud_srlz::m();
        mud_math::m();
        mud_geom::m();

        // setup reflection meta data
		mud_procgen_meta(*this);
	}
}

#ifdef MUD_PROCGEN_MODULE
extern "C"
Module& getModule()
{
	return mud_procgen::m();
}
#endif
