#pragma once

#include <pool/Forward.h>

#if defined TWO_TYPE_LIB
#include <type/Type.h>
#endif


namespace two
{
    // Exported types
    
    
    template <> TWO_POOL_EXPORT Type& type<two::Pool>();
    template <> TWO_POOL_EXPORT Type& type<two::HandlePool>();
}
