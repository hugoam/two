#pragma once

#include <gfx-pbr/Forward.h>

#if defined TWO_TYPE_LIB
#include <type/Type.h>
#endif


namespace two
{
    // Exported types
    template <> TWO_GFX_PBR_EXPORT Type& type<two::TonemapMode>();
    
    
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockLight>();
    template <> TWO_GFX_PBR_EXPORT Type& type<two::LightmapItem>();
    template <> TWO_GFX_PBR_EXPORT Type& type<two::Lightmap>();
    template <> TWO_GFX_PBR_EXPORT Type& type<two::LightmapAtlas>();
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockLightmap>();
    template <> TWO_GFX_PBR_EXPORT Type& type<two::PBRShot>();
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockGeometry>();
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockRadiance>();
    template <> TWO_GFX_PBR_EXPORT Type& type<two::CubeTarget>();
    template <> TWO_GFX_PBR_EXPORT Type& type<two::CubeCamera>();
    template <> TWO_GFX_PBR_EXPORT Type& type<two::ReflectionProbe>();
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockReflection>();
    template <> TWO_GFX_PBR_EXPORT Type& type<two::LightShadow>();
    template <> TWO_GFX_PBR_EXPORT Type& type<two::CSMSlice>();
    template <> TWO_GFX_PBR_EXPORT Type& type<two::CSMShadow>();
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockShadow>();
    template <> TWO_GFX_PBR_EXPORT Type& type<two::GIProbeHandle>();
    template <> TWO_GFX_PBR_EXPORT Type& type<two::LightmapAtlasHandle>();
    template <> TWO_GFX_PBR_EXPORT Type& type<two::GIProbe>();
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockGITrace>();
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockGIBake>();
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockBlur>();
    template <> TWO_GFX_PBR_EXPORT Type& type<two::DofParams>();
    template <> TWO_GFX_PBR_EXPORT Type& type<two::DofBlur>();
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockDofBlur>();
    template <> TWO_GFX_PBR_EXPORT Type& type<two::Glow>();
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockGlow>();
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BCS>();
    template <> TWO_GFX_PBR_EXPORT Type& type<two::Tonemap>();
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockTonemap>();
}
