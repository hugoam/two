#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.refl;
#else
#include <meta/refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/refl/Convert.h>
#endif
#define MUD_REFL_REFLECTION_IMPL
#include <meta/refl/Meta.h>

namespace mud
{
	mud_refl::mud_refl()
		: Module("mud::refl")
	{
        // ensure dependencies are instantiated
        mud_infra::m();
        mud_obj::m();
        mud_pool::m();

        // setup reflection meta data
		mud_refl_meta(*this);
	}
}

#ifdef MUD_REFL_MODULE
extern "C"
Module& getModule()
{
	return mud_refl::m();
}
#endif
