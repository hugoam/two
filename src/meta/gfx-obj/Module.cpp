#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx-obj;
#else
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
#include <meta/srlz/Module.h>
#include <meta/math/Module.h>
#include <meta/geom/Module.h>
#include <meta/gfx/Module.h>
#include <meta/gfx-obj/Module.h>
#include <meta/gfx-obj/Convert.h>
#endif

#include <gfx-obj/Api.h>
#define MUD_GFX_OBJ_REFLECTION_IMPL
#include <meta/gfx-obj/Meta.h>

namespace mud
{
	mud_gfx_obj::mud_gfx_obj()
		: Module("mud::gfx-obj", { &mud_infra::m(), &mud_type::m(), &mud_srlz::m(), &mud_math::m(), &mud_geom::m(), &mud_gfx::m() })
	{
		// setup reflection meta data
		mud_gfx_obj_meta(*this);
	}
}

#ifdef MUD_GFX_OBJ_MODULE
extern "C"
Module& getModule()
{
		return mud_gfx_obj::m();
}
#endif
