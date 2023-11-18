#include <two/srlz.refl.h>
#include <two/uio.refl.h>
#include <two/gfx.pbr.refl.h>
#include <two/geom.refl.h>
#include <two/ui.refl.h>
#include <two/gfx.refl.h>
#include <two/infra.refl.h>
#include <two/type.refl.h>
#include <two/refl.refl.h>
#include <two/refl.h>
#include <two/math.refl.h>
#include <two/infra.h>
#include <two/gfx.edit.refl.h>


module two.gfx-edit;

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
