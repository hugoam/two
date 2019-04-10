#include <mud/infra.refl.h>
#include <mud/refl.h>
#include <mud/infra.h>


#ifdef MUD_MODULES
module mud.infra;
#else
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
