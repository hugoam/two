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
	mud_ui::mud_ui()
		: Module("mud::ui")
	{
        // ensure dependencies are instantiated
        mud_infra::m();
        mud_obj::m();
        mud_refl::m();
        mud_srlz::m();
        mud_math::m();
        mud_ctx::m();

        // setup reflection meta data
		mud_ui_meta(*this);
	}
}

#ifdef MUD_UI_MODULE
extern "C"
Module& getModule()
{
	return mud_ui::m();
}
#endif
