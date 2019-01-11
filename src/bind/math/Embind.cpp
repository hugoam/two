#include <math/Api.h>
#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(mud_math)
{
    
    // Enums
    enum_<mud::Axes>("mud::Axes")
        .value("None", mud::Axes::None)
        .value("X", mud::Axes::X)
        .value("Y", mud::Axes::Y)
        .value("Z", mud::Axes::Z)
        ;
    enum_<mud::Axis>("mud::Axis")
        .value("X", mud::Axis::X)
        .value("Y", mud::Axis::Y)
        .value("Z", mud::Axis::Z)
        ;
    enum_<mud::Clockwise>("mud::Clockwise")
        .value("CLOCKWISE", mud::CLOCKWISE)
        .value("ANTI_CLOCKWISE", mud::ANTI_CLOCKWISE)
        ;
    enum_<mud::Side>("mud::Side")
        .value("Right", mud::Side::Right)
        .value("Left", mud::Side::Left)
        .value("Up", mud::Side::Up)
        .value("Down", mud::Side::Down)
        .value("Back", mud::Side::Back)
        .value("Front", mud::Side::Front)
        ;
    enum_<mud::SignedAxis>("mud::SignedAxis")
        .value("PlusX", mud::SignedAxis::PlusX)
        .value("MinusX", mud::SignedAxis::MinusX)
        .value("PlusY", mud::SignedAxis::PlusY)
        .value("MinusY", mud::SignedAxis::MinusY)
        .value("PlusZ", mud::SignedAxis::PlusZ)
        .value("MinusZ", mud::SignedAxis::MinusZ)
        ;
    enum_<mud::Spectrum>("mud::Spectrum")
        .value("Value", mud::Spectrum::Value)
        .value("Hue", mud::Spectrum::Hue)
        ;
    enum_<mud::TrackMode>("mud::TrackMode")
        .value("Constant", mud::TrackMode::Constant)
        .value("ConstantRandom", mud::TrackMode::ConstantRandom)
        .value("Curve", mud::TrackMode::Curve)
        .value("CurveRandom", mud::TrackMode::CurveRandom)
        ;
    
    // Sequences
    
    // Arrays
    value_array<mud::Colour>("Colour")
        .element(&mud::Colour::m_r)
        .element(&mud::Colour::m_g)
        .element(&mud::Colour::m_b)
        .element(&mud::Colour::m_a)
        ;
    value_array<mud::ivec3>("ivec3")
        .element(&mud::ivec3::x)
        .element(&mud::ivec3::y)
        .element(&mud::ivec3::z)
        ;
    value_array<mud::quat>("quat")
        .element(&mud::quat::x)
        .element(&mud::quat::y)
        .element(&mud::quat::z)
        .element(&mud::quat::w)
        ;
    value_array<mud::uvec2>("uvec2")
        .element(&mud::uvec2::x)
        .element(&mud::uvec2::y)
        ;
    value_array<mud::uvec3>("uvec3")
        .element(&mud::uvec3::x)
        .element(&mud::uvec3::y)
        .element(&mud::uvec3::z)
        ;
    value_array<mud::uvec4>("uvec4")
        .element(&mud::uvec4::x)
        .element(&mud::uvec4::y)
        .element(&mud::uvec4::z)
        .element(&mud::uvec4::w)
        ;
    value_array<mud::vec2>("vec2")
        .element(&mud::vec2::x)
        .element(&mud::vec2::y)
        ;
    value_array<mud::vec3>("vec3")
        .element(&mud::vec3::x)
        .element(&mud::vec3::y)
        .element(&mud::vec3::z)
        ;
    value_array<mud::vec4>("vec4")
        .element(&mud::vec4::x)
        .element(&mud::vec4::y)
        .element(&mud::vec4::z)
        .element(&mud::vec4::w)
        ;
    
    // Structs
    value_object<mud::Gauge>("Gauge")
        ;
    value_object<mud::Image>("Image")
        ;
    value_object<mud::Image256>("Image256")
        .field("pixels", &mud::Image256::m_pixels)
        .field("width", &mud::Image256::m_width)
        .field("height", &mud::Image256::m_height)
        .field("palette", &mud::Image256::m_palette)
        ;
    value_object<mud::Palette>("Palette")
        ;
    value_object<mud::Range<float>>("Range<float>")
        .field("min", &mud::Range<float>::m_min)
        .field("max", &mud::Range<float>::m_max)
        ;
    value_object<mud::Range<mud::Colour>>("Range<mud::Colour>")
        .field("min", &mud::Range<mud::Colour>::m_min)
        .field("max", &mud::Range<mud::Colour>::m_max)
        ;
    value_object<mud::Range<mud::quat>>("Range<mud::quat>")
        .field("min", &mud::Range<mud::quat>::m_min)
        .field("max", &mud::Range<mud::quat>::m_max)
        ;
    value_object<mud::Range<mud::vec3>>("Range<mud::vec3>")
        .field("min", &mud::Range<mud::vec3>::m_min)
        .field("max", &mud::Range<mud::vec3>::m_max)
        ;
    value_object<mud::Range<uint32_t>>("Range<uint32_t>")
        .field("min", &mud::Range<uint32_t>::m_min)
        .field("max", &mud::Range<uint32_t>::m_max)
        ;
    value_object<mud::Ratio>("Ratio")
        ;
    value_object<mud::Time>("Time")
        .field("value", &mud::Time::m_value)
        ;
    value_object<mud::TimeSpan>("TimeSpan")
        .field("start", &mud::TimeSpan::start)
        .field("end", &mud::TimeSpan::end)
        ;
    value_object<mud::Transform>("Transform")
        .field("position", &mud::Transform::m_position)
        .field("rotation", &mud::Transform::m_rotation)
        .field("scale", &mud::Transform::m_scale)
        ;
    value_object<mud::ValueCurve<float>>("ValueCurve<float>")
        .field("keys", &mud::ValueCurve<float>::m_keys)
        ;
    value_object<mud::ValueCurve<mud::Colour>>("ValueCurve<mud::Colour>")
        .field("keys", &mud::ValueCurve<mud::Colour>::m_keys)
        ;
    value_object<mud::ValueCurve<mud::quat>>("ValueCurve<mud::quat>")
        .field("keys", &mud::ValueCurve<mud::quat>::m_keys)
        ;
    value_object<mud::ValueCurve<mud::vec3>>("ValueCurve<mud::vec3>")
        .field("keys", &mud::ValueCurve<mud::vec3>::m_keys)
        ;
    value_object<mud::ValueCurve<uint32_t>>("ValueCurve<uint32_t>")
        .field("keys", &mud::ValueCurve<uint32_t>::m_keys)
        ;
    value_object<mud::ValueTrack<float>>("ValueTrack<float>")
        .field("mode", &mud::ValueTrack<float>::m_mode)
        .field("value", &mud::ValueTrack<float>::m_value)
        .field("min", &mud::ValueTrack<float>::m_min)
        .field("max", &mud::ValueTrack<float>::m_max)
        .field("curve", &mud::ValueTrack<float>::m_curve)
        .field("min_curve", &mud::ValueTrack<float>::m_min_curve)
        .field("max_curve", &mud::ValueTrack<float>::m_max_curve)
        ;
    value_object<mud::ValueTrack<mud::Colour>>("ValueTrack<mud::Colour>")
        .field("mode", &mud::ValueTrack<mud::Colour>::m_mode)
        .field("value", &mud::ValueTrack<mud::Colour>::m_value)
        .field("min", &mud::ValueTrack<mud::Colour>::m_min)
        .field("max", &mud::ValueTrack<mud::Colour>::m_max)
        .field("curve", &mud::ValueTrack<mud::Colour>::m_curve)
        .field("min_curve", &mud::ValueTrack<mud::Colour>::m_min_curve)
        .field("max_curve", &mud::ValueTrack<mud::Colour>::m_max_curve)
        ;
    value_object<mud::ValueTrack<mud::quat>>("ValueTrack<mud::quat>")
        .field("mode", &mud::ValueTrack<mud::quat>::m_mode)
        .field("value", &mud::ValueTrack<mud::quat>::m_value)
        .field("min", &mud::ValueTrack<mud::quat>::m_min)
        .field("max", &mud::ValueTrack<mud::quat>::m_max)
        .field("curve", &mud::ValueTrack<mud::quat>::m_curve)
        .field("min_curve", &mud::ValueTrack<mud::quat>::m_min_curve)
        .field("max_curve", &mud::ValueTrack<mud::quat>::m_max_curve)
        ;
    value_object<mud::ValueTrack<mud::vec3>>("ValueTrack<mud::vec3>")
        .field("mode", &mud::ValueTrack<mud::vec3>::m_mode)
        .field("value", &mud::ValueTrack<mud::vec3>::m_value)
        .field("min", &mud::ValueTrack<mud::vec3>::m_min)
        .field("max", &mud::ValueTrack<mud::vec3>::m_max)
        .field("curve", &mud::ValueTrack<mud::vec3>::m_curve)
        .field("min_curve", &mud::ValueTrack<mud::vec3>::m_min_curve)
        .field("max_curve", &mud::ValueTrack<mud::vec3>::m_max_curve)
        ;
    value_object<mud::ValueTrack<uint32_t>>("ValueTrack<uint32_t>")
        .field("mode", &mud::ValueTrack<uint32_t>::m_mode)
        .field("value", &mud::ValueTrack<uint32_t>::m_value)
        .field("min", &mud::ValueTrack<uint32_t>::m_min)
        .field("max", &mud::ValueTrack<uint32_t>::m_max)
        .field("curve", &mud::ValueTrack<uint32_t>::m_curve)
        .field("min_curve", &mud::ValueTrack<uint32_t>::m_min_curve)
        .field("max_curve", &mud::ValueTrack<uint32_t>::m_max_curve)
        ;
    value_object<mud::bvec3>("bvec3")
        ;
    value_object<mud::bvec4>("bvec4")
        ;
    value_object<mud::half2>("half2")
        ;
    value_object<mud::half3>("half3")
        ;
    value_object<mud::ivec2>("ivec2")
        ;
    value_object<mud::ivec4>("ivec4")
        ;
    value_object<mud::mat4>("mat4")
        ;
    
    // Classes
    class_<mud::AutoStat<float>>("AutoStat<float>")
        ;
    class_<mud::AutoStat<int>>("AutoStat<int>")
        ;
    class_<mud::ImageAtlas>("ImageAtlas")
        ;
    class_<mud::Sprite>("Sprite")
        ;
    class_<mud::SpriteAtlas>("SpriteAtlas")
        ;
    class_<mud::TextureAtlas>("TextureAtlas")
        ;
    
    // Functions
    function("sinf", &sinf);
    function("cosf", &cosf);
    function("sin", &sin);
    function("cos", &cos);
    function("add<float>", &mud::add<float>);
    function("subtract<float>", &mud::subtract<float>);
    function("multiply<float>", &mud::multiply<float>);
    function("divide<float>", &mud::divide<float>);
    function("nsinf", &mud::nsinf);
    function("ncosf", &mud::ncosf);
    function("nsin", &mud::nsin);
    function("ncos", &mud::ncos);
    function("to_rgba", &mud::to_rgba);
    function("to_abgr", &mud::to_abgr);
    function("from_rgba", &mud::from_rgba);
    function("from_abgr", &mud::from_abgr);
    function("to_linear", &mud::to_linear);
    function("to_gamma", &mud::to_gamma);
    function("to_srgb", &mud::to_srgb);
    function("hsl_to_rgb", &mud::hsl_to_rgb);
    function("rgb_to_hsl", &mud::rgb_to_hsl);
    function("rgba_to_hsla", &mud::rgba_to_hsla);
    function("hsla_to_rgba", &mud::hsla_to_rgba);
    function("oriented_angle_2d", &mud::oriented_angle_2d);
    function("oriented_angle", &mud::oriented_angle);
    function("angle_axis", &mud::angle_axis);
    function("axis_angle", &mud::axis_angle);
    function("rotate", &mud::rotate);
    function("rotate", &mud::rotate);
    function("look_dir", &mud::look_dir);
    function("look_at", &mud::look_at);
    function("add<mud::vec3>", &mud::add<mud::vec3>);
    function("subtract<mud::vec3>", &mud::subtract<mud::vec3>);
    function("multiply<mud::vec3>", &mud::multiply<mud::vec3>);
    function("divide<mud::vec3>", &mud::divide<mud::vec3>);
    function("distance", &glm::distance);
    function("length", &glm::length);
    function("length2", &glm::length2);
    function("grid", &mud::grid);
    function("grid_center", &mud::grid_center);
    function("index_list", &mud::index_list);
    
}
