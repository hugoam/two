#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.uio;
#else
#include <stl/tinystl/vector.impl.h>
#include <stl/tinystl/unordered_map.impl.h>
#include <pool/Extern.h>
#endif

using namespace mud;
namespace tinystl
{
	template class MUD_POOL_EXPORT vector<unique<Pool>>;
}
