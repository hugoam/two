#include <mud/srlz.refl.h>
#include <mud/uio.refl.h>
#include <mud/gfx.pbr.refl.h>
#include <mud/geom.refl.h>
#include <mud/ui.refl.h>
#include <mud/gfx.refl.h>
#include <mud/infra.refl.h>
#include <mud/type.refl.h>
#include <mud/refl.refl.h>
#include <mud/refl.h>
#include <mud/math.refl.h>
#include <mud/infra.h>
#include <mud/gfx.edit.refl.h>


#ifdef MUD_MODULES
module mud.gfx-edit;
#else
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
