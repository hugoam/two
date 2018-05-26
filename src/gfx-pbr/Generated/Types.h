#pragma once

#include <gfx-pbr/Generated/Forward.h>

#include <obj/Generated/Types.h>
#include <math/Generated/Types.h>
#include <geom/Generated/Types.h>
#include <gfx/Generated/Types.h>

#include <obj/Type.h>
#include <obj/Proto.h>

#include <string>
#include <vector>
#include <stdint.h>


namespace mud
{
    // Exported types
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::CSMFilterMode>();
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::ShaderModeShadow>();
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::ShaderOptionBlur>();
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::ShaderOptionDofBlur>();
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::ShaderOptionGlow>();
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::ShaderOptionLight>();
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::ShaderOptionRadiance>();
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::ShaderOptionShadow>();
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::TonemapMode>();
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::TonemapShaderMode>();
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::TonemapShaderOption>();
    
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BCS>();
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::DepthParams>();
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::DofBlur>();
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::Glow>();
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::LightShadow>();
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::ReflectionProbe>();
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::RenderFilters>();
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::Tonemap>();
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockBlur>();
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockDofBlur>();
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockGlow>();
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockReflection>();
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockTonemap>();
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockDepth>();
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockLight>();
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockRadiance>();
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockShadow>();
}
