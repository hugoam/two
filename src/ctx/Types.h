#pragma once

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>
#include <ctx/Forward.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <type/Type.h>
#endif

#ifndef MUD_MODULES
#include <infra/Types.h>
#include <type/Types.h>
#include <math/Types.h>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_CTX_EXPORT Type& type<mud::Key>();
    export_ template <> MUD_CTX_EXPORT Type& type<mud::MouseButtonCode>();
    export_ template <> MUD_CTX_EXPORT Type& type<mud::InputMod>();
    export_ template <> MUD_CTX_EXPORT Type& type<mud::DeviceType>();
    export_ template <> MUD_CTX_EXPORT Type& type<mud::EventType>();
    
    
    export_ template <> MUD_CTX_EXPORT Type& type<mud::RenderSystem>();
    export_ template <> MUD_CTX_EXPORT Type& type<mud::Context>();
    export_ template <> MUD_CTX_EXPORT Type& type<mud::InputEvent>();
    export_ template <> MUD_CTX_EXPORT Type& type<mud::MouseEvent>();
    export_ template <> MUD_CTX_EXPORT Type& type<mud::KeyEvent>();
    export_ template <> MUD_CTX_EXPORT Type& type<mud::ControlNode>();
    export_ template <> MUD_CTX_EXPORT Type& type<mud::Keyboard>();
    export_ template <> MUD_CTX_EXPORT Type& type<mud::Mouse>();
}
