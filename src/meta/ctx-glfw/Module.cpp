#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ctx-glfw;
#else
#include <meta/ctx-glfw/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/ctx-glfw/Convert.h>
#endif
#define MUD_CTX_GLFW_REFLECTION_IMPL
#include <meta/ctx-glfw/Meta.h>

namespace mud
{
	mud_ctx_glfw::mud_ctx_glfw()
		: Module("mud::ctx-glfw", { &mud_math::m(), &mud_ctx::m() })
	{
        // setup reflection meta data
		mud_ctx_glfw_meta(*this);
	}
}

#ifdef MUD_CTX_GLFW_MODULE
extern "C"
Module& getModule()
{
	return mud_ctx_glfw::m();
}
#endif
