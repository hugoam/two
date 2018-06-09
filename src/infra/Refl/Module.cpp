#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.infra;
#else
#include <infra/Refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <infra/Refl/Convert.h>
#endif
#define MUD_INFRA_REFLECTION_IMPL
#include <infra/Refl/Meta.h>

namespace mud
{
	mudinfra::mudinfra()
		: Module("mud::infra")
	{
        // ensure dependencies are instantiated

        // setup reflection meta data
		mudinfra_meta(*this);
	}
}

#ifdef MUD_INFRA_MODULE
extern "C"
Module& getModule()
{
	return mudinfra::m();
}
#endif
