#pragma once

#include <stl/vector.h>
#include <refl/Api.h>

namespace stl
{
	using namespace mud;
	export_ extern template class vector<Namespace>;
	export_ extern template class vector<Param>;
	export_ extern template class vector<Function>;
	export_ extern template class vector<Operator>;
	export_ extern template class vector<Constructor>;
	export_ extern template class vector<CopyConstructor>;
	export_ extern template class vector<Destructor>;
	export_ extern template class vector<Method>;
	export_ extern template class vector<Member>;
	export_ extern template class vector<Static>;
	export_ extern template class vector<Function*>;
	export_ extern template class vector<Method*>;
	export_ extern template class vector<Member*>;
	export_ extern template class vector<Meta*>;
	export_ extern template class vector<Enum*>;
	export_ extern template class vector<Convert*>;
	export_ extern template class vector<Iterable*>;
	export_ extern template class vector<Sequence*>;
	export_ extern template class vector<Class*>;
	export_ extern template class vector<Module*>;
	export_ extern template class vector<Prototype*>;
}
