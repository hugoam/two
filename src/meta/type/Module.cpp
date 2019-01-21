#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.type;
#else
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
#include <meta/type/Convert.h>
#endif

#include <type/Api.h>
#define MUD_TYPE_REFLECTION_IMPL
#include <meta/type/Meta.h>

namespace mud
{
	mud_type::mud_type()
		: Module("mud::type", { &mud_infra::m() })
	{
		// setup reflection meta data
		mud_type_meta(*this);
	}
}

#ifdef MUD_TYPE_MODULE
extern "C"
Module& getModule()
{
		return mud_type::m();
}
#endif
