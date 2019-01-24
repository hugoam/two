#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.snd;
#else
#include <type/Any.h>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/snd/Module.h>
#include <meta/snd/Convert.h>
#endif

#include <snd/Api.h>

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
