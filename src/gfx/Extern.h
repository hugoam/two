#pragma once

#include <stl/vector.h>
#include <stl/unordered_map.h>
#include <stl/unordered_set.h>
#include <gfx/Api.h>

namespace stl
{
	using namespace mud;
	export_ extern template class vector<Texture*>;
	export_ extern template class vector<Material*>;
	export_ extern template class vector<Animation*>;
	export_ extern template class vector<Rig*>;
	export_ extern template class vector<Light*>;
	export_ extern template class vector<Mesh*>;
	export_ extern template class vector<Model*>;
	export_ extern template class vector<Animated*>;
	export_ extern template class vector<Particles*>;
	export_ extern template class vector<Item*>;
	export_ extern template class vector<Sound*>;
	export_ extern template class vector<Node3*>;
	export_ extern template class vector<ReflectionProbe*>;
	export_ extern template class vector<GIProbe*>;
	export_ extern template class vector<LightmapAtlas*>;
	export_ extern template class vector<ImmediateDraw*>;
	export_ extern template class vector<Scene*>;
	export_ extern template class vector<Viewport*>;
	export_ extern template class vector<Importer*>;
	export_ extern template class vector<Renderer*>;
	export_ extern template class vector<GfxBlock*>;
	export_ extern template class vector<DrawBlock*>;
	export_ extern template class vector<GfxContext*>;
	export_ extern template class vector<GfxSystem*>;
	export_ extern template class vector<Vertex>;
	export_ extern template class vector<ShapeVertex>;
	export_ extern template class vector<Tri>;
	export_ extern template class vector<ModelItem>;
	export_ extern template class vector<Item>;
	export_ extern template class vector<Node3>;
	export_ extern template class vector<Bone>;
	export_ extern template class vector<Joint>;
	export_ extern template class vector<Skin>;
	export_ extern template class vector<ShaderDefine>;
	export_ extern template class vector<PassJob>;
	export_ extern template class vector<AnimationTrack>;
	export_ extern template class vector<AnimationTrack::Key>;
	export_ extern template class vector<AnimationPlay>;
	export_ extern template class vector<AnimatedTrack>;
	export_ extern template class vector<Particle>;
	export_ extern template class vector<Viewport::RenderTask>;
	export_ extern template class vector<ImmediateDraw::Batch>;
	export_ extern template class vector<ImmediateDraw::Vertex>;
	export_ extern template class vector<Import::Item>;
	export_ extern template class vector<DrawElement>;
	export_ extern template class vector<ProcShape>;
	export_ extern template class vector<Frustum>;
	export_ extern template class vector<Froxelizer>;
	export_ extern template class vector<LightRecord>;
	export_ extern template class vector<Froxelizer::FroxelEntry>;
	export_ extern template class vector<carray<uint, 8193>>;
	export_ extern template class vector<unique<Gnode>>;
	export_ extern template class vector<unique<RenderPass>>;
	export_ extern template class vector<unique<GfxBlock>>;
	export_ extern template class vector<unique<Picker>>;
	export_ extern template class unordered_map<int, Skeleton*>;
	export_ extern template class unordered_set<Model*>;
	export_ extern template class vector<function<void(Texture&, const string&)>>;
	export_ extern template class vector<function<void(Material&, const string&)>>;
	export_ extern template class vector<function<void(Program&, const string&)>>;
	export_ extern template class vector<function<void(Model&, const string&)>>;
	export_ extern template class vector<function<void(ParticleFlow&, const string&)>>;
	export_ extern template class vector<function<void(Prefab&, const string&)>>;
	export_ extern template class unordered_map<string, unique<Texture>>;
	export_ extern template class unordered_map<string, unique<Material>>;
	export_ extern template class unordered_map<string, unique<Program>>;
	export_ extern template class unordered_map<string, unique<Model>>;
	export_ extern template class unordered_map<string, unique<ParticleFlow>>;
	export_ extern template class unordered_map<string, unique<Prefab>>;
	export_ extern template class unordered_map<uint, uint>;
	export_ extern template class unordered_map<uint64_t, Program::Version>;

	export_ extern template class vector<bgfx::InstanceDataBuffer>;
	export_ extern template class unordered_map<uint, bgfx::VertexDecl>;
}
