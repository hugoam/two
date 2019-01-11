#include <gfx-pbr/Api.h>
#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(mud_gfx_pbr)
{
    
    // Enums
    enum_<mud::TonemapMode>("mud::TonemapMode")
        .value("Linear", mud::TonemapMode::Linear)
        .value("Reinhardt", mud::TonemapMode::Reinhardt)
        .value("Filmic", mud::TonemapMode::Filmic)
        .value("ACES", mud::TonemapMode::ACES)
        ;
    
    // Sequences
    
    // Arrays
    
    // Structs
    value_object<mud::BCS>("BCS")
        .field("enabled", &mud::BCS::enabled)
        .field("brightness", &mud::BCS::brightness)
        .field("contrast", &mud::BCS::contrast)
        .field("saturation", &mud::BCS::saturation)
        ;
    value_object<mud::DofBlur>("DofBlur")
        .field("enabled", &mud::DofBlur::enabled)
        .field("far_distance", &mud::DofBlur::far_distance)
        .field("far_transition", &mud::DofBlur::far_transition)
        .field("far_radius", &mud::DofBlur::far_radius)
        .field("near_distance", &mud::DofBlur::near_distance)
        .field("near_transition", &mud::DofBlur::near_transition)
        .field("near_radius", &mud::DofBlur::near_radius)
        .field("max_coc_radius", &mud::DofBlur::max_coc_radius)
        ;
    value_object<mud::Glow>("Glow")
        .field("enabled", &mud::Glow::enabled)
        .field("levels_1_4", &mud::Glow::levels_1_4)
        .field("levels_5_8", &mud::Glow::levels_5_8)
        .field("intensity", &mud::Glow::intensity)
        .field("bloom", &mud::Glow::bloom)
        .field("bleed_threshold", &mud::Glow::bleed_threshold)
        .field("bleed_scale", &mud::Glow::bleed_scale)
        .field("bicubic_filter", &mud::Glow::bicubic_filter)
        ;
    value_object<mud::LightShadow>("LightShadow")
        ;
    value_object<mud::RenderFilters>("RenderFilters")
        .field("dof_blur", &mud::RenderFilters::dof_blur)
        .field("glow", &mud::RenderFilters::glow)
        .field("bcs", &mud::RenderFilters::bcs)
        .field("tonemap", &mud::RenderFilters::tonemap)
        ;
    value_object<mud::Tonemap>("Tonemap")
        .field("mode", &mud::Tonemap::mode)
        .field("enabled", &mud::Tonemap::enabled)
        .field("exposure", &mud::Tonemap::exposure)
        .field("white_point", &mud::Tonemap::white_point)
        ;
    
    // Classes
    class_<mud::GIProbe>("GIProbe")
        ;
    class_<mud::Lightmap>("Lightmap")
        ;
    class_<mud::LightmapAtlas>("LightmapAtlas")
        ;
    class_<mud::LightmapItem>("LightmapItem")
        ;
    class_<mud::ReflectionProbe>("ReflectionProbe")
        .property("node", &mud::ReflectionProbe::node)
        .property("visible", &mud::ReflectionProbe::visible)
        .property("intensity", &mud::ReflectionProbe::intensity)
        .property("extents", &mud::ReflectionProbe::extents)
        .property("shadows", &mud::ReflectionProbe::shadows)
        .property("dirty", &mud::ReflectionProbe::dirty)
        ;
    class_<mud::BlockBlur>("BlockBlur")
        ;
    class_<mud::BlockDofBlur>("BlockDofBlur")
        ;
    class_<mud::BlockGIBake>("BlockGIBake")
        ;
    class_<mud::BlockGITrace>("BlockGITrace")
        ;
    class_<mud::BlockGeometry>("BlockGeometry")
        ;
    class_<mud::BlockGlow>("BlockGlow")
        ;
    class_<mud::BlockLight>("BlockLight")
        ;
    class_<mud::BlockLightmap>("BlockLightmap")
        ;
    class_<mud::BlockRadiance>("BlockRadiance")
        ;
    class_<mud::BlockReflection>("BlockReflection")
        ;
    class_<mud::BlockShadow>("BlockShadow")
        ;
    class_<mud::BlockTonemap>("BlockTonemap")
        ;
    
    // Functions
    function("gi_probe", &mud::gfx::gi_probe);
    function("lightmap", &mud::gfx::lightmap);
    
}
