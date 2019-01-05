#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.obj;
#else
#include <meta/type/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/type/Convert.h>
#endif
#define MUD_TYPE_REFLECTION_IMPL
#include <meta/type/Meta.h>

namespace mud
{
	mud_type::mud_type()
		: Module("mud::obj", { &mud_infra::m() })
	{
        // setup reflection meta data
		mud_type_meta(*this);
	}
}

#ifdef MUD_TYPE_MODULE
extern "C"
Module& getModule()
{
	return mud_type::m();
}
#endif
