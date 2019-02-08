#ifndef USE_STL
#ifdef MUD_MODULES
module mud.jobs;
#else
#include <stl/vector.hpp>
#include <math/Grid.hpp>
#include <noise/Api.h>
#endif

namespace mud
{
	template struct MUD_NOISE_EXPORT vector3d<float>;
}
#endif
