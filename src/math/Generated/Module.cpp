
#include <math/Generated/Module.h>

#ifdef MUD_MATH_REFLECT
#include <math/Generated/Convert.h>

#define MUD_MATH_REFLECTION_IMPL
#include <math/Generated/Meta.h>
#endif

namespace mud
{
	mudmath::mudmath()
		: Module("mud::math")
	{
        // ensure dependencies are instantiated
        mudobj::module();

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
	return mudmath::module();
}
#endif
