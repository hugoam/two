#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx-edit;
#else
#include <refl/Module.h>
#include <meta/infra/infra.meta.h>
#include <meta/type/type.meta.h>
#include <meta/refl/refl.meta.h>
#include <meta/srlz/srlz.meta.h>
#include <meta/math/math.meta.h>
#include <meta/geom/geom.meta.h>
#include <meta/ui/ui.meta.h>
#include <meta/uio/uio.meta.h>
#include <meta/gfx/gfx.meta.h>
#include <meta/gfx-pbr/gfx.pbr.meta.h>
#include <meta/gfx-edit/gfx.edit.meta.h>
#endif

namespace mud
{
	mud_gfx_edit::mud_gfx_edit()
		: Module("mud::gfx-edit", { &mud_infra::m(), &mud_type::m(), &mud_refl::m(), &mud_srlz::m(), &mud_math::m(), &mud_geom::m(), &mud_ui::m(), &mud_uio::m(), &mud_gfx::m(), &mud_gfx_pbr::m() })
	{}
}

#ifdef MUD_GFX_EDIT_MODULE
extern "C"
Module& getModule()
{
		return mud_gfx_edit::m();
}
#endif
