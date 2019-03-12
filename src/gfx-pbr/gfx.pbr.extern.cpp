#ifndef USE_STL
#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
#include <stl/vector.hpp>
#include <stl/unordered_map.hpp>
#include <gfx-pbr/Api.h>
#include <geom/Geometry.h>
#endif

namespace stl
{
	using namespace mud;
	template class MUD_GFX_PBR_EXPORT vector<Radiance*>;
	template class MUD_GFX_PBR_EXPORT vector<DofBlur>;;
	template class MUD_GFX_PBR_EXPORT vector<Glow>;;
	template class MUD_GFX_PBR_EXPORT vector<BCS>;;
	template class MUD_GFX_PBR_EXPORT vector<Tonemap>;
	template class MUD_GFX_PBR_EXPORT vector<MeshPacker>;
	template class MUD_GFX_PBR_EXPORT vector<GpuLight>;
	template class MUD_GFX_PBR_EXPORT vector<GpuLightShadow>;
	template class MUD_GFX_PBR_EXPORT vector<LightShadow>;
	template class MUD_GFX_PBR_EXPORT vector<LightmapItem>;
	template class MUD_GFX_PBR_EXPORT vector<FrustumSlice>;
	template class MUD_GFX_PBR_EXPORT vector<ShadowAtlas::Slice>;
	template class MUD_GFX_PBR_EXPORT vector<ShadowAtlas::Index>;
	template class MUD_GFX_PBR_EXPORT vector<ShadowAtlas::Slot>;
	template class MUD_GFX_PBR_EXPORT vector<ShadowAtlas::Slot*>;
	template class MUD_GFX_PBR_EXPORT vector<ReflectionCubemap>;
	template class MUD_GFX_PBR_EXPORT vector<ReflectionAtlas::Slot>;
	template class MUD_GFX_PBR_EXPORT vector<ReflectionAtlas::Slot*>;
	template class MUD_GFX_PBR_EXPORT vector<CSMShadow>;
	template class MUD_GFX_PBR_EXPORT vector<BlockLightmap::BakeEntry>;
	template class MUD_GFX_PBR_EXPORT vector<unique<Lightmap>>;
	template class MUD_GFX_PBR_EXPORT unordered_map<Model*, ModelUnwrap>;
	template class MUD_GFX_PBR_EXPORT unordered_map<Texture*, Texture*>;
	//template class MUD_GFX_PBR_EXPORT unordered_map<uint32_t, Shadowmap>;
}
#endif
