#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.uio;
#else
#include <stl/vector.hpp>
#include <stl/unordered_map.hpp>
#include <uio/Extern.h>
#endif

namespace stl
{
	using namespace mud;
	template class MUD_UIO_EXPORT vector<EditSpec>;
	template class MUD_UIO_EXPORT unordered_map<Module*, bool>;
}
