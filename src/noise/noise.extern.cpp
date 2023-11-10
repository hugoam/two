#ifndef USE_STL
#ifdef TWO_MODULES
module two.jobs;
#else
#include <stl/vector.hpp>
#include <math/Grid.hpp>
#include <noise/Api.h>
#endif

namespace two
{
	template struct TWO_NOISE_EXPORT vector3d<float>;
}
#endif
