#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ecs;
#else
#include <stl/tinystl/vector.impl.h>
#include <stl/tinystl/unordered_map.impl.h>
#include <ecs/Extern.h>
#endif

namespace mud
{
	template class MUD_ECS_EXPORT vector<Buffer*>;
	template class MUD_ECS_EXPORT vector<EntityData>;
	template class MUD_ECS_EXPORT vector<EntityStream>;
	template class MUD_ECS_EXPORT vector<unique<Buffer>>;
}
