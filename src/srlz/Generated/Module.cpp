#include <obj/Cpp20.h>

#ifdef MUD_MODULES
module mud.srlz;
#else
#include <srlz/Generated/Module.h>
#endif

#ifdef MUD_SRLZ_REFLECT
#ifndef MUD_MODULES
#include <srlz/Generated/Convert.h>
#endif
#define MUD_SRLZ_REFLECTION_IMPL
#include <srlz/Generated/Meta.h>
#endif

namespace mud
{
	mudsrlz::mudsrlz()
		: Module("mud::srlz")
	{
        // ensure dependencies are instantiated
        mudobj::m();

#ifdef MUD_SRLZ_REFLECT
        // setup reflection meta data
		srlz_meta(*this);
#endif
	}
}

#ifdef MUD_SRLZ_MODULE
extern "C"
MUD_SRLZ_EXPORT Module& getModule()
{
	return mudsrlz::m();
}
#endif
