module;
#include <infra/Cpp20.h>
module two.wfc;

namespace two
{
    // Exported types
    template <> TWO_WFC_EXPORT Type& type<two::Result>() { static Type ty("Result", sizeof(two::Result)); return ty; }
    
    
    template <> TWO_WFC_EXPORT Type& type<two::Tile>() { static Type ty("Tile", sizeof(two::Tile)); return ty; }
    template <> TWO_WFC_EXPORT Type& type<two::Tileset>() { static Type ty("Tileset", sizeof(two::Tileset)); return ty; }
    template <> TWO_WFC_EXPORT Type& type<two::Wave>() { static Type ty("Wave", sizeof(two::Wave)); return ty; }
    template <> TWO_WFC_EXPORT Type& type<two::WaveTileset>() { static Type ty("WaveTileset", type<two::Tileset>(), sizeof(two::WaveTileset)); return ty; }
    template <> TWO_WFC_EXPORT Type& type<two::TileWave>() { static Type ty("TileWave", type<two::Wave>(), sizeof(two::TileWave)); return ty; }
}
