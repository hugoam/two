#include <mud/infra.refl.h>
#include <mud/refl.h>
#include <mud/infra.h>
#include <mud/type.h>

#ifdef MUD_MODULES
module mud.infra;
#else
#endif


using namespace mud;


namespace mud
{
	void mud_infra_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	
	// Sequences
	
	}
}

namespace mud
{
	mud_infra::mud_infra()
		: Module("mud::infra", {  })
	{
		// setup reflection meta data
		mud_infra_meta(*this);
	}
}

#ifdef MUD_INFRA_MODULE
extern "C"
Module& getModule()
{
		return mud_infra::m();
}
#endif
