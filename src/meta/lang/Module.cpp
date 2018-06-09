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
	mudlang::mudlang()
		: Module("mud::lang")
	{
        // ensure dependencies are instantiated
        mudobj::m();
        mudrefl::m();

        // setup reflection meta data
		mudlang_meta(*this);
	}
}

#ifdef MUD_LANG_MODULE
extern "C"
Module& getModule()
{
	return mudlang::m();
}
#endif
