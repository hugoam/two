#include <obj/Cpp20.h>

#ifdef MUD_MODULES
module mud.ctx;
#else
#include <ctx/Generated/Module.h>
#endif

#ifdef MUD_CTX_REFLECT
#ifndef MUD_MODULES
#include <ctx/Generated/Convert.h>
#endif
#define MUD_CTX_REFLECTION_IMPL
#include <ctx/Generated/Meta.h>
#endif

namespace mud
{
	mudctx::mudctx()
		: Module("mud::ctx")
	{
        // ensure dependencies are instantiated
        mudobj::m();
        mudsrlz::m();
        mudmath::m();

#ifdef MUD_CTX_REFLECT
        // setup reflection meta data
		ctx_meta(*this);
#endif
	}
}

#ifdef MUD_CTX_MODULE
extern "C"
MUD_CTX_EXPORT Module& getModule()
{
	return mudctx::m();
}
#endif
