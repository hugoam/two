#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.pool;
#else
#include <meta/pool/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/pool/Convert.h>
#endif
#define MUD_POOL_REFLECTION_IMPL
#include <meta/pool/Meta.h>

namespace mud
{
	mud_pool::mud_pool()
		: Module("mud::pool")
	{
        // ensure dependencies are instantiated
        mud_infra::m();
        mud_type::m();

        // setup reflection meta data
		mud_pool_meta(*this);
	}
}

#ifdef MUD_POOL_MODULE
extern "C"
Module& getModule()
{
	return mud_pool::m();
}
#endif
