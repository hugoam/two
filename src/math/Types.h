#pragma once

#include <math/Forward.h>

#if defined TWO_TYPE_LIB
#include <type/Type.h>
#endif

#include <math/Structs.h>

namespace two
{
    // Exported types
    template <> TWO_MATH_EXPORT Type& type<two::Axis>();
    template <> TWO_MATH_EXPORT Type& type<two::Axes>();
    template <> TWO_MATH_EXPORT Type& type<two::SignedAxis>();
    template <> TWO_MATH_EXPORT Type& type<two::Side>();
    template <> TWO_MATH_EXPORT Type& type<two::Clockwise>();
    template <> TWO_MATH_EXPORT Type& type<two::TrackMode>();
    template <> TWO_MATH_EXPORT Type& type<two::Spectrum>();
    
    template <> TWO_MATH_EXPORT Type& type<stl::span<uint8_t>>();
    template <> TWO_MATH_EXPORT Type& type<stl::span<int>>();
    template <> TWO_MATH_EXPORT Type& type<stl::span<float>>();
    template <> TWO_MATH_EXPORT Type& type<stl::span<uint32_t>>();
    template <> TWO_MATH_EXPORT Type& type<stl::span<two::vec3>>();
    template <> TWO_MATH_EXPORT Type& type<stl::span<two::quat>>();
    template <> TWO_MATH_EXPORT Type& type<stl::span<two::Colour>>();
    template <> TWO_MATH_EXPORT Type& type<stl::span<two::uvec3>>();
    template <> TWO_MATH_EXPORT Type& type<stl::vector<int>>();
    template <> TWO_MATH_EXPORT Type& type<stl::vector<float>>();
    template <> TWO_MATH_EXPORT Type& type<stl::vector<uint32_t>>();
    template <> TWO_MATH_EXPORT Type& type<stl::vector<two::vec3>>();
    template <> TWO_MATH_EXPORT Type& type<stl::vector<two::quat>>();
    template <> TWO_MATH_EXPORT Type& type<stl::vector<two::Colour>>();
    template <> TWO_MATH_EXPORT Type& type<stl::vector<two::uvec3>>();
    
    template <> TWO_MATH_EXPORT Type& type<two::v2<float>>();
    template <> TWO_MATH_EXPORT Type& type<two::v3<float>>();
    template <> TWO_MATH_EXPORT Type& type<two::v4<float>>();
    template <> TWO_MATH_EXPORT Type& type<two::v2<int>>();
    template <> TWO_MATH_EXPORT Type& type<two::v3<int>>();
    template <> TWO_MATH_EXPORT Type& type<two::v4<int>>();
    template <> TWO_MATH_EXPORT Type& type<two::v2<uint>>();
    template <> TWO_MATH_EXPORT Type& type<two::v3<uint>>();
    template <> TWO_MATH_EXPORT Type& type<two::v4<uint>>();
    template <> TWO_MATH_EXPORT Type& type<two::v2<bool>>();
    template <> TWO_MATH_EXPORT Type& type<two::v3<bool>>();
    template <> TWO_MATH_EXPORT Type& type<two::v4<bool>>();
    template <> TWO_MATH_EXPORT Type& type<two::mat3>();
    template <> TWO_MATH_EXPORT Type& type<two::mat4>();
    template <> TWO_MATH_EXPORT Type& type<two::quat>();
    template <> TWO_MATH_EXPORT Type& type<two::Transform>();
    template <> TWO_MATH_EXPORT Type& type<two::ColourHSL>();
    template <> TWO_MATH_EXPORT Type& type<two::Colour>();
    template <> TWO_MATH_EXPORT Type& type<two::ValueCurve<float>>();
    template <> TWO_MATH_EXPORT Type& type<two::ValueCurve<uint32_t>>();
    template <> TWO_MATH_EXPORT Type& type<two::ValueCurve<two::vec3>>();
    template <> TWO_MATH_EXPORT Type& type<two::ValueCurve<two::quat>>();
    template <> TWO_MATH_EXPORT Type& type<two::ValueCurve<two::Colour>>();
    template <> TWO_MATH_EXPORT Type& type<two::ValueTrack<two::vec3>>();
    template <> TWO_MATH_EXPORT Type& type<two::ValueTrack<two::quat>>();
    template <> TWO_MATH_EXPORT Type& type<two::ValueTrack<float>>();
    template <> TWO_MATH_EXPORT Type& type<two::ValueTrack<uint32_t>>();
    template <> TWO_MATH_EXPORT Type& type<two::ValueTrack<two::Colour>>();
    template <> TWO_MATH_EXPORT Type& type<two::Image>();
    template <> TWO_MATH_EXPORT Type& type<two::Palette>();
    template <> TWO_MATH_EXPORT Type& type<two::Image256>();
    template <> TWO_MATH_EXPORT Type& type<two::ImageAtlas>();
    template <> TWO_MATH_EXPORT Type& type<two::TextureAtlas>();
    template <> TWO_MATH_EXPORT Type& type<two::Sprite>();
    template <> TWO_MATH_EXPORT Type& type<two::SpriteAtlas>();
    template <> TWO_MATH_EXPORT Type& type<two::Range<two::vec3>>();
    template <> TWO_MATH_EXPORT Type& type<two::Range<two::quat>>();
    template <> TWO_MATH_EXPORT Type& type<two::Range<float>>();
    template <> TWO_MATH_EXPORT Type& type<two::Range<uint32_t>>();
    template <> TWO_MATH_EXPORT Type& type<two::Range<two::Colour>>();
    template <> TWO_MATH_EXPORT Type& type<two::StatDef<int>>();
    template <> TWO_MATH_EXPORT Type& type<two::StatDef<float>>();
    template <> TWO_MATH_EXPORT Type& type<two::Time>();
    template <> TWO_MATH_EXPORT Type& type<two::TimeSpan>();
}
