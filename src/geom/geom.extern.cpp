#ifndef USE_STL
#ifdef TWO_MODULES
module two.geom;
#else
#include <stl/vector.hpp>
#include <stl/unordered_map.hpp>
#include <geom/Api.h>
#endif

namespace stl
{
	using namespace two;
	template class TWO_GEOM_EXPORT vector<Poisson*>;
	template class TWO_GEOM_EXPORT vector<Geometry*>;
	template class TWO_GEOM_EXPORT vector<Geometry>;
	template class TWO_GEOM_EXPORT vector<Circle>;
	template class TWO_GEOM_EXPORT vector<IcoSphere>;
	template class TWO_GEOM_EXPORT vector<ProcShape>;
	template class TWO_GEOM_EXPORT vector<MarchingCubes::Cache::Normal>;
	template class TWO_GEOM_EXPORT vector<Distribution::Point>;
	template class TWO_GEOM_EXPORT vector<vector<Distribution::Point>>;
	template class TWO_GEOM_EXPORT vector<vector<Distribution::Point>*>;
	template class TWO_GEOM_EXPORT unordered_map<int64_t, int>;
}
#endif
