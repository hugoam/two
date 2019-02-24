#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx-obj;
#else
#include <refl/Module.h>
#include <meta/infra.meta.h>
#include <meta/type.meta.h>
#include <meta/srlz.meta.h>
#include <meta/math.meta.h>
#include <meta/geom.meta.h>
#include <meta/gfx.meta.h>
#include <meta/gfx.obj.meta.h>
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
