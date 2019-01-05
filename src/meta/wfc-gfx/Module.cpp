#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.wfc-gfx;
#else
#include <meta/wfc-gfx/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/wfc-gfx/Convert.h>
#endif
#define MUD_WFC_GFX_REFLECTION_IMPL
#include <meta/wfc-gfx/Meta.h>

namespace mud
{
	mud_wfc_gfx::mud_wfc_gfx()
		: Module("mud::wfc-gfx", { &mud_infra::m(), &mud_tree::m(), &mud_type::m(), &mud_srlz::m(), &mud_math::m(), &mud_geom::m(),
								   &mud_wfc::m(), &mud_ctx::m(), &mud_ui::m(), &mud_uio::m(), &mud_gfx::m(), &mud_gfx_ui::m() })
	{
        // setup reflection meta data
		mud_wfc_gfx_meta(*this);
	}
}

#ifdef MUD_WFC_GFX_MODULE
extern "C"
Module& getModule()
{
	return mud_wfc_gfx::m();
}
#endif
