#pragma once

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>
#include <pool/Forward.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <type/Type.h>
#endif

#ifndef TWO_MODULES
#include <infra/Types.h>
#include <type/Types.h>
#endif


namespace two
{
    // Exported types
    
    
    export_ template <> TWO_POOL_EXPORT Type& type<two::Pool>();
    export_ template <> TWO_POOL_EXPORT Type& type<two::HandlePool>();
}
