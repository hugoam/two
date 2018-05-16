#pragma once

#include <gen/Generated/Forward.h>

#include <obj/Generated/Types.h>
#include <math/Generated/Types.h>
#include <geom/Generated/Types.h>
#include <ui/Generated/Types.h>
#include <gfx/Generated/Types.h>

#include <obj/Type.h>
#include <obj/Proto.h>

#include <string>
#include <vector>
#include <stdint.h>

#include <gen/Structs.h>

namespace mud
{
    // Exported types
    template <> MUD_GEN_EXPORT Type& type<mud::PatternSampling>();
    template <> MUD_GEN_EXPORT Type& type<mud::Result>();
    template <> MUD_GEN_EXPORT Type& type<std::vector<mud::Image256>>();
    
    template <> MUD_GEN_EXPORT Type& type<mud::Circlifier>();
    template <> MUD_GEN_EXPORT Type& type<mud::Fract>();
    template <> MUD_GEN_EXPORT Type& type<mud::FractSample>();
    template <> MUD_GEN_EXPORT Type& type<mud::FractTab>();
    template <> MUD_GEN_EXPORT Type& type<mud::Noise>();
    template <> MUD_GEN_EXPORT Type& type<mud::Pattern>();
    template <> MUD_GEN_EXPORT Type& type<mud::Tile>();
    template <> MUD_GEN_EXPORT Type& type<mud::Tileblock>();
    template <> MUD_GEN_EXPORT Type& type<mud::Tileset>();
    template <> MUD_GEN_EXPORT Type& type<mud::Wave>();
    template <> MUD_GEN_EXPORT Type& type<mud::WaveTileset>();
    template <> MUD_GEN_EXPORT Type& type<mud::TileWave>();
    template <> MUD_GEN_EXPORT Type& type<mud::array_3d<float>>();
}
