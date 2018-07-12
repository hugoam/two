#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ui-nanovg;
#else
#include <meta/ui-nanovg/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/ui-nanovg/Convert.h>
#endif
#define MUD_UI_NANOVG_REFLECTION_IMPL
#include <meta/ui-nanovg/Meta.h>

namespace mud
{
	mud_ui_nanovg::mud_ui_nanovg()
		: Module("mud::ui-nanovg")
	{
        // ensure dependencies are instantiated

        // setup reflection meta data
		mud_ui_nanovg_meta(*this);
	}
}

#ifdef MUD_UI_NANOVG_MODULE
extern "C"
Module& getModule()
{
	return mud_ui_nanovg::m();
}
#endif
