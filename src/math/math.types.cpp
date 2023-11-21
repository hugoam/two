module;
#include <infra/Cpp20.h>
module two.math;

namespace two
{
    // Exported types
    template <> TWO_MATH_EXPORT Type& type<two::Axis>() { static Type ty("Axis", sizeof(two::Axis)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::Axes>() { static Type ty("Axes", sizeof(two::Axes)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::SignedAxis>() { static Type ty("SignedAxis", sizeof(two::SignedAxis)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::Side>() { static Type ty("Side", sizeof(two::Side)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::Clockwise>() { static Type ty("Clockwise", sizeof(two::Clockwise)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::TrackMode>() { static Type ty("TrackMode", sizeof(two::TrackMode)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::Spectrum>() { static Type ty("Spectrum", sizeof(two::Spectrum)); return ty; }
    
    template <> TWO_MATH_EXPORT Type& type<stl::span<uint8_t>>() { static Type ty("span<uint8_t>", sizeof(stl::span<uint8_t>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<stl::span<int>>() { static Type ty("span<int>", sizeof(stl::span<int>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<stl::span<float>>() { static Type ty("span<float>", sizeof(stl::span<float>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<stl::span<uint32_t>>() { static Type ty("span<uint32_t>", sizeof(stl::span<uint32_t>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<stl::span<two::vec3>>() { static Type ty("span<two::vec3>", sizeof(stl::span<two::vec3>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<stl::span<two::quat>>() { static Type ty("span<two::quat>", sizeof(stl::span<two::quat>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<stl::span<two::Colour>>() { static Type ty("span<two::Colour>", sizeof(stl::span<two::Colour>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<stl::span<two::uvec3>>() { static Type ty("span<two::uvec3>", sizeof(stl::span<two::uvec3>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<stl::vector<int>>() { static Type ty("vector<int>", sizeof(stl::vector<int>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<stl::vector<float>>() { static Type ty("vector<float>", sizeof(stl::vector<float>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<stl::vector<uint32_t>>() { static Type ty("vector<uint32_t>", sizeof(stl::vector<uint32_t>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<stl::vector<two::vec3>>() { static Type ty("vector<two::vec3>", sizeof(stl::vector<two::vec3>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<stl::vector<two::quat>>() { static Type ty("vector<two::quat>", sizeof(stl::vector<two::quat>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<stl::vector<two::Colour>>() { static Type ty("vector<two::Colour>", sizeof(stl::vector<two::Colour>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<stl::vector<two::uvec3>>() { static Type ty("vector<two::uvec3>", sizeof(stl::vector<two::uvec3>)); return ty; }
    
    template <> TWO_MATH_EXPORT Type& type<two::v2<float>>() { static Type ty("v2<float>", sizeof(two::v2<float>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::v3<float>>() { static Type ty("v3<float>", sizeof(two::v3<float>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::v4<float>>() { static Type ty("v4<float>", sizeof(two::v4<float>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::v2<int>>() { static Type ty("v2<int>", sizeof(two::v2<int>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::v3<int>>() { static Type ty("v3<int>", sizeof(two::v3<int>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::v4<int>>() { static Type ty("v4<int>", sizeof(two::v4<int>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::v2<uint>>() { static Type ty("v2<uint>", sizeof(two::v2<uint>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::v3<uint>>() { static Type ty("v3<uint>", sizeof(two::v3<uint>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::v4<uint>>() { static Type ty("v4<uint>", sizeof(two::v4<uint>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::v2<bool>>() { static Type ty("v2<bool>", sizeof(two::v2<bool>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::v3<bool>>() { static Type ty("v3<bool>", sizeof(two::v3<bool>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::v4<bool>>() { static Type ty("v4<bool>", sizeof(two::v4<bool>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::mat3>() { static Type ty("mat3", sizeof(two::mat3)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::mat4>() { static Type ty("mat4", sizeof(two::mat4)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::quat>() { static Type ty("quat", type<two::v4<float>>(), sizeof(two::quat)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::Transform>() { static Type ty("Transform", sizeof(two::Transform)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::ColourHSL>() { static Type ty("ColourHSL", sizeof(two::ColourHSL)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::Colour>() { static Type ty("Colour", sizeof(two::Colour)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::ValueCurve<float>>() { static Type ty("ValueCurve<float>", sizeof(two::ValueCurve<float>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::ValueCurve<uint32_t>>() { static Type ty("ValueCurve<uint32_t>", sizeof(two::ValueCurve<uint32_t>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::ValueCurve<two::vec3>>() { static Type ty("ValueCurve<two::vec3>", sizeof(two::ValueCurve<two::vec3>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::ValueCurve<two::quat>>() { static Type ty("ValueCurve<two::quat>", sizeof(two::ValueCurve<two::quat>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::ValueCurve<two::Colour>>() { static Type ty("ValueCurve<two::Colour>", sizeof(two::ValueCurve<two::Colour>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::ValueTrack<two::vec3>>() { static Type ty("ValueTrack<two::vec3>", sizeof(two::ValueTrack<two::vec3>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::ValueTrack<two::quat>>() { static Type ty("ValueTrack<two::quat>", sizeof(two::ValueTrack<two::quat>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::ValueTrack<float>>() { static Type ty("ValueTrack<float>", sizeof(two::ValueTrack<float>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::ValueTrack<uint32_t>>() { static Type ty("ValueTrack<uint32_t>", sizeof(two::ValueTrack<uint32_t>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::ValueTrack<two::Colour>>() { static Type ty("ValueTrack<two::Colour>", sizeof(two::ValueTrack<two::Colour>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::Image>() { static Type ty("Image", sizeof(two::Image)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::Palette>() { static Type ty("Palette", sizeof(two::Palette)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::Image256>() { static Type ty("Image256", sizeof(two::Image256)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::ImageAtlas>() { static Type ty("ImageAtlas", sizeof(two::ImageAtlas)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::TextureAtlas>() { static Type ty("TextureAtlas", type<two::ImageAtlas>(), sizeof(two::TextureAtlas)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::Sprite>() { static Type ty("Sprite", type<two::Image>(), sizeof(two::Sprite)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::SpriteAtlas>() { static Type ty("SpriteAtlas", type<two::ImageAtlas>(), sizeof(two::SpriteAtlas)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::Range<two::vec3>>() { static Type ty("Range<two::vec3>", sizeof(two::Range<two::vec3>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::Range<two::quat>>() { static Type ty("Range<two::quat>", sizeof(two::Range<two::quat>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::Range<float>>() { static Type ty("Range<float>", sizeof(two::Range<float>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::Range<uint32_t>>() { static Type ty("Range<uint32_t>", sizeof(two::Range<uint32_t>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::Range<two::Colour>>() { static Type ty("Range<two::Colour>", sizeof(two::Range<two::Colour>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::StatDef<int>>() { static Type ty("StatDef<int>", sizeof(two::StatDef<int>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::StatDef<float>>() { static Type ty("StatDef<float>", sizeof(two::StatDef<float>)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::Time>() { static Type ty("Time", sizeof(two::Time)); return ty; }
    template <> TWO_MATH_EXPORT Type& type<two::TimeSpan>() { static Type ty("TimeSpan", sizeof(two::TimeSpan)); return ty; }
}
