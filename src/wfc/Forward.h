#pragma once

#include <infra/Config.h>

#ifndef TWO_WFC_EXPORT
#define TWO_WFC_EXPORT TWO_IMPORT
#endif

namespace two
{
    export_ enum Result : unsigned int;


    export_ struct Tile;
    export_ struct Tileset;
    export_ struct DoubleGenerator;
    export_ struct Wave;
    export_ struct WaveTileset;
    export_ struct TileWave;
    export_ struct VoxelTile;
    export_ struct RGBA;
    export_ struct PalettedImage;
    export_ class Patternset;
}
