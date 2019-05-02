#include <infra/Cpp20.h>

#ifdef TWO_MODULES
module two.gfx-pbr;
#else
#include <gfx-pbr/Types.h>
#include <gfx-pbr/Api.h>
#include <type/Vector.h>
#endif

namespace two
{
    // Exported types
    template <> TWO_GFX_PBR_EXPORT Type& type<two::TonemapMode>() { static Type ty("TonemapMode", sizeof(two::TonemapMode)); return ty; }
    
    
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockLight>() { static Type ty("BlockLight", type<two::DrawBlock>(), sizeof(two::BlockLight)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::LightmapItem>() { static Type ty("LightmapItem", sizeof(two::LightmapItem)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::Lightmap>() { static Type ty("Lightmap", sizeof(two::Lightmap)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::LightmapAtlas>() { static Type ty("LightmapAtlas", sizeof(two::LightmapAtlas)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockLightmap>() { static Type ty("BlockLightmap", type<two::DrawBlock>(), sizeof(two::BlockLightmap)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockGeometry>() { static Type ty("BlockGeometry", type<two::DrawBlock>(), sizeof(two::BlockGeometry)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockRadiance>() { static Type ty("BlockRadiance", type<two::DrawBlock>(), sizeof(two::BlockRadiance)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::CubeTarget>() { static Type ty("CubeTarget", sizeof(two::CubeTarget)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::CubeCamera>() { static Type ty("CubeCamera", sizeof(two::CubeCamera)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::ReflectionProbe>() { static Type ty("ReflectionProbe", sizeof(two::ReflectionProbe)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockReflection>() { static Type ty("BlockReflection", type<two::DrawBlock>(), sizeof(two::BlockReflection)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::LightShadow>() { static Type ty("LightShadow", sizeof(two::LightShadow)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::CSMSlice>() { static Type ty("CSMSlice", type<two::LightShadow>(), sizeof(two::CSMSlice)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::CSMShadow>() { static Type ty("CSMShadow", sizeof(two::CSMShadow)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockShadow>() { static Type ty("BlockShadow", type<two::DrawBlock>(), sizeof(two::BlockShadow)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::GIProbe>() { static Type ty("GIProbe", sizeof(two::GIProbe)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockGITrace>() { static Type ty("BlockGITrace", type<two::DrawBlock>(), sizeof(two::BlockGITrace)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockGIBake>() { static Type ty("BlockGIBake", type<two::DrawBlock>(), sizeof(two::BlockGIBake)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockBlur>() { static Type ty("BlockBlur", type<two::GfxBlock>(), sizeof(two::BlockBlur)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::DofParams>() { static Type ty("DofParams", sizeof(two::DofParams)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::DofBlur>() { static Type ty("DofBlur", sizeof(two::DofBlur)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockDofBlur>() { static Type ty("BlockDofBlur", type<two::GfxBlock>(), sizeof(two::BlockDofBlur)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::Glow>() { static Type ty("Glow", sizeof(two::Glow)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockGlow>() { static Type ty("BlockGlow", type<two::GfxBlock>(), sizeof(two::BlockGlow)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BCS>() { static Type ty("BCS", sizeof(two::BCS)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::Tonemap>() { static Type ty("Tonemap", sizeof(two::Tonemap)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockTonemap>() { static Type ty("BlockTonemap", type<two::GfxBlock>(), sizeof(two::BlockTonemap)); return ty; }
}
