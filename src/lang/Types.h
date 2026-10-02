#pragma once

#include <lang/Forward.h>

#if defined TWO_TYPE_LIB
#include <type/Type.h>
#endif


namespace two
{
    // Exported types
    template <> TWO_LANG_EXPORT Type& type<two::Language>();
    
    
    template <> TWO_LANG_EXPORT Type& type<two::Script>();
    template <> TWO_LANG_EXPORT Type& type<two::ScriptError>();
    template <> TWO_LANG_EXPORT Type& type<two::TextScript>();
    template <> TWO_LANG_EXPORT Type& type<two::Interpreter>();
    template <> TWO_LANG_EXPORT Type& type<two::ScriptClass>();
    template <> TWO_LANG_EXPORT Type& type<two::LuaInterpreter>();
    template <> TWO_LANG_EXPORT Type& type<two::StreamBranch>();
    template <> TWO_LANG_EXPORT Type& type<two::Stream>();
    template <> TWO_LANG_EXPORT Type& type<two::Valve>();
    template <> TWO_LANG_EXPORT Type& type<two::Pipe>();
    template <> TWO_LANG_EXPORT Type& type<two::Process>();
    template <> TWO_LANG_EXPORT Type& type<two::VisualScript>();
    template <> TWO_LANG_EXPORT Type& type<two::ProcessInput>();
    template <> TWO_LANG_EXPORT Type& type<two::ProcessOutput>();
    template <> TWO_LANG_EXPORT Type& type<two::ProcessValue>();
    template <> TWO_LANG_EXPORT Type& type<two::ProcessCreate>();
    template <> TWO_LANG_EXPORT Type& type<two::ProcessCallable>();
    template <> TWO_LANG_EXPORT Type& type<two::ProcessScript>();
    template <> TWO_LANG_EXPORT Type& type<two::ProcessFunction>();
    template <> TWO_LANG_EXPORT Type& type<two::ProcessMethod>();
    template <> TWO_LANG_EXPORT Type& type<two::ProcessGetMember>();
    template <> TWO_LANG_EXPORT Type& type<two::ProcessSetMember>();
    template <> TWO_LANG_EXPORT Type& type<two::ProcessDisplay>();
    template <> TWO_LANG_EXPORT Type& type<two::WrenInterpreter>();
}
