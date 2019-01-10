#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.noise;
#else
#include <noise/Types.h>
#include <noise/Api.h>
#include <type/Vector.h>
#endif

namespace mud
{
    // Exported types
    template <> MUD_NOISE_EXPORT Type& type<mud::Noise::CellularDistanceFunction>() { static Type ty("mud::Noise::CellularDistanceFunction"); return ty; }
    template <> MUD_NOISE_EXPORT Type& type<mud::Noise::CellularReturnType>() { static Type ty("mud::Noise::CellularReturnType"); return ty; }
    template <> MUD_NOISE_EXPORT Type& type<mud::Noise::FractalType>() { static Type ty("mud::Noise::FractalType"); return ty; }
    template <> MUD_NOISE_EXPORT Type& type<mud::Noise::Interp>() { static Type ty("mud::Noise::Interp"); return ty; }
    template <> MUD_NOISE_EXPORT Type& type<mud::Noise::NoiseType>() { static Type ty("mud::Noise::NoiseType"); return ty; }
    
    template <> MUD_NOISE_EXPORT Type& type<mud::Noise>() { static Type ty("Noise"); return ty; }
    template <> MUD_NOISE_EXPORT Type& type<mud::array_3d<float>>() { static Type ty("array_3d<float>", type<std::vector<float>>()); return ty; }
}
