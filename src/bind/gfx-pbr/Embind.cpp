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
        .field("enabled", &mud::BCS::m_enabled)
        .field("brightness", &mud::BCS::m_brightness)
        .field("contrast", &mud::BCS::m_contrast)
        .field("saturation", &mud::BCS::m_saturation)
        ;
    value_object<mud::DofBlur>("DofBlur")
        .field("enabled", &mud::DofBlur::m_enabled)
        .field("far_distance", &mud::DofBlur::m_far_distance)
        .field("far_transition", &mud::DofBlur::m_far_transition)
        .field("far_radius", &mud::DofBlur::m_far_radius)
        .field("near_distance", &mud::DofBlur::m_near_distance)
        .field("near_transition", &mud::DofBlur::m_near_transition)
        .field("near_radius", &mud::DofBlur::m_near_radius)
        .field("max_coc_radius", &mud::DofBlur::m_max_coc_radius)
        ;
    value_object<mud::Glow>("Glow")
        .field("enabled", &mud::Glow::m_enabled)
        .field("levels_1_4", &mud::Glow::m_levels_1_4)
        .field("levels_5_8", &mud::Glow::m_levels_5_8)
        .field("intensity", &mud::Glow::m_intensity)
        .field("bloom", &mud::Glow::m_bloom)
        .field("bleed_threshold", &mud::Glow::m_bleed_threshold)
        .field("bleed_scale", &mud::Glow::m_bleed_scale)
        .field("bicubic_filter", &mud::Glow::m_bicubic_filter)
        ;
    value_object<mud::LightShadow>("LightShadow")
        ;
    value_object<mud::RenderFilters>("RenderFilters")
        .field("dof_blur", &mud::RenderFilters::m_dof_blur)
        .field("glow", &mud::RenderFilters::m_glow)
        .field("bcs", &mud::RenderFilters::m_bcs)
        .field("tonemap", &mud::RenderFilters::m_tonemap)
        ;
    value_object<mud::Tonemap>("Tonemap")
        .field("mode", &mud::Tonemap::m_mode)
        .field("enabled", &mud::Tonemap::m_enabled)
        .field("exposure", &mud::Tonemap::m_exposure)
        .field("white_point", &mud::Tonemap::m_white_point)
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
        .property("node", &mud::ReflectionProbe::m_node)
        .property("visible", &mud::ReflectionProbe::m_visible)
        .property("intensity", &mud::ReflectionProbe::m_intensity)
        .property("extents", &mud::ReflectionProbe::m_extents)
        .property("shadows", &mud::ReflectionProbe::m_shadows)
        .property("dirty", &mud::ReflectionProbe::m_dirty)
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
