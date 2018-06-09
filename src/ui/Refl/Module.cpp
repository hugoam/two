#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ui;
#else
#include <ui/Refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <ui/Refl/Convert.h>
#endif
#define MUD_UI_REFLECTION_IMPL
#include <ui/Refl/Meta.h>

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
