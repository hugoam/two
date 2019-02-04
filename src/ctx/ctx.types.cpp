#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ctx;
#else
#include <ctx/Types.h>
#include <ctx/Api.h>
#include <type/Vector.h>
#endif

namespace mud
{
    // Exported types
    template <> MUD_CTX_EXPORT Type& type<mud::DeviceType>() { static Type ty("mud::DeviceType", sizeof(mud::DeviceType)); return ty; }
    template <> MUD_CTX_EXPORT Type& type<mud::EventType>() { static Type ty("mud::EventType", sizeof(mud::EventType)); return ty; }
    template <> MUD_CTX_EXPORT Type& type<mud::InputMod>() { static Type ty("mud::InputMod", sizeof(mud::InputMod)); return ty; }
    template <> MUD_CTX_EXPORT Type& type<mud::Key>() { static Type ty("mud::Key", sizeof(mud::Key)); return ty; }
    template <> MUD_CTX_EXPORT Type& type<mud::MouseButtonCode>() { static Type ty("mud::MouseButtonCode", sizeof(mud::MouseButtonCode)); return ty; }
    
    template <> MUD_CTX_EXPORT Type& type<mud::Context>() { static Type ty("Context", sizeof(mud::Context)); return ty; }
    template <> MUD_CTX_EXPORT Type& type<mud::ControlNode>() { static Type ty("ControlNode", sizeof(mud::ControlNode)); return ty; }
    template <> MUD_CTX_EXPORT Type& type<mud::InputEvent>() { static Type ty("InputEvent", sizeof(mud::InputEvent)); return ty; }
    template <> MUD_CTX_EXPORT Type& type<mud::Keyboard>() { static Type ty("Keyboard", sizeof(mud::Keyboard)); return ty; }
    template <> MUD_CTX_EXPORT Type& type<mud::Mouse>() { static Type ty("Mouse", sizeof(mud::Mouse)); return ty; }
    template <> MUD_CTX_EXPORT Type& type<mud::RenderSystem>() { static Type ty("RenderSystem", sizeof(mud::RenderSystem)); return ty; }
    template <> MUD_CTX_EXPORT Type& type<mud::KeyEvent>() { static Type ty("KeyEvent", type<mud::InputEvent>(), sizeof(mud::KeyEvent)); return ty; }
    template <> MUD_CTX_EXPORT Type& type<mud::MouseEvent>() { static Type ty("MouseEvent", type<mud::InputEvent>(), sizeof(mud::MouseEvent)); return ty; }
}
