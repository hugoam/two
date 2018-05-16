#pragma once

#include <uio/Generated/Forward.h>

#include <obj/Generated/Types.h>
#include <lang/Generated/Types.h>
#include <ui/Generated/Types.h>

#include <obj/Type.h>
#include <obj/Proto.h>

#include <string>
#include <vector>
#include <stdint.h>


namespace mud
{
    // Exported types
    template <> MUD_UIO_EXPORT Type& type<mud::EditorHint>();
    
    template <> MUD_UIO_EXPORT Type& type<mud::ScriptEditor>();
}
