#pragma once

#include <pool/Forward.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <type/Type.h>
#include <type/Vector.h>
#endif

#ifndef MUD_MODULES
#include <infra/Types.h>
#include <type/Types.h>
#endif

#ifndef MUD_CPP_20
#include <string>
#include <cstdint>
#include <vector>
#endif


namespace mud
{
    // Exported types
    
    export_ template <> MUD_POOL_EXPORT Type& type<mud::HandlePool>();
    export_ template <> MUD_POOL_EXPORT Type& type<mud::Pool>();
    
    export_ template struct MUD_POOL_EXPORT Typed<std::vector<mud::HandlePool*>>;
    export_ template struct MUD_POOL_EXPORT Typed<std::vector<mud::Pool*>>;
}
