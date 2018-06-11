#pragma once

#include <proto/Forward.h>

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <obj/Type.h>
//#include <proto/Proto.h>
#endif

#ifndef MUD_MODULES
#include <infra/Types.h>
#include <obj/Types.h>
#include <refl/Types.h>
#endif

#ifndef MUD_CPP_20
#include <string>
#include <vector>
#include <cstdint>
#endif


namespace mud
{
    // Exported types
    
    export_ template <> MUD_PROTO_EXPORT Type& type<mud::Complex>();
    export_ template <> MUD_PROTO_EXPORT Type& type<mud::Construct>();
    export_ template <> MUD_PROTO_EXPORT Type& type<mud::Prototype>();
}
