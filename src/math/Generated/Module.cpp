#include <obj/Cpp20.h>

#ifdef MUD_MODULES
module mud.math;
#else
#include <math/Generated/Module.h>
#endif

#ifdef MUD_MATH_REFLECT
#ifndef MUD_MODULES
#include <math/Generated/Convert.h>
#endif
#define MUD_MATH_REFLECTION_IMPL
#include <math/Generated/Meta.h>
#endif

namespace mud
{
	mudmath::mudmath()
		: Module("mud::math")
	{
        // ensure dependencies are instantiated
        mudobj::m();
        mudsrlz::m();

#ifdef MUD_MATH_REFLECT
        // setup reflection meta data
		math_meta(*this);
#endif
	}
}

#ifdef MUD_MATH_MODULE
extern "C"
MUD_MATH_EXPORT Module& getModule()
{
	return mudmath::m();
}
#endif
