#pragma once

#include <wfc/Forward.h>

#if defined TWO_TYPE_LIB
#include <type/Type.h>
#endif


namespace two
{
    // Exported types
    template <> TWO_WFC_EXPORT Type& type<two::Result>();
    
    
    template <> TWO_WFC_EXPORT Type& type<two::Tile>();
    template <> TWO_WFC_EXPORT Type& type<two::Tileset>();
    template <> TWO_WFC_EXPORT Type& type<two::Wave>();
    template <> TWO_WFC_EXPORT Type& type<two::WaveTileset>();
    template <> TWO_WFC_EXPORT Type& type<two::TileWave>();
}
