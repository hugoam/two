#include <mud/snd.h>
#include <mud/snd.refl.h>
#include <mud/refl.h>
#include <mud/infra.h>
#include <mud/type.h>

#ifdef MUD_MODULES
module mud.snd;
#else
#endif


using namespace mud;


namespace mud
{
	void mud_snd_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	
	// Sequences
	
	}
}

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
