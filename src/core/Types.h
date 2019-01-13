#pragma once

#include <core/Forward.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <type/Type.h>
#include <type/Vector.h>
#endif

#ifndef MUD_MODULES
#include <gfx/Types.h>
#include <gfx-ui/Types.h>
#endif

#ifndef MUD_CPP_20
#include <string>
#include <cstdint>
#include <vector>
#endif


namespace mud
{
    // Exported types
    
    export_ template <> MUD_CORE_EXPORT Type& type<mud::Shell>();
    export_ template <> MUD_CORE_EXPORT Type& type<mud::ShellContext>();
    
    export_ template struct MUD_CORE_EXPORT Typed<std::vector<mud::Shell*>>;
    export_ template struct MUD_CORE_EXPORT Typed<std::vector<mud::ShellContext*>>;
}
