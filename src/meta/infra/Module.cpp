#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.infra;
#else
#include <type/Vector.h>
#include <type/Any.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/infra/Module.h>
#include <meta/infra/Convert.h>
#endif

#include <infra/Api.h>

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
