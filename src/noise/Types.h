#pragma once

#ifndef TWO_MODULES
#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>
#endif
#include <noise/Forward.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <type/Type.h>
#endif

#ifndef TWO_MODULES
#include <infra/Types.h>
#include <type/Types.h>
#include <math/Types.h>
#include <geom/Types.h>
#endif

#include <noise/Structs.h>

namespace two
{
    // Exported types
    export_ template <> TWO_NOISE_EXPORT Type& type<two::Noise::NoiseType>();
    export_ template <> TWO_NOISE_EXPORT Type& type<two::Noise::Interp>();
    export_ template <> TWO_NOISE_EXPORT Type& type<two::Noise::FractalType>();
    export_ template <> TWO_NOISE_EXPORT Type& type<two::Noise::CellularDistanceFunction>();
    export_ template <> TWO_NOISE_EXPORT Type& type<two::Noise::CellularReturnType>();
    
    export_ template <> TWO_NOISE_EXPORT Type& type<two::vector3d<float>>();
    
    export_ template <> TWO_NOISE_EXPORT Type& type<two::Noise>();
}
