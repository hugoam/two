#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.lang;
#else
#include <meta/lang/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/lang/Convert.h>
#endif
#define MUD_LANG_REFLECTION_IMPL
#include <meta/lang/Meta.h>

namespace mud
{
	mud_lang::mud_lang()
		: Module("mud::lang")
	{
        // ensure dependencies are instantiated
        mud_infra::m();
        mud_type::m();
        mud_pool::m();
        mud_refl::m();

        // setup reflection meta data
		mud_lang_meta(*this);
	}
}

#ifdef MUD_LANG_MODULE
extern "C"
Module& getModule()
{
	return mud_lang::m();
}
#endif
