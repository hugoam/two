#pragma once

#include <procgen-gfx/Forward.h>

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <obj/Type.h>
//#include <proto/Proto.h>
#endif

#ifndef MUD_MODULES
#include <infra/Types.h>
#include <obj/Types.h>
#include <srlz/Types.h>
#include <math/Types.h>
#include <geom/Types.h>
#include <procgen/Types.h>
#include <ctx/Types.h>
#include <ui/Types.h>
#include <uio/Types.h>
#include <gfx/Types.h>
#include <gfx-ui/Types.h>
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
