#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.pool;
#else
#include <pool/Refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <pool/Refl/Convert.h>
#endif
#define MUD_POOL_REFLECTION_IMPL
#include <pool/Refl/Meta.h>

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
