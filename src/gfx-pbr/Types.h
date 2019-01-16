#pragma once

#include <gfx-pbr/Forward.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <type/Type.h>
#include <type/Vector.h>
#endif

#ifndef MUD_MODULES
#include <infra/Types.h>
#include <type/Types.h>
#include <math/Types.h>
#include <geom/Types.h>
#include <gfx/Types.h>
#endif

#ifndef MUD_CPP_20
#include <stl/string.h>
#include <cstdint>
#include <stl/vector.h>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::TonemapMode>();
    
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BCS>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::DofBlur>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::GIProbe>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::Glow>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::LightShadow>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::Lightmap>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::LightmapAtlas>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::LightmapItem>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::ReflectionProbe>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::RenderFilters>();
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
    
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::BCS*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::DofBlur*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::GIProbe*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::Glow*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::LightShadow*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::Lightmap*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::LightmapAtlas*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::LightmapItem*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::ReflectionProbe*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::RenderFilters*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::Tonemap*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::BlockBlur*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::BlockDofBlur*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::BlockGIBake*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::BlockGITrace*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::BlockGeometry*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::BlockGlow*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::BlockLight*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::BlockLightmap*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::BlockRadiance*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::BlockReflection*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::BlockShadow*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::BlockTonemap*>>;
}
