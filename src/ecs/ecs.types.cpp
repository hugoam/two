#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ecs;
#else
#include <ecs/Types.h>
#include <ecs/Api.h>
#include <type/Vector.h>
#endif

namespace mud
{
    // Exported types
    
    
    template <> MUD_ECS_EXPORT Type& type<mud::Complex>() { static Type ty("Complex", sizeof(mud::Complex)); return ty; }
    template <> MUD_ECS_EXPORT Type& type<mud::Entity>() { static Type ty("Entity", sizeof(mud::Entity)); return ty; }
}
