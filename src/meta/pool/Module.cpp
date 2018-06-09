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
	mudpool::mudpool()
		: Module("mud::pool")
	{
        // ensure dependencies are instantiated
        mudobj::m();

        // setup reflection meta data
		mudpool_meta(*this);
	}
}

#ifdef MUD_POOL_MODULE
extern "C"
Module& getModule()
{
	return mudpool::m();
}
#endif
