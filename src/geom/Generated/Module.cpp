#include <obj/Cpp20.h>

#ifdef MUD_MODULES
module mud.geom;
#else
#include <geom/Generated/Module.h>
#endif

#ifdef MUD_GEOM_REFLECT
#include <geom/Generated/Convert.h>
#define MUD_GEOM_REFLECTION_IMPL
#include <geom/Generated/Meta.h>
#endif

namespace mud
{
	mudgeom::mudgeom()
		: Module("mud::geom")
	{
        // ensure dependencies are instantiated
        mudobj::m();
        mudsrlz::m();
        mudmath::m();

#ifdef MUD_GEOM_REFLECT
        // setup reflection meta data
		geom_meta(*this);
#endif
	}
}

#ifdef MUD_GEOM_MODULE
extern "C"
MUD_GEOM_EXPORT Module& getModule()
{
	return mudgeom::m();
}
#endif
