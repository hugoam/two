#pragma once

#include <math/Generated/Forward.h>

#include <obj/Generated/Types.h>

#include <obj/Type.h>
#include <obj/Proto.h>

#include <string>
#include <vector>
#include <stdint.h>

#include <math/Structs.h>

namespace mud
{
    // Exported types
    template <> MUD_MATH_EXPORT Type& type<mud::Axes>();
    template <> MUD_MATH_EXPORT Type& type<mud::Axis>();
    template <> MUD_MATH_EXPORT Type& type<mud::Clockwise>();
    template <> MUD_MATH_EXPORT Type& type<mud::Side>();
    template <> MUD_MATH_EXPORT Type& type<mud::SignedAxis>();
    template <> MUD_MATH_EXPORT Type& type<mud::SpectrumPalette>();
    template <> MUD_MATH_EXPORT Type& type<mud::TrackMode>();
    template <> MUD_MATH_EXPORT Type& type<std::vector<float>>();
    //template <> MUD_MATH_EXPORT Type& type<std::vector<mud::Colour>>();
    template <> MUD_MATH_EXPORT Type& type<std::vector<mud::Colour>>();
    template <> MUD_MATH_EXPORT Type& type<std::vector<mud::quat>>();
    template <> MUD_MATH_EXPORT Type& type<std::vector<mud::uvec3>>();
    template <> MUD_MATH_EXPORT Type& type<std::vector<mud::vec3>>();
    template <> MUD_MATH_EXPORT Type& type<std::vector<uint32_t>>();
    
    template <> MUD_MATH_EXPORT Type& type<mud::AutoStat<float>>();
    template <> MUD_MATH_EXPORT Type& type<mud::AutoStat<int>>();
    template <> MUD_MATH_EXPORT Type& type<mud::Colour>();
    template <> MUD_MATH_EXPORT Type& type<mud::Gauge>();
    template <> MUD_MATH_EXPORT Type& type<mud::Image256>();
    template <> MUD_MATH_EXPORT Type& type<mud::Palette>();
    template <> MUD_MATH_EXPORT Type& type<mud::Range<float>>();
    template <> MUD_MATH_EXPORT Type& type<mud::Range<mud::Colour>>();
    template <> MUD_MATH_EXPORT Type& type<mud::Range<mud::quat>>();
    template <> MUD_MATH_EXPORT Type& type<mud::Range<mud::vec3>>();
    template <> MUD_MATH_EXPORT Type& type<mud::Range<uint32_t>>();
    template <> MUD_MATH_EXPORT Type& type<mud::Ratio>();
    template <> MUD_MATH_EXPORT Type& type<mud::ValueCurve<float>>();
    template <> MUD_MATH_EXPORT Type& type<mud::ValueCurve<mud::Colour>>();
    template <> MUD_MATH_EXPORT Type& type<mud::ValueCurve<mud::quat>>();
    template <> MUD_MATH_EXPORT Type& type<mud::ValueCurve<mud::vec3>>();
    template <> MUD_MATH_EXPORT Type& type<mud::ValueCurve<uint32_t>>();
    template <> MUD_MATH_EXPORT Type& type<mud::ValueTrack<float>>();
    template <> MUD_MATH_EXPORT Type& type<mud::ValueTrack<mud::Colour>>();
    template <> MUD_MATH_EXPORT Type& type<mud::ValueTrack<mud::quat>>();
    template <> MUD_MATH_EXPORT Type& type<mud::ValueTrack<mud::vec3>>();
    template <> MUD_MATH_EXPORT Type& type<mud::ValueTrack<uint32_t>>();
    template <> MUD_MATH_EXPORT Type& type<mud::ivec3>();
    template <> MUD_MATH_EXPORT Type& type<mud::mat4>();
    template <> MUD_MATH_EXPORT Type& type<mud::quat>();
    template <> MUD_MATH_EXPORT Type& type<mud::uvec2>();
    template <> MUD_MATH_EXPORT Type& type<mud::uvec3>();
    template <> MUD_MATH_EXPORT Type& type<mud::uvec4>();
    template <> MUD_MATH_EXPORT Type& type<mud::vec2>();
    template <> MUD_MATH_EXPORT Type& type<mud::vec3>();
    template <> MUD_MATH_EXPORT Type& type<mud::vec4>();
}
