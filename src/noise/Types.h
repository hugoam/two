#pragma once

#include <noise/Forward.h>

#if defined TWO_TYPE_LIB
#include <type/Type.h>
#endif

#include <noise/Structs.h>

namespace two
{
    // Exported types
    template <> TWO_NOISE_EXPORT Type& type<two::Noise::NoiseType>();
    template <> TWO_NOISE_EXPORT Type& type<two::Noise::Interp>();
    template <> TWO_NOISE_EXPORT Type& type<two::Noise::FractalType>();
    template <> TWO_NOISE_EXPORT Type& type<two::Noise::CellularDistanceFunction>();
    template <> TWO_NOISE_EXPORT Type& type<two::Noise::CellularReturnType>();
    
    template <> TWO_NOISE_EXPORT Type& type<two::vector3d<float>>();
    
    template <> TWO_NOISE_EXPORT Type& type<two::Noise>();
}
