#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx-edit;
#else
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
#include <meta/refl/Module.h>
#include <meta/srlz/Module.h>
#include <meta/math/Module.h>
#include <meta/geom/Module.h>
#include <meta/ui/Module.h>
#include <meta/uio/Module.h>
#include <meta/gfx/Module.h>
#include <meta/gfx-pbr/Module.h>
#include <meta/gfx-edit/Module.h>
#include <meta/gfx-edit/Convert.h>
#endif

#include <gfx-edit/Api.h>
#define MUD_GFX_EDIT_REFLECTION_IMPL
#include <meta/gfx-edit/Meta.h>

namespace mud
{
	mud_gfx_edit::mud_gfx_edit()
		: Module("mud::gfx-edit", { &mud_infra::m(), &mud_type::m(), &mud_refl::m(), &mud_srlz::m(), &mud_math::m(), &mud_geom::m(), &mud_ui::m(), &mud_uio::m(), &mud_gfx::m(), &mud_gfx_pbr::m() })
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
