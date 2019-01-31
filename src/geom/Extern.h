#pragma once

#include <stl/vector.h>
#include <stl/unordered_map.h>
#include <geom/Api.h>

namespace stl
{
	using namespace mud;
	export_ extern template class vector<Poisson*>;
	export_ extern template class vector<Geometry*>;
	export_ extern template class vector<Geometry>;
	export_ extern template class vector<Circle>;
	export_ extern template class vector<IcoSphere>;
	export_ extern template class vector<ProcShape>;
	export_ extern template class vector<Distribution::Point>;
	export_ extern template class vector<vector<Distribution::Point>>;
	export_ extern template class vector<vector<Distribution::Point>*>;
	export_ extern template class unordered_map<int64_t, int>;
}
