#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx-pbr;
#else
#include <gfx-pbr/Types.h>
#include <gfx-pbr/Api.h>
#include <type/Vector.h>
#endif

namespace mud
{
    // Exported types
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::TonemapMode>() { static Type ty("mud::TonemapMode"); return ty; }
    
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BCS>() { static Type ty("BCS"); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::DofBlur>() { static Type ty("DofBlur"); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::GIProbe>() { static Type ty("GIProbe"); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::Glow>() { static Type ty("Glow"); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::LightShadow>() { static Type ty("LightShadow"); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::Lightmap>() { static Type ty("Lightmap"); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::LightmapAtlas>() { static Type ty("LightmapAtlas"); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::LightmapItem>() { static Type ty("LightmapItem"); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::ReflectionProbe>() { static Type ty("ReflectionProbe"); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::RenderFilters>() { static Type ty("RenderFilters"); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::Tonemap>() { static Type ty("Tonemap"); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockBlur>() { static Type ty("BlockBlur", type<mud::GfxBlock>()); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockDofBlur>() { static Type ty("BlockDofBlur", type<mud::GfxBlock>()); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockGIBake>() { static Type ty("BlockGIBake", type<mud::DrawBlock>()); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockGITrace>() { static Type ty("BlockGITrace", type<mud::DrawBlock>()); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockGeometry>() { static Type ty("BlockGeometry", type<mud::DrawBlock>()); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockGlow>() { static Type ty("BlockGlow", type<mud::GfxBlock>()); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockLight>() { static Type ty("BlockLight", type<mud::DrawBlock>()); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockLightmap>() { static Type ty("BlockLightmap", type<mud::DrawBlock>()); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockRadiance>() { static Type ty("BlockRadiance", type<mud::DrawBlock>()); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockReflection>() { static Type ty("BlockReflection", type<mud::DrawBlock>()); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockShadow>() { static Type ty("BlockShadow", type<mud::DrawBlock>()); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockTonemap>() { static Type ty("BlockTonemap", type<mud::GfxBlock>()); return ty; }
}
