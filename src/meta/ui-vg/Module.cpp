#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ui-vg;
#else
#include <meta/ui-vg/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/ui-vg/Convert.h>
#endif
#define MUD_UI_VG_REFLECTION_IMPL
#include <meta/ui-vg/Meta.h>

namespace mud
{
	mud_ui_vg::mud_ui_vg()
		: Module("mud::ui-vg", { &mud_infra::m(), &mud_type::m(), &mud_math::m(), &mud_ui::m() })
	{
        // setup reflection meta data
		mud_ui_vg_meta(*this);
	}
}

#ifdef MUD_UI_VG_MODULE
extern "C"
Module& getModule()
{
	return mud_ui_vg::m();
}
#endif
