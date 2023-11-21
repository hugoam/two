module;
#include <infra/Cpp20.h>
module two.ctx;

namespace two
{
    // Exported types
    template <> TWO_CTX_EXPORT Type& type<two::Key>() { static Type ty("Key", sizeof(two::Key)); return ty; }
    template <> TWO_CTX_EXPORT Type& type<two::MouseButtonCode>() { static Type ty("MouseButtonCode", sizeof(two::MouseButtonCode)); return ty; }
    template <> TWO_CTX_EXPORT Type& type<two::InputMod>() { static Type ty("InputMod", sizeof(two::InputMod)); return ty; }
    template <> TWO_CTX_EXPORT Type& type<two::DeviceType>() { static Type ty("DeviceType", sizeof(two::DeviceType)); return ty; }
    template <> TWO_CTX_EXPORT Type& type<two::EventType>() { static Type ty("EventType", sizeof(two::EventType)); return ty; }
    
    
    template <> TWO_CTX_EXPORT Type& type<two::RenderSystem>() { static Type ty("RenderSystem", sizeof(two::RenderSystem)); return ty; }
    template <> TWO_CTX_EXPORT Type& type<two::Context>() { static Type ty("Context", sizeof(two::Context)); return ty; }
    template <> TWO_CTX_EXPORT Type& type<two::InputEvent>() { static Type ty("InputEvent", sizeof(two::InputEvent)); return ty; }
    template <> TWO_CTX_EXPORT Type& type<two::MouseEvent>() { static Type ty("MouseEvent", type<two::InputEvent>(), sizeof(two::MouseEvent)); return ty; }
    template <> TWO_CTX_EXPORT Type& type<two::KeyEvent>() { static Type ty("KeyEvent", type<two::InputEvent>(), sizeof(two::KeyEvent)); return ty; }
    template <> TWO_CTX_EXPORT Type& type<two::ControlNode>() { static Type ty("ControlNode", sizeof(two::ControlNode)); return ty; }
    template <> TWO_CTX_EXPORT Type& type<two::Keyboard>() { static Type ty("Keyboard", sizeof(two::Keyboard)); return ty; }
    template <> TWO_CTX_EXPORT Type& type<two::Mouse>() { static Type ty("Mouse", sizeof(two::Mouse)); return ty; }
}
