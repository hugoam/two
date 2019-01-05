#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx-edit;
#else
#include <meta/gfx-edit/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/gfx-edit/Convert.h>
#endif
#define MUD_GFX_EDIT_REFLECTION_IMPL
#include <meta/gfx-edit/Meta.h>

namespace mud
{
	mud_gfx_edit::mud_gfx_edit()
		: Module("mud::gfx-edit", { &mud_infra::m(), &mud_tree::m(), &mud_type::m(), &mud_refl::m(), &mud_srlz::m(), &mud_lang::m(), &mud_math::m(),
									&mud_geom::m(), &mud_ctx::m(), &mud_ui::m(), &mud_uio::m(), &mud_gfx::m(), &mud_gfx_pbr::m() })
	{
        // setup reflection meta data
		mud_gfx_edit_meta(*this);
	}
}

#ifdef MUD_GFX_EDIT_MODULE
extern "C"
Module& getModule()
{
	return mud_gfx_edit::m();
}
#endif
