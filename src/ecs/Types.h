#pragma once

#ifndef TWO_MODULES
#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>
#endif
#include <ecs/Forward.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <type/Type.h>
#endif

#ifndef TWO_MODULES
#include <infra/Types.h>
#include <pool/Types.h>
#include <type/Types.h>
#endif


namespace two
{
    // Exported types
    
    
    export_ template <> TWO_ECS_EXPORT Type& type<two::Entity>();
    export_ template <> TWO_ECS_EXPORT Type& type<two::Entt>();
    export_ template <> TWO_ECS_EXPORT Type& type<two::OEntt>();
    export_ template <> TWO_ECS_EXPORT Type& type<two::Complex>();
}
