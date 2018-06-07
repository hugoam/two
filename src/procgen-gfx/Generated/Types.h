#pragma once

#include <procgen-gfx/Generated/Forward.h>

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <obj/Type.h>
#include <obj/Proto.h>
#endif

#ifndef MUD_MODULES
#include <obj/Generated/Types.h>
#include <srlz/Generated/Types.h>
#include <math/Generated/Types.h>
#include <geom/Generated/Types.h>
#include <procgen/Generated/Types.h>
#include <ui/Generated/Types.h>
#include <uio/Generated/Types.h>
#include <gfx/Generated/Types.h>
#include <edit/Generated/Types.h>
#endif

#ifndef MUD_CPP_20
#include <string>
#include <vector>
#include <cstdint>
#endif


namespace mud
{
    // Exported types
    
    export_ template <> MUD_PROCGEN_GFX_EXPORT Type& type<mud::TileModel>();
    export_ template <> MUD_PROCGEN_GFX_EXPORT Type& type<mud::Tileblock>();
}
