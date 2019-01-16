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
    template <> MUD_NOISE_EXPORT Type& type<mud::Noise::CellularDistanceFunction>() { static Type ty("mud::Noise::CellularDistanceFunction", sizeof(mud::Noise::CellularDistanceFunction)); return ty; }
    template <> MUD_NOISE_EXPORT Type& type<mud::Noise::CellularReturnType>() { static Type ty("mud::Noise::CellularReturnType", sizeof(mud::Noise::CellularReturnType)); return ty; }
    template <> MUD_NOISE_EXPORT Type& type<mud::Noise::FractalType>() { static Type ty("mud::Noise::FractalType", sizeof(mud::Noise::FractalType)); return ty; }
    template <> MUD_NOISE_EXPORT Type& type<mud::Noise::Interp>() { static Type ty("mud::Noise::Interp", sizeof(mud::Noise::Interp)); return ty; }
    template <> MUD_NOISE_EXPORT Type& type<mud::Noise::NoiseType>() { static Type ty("mud::Noise::NoiseType", sizeof(mud::Noise::NoiseType)); return ty; }
    
    template <> MUD_NOISE_EXPORT Type& type<mud::Noise>() { static Type ty("Noise", sizeof(mud::Noise)); return ty; }
    template <> MUD_NOISE_EXPORT Type& type<mud::array_3d<float>>() { static Type ty("array_3d<float>", type<vector<float>>(), sizeof(mud::array_3d<float>)); return ty; }
}
