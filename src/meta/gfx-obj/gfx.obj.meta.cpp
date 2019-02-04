#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx-obj;
#else
#include <refl/Module.h>
#include <meta/infra/infra.meta.h>
#include <meta/type/type.meta.h>
#include <meta/srlz/srlz.meta.h>
#include <meta/math/math.meta.h>
#include <meta/geom/geom.meta.h>
#include <meta/gfx/gfx.meta.h>
#include <meta/gfx-obj/gfx.obj.meta.h>
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
