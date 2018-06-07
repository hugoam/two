#pragma once

#include <uio/Generated/Forward.h>

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <obj/Type.h>
#include <obj/Proto.h>
#endif

#ifndef MUD_MODULES
#include <obj/Generated/Types.h>
#include <lang/Generated/Types.h>
#include <ui/Generated/Types.h>
#endif

#ifndef MUD_CPP_20
#include <string>
#include <vector>
#include <cstdint>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_UIO_EXPORT Type& type<mud::EditorHint>();
    
    export_ template <> MUD_UIO_EXPORT Type& type<mud::ScriptEditor>();
}
