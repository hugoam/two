#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx-edit;
#else
#include <refl/Module.h>
#include <meta/infra.meta.h>
#include <meta/type.meta.h>
#include <meta/refl.meta.h>
#include <meta/srlz.meta.h>
#include <meta/math.meta.h>
#include <meta/geom.meta.h>
#include <meta/ui.meta.h>
#include <meta/uio.meta.h>
#include <meta/gfx.meta.h>
#include <meta/gfx.pbr.meta.h>
#include <meta/gfx.edit.meta.h>
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
