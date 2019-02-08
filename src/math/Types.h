#pragma once

#include <math/Forward.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <type/Type.h>
#endif

#ifndef MUD_MODULES
#include <infra/Types.h>
#include <type/Types.h>
#endif

#ifndef MUD_CPP_20
#include <stl/string.h>
#include <stl/vector.h>
#include <stdint.h>
#endif

#include <math/Structs.h>

namespace mud
{
    // Exported types
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Axes>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Axis>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Clockwise>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Side>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::SignedAxis>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Spectrum>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::TrackMode>();
    
    export_ template <> MUD_MATH_EXPORT Type& type<stl::vector<float>>();
    export_ template <> MUD_MATH_EXPORT Type& type<stl::vector<int>>();
    export_ template <> MUD_MATH_EXPORT Type& type<stl::vector<mud::Colour>>();
    export_ template <> MUD_MATH_EXPORT Type& type<stl::vector<mud::quat>>();
    export_ template <> MUD_MATH_EXPORT Type& type<stl::vector<mud::uvec3>>();
    export_ template <> MUD_MATH_EXPORT Type& type<stl::vector<mud::vec3>>();
    export_ template <> MUD_MATH_EXPORT Type& type<stl::vector<uint32_t>>();
    
    export_ template <> MUD_MATH_EXPORT Type& type<mud::AutoStat<float>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::AutoStat<int>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Colour>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Image>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Image256>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::ImageAtlas>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Palette>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Range<float>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Range<mud::Colour>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Range<mud::quat>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Range<mud::vec3>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Range<uint32_t>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Time>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::TimeSpan>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Transform>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::ValueCurve<float>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::ValueCurve<mud::Colour>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::ValueCurve<mud::quat>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::ValueCurve<mud::vec3>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::ValueCurve<uint32_t>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::ValueTrack<float>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::ValueTrack<mud::Colour>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::ValueTrack<mud::quat>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::ValueTrack<mud::vec3>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::ValueTrack<uint32_t>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::mat3>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::mat4>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::v2<bool>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::v2<float>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::v2<int>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::v2<stl::uint>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::v3<bool>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::v3<float>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::v3<int>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::v3<stl::uint>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::v4<bool>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::v4<float>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::v4<int>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::v4<stl::uint>>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::Sprite>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::SpriteAtlas>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::TextureAtlas>();
    export_ template <> MUD_MATH_EXPORT Type& type<mud::quat>();
}
