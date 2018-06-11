#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.obj;
#else
#include <meta/obj/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/obj/Convert.h>
#endif
#define MUD_OBJ_REFLECTION_IMPL
#include <meta/obj/Meta.h>

namespace mud
{
	mud_obj::mud_obj()
		: Module("mud::obj")
	{
        // ensure dependencies are instantiated
        mud_infra::m();

        // setup reflection meta data
		mud_obj_meta(*this);
	}
}

#ifdef MUD_OBJ_MODULE
extern "C"
Module& getModule()
{
	return mud_obj::m();
}
#endif
