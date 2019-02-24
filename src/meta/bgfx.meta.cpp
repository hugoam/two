#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.bgfx;
#else
#include <refl/Module.h>
#include <meta/infra.meta.h>
#include <meta/type.meta.h>
#include <meta/math.meta.h>
#include <meta/ctx.meta.h>
#include <meta/bgfx.meta.h>
#endif

namespace mud
{
	mud_bgfx::mud_bgfx()
		: Module("mud::bgfx", { &mud_infra::m(), &mud_type::m(), &mud_math::m(), &mud_ctx::m() })
	{}
}

#ifdef MUD_BGFX_MODULE
extern "C"
Module& getModule()
{
	return mud_bgfx::m();
}
#endif
