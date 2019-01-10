#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.srlz;
#else
#include <meta/srlz/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/srlz/Convert.h>
#endif
#define MUD_SRLZ_REFLECTION_IMPL
#include <meta/srlz/Meta.h>

namespace mud
{
	mud_srlz::mud_srlz()
		: Module("mud::srlz", { &mud_infra::m(), &mud_type::m(), &mud_refl::m() })
	{
		// setup reflection meta data
		mud_srlz_meta(*this);
	}
}

#ifdef MUD_SRLZ_MODULE
extern "C"
Module& getModule()
{
		return mud_srlz::m();
}
#endif
