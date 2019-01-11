#include <wfc/Api.h>
#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(mud_wfc)
{
    
    // Enums
    enum_<mud::Result>("mud::Result")
        .value("kSuccess", mud::kSuccess)
        .value("kFail", mud::kFail)
        .value("kUnfinished", mud::kUnfinished)
        ;
    
    // Sequences
    
    // Arrays
    
    // Structs
    value_object<mud::Tile>("Tile")
        .field("index", &mud::Tile::m_index)
        .field("name", &mud::Tile::m_name)
        .field("symmetry", &mud::Tile::m_symmetry)
        .field("cardinality", &mud::Tile::m_cardinality)
        .field("profile", &mud::Tile::m_profile)
        ;
    value_object<mud::Tileset>("Tileset")
        .field("name", &mud::Tileset::m_name)
        .field("tile_size", &mud::Tileset::m_tile_size)
        .field("tile_scale", &mud::Tileset::m_tile_scale)
        .field("nutiles", &mud::Tileset::m_num_tiles)
        ;
    value_object<mud::Wave>("Wave")
        ;
    value_object<mud::TileWave>("TileWave")
        ;
    value_object<mud::WaveTileset>("WaveTileset")
        ;
    
    // Classes
    
    // Functions
    function("parse_json_tileset", &mud::parse_json_tileset);
    function("parse_json_wave_tileset", &mud::parse_json_wave_tileset);
    
}
