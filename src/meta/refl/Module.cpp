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
	mudrefl::mudrefl()
		: Module("mud::refl")
	{
        // ensure dependencies are instantiated
        mudobj::m();
        mudpool::m();

        // setup reflection meta data
		mudrefl_meta(*this);
	}
}

#ifdef MUD_REFL_MODULE
extern "C"
Module& getModule()
{
	return mudrefl::m();
}
#endif
