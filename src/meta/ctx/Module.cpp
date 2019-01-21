#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ctx;
#else
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
#include <meta/math/Module.h>
#include <meta/ctx/Module.h>
#include <meta/ctx/Convert.h>
#endif

#include <ctx/Api.h>
#define MUD_CTX_REFLECTION_IMPL
#include <meta/ctx/Meta.h>

namespace mud
{
	mud_ctx::mud_ctx()
		: Module("mud::ctx", { &mud_infra::m(), &mud_type::m(), &mud_math::m() })
	{
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
