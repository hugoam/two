#pragma once

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>
#include <pool/Forward.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <type/Type.h>
#endif

#ifndef MUD_MODULES
#include <infra/Types.h>
#include <type/Types.h>
#endif


namespace mud
{
    // Exported types
    
    
    export_ template <> MUD_POOL_EXPORT Type& type<mud::Pool>();
    export_ template <> MUD_POOL_EXPORT Type& type<mud::HandlePool>();
}
