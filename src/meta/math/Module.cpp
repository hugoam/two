#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.math;
#else
#include <meta/math/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/math/Convert.h>
#endif
#define MUD_MATH_REFLECTION_IMPL
#include <meta/math/Meta.h>

namespace mud
{
	mudmath::mudmath()
		: Module("mud::math")
	{
        // ensure dependencies are instantiated
        mudobj::m();
        mudsrlz::m();

        // setup reflection meta data
		mudmath_meta(*this);
	}
}

#ifdef MUD_MATH_MODULE
extern "C"
Module& getModule()
{
	return mudmath::m();
}
#endif
