#pragma once

#include <frame/Forward.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <type/Type.h>
#include <type/Vector.h>
#endif

#ifndef MUD_MODULES
#include <gfx/Types.h>
#include <gfx-ui/Types.h>
#endif

#ifndef MUD_CPP_20
#include <stl/string.h>
#include <cstdint>
#include <stl/vector.h>
#endif


namespace mud
{
    // Exported types
    
    export_ template <> MUD_FRAME_EXPORT Type& type<mud::Shell>();
    export_ template <> MUD_FRAME_EXPORT Type& type<mud::ShellContext>();
    
    export_ template struct MUD_FRAME_EXPORT Typed<vector<mud::Shell*>>;
    export_ template struct MUD_FRAME_EXPORT Typed<vector<mud::ShellContext*>>;
}
