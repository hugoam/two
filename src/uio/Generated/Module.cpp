
#include <uio/Generated/Module.h>

#ifdef MUD_UIO_REFLECT
#include <uio/Generated/Convert.h>

#define MUD_UIO_REFLECTION_IMPL
#include <uio/Generated/Meta.h>
#endif

namespace mud
{
	muduio::muduio()
		: Module("mud::uio")
	{
        // ensure dependencies are instantiated
        mudobj::module();
        mudlang::module();
        mudui::module();

#ifdef MUD_UIO_REFLECT
        // setup reflection meta data
		uio_meta(*this);
#endif
	}
}

#ifdef MUD_UIO_MODULE
extern "C"
MUD_UIO_EXPORT Module& getModule()
{
	return muduio::module();
}
#endif
