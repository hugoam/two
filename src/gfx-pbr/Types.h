#pragma once

#include <gfx-pbr/Forward.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <type/Type.h>
#include <type/Vector.h>
#endif

#ifndef MUD_MODULES
#include <infra/Types.h>
#include <type/Types.h>
#include <srlz/Types.h>
#include <math/Types.h>
#include <geom/Types.h>
#include <gfx/Types.h>
#endif

#ifndef MUD_CPP_20
#include <string>
#include <cstdint>
#include <vector>
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

	export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::GIProbe>();
	export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::LightmapAtlas>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BCS>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::DofBlur>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::Glow>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::LightShadow>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::ReflectionProbe>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::RenderFilters>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::Tonemap>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockBlur>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockDofBlur>();
	export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockGI>();
	export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockGIBake>();
	export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockGITrace>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockGlow>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockReflection>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockTonemap>();
	export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockGeometry>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockLight>();
	export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockLightmap>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockRadiance>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockShadow>();
    
	export_ template struct MUD_GFX_PBR_EXPORT Typed<std::vector<mud::BCS*>>;
	export_ template struct MUD_GFX_PBR_EXPORT Typed<std::vector<mud::DofBlur*>>;
	export_ template struct MUD_GFX_PBR_EXPORT Typed<std::vector<mud::Glow*>>;
	export_ template struct MUD_GFX_PBR_EXPORT Typed<std::vector<mud::LightShadow*>>;
	export_ template struct MUD_GFX_PBR_EXPORT Typed<std::vector<mud::ReflectionProbe*>>;
	export_ template struct MUD_GFX_PBR_EXPORT Typed<std::vector<mud::RenderFilters*>>;
	export_ template struct MUD_GFX_PBR_EXPORT Typed<std::vector<mud::Tonemap*>>;
	export_ template struct MUD_GFX_PBR_EXPORT Typed<std::vector<mud::BlockBlur*>>;
	export_ template struct MUD_GFX_PBR_EXPORT Typed<std::vector<mud::BlockDofBlur*>>;
	export_ template struct MUD_GFX_PBR_EXPORT Typed<std::vector<mud::BlockGlow*>>;
	export_ template struct MUD_GFX_PBR_EXPORT Typed<std::vector<mud::BlockReflection*>>;
	export_ template struct MUD_GFX_PBR_EXPORT Typed<std::vector<mud::BlockTonemap*>>;
	export_ template struct MUD_GFX_PBR_EXPORT Typed<std::vector<mud::BlockLight*>>;
	export_ template struct MUD_GFX_PBR_EXPORT Typed<std::vector<mud::BlockRadiance*>>;
	export_ template struct MUD_GFX_PBR_EXPORT Typed<std::vector<mud::BlockShadow*>>;
}
