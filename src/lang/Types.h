#pragma once

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>
#include <lang/Forward.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <type/Type.h>
#endif

#ifndef TWO_MODULES
#include <infra/Types.h>
#include <type/Types.h>
#include <pool/Types.h>
#include <refl/Types.h>
#endif


namespace two
{
    // Exported types
    export_ template <> TWO_LANG_EXPORT Type& type<two::Language>();
    
    
    export_ template <> TWO_LANG_EXPORT Type& type<two::Script>();
    export_ template <> TWO_LANG_EXPORT Type& type<two::ScriptError>();
    export_ template <> TWO_LANG_EXPORT Type& type<two::TextScript>();
    export_ template <> TWO_LANG_EXPORT Type& type<two::Interpreter>();
    export_ template <> TWO_LANG_EXPORT Type& type<two::ScriptClass>();
    export_ template <> TWO_LANG_EXPORT Type& type<two::LuaInterpreter>();
    export_ template <> TWO_LANG_EXPORT Type& type<two::StreamBranch>();
    export_ template <> TWO_LANG_EXPORT Type& type<two::Stream>();
    export_ template <> TWO_LANG_EXPORT Type& type<two::Valve>();
    export_ template <> TWO_LANG_EXPORT Type& type<two::Pipe>();
    export_ template <> TWO_LANG_EXPORT Type& type<two::Process>();
    export_ template <> TWO_LANG_EXPORT Type& type<two::VisualScript>();
    export_ template <> TWO_LANG_EXPORT Type& type<two::ProcessInput>();
    export_ template <> TWO_LANG_EXPORT Type& type<two::ProcessOutput>();
    export_ template <> TWO_LANG_EXPORT Type& type<two::ProcessValue>();
    export_ template <> TWO_LANG_EXPORT Type& type<two::ProcessCreate>();
    export_ template <> TWO_LANG_EXPORT Type& type<two::ProcessCallable>();
    export_ template <> TWO_LANG_EXPORT Type& type<two::ProcessScript>();
    export_ template <> TWO_LANG_EXPORT Type& type<two::ProcessFunction>();
    export_ template <> TWO_LANG_EXPORT Type& type<two::ProcessMethod>();
    export_ template <> TWO_LANG_EXPORT Type& type<two::ProcessGetMember>();
    export_ template <> TWO_LANG_EXPORT Type& type<two::ProcessSetMember>();
    export_ template <> TWO_LANG_EXPORT Type& type<two::ProcessDisplay>();
    export_ template <> TWO_LANG_EXPORT Type& type<two::WrenInterpreter>();
}
