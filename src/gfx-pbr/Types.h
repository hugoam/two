#pragma once

#include <gfx-pbr/Forward.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <type/Type.h>
#endif


namespace two
{
    // Exported types
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::TonemapMode>();
    
    
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockLight>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::LightmapItem>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::Lightmap>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::LightmapAtlas>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockLightmap>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::PBRShot>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockGeometry>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockRadiance>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::CubeTarget>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::CubeCamera>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::ReflectionProbe>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockReflection>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::LightShadow>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::CSMSlice>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::CSMShadow>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockShadow>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::GIProbe>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockGITrace>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockGIBake>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockBlur>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::DofParams>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::DofBlur>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockDofBlur>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::Glow>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockGlow>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::BCS>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::Tonemap>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockTonemap>();
}
