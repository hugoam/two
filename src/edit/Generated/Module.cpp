#include <obj/Cpp20.h>

#ifdef MUD_MODULES
module mud.edit;
#else
#include <edit/Generated/Module.h>
#endif

#ifdef MUD_EDIT_REFLECT
#ifndef MUD_MODULES
#include <edit/Generated/Convert.h>
#endif
#define MUD_EDIT_REFLECTION_IMPL
#include <edit/Generated/Meta.h>
#endif

namespace mud
{
	mudedit::mudedit()
		: Module("mud::edit")
	{
        // ensure dependencies are instantiated
        mudobj::m();
        mudsrlz::m();
        mudmath::m();
        mudgeom::m();
        mudlang::m();
        mudui::m();
        muduio::m();
        mudgfx::m();
        mudgfxpbr::m();

#ifdef MUD_EDIT_REFLECT
        // setup reflection meta data
		edit_meta(*this);
#endif
	}
}

#ifdef MUD_EDIT_MODULE
extern "C"
MUD_EDIT_EXPORT Module& getModule()
{
	return mudedit::m();
}
#endif
