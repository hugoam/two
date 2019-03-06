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
    template <> MUD_NOISE_EXPORT Type& type<mud::Noise::CellularDistanceFunction>() { static Type ty("CellularDistanceFunction", sizeof(mud::Noise::CellularDistanceFunction)); return ty; }
    template <> MUD_NOISE_EXPORT Type& type<mud::Noise::CellularReturnType>() { static Type ty("CellularReturnType", sizeof(mud::Noise::CellularReturnType)); return ty; }
    template <> MUD_NOISE_EXPORT Type& type<mud::Noise::FractalType>() { static Type ty("FractalType", sizeof(mud::Noise::FractalType)); return ty; }
    template <> MUD_NOISE_EXPORT Type& type<mud::Noise::Interp>() { static Type ty("Interp", sizeof(mud::Noise::Interp)); return ty; }
    template <> MUD_NOISE_EXPORT Type& type<mud::Noise::NoiseType>() { static Type ty("NoiseType", sizeof(mud::Noise::NoiseType)); return ty; }
    
    template <> MUD_NOISE_EXPORT Type& type<mud::vector3d<float>>() { static Type ty("vector3d<float>", sizeof(mud::vector3d<float>)); return ty; }
    
    template <> MUD_NOISE_EXPORT Type& type<mud::Noise>() { static Type ty("Noise", sizeof(mud::Noise)); return ty; }
}
