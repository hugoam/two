#pragma once

#ifndef TWO_MODULES
#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>
#endif
#include <math/Forward.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <type/Type.h>
#endif

#ifndef TWO_MODULES
#include <infra/Types.h>
#include <type/Types.h>
#endif

#include <math/Structs.h>

namespace two
{
    // Exported types
    export_ template <> TWO_MATH_EXPORT Type& type<two::Axis>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::Axes>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::SignedAxis>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::Side>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::Clockwise>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::TrackMode>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::Spectrum>();
    
    export_ template <> TWO_MATH_EXPORT Type& type<stl::span<uint8_t>>();
    export_ template <> TWO_MATH_EXPORT Type& type<stl::span<int>>();
    export_ template <> TWO_MATH_EXPORT Type& type<stl::span<float>>();
    export_ template <> TWO_MATH_EXPORT Type& type<stl::span<uint32_t>>();
    export_ template <> TWO_MATH_EXPORT Type& type<stl::span<two::vec3>>();
    export_ template <> TWO_MATH_EXPORT Type& type<stl::span<two::quat>>();
    export_ template <> TWO_MATH_EXPORT Type& type<stl::span<two::Colour>>();
    export_ template <> TWO_MATH_EXPORT Type& type<stl::span<two::uvec3>>();
    export_ template <> TWO_MATH_EXPORT Type& type<stl::vector<int>>();
    export_ template <> TWO_MATH_EXPORT Type& type<stl::vector<float>>();
    export_ template <> TWO_MATH_EXPORT Type& type<stl::vector<uint32_t>>();
    export_ template <> TWO_MATH_EXPORT Type& type<stl::vector<two::vec3>>();
    export_ template <> TWO_MATH_EXPORT Type& type<stl::vector<two::quat>>();
    export_ template <> TWO_MATH_EXPORT Type& type<stl::vector<two::Colour>>();
    export_ template <> TWO_MATH_EXPORT Type& type<stl::vector<two::uvec3>>();
    
    export_ template <> TWO_MATH_EXPORT Type& type<two::v2<float>>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::v3<float>>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::v4<float>>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::v2<int>>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::v3<int>>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::v4<int>>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::v2<uint>>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::v3<uint>>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::v4<uint>>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::v2<bool>>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::v3<bool>>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::v4<bool>>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::mat3>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::mat4>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::quat>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::Transform>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::ColourHSL>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::Colour>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::ValueCurve<float>>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::ValueCurve<uint32_t>>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::ValueCurve<two::vec3>>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::ValueCurve<two::quat>>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::ValueCurve<two::Colour>>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::ValueTrack<two::vec3>>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::ValueTrack<two::quat>>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::ValueTrack<float>>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::ValueTrack<uint32_t>>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::ValueTrack<two::Colour>>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::Image>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::Palette>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::Image256>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::ImageAtlas>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::TextureAtlas>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::Sprite>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::SpriteAtlas>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::Range<two::vec3>>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::Range<two::quat>>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::Range<float>>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::Range<uint32_t>>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::Range<two::Colour>>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::StatDef<int>>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::StatDef<float>>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::Time>();
    export_ template <> TWO_MATH_EXPORT Type& type<two::TimeSpan>();
}
