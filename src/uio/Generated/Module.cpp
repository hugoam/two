#include <obj/Cpp20.h>

#ifdef MUD_MODULES
module mud.uio;
#else
#include <uio/Generated/Module.h>
#endif

#ifdef MUD_UIO_REFLECT
#ifndef MUD_MODULES
#include <uio/Generated/Convert.h>
#endif
#define MUD_UIO_REFLECTION_IMPL
#include <uio/Generated/Meta.h>
#endif

namespace mud
{
	muduio::muduio()
		: Module("mud::uio")
	{
        // ensure dependencies are instantiated
        mudobj::m();
        mudlang::m();
        mudui::m();

#ifdef MUD_UIO_REFLECT
        // setup reflection meta data
		muduio_meta(*this);
#endif
	}
}

#ifdef MUD_UIO_MODULE
extern "C"
MUD_UIO_EXPORT Module& getModule()
{
	return muduio::m();
}
#endif
