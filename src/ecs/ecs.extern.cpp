#ifndef USE_STL
#ifdef MUD_MODULES
module mud.ecs;
#else
#include <stl/vector.hpp>
#include <ecs/Api.h>
#include <ecs/ECS.hpp>
#endif

namespace stl
{
	using namespace mud;
	template class MUD_ECS_EXPORT vector<Buffer*>;
	template class MUD_ECS_EXPORT vector<EntityStream*>;
	template class MUD_ECS_EXPORT vector<EntityStream>;
	template class MUD_ECS_EXPORT vector<unique<Buffer>>;
}
#endif
