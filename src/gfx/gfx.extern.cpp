#ifndef USE_STL
#ifdef TWO_MODULES
module two.gfx;
#else
#include <stl/array.h>
#include <stl/vector.hpp>
#include <stl/unordered_map.hpp>
#include <stl/unordered_set.hpp>
#include <gfx/Api.h>
#endif

namespace stl
{
	using namespace two;
	template class TWO_GFX_EXPORT vector<Texture*>;
	template class TWO_GFX_EXPORT vector<Program*>;
	template class TWO_GFX_EXPORT vector<Material*>;
	template class TWO_GFX_EXPORT vector<Animation*>;
	template class TWO_GFX_EXPORT vector<Rig*>;
	template class TWO_GFX_EXPORT vector<Light*>;
	template class TWO_GFX_EXPORT vector<Mesh*>;
	template class TWO_GFX_EXPORT vector<Model*>;
	template class TWO_GFX_EXPORT vector<Mime*>;
	template class TWO_GFX_EXPORT vector<Flare*>;
	template class TWO_GFX_EXPORT vector<Flow*>;
	template class TWO_GFX_EXPORT vector<Prefab*>;
	template class TWO_GFX_EXPORT vector<Item*>;
	template class TWO_GFX_EXPORT vector<Direct*>;
	template class TWO_GFX_EXPORT vector<Batch*>;
	template class TWO_GFX_EXPORT vector<Sound*>;
	template class TWO_GFX_EXPORT vector<Node3*>;
	template class TWO_GFX_EXPORT vector<ImmediateDraw*>;
	template class TWO_GFX_EXPORT vector<Scene*>;
	template class TWO_GFX_EXPORT vector<Viewport*>;
	template class TWO_GFX_EXPORT vector<Importer*>;
	template class TWO_GFX_EXPORT vector<Renderer*>;
	template class TWO_GFX_EXPORT vector<ShaderBlock*>;
	template class TWO_GFX_EXPORT vector<GfxBlock*>;
	template class TWO_GFX_EXPORT vector<DrawBlock*>;
	template class TWO_GFX_EXPORT vector<GfxWindow*>;
	template class TWO_GFX_EXPORT vector<GfxSystem*>;
	template class TWO_GFX_EXPORT vector<Vertex>;
	template class TWO_GFX_EXPORT vector<ShapeVertex>;
	template class TWO_GFX_EXPORT vector<Tri>;
	template class TWO_GFX_EXPORT vector<ModelElem>;
	template class TWO_GFX_EXPORT vector<Item>;
	template class TWO_GFX_EXPORT vector<Direct>;
	//template class TWO_GFX_EXPORT vector<Direct::Batch>;
	template class TWO_GFX_EXPORT vector<Node3>;
	template class TWO_GFX_EXPORT vector<Joint>;
	template class TWO_GFX_EXPORT vector<Skin>;
	template class TWO_GFX_EXPORT vector<ShaderDefine>;
	template class TWO_GFX_EXPORT vector<PassJob>;
	template class TWO_GFX_EXPORT vector<Prefab::Elem>;
	template class TWO_GFX_EXPORT vector<Mesh::Morph>;
	template class TWO_GFX_EXPORT vector<Rig::MorphWeight>;
	template class TWO_GFX_EXPORT vector<AnimNode>;
	template class TWO_GFX_EXPORT vector<AnimTrack>;
	template class TWO_GFX_EXPORT vector<AnimTrack::Key>;
	template class TWO_GFX_EXPORT vector<AnimPlay>;
	template class TWO_GFX_EXPORT vector<AnimPlay::Track>;
	template class TWO_GFX_EXPORT vector<Particle>;
	template class TWO_GFX_EXPORT vector<ParticleSort>;
	template class TWO_GFX_EXPORT vector<Viewport::RenderTask>;
	template class TWO_GFX_EXPORT vector<ImmediateDraw::Batch>;
	template class TWO_GFX_EXPORT vector<ImmediateDraw::Vertex>;
	template class TWO_GFX_EXPORT vector<Lines::Segment>;
	template class TWO_GFX_EXPORT vector<Import::Item>;
	template class TWO_GFX_EXPORT vector<DrawElement>;
	template class TWO_GFX_EXPORT vector<Frustum>;
	//template class TWO_GFX_EXPORT vector<LightRecord>;
	template class TWO_GFX_EXPORT vector<Froxelizer::FroxelEntry>;
	template class TWO_GFX_EXPORT vector<array<uint, 8193>>;
	template class TWO_GFX_EXPORT vector<unique<Gnode>>;
	template class TWO_GFX_EXPORT vector<unique<GfxBlock>>;
	template class TWO_GFX_EXPORT vector<unique<Picker>>;
	template class TWO_GFX_EXPORT vector<vector<float>>;
	template class TWO_GFX_EXPORT unordered_map<int, Skeleton*>;
	template class TWO_GFX_EXPORT unordered_map<string, Material*>;
	template class TWO_GFX_EXPORT unordered_set<Model*>;
	template class TWO_GFX_EXPORT vector<function<void(Texture&, const string&, const NoConfig&)>>;
	template class TWO_GFX_EXPORT vector<function<void(Material&, const string&, const NoConfig&)>>;
	template class TWO_GFX_EXPORT vector<function<void(Program&, const string&, const NoConfig&)>>;
	template class TWO_GFX_EXPORT vector<function<void(Model&, const string&, const ImportConfig&)>>;
	template class TWO_GFX_EXPORT vector<function<void(Flow&, const string&, const NoConfig&)>>;
	template class TWO_GFX_EXPORT vector<function<void(Prefab&, const string&, const ImportConfig&)>>;
	template class TWO_GFX_EXPORT unordered_map<string, unique<Texture>>;
	template class TWO_GFX_EXPORT unordered_map<string, unique<Material>>;
	template class TWO_GFX_EXPORT unordered_map<string, unique<Program>>;
	template class TWO_GFX_EXPORT unordered_map<string, unique<Model>>;
	template class TWO_GFX_EXPORT unordered_map<string, unique<Flow>>;
	template class TWO_GFX_EXPORT unordered_map<string, unique<Prefab>>;
	template class TWO_GFX_EXPORT unordered_map<uint32_t, uint32_t>;
	template class TWO_GFX_EXPORT unordered_map<uint64_t, Program::Version>;
	template class TWO_GFX_EXPORT unordered_map<string, bgfx::UniformHandle>;

	template class TWO_GFX_EXPORT vector<bgfx::InstanceDataBuffer>;
	template class TWO_GFX_EXPORT unordered_map<uint, bgfx::VertexLayout>;
}
#endif
