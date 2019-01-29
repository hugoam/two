#pragma once

#include <stl/vector.h>
#include <stl/string.h>
#include <stl/unordered_set.h>
#include <stl/unordered_map.h>
#include <type/Api.h>

namespace mud
{
	export_ extern template class vector<string>;
	export_ extern template class vector<Type*>;
	export_ extern template class vector<Var>;
	export_ extern template class vector<Ref>;
	export_ extern template class vector<void(*)(Ref, Ref)>;
	export_ extern template class vector<vector<void(*)(Ref, Ref)>>;
	export_ extern template class vector<unique<Indexer>>;
	export_ extern template class unordered_set<string>;
	export_ extern template class unordered_map<string, string>;
}
