#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.math;
#else
#include <stl/vector.hpp>
#include <stl/unordered_set.hpp>
#include <stl/unordered_map.hpp>
#include <type/Extern.h>
#endif

namespace stl
{
	using namespace mud;
	template class MUD_TYPE_EXPORT vector<string>;
	template class MUD_TYPE_EXPORT vector<Type*>;
	template class MUD_TYPE_EXPORT vector<Var>;
	template class MUD_TYPE_EXPORT vector<Ref>;
	template class MUD_TYPE_EXPORT vector<void(*)(Ref, Ref)>;
	template class MUD_TYPE_EXPORT vector<vector<void(*)(Ref, Ref)>>;
	template class MUD_TYPE_EXPORT vector<unique<Indexer>>;
	//template class MUD_TYPE_EXPORT unordered_set<string>;
	template class MUD_TYPE_EXPORT unordered_map<string, string>;
}
