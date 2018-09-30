

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.procgen;
#else
#include <procgen/Types.h>
#include <procgen/Api.h>
#include <obj/Vector.h>
//#include <ecs/Proto.h>
#endif

namespace mud
{
    // Exported types
    template <> MUD_PROCGEN_EXPORT Type& type<mud::Noise::CellularDistanceFunction>() { static Type ty("mud::Noise::CellularDistanceFunction"); return ty; }
    template <> MUD_PROCGEN_EXPORT Type& type<mud::Noise::CellularReturnType>() { static Type ty("mud::Noise::CellularReturnType"); return ty; }
    template <> MUD_PROCGEN_EXPORT Type& type<mud::Noise::FractalType>() { static Type ty("mud::Noise::FractalType"); return ty; }
    template <> MUD_PROCGEN_EXPORT Type& type<mud::Noise::Interp>() { static Type ty("mud::Noise::Interp"); return ty; }
    template <> MUD_PROCGEN_EXPORT Type& type<mud::Noise::NoiseType>() { static Type ty("mud::Noise::NoiseType"); return ty; }
    template <> MUD_PROCGEN_EXPORT Type& type<mud::PatternSampling>() { static Type ty("mud::PatternSampling"); return ty; }
    template <> MUD_PROCGEN_EXPORT Type& type<mud::Result>() { static Type ty("mud::Result"); return ty; }
    
    template <> MUD_PROCGEN_EXPORT Type& type<mud::Circlifier>() { static Type ty("Circlifier"); return ty; }
    template <> MUD_PROCGEN_EXPORT Type& type<mud::Fract>() { static Type ty("Fract"); return ty; }
    template <> MUD_PROCGEN_EXPORT Type& type<mud::FractSample>() { static Type ty("FractSample"); return ty; }
    template <> MUD_PROCGEN_EXPORT Type& type<mud::FractTab>() { static Type ty("FractTab"); return ty; }
    template <> MUD_PROCGEN_EXPORT Type& type<mud::Noise>() { static Type ty("Noise"); return ty; }
    template <> MUD_PROCGEN_EXPORT Type& type<mud::Pattern>() { static Type ty("Pattern"); return ty; }
    template <> MUD_PROCGEN_EXPORT Type& type<mud::Tile>() { static Type ty("Tile"); return ty; }
    template <> MUD_PROCGEN_EXPORT Type& type<mud::Tileset>() { static Type ty("Tileset"); return ty; }
    template <> MUD_PROCGEN_EXPORT Type& type<mud::Wave>() { static Type ty("Wave"); return ty; }
    template <> MUD_PROCGEN_EXPORT Type& type<mud::TileWave>() { static Type ty("TileWave", type<mud::Wave>()); return ty; }
    template <> MUD_PROCGEN_EXPORT Type& type<mud::WaveTileset>() { static Type ty("WaveTileset", type<mud::Tileset>()); return ty; }
    template <> MUD_PROCGEN_EXPORT Type& type<mud::array_3d<float>>() { static Type ty("array_3d<float>", type<std::vector<float>>()); return ty; }
}
