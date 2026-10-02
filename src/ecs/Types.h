#pragma once

#include <ecs/Forward.h>

#if defined TWO_TYPE_LIB
#include <type/Type.h>
#endif


namespace two
{
    // Exported types
    
    
    template <> TWO_ECS_EXPORT Type& type<two::Entity>();
    template <> TWO_ECS_EXPORT Type& type<two::Entt>();
    template <> TWO_ECS_EXPORT Type& type<two::OEntt>();
    template <> TWO_ECS_EXPORT Type& type<two::Complex>();
}
