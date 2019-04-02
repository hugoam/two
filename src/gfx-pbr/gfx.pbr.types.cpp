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
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::TonemapMode>() { static Type ty("TonemapMode", sizeof(mud::TonemapMode)); return ty; }
    
    
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BCS>() { static Type ty("BCS", sizeof(mud::BCS)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::CSMShadow>() { static Type ty("CSMShadow", sizeof(mud::CSMShadow)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::CubeCamera>() { static Type ty("CubeCamera", sizeof(mud::CubeCamera)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::CubeTarget>() { static Type ty("CubeTarget", sizeof(mud::CubeTarget)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::DofBlur>() { static Type ty("DofBlur", sizeof(mud::DofBlur)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::DofParams>() { static Type ty("DofParams", sizeof(mud::DofParams)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::GIProbe>() { static Type ty("GIProbe", sizeof(mud::GIProbe)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::Glow>() { static Type ty("Glow", sizeof(mud::Glow)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::LightShadow>() { static Type ty("LightShadow", sizeof(mud::LightShadow)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::Lightmap>() { static Type ty("Lightmap", sizeof(mud::Lightmap)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::LightmapAtlas>() { static Type ty("LightmapAtlas", sizeof(mud::LightmapAtlas)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::LightmapItem>() { static Type ty("LightmapItem", sizeof(mud::LightmapItem)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::ReflectionProbe>() { static Type ty("ReflectionProbe", sizeof(mud::ReflectionProbe)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::Tonemap>() { static Type ty("Tonemap", sizeof(mud::Tonemap)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockBlur>() { static Type ty("BlockBlur", type<mud::GfxBlock>(), sizeof(mud::BlockBlur)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockDofBlur>() { static Type ty("BlockDofBlur", type<mud::GfxBlock>(), sizeof(mud::BlockDofBlur)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockGIBake>() { static Type ty("BlockGIBake", type<mud::DrawBlock>(), sizeof(mud::BlockGIBake)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockGITrace>() { static Type ty("BlockGITrace", type<mud::DrawBlock>(), sizeof(mud::BlockGITrace)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockGeometry>() { static Type ty("BlockGeometry", type<mud::DrawBlock>(), sizeof(mud::BlockGeometry)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockGlow>() { static Type ty("BlockGlow", type<mud::GfxBlock>(), sizeof(mud::BlockGlow)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockLight>() { static Type ty("BlockLight", type<mud::DrawBlock>(), sizeof(mud::BlockLight)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockLightmap>() { static Type ty("BlockLightmap", type<mud::DrawBlock>(), sizeof(mud::BlockLightmap)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockRadiance>() { static Type ty("BlockRadiance", type<mud::DrawBlock>(), sizeof(mud::BlockRadiance)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockReflection>() { static Type ty("BlockReflection", type<mud::DrawBlock>(), sizeof(mud::BlockReflection)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockShadow>() { static Type ty("BlockShadow", type<mud::DrawBlock>(), sizeof(mud::BlockShadow)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockTonemap>() { static Type ty("BlockTonemap", type<mud::GfxBlock>(), sizeof(mud::BlockTonemap)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::CSMSlice>() { static Type ty("CSMSlice", type<mud::LightShadow>(), sizeof(mud::CSMSlice)); return ty; }
}
