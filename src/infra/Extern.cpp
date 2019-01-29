#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.infra;
#else
#include <stl/tinystl/vector.impl.h>
#include <infra/Extern.h>
#endif

using namespace mud;
namespace tinystl
{
	template class MUD_INFRA_EXPORT vector<string>;
	template class MUD_INFRA_EXPORT vector<uchar>;
}
