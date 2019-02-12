#include <mud/infra.refl.h>
#include <mud/type.refl.h>
#include <mud/ctx.refl.h>
#include <mud/refl.h>
#include <mud/math.refl.h>
#include <mud/infra.h>
#include <mud/bgfx.refl.h>


#ifdef MUD_MODULES
module mud.bgfx;
#else
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
