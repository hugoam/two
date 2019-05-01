#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.math;
#else
#include <math/Types.h>
#include <math/Api.h>
#include <type/Vector.h>
#endif

namespace mud
{
    // Exported types
    template <> MUD_MATH_EXPORT Type& type<mud::Axes>() { static Type ty("Axes", sizeof(mud::Axes)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Axis>() { static Type ty("Axis", sizeof(mud::Axis)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Clockwise>() { static Type ty("Clockwise", sizeof(mud::Clockwise)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Side>() { static Type ty("Side", sizeof(mud::Side)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::SignedAxis>() { static Type ty("SignedAxis", sizeof(mud::SignedAxis)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Spectrum>() { static Type ty("Spectrum", sizeof(mud::Spectrum)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::TrackMode>() { static Type ty("TrackMode", sizeof(mud::TrackMode)); return ty; }
    
    template <> MUD_MATH_EXPORT Type& type<stl::span<float>>() { static Type ty("span<float>", sizeof(stl::span<float>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<stl::span<int>>() { static Type ty("span<int>", sizeof(stl::span<int>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<stl::span<mud::Colour>>() { static Type ty("span<mud::Colour>", sizeof(stl::span<mud::Colour>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<stl::span<mud::quat>>() { static Type ty("span<mud::quat>", sizeof(stl::span<mud::quat>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<stl::span<mud::uvec3>>() { static Type ty("span<mud::uvec3>", sizeof(stl::span<mud::uvec3>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<stl::span<mud::vec3>>() { static Type ty("span<mud::vec3>", sizeof(stl::span<mud::vec3>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<stl::span<uint32_t>>() { static Type ty("span<uint32_t>", sizeof(stl::span<uint32_t>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<stl::span<uint8_t>>() { static Type ty("span<uint8_t>", sizeof(stl::span<uint8_t>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<stl::vector<float>>() { static Type ty("vector<float>", sizeof(stl::vector<float>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<stl::vector<int>>() { static Type ty("vector<int>", sizeof(stl::vector<int>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<stl::vector<mud::Colour>>() { static Type ty("vector<mud::Colour>", sizeof(stl::vector<mud::Colour>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<stl::vector<mud::quat>>() { static Type ty("vector<mud::quat>", sizeof(stl::vector<mud::quat>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<stl::vector<mud::uvec3>>() { static Type ty("vector<mud::uvec3>", sizeof(stl::vector<mud::uvec3>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<stl::vector<mud::vec3>>() { static Type ty("vector<mud::vec3>", sizeof(stl::vector<mud::vec3>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<stl::vector<uint32_t>>() { static Type ty("vector<uint32_t>", sizeof(stl::vector<uint32_t>)); return ty; }
    
    template <> MUD_MATH_EXPORT Type& type<mud::Colour>() { static Type ty("Colour", sizeof(mud::Colour)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::ColourHSL>() { static Type ty("ColourHSL", sizeof(mud::ColourHSL)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Image>() { static Type ty("Image", sizeof(mud::Image)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Image256>() { static Type ty("Image256", sizeof(mud::Image256)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::ImageAtlas>() { static Type ty("ImageAtlas", sizeof(mud::ImageAtlas)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Palette>() { static Type ty("Palette", sizeof(mud::Palette)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Range<float>>() { static Type ty("Range<float>", sizeof(mud::Range<float>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Range<mud::Colour>>() { static Type ty("Range<mud::Colour>", sizeof(mud::Range<mud::Colour>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Range<mud::quat>>() { static Type ty("Range<mud::quat>", sizeof(mud::Range<mud::quat>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Range<mud::vec3>>() { static Type ty("Range<mud::vec3>", sizeof(mud::Range<mud::vec3>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Range<uint32_t>>() { static Type ty("Range<uint32_t>", sizeof(mud::Range<uint32_t>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::StatDef<float>>() { static Type ty("StatDef<float>", sizeof(mud::StatDef<float>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::StatDef<int>>() { static Type ty("StatDef<int>", sizeof(mud::StatDef<int>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Time>() { static Type ty("Time", sizeof(mud::Time)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::TimeSpan>() { static Type ty("TimeSpan", sizeof(mud::TimeSpan)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Transform>() { static Type ty("Transform", sizeof(mud::Transform)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::ValueCurve<float>>() { static Type ty("ValueCurve<float>", sizeof(mud::ValueCurve<float>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::ValueCurve<mud::Colour>>() { static Type ty("ValueCurve<mud::Colour>", sizeof(mud::ValueCurve<mud::Colour>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::ValueCurve<mud::quat>>() { static Type ty("ValueCurve<mud::quat>", sizeof(mud::ValueCurve<mud::quat>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::ValueCurve<mud::vec3>>() { static Type ty("ValueCurve<mud::vec3>", sizeof(mud::ValueCurve<mud::vec3>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::ValueCurve<uint32_t>>() { static Type ty("ValueCurve<uint32_t>", sizeof(mud::ValueCurve<uint32_t>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::ValueTrack<float>>() { static Type ty("ValueTrack<float>", sizeof(mud::ValueTrack<float>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::ValueTrack<mud::Colour>>() { static Type ty("ValueTrack<mud::Colour>", sizeof(mud::ValueTrack<mud::Colour>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::ValueTrack<mud::quat>>() { static Type ty("ValueTrack<mud::quat>", sizeof(mud::ValueTrack<mud::quat>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::ValueTrack<mud::vec3>>() { static Type ty("ValueTrack<mud::vec3>", sizeof(mud::ValueTrack<mud::vec3>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::ValueTrack<uint32_t>>() { static Type ty("ValueTrack<uint32_t>", sizeof(mud::ValueTrack<uint32_t>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::mat3>() { static Type ty("mat3", sizeof(mud::mat3)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::mat4>() { static Type ty("mat4", sizeof(mud::mat4)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::v2<bool>>() { static Type ty("v2<bool>", sizeof(mud::v2<bool>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::v2<float>>() { static Type ty("v2<float>", sizeof(mud::v2<float>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::v2<int>>() { static Type ty("v2<int>", sizeof(mud::v2<int>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::v2<uint>>() { static Type ty("v2<uint>", sizeof(mud::v2<uint>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::v3<bool>>() { static Type ty("v3<bool>", sizeof(mud::v3<bool>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::v3<float>>() { static Type ty("v3<float>", sizeof(mud::v3<float>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::v3<int>>() { static Type ty("v3<int>", sizeof(mud::v3<int>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::v3<uint>>() { static Type ty("v3<uint>", sizeof(mud::v3<uint>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::v4<bool>>() { static Type ty("v4<bool>", sizeof(mud::v4<bool>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::v4<float>>() { static Type ty("v4<float>", sizeof(mud::v4<float>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::v4<int>>() { static Type ty("v4<int>", sizeof(mud::v4<int>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::v4<uint>>() { static Type ty("v4<uint>", sizeof(mud::v4<uint>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Sprite>() { static Type ty("Sprite", type<mud::Image>(), sizeof(mud::Sprite)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::SpriteAtlas>() { static Type ty("SpriteAtlas", type<mud::ImageAtlas>(), sizeof(mud::SpriteAtlas)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::TextureAtlas>() { static Type ty("TextureAtlas", type<mud::ImageAtlas>(), sizeof(mud::TextureAtlas)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::quat>() { static Type ty("quat", type<mud::float4>(), sizeof(mud::quat)); return ty; }
}
