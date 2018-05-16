
#include <ctx/Generated/Module.h>

#ifdef MUD_CTX_REFLECT
#include <ctx/Generated/Convert.h>

#define MUD_CTX_REFLECTION_IMPL
#include <ctx/Generated/Meta.h>
#endif

namespace mud
{
	mudctx::mudctx()
		: Module("mud::ctx")
	{
        // ensure dependencies are instantiated
        mudobj::module();
        mudmath::module();

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
	return mudctx::module();
}
#endif
