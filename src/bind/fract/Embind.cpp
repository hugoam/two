#include <fract/Api.h>
#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(mud_fract)
{
    
    // Enums
    enum_<mud::PatternSampling>("mud::PatternSampling")
        .value("X", mud::PatternSampling::X)
        .value("XY", mud::PatternSampling::XY)
        .value("Depth", mud::PatternSampling::Depth)
        ;
    
    // Sequences
    
    // Arrays
    
    // Structs
    value_object<mud::Circlifier>("Circlifier")
        ;
    value_object<mud::FractTab>("FractTab")
        ;
    value_object<mud::Pattern>("Pattern")
        ;
    
    // Classes
    class_<mud::Fract>("Fract")
        .constructor<size_t>()
        .property("nutabs", &mud::Fract::nutabs)
        .function("generate", &mud::Fract::generate)
        .function("regen", &mud::Fract::regen)
        .function("render", &mud::Fract::render)
        .function("render_whole", &mud::Fract::render_whole)
        .function("render_grid", &mud::Fract::render_grid)
        ;
    class_<mud::FractSample>("FractSample")
        .constructor<mud::Fract&, const mud::Rect&, mud::uvec2>()
        .property("fract", &mud::FractSample::fract)
        .property("rect", &mud::FractSample::rect)
        .property("resolution", &mud::FractSample::resolution)
        .function("render", &mud::FractSample::render)
        ;
    
    // Functions
    function("generate_fract", &mud::generate_fract);
    
}
