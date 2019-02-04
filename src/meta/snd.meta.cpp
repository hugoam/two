#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.snd;
#else
#include <refl/Module.h>
#include <meta/snd.meta.h>
#endif

namespace mud
{
	mud_snd::mud_snd()
		: Module("mud::snd", {  })
	{}
}

#ifdef MUD_SND_MODULE
extern "C"
Module& getModule()
{
		return mud_snd::m();
}
#endif
