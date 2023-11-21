#ifndef USE_STL
module two.gfx.pbr;

namespace stl
{
	using namespace two;
	template class TWO_GFX_PBR_EXPORT vector<Radiance*>;
	template class TWO_GFX_PBR_EXPORT vector<DofBlur>;;
	template class TWO_GFX_PBR_EXPORT vector<Glow>;;
	template class TWO_GFX_PBR_EXPORT vector<BCS>;;
	template class TWO_GFX_PBR_EXPORT vector<Tonemap>;
	template class TWO_GFX_PBR_EXPORT vector<MeshPacker>;
	template class TWO_GFX_PBR_EXPORT vector<GpuLight>;
	template class TWO_GFX_PBR_EXPORT vector<LightShadow>;
	template class TWO_GFX_PBR_EXPORT vector<LightmapItem>;
	template class TWO_GFX_PBR_EXPORT vector<FrustumSlice*>;
	template class TWO_GFX_PBR_EXPORT vector<CSMSlice>;
	template class TWO_GFX_PBR_EXPORT vector<CSMShadow>;
	template class TWO_GFX_PBR_EXPORT vector<AtlasIndex>;
	template class TWO_GFX_PBR_EXPORT vector<ShadowAtlas::Slice>;
	template class TWO_GFX_PBR_EXPORT vector<ShadowAtlas::Slot>;
	template class TWO_GFX_PBR_EXPORT vector<ShadowAtlas::Block>;
	template class TWO_GFX_PBR_EXPORT vector<CubeTarget>;
	template class TWO_GFX_PBR_EXPORT vector<ReflectionAtlas::Slot>;
	template class TWO_GFX_PBR_EXPORT vector<ReflectionAtlas::Slot*>;
	template class TWO_GFX_PBR_EXPORT vector<BlockLightmap::BakeEntry>;
	template class TWO_GFX_PBR_EXPORT vector<unique<Lightmap>>;
	template class TWO_GFX_PBR_EXPORT vector<ReflectionProbe*>;
	template class TWO_GFX_PBR_EXPORT vector<GIProbe*>;
	template class TWO_GFX_PBR_EXPORT vector<LightmapAtlas*>;
	template class TWO_GFX_PBR_EXPORT vector<LightmapItem*>;
	template class TWO_GFX_PBR_EXPORT unordered_map<Model*, ModelUnwrap>;
	template class TWO_GFX_PBR_EXPORT unordered_map<Texture*, Texture*>;
	//template class TWO_GFX_PBR_EXPORT unordered_map<uint32_t, Shadowmap>;
}
#endif
