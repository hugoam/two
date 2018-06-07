

#include <obj/Cpp20.h>

#ifdef MUD_MODULES
module mud.ctx;
#else
#include <ctx/Generated/Types.h>
#include <ctx/Generated/Module.h>
#include <obj/Proto.h>
#endif

namespace mud
{
    // Exported types
    template <> MUD_CTX_EXPORT Type& type<mud::DeviceMask>() { static Type ty("mud::DeviceMask"); return ty; }
    template <> MUD_CTX_EXPORT Type& type<mud::DeviceType>() { static Type ty("mud::DeviceType"); return ty; }
    template <> MUD_CTX_EXPORT Type& type<mud::EventType>() { static Type ty("mud::EventType"); return ty; }
    template <> MUD_CTX_EXPORT Type& type<mud::InputModifier>() { static Type ty("mud::InputModifier"); return ty; }
    template <> MUD_CTX_EXPORT Type& type<mud::KeyCode>() { static Type ty("mud::KeyCode"); return ty; }
    template <> MUD_CTX_EXPORT Type& type<mud::MouseButtonCode>() { static Type ty("mud::MouseButtonCode"); return ty; }
    
    template <> MUD_CTX_EXPORT Type& type<mud::Context>() { static Type ty("Context"); return ty; }
    template <> MUD_CTX_EXPORT Type& type<mud::RenderSystem>() { static Type ty("RenderSystem"); return ty; }
}
