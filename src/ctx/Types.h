#pragma once

#include <ctx/Forward.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <type/Type.h>
#endif


namespace two
{
    // Exported types
    export_ template <> TWO_CTX_EXPORT Type& type<two::Key>();
    export_ template <> TWO_CTX_EXPORT Type& type<two::MouseButtonCode>();
    export_ template <> TWO_CTX_EXPORT Type& type<two::InputMod>();
    export_ template <> TWO_CTX_EXPORT Type& type<two::DeviceType>();
    export_ template <> TWO_CTX_EXPORT Type& type<two::EventType>();
    
    
    export_ template <> TWO_CTX_EXPORT Type& type<two::RenderSystem>();
    export_ template <> TWO_CTX_EXPORT Type& type<two::Context>();
    export_ template <> TWO_CTX_EXPORT Type& type<two::InputEvent>();
    export_ template <> TWO_CTX_EXPORT Type& type<two::MouseEvent>();
    export_ template <> TWO_CTX_EXPORT Type& type<two::KeyEvent>();
    export_ template <> TWO_CTX_EXPORT Type& type<two::ControlNode>();
    export_ template <> TWO_CTX_EXPORT Type& type<two::Keyboard>();
    export_ template <> TWO_CTX_EXPORT Type& type<two::Mouse>();
}
