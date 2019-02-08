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
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockBlur>() { static Type ty("BlockBlur", sizeof(mud::BlockBlur)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockDofBlur>() { static Type ty("BlockDofBlur", sizeof(mud::BlockDofBlur)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockGIBake>() { static Type ty("BlockGIBake", sizeof(mud::BlockGIBake)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockGITrace>() { static Type ty("BlockGITrace", sizeof(mud::BlockGITrace)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockGeometry>() { static Type ty("BlockGeometry", sizeof(mud::BlockGeometry)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockGlow>() { static Type ty("BlockGlow", sizeof(mud::BlockGlow)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockLight>() { static Type ty("BlockLight", sizeof(mud::BlockLight)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockLightmap>() { static Type ty("BlockLightmap", sizeof(mud::BlockLightmap)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockRadiance>() { static Type ty("BlockRadiance", sizeof(mud::BlockRadiance)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockReflection>() { static Type ty("BlockReflection", sizeof(mud::BlockReflection)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockShadow>() { static Type ty("BlockShadow", sizeof(mud::BlockShadow)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockTonemap>() { static Type ty("BlockTonemap", sizeof(mud::BlockTonemap)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::DofBlur>() { static Type ty("DofBlur", sizeof(mud::DofBlur)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::GIProbe>() { static Type ty("GIProbe", sizeof(mud::GIProbe)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::Glow>() { static Type ty("Glow", sizeof(mud::Glow)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::LightShadow>() { static Type ty("LightShadow", sizeof(mud::LightShadow)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::Lightmap>() { static Type ty("Lightmap", sizeof(mud::Lightmap)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::LightmapAtlas>() { static Type ty("LightmapAtlas", sizeof(mud::LightmapAtlas)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::LightmapItem>() { static Type ty("LightmapItem", sizeof(mud::LightmapItem)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::ReflectionProbe>() { static Type ty("ReflectionProbe", sizeof(mud::ReflectionProbe)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::Tonemap>() { static Type ty("Tonemap", sizeof(mud::Tonemap)); return ty; }
}
