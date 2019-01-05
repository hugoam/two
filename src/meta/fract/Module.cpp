#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.fract;
#else
#include <meta/fract/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/fract/Convert.h>
#endif
#define MUD_FRACT_REFLECTION_IMPL
#include <meta/fract/Meta.h>

namespace mud
{
	mud_fract::mud_fract()
		: Module("mud::fract", { &mud_infra::m(), &mud_type::m(), &mud_math::m(), &mud_geom::m() })
	{
        // setup reflection meta data
		mud_fract_meta(*this);
	}
}

#ifdef MUD_FRACT_MODULE
extern "C"
Module& getModule()
{
	return mud_fract::m();
}
#endif
