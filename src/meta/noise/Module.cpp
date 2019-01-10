#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.noise;
#else
#include <meta/noise/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/noise/Convert.h>
#endif
#define MUD_NOISE_REFLECTION_IMPL
#include <meta/noise/Meta.h>

namespace mud
{
	mud_noise::mud_noise()
		: Module("mud::noise", { &mud_infra::m(), &mud_type::m(), &mud_math::m(), &mud_geom::m() })
	{
		// setup reflection meta data
		mud_noise_meta(*this);
	}
}

#ifdef MUD_NOISE_MODULE
extern "C"
Module& getModule()
{
		return mud_noise::m();
}
#endif
