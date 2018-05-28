#pragma once

#include <lang/Generated/Forward.h>

#include <obj/Generated/Types.h>

#include <obj/Type.h>
#include <obj/Proto.h>

#include <string>
#include <vector>
#include <stdint.h>


namespace mud
{
    // Exported types
    template <> MUD_LANG_EXPORT Type& type<mud::StreamModifier>();
    template <> MUD_LANG_EXPORT Type& type<mud::ValveKind>();
    
    template <> MUD_LANG_EXPORT Type& type<mud::LuaInterpreter>();
    template <> MUD_LANG_EXPORT Type& type<mud::Pipe>();
    template <> MUD_LANG_EXPORT Type& type<mud::Process>();
    template <> MUD_LANG_EXPORT Type& type<mud::StreamBranch>();
    template <> MUD_LANG_EXPORT Type& type<mud::Valve>();
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessCallable>();
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessCreate>();
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessDisplay>();
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessGetMember>();
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessSetMember>();
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessValue>();
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessInput>();
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessOutput>();
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessFunction>();
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessMethod>();
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessScript>();
    template <> MUD_LANG_EXPORT Type& type<mud::Script>();
    template <> MUD_LANG_EXPORT Type& type<mud::Stream>();
    template <> MUD_LANG_EXPORT Type& type<mud::VisualScript>();
}
