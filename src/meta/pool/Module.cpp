#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.pool;
#else
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
#include <meta/pool/Module.h>
#include <meta/pool/Convert.h>
#endif

#include <pool/Api.h>
#define MUD_POOL_REFLECTION_IMPL
#include <meta/pool/Meta.h>

namespace mud
{
	mud_pool::mud_pool()
		: Module("mud::pool", { &mud_infra::m(), &mud_type::m() })
	{
		// setup reflection meta data
		mud_pool_meta(*this);
	}
}

#ifdef MUD_POOL_MODULE
extern "C"
Module& getModule()
{
		return mud_pool::m();
}
#endif
