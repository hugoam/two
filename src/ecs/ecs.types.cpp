#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
module two.ecs;
#else
#include <ecs/Types.h>
#include <ecs/Api.h>
#include <type/Vector.h>
#endif

namespace two
{
    // Exported types
    
    
    template <> TWO_ECS_EXPORT Type& type<two::Entity>() { static Type ty("Entity", sizeof(two::Entity)); return ty; }
    template <> TWO_ECS_EXPORT Type& type<two::Entt>() { static Type ty("Entt", sizeof(two::Entt)); return ty; }
    template <> TWO_ECS_EXPORT Type& type<two::OEntt>() { static Type ty("OEntt", type<two::Entt>(), sizeof(two::OEntt)); return ty; }
    template <> TWO_ECS_EXPORT Type& type<two::Complex>() { static Type ty("Complex", sizeof(two::Complex)); return ty; }
}
