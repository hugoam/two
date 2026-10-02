#pragma once

#include <ctx/Forward.h>

#if defined TWO_TYPE_LIB
#include <type/Type.h>
#endif


namespace two
{
    // Exported types
    template <> TWO_CTX_EXPORT Type& type<two::Key>();
    template <> TWO_CTX_EXPORT Type& type<two::MouseButtonCode>();
    template <> TWO_CTX_EXPORT Type& type<two::InputMod>();
    template <> TWO_CTX_EXPORT Type& type<two::DeviceType>();
    template <> TWO_CTX_EXPORT Type& type<two::EventType>();
    
    
    template <> TWO_CTX_EXPORT Type& type<two::RenderSystem>();
    template <> TWO_CTX_EXPORT Type& type<two::Context>();
    template <> TWO_CTX_EXPORT Type& type<two::InputEvent>();
    template <> TWO_CTX_EXPORT Type& type<two::MouseEvent>();
    template <> TWO_CTX_EXPORT Type& type<two::KeyEvent>();
    template <> TWO_CTX_EXPORT Type& type<two::ControlNode>();
    template <> TWO_CTX_EXPORT Type& type<two::Keyboard>();
    template <> TWO_CTX_EXPORT Type& type<two::Mouse>();
}
