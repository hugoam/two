#pragma once

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>
#include <frame/Forward.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <type/Type.h>
#endif

#ifndef MUD_MODULES
#include <gfx/Types.h>
#include <gfx-ui/Types.h>
#endif


namespace mud
{
    // Exported types
    
    
    export_ template <> MUD_FRAME_EXPORT Type& type<mud::Shell>();
    export_ template <> MUD_FRAME_EXPORT Type& type<mud::ShellContext>();
    export_ template <> MUD_FRAME_EXPORT Type& type<mud::ShellWindow>();
}
