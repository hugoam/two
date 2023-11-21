#ifndef USE_STL
module two.math;

namespace stl
{
	using namespace two;
	template class TWO_TYPE_EXPORT vector<string>;
	template class TWO_TYPE_EXPORT vector<Type*>;
	template class TWO_TYPE_EXPORT vector<Prototype*>;
	template class TWO_TYPE_EXPORT buf<Var>;
	template class TWO_TYPE_EXPORT buffer<Var>;
	template class TWO_TYPE_EXPORT vector<Var>;
	template class TWO_TYPE_EXPORT vector<Ref>;
	template class TWO_TYPE_EXPORT vector<void(*)(Ref, Ref)>;
	template class TWO_TYPE_EXPORT vector<vector<void(*)(Ref, Ref)>>;
	template class TWO_TYPE_EXPORT vector<unique<Indexer>>;
	//template class TWO_TYPE_EXPORT unordered_set<string>;
	template class TWO_TYPE_EXPORT unordered_map<string, string>;
}
#endif
