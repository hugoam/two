#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.snd;
#else
#include <meta/snd/Module.h>
#endif

#include <snd/Api.h>

#ifndef MUD_MODULES
#include <meta/snd/Convert.h>
#endif
#define MUD_SND_REFLECTION_IMPL
#include <meta/snd/Meta.h>

namespace mud
{
	mud_snd::mud_snd()
		: Module("mud::snd", {  })
	{
		// setup reflection meta data
		mud_snd_meta(*this);
	}
}

#ifdef MUD_SND_MODULE
extern "C"
Module& getModule()
{
		return mud_snd::m();
}
#endif
