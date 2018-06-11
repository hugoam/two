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
	mud_edit::mud_edit()
		: Module("mud::edit")
	{
        // ensure dependencies are instantiated
        mud_infra::m();
        mud_obj::m();
        mud_refl::m();
        mud_srlz::m();
        mud_lang::m();
        mud_math::m();
        mud_geom::m();
        mud_ctx::m();
        mud_ui::m();
        mud_uio::m();
        mud_gfx::m();
        mud_gfx_pbr::m();

        // setup reflection meta data
		mud_edit_meta(*this);
	}
}

#ifdef MUD_EDIT_MODULE
extern "C"
Module& getModule()
{
	return mud_edit::m();
}
#endif
