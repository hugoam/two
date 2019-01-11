#include <wfc-gfx/Api.h>
#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(mud_wfc_gfx)
{
    
    // Enums
    
    // Sequences
    
    // Arrays
    
    // Structs
    value_object<mud::TileModel>("TileModel")
        ;
    
    // Classes
    class_<mud::WfcBlock>("WfcBlock")
        .constructor<>()
        .constructor<const mud::vec3&, const mud::uvec3&, const mud::vec3&, mud::WaveTileset&, bool>()
        .property("position", &mud::WfcBlock::m_position)
        .property("size", &mud::WfcBlock::m_size)
        .property("scale", &mud::WfcBlock::m_scale)
        .property("aabb", &mud::WfcBlock::m_aabb)
        .function("reset", &mud::WfcBlock::reset)
        .function("observe", &mud::WfcBlock::observe)
        .function("propagate", &mud::WfcBlock::propagate)
        .function("solve", &mud::WfcBlock::solve)
        .function("update", &mud::WfcBlock::update)
        ;
    
    // Functions
    
}
