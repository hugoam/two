#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.bgfx;
#else
#include <refl/Module.h>
#include <meta/infra/infra.meta.h>
#include <meta/type/type.meta.h>
#include <meta/math/math.meta.h>
#include <meta/ctx/ctx.meta.h>
#include <meta/bgfx/bgfx.meta.h>
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
