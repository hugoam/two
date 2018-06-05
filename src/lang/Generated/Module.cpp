#include <obj/Cpp20.h>

#ifdef MUD_MODULES
module mud.lang;
#else
#include <lang/Generated/Module.h>
#endif

#ifdef MUD_LANG_REFLECT
#ifndef MUD_MODULES
#include <lang/Generated/Convert.h>
#endif
#define MUD_LANG_REFLECTION_IMPL
#include <lang/Generated/Meta.h>
#endif

namespace mud
{
	mudlang::mudlang()
		: Module("mud::lang")
	{
        // ensure dependencies are instantiated
        mudobj::m();

#ifdef MUD_LANG_REFLECT
        // setup reflection meta data
		lang_meta(*this);
#endif
	}
}

#ifdef MUD_LANG_MODULE
extern "C"
MUD_LANG_EXPORT Module& getModule()
{
	return mudlang::m();
}
#endif
