#pragma once

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>
#include <gfx-pbr/Forward.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <type/Type.h>
#endif

#ifndef MUD_MODULES
#include <infra/Types.h>
#include <type/Types.h>
#include <math/Types.h>
#include <geom/Types.h>
#include <gfx/Types.h>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::TonemapMode>();
    
    
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BCS>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::CSMShadow>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::DofBlur>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::DofParams>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::GIProbe>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::Glow>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::LightShadow>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::Lightmap>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::LightmapAtlas>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::LightmapItem>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::ReflectionProbe>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::Tonemap>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockBlur>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockDofBlur>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockGIBake>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockGITrace>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockGeometry>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockGlow>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockLight>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockLightmap>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockRadiance>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockReflection>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockShadow>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockTonemap>();
}
