#include <two/infra.h>

module;
module two.gfx.edit.meta;

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
