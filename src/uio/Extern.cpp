#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.uio;
#else
#include <stl/tinystl/vector.impl.h>
#include <stl/tinystl/unordered_map.impl.h>
#include <uio/Extern.h>
#endif

using namespace mud;
namespace tinystl
{
	template class MUD_UIO_EXPORT vector<EditSpec>;
	template class MUD_UIO_EXPORT unordered_map<Module*, bool>;
}
