#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <meta/infra/Module.h>
#include <meta/jobs/Module.h>
#include <meta/type/Module.h>
#include <meta/pool/Module.h>
#include <meta/math/Module.h>
#include <meta/geom/Module.h>
#include <meta/ctx/Module.h>
#include <meta/bgfx/Module.h>
#include <meta/gfx/Module.h>
#include <meta/gfx/Convert.h>
#endif

#include <gfx/Api.h>
#define MUD_GFX_REFLECTION_IMPL
#include <meta/gfx/Meta.h>

namespace mud
{
	mud_gfx::mud_gfx()
		: Module("mud::gfx", { &mud_infra::m(), &mud_jobs::m(), &mud_type::m(), &mud_pool::m(), &mud_math::m(), &mud_geom::m(), &mud_ctx::m(), &mud_bgfx::m() })
	{
		// setup reflection meta data
		mud_gfx_meta(*this);
	}
}

#ifdef MUD_GFX_MODULE
extern "C"
Module& getModule()
{
		return mud_gfx::m();
}
#endif
