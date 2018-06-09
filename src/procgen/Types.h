#pragma once

#include <procgen/Forward.h>

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <obj/Type.h>
//#include <proto/Proto.h>
#endif

#ifndef MUD_MODULES
#include <obj/Types.h>
#include <srlz/Types.h>
#include <math/Types.h>
#include <geom/Types.h>
#endif

#ifndef MUD_CPP_20
#include <string>
#include <vector>
#include <cstdint>
#endif

#include <procgen/Structs.h>

namespace mud
{
    // Exported types
    export_ template <> MUD_PROCGEN_EXPORT Type& type<mud::Noise::CellularDistanceFunction>();
    export_ template <> MUD_PROCGEN_EXPORT Type& type<mud::Noise::CellularReturnType>();
    export_ template <> MUD_PROCGEN_EXPORT Type& type<mud::Noise::FractalType>();
    export_ template <> MUD_PROCGEN_EXPORT Type& type<mud::Noise::Interp>();
    export_ template <> MUD_PROCGEN_EXPORT Type& type<mud::Noise::NoiseType>();
    export_ template <> MUD_PROCGEN_EXPORT Type& type<mud::PatternSampling>();
    export_ template <> MUD_PROCGEN_EXPORT Type& type<mud::Result>();
    
    export_ template <> MUD_PROCGEN_EXPORT Type& type<mud::Circlifier>();
    export_ template <> MUD_PROCGEN_EXPORT Type& type<mud::Fract>();
    export_ template <> MUD_PROCGEN_EXPORT Type& type<mud::FractSample>();
    export_ template <> MUD_PROCGEN_EXPORT Type& type<mud::FractTab>();
    export_ template <> MUD_PROCGEN_EXPORT Type& type<mud::Noise>();
    export_ template <> MUD_PROCGEN_EXPORT Type& type<mud::Pattern>();
    export_ template <> MUD_PROCGEN_EXPORT Type& type<mud::Tile>();
    export_ template <> MUD_PROCGEN_EXPORT Type& type<mud::Tileset>();
    export_ template <> MUD_PROCGEN_EXPORT Type& type<mud::Wave>();
    export_ template <> MUD_PROCGEN_EXPORT Type& type<mud::TileWave>();
    export_ template <> MUD_PROCGEN_EXPORT Type& type<mud::WaveTileset>();
    export_ template <> MUD_PROCGEN_EXPORT Type& type<mud::array_3d<float>>();
}
