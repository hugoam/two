#ifndef USE_STL
#ifdef TWO_MODULES
module two.refl;
#else
#include <stl/vector.hpp>
#include <refl/Api.h>
#endif

namespace stl
{
	using namespace two;
	template class TWO_REFL_EXPORT vector<void*>;
	template class TWO_REFL_EXPORT vector<Alias*>;
	template class TWO_REFL_EXPORT vector<Function*>;
	template class TWO_REFL_EXPORT vector<Method*>;
	template class TWO_REFL_EXPORT vector<Member*>;
	template class TWO_REFL_EXPORT vector<Meta*>;
	template class TWO_REFL_EXPORT vector<Enum*>;
	template class TWO_REFL_EXPORT vector<Convert*>;
	template class TWO_REFL_EXPORT vector<Iterable*>;
	template class TWO_REFL_EXPORT vector<Sequence*>;
	template class TWO_REFL_EXPORT vector<Class*>;
	template class TWO_REFL_EXPORT vector<Module*>;
	template class TWO_REFL_EXPORT vector<Namespace>;
	template class TWO_REFL_EXPORT vector<Param>;
	template class TWO_REFL_EXPORT vector<Function>;
	template class TWO_REFL_EXPORT vector<Operator>;
	template class TWO_REFL_EXPORT vector<Constructor>;
	template class TWO_REFL_EXPORT vector<CopyConstructor>;
	template class TWO_REFL_EXPORT vector<Destructor>;
	template class TWO_REFL_EXPORT vector<Method>;
	template class TWO_REFL_EXPORT vector<Member>;
	template class TWO_REFL_EXPORT vector<Static>;
}
#endif
