

#include <math/Generated/Types.h>
#include <math/Generated/Module.h>
#include <obj/Proto.h>

namespace mud
{
    // Exported types
    template <> MUD_MATH_EXPORT Type& type<mud::Axis>() { static Type ty("mud::Axis"); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Clockwise>() { static Type ty("mud::Clockwise"); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Side>() { static Type ty("mud::Side"); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::SignedAxis>() { static Type ty("mud::SignedAxis"); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::SpectrumPalette>() { static Type ty("mud::SpectrumPalette"); return ty; }
    template <> MUD_MATH_EXPORT Type& type<std::vector<mud::Colour>>() { static Type ty("std::vector<mud::Colour>"); return ty; }
    template <> MUD_MATH_EXPORT Type& type<std::vector<mud::uvec3>>() { static Type ty("std::vector<mud::uvec3>"); return ty; }
    template <> MUD_MATH_EXPORT Type& type<std::vector<uint32_t>>() { static Type ty("std::vector<uint32_t>"); return ty; }
    
    template <> MUD_MATH_EXPORT Type& type<mud::AutoStat<float>>() { static Type ty("AutoStat<float>"); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::AutoStat<int>>() { static Type ty("AutoStat<int>"); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Colour>() { static Type ty("Colour"); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Gauge>() { static Type ty("Gauge"); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Image256>() { static Type ty("Image256"); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Palette>() { static Type ty("Palette"); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Range<float>>() { static Type ty("Range<float>"); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Range<mud::Colour>>() { static Type ty("Range<mud::Colour>"); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Range<mud::quat>>() { static Type ty("Range<mud::quat>"); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Range<mud::vec3>>() { static Type ty("Range<mud::vec3>"); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Range<uint32_t>>() { static Type ty("Range<uint32_t>"); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Ratio>() { static Type ty("Ratio"); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::ivec3>() { static Type ty("ivec3"); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::mat4>() { static Type ty("mat4"); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::quat>() { static Type ty("quat"); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::uvec2>() { static Type ty("uvec2"); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::uvec3>() { static Type ty("uvec3"); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::uvec4>() { static Type ty("uvec4"); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::vec2>() { static Type ty("vec2"); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::vec3>() { static Type ty("vec3"); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::vec4>() { static Type ty("vec4"); return ty; }
}
