#pragma once

#include <infra/Config.h>

#include <infra/Forward.h>
#include <type/Forward.h>
#include <srlz/Forward.h>
#include <math/Forward.h>
#include <geom/Forward.h>

#ifndef TWO_WFC_EXPORT
#define TWO_WFC_EXPORT TWO_IMPORT
#endif

namespace two
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
