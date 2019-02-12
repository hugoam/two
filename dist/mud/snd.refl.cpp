#include <mud/snd.refl.h>
#include <mud/refl.h>
#include <mud/infra.h>


#ifdef MUD_MODULES
module mud.snd;
#else
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
