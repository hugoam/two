#ifndef USE_STL
#ifdef MUD_MODULES
module mud.gfx;
#else
#include <stl/array.h>
#include <stl/vector.hpp>
#include <stl/unordered_map.hpp>
#include <stl/unordered_set.hpp>
#include <gfx/Api.h>
#endif

namespace stl
{
	using namespace mud;
	template class MUD_GFX_EXPORT vector<Texture*>;
	template class MUD_GFX_EXPORT vector<Program*>;
	template class MUD_GFX_EXPORT vector<Material*>;
	template class MUD_GFX_EXPORT vector<Animation*>;
	template class MUD_GFX_EXPORT vector<Rig*>;
	template class MUD_GFX_EXPORT vector<Light*>;
	template class MUD_GFX_EXPORT vector<Mesh*>;
	template class MUD_GFX_EXPORT vector<Model*>;
	template class MUD_GFX_EXPORT vector<Mime*>;
	template class MUD_GFX_EXPORT vector<Flare*>;
	template class MUD_GFX_EXPORT vector<Flow*>;
	template class MUD_GFX_EXPORT vector<Prefab*>;
	template class MUD_GFX_EXPORT vector<Item*>;
	template class MUD_GFX_EXPORT vector<Direct*>;
	template class MUD_GFX_EXPORT vector<Batch*>;
	template class MUD_GFX_EXPORT vector<Sound*>;
	template class MUD_GFX_EXPORT vector<Node3*>;
	template class MUD_GFX_EXPORT vector<ReflectionProbe*>;
	template class MUD_GFX_EXPORT vector<GIProbe*>;
	template class MUD_GFX_EXPORT vector<LightmapAtlas*>;
	template class MUD_GFX_EXPORT vector<LightmapItem*>;
	template class MUD_GFX_EXPORT vector<ImmediateDraw*>;
	template class MUD_GFX_EXPORT vector<Scene*>;
	template class MUD_GFX_EXPORT vector<Viewport*>;
	template class MUD_GFX_EXPORT vector<Importer*>;
	template class MUD_GFX_EXPORT vector<Renderer*>;
	template class MUD_GFX_EXPORT vector<ShaderBlock*>;
	template class MUD_GFX_EXPORT vector<GfxBlock*>;
	template class MUD_GFX_EXPORT vector<DrawBlock*>;
	template class MUD_GFX_EXPORT vector<GfxWindow*>;
	template class MUD_GFX_EXPORT vector<GfxSystem*>;
	template class MUD_GFX_EXPORT vector<Vertex>;
	template class MUD_GFX_EXPORT vector<ShapeVertex>;
	template class MUD_GFX_EXPORT vector<Tri>;
	template class MUD_GFX_EXPORT vector<ModelElem>;
	template class MUD_GFX_EXPORT vector<Item>;
	template class MUD_GFX_EXPORT vector<Direct>;
	//template class MUD_GFX_EXPORT vector<Direct::Batch>;
	template class MUD_GFX_EXPORT vector<Node3>;
	template class MUD_GFX_EXPORT vector<Joint>;
	template class MUD_GFX_EXPORT vector<Skin>;
	template class MUD_GFX_EXPORT vector<ShaderDefine>;
	template class MUD_GFX_EXPORT vector<PassJob>;
	template class MUD_GFX_EXPORT vector<Prefab::Elem>;
	template class MUD_GFX_EXPORT vector<Mesh::Morph>;
	template class MUD_GFX_EXPORT vector<Rig::MorphWeight>;
	template class MUD_GFX_EXPORT vector<AnimNode>;
	template class MUD_GFX_EXPORT vector<AnimTrack>;
	template class MUD_GFX_EXPORT vector<AnimTrack::Key>;
	template class MUD_GFX_EXPORT vector<AnimPlay>;
	template class MUD_GFX_EXPORT vector<AnimPlay::Track>;
	template class MUD_GFX_EXPORT vector<Particle>;
	template class MUD_GFX_EXPORT vector<ParticleSort>;
	template class MUD_GFX_EXPORT vector<Viewport::RenderTask>;
	template class MUD_GFX_EXPORT vector<ImmediateDraw::Batch>;
	template class MUD_GFX_EXPORT vector<ImmediateDraw::Vertex>;
	template class MUD_GFX_EXPORT vector<Lines::Segment>;
	template class MUD_GFX_EXPORT vector<Import::Item>;
	template class MUD_GFX_EXPORT vector<DrawElement>;
	template class MUD_GFX_EXPORT vector<Frustum>;
	//template class MUD_GFX_EXPORT vector<LightRecord>;
	template class MUD_GFX_EXPORT vector<Froxelizer::FroxelEntry>;
	template class MUD_GFX_EXPORT vector<array<uint, 8193>>;
	template class MUD_GFX_EXPORT vector<unique<Gnode>>;
	template class MUD_GFX_EXPORT vector<unique<GfxBlock>>;
	template class MUD_GFX_EXPORT vector<unique<Picker>>;
	template class MUD_GFX_EXPORT vector<vector<float>>;
	template class MUD_GFX_EXPORT unordered_map<int, Skeleton*>;
	template class MUD_GFX_EXPORT unordered_map<string, Material*>;
	template class MUD_GFX_EXPORT unordered_set<Model*>;
	template class MUD_GFX_EXPORT vector<function<void(Texture&, const string&, const NoConfig&)>>;
	template class MUD_GFX_EXPORT vector<function<void(Material&, const string&, const NoConfig&)>>;
	template class MUD_GFX_EXPORT vector<function<void(Program&, const string&, const NoConfig&)>>;
	template class MUD_GFX_EXPORT vector<function<void(Model&, const string&, const ImportConfig&)>>;
	template class MUD_GFX_EXPORT vector<function<void(Flow&, const string&, const NoConfig&)>>;
	template class MUD_GFX_EXPORT vector<function<void(Prefab&, const string&, const ImportConfig&)>>;
	template class MUD_GFX_EXPORT unordered_map<string, unique<Texture>>;
	template class MUD_GFX_EXPORT unordered_map<string, unique<Material>>;
	template class MUD_GFX_EXPORT unordered_map<string, unique<Program>>;
	template class MUD_GFX_EXPORT unordered_map<string, unique<Model>>;
	template class MUD_GFX_EXPORT unordered_map<string, unique<Flow>>;
	template class MUD_GFX_EXPORT unordered_map<string, unique<Prefab>>;
	template class MUD_GFX_EXPORT unordered_map<uint32_t, uint32_t>;
	template class MUD_GFX_EXPORT unordered_map<uint64_t, Program::Version>;
	template class MUD_GFX_EXPORT unordered_map<string, bgfx::UniformHandle>;

	template class MUD_GFX_EXPORT vector<bgfx::InstanceDataBuffer>;
	template class MUD_GFX_EXPORT unordered_map<uint, bgfx::VertexDecl>;
}
#endif
