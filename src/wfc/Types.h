#pragma once

#ifndef TWO_MODULES
#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>
#endif
#include <wfc/Forward.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <type/Type.h>
#endif

#ifndef TWO_MODULES
#include <infra/Types.h>
#include <type/Types.h>
#include <srlz/Types.h>
#include <math/Types.h>
#include <geom/Types.h>
#endif


namespace two
{
    // Exported types
    export_ template <> TWO_WFC_EXPORT Type& type<two::Result>();
    
    
    export_ template <> TWO_WFC_EXPORT Type& type<two::Tile>();
    export_ template <> TWO_WFC_EXPORT Type& type<two::Tileset>();
    export_ template <> TWO_WFC_EXPORT Type& type<two::Wave>();
    export_ template <> TWO_WFC_EXPORT Type& type<two::WaveTileset>();
    export_ template <> TWO_WFC_EXPORT Type& type<two::TileWave>();
}
