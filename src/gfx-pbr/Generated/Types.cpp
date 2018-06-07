

#include <gfx/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
#include <gfx-pbr/Generated/Types.h>
#include <gfx-pbr/Generated/Module.h>
#include <obj/Proto.h>
#endif

namespace mud
{
    // Exported types
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::CSMFilterMode>() { static Type ty("mud::CSMFilterMode"); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::ShaderModeShadow>() { static Type ty("mud::ShaderModeShadow"); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::ShaderOptionBlur>() { static Type ty("mud::ShaderOptionBlur"); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::ShaderOptionDofBlur>() { static Type ty("mud::ShaderOptionDofBlur"); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::ShaderOptionGlow>() { static Type ty("mud::ShaderOptionGlow"); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::ShaderOptionLight>() { static Type ty("mud::ShaderOptionLight"); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::ShaderOptionRadiance>() { static Type ty("mud::ShaderOptionRadiance"); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::ShaderOptionShadow>() { static Type ty("mud::ShaderOptionShadow"); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::TonemapMode>() { static Type ty("mud::TonemapMode"); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::TonemapShaderMode>() { static Type ty("mud::TonemapShaderMode"); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::TonemapShaderOption>() { static Type ty("mud::TonemapShaderOption"); return ty; }
    
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BCS>() { static Type ty("BCS"); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::DepthParams>() { static Type ty("DepthParams"); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::DofBlur>() { static Type ty("DofBlur"); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::Glow>() { static Type ty("Glow"); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::LightShadow>() { static Type ty("LightShadow"); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::ReflectionProbe>() { static Type ty("ReflectionProbe"); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::RenderFilters>() { static Type ty("RenderFilters"); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::Tonemap>() { static Type ty("Tonemap"); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockBlur>() { static Type ty("BlockBlur", type<mud::GfxBlock>()); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockDofBlur>() { static Type ty("BlockDofBlur", type<mud::GfxBlock>()); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockGlow>() { static Type ty("BlockGlow", type<mud::GfxBlock>()); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockReflection>() { static Type ty("BlockReflection", type<mud::GfxBlock>()); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockTonemap>() { static Type ty("BlockTonemap", type<mud::GfxBlock>()); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockDepth>() { static Type ty("BlockDepth", type<mud::DrawBlock>()); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockLight>() { static Type ty("BlockLight", type<mud::DrawBlock>()); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockRadiance>() { static Type ty("BlockRadiance", type<mud::DrawBlock>()); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockShadow>() { static Type ty("BlockShadow", type<mud::DrawBlock>()); return ty; }
}
