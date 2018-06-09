#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ui;
#else
#include <meta/ui/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/ui/Convert.h>
#endif
#define MUD_UI_REFLECTION_IMPL
#include <meta/ui/Meta.h>

namespace mud
{
	mudui::mudui()
		: Module("mud::ui")
	{
        // ensure dependencies are instantiated
        mudobj::m();
        mudsrlz::m();
        mudmath::m();
        mudctx::m();

        // setup reflection meta data
		mudui_meta(*this);
	}
}

#ifdef MUD_UI_MODULE
extern "C"
Module& getModule()
{
	return mudui::m();
}
#endif
