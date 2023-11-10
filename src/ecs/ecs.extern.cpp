#ifndef USE_STL
#ifdef TWO_MODULES
module two.ecs;
#else
#include <stl/vector.hpp>
#include <ecs/Api.h>
#include <ecs/ECS.hpp>
#endif

namespace stl
{
	using namespace two;
	template class TWO_ECS_EXPORT vector<Buffer*>;
	template class TWO_ECS_EXPORT vector<EntityStream*>;
	template class TWO_ECS_EXPORT vector<EntityStream>;
	template class TWO_ECS_EXPORT vector<unique<Buffer>>;
}
#endif
