
#include <snd/Generated/Module.h>

#ifdef MUD_SND_REFLECT
#include <snd/Generated/Convert.h>

#define MUD_SND_REFLECTION_IMPL
#include <snd/Generated/Meta.h>
#endif

namespace mud
{
	mudsnd::mudsnd()
		: Module("mud::snd")
	{
        // ensure dependencies are instantiated
        mudobj::module();

#ifdef MUD_SND_REFLECT
        // setup reflection meta data
		snd_meta(*this);
#endif
	}
}

#ifdef MUD_SND_MODULE
extern "C"
MUD_SND_EXPORT Module& getModule()
{
	return mudsnd::module();
}
#endif
