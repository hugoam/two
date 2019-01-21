#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.math;
#else
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
#include <meta/math/Module.h>
#include <meta/math/Convert.h>
#endif

#include <math/Api.h>
#define MUD_MATH_REFLECTION_IMPL
#include <meta/math/Meta.h>

namespace mud
{
	mud_math::mud_math()
		: Module("mud::math", { &mud_infra::m(), &mud_type::m() })
	{
		// setup reflection meta data
		mud_math_meta(*this);
	}
}

#ifdef MUD_MATH_MODULE
extern "C"
Module& getModule()
{
		return mud_math::m();
}
#endif
