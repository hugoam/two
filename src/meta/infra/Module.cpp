#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.infra;
#else
#include <meta/infra/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/infra/Convert.h>
#endif
#define MUD_INFRA_REFLECTION_IMPL
#include <meta/infra/Meta.h>

namespace mud
{
	mud_infra::mud_infra()
		: Module("mud::infra", {})
	{
        // setup reflection meta data
		mud_infra_meta(*this);
	}
}

#ifdef MUD_INFRA_MODULE
extern "C"
Module& getModule()
{
	return mud_infra::m();
}
#endif
