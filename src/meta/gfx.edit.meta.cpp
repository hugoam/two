#include <infra/Cpp20.h>

#ifdef TWO_MODULES
module two.gfx-edit;
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

namespace two
{
	two_gfx_edit::two_gfx_edit()
		: Module("two::gfx-edit", { &two_infra::m(), &two_type::m(), &two_refl::m(), &two_srlz::m(), &two_math::m(), &two_geom::m(), &two_ui::m(), &two_uio::m(), &two_gfx::m(), &two_gfx_pbr::m() })
	{}
}

#ifdef TWO_GFX_EDIT_MODULE
extern "C"
Module& getModule()
{
	return two_gfx_edit::m();
}
#endif
