#ifndef USE_STL
#ifdef MUD_MODULES
module mud.refl;
#else
#include <stl/vector.hpp>
#include <refl/Api.h>
#endif

namespace stl
{
	using namespace mud;
	template class MUD_TYPE_EXPORT vector<void*>;
	template class MUD_TYPE_EXPORT vector<Alias*>;
	template class MUD_TYPE_EXPORT vector<Function*>;
	template class MUD_TYPE_EXPORT vector<Method*>;
	template class MUD_TYPE_EXPORT vector<Member*>;
	template class MUD_TYPE_EXPORT vector<Meta*>;
	template class MUD_TYPE_EXPORT vector<Enum*>;
	template class MUD_TYPE_EXPORT vector<Convert*>;
	template class MUD_TYPE_EXPORT vector<Iterable*>;
	template class MUD_TYPE_EXPORT vector<Sequence*>;
	template class MUD_TYPE_EXPORT vector<Class*>;
	template class MUD_TYPE_EXPORT vector<Module*>;
	template class MUD_TYPE_EXPORT vector<Prototype*>;
	template class MUD_TYPE_EXPORT vector<Namespace>;
	template class MUD_TYPE_EXPORT vector<Param>;
	template class MUD_TYPE_EXPORT vector<Function>;
	template class MUD_TYPE_EXPORT vector<Operator>;
	template class MUD_TYPE_EXPORT vector<Constructor>;
	template class MUD_TYPE_EXPORT vector<CopyConstructor>;
	template class MUD_TYPE_EXPORT vector<Destructor>;
	template class MUD_TYPE_EXPORT vector<Method>;
	template class MUD_TYPE_EXPORT vector<Member>;
	template class MUD_TYPE_EXPORT vector<Static>;
}
#endif
