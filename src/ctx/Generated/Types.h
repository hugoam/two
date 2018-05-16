#pragma once

#include <ctx/Generated/Forward.h>

#include <obj/Generated/Types.h>
#include <math/Generated/Types.h>

#include <obj/Type.h>
#include <obj/Proto.h>

#include <string>
#include <vector>
#include <stdint.h>


namespace mud
{
    // Exported types
    template <> MUD_CTX_EXPORT Type& type<mud::DeviceMask>();
    template <> MUD_CTX_EXPORT Type& type<mud::DeviceType>();
    template <> MUD_CTX_EXPORT Type& type<mud::EventType>();
    template <> MUD_CTX_EXPORT Type& type<mud::InputModifier>();
    template <> MUD_CTX_EXPORT Type& type<mud::KeyCode>();
    template <> MUD_CTX_EXPORT Type& type<mud::MouseButtonCode>();
    
    template <> MUD_CTX_EXPORT Type& type<mud::Context>();
    template <> MUD_CTX_EXPORT Type& type<mud::RenderSystem>();
}
