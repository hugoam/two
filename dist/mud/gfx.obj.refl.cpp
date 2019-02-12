#include <mud/srlz.refl.h>
#include <mud/geom.refl.h>
#include <mud/gfx.obj.refl.h>
#include <mud/gfx.refl.h>
#include <mud/infra.refl.h>
#include <mud/type.refl.h>
#include <mud/refl.h>
#include <mud/math.refl.h>
#include <mud/infra.h>


#ifdef MUD_MODULES
module mud.gfx-obj;
#else
#endif

namespace mud
{
	mud_gfx_obj::mud_gfx_obj()
		: Module("mud::gfx-obj", { &mud_infra::m(), &mud_type::m(), &mud_srlz::m(), &mud_math::m(), &mud_geom::m(), &mud_gfx::m() })
	{}
}

#ifdef MUD_GFX_OBJ_MODULE
extern "C"
Module& getModule()
{
		return mud_gfx_obj::m();
}
#endif
