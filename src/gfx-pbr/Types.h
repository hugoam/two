#pragma once

#include <gfx-pbr/Forward.h>

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <obj/Type.h>
//#include <proto/Proto.h>
#endif

#ifndef MUD_MODULES
#include <obj/Types.h>
#include <srlz/Types.h>
#include <math/Types.h>
#include <geom/Types.h>
#include <gfx/Types.h>
#endif

#ifndef MUD_CPP_20
#include <string>
#include <vector>
#include <cstdint>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::CSMFilterMode>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::ShaderModeShadow>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::ShaderOptionBlur>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::ShaderOptionDofBlur>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::ShaderOptionGlow>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::ShaderOptionLight>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::ShaderOptionRadiance>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::ShaderOptionShadow>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::TonemapMode>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::TonemapShaderMode>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::TonemapShaderOption>();
    
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BCS>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::DepthParams>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::DofBlur>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::Glow>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::LightShadow>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::ReflectionProbe>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::RenderFilters>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::Tonemap>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockBlur>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockDofBlur>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockGlow>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockReflection>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockTonemap>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockDepth>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockLight>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockRadiance>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockShadow>();
}
