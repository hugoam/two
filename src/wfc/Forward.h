#pragma once

#include <infra/Config.h>

#include <infra/Forward.h>
#include <type/Forward.h>
#include <srlz/Forward.h>
#include <math/Forward.h>
#include <geom/Forward.h>

#ifndef MUD_WFC_EXPORT
#define MUD_WFC_EXPORT MUD_IMPORT
#endif

namespace mud
{
    enum Result : unsigned int;
    
    
    struct Tile;
    struct Tileset;
    struct DoubleGenerator;
    struct Wave;
    struct WaveTileset;
    struct TileWave;
    struct VoxelTile;
    struct RGBA;
    struct PalettedImage;
    class Patternset;
}
