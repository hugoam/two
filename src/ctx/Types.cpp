

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ctx;
#else
#include <ctx/Types.h>
#include <ctx/Api.h>
#include <obj/Vector.h>
//#include <ecs/Proto.h>
#endif

namespace mud
{
    // Exported types
    template <> MUD_CTX_EXPORT Type& type<mud::DeviceMask>() { static Type ty("mud::DeviceMask"); return ty; }
    template <> MUD_CTX_EXPORT Type& type<mud::DeviceType>() { static Type ty("mud::DeviceType"); return ty; }
    template <> MUD_CTX_EXPORT Type& type<mud::EventType>() { static Type ty("mud::EventType"); return ty; }
    template <> MUD_CTX_EXPORT Type& type<mud::InputMod>() { static Type ty("mud::InputMod"); return ty; }
    template <> MUD_CTX_EXPORT Type& type<mud::Key>() { static Type ty("mud::Key"); return ty; }
    template <> MUD_CTX_EXPORT Type& type<mud::MouseButtonCode>() { static Type ty("mud::MouseButtonCode"); return ty; }
    
    template <> MUD_CTX_EXPORT Type& type<mud::Context>() { static Type ty("Context"); return ty; }
    template <> MUD_CTX_EXPORT Type& type<mud::ControlNode>() { static Type ty("ControlNode"); return ty; }
    template <> MUD_CTX_EXPORT Type& type<mud::InputEvent>() { static Type ty("InputEvent"); return ty; }
    template <> MUD_CTX_EXPORT Type& type<mud::RenderSystem>() { static Type ty("RenderSystem"); return ty; }
    template <> MUD_CTX_EXPORT Type& type<mud::KeyEvent>() { static Type ty("KeyEvent", type<mud::InputEvent>()); return ty; }
    template <> MUD_CTX_EXPORT Type& type<mud::MouseEvent>() { static Type ty("MouseEvent", type<mud::InputEvent>()); return ty; }
}
