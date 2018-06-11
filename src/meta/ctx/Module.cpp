#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ctx;
#else
#include <meta/ctx/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/ctx/Convert.h>
#endif
#define MUD_CTX_REFLECTION_IMPL
#include <meta/ctx/Meta.h>

namespace mud
{
	mud_ctx::mud_ctx()
		: Module("mud::ctx")
	{
        // ensure dependencies are instantiated
        mud_infra::m();
        mud_obj::m();
        mud_math::m();

        // setup reflection meta data
		mud_ctx_meta(*this);
	}
}

#ifdef MUD_CTX_MODULE
extern "C"
Module& getModule()
{
	return mud_ctx::m();
}
#endif
