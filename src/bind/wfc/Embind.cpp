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
        .field("index", &mud::Tile::index)
        .field("name", &mud::Tile::name)
        .field("symmetry", &mud::Tile::symmetry)
        .field("cardinality", &mud::Tile::cardinality)
        .field("profile", &mud::Tile::profile)
        ;
    value_object<mud::Tileset>("Tileset")
        .field("name", &mud::Tileset::name)
        .field("tile_size", &mud::Tileset::tile_size)
        .field("tile_scale", &mud::Tileset::tile_scale)
        .field("nutiles", &mud::Tileset::nutiles)
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
