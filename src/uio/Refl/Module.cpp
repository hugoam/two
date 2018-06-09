#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.uio;
#else
#include <uio/Refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <uio/Refl/Convert.h>
#endif
#define MUD_UIO_REFLECTION_IMPL
#include <uio/Refl/Meta.h>

namespace mud
{
	muduio::muduio()
		: Module("mud::uio")
	{
        // ensure dependencies are instantiated
        mudobj::m();
        mudlang::m();
        mudui::m();

        // setup reflection meta data
		muduio_meta(*this);
	}
}

#ifdef MUD_UIO_MODULE
extern "C"
Module& getModule()
{
	return muduio::m();
}
#endif
