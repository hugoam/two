#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.infra;
#else
#include <refl/Module.h>
#include <meta/infra.meta.h>
#endif

namespace mud
{
	mud_infra::mud_infra()
		: Module("mud::infra", {  })
	{}
}

#ifdef MUD_INFRA_MODULE
extern "C"
Module& getModule()
{
		return mud_infra::m();
}
#endif
