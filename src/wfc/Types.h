#pragma once

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>
#include <wfc/Forward.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <type/Type.h>
#endif

#ifndef MUD_MODULES
#include <infra/Types.h>
#include <type/Types.h>
#include <srlz/Types.h>
#include <math/Types.h>
#include <geom/Types.h>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_WFC_EXPORT Type& type<mud::Result>();
    
    
    export_ template <> MUD_WFC_EXPORT Type& type<mud::Tile>();
    export_ template <> MUD_WFC_EXPORT Type& type<mud::Tileset>();
    export_ template <> MUD_WFC_EXPORT Type& type<mud::Wave>();
    export_ template <> MUD_WFC_EXPORT Type& type<mud::WaveTileset>();
    export_ template <> MUD_WFC_EXPORT Type& type<mud::TileWave>();
}
