#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.jobs;
#else
#include <stl/tinystl/vector.impl.h>
#include <stl/tinystl/unordered_map.impl.h>
#include <noise/Extern.h>
#endif

namespace mud
{
	template struct MUD_NOISE_EXPORT array3d<float>;
}
