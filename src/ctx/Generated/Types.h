#pragma once

#include <ctx/Generated/Forward.h>

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <obj/Type.h>
#include <obj/Proto.h>
#endif

#ifndef MUD_MODULES
#include <obj/Generated/Types.h>
#include <srlz/Generated/Types.h>
#include <math/Generated/Types.h>
#endif

#ifndef MUD_CPP_20
#include <string>
#include <vector>
#include <cstdint>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_CTX_EXPORT Type& type<mud::DeviceMask>();
    export_ template <> MUD_CTX_EXPORT Type& type<mud::DeviceType>();
    export_ template <> MUD_CTX_EXPORT Type& type<mud::EventType>();
    export_ template <> MUD_CTX_EXPORT Type& type<mud::InputModifier>();
    export_ template <> MUD_CTX_EXPORT Type& type<mud::KeyCode>();
    export_ template <> MUD_CTX_EXPORT Type& type<mud::MouseButtonCode>();
    
    export_ template <> MUD_CTX_EXPORT Type& type<mud::Context>();
    export_ template <> MUD_CTX_EXPORT Type& type<mud::RenderSystem>();
}
