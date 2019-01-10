#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx-pbr;
#else
#include <meta/gfx-pbr/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/gfx-pbr/Convert.h>
#endif
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
