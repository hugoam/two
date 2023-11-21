#pragma once

#include <wfc/Forward.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <type/Type.h>
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
