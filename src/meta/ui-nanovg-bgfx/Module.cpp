#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ui-nanovg-bgfx;
#else
#include <meta/ui-nanovg-bgfx/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/ui-nanovg-bgfx/Convert.h>
#endif
#define MUD_UI_NANOVG_BGFX_REFLECTION_IMPL
#include <meta/ui-nanovg-bgfx/Meta.h>

namespace mud
{
	mud_ui_nanovg_bgfx::mud_ui_nanovg_bgfx()
		: Module("mud::ui-nanovg-bgfx")
	{
        // ensure dependencies are instantiated
        mud_infra::m();
        mud_obj::m();
        mud_math::m();
        mud_ui::m();

        // setup reflection meta data
		mud_ui_nanovg_bgfx_meta(*this);
	}
}

#ifdef MUD_UI_NANOVG_BGFX_MODULE
extern "C"
Module& getModule()
{
	return mud_ui_nanovg_bgfx::m();
}
#endif
