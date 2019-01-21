#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.wfc-gfx;
#else
#include <meta/infra/Module.h>
#include <meta/tree/Module.h>
#include <meta/type/Module.h>
#include <meta/srlz/Module.h>
#include <meta/math/Module.h>
#include <meta/geom/Module.h>
#include <meta/wfc/Module.h>
#include <meta/ctx/Module.h>
#include <meta/ui/Module.h>
#include <meta/uio/Module.h>
#include <meta/gfx/Module.h>
#include <meta/gfx-ui/Module.h>
#include <meta/wfc-gfx/Module.h>
#include <meta/wfc-gfx/Convert.h>
#endif

#include <wfc-gfx/Api.h>
#define MUD_WFC_GFX_REFLECTION_IMPL
#include <meta/wfc-gfx/Meta.h>

namespace mud
{
	mud_wfc_gfx::mud_wfc_gfx()
		: Module("mud::wfc-gfx", { &mud_infra::m(), &mud_tree::m(), &mud_type::m(), &mud_srlz::m(), &mud_math::m(), &mud_geom::m(), &mud_wfc::m(), &mud_ctx::m(), &mud_ui::m(), &mud_uio::m(), &mud_gfx::m(), &mud_gfx_ui::m() })
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
