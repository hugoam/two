module;
#include <infra/Cpp20.h>
module two.noise;

namespace two
{
    // Exported types
    template <> TWO_NOISE_EXPORT Type& type<two::Noise::NoiseType>() { static Type ty("NoiseType", sizeof(two::Noise::NoiseType)); return ty; }
    template <> TWO_NOISE_EXPORT Type& type<two::Noise::Interp>() { static Type ty("Interp", sizeof(two::Noise::Interp)); return ty; }
    template <> TWO_NOISE_EXPORT Type& type<two::Noise::FractalType>() { static Type ty("FractalType", sizeof(two::Noise::FractalType)); return ty; }
    template <> TWO_NOISE_EXPORT Type& type<two::Noise::CellularDistanceFunction>() { static Type ty("CellularDistanceFunction", sizeof(two::Noise::CellularDistanceFunction)); return ty; }
    template <> TWO_NOISE_EXPORT Type& type<two::Noise::CellularReturnType>() { static Type ty("CellularReturnType", sizeof(two::Noise::CellularReturnType)); return ty; }
    
    template <> TWO_NOISE_EXPORT Type& type<two::vector3d<float>>() { static Type ty("vector3d<float>", sizeof(two::vector3d<float>)); return ty; }
    
    template <> TWO_NOISE_EXPORT Type& type<two::Noise>() { static Type ty("Noise", sizeof(two::Noise)); return ty; }
}
