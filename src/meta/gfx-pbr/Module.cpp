#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx-pbr;
#else
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
#include <meta/math/Module.h>
#include <meta/geom/Module.h>
#include <meta/gfx/Module.h>
#include <meta/gfx-pbr/Module.h>
#include <meta/gfx-pbr/Convert.h>
#endif

#include <gfx-pbr/Api.h>
#define MUD_GFX_PBR_REFLECTION_IMPL
#include <meta/gfx-pbr/Meta.h>

namespace mud
{
	mud_gfx_pbr::mud_gfx_pbr()
		: Module("mud::gfx-pbr", { &mud_infra::m(), &mud_type::m(), &mud_math::m(), &mud_geom::m(), &mud_gfx::m() })
	{
		// setup reflection meta data
		mud_gfx_pbr_meta(*this);
	}
}

#ifdef MUD_GFX_PBR_MODULE
extern "C"
Module& getModule()
{
		return mud_gfx_pbr::m();
}
#endif
