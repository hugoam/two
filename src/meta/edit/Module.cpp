#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.edit;
#else
#include <meta/edit/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/edit/Convert.h>
#endif
#define MUD_EDIT_REFLECTION_IMPL
#include <meta/edit/Meta.h>

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

        // setup reflection meta data
		mudedit_meta(*this);
	}
}

#ifdef MUD_EDIT_MODULE
extern "C"
Module& getModule()
{
	return mudedit::m();
}
#endif
