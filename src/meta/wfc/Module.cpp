#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.wfc;
#else
#include <meta/wfc/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/wfc/Convert.h>
#endif
#define MUD_WFC_REFLECTION_IMPL
#include <meta/wfc/Meta.h>

namespace mud
{
	mud_wfc::mud_wfc()
		: Module("mud::wfc")
	{
        // ensure dependencies are instantiated
        mud_infra::m();
        mud_type::m();
        mud_srlz::m();
        mud_math::m();
        mud_geom::m();

        // setup reflection meta data
		mud_wfc_meta(*this);
	}
}

#ifdef MUD_WFC_MODULE
extern "C"
Module& getModule()
{
	return mud_wfc::m();
}
#endif
