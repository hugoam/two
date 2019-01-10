#pragma once

#include <wfc/Forward.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <type/Type.h>
#include <type/Vector.h>
#endif

#ifndef MUD_MODULES
#include <infra/Types.h>
#include <type/Types.h>
#include <srlz/Types.h>
#include <math/Types.h>
#include <geom/Types.h>
#endif

#ifndef MUD_CPP_20
#include <string>
#include <cstdint>
#include <vector>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_WFC_EXPORT Type& type<mud::Result>();
    
    export_ template <> MUD_WFC_EXPORT Type& type<mud::Tile>();
    export_ template <> MUD_WFC_EXPORT Type& type<mud::Tileset>();
    export_ template <> MUD_WFC_EXPORT Type& type<mud::Wave>();
    export_ template <> MUD_WFC_EXPORT Type& type<mud::TileWave>();
    export_ template <> MUD_WFC_EXPORT Type& type<mud::WaveTileset>();
    
    export_ template struct MUD_WFC_EXPORT Typed<std::vector<mud::Tile*>>;
    export_ template struct MUD_WFC_EXPORT Typed<std::vector<mud::Tileset*>>;
    export_ template struct MUD_WFC_EXPORT Typed<std::vector<mud::Wave*>>;
    export_ template struct MUD_WFC_EXPORT Typed<std::vector<mud::TileWave*>>;
    export_ template struct MUD_WFC_EXPORT Typed<std::vector<mud::WaveTileset*>>;
}
