#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.geom;
#else
#include <meta/type/Module.h>
#include <meta/math/Module.h>
#include <meta/geom/Module.h>
#include <meta/geom/Convert.h>
#endif

#include <geom/Api.h>
#define MUD_GEOM_REFLECTION_IMPL
#include <meta/geom/Meta.h>

namespace mud
{
	mud_geom::mud_geom()
		: Module("mud::geom", { &mud_type::m(), &mud_math::m() })
	{
		// setup reflection meta data
		mud_geom_meta(*this);
	}
}

#ifdef MUD_GEOM_MODULE
extern "C"
Module& getModule()
{
		return mud_geom::m();
}
#endif
