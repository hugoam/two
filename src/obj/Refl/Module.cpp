#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.obj;
#else
#include <obj/Refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <obj/Refl/Convert.h>
#endif
#define MUD_OBJ_REFLECTION_IMPL
#include <obj/Refl/Meta.h>

namespace mud
{
	mudobj::mudobj()
		: Module("mud::obj")
	{
        // ensure dependencies are instantiated
        mudinfra::m();

        // setup reflection meta data
		mudobj_meta(*this);
	}
}

#ifdef MUD_OBJ_MODULE
extern "C"
Module& getModule()
{
	return mudobj::m();
}
#endif
