#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.bgfx;
#else
#include <refl/Module.h>
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
#include <meta/math/Module.h>
#include <meta/ctx/Module.h>
#include <meta/bgfx/Module.h>
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
