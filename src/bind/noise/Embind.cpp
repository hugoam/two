#include <noise/Api.h>
#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(mud_noise)
{
    
    // Enums
    enum_<mud::Noise::CellularDistanceFunction>("mud::Noise::CellularDistanceFunction")
        .value("Euclidean", mud::Noise::Euclidean)
        .value("Manhattan", mud::Noise::Manhattan)
        .value("Natural", mud::Noise::Natural)
        ;
    enum_<mud::Noise::CellularReturnType>("mud::Noise::CellularReturnType")
        .value("CellValue", mud::Noise::CellValue)
        .value("NoiseLookup", mud::Noise::NoiseLookup)
        .value("Distance", mud::Noise::Distance)
        .value("Distance2", mud::Noise::Distance2)
        .value("Distance2Add", mud::Noise::Distance2Add)
        .value("Distance2Sub", mud::Noise::Distance2Sub)
        .value("Distance2Mul", mud::Noise::Distance2Mul)
        .value("Distance2Div", mud::Noise::Distance2Div)
        ;
    enum_<mud::Noise::FractalType>("mud::Noise::FractalType")
        .value("FBM", mud::Noise::FBM)
        .value("Billow", mud::Noise::Billow)
        .value("RigidMulti", mud::Noise::RigidMulti)
        ;
    enum_<mud::Noise::Interp>("mud::Noise::Interp")
        .value("Linear", mud::Noise::Linear)
        .value("Hermite", mud::Noise::Hermite)
        .value("Quintic", mud::Noise::Quintic)
        ;
    enum_<mud::Noise::NoiseType>("mud::Noise::NoiseType")
        .value("Value", mud::Noise::Value)
        .value("ValueFractal", mud::Noise::ValueFractal)
        .value("Perlin", mud::Noise::Perlin)
        .value("PerlinFractal", mud::Noise::PerlinFractal)
        .value("Simplex", mud::Noise::Simplex)
        .value("SimplexFractal", mud::Noise::SimplexFractal)
        .value("Cellular", mud::Noise::Cellular)
        .value("WhiteNoise", mud::Noise::WhiteNoise)
        .value("Cubic", mud::Noise::Cubic)
        .value("CubicFractal", mud::Noise::CubicFractal)
        ;
    
    // Sequences
    
    // Arrays
    
    // Structs
    value_object<mud::array_3d<float>>("array_3d<float>")
        ;
    
    // Classes
    class_<mud::Noise>("Noise")
        ;
    
    // Functions
    function("noise_2d", &mud::noise_2d);
    function("noise_3d", &mud::noise_3d);
    function("noise_fract_2d", &mud::noise_fract_2d);
    function("noise_fract_3d", &mud::noise_fract_3d);
    function("noise_field_2d", &mud::noise_field_2d);
    function("noise_field_3d", &mud::noise_field_3d);
    
}
