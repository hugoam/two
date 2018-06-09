#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.srlz;
#else
#include <meta/srlz/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/srlz/Convert.h>
#endif
#define MUD_SRLZ_REFLECTION_IMPL
#include <meta/srlz/Meta.h>

namespace mud
{
	mudsrlz::mudsrlz()
		: Module("mud::srlz")
	{
        // ensure dependencies are instantiated
        mudobj::m();
        mudrefl::m();

        // setup reflection meta data
		mudsrlz_meta(*this);
	}
}

#ifdef MUD_SRLZ_MODULE
extern "C"
Module& getModule()
{
	return mudsrlz::m();
}
#endif
