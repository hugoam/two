#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.bgfx;
#else
#include <meta/bgfx/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/bgfx/Convert.h>
#endif
#define MUD_BGFX_REFLECTION_IMPL
#include <meta/bgfx/Meta.h>

namespace mud
{
	mud_bgfx::mud_bgfx()
		: Module("mud::bgfx")
	{
        // ensure dependencies are instantiated
        mud_infra::m();
        mud_type::m();
        mud_math::m();
        mud_ctx::m();
        //mud_ctx_glfw::m();

        // setup reflection meta data
		mud_bgfx_meta(*this);
	}
}

#ifdef MUD_BGFX_MODULE
extern "C"
Module& getModule()
{
	return mud_bgfx::m();
}
#endif
