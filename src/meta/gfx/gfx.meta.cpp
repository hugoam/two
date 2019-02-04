#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <cstddef>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/infra/infra.meta.h>
#include <meta/jobs/jobs.meta.h>
#include <meta/type/type.meta.h>
#include <meta/pool/pool.meta.h>
#include <meta/math/math.meta.h>
#include <meta/geom/geom.meta.h>
#include <meta/ctx/ctx.meta.h>
#include <meta/bgfx/bgfx.meta.h>
#include <meta/gfx/gfx.meta.h>
#include <meta/gfx/Convert.h>
#endif

#include <gfx/Api.h>

using namespace mud;

void mud_AnimationTarget__to_string(void* val, string& str) { str = g_enu[type<mud::AnimationTarget>().m_id]->name(uint32_t((*static_cast<mud::AnimationTarget*>(val)))); }
void mud_AnimationTarget__to_value(const string& str, void* val) { (*static_cast<mud::AnimationTarget*>(val)) = mud::AnimationTarget(g_enu[type<mud::AnimationTarget>().m_id]->value(str.c_str())); }
void mud_BackgroundMode__to_string(void* val, string& str) { str = g_enu[type<mud::BackgroundMode>().m_id]->name(uint32_t((*static_cast<mud::BackgroundMode*>(val)))); }
void mud_BackgroundMode__to_value(const string& str, void* val) { (*static_cast<mud::BackgroundMode*>(val)) = mud::BackgroundMode(g_enu[type<mud::BackgroundMode>().m_id]->value(str.c_str())); }
void mud_BlendMode__to_string(void* val, string& str) { str = g_enu[type<mud::BlendMode>().m_id]->name(uint32_t((*static_cast<mud::BlendMode*>(val)))); }
void mud_BlendMode__to_value(const string& str, void* val) { (*static_cast<mud::BlendMode*>(val)) = mud::BlendMode(g_enu[type<mud::BlendMode>().m_id]->value(str.c_str())); }
void mud_CullMode__to_string(void* val, string& str) { str = g_enu[type<mud::CullMode>().m_id]->name(uint32_t((*static_cast<mud::CullMode*>(val)))); }
void mud_CullMode__to_value(const string& str, void* val) { (*static_cast<mud::CullMode*>(val)) = mud::CullMode(g_enu[type<mud::CullMode>().m_id]->value(str.c_str())); }
void mud_DepthDraw__to_string(void* val, string& str) { str = g_enu[type<mud::DepthDraw>().m_id]->name(uint32_t((*static_cast<mud::DepthDraw*>(val)))); }
void mud_DepthDraw__to_value(const string& str, void* val) { (*static_cast<mud::DepthDraw*>(val)) = mud::DepthDraw(g_enu[type<mud::DepthDraw>().m_id]->value(str.c_str())); }
void mud_DepthTest__to_string(void* val, string& str) { str = g_enu[type<mud::DepthTest>().m_id]->name(uint32_t((*static_cast<mud::DepthTest*>(val)))); }
void mud_DepthTest__to_value(const string& str, void* val) { (*static_cast<mud::DepthTest*>(val)) = mud::DepthTest(g_enu[type<mud::DepthTest>().m_id]->value(str.c_str())); }
void mud_EmitterFlow__to_string(void* val, string& str) { str = g_enu[type<mud::EmitterFlow>().m_id]->name(uint32_t((*static_cast<mud::EmitterFlow*>(val)))); }
void mud_EmitterFlow__to_value(const string& str, void* val) { (*static_cast<mud::EmitterFlow*>(val)) = mud::EmitterFlow(g_enu[type<mud::EmitterFlow>().m_id]->value(str.c_str())); }
void mud_Interpolation__to_string(void* val, string& str) { str = g_enu[type<mud::Interpolation>().m_id]->name(uint32_t((*static_cast<mud::Interpolation*>(val)))); }
void mud_Interpolation__to_value(const string& str, void* val) { (*static_cast<mud::Interpolation*>(val)) = mud::Interpolation(g_enu[type<mud::Interpolation>().m_id]->value(str.c_str())); }
void mud_IsometricAngle__to_string(void* val, string& str) { str = g_enu[type<mud::IsometricAngle>().m_id]->name(uint32_t((*static_cast<mud::IsometricAngle*>(val)))); }
void mud_IsometricAngle__to_value(const string& str, void* val) { (*static_cast<mud::IsometricAngle*>(val)) = mud::IsometricAngle(g_enu[type<mud::IsometricAngle>().m_id]->value(str.c_str())); }
void mud_ItemShadow__to_string(void* val, string& str) { str = g_enu[type<mud::ItemShadow>().m_id]->name(uint32_t((*static_cast<mud::ItemShadow*>(val)))); }
void mud_ItemShadow__to_value(const string& str, void* val) { (*static_cast<mud::ItemShadow*>(val)) = mud::ItemShadow(g_enu[type<mud::ItemShadow>().m_id]->value(str.c_str())); }
void mud_LightType__to_string(void* val, string& str) { str = g_enu[type<mud::LightType>().m_id]->name(uint32_t((*static_cast<mud::LightType*>(val)))); }
void mud_LightType__to_value(const string& str, void* val) { (*static_cast<mud::LightType*>(val)) = mud::LightType(g_enu[type<mud::LightType>().m_id]->value(str.c_str())); }
void mud_Lighting__to_string(void* val, string& str) { str = g_enu[type<mud::Lighting>().m_id]->name(uint32_t((*static_cast<mud::Lighting*>(val)))); }
void mud_Lighting__to_value(const string& str, void* val) { (*static_cast<mud::Lighting*>(val)) = mud::Lighting(g_enu[type<mud::Lighting>().m_id]->value(str.c_str())); }
void mud_MSAA__to_string(void* val, string& str) { str = g_enu[type<mud::MSAA>().m_id]->name(uint32_t((*static_cast<mud::MSAA*>(val)))); }
void mud_MSAA__to_value(const string& str, void* val) { (*static_cast<mud::MSAA*>(val)) = mud::MSAA(g_enu[type<mud::MSAA>().m_id]->value(str.c_str())); }
void mud_MaterialFlag__to_string(void* val, string& str) { str = g_enu[type<mud::MaterialFlag>().m_id]->name(uint32_t((*static_cast<mud::MaterialFlag*>(val)))); }
void mud_MaterialFlag__to_value(const string& str, void* val) { (*static_cast<mud::MaterialFlag*>(val)) = mud::MaterialFlag(g_enu[type<mud::MaterialFlag>().m_id]->value(str.c_str())); }
void mud_ModelFormat__to_string(void* val, string& str) { str = g_enu[type<mud::ModelFormat>().m_id]->name(uint32_t((*static_cast<mud::ModelFormat*>(val)))); }
void mud_ModelFormat__to_value(const string& str, void* val) { (*static_cast<mud::ModelFormat*>(val)) = mud::ModelFormat(g_enu[type<mud::ModelFormat>().m_id]->value(str.c_str())); }
void mud_Month__to_string(void* val, string& str) { str = g_enu[type<mud::Month>().m_id]->name(uint32_t((*static_cast<mud::Month*>(val)))); }
void mud_Month__to_value(const string& str, void* val) { (*static_cast<mud::Month*>(val)) = mud::Month(g_enu[type<mud::Month>().m_id]->value(str.c_str())); }
void mud_PbrDiffuseMode__to_string(void* val, string& str) { str = g_enu[type<mud::PbrDiffuseMode>().m_id]->name(uint32_t((*static_cast<mud::PbrDiffuseMode*>(val)))); }
void mud_PbrDiffuseMode__to_value(const string& str, void* val) { (*static_cast<mud::PbrDiffuseMode*>(val)) = mud::PbrDiffuseMode(g_enu[type<mud::PbrDiffuseMode>().m_id]->value(str.c_str())); }
void mud_PbrSpecularMode__to_string(void* val, string& str) { str = g_enu[type<mud::PbrSpecularMode>().m_id]->name(uint32_t((*static_cast<mud::PbrSpecularMode*>(val)))); }
void mud_PbrSpecularMode__to_value(const string& str, void* val) { (*static_cast<mud::PbrSpecularMode*>(val)) = mud::PbrSpecularMode(g_enu[type<mud::PbrSpecularMode>().m_id]->value(str.c_str())); }
void mud_ShaderType__to_string(void* val, string& str) { str = g_enu[type<mud::ShaderType>().m_id]->name(uint32_t((*static_cast<mud::ShaderType*>(val)))); }
void mud_ShaderType__to_value(const string& str, void* val) { (*static_cast<mud::ShaderType*>(val)) = mud::ShaderType(g_enu[type<mud::ShaderType>().m_id]->value(str.c_str())); }
void mud_Shading__to_string(void* val, string& str) { str = g_enu[type<mud::Shading>().m_id]->name(uint32_t((*static_cast<mud::Shading*>(val)))); }
void mud_Shading__to_value(const string& str, void* val) { (*static_cast<mud::Shading*>(val)) = mud::Shading(g_enu[type<mud::Shading>().m_id]->value(str.c_str())); }
void mud_ShadowFlags__to_string(void* val, string& str) { str = g_enu[type<mud::ShadowFlags>().m_id]->name(uint32_t((*static_cast<mud::ShadowFlags*>(val)))); }
void mud_ShadowFlags__to_value(const string& str, void* val) { (*static_cast<mud::ShadowFlags*>(val)) = mud::ShadowFlags(g_enu[type<mud::ShadowFlags>().m_id]->value(str.c_str())); }
void mud_TextureChannel__to_string(void* val, string& str) { str = g_enu[type<mud::TextureChannel>().m_id]->name(uint32_t((*static_cast<mud::TextureChannel*>(val)))); }
void mud_TextureChannel__to_value(const string& str, void* val) { (*static_cast<mud::TextureChannel*>(val)) = mud::TextureChannel(g_enu[type<mud::TextureChannel>().m_id]->value(str.c_str())); }
void mud_TextureHint__to_string(void* val, string& str) { str = g_enu[type<mud::TextureHint>().m_id]->name(uint32_t((*static_cast<mud::TextureHint*>(val)))); }
void mud_TextureHint__to_value(const string& str, void* val) { (*static_cast<mud::TextureHint*>(val)) = mud::TextureHint(g_enu[type<mud::TextureHint>().m_id]->value(str.c_str())); }
void mud_TextureSampler__to_string(void* val, string& str) { str = g_enu[type<mud::TextureSampler>().m_id]->name(uint32_t((*static_cast<mud::TextureSampler*>(val)))); }
void mud_TextureSampler__to_value(const string& str, void* val) { (*static_cast<mud::TextureSampler*>(val)) = mud::TextureSampler(g_enu[type<mud::TextureSampler>().m_id]->value(str.c_str())); }
size_t array_mud_mat4___size(void* vec) { return (*static_cast<array<mud::mat4>*>(vec)).size(); }
void* array_mud_mat4___at(void* vec, size_t i) { return &(*static_cast<array<mud::mat4>*>(vec))[i]; }
size_t vector_mud_Animation____size(void* vec) { return (*static_cast<vector<mud::Animation*>*>(vec)).size(); }
void* vector_mud_Animation____at(void* vec, size_t i) { return &(*static_cast<vector<mud::Animation*>*>(vec))[i]; }
void vector_mud_Animation____add(void* vec, void* value) { (*static_cast<vector<mud::Animation*>*>(vec)).push_back(static_cast<mud::Animation*>(value)); }
void vector_mud_Animation____remove(void* vec, void* value) { vector_remove_any((*static_cast<vector<mud::Animation*>*>(vec)), static_cast<mud::Animation*>(value)); }
size_t vector_mud_AnimationPlay___size(void* vec) { return (*static_cast<vector<mud::AnimationPlay>*>(vec)).size(); }
void* vector_mud_AnimationPlay___at(void* vec, size_t i) { return &(*static_cast<vector<mud::AnimationPlay>*>(vec))[i]; }
void vector_mud_AnimationPlay___add(void* vec, void* value) { (*static_cast<vector<mud::AnimationPlay>*>(vec)).push_back(*static_cast<mud::AnimationPlay*>(value)); }
void vector_mud_AnimationPlay___remove(void* vec, void* value) { vector_remove_any((*static_cast<vector<mud::AnimationPlay>*>(vec)), *static_cast<mud::AnimationPlay*>(value)); }
size_t vector_string___size(void* vec) { return (*static_cast<vector<string>*>(vec)).size(); }
void* vector_string___at(void* vec, size_t i) { return &(*static_cast<vector<string>*>(vec))[i]; }
void vector_string___add(void* vec, void* value) { (*static_cast<vector<string>*>(vec)).push_back(*static_cast<string*>(value)); }
void vector_string___remove(void* vec, void* value) { vector_remove_any((*static_cast<vector<string>*>(vec)), *static_cast<string*>(value)); }
void mud_Animated_start(void* object, array<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Animated*>(object)).start(static_cast<const char*>(args[0]), *static_cast<bool*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3]), *static_cast<bool*>(args[4])); }
void mud_Animated_play(void* object, array<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Animated*>(object)).play(*static_cast<mud::Animation*>(args[0]), *static_cast<bool*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3]), *static_cast<bool*>(args[4])); }
void mud_Animated_seek(void* object, array<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Animated*>(object)).seek(*static_cast<float*>(args[0])); }
void mud_Animated_pause(void* object, array<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::Animated*>(object)).pause(); }
void mud_Animated_stop(void* object, array<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::Animated*>(object)).stop(); }
void mud_Animated_advance(void* object, array<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Animated*>(object)).advance(*static_cast<float*>(args[0])); }
void mud_Animated_next_animation(void* object, array<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::Animated*>(object)).next_animation(); }
void mud_Animated_playing(void* object, array<void*> args, void*& result) { UNUSED(args); (*static_cast<string*>(result)) = (*static_cast<mud::Animated*>(object)).playing(); }
void mud_AnimatedTrack__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::AnimatedTrack*>(ref))) mud::AnimatedTrack(  ); }
void mud_AnimatedTrack__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::AnimatedTrack*>(ref))) mud::AnimatedTrack((*static_cast<mud::AnimatedTrack*>(other))); }
void mud_AnimationPlay__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::AnimationPlay*>(ref))) mud::AnimationPlay(  ); }
void mud_AnimationPlay__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::AnimationPlay*>(ref))) mud::AnimationPlay((*static_cast<mud::AnimationPlay*>(other))); }
void mud_AssetStore_mud_Material__get(void* object, array<void*> args, void*& result) { result = (*static_cast<mud::AssetStore<mud::Material>*>(object)).get(*static_cast<string*>(args[0])); }
void mud_AssetStore_mud_Material__create(void* object, array<void*> args, void*& result) { result = &(*static_cast<mud::AssetStore<mud::Material>*>(object)).create(*static_cast<string*>(args[0])); }
void mud_AssetStore_mud_Material__fetch(void* object, array<void*> args, void*& result) { result = &(*static_cast<mud::AssetStore<mud::Material>*>(object)).fetch(*static_cast<string*>(args[0])); }
void mud_AssetStore_mud_Material__file(void* object, array<void*> args, void*& result) { result = (*static_cast<mud::AssetStore<mud::Material>*>(object)).file(*static_cast<string*>(args[0])); }
void mud_AssetStore_mud_Material__file_at(void* object, array<void*> args, void*& result) { result = &(*static_cast<mud::AssetStore<mud::Material>*>(object)).file_at(*static_cast<string*>(args[0]), *static_cast<string*>(args[1])); }
void mud_AssetStore_mud_Material__destroy(void* object, array<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::AssetStore<mud::Material>*>(object)).destroy(*static_cast<string*>(args[0])); }
void mud_AssetStore_mud_Model__get(void* object, array<void*> args, void*& result) { result = (*static_cast<mud::AssetStore<mud::Model>*>(object)).get(*static_cast<string*>(args[0])); }
void mud_AssetStore_mud_Model__create(void* object, array<void*> args, void*& result) { result = &(*static_cast<mud::AssetStore<mud::Model>*>(object)).create(*static_cast<string*>(args[0])); }
void mud_AssetStore_mud_Model__fetch(void* object, array<void*> args, void*& result) { result = &(*static_cast<mud::AssetStore<mud::Model>*>(object)).fetch(*static_cast<string*>(args[0])); }
void mud_AssetStore_mud_Model__file(void* object, array<void*> args, void*& result) { result = (*static_cast<mud::AssetStore<mud::Model>*>(object)).file(*static_cast<string*>(args[0])); }
void mud_AssetStore_mud_Model__file_at(void* object, array<void*> args, void*& result) { result = &(*static_cast<mud::AssetStore<mud::Model>*>(object)).file_at(*static_cast<string*>(args[0]), *static_cast<string*>(args[1])); }
void mud_AssetStore_mud_Model__destroy(void* object, array<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::AssetStore<mud::Model>*>(object)).destroy(*static_cast<string*>(args[0])); }
void mud_AssetStore_mud_ParticleFlow__get(void* object, array<void*> args, void*& result) { result = (*static_cast<mud::AssetStore<mud::ParticleFlow>*>(object)).get(*static_cast<string*>(args[0])); }
void mud_AssetStore_mud_ParticleFlow__create(void* object, array<void*> args, void*& result) { (*static_cast<mud::ParticleFlow*>(result)) = (*static_cast<mud::AssetStore<mud::ParticleFlow>*>(object)).create(*static_cast<string*>(args[0])); }
void mud_AssetStore_mud_ParticleFlow__fetch(void* object, array<void*> args, void*& result) { (*static_cast<mud::ParticleFlow*>(result)) = (*static_cast<mud::AssetStore<mud::ParticleFlow>*>(object)).fetch(*static_cast<string*>(args[0])); }
void mud_AssetStore_mud_ParticleFlow__file(void* object, array<void*> args, void*& result) { result = (*static_cast<mud::AssetStore<mud::ParticleFlow>*>(object)).file(*static_cast<string*>(args[0])); }
void mud_AssetStore_mud_ParticleFlow__file_at(void* object, array<void*> args, void*& result) { (*static_cast<mud::ParticleFlow*>(result)) = (*static_cast<mud::AssetStore<mud::ParticleFlow>*>(object)).file_at(*static_cast<string*>(args[0]), *static_cast<string*>(args[1])); }
void mud_AssetStore_mud_ParticleFlow__destroy(void* object, array<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::AssetStore<mud::ParticleFlow>*>(object)).destroy(*static_cast<string*>(args[0])); }
void mud_AssetStore_mud_Prefab__get(void* object, array<void*> args, void*& result) { result = (*static_cast<mud::AssetStore<mud::Prefab>*>(object)).get(*static_cast<string*>(args[0])); }
void mud_AssetStore_mud_Prefab__create(void* object, array<void*> args, void*& result) { result = &(*static_cast<mud::AssetStore<mud::Prefab>*>(object)).create(*static_cast<string*>(args[0])); }
void mud_AssetStore_mud_Prefab__fetch(void* object, array<void*> args, void*& result) { result = &(*static_cast<mud::AssetStore<mud::Prefab>*>(object)).fetch(*static_cast<string*>(args[0])); }
void mud_AssetStore_mud_Prefab__file(void* object, array<void*> args, void*& result) { result = (*static_cast<mud::AssetStore<mud::Prefab>*>(object)).file(*static_cast<string*>(args[0])); }
void mud_AssetStore_mud_Prefab__file_at(void* object, array<void*> args, void*& result) { result = &(*static_cast<mud::AssetStore<mud::Prefab>*>(object)).file_at(*static_cast<string*>(args[0]), *static_cast<string*>(args[1])); }
void mud_AssetStore_mud_Prefab__destroy(void* object, array<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::AssetStore<mud::Prefab>*>(object)).destroy(*static_cast<string*>(args[0])); }
void mud_AssetStore_mud_Program__get(void* object, array<void*> args, void*& result) { result = (*static_cast<mud::AssetStore<mud::Program>*>(object)).get(*static_cast<string*>(args[0])); }
void mud_AssetStore_mud_Program__create(void* object, array<void*> args, void*& result) { result = &(*static_cast<mud::AssetStore<mud::Program>*>(object)).create(*static_cast<string*>(args[0])); }
void mud_AssetStore_mud_Program__fetch(void* object, array<void*> args, void*& result) { result = &(*static_cast<mud::AssetStore<mud::Program>*>(object)).fetch(*static_cast<string*>(args[0])); }
void mud_AssetStore_mud_Program__file(void* object, array<void*> args, void*& result) { result = (*static_cast<mud::AssetStore<mud::Program>*>(object)).file(*static_cast<string*>(args[0])); }
void mud_AssetStore_mud_Program__file_at(void* object, array<void*> args, void*& result) { result = &(*static_cast<mud::AssetStore<mud::Program>*>(object)).file_at(*static_cast<string*>(args[0]), *static_cast<string*>(args[1])); }
void mud_AssetStore_mud_Program__destroy(void* object, array<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::AssetStore<mud::Program>*>(object)).destroy(*static_cast<string*>(args[0])); }
void mud_AssetStore_mud_Texture__get(void* object, array<void*> args, void*& result) { result = (*static_cast<mud::AssetStore<mud::Texture>*>(object)).get(*static_cast<string*>(args[0])); }
void mud_AssetStore_mud_Texture__create(void* object, array<void*> args, void*& result) { result = &(*static_cast<mud::AssetStore<mud::Texture>*>(object)).create(*static_cast<string*>(args[0])); }
void mud_AssetStore_mud_Texture__fetch(void* object, array<void*> args, void*& result) { result = &(*static_cast<mud::AssetStore<mud::Texture>*>(object)).fetch(*static_cast<string*>(args[0])); }
void mud_AssetStore_mud_Texture__file(void* object, array<void*> args, void*& result) { result = (*static_cast<mud::AssetStore<mud::Texture>*>(object)).file(*static_cast<string*>(args[0])); }
void mud_AssetStore_mud_Texture__file_at(void* object, array<void*> args, void*& result) { result = &(*static_cast<mud::AssetStore<mud::Texture>*>(object)).file_at(*static_cast<string*>(args[0]), *static_cast<string*>(args[1])); }
void mud_AssetStore_mud_Texture__destroy(void* object, array<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::AssetStore<mud::Texture>*>(object)).destroy(*static_cast<string*>(args[0])); }
void mud_Background__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Background*>(ref))) mud::Background(  ); }
void mud_Background__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Background*>(ref))) mud::Background((*static_cast<mud::Background*>(other))); }
void mud_BaseMaterialBlock__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::BaseMaterialBlock*>(ref))) mud::BaseMaterialBlock(  ); }
void mud_BaseMaterialBlock__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::BaseMaterialBlock*>(ref))) mud::BaseMaterialBlock((*static_cast<mud::BaseMaterialBlock*>(other))); }
void mud_Bone__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Bone*>(ref))) mud::Bone(  ); }
void mud_Bone__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Bone*>(ref))) mud::Bone((*static_cast<mud::Bone*>(other))); }
void mud_DepthParams__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::DepthParams*>(ref))) mud::DepthParams(  ); }
void mud_DepthParams__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::DepthParams*>(ref))) mud::DepthParams((*static_cast<mud::DepthParams*>(other))); }
void mud_Environment__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Environment*>(ref))) mud::Environment(  ); }
void mud_Environment__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Environment*>(ref))) mud::Environment((*static_cast<mud::Environment*>(other))); }
void mud_Fog__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Fog*>(ref))) mud::Fog(  ); }
void mud_Fog__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Fog*>(ref))) mud::Fog((*static_cast<mud::Fog*>(other))); }
void mud_FresnelMaterialBlock__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::FresnelMaterialBlock*>(ref))) mud::FresnelMaterialBlock(  ); }
void mud_FresnelMaterialBlock__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::FresnelMaterialBlock*>(ref))) mud::FresnelMaterialBlock((*static_cast<mud::FresnelMaterialBlock*>(other))); }
void mud_FrustumSlice__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::FrustumSlice*>(ref))) mud::FrustumSlice(  ); }
void mud_FrustumSlice__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::FrustumSlice*>(ref))) mud::FrustumSlice((*static_cast<mud::FrustumSlice*>(other))); }
void* mud_GfxBlock__get_type(void* object) { return &(*static_cast<mud::GfxBlock*>(object)).m_type; }
void mud_GfxSystem__construct_0(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::GfxSystem*>(ref))) mud::GfxSystem( *static_cast<string*>(args[0]) ); }
void* mud_GfxSystem__get_textures(void* object) { return &(*static_cast<mud::GfxSystem*>(object)).textures(); }
void* mud_GfxSystem__get_programs(void* object) { return &(*static_cast<mud::GfxSystem*>(object)).programs(); }
void* mud_GfxSystem__get_materials(void* object) { return &(*static_cast<mud::GfxSystem*>(object)).materials(); }
void* mud_GfxSystem__get_models(void* object) { return &(*static_cast<mud::GfxSystem*>(object)).models(); }
void* mud_GfxSystem__get_particles(void* object) { return &(*static_cast<mud::GfxSystem*>(object)).particles(); }
void* mud_GfxSystem__get_prefabs(void* object) { return &(*static_cast<mud::GfxSystem*>(object)).prefabs(); }
void mud_GfxSystem_default_pipeline(void* object, array<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::GfxSystem*>(object)).default_pipeline(); }
void mud_GfxSystem_add_resource_path(void* object, array<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::GfxSystem*>(object)).add_resource_path(*static_cast<string*>(args[0]), *static_cast<bool*>(args[1])); }
void mud_GfxSystem_debug_material(void* object, array<void*> args, void*& result) { UNUSED(args); result = &(*static_cast<mud::GfxSystem*>(object)).debug_material(); }
void mud_GfxSystem_fetch_material(void* object, array<void*> args, void*& result) { result = &(*static_cast<mud::GfxSystem*>(object)).fetch_material(*static_cast<string*>(args[0]), *static_cast<string*>(args[1]), *static_cast<bool*>(args[2])); }
void mud_GfxSystem_fetch_image256_material(void* object, array<void*> args, void*& result) { result = &(*static_cast<mud::GfxSystem*>(object)).fetch_image256_material(*static_cast<mud::Image256*>(args[0])); }
void mud_GfxSystem_fetch_symbol(void* object, array<void*> args, void*& result) { result = &(*static_cast<mud::GfxSystem*>(object)).fetch_symbol(*static_cast<mud::Symbol*>(args[0]), *static_cast<mud::Shape*>(args[1]), *static_cast<mud::DrawMode*>(args[2])); }
void mud_GfxSystem_fetch_symbol_material(void* object, array<void*> args, void*& result) { result = &(*static_cast<mud::GfxSystem*>(object)).fetch_symbol_material(*static_cast<mud::Symbol*>(args[0]), *static_cast<mud::DrawMode*>(args[1])); }
void mud_ImportConfig__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::ImportConfig*>(ref))) mud::ImportConfig(  ); }
void mud_ImportConfig__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::ImportConfig*>(ref))) mud::ImportConfig((*static_cast<mud::ImportConfig*>(other))); }
void mud_Joint__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Joint*>(ref))) mud::Joint(  ); }
void mud_Joint__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Joint*>(ref))) mud::Joint((*static_cast<mud::Joint*>(other))); }
void* mud_Light__get_node(void* object) { return &(*static_cast<mud::Light*>(object)).m_node; }
void mud_MaterialParam_float___construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::MaterialParam<float>*>(ref))) mud::MaterialParam<float>(  ); }
void mud_MaterialParam_float___copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::MaterialParam<float>*>(ref))) mud::MaterialParam<float>((*static_cast<mud::MaterialParam<float>*>(other))); }
void mud_MaterialParam_mud_Colour___construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::MaterialParam<mud::Colour>*>(ref))) mud::MaterialParam<mud::Colour>(  ); }
void mud_MaterialParam_mud_Colour___copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::MaterialParam<mud::Colour>*>(ref))) mud::MaterialParam<mud::Colour>((*static_cast<mud::MaterialParam<mud::Colour>*>(other))); }
void mud_ModelItem__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::ModelItem*>(ref))) mud::ModelItem(  ); }
void mud_ModelItem__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::ModelItem*>(ref))) mud::ModelItem((*static_cast<mud::ModelItem*>(other))); }
void mud_ParticleFlow__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::ParticleFlow*>(ref))) mud::ParticleFlow(  ); }
void mud_ParticleFlow__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::ParticleFlow*>(ref))) mud::ParticleFlow((*static_cast<mud::ParticleFlow*>(other))); }
void mud_PbrMaterialBlock__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::PbrMaterialBlock*>(ref))) mud::PbrMaterialBlock(  ); }
void mud_PbrMaterialBlock__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::PbrMaterialBlock*>(ref))) mud::PbrMaterialBlock( *static_cast<mud::Colour*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]) ); }
void mud_PbrMaterialBlock__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::PbrMaterialBlock*>(ref))) mud::PbrMaterialBlock((*static_cast<mud::PbrMaterialBlock*>(other))); }
//void* mud_Program__get_name(void* object) { return (*static_cast<mud::Program*>(object)).name(); }
void mud_Radiance__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Radiance*>(ref))) mud::Radiance(  ); }
void mud_Radiance__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Radiance*>(ref))) mud::Radiance((*static_cast<mud::Radiance*>(other))); }
void mud_RenderFrame__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::RenderFrame*>(ref))) mud::RenderFrame(  ); }
void mud_RenderFrame__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::RenderFrame*>(ref))) mud::RenderFrame((*static_cast<mud::RenderFrame*>(other))); }
void mud_RenderQuad__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::RenderQuad*>(ref))) mud::RenderQuad(  ); }
void mud_RenderQuad__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::RenderQuad*>(ref))) mud::RenderQuad((*static_cast<mud::RenderQuad*>(other))); }
void mud_Scene_begin(void* object, array<void*> args, void*& result) { UNUSED(args); result = &(*static_cast<mud::Scene*>(object)).begin(); }
void mud_Sun__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Sun*>(ref))) mud::Sun(  ); }
void mud_Sun__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Sun*>(ref))) mud::Sun((*static_cast<mud::Sun*>(other))); }
void mud_UnshadedMaterialBlock__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::UnshadedMaterialBlock*>(ref))) mud::UnshadedMaterialBlock(  ); }
void mud_UnshadedMaterialBlock__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::UnshadedMaterialBlock*>(ref))) mud::UnshadedMaterialBlock((*static_cast<mud::UnshadedMaterialBlock*>(other))); }
void mud_ClusteredFrustum__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::ClusteredFrustum*>(ref))) mud::ClusteredFrustum(  ); }
void mud_ClusteredFrustum__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::ClusteredFrustum*>(ref))) mud::ClusteredFrustum((*static_cast<mud::ClusteredFrustum*>(other))); }
void mud_Particles__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Particles*>(ref))) mud::Particles(  ); }
void mud_Particles__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Particles*>(ref))) mud::Particles((*static_cast<mud::Particles*>(other))); }
void mud_gfx_update_item_lights_0(array<void*> args, void*& result) { UNUSED(result);  mud::gfx::update_item_lights(*static_cast<mud::Item*>(args[0])); }
void mud_gfx_update_item_aabb_1(array<void*> args, void*& result) { UNUSED(result);  mud::gfx::update_item_aabb(*static_cast<mud::Item*>(args[0])); }
void mud_gfx_node_2(array<void*> args, void*& result) { result = &mud::gfx::node(*static_cast<mud::Gnode*>(args[0]), *static_cast<mud::Ref*>(args[1]), *static_cast<mud::vec3*>(args[2]), *static_cast<mud::quat*>(args[3]), *static_cast<mud::vec3*>(args[4])); }
void mud_gfx_shape_3(array<void*> args, void*& result) { result = &mud::gfx::shape(*static_cast<mud::Gnode*>(args[0]), *static_cast<mud::Shape*>(args[1]), *static_cast<mud::Symbol*>(args[2]), *static_cast<uint32_t*>(args[3]), static_cast<mud::Material*>(args[4]), *static_cast<size_t*>(args[5])); }
void mud_gfx_draw_4(array<void*> args, void*& result) { UNUSED(result);  mud::gfx::draw(*static_cast<mud::Gnode*>(args[0]), *static_cast<mud::Shape*>(args[1]), *static_cast<mud::Symbol*>(args[2]), *static_cast<uint32_t*>(args[3])); }
void mud_gfx_sprite_5(array<void*> args, void*& result) { result = &mud::gfx::sprite(*static_cast<mud::Gnode*>(args[0]), *static_cast<mud::Image256*>(args[1]), *static_cast<mud::vec2*>(args[2]), *static_cast<uint32_t*>(args[3]), static_cast<mud::Material*>(args[4]), *static_cast<size_t*>(args[5])); }
void mud_gfx_item_6(array<void*> args, void*& result) { result = &mud::gfx::item(*static_cast<mud::Gnode*>(args[0]), *static_cast<mud::Model*>(args[1]), *static_cast<uint32_t*>(args[2]), static_cast<mud::Material*>(args[3]), *static_cast<size_t*>(args[4]), *static_cast<array<mud::mat4>*>(args[5])); }
void mud_gfx_prefab_7(array<void*> args, void*& result) { UNUSED(result);  mud::gfx::prefab(*static_cast<mud::Gnode*>(args[0]), *static_cast<mud::Prefab*>(args[1]), *static_cast<bool*>(args[2]), *static_cast<uint32_t*>(args[3]), static_cast<mud::Material*>(args[4]), *static_cast<size_t*>(args[5]), *static_cast<array<mud::mat4>*>(args[6])); }
void mud_gfx_model_8(array<void*> args, void*& result) { result = mud::gfx::model(*static_cast<mud::Gnode*>(args[0]), *static_cast<string*>(args[1]), *static_cast<uint32_t*>(args[2]), static_cast<mud::Material*>(args[3]), *static_cast<size_t*>(args[4])); }
void mud_gfx_animated_9(array<void*> args, void*& result) { result = &mud::gfx::animated(*static_cast<mud::Gnode*>(args[0]), *static_cast<mud::Item*>(args[1])); }
void mud_gfx_particles_10(array<void*> args, void*& result) { (*static_cast<mud::Particles*>(result)) = mud::gfx::particles(*static_cast<mud::Gnode*>(args[0]), *static_cast<mud::ParticleFlow*>(args[1]), *static_cast<uint32_t*>(args[2]), *static_cast<size_t*>(args[3])); }
void mud_gfx_light_11(array<void*> args, void*& result) { result = &mud::gfx::light(*static_cast<mud::Gnode*>(args[0]), *static_cast<mud::LightType*>(args[1]), *static_cast<bool*>(args[2]), *static_cast<mud::Colour*>(args[3]), *static_cast<float*>(args[4]), *static_cast<float*>(args[5])); }
void mud_gfx_sun_light_12(array<void*> args, void*& result) { result = &mud::gfx::sun_light(*static_cast<mud::Gnode*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2])); }
void mud_gfx_radiance_13(array<void*> args, void*& result) { UNUSED(result);  mud::gfx::radiance(*static_cast<mud::Gnode*>(args[0]), *static_cast<string*>(args[1]), *static_cast<mud::BackgroundMode*>(args[2])); }

namespace mud
{
	void mud_gfx_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		Type& t = type<mud::AnimationTarget>();
		static Meta meta = { t, &namspc({ "mud" }), "AnimationTarget", sizeof(mud::AnimationTarget), TypeClass::Enum };
		static cstring ids[] = { "Position", "Rotation", "Scale" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::AnimationTarget vars[] = { mud::AnimationTarget::Position, mud::AnimationTarget::Rotation, mud::AnimationTarget::Scale};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_AnimationTarget__to_string,
		                           mud_AnimationTarget__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::BackgroundMode>();
		static Meta meta = { t, &namspc({ "mud" }), "BackgroundMode", sizeof(mud::BackgroundMode), TypeClass::Enum };
		static cstring ids[] = { "None", "Panorama", "Radiance", "Custom" };
		static uint32_t values[] = { 0, 1, 2, 3 };
		static mud::BackgroundMode vars[] = { mud::BackgroundMode::None, mud::BackgroundMode::Panorama, mud::BackgroundMode::Radiance, mud::BackgroundMode::Custom};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_BackgroundMode__to_string,
		                           mud_BackgroundMode__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::BlendMode>();
		static Meta meta = { t, &namspc({ "mud" }), "BlendMode", sizeof(mud::BlendMode), TypeClass::Enum };
		static cstring ids[] = { "Mix", "Add", "Sub", "Mul", "Normal", "Alpha" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5 };
		static mud::BlendMode vars[] = { mud::BlendMode::Mix, mud::BlendMode::Add, mud::BlendMode::Sub, mud::BlendMode::Mul, mud::BlendMode::Normal, mud::BlendMode::Alpha};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_BlendMode__to_string,
		                           mud_BlendMode__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::CullMode>();
		static Meta meta = { t, &namspc({ "mud" }), "CullMode", sizeof(mud::CullMode), TypeClass::Enum };
		static cstring ids[] = { "None", "Front", "Back" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::CullMode vars[] = { mud::CullMode::None, mud::CullMode::Front, mud::CullMode::Back};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_CullMode__to_string,
		                           mud_CullMode__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::DepthDraw>();
		static Meta meta = { t, &namspc({ "mud" }), "DepthDraw", sizeof(mud::DepthDraw), TypeClass::Enum };
		static cstring ids[] = { "Enabled", "Disabled" };
		static uint32_t values[] = { 0, 1 };
		static mud::DepthDraw vars[] = { mud::DepthDraw::Enabled, mud::DepthDraw::Disabled};
		static void* refs[] = { &vars[0], &vars[1]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_DepthDraw__to_string,
		                           mud_DepthDraw__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::DepthTest>();
		static Meta meta = { t, &namspc({ "mud" }), "DepthTest", sizeof(mud::DepthTest), TypeClass::Enum };
		static cstring ids[] = { "Enabled", "Disabled" };
		static uint32_t values[] = { 0, 1 };
		static mud::DepthTest vars[] = { mud::DepthTest::Enabled, mud::DepthTest::Disabled};
		static void* refs[] = { &vars[0], &vars[1]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_DepthTest__to_string,
		                           mud_DepthTest__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::EmitterFlow>();
		static Meta meta = { t, &namspc({ "mud" }), "EmitterFlow", sizeof(mud::EmitterFlow), TypeClass::Enum };
		static cstring ids[] = { "Outward", "Absolute" };
		static uint32_t values[] = { 0, 1 };
		static mud::EmitterFlow vars[] = { mud::EmitterFlow::Outward, mud::EmitterFlow::Absolute};
		static void* refs[] = { &vars[0], &vars[1]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_EmitterFlow__to_string,
		                           mud_EmitterFlow__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::Interpolation>();
		static Meta meta = { t, &namspc({ "mud" }), "Interpolation", sizeof(mud::Interpolation), TypeClass::Enum };
		static cstring ids[] = { "Nearest", "Linear", "Cubic" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::Interpolation vars[] = { mud::Interpolation::Nearest, mud::Interpolation::Linear, mud::Interpolation::Cubic};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_Interpolation__to_string,
		                           mud_Interpolation__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::IsometricAngle>();
		static Meta meta = { t, &namspc({ "mud" }), "IsometricAngle", sizeof(mud::IsometricAngle), TypeClass::Enum };
		static cstring ids[] = { "NORTH", "SOUTH", "EAST", "WEST" };
		static uint32_t values[] = { 1, 2, 256, 512 };
		static mud::IsometricAngle vars[] = { mud::NORTH, mud::SOUTH, mud::EAST, mud::WEST};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, false, ids, values, refs };
		static Convert convert = { mud_IsometricAngle__to_string,
		                           mud_IsometricAngle__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::ItemShadow>();
		static Meta meta = { t, &namspc({ "mud" }), "ItemShadow", sizeof(mud::ItemShadow), TypeClass::Enum };
		static cstring ids[] = { "Default", "DoubleSided" };
		static uint32_t values[] = { 0, 1 };
		static mud::ItemShadow vars[] = { mud::ItemShadow::Default, mud::ItemShadow::DoubleSided};
		static void* refs[] = { &vars[0], &vars[1]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_ItemShadow__to_string,
		                           mud_ItemShadow__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::LightType>();
		static Meta meta = { t, &namspc({ "mud" }), "LightType", sizeof(mud::LightType), TypeClass::Enum };
		static cstring ids[] = { "Direct", "Point", "Spot", "Count" };
		static uint32_t values[] = { 0, 1, 2, 3 };
		static mud::LightType vars[] = { mud::LightType::Direct, mud::LightType::Point, mud::LightType::Spot, mud::LightType::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_LightType__to_string,
		                           mud_LightType__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::Lighting>();
		static Meta meta = { t, &namspc({ "mud" }), "Lighting", sizeof(mud::Lighting), TypeClass::Enum };
		static cstring ids[] = { "None", "Clustered", "Deferred", "VoxelGI" };
		static uint32_t values[] = { 0, 1, 2, 4 };
		static mud::Lighting vars[] = { mud::Lighting::None, mud::Lighting::Clustered, mud::Lighting::Deferred, mud::Lighting::VoxelGI};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_Lighting__to_string,
		                           mud_Lighting__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::MSAA>();
		static Meta meta = { t, &namspc({ "mud" }), "MSAA", sizeof(mud::MSAA), TypeClass::Enum };
		static cstring ids[] = { "Disabled", "X2", "X4", "X8", "X16" };
		static uint32_t values[] = { 0, 1, 2, 3, 4 };
		static mud::MSAA vars[] = { mud::MSAA::Disabled, mud::MSAA::X2, mud::MSAA::X4, mud::MSAA::X8, mud::MSAA::X16};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_MSAA__to_string,
		                           mud_MSAA__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::MaterialFlag>();
		static Meta meta = { t, &namspc({ "mud" }), "MaterialFlag", sizeof(mud::MaterialFlag), TypeClass::Enum };
		static cstring ids[] = { "TriplanarUV1", "TriplanarUV2", "Count" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::MaterialFlag vars[] = { mud::MaterialFlag::TriplanarUV1, mud::MaterialFlag::TriplanarUV2, mud::MaterialFlag::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_MaterialFlag__to_string,
		                           mud_MaterialFlag__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::ModelFormat>();
		static Meta meta = { t, &namspc({ "mud" }), "ModelFormat", sizeof(mud::ModelFormat), TypeClass::Enum };
		static cstring ids[] = { "obj", "gltf", "Count" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::ModelFormat vars[] = { mud::ModelFormat::obj, mud::ModelFormat::gltf, mud::ModelFormat::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_ModelFormat__to_string,
		                           mud_ModelFormat__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::Month>();
		static Meta meta = { t, &namspc({ "mud" }), "Month", sizeof(mud::Month), TypeClass::Enum };
		static cstring ids[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
		static mud::Month vars[] = { mud::Month::January, mud::Month::February, mud::Month::March, mud::Month::April, mud::Month::May, mud::Month::June, mud::Month::July, mud::Month::August, mud::Month::September, mud::Month::October, mud::Month::November, mud::Month::December};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7], &vars[8], &vars[9], &vars[10], &vars[11]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_Month__to_string,
		                           mud_Month__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::PbrDiffuseMode>();
		static Meta meta = { t, &namspc({ "mud" }), "PbrDiffuseMode", sizeof(mud::PbrDiffuseMode), TypeClass::Enum };
		static cstring ids[] = { "Lambert", "LambertHalf", "OrenNayar", "Burley", "Toon" };
		static uint32_t values[] = { 0, 1, 2, 3, 4 };
		static mud::PbrDiffuseMode vars[] = { mud::PbrDiffuseMode::Lambert, mud::PbrDiffuseMode::LambertHalf, mud::PbrDiffuseMode::OrenNayar, mud::PbrDiffuseMode::Burley, mud::PbrDiffuseMode::Toon};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_PbrDiffuseMode__to_string,
		                           mud_PbrDiffuseMode__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::PbrSpecularMode>();
		static Meta meta = { t, &namspc({ "mud" }), "PbrSpecularMode", sizeof(mud::PbrSpecularMode), TypeClass::Enum };
		static cstring ids[] = { "SchlickGGX", "Blinn", "Phong", "Toon", "Disabled" };
		static uint32_t values[] = { 0, 1, 2, 3, 4 };
		static mud::PbrSpecularMode vars[] = { mud::PbrSpecularMode::SchlickGGX, mud::PbrSpecularMode::Blinn, mud::PbrSpecularMode::Phong, mud::PbrSpecularMode::Toon, mud::PbrSpecularMode::Disabled};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_PbrSpecularMode__to_string,
		                           mud_PbrSpecularMode__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::ShaderType>();
		static Meta meta = { t, &namspc({ "mud" }), "ShaderType", sizeof(mud::ShaderType), TypeClass::Enum };
		static cstring ids[] = { "Compute", "Fragment", "Geometry", "Vertex", "Count" };
		static uint32_t values[] = { 0, 1, 2, 3, 4 };
		static mud::ShaderType vars[] = { mud::ShaderType::Compute, mud::ShaderType::Fragment, mud::ShaderType::Geometry, mud::ShaderType::Vertex, mud::ShaderType::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_ShaderType__to_string,
		                           mud_ShaderType__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::Shading>();
		static Meta meta = { t, &namspc({ "mud" }), "Shading", sizeof(mud::Shading), TypeClass::Enum };
		static cstring ids[] = { "Wireframe", "Unshaded", "Shaded", "Volume", "Voxels", "Lightmap", "Clear", "Count" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
		static mud::Shading vars[] = { mud::Shading::Wireframe, mud::Shading::Unshaded, mud::Shading::Shaded, mud::Shading::Volume, mud::Shading::Voxels, mud::Shading::Lightmap, mud::Shading::Clear, mud::Shading::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_Shading__to_string,
		                           mud_Shading__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::ShadowFlags>();
		static Meta meta = { t, &namspc({ "mud" }), "ShadowFlags", sizeof(mud::ShadowFlags), TypeClass::Enum };
		static cstring ids[] = { "CSM_Stabilize", "CSM_Optimize", "CSM_BlendSplits" };
		static uint32_t values[] = { 1, 2, 4 };
		static mud::ShadowFlags vars[] = { mud::CSM_Stabilize, mud::CSM_Optimize, mud::CSM_BlendSplits};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, false, ids, values, refs };
		static Convert convert = { mud_ShadowFlags__to_string,
		                           mud_ShadowFlags__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::TextureChannel>();
		static Meta meta = { t, &namspc({ "mud" }), "TextureChannel", sizeof(mud::TextureChannel), TypeClass::Enum };
		static cstring ids[] = { "Red", "Green", "Blue", "Alpha", "All" };
		static uint32_t values[] = { 0, 1, 2, 3, 4 };
		static mud::TextureChannel vars[] = { mud::TextureChannel::Red, mud::TextureChannel::Green, mud::TextureChannel::Blue, mud::TextureChannel::Alpha, mud::TextureChannel::All};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_TextureChannel__to_string,
		                           mud_TextureChannel__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::TextureHint>();
		static Meta meta = { t, &namspc({ "mud" }), "TextureHint", sizeof(mud::TextureHint), TypeClass::Enum };
		static cstring ids[] = { "Black", "White", "Normal" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::TextureHint vars[] = { mud::TextureHint::Black, mud::TextureHint::White, mud::TextureHint::Normal};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_TextureHint__to_string,
		                           mud_TextureHint__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::TextureSampler>();
		static Meta meta = { t, &namspc({ "mud" }), "TextureSampler", sizeof(mud::TextureSampler), TypeClass::Enum };
		static cstring ids[] = { "Source0", "Source1", "Source2", "Source3", "SourceDepth", "Color", "Albedo", "Metallic", "Roughness", "Emissive", "Normal", "AO", "Depth", "Skeleton", "ShadowCSM", "ShadowAtlas", "Radiance", "ReflectionProbe", "GIProbe", "Lights", "Clusters", "LightRecords", "Lightmap" };
		static uint32_t values[] = { 0, 1, 2, 3, 3, 0, 0, 1, 2, 3, 4, 11, 12, 5, 6, 7, 8, 9, 10, 13, 14, 15, 7 };
		static mud::TextureSampler vars[] = { mud::TextureSampler::Source0, mud::TextureSampler::Source1, mud::TextureSampler::Source2, mud::TextureSampler::Source3, mud::TextureSampler::SourceDepth, mud::TextureSampler::Color, mud::TextureSampler::Albedo, mud::TextureSampler::Metallic, mud::TextureSampler::Roughness, mud::TextureSampler::Emissive, mud::TextureSampler::Normal, mud::TextureSampler::AO, mud::TextureSampler::Depth, mud::TextureSampler::Skeleton, mud::TextureSampler::ShadowCSM, mud::TextureSampler::ShadowAtlas, mud::TextureSampler::Radiance, mud::TextureSampler::ReflectionProbe, mud::TextureSampler::GIProbe, mud::TextureSampler::Lights, mud::TextureSampler::Clusters, mud::TextureSampler::LightRecords, mud::TextureSampler::Lightmap};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7], &vars[8], &vars[9], &vars[10], &vars[11], &vars[12], &vars[13], &vars[14], &vars[15], &vars[16], &vars[17], &vars[18], &vars[19], &vars[20], &vars[21], &vars[22]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_TextureSampler__to_string,
		                           mud_TextureSampler__to_value };
		g_convert[t.m_id] = &convert;
	}
	
	// Sequences
	{
		Type& t = type<array<mud::mat4>>();
		static Meta meta = { t, &namspc({}), "array<mud::mat4>", sizeof(array<mud::mat4>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::mat4>(),
		                             array_mud_mat4___size,
		                             array_mud_mat4___at};
		g_iterable[t.m_id] = &iterable;
	}
	{
		Type& t = type<vector<mud::Animation*>>();
		static Meta meta = { t, &namspc({}), "vector<mud::Animation*>", sizeof(vector<mud::Animation*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::Animation>(),
		                             vector_mud_Animation____size,
		                             vector_mud_Animation____at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { vector_mud_Animation____add,
		                             vector_mud_Animation____remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<vector<mud::AnimationPlay>>();
		static Meta meta = { t, &namspc({}), "vector<mud::AnimationPlay>", sizeof(vector<mud::AnimationPlay>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::AnimationPlay>(),
		                             vector_mud_AnimationPlay___size,
		                             vector_mud_AnimationPlay___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { vector_mud_AnimationPlay___add,
		                             vector_mud_AnimationPlay___remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<vector<string>>();
		static Meta meta = { t, &namspc({}), "vector<string>", sizeof(vector<string>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<string>(),
		                             vector_string___size,
		                             vector_string___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { vector_string___add,
		                             vector_string___remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<vector<string>>();
		static Meta meta = { t, &namspc({}), "vector<string>", sizeof(vector<string>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<string>(),
		                             vector_string___size,
		                             vector_string___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { vector_string___add,
		                             vector_string___remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<vector<string>>();
		static Meta meta = { t, &namspc({}), "vector<string>", sizeof(vector<string>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<string>(),
		                             vector_string___size,
		                             vector_string___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { vector_string___add,
		                             vector_string___remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<vector<string>>();
		static Meta meta = { t, &namspc({}), "vector<string>", sizeof(vector<string>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<string>(),
		                             vector_string___size,
		                             vector_string___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { vector_string___add,
		                             vector_string___remove };
		g_sequence[t.m_id] = &sequence;
	}
	
	// mud::Animated
	{
		Type& t = type<mud::Animated>();
		static Meta meta = { t, &namspc({ "mud" }), "Animated", sizeof(mud::Animated), TypeClass::Object };
		// bases
		// defaults
		static bool active_default = true;
		static float speed_scale_default = 1.f;
		static float default_blend_time_default = 1.f;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Animated, m_playing), type<vector<mud::AnimationPlay>>(), "playing", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Animated, m_queue), type<vector<mud::Animation*>>(), "queue", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Animated, m_active), type<bool>(), "active", &active_default, Member::Value, nullptr },
			{ t, offsetof(mud::Animated, m_speed_scale), type<float>(), "speed_scale", &speed_scale_default, Member::Value, nullptr },
			{ t, offsetof(mud::Animated, m_default_blend_time), type<float>(), "default_blend_time", &default_blend_time_default, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "start", Address(), mud_Animated_start, { { "animation", type<const char*>(), Param::Nullable }, { "loop", type<bool>(),  }, { "blend", type<float>(), Param::Default }, { "speed", type<float>(), Param::Default }, { "transient", type<bool>(), Param::Default } }, g_qvoid },
			{ t, "play", Address(), mud_Animated_play, { { "animation", type<mud::Animation>(),  }, { "loop", type<bool>(),  }, { "blend", type<float>(), Param::Default }, { "speed", type<float>(), Param::Default }, { "transient", type<bool>(), Param::Default } }, g_qvoid },
			{ t, "seek", Address(), mud_Animated_seek, { { "time", type<float>(),  } }, g_qvoid },
			{ t, "pause", Address(), mud_Animated_pause, {}, g_qvoid },
			{ t, "stop", Address(), mud_Animated_stop, {}, g_qvoid },
			{ t, "advance", Address(), mud_Animated_advance, { { "time", type<float>(),  } }, g_qvoid },
			{ t, "next_animation", Address(), mud_Animated_next_animation, {}, g_qvoid },
			{ t, "playing", Address(), mud_Animated_playing, {}, { &type<string>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, methods, {}, };
	}
	// mud::AnimatedTrack
	{
		Type& t = type<mud::AnimatedTrack>();
		static Meta meta = { t, &namspc({ "mud" }), "AnimatedTrack", sizeof(mud::AnimatedTrack), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_AnimatedTrack__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_AnimatedTrack__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// mud::Animation
	{
		Type& t = type<mud::Animation>();
		static Meta meta = { t, &namspc({ "mud" }), "Animation", sizeof(mud::Animation), TypeClass::Object };
		// bases
		// defaults
		static float length_default = 1.f;
		static float step_default = 0.1f;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Animation, m_name), type<string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Animation, m_length), type<float>(), "length", &length_default, Member::Value, nullptr },
			{ t, offsetof(mud::Animation, m_step), type<float>(), "step", &step_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// mud::AnimationPlay
	{
		Type& t = type<mud::AnimationPlay>();
		static Meta meta = { t, &namspc({ "mud" }), "AnimationPlay", sizeof(mud::AnimationPlay), TypeClass::Struct };
		// bases
		// defaults
		static const mud::Animation* animation_default = nullptr;
		static bool loop_default = true;
		static float speed_default = 1.f;
		static bool transient_default = false;
		static float fadeout_default = 0.f;
		static float fadeout_left_default = 0.f;
		static float cursor_default = 0.f;
		static bool ended_default = false;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_AnimationPlay__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_AnimationPlay__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::AnimationPlay, m_animation), type<mud::Animation>(), "animation", animation_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::AnimationPlay, m_loop), type<bool>(), "loop", &loop_default, Member::Value, nullptr },
			{ t, offsetof(mud::AnimationPlay, m_speed), type<float>(), "speed", &speed_default, Member::Value, nullptr },
			{ t, offsetof(mud::AnimationPlay, m_transient), type<bool>(), "transient", &transient_default, Member::Value, nullptr },
			{ t, offsetof(mud::AnimationPlay, m_fadeout), type<float>(), "fadeout", &fadeout_default, Member::Value, nullptr },
			{ t, offsetof(mud::AnimationPlay, m_fadeout_left), type<float>(), "fadeout_left", &fadeout_left_default, Member::Value, nullptr },
			{ t, offsetof(mud::AnimationPlay, m_cursor), type<float>(), "cursor", &cursor_default, Member::Value, nullptr },
			{ t, offsetof(mud::AnimationPlay, m_ended), type<bool>(), "ended", &ended_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::AnimationTrack
	{
		Type& t = type<mud::AnimationTrack>();
		static Meta meta = { t, &namspc({ "mud" }), "AnimationTrack", sizeof(mud::AnimationTrack), TypeClass::Object };
		// bases
		// defaults
		static mud::Type* value_type_default = nullptr;
		static float length_default = 0.f;
		static mud::Interpolation interpolation_default = mud::Interpolation::Linear;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::AnimationTrack, m_animation), type<mud::Animation>(), "animation", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::AnimationTrack, m_node), type<size_t>(), "node", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::AnimationTrack, m_node_name), type<string>(), "node_name", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::AnimationTrack, m_target), type<mud::AnimationTarget>(), "target", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::AnimationTrack, m_value_type), type<mud::Type>(), "value_type", value_type_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::AnimationTrack, m_length), type<float>(), "length", &length_default, Member::Value, nullptr },
			{ t, offsetof(mud::AnimationTrack, m_interpolation), type<mud::Interpolation>(), "interpolation", &interpolation_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// mud::AssetStore<mud::Material>
	{
		Type& t = type<mud::AssetStore<mud::Material>>();
		static Meta meta = { t, &namspc({ "mud" }), "AssetStore<mud::Material>", sizeof(mud::AssetStore<mud::Material>), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "get", Address(), mud_AssetStore_mud_Material__get, { { "name", type<string>(),  } }, { &type<mud::Material>(), QualType::None } },
			{ t, "create", Address(), mud_AssetStore_mud_Material__create, { { "name", type<string>(),  } }, { &type<mud::Material>(), QualType::None } },
			{ t, "fetch", Address(), mud_AssetStore_mud_Material__fetch, { { "name", type<string>(),  } }, { &type<mud::Material>(), QualType::None } },
			{ t, "file", Address(), mud_AssetStore_mud_Material__file, { { "name", type<string>(),  } }, { &type<mud::Material>(), QualType::None } },
			{ t, "file_at", Address(), mud_AssetStore_mud_Material__file_at, { { "path", type<string>(),  }, { "name", type<string>(),  } }, { &type<mud::Material>(), QualType::None } },
			{ t, "destroy", Address(), mud_AssetStore_mud_Material__destroy, { { "name", type<string>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, methods, {}, };
	}
	// mud::AssetStore<mud::Model>
	{
		Type& t = type<mud::AssetStore<mud::Model>>();
		static Meta meta = { t, &namspc({ "mud" }), "AssetStore<mud::Model>", sizeof(mud::AssetStore<mud::Model>), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "get", Address(), mud_AssetStore_mud_Model__get, { { "name", type<string>(),  } }, { &type<mud::Model>(), QualType::None } },
			{ t, "create", Address(), mud_AssetStore_mud_Model__create, { { "name", type<string>(),  } }, { &type<mud::Model>(), QualType::None } },
			{ t, "fetch", Address(), mud_AssetStore_mud_Model__fetch, { { "name", type<string>(),  } }, { &type<mud::Model>(), QualType::None } },
			{ t, "file", Address(), mud_AssetStore_mud_Model__file, { { "name", type<string>(),  } }, { &type<mud::Model>(), QualType::None } },
			{ t, "file_at", Address(), mud_AssetStore_mud_Model__file_at, { { "path", type<string>(),  }, { "name", type<string>(),  } }, { &type<mud::Model>(), QualType::None } },
			{ t, "destroy", Address(), mud_AssetStore_mud_Model__destroy, { { "name", type<string>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, methods, {}, };
	}
	// mud::AssetStore<mud::ParticleFlow>
	{
		Type& t = type<mud::AssetStore<mud::ParticleFlow>>();
		static Meta meta = { t, &namspc({ "mud" }), "AssetStore<mud::ParticleFlow>", sizeof(mud::AssetStore<mud::ParticleFlow>), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "get", Address(), mud_AssetStore_mud_ParticleFlow__get, { { "name", type<string>(),  } }, { &type<mud::ParticleFlow>(), QualType::None } },
			{ t, "create", Address(), mud_AssetStore_mud_ParticleFlow__create, { { "name", type<string>(),  } }, { &type<mud::ParticleFlow>(), QualType::None } },
			{ t, "fetch", Address(), mud_AssetStore_mud_ParticleFlow__fetch, { { "name", type<string>(),  } }, { &type<mud::ParticleFlow>(), QualType::None } },
			{ t, "file", Address(), mud_AssetStore_mud_ParticleFlow__file, { { "name", type<string>(),  } }, { &type<mud::ParticleFlow>(), QualType::None } },
			{ t, "file_at", Address(), mud_AssetStore_mud_ParticleFlow__file_at, { { "path", type<string>(),  }, { "name", type<string>(),  } }, { &type<mud::ParticleFlow>(), QualType::None } },
			{ t, "destroy", Address(), mud_AssetStore_mud_ParticleFlow__destroy, { { "name", type<string>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, methods, {}, };
	}
	// mud::AssetStore<mud::Prefab>
	{
		Type& t = type<mud::AssetStore<mud::Prefab>>();
		static Meta meta = { t, &namspc({ "mud" }), "AssetStore<mud::Prefab>", sizeof(mud::AssetStore<mud::Prefab>), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "get", Address(), mud_AssetStore_mud_Prefab__get, { { "name", type<string>(),  } }, { &type<mud::Prefab>(), QualType::None } },
			{ t, "create", Address(), mud_AssetStore_mud_Prefab__create, { { "name", type<string>(),  } }, { &type<mud::Prefab>(), QualType::None } },
			{ t, "fetch", Address(), mud_AssetStore_mud_Prefab__fetch, { { "name", type<string>(),  } }, { &type<mud::Prefab>(), QualType::None } },
			{ t, "file", Address(), mud_AssetStore_mud_Prefab__file, { { "name", type<string>(),  } }, { &type<mud::Prefab>(), QualType::None } },
			{ t, "file_at", Address(), mud_AssetStore_mud_Prefab__file_at, { { "path", type<string>(),  }, { "name", type<string>(),  } }, { &type<mud::Prefab>(), QualType::None } },
			{ t, "destroy", Address(), mud_AssetStore_mud_Prefab__destroy, { { "name", type<string>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, methods, {}, };
	}
	// mud::AssetStore<mud::Program>
	{
		Type& t = type<mud::AssetStore<mud::Program>>();
		static Meta meta = { t, &namspc({ "mud" }), "AssetStore<mud::Program>", sizeof(mud::AssetStore<mud::Program>), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "get", Address(), mud_AssetStore_mud_Program__get, { { "name", type<string>(),  } }, { &type<mud::Program>(), QualType::None } },
			{ t, "create", Address(), mud_AssetStore_mud_Program__create, { { "name", type<string>(),  } }, { &type<mud::Program>(), QualType::None } },
			{ t, "fetch", Address(), mud_AssetStore_mud_Program__fetch, { { "name", type<string>(),  } }, { &type<mud::Program>(), QualType::None } },
			{ t, "file", Address(), mud_AssetStore_mud_Program__file, { { "name", type<string>(),  } }, { &type<mud::Program>(), QualType::None } },
			{ t, "file_at", Address(), mud_AssetStore_mud_Program__file_at, { { "path", type<string>(),  }, { "name", type<string>(),  } }, { &type<mud::Program>(), QualType::None } },
			{ t, "destroy", Address(), mud_AssetStore_mud_Program__destroy, { { "name", type<string>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, methods, {}, };
	}
	// mud::AssetStore<mud::Texture>
	{
		Type& t = type<mud::AssetStore<mud::Texture>>();
		static Meta meta = { t, &namspc({ "mud" }), "AssetStore<mud::Texture>", sizeof(mud::AssetStore<mud::Texture>), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "get", Address(), mud_AssetStore_mud_Texture__get, { { "name", type<string>(),  } }, { &type<mud::Texture>(), QualType::None } },
			{ t, "create", Address(), mud_AssetStore_mud_Texture__create, { { "name", type<string>(),  } }, { &type<mud::Texture>(), QualType::None } },
			{ t, "fetch", Address(), mud_AssetStore_mud_Texture__fetch, { { "name", type<string>(),  } }, { &type<mud::Texture>(), QualType::None } },
			{ t, "file", Address(), mud_AssetStore_mud_Texture__file, { { "name", type<string>(),  } }, { &type<mud::Texture>(), QualType::None } },
			{ t, "file_at", Address(), mud_AssetStore_mud_Texture__file_at, { { "path", type<string>(),  }, { "name", type<string>(),  } }, { &type<mud::Texture>(), QualType::None } },
			{ t, "destroy", Address(), mud_AssetStore_mud_Texture__destroy, { { "name", type<string>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, methods, {}, };
	}
	// mud::Background
	{
		Type& t = type<mud::Background>();
		static Meta meta = { t, &namspc({ "mud" }), "Background", sizeof(mud::Background), TypeClass::Struct };
		// bases
		// defaults
		static mud::BackgroundMode mode_default = mud::BackgroundMode::None;
		static mud::Colour colour_default = mud::Colour::Black;
		static mud::Program* custoprogram_default = nullptr;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Background__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Background__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Background, m_mode), type<mud::BackgroundMode>(), "mode", &mode_default, Member::Value, nullptr },
			{ t, offsetof(mud::Background, m_colour), type<mud::Colour>(), "colour", &colour_default, Member::Value, nullptr },
			{ t, offsetof(mud::Background, m_custom_program), type<mud::Program>(), "custoprogram", custoprogram_default, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::BaseMaterialBlock
	{
		Type& t = type<mud::BaseMaterialBlock>();
		static Meta meta = { t, &namspc({ "mud" }), "BaseMaterialBlock", sizeof(mud::BaseMaterialBlock), TypeClass::Struct };
		// bases
		// defaults
		static mud::BlendMode blend_mode_default = mud::BlendMode::Mix;
		static mud::CullMode cull_mode_default = mud::CullMode::Back;
		static mud::DepthDraw depth_draw_mode_default = mud::DepthDraw::Enabled;
		static mud::DepthTest depth_test_default = mud::DepthTest::Enabled;
		static mud::vec2 uv0_scale_default = {1.f,1.f};
		static mud::vec2 uv0_offset_default = {0.f,0.f};
		static mud::vec2 uv1_scale_default = {1.f,1.f};
		static mud::vec2 uv1_offset_default = {0.f,0.f};
		static bool is_alpha_default = false;
		static bool screen_filter_default = false;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_BaseMaterialBlock__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_BaseMaterialBlock__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::BaseMaterialBlock, m_blend_mode), type<mud::BlendMode>(), "blend_mode", &blend_mode_default, Member::Value, nullptr },
			{ t, offsetof(mud::BaseMaterialBlock, m_cull_mode), type<mud::CullMode>(), "cull_mode", &cull_mode_default, Member::Value, nullptr },
			{ t, offsetof(mud::BaseMaterialBlock, m_depth_draw_mode), type<mud::DepthDraw>(), "depth_draw_mode", &depth_draw_mode_default, Member::Value, nullptr },
			{ t, offsetof(mud::BaseMaterialBlock, m_depth_test), type<mud::DepthTest>(), "depth_test", &depth_test_default, Member::Value, nullptr },
			{ t, offsetof(mud::BaseMaterialBlock, m_uv0_scale), type<mud::vec2>(), "uv0_scale", &uv0_scale_default, Member::Value, nullptr },
			{ t, offsetof(mud::BaseMaterialBlock, m_uv0_offset), type<mud::vec2>(), "uv0_offset", &uv0_offset_default, Member::Value, nullptr },
			{ t, offsetof(mud::BaseMaterialBlock, m_uv1_scale), type<mud::vec2>(), "uv1_scale", &uv1_scale_default, Member::Value, nullptr },
			{ t, offsetof(mud::BaseMaterialBlock, m_uv1_offset), type<mud::vec2>(), "uv1_offset", &uv1_offset_default, Member::Value, nullptr },
			{ t, offsetof(mud::BaseMaterialBlock, m_is_alpha), type<bool>(), "is_alpha", &is_alpha_default, Member::Value, nullptr },
			{ t, offsetof(mud::BaseMaterialBlock, m_screen_filter), type<bool>(), "screen_filter", &screen_filter_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Bone
	{
		Type& t = type<mud::Bone>();
		static Meta meta = { t, &namspc({ "mud" }), "Bone", sizeof(mud::Bone), TypeClass::Struct };
		// bases
		// defaults
		static mud::vec3 position_default = Zero3;
		static mud::quat rotation_default = ZeroQuat;
		static mud::vec3 scale_default = Unit3;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Bone__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Bone__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Bone, m_position), type<mud::vec3>(), "position", &position_default, Member::Value, nullptr },
			{ t, offsetof(mud::Bone, m_rotation), type<mud::quat>(), "rotation", &rotation_default, Member::Value, nullptr },
			{ t, offsetof(mud::Bone, m_scale), type<mud::vec3>(), "scale", &scale_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Camera
	{
		Type& t = type<mud::Camera>();
		static Meta meta = { t, &namspc({ "mud" }), "Camera", sizeof(mud::Camera), TypeClass::Object };
		// bases
		// defaults
		static float fov_default = 60.f;
		static float aspect_default = 1.f;
		static float near_default = 0.1f;
		static float far_default = 100.f;
		static bool orthographic_default = false;
		static float height_default = 1.f;
		static bool optimize_ends_default = true;
		static bool clustered_default = false;
		static mud::vec4 lod_offsets_default = {0.1f,0.3f,0.6f,0.8f};
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Camera, m_eye), type<mud::vec3>(), "eye", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Camera, m_target), type<mud::vec3>(), "target", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Camera, m_transform), type<mud::mat4>(), "transform", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Camera, m_projection), type<mud::mat4>(), "projection", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Camera, m_fov), type<float>(), "fov", &fov_default, Member::Value, nullptr },
			{ t, offsetof(mud::Camera, m_aspect), type<float>(), "aspect", &aspect_default, Member::Value, nullptr },
			{ t, offsetof(mud::Camera, m_near), type<float>(), "near", &near_default, Member::Value, nullptr },
			{ t, offsetof(mud::Camera, m_far), type<float>(), "far", &far_default, Member::Value, nullptr },
			{ t, offsetof(mud::Camera, m_orthographic), type<bool>(), "orthographic", &orthographic_default, Member::Value, nullptr },
			{ t, offsetof(mud::Camera, m_height), type<float>(), "height", &height_default, Member::Value, nullptr },
			{ t, offsetof(mud::Camera, m_optimize_ends), type<bool>(), "optimize_ends", &optimize_ends_default, Member::Value, nullptr },
			{ t, offsetof(mud::Camera, m_clustered), type<bool>(), "clustered", &clustered_default, Member::Value, nullptr },
			{ t, offsetof(mud::Camera, m_lod_offsets), type<mud::vec4>(), "lod_offsets", &lod_offsets_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// mud::Culler
	{
		Type& t = type<mud::Culler>();
		static Meta meta = { t, &namspc({ "mud" }), "Culler", sizeof(mud::Culler), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Culler, m_viewport), type<mud::Viewport>(), "viewport", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// mud::DepthParams
	{
		Type& t = type<mud::DepthParams>();
		static Meta meta = { t, &namspc({ "mud" }), "DepthParams", sizeof(mud::DepthParams), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_DepthParams__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_DepthParams__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// mud::Environment
	{
		Type& t = type<mud::Environment>();
		static Meta meta = { t, &namspc({ "mud" }), "Environment", sizeof(mud::Environment), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Environment__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Environment__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Environment, m_background), type<mud::Background>(), "background", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Environment, m_radiance), type<mud::Radiance>(), "radiance", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Environment, m_sun), type<mud::Sun>(), "sun", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Environment, m_fog), type<mud::Fog>(), "fog", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Filter
	{
		Type& t = type<mud::Filter>();
		static Meta meta = { t, &namspc({ "mud" }), "Filter", sizeof(mud::Filter), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::Fog
	{
		Type& t = type<mud::Fog>();
		static Meta meta = { t, &namspc({ "mud" }), "Fog", sizeof(mud::Fog), TypeClass::Struct };
		// bases
		// defaults
		static bool enabled_default = false;
		static float density_default = 0.01f;
		static mud::Colour colour_default = mud::Colour::White;
		static bool depth_default = false;
		static float depth_begin_default = 0.f;
		static float depth_curve_default = 1.f;
		static bool height_default = false;
		static float height_min_default = 0.f;
		static float height_max_default = 1.f;
		static float height_curve_default = 0.1f;
		static bool transmit_default = false;
		static float transmit_curve_default = 1.f;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Fog__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Fog__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Fog, m_enabled), type<bool>(), "enabled", &enabled_default, Member::Value, nullptr },
			{ t, offsetof(mud::Fog, m_density), type<float>(), "density", &density_default, Member::Value, nullptr },
			{ t, offsetof(mud::Fog, m_colour), type<mud::Colour>(), "colour", &colour_default, Member::Value, nullptr },
			{ t, offsetof(mud::Fog, m_depth), type<bool>(), "depth", &depth_default, Member::Value, nullptr },
			{ t, offsetof(mud::Fog, m_depth_begin), type<float>(), "depth_begin", &depth_begin_default, Member::Value, nullptr },
			{ t, offsetof(mud::Fog, m_depth_curve), type<float>(), "depth_curve", &depth_curve_default, Member::Value, nullptr },
			{ t, offsetof(mud::Fog, m_height), type<bool>(), "height", &height_default, Member::Value, nullptr },
			{ t, offsetof(mud::Fog, m_height_min), type<float>(), "height_min", &height_min_default, Member::Value, nullptr },
			{ t, offsetof(mud::Fog, m_height_max), type<float>(), "height_max", &height_max_default, Member::Value, nullptr },
			{ t, offsetof(mud::Fog, m_height_curve), type<float>(), "height_curve", &height_curve_default, Member::Value, nullptr },
			{ t, offsetof(mud::Fog, m_transmit), type<bool>(), "transmit", &transmit_default, Member::Value, nullptr },
			{ t, offsetof(mud::Fog, m_transmit_curve), type<float>(), "transmit_curve", &transmit_curve_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::FrameBuffer
	{
		Type& t = type<mud::FrameBuffer>();
		static Meta meta = { t, &namspc({ "mud" }), "FrameBuffer", sizeof(mud::FrameBuffer), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::FresnelMaterialBlock
	{
		Type& t = type<mud::FresnelMaterialBlock>();
		static Meta meta = { t, &namspc({ "mud" }), "FresnelMaterialBlock", sizeof(mud::FresnelMaterialBlock), TypeClass::Struct };
		// bases
		// defaults
		static bool enabled_default = false;
		static mud::MaterialParam<mud::Colour> value_default = {Colour::White,nullptr};
		static float fresnel_scale_default = 1.f;
		static float fresnel_bias_default = 0.01f;
		static float fresnel_power_default = 5.f;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_FresnelMaterialBlock__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_FresnelMaterialBlock__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::FresnelMaterialBlock, m_enabled), type<bool>(), "enabled", &enabled_default, Member::Value, nullptr },
			{ t, offsetof(mud::FresnelMaterialBlock, m_value), type<mud::MaterialParam<mud::Colour>>(), "value", &value_default, Member::Value, nullptr },
			{ t, offsetof(mud::FresnelMaterialBlock, m_fresnel_scale), type<float>(), "fresnel_scale", &fresnel_scale_default, Member::Value, nullptr },
			{ t, offsetof(mud::FresnelMaterialBlock, m_fresnel_bias), type<float>(), "fresnel_bias", &fresnel_bias_default, Member::Value, nullptr },
			{ t, offsetof(mud::FresnelMaterialBlock, m_fresnel_power), type<float>(), "fresnel_power", &fresnel_power_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Frustum
	{
		Type& t = type<mud::Frustum>();
		static Meta meta = { t, &namspc({ "mud" }), "Frustum", sizeof(mud::Frustum), TypeClass::Object };
		// bases
		// defaults
		static float fov_default = 60.f;
		static float aspect_default = 1.f;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Frustum, m_fov), type<float>(), "fov", &fov_default, Member::Value, nullptr },
			{ t, offsetof(mud::Frustum, m_aspect), type<float>(), "aspect", &aspect_default, Member::Value, nullptr },
			{ t, offsetof(mud::Frustum, m_near), type<float>(), "near", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Frustum, m_far), type<float>(), "far", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Frustum, m_center), type<mud::vec3>(), "center", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Frustum, m_radius), type<float>(), "radius", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// mud::FrustumSlice
	{
		Type& t = type<mud::FrustumSlice>();
		static Meta meta = { t, &namspc({ "mud" }), "FrustumSlice", sizeof(mud::FrustumSlice), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_FrustumSlice__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_FrustumSlice__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// mud::GfxBlock
	{
		Type& t = type<mud::GfxBlock>();
		static Meta meta = { t, &namspc({ "mud" }), "GfxBlock", sizeof(mud::GfxBlock), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, SIZE_MAX, type<mud::Type>(), "type", nullptr, Member::Flags(Member::NonMutable|Member::Link), mud_GfxBlock__get_type },
			{ t, offsetof(mud::GfxBlock, m_index), type<uint8_t>(), "index", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// mud::GfxContext
	{
		Type& t = type<mud::GfxContext>();
		static Meta meta = { t, &namspc({ "mud" }), "GfxContext", sizeof(mud::GfxContext), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::GfxSystem
	{
		Type& t = type<mud::GfxSystem>();
		static Meta meta = { t, &namspc({ "mud" }), "GfxSystem", sizeof(mud::GfxSystem), TypeClass::Object };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_GfxSystem__construct_0, { { "resource_path", type<string>(),  } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, SIZE_MAX, type<mud::AssetStore<mud::Texture>>(), "textures", nullptr, Member::Flags(Member::NonMutable|Member::Link), mud_GfxSystem__get_textures },
			{ t, SIZE_MAX, type<mud::AssetStore<mud::Program>>(), "programs", nullptr, Member::Flags(Member::NonMutable|Member::Link), mud_GfxSystem__get_programs },
			{ t, SIZE_MAX, type<mud::AssetStore<mud::Material>>(), "materials", nullptr, Member::Flags(Member::NonMutable|Member::Link), mud_GfxSystem__get_materials },
			{ t, SIZE_MAX, type<mud::AssetStore<mud::Model>>(), "models", nullptr, Member::Flags(Member::NonMutable|Member::Link), mud_GfxSystem__get_models },
			{ t, SIZE_MAX, type<mud::AssetStore<mud::ParticleFlow>>(), "particles", nullptr, Member::Flags(Member::NonMutable|Member::Link), mud_GfxSystem__get_particles },
			{ t, SIZE_MAX, type<mud::AssetStore<mud::Prefab>>(), "prefabs", nullptr, Member::Flags(Member::NonMutable|Member::Link), mud_GfxSystem__get_prefabs }
		};
		// methods
		static Method methods[] = {
			{ t, "default_pipeline", Address(), mud_GfxSystem_default_pipeline, {}, g_qvoid },
			{ t, "add_resource_path", Address(), mud_GfxSystem_add_resource_path, { { "path", type<string>(),  }, { "relative", type<bool>(), Param::Default } }, g_qvoid },
			{ t, "debug_material", Address(), mud_GfxSystem_debug_material, {}, { &type<mud::Material>(), QualType::None } },
			{ t, "fetch_material", Address(), mud_GfxSystem_fetch_material, { { "name", type<string>(),  }, { "shader", type<string>(),  }, { "builtin", type<bool>(), Param::Default } }, { &type<mud::Material>(), QualType::None } },
			{ t, "fetch_image256_material", Address(), mud_GfxSystem_fetch_image256_material, { { "image", type<mud::Image256>(),  } }, { &type<mud::Material>(), QualType::None } },
			{ t, "fetch_symbol", Address(), mud_GfxSystem_fetch_symbol, { { "symbol", type<mud::Symbol>(),  }, { "shape", type<mud::Shape>(),  }, { "draw_mode", type<mud::DrawMode>(),  } }, { &type<mud::Model>(), QualType::None } },
			{ t, "fetch_symbol_material", Address(), mud_GfxSystem_fetch_symbol_material, { { "symbol", type<mud::Symbol>(),  }, { "draw_mode", type<mud::DrawMode>(),  } }, { &type<mud::Material>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, members, methods, {}, };
	}
	// mud::Gnode
	{
		Type& t = type<mud::Gnode>();
		static Meta meta = { t, &namspc({ "mud" }), "Gnode", sizeof(mud::Gnode), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::ImmediateDraw
	{
		Type& t = type<mud::ImmediateDraw>();
		static Meta meta = { t, &namspc({ "mud" }), "ImmediateDraw", sizeof(mud::ImmediateDraw), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::ImportConfig
	{
		Type& t = type<mud::ImportConfig>();
		static Meta meta = { t, &namspc({ "mud" }), "ImportConfig", sizeof(mud::ImportConfig), TypeClass::Struct };
		// bases
		// defaults
		static mud::ModelFormat format_default = mud::ModelFormat::obj;
		static mud::vec3 position_default = Zero3;
		static mud::quat rotation_default = ZeroQuat;
		static mud::vec3 scale_default = Unit3;
		static mud::mat4 transform_default = bxidentity();
		static vector<string> exclude_elements_default = {};
		static vector<string> exclude_materials_default = {};
		static vector<string> include_elements_default = {};
		static vector<string> include_materials_default = {};
		static bool force_reimport_default = false;
		static bool cache_geometry_default = false;
		static bool optimize_geometry_default = false;
		static uint32_t flags_default = ItemFlag::None;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ImportConfig__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_ImportConfig__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::ImportConfig, m_format), type<mud::ModelFormat>(), "format", &format_default, Member::Value, nullptr },
			{ t, offsetof(mud::ImportConfig, m_position), type<mud::vec3>(), "position", &position_default, Member::Value, nullptr },
			{ t, offsetof(mud::ImportConfig, m_rotation), type<mud::quat>(), "rotation", &rotation_default, Member::Value, nullptr },
			{ t, offsetof(mud::ImportConfig, m_scale), type<mud::vec3>(), "scale", &scale_default, Member::Value, nullptr },
			{ t, offsetof(mud::ImportConfig, m_transform), type<mud::mat4>(), "transform", &transform_default, Member::Value, nullptr },
			{ t, offsetof(mud::ImportConfig, m_exclude_elements), type<vector<string>>(), "exclude_elements", &exclude_elements_default, Member::Value, nullptr },
			{ t, offsetof(mud::ImportConfig, m_exclude_materials), type<vector<string>>(), "exclude_materials", &exclude_materials_default, Member::Value, nullptr },
			{ t, offsetof(mud::ImportConfig, m_include_elements), type<vector<string>>(), "include_elements", &include_elements_default, Member::Value, nullptr },
			{ t, offsetof(mud::ImportConfig, m_include_materials), type<vector<string>>(), "include_materials", &include_materials_default, Member::Value, nullptr },
			{ t, offsetof(mud::ImportConfig, m_suffix), type<string>(), "suffix", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::ImportConfig, m_force_reimport), type<bool>(), "force_reimport", &force_reimport_default, Member::Value, nullptr },
			{ t, offsetof(mud::ImportConfig, m_cache_geometry), type<bool>(), "cache_geometry", &cache_geometry_default, Member::Value, nullptr },
			{ t, offsetof(mud::ImportConfig, m_optimize_geometry), type<bool>(), "optimize_geometry", &optimize_geometry_default, Member::Value, nullptr },
			{ t, offsetof(mud::ImportConfig, m_flags), type<uint32_t>(), "flags", &flags_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Item
	{
		Type& t = type<mud::Item>();
		static Meta meta = { t, &namspc({ "mud" }), "Item", sizeof(mud::Item), TypeClass::Object };
		// bases
		// defaults
		static mud::Model* model_default = nullptr;
		static uint32_t flags_default = 0;
		static mud::Colour colour_default = mud::Colour::White;
		static mud::Material* material_default = nullptr;
		static bool visible_default = true;
		static mud::ItemShadow shadow_default = mud::ItemShadow::Default;
		static mud::Rig* rig_default = nullptr;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Item, m_node), type<mud::Node3>(), "node", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::Item, m_model), type<mud::Model>(), "model", model_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::Item, m_flags), type<uint32_t>(), "flags", &flags_default, Member::Value, nullptr },
			{ t, offsetof(mud::Item, m_colour), type<mud::Colour>(), "colour", &colour_default, Member::Value, nullptr },
			{ t, offsetof(mud::Item, m_material), type<mud::Material>(), "material", material_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::Item, m_visible), type<bool>(), "visible", &visible_default, Member::Value, nullptr },
			{ t, offsetof(mud::Item, m_shadow), type<mud::ItemShadow>(), "shadow", &shadow_default, Member::Value, nullptr },
			{ t, offsetof(mud::Item, m_rig), type<mud::Rig>(), "rig", rig_default, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// mud::Joint
	{
		Type& t = type<mud::Joint>();
		static Meta meta = { t, &namspc({ "mud" }), "Joint", sizeof(mud::Joint), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Joint__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Joint__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// mud::Light
	{
		Type& t = type<mud::Light>();
		static Meta meta = { t, &namspc({ "mud" }), "Light", sizeof(mud::Light), TypeClass::Object };
		// bases
		// defaults
		static mud::LightType type_default = mud::LightType::Point;
		static bool visible_default = true;
		static mud::Colour colour_default = mud::Colour::White;
		static float range_default = 1.f;
		static float energy_default = 1.f;
		static float specular_default = 0.5f;
		static float attenuation_default = 0.5f;
		static bool shadows_default = false;
		static mud::Colour shadow_colour_default = mud::Colour::Black;
		static float shadow_range_default = 100.f;
		static uint32_t layers_default = 0xFFFFFFFF;
		static uint32_t last_render_default = 0;
		static uint32_t last_update_default = 0;
		static float spot_angle_default = 45.f;
		static float spot_attenuation_default = 0.5f;
		static uint8_t shadow_nusplits_default = 1;
		static float shadow_split_distribution_default = 0.6f;
		static float shadow_normal_bias_default = 0.1f;
		static float shadow_bias_default = 0.f;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, SIZE_MAX, type<mud::Node3>(), "node", nullptr, Member::Flags(Member::NonMutable|Member::Link), mud_Light__get_node },
			{ t, offsetof(mud::Light, m_type), type<mud::LightType>(), "type", &type_default, Member::Value, nullptr },
			{ t, offsetof(mud::Light, m_visible), type<bool>(), "visible", &visible_default, Member::Value, nullptr },
			{ t, offsetof(mud::Light, m_colour), type<mud::Colour>(), "colour", &colour_default, Member::Value, nullptr },
			{ t, offsetof(mud::Light, m_range), type<float>(), "range", &range_default, Member::Value, nullptr },
			{ t, offsetof(mud::Light, m_energy), type<float>(), "energy", &energy_default, Member::Value, nullptr },
			{ t, offsetof(mud::Light, m_specular), type<float>(), "specular", &specular_default, Member::Value, nullptr },
			{ t, offsetof(mud::Light, m_attenuation), type<float>(), "attenuation", &attenuation_default, Member::Value, nullptr },
			{ t, offsetof(mud::Light, m_shadows), type<bool>(), "shadows", &shadows_default, Member::Value, nullptr },
			{ t, offsetof(mud::Light, m_shadow_colour), type<mud::Colour>(), "shadow_colour", &shadow_colour_default, Member::Value, nullptr },
			{ t, offsetof(mud::Light, m_shadow_range), type<float>(), "shadow_range", &shadow_range_default, Member::Value, nullptr },
			{ t, offsetof(mud::Light, m_layers), type<uint32_t>(), "layers", &layers_default, Member::Value, nullptr },
			{ t, offsetof(mud::Light, m_last_render), type<uint32_t>(), "last_render", &last_render_default, Member::Value, nullptr },
			{ t, offsetof(mud::Light, m_last_update), type<uint32_t>(), "last_update", &last_update_default, Member::Value, nullptr },
			{ t, offsetof(mud::Light, m_spot_angle), type<float>(), "spot_angle", &spot_angle_default, Member::Value, nullptr },
			{ t, offsetof(mud::Light, m_spot_attenuation), type<float>(), "spot_attenuation", &spot_attenuation_default, Member::Value, nullptr },
			{ t, offsetof(mud::Light, m_shadow_flags), type<mud::ShadowFlags>(), "shadow_flags", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Light, m_shadow_num_splits), type<uint8_t>(), "shadow_nusplits", &shadow_nusplits_default, Member::Value, nullptr },
			{ t, offsetof(mud::Light, m_shadow_split_distribution), type<float>(), "shadow_split_distribution", &shadow_split_distribution_default, Member::Value, nullptr },
			{ t, offsetof(mud::Light, m_shadow_normal_bias), type<float>(), "shadow_normal_bias", &shadow_normal_bias_default, Member::Value, nullptr },
			{ t, offsetof(mud::Light, m_shadow_bias), type<float>(), "shadow_bias", &shadow_bias_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// mud::Material
	{
		Type& t = type<mud::Material>();
		static Meta meta = { t, &namspc({ "mud" }), "Material", sizeof(mud::Material), TypeClass::Object };
		// bases
		// defaults
		static uint16_t index_default = 0;
		static bool builtin_default = false;
		static mud::Program* program_default = nullptr;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Material, m_index), type<uint16_t>(), "index", &index_default, Member::Value, nullptr },
			{ t, offsetof(mud::Material, m_name), type<string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Material, m_builtin), type<bool>(), "builtin", &builtin_default, Member::Value, nullptr },
			{ t, offsetof(mud::Material, m_program), type<mud::Program>(), "program", program_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::Material, m_base_block), type<mud::BaseMaterialBlock>(), "base_block", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Material, m_unshaded_block), type<mud::UnshadedMaterialBlock>(), "unshaded_block", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Material, m_pbr_block), type<mud::PbrMaterialBlock>(), "pbr_block", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Material, m_fresnel_block), type<mud::FresnelMaterialBlock>(), "fresnel_block", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// mud::MaterialParam<float>
	{
		Type& t = type<mud::MaterialParam<float>>();
		static Meta meta = { t, &namspc({ "mud" }), "MaterialParam<float>", sizeof(mud::MaterialParam<float>), TypeClass::Struct };
		// bases
		// defaults
		static mud::Texture* texture_default = nullptr;
		static mud::TextureChannel channel_default = mud::TextureChannel::All;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_MaterialParam_float___construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_MaterialParam_float___copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::MaterialParam<float>, m_value), type<float>(), "value", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialParam<float>, m_texture), type<mud::Texture>(), "texture", texture_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::MaterialParam<float>, m_channel), type<mud::TextureChannel>(), "channel", &channel_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::MaterialParam<mud::Colour>
	{
		Type& t = type<mud::MaterialParam<mud::Colour>>();
		static Meta meta = { t, &namspc({ "mud" }), "MaterialParam<mud::Colour>", sizeof(mud::MaterialParam<mud::Colour>), TypeClass::Struct };
		// bases
		// defaults
		static mud::Texture* texture_default = nullptr;
		static mud::TextureChannel channel_default = mud::TextureChannel::All;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_MaterialParam_mud_Colour___construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_MaterialParam_mud_Colour___copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::MaterialParam<mud::Colour>, m_value), type<mud::Colour>(), "value", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialParam<mud::Colour>, m_texture), type<mud::Texture>(), "texture", texture_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::MaterialParam<mud::Colour>, m_channel), type<mud::TextureChannel>(), "channel", &channel_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Mesh
	{
		Type& t = type<mud::Mesh>();
		static Meta meta = { t, &namspc({ "mud" }), "Mesh", sizeof(mud::Mesh), TypeClass::Object };
		// bases
		// defaults
		static mud::DrawMode draw_mode_default = PLAIN;
		static mud::Aabb aabb_default = {};
		static float radius_default = 0.f;
		static mud::vec3 origin_default = Zero3;
		static bool readback_default = false;
		static uint32_t vertex_format_default = 0;
		static bool qnormals_default = false;
		static uint32_t vertex_count_default = 0;
		static uint32_t index_count_default = 0;
		static bool index32_default = false;
		static mud::Material* material_default = nullptr;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Mesh, m_name), type<string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Mesh, m_index), type<uint16_t>(), "index", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Mesh, m_draw_mode), type<mud::DrawMode>(), "draw_mode", &draw_mode_default, Member::Value, nullptr },
			{ t, offsetof(mud::Mesh, m_aabb), type<mud::Aabb>(), "aabb", &aabb_default, Member::Value, nullptr },
			{ t, offsetof(mud::Mesh, m_radius), type<float>(), "radius", &radius_default, Member::Value, nullptr },
			{ t, offsetof(mud::Mesh, m_origin), type<mud::vec3>(), "origin", &origin_default, Member::Value, nullptr },
			{ t, offsetof(mud::Mesh, m_readback), type<bool>(), "readback", &readback_default, Member::Value, nullptr },
			{ t, offsetof(mud::Mesh, m_vertex_format), type<uint32_t>(), "vertex_format", &vertex_format_default, Member::Value, nullptr },
			{ t, offsetof(mud::Mesh, m_qnormals), type<bool>(), "qnormals", &qnormals_default, Member::Value, nullptr },
			{ t, offsetof(mud::Mesh, m_vertex_count), type<uint32_t>(), "vertex_count", &vertex_count_default, Member::Value, nullptr },
			{ t, offsetof(mud::Mesh, m_index_count), type<uint32_t>(), "index_count", &index_count_default, Member::Value, nullptr },
			{ t, offsetof(mud::Mesh, m_index32), type<bool>(), "index32", &index32_default, Member::Value, nullptr },
			{ t, offsetof(mud::Mesh, m_material), type<mud::Material>(), "material", material_default, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// mud::Model
	{
		Type& t = type<mud::Model>();
		static Meta meta = { t, &namspc({ "mud" }), "Model", sizeof(mud::Model), TypeClass::Object };
		// bases
		// defaults
		static mud::Aabb aabb_default = {Zero3,Zero3};
		static float radius_default = 0.f;
		static mud::vec3 origin_default = Zero3;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Model, m_name), type<string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Model, m_index), type<uint16_t>(), "index", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Model, m_aabb), type<mud::Aabb>(), "aabb", &aabb_default, Member::Value, nullptr },
			{ t, offsetof(mud::Model, m_radius), type<float>(), "radius", &radius_default, Member::Value, nullptr },
			{ t, offsetof(mud::Model, m_origin), type<mud::vec3>(), "origin", &origin_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// mud::ModelItem
	{
		Type& t = type<mud::ModelItem>();
		static Meta meta = { t, &namspc({ "mud" }), "ModelItem", sizeof(mud::ModelItem), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ModelItem__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_ModelItem__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::ModelItem, m_index), type<size_t>(), "index", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::ModelItem, m_mesh), type<mud::Mesh>(), "mesh", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::ModelItem, m_has_transform), type<bool>(), "has_transform", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::ModelItem, m_transform), type<mud::mat4>(), "transform", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::ModelItem, m_skin), type<int>(), "skin", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::ModelItem, m_colour), type<mud::Colour>(), "colour", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::ModelItem, m_material), type<mud::Material>(), "material", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Node3
	{
		Type& t = type<mud::Node3>();
		static Meta meta = { t, &namspc({ "mud" }), "Node3", sizeof(mud::Node3), TypeClass::Object };
		// bases
		// defaults
		static mud::Scene* scene_default = nullptr;
		static uint16_t index_default = 0;
		static mud::mat4 transform_default = bxidentity();
		static bool visible_default = true;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Node3, m_scene), type<mud::Scene>(), "scene", scene_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::Node3, m_index), type<uint16_t>(), "index", &index_default, Member::Value, nullptr },
			{ t, offsetof(mud::Node3, m_transform), type<mud::mat4>(), "transform", &transform_default, Member::Value, nullptr },
			{ t, offsetof(mud::Node3, m_visible), type<bool>(), "visible", &visible_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// mud::ParticleFlow
	{
		Type& t = type<mud::ParticleFlow>();
		static Meta meta = { t, &namspc({ "mud" }), "ParticleFlow", sizeof(mud::ParticleFlow), TypeClass::Struct };
		// bases
		// defaults
		static float duration_default = 1.f;
		static float start_time_default = 0.f;
		static bool loop_default = false;
		static mud::ShapeVar shape_default = {};
		static mud::EmitterFlow flow_default = mud::EmitterFlow::Outward;
		static bool billboard_default = true;
		static mud::vec3 direction_default = {0.f,0.f,-1.f};
		static mud::quat rotation_default = ZeroQuat;
		static mud::BlendMode blend_mode_default = mud::BlendMode::Normal;
		static mud::ValueTrack<float> volume_default = {1.f};
		static mud::ValueTrack<uint32_t> rate_default = {0};
		static mud::ValueTrack<float> lifetime_default = {1.f};
		static mud::ValueTrack<float> gravity_default = {0.f};
		static mud::ValueTrack<float> speed_default = {1.f};
		static mud::ValueTrack<float> angle_default = {0.f};
		static mud::ValueTrack<float> blend_default = {vector<float>({0.8f,0.0f})};
		static mud::ValueTrack<mud::Colour> colour_default = {Colour::White};
		static mud::ValueTrack<float> scale_default = {0.1f};
		static mud::ValueTrack<float> sprite_frame_default = {0.f};
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ParticleFlow__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_ParticleFlow__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::ParticleFlow, m_name), type<string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::ParticleFlow, m_duration), type<float>(), "duration", &duration_default, Member::Value, nullptr },
			{ t, offsetof(mud::ParticleFlow, m_start_time), type<float>(), "start_time", &start_time_default, Member::Value, nullptr },
			{ t, offsetof(mud::ParticleFlow, m_loop), type<bool>(), "loop", &loop_default, Member::Value, nullptr },
			{ t, offsetof(mud::ParticleFlow, m_shape), type<mud::ShapeVar>(), "shape", &shape_default, Member::Value, nullptr },
			{ t, offsetof(mud::ParticleFlow, m_flow), type<mud::EmitterFlow>(), "flow", &flow_default, Member::Value, nullptr },
			{ t, offsetof(mud::ParticleFlow, m_billboard), type<bool>(), "billboard", &billboard_default, Member::Value, nullptr },
			{ t, offsetof(mud::ParticleFlow, m_direction), type<mud::vec3>(), "direction", &direction_default, Member::Value, nullptr },
			{ t, offsetof(mud::ParticleFlow, m_rotation), type<mud::quat>(), "rotation", &rotation_default, Member::Value, nullptr },
			{ t, offsetof(mud::ParticleFlow, m_blend_mode), type<mud::BlendMode>(), "blend_mode", &blend_mode_default, Member::Value, nullptr },
			{ t, offsetof(mud::ParticleFlow, m_volume), type<mud::ValueTrack<float>>(), "volume", &volume_default, Member::Value, nullptr },
			{ t, offsetof(mud::ParticleFlow, m_rate), type<mud::ValueTrack<uint32_t>>(), "rate", &rate_default, Member::Value, nullptr },
			{ t, offsetof(mud::ParticleFlow, m_lifetime), type<mud::ValueTrack<float>>(), "lifetime", &lifetime_default, Member::Value, nullptr },
			{ t, offsetof(mud::ParticleFlow, m_gravity), type<mud::ValueTrack<float>>(), "gravity", &gravity_default, Member::Value, nullptr },
			{ t, offsetof(mud::ParticleFlow, m_speed), type<mud::ValueTrack<float>>(), "speed", &speed_default, Member::Value, nullptr },
			{ t, offsetof(mud::ParticleFlow, m_angle), type<mud::ValueTrack<float>>(), "angle", &angle_default, Member::Value, nullptr },
			{ t, offsetof(mud::ParticleFlow, m_blend), type<mud::ValueTrack<float>>(), "blend", &blend_default, Member::Value, nullptr },
			{ t, offsetof(mud::ParticleFlow, m_colour), type<mud::ValueTrack<mud::Colour>>(), "colour", &colour_default, Member::Value, nullptr },
			{ t, offsetof(mud::ParticleFlow, m_scale), type<mud::ValueTrack<float>>(), "scale", &scale_default, Member::Value, nullptr },
			{ t, offsetof(mud::ParticleFlow, m_sprite_frame), type<mud::ValueTrack<float>>(), "sprite_frame", &sprite_frame_default, Member::Value, nullptr },
			{ t, offsetof(mud::ParticleFlow, m_sprite_name), type<string>(), "sprite_name", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::PbrMaterialBlock
	{
		Type& t = type<mud::PbrMaterialBlock>();
		static Meta meta = { t, &namspc({ "mud" }), "PbrMaterialBlock", sizeof(mud::PbrMaterialBlock), TypeClass::Struct };
		// bases
		// defaults
		static bool enabled_default = false;
		static mud::MaterialParam<mud::Colour> albedo_default = {Colour::White,nullptr};
		static float specular_default = 0.5f;
		static mud::MaterialParam<float> metallic_default = {0.f,nullptr,TextureChannel::Red};
		static mud::MaterialParam<float> roughness_default = {1.f,nullptr,TextureChannel::Red};
		static mud::MaterialParam<mud::Colour> emissive_default = {Colour::None,nullptr};
		static float emissive_energy_default = 0.f;
		static mud::MaterialParam<float> normal_default = {1.f,nullptr};
		static mud::MaterialParam<float> depth_default = {-0.02f,nullptr};
		static bool deep_parallax_default = false;
		static mud::PbrDiffuseMode diffuse_mode_default = mud::PbrDiffuseMode::Burley;
		static mud::PbrSpecularMode specular_mode_default = mud::PbrSpecularMode::SchlickGGX;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_PbrMaterialBlock__construct_0, {} },
			{ t, mud_PbrMaterialBlock__construct_1, { { "albedo", type<mud::Colour>(),  }, { "metallic", type<float>(), Param::Default }, { "roughness", type<float>(), Param::Default } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_PbrMaterialBlock__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::PbrMaterialBlock, m_enabled), type<bool>(), "enabled", &enabled_default, Member::Value, nullptr },
			{ t, offsetof(mud::PbrMaterialBlock, m_albedo), type<mud::MaterialParam<mud::Colour>>(), "albedo", &albedo_default, Member::Value, nullptr },
			{ t, offsetof(mud::PbrMaterialBlock, m_specular), type<float>(), "specular", &specular_default, Member::Value, nullptr },
			{ t, offsetof(mud::PbrMaterialBlock, m_metallic), type<mud::MaterialParam<float>>(), "metallic", &metallic_default, Member::Value, nullptr },
			{ t, offsetof(mud::PbrMaterialBlock, m_roughness), type<mud::MaterialParam<float>>(), "roughness", &roughness_default, Member::Value, nullptr },
			{ t, offsetof(mud::PbrMaterialBlock, m_emissive), type<mud::MaterialParam<mud::Colour>>(), "emissive", &emissive_default, Member::Value, nullptr },
			{ t, offsetof(mud::PbrMaterialBlock, m_emissive_energy), type<float>(), "emissive_energy", &emissive_energy_default, Member::Value, nullptr },
			{ t, offsetof(mud::PbrMaterialBlock, m_normal), type<mud::MaterialParam<float>>(), "normal", &normal_default, Member::Value, nullptr },
			{ t, offsetof(mud::PbrMaterialBlock, m_rim), type<mud::MaterialParam<float>>(), "rim", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::PbrMaterialBlock, m_rim_tint), type<float>(), "ritint", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::PbrMaterialBlock, m_clearcoat), type<mud::MaterialParam<float>>(), "clearcoat", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::PbrMaterialBlock, m_clearcoat_gloss), type<float>(), "clearcoat_gloss", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::PbrMaterialBlock, m_anisotropy), type<mud::MaterialParam<float>>(), "anisotropy", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::PbrMaterialBlock, m_subsurface), type<mud::MaterialParam<float>>(), "subsurface", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::PbrMaterialBlock, m_transmission), type<mud::MaterialParam<mud::Colour>>(), "transmission", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::PbrMaterialBlock, m_refraction), type<mud::MaterialParam<float>>(), "refraction", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::PbrMaterialBlock, m_ambient_occlusion), type<mud::MaterialParam<float>>(), "ambient_occlusion", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::PbrMaterialBlock, m_depth), type<mud::MaterialParam<float>>(), "depth", &depth_default, Member::Value, nullptr },
			{ t, offsetof(mud::PbrMaterialBlock, m_deep_parallax), type<bool>(), "deep_parallax", &deep_parallax_default, Member::Value, nullptr },
			{ t, offsetof(mud::PbrMaterialBlock, m_diffuse_mode), type<mud::PbrDiffuseMode>(), "diffuse_mode", &diffuse_mode_default, Member::Value, nullptr },
			{ t, offsetof(mud::PbrMaterialBlock, m_specular_mode), type<mud::PbrSpecularMode>(), "specular_mode", &specular_mode_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Prefab
	{
		Type& t = type<mud::Prefab>();
		static Meta meta = { t, &namspc({ "mud" }), "Prefab", sizeof(mud::Prefab), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Prefab, m_name), type<string>(), "name", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// mud::Program
	{
		Type& t = type<mud::Program>();
		static Meta meta = { t, &namspc({ "mud" }), "Program", sizeof(mud::Program), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::Radiance
	{
		Type& t = type<mud::Radiance>();
		static Meta meta = { t, &namspc({ "mud" }), "Radiance", sizeof(mud::Radiance), TypeClass::Struct };
		// bases
		// defaults
		static float energy_default = 1.0f;
		static float ambient_default = 1.0f;
		static mud::Colour colour_default = mud::Colour::Black;
		static mud::Texture* texture_default = nullptr;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Radiance__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Radiance__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Radiance, m_energy), type<float>(), "energy", &energy_default, Member::Value, nullptr },
			{ t, offsetof(mud::Radiance, m_ambient), type<float>(), "ambient", &ambient_default, Member::Value, nullptr },
			{ t, offsetof(mud::Radiance, m_colour), type<mud::Colour>(), "colour", &colour_default, Member::Value, nullptr },
			{ t, offsetof(mud::Radiance, m_texture), type<mud::Texture>(), "texture", texture_default, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::RenderFrame
	{
		Type& t = type<mud::RenderFrame>();
		static Meta meta = { t, &namspc({ "mud" }), "RenderFrame", sizeof(mud::RenderFrame), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_RenderFrame__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_RenderFrame__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// mud::RenderQuad
	{
		Type& t = type<mud::RenderQuad>();
		static Meta meta = { t, &namspc({ "mud" }), "RenderQuad", sizeof(mud::RenderQuad), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_RenderQuad__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_RenderQuad__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// mud::Rig
	{
		Type& t = type<mud::Rig>();
		static Meta meta = { t, &namspc({ "mud" }), "Rig", sizeof(mud::Rig), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::Scene
	{
		Type& t = type<mud::Scene>();
		static Meta meta = { t, &namspc({ "mud" }), "Scene", sizeof(mud::Scene), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Scene, m_graph), type<mud::Gnode>(), "graph", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::Scene, m_root_node), type<mud::Node3>(), "root_node", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::Scene, m_environment), type<mud::Environment>(), "environment", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Scene, m_user), type<mud::Ref>(), "user", nullptr, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "begin", Address(), mud_Scene_begin, {}, { &type<mud::Gnode>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, methods, {}, };
	}
	// mud::Shot
	{
		Type& t = type<mud::Shot>();
		static Meta meta = { t, &namspc({ "mud" }), "Shot", sizeof(mud::Shot), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::Skeleton
	{
		Type& t = type<mud::Skeleton>();
		static Meta meta = { t, &namspc({ "mud" }), "Skeleton", sizeof(mud::Skeleton), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::Skin
	{
		Type& t = type<mud::Skin>();
		static Meta meta = { t, &namspc({ "mud" }), "Skin", sizeof(mud::Skin), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::Sun
	{
		Type& t = type<mud::Sun>();
		static Meta meta = { t, &namspc({ "mud" }), "Sun", sizeof(mud::Sun), TypeClass::Struct };
		// bases
		// defaults
		static mud::Colour colour_default = {0.8f,0.8f,0.0f};
		static float intensity_default = 0.f;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Sun__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Sun__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Sun, azimuth), type<float>(), "azimuth", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Sun, elevation), type<float>(), "elevation", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Sun, m_colour), type<mud::Colour>(), "colour", &colour_default, Member::Value, nullptr },
			{ t, offsetof(mud::Sun, m_intensity), type<float>(), "intensity", &intensity_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::SymbolIndex
	{
		Type& t = type<mud::SymbolIndex>();
		static Meta meta = { t, &namspc({ "mud" }), "SymbolIndex", sizeof(mud::SymbolIndex), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::Texture
	{
		Type& t = type<mud::Texture>();
		static Meta meta = { t, &namspc({ "mud" }), "Texture", sizeof(mud::Texture), TypeClass::Object };
		// bases
		// defaults
		static uint16_t width_default = 0;
		static uint16_t height_default = 0;
		static uint32_t bits_per_pixel_default = 0;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Texture, m_name), type<string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Texture, m_width), type<uint16_t>(), "width", &width_default, Member::Value, nullptr },
			{ t, offsetof(mud::Texture, m_height), type<uint16_t>(), "height", &height_default, Member::Value, nullptr },
			{ t, offsetof(mud::Texture, m_bits_per_pixel), type<uint32_t>(), "bits_per_pixel", &bits_per_pixel_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// mud::UnshadedMaterialBlock
	{
		Type& t = type<mud::UnshadedMaterialBlock>();
		static Meta meta = { t, &namspc({ "mud" }), "UnshadedMaterialBlock", sizeof(mud::UnshadedMaterialBlock), TypeClass::Struct };
		// bases
		// defaults
		static bool enabled_default = false;
		static mud::MaterialParam<mud::Colour> colour_default = {Colour::White,nullptr};
		// constructors
		static Constructor constructors[] = {
			{ t, mud_UnshadedMaterialBlock__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_UnshadedMaterialBlock__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::UnshadedMaterialBlock, m_enabled), type<bool>(), "enabled", &enabled_default, Member::Value, nullptr },
			{ t, offsetof(mud::UnshadedMaterialBlock, m_colour), type<mud::MaterialParam<mud::Colour>>(), "colour", &colour_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Viewport
	{
		Type& t = type<mud::Viewport>();
		static Meta meta = { t, &namspc({ "mud" }), "Viewport", sizeof(mud::Viewport), TypeClass::Object };
		// bases
		// defaults
		static uint16_t index_default = 0;
		static bool active_default = true;
		static bool scissor_default = false;
		static mud::Colour clear_colour_default = mud::Colour::Black;
		static mud::Shading shading_default = mud::Shading::Shaded;
		static mud::Lighting lighting_default = mud::Lighting::Clustered;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Viewport, m_camera), type<mud::Camera>(), "camera", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::Viewport, m_scene), type<mud::Scene>(), "scene", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::Viewport, m_index), type<uint16_t>(), "index", &index_default, Member::Value, nullptr },
			{ t, offsetof(mud::Viewport, m_active), type<bool>(), "active", &active_default, Member::Value, nullptr },
			{ t, offsetof(mud::Viewport, m_rect), type<mud::uvec4>(), "rect", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Viewport, m_scissor), type<bool>(), "scissor", &scissor_default, Member::Value, nullptr },
			{ t, offsetof(mud::Viewport, m_clear_colour), type<mud::Colour>(), "clear_colour", &clear_colour_default, Member::Value, nullptr },
			{ t, offsetof(mud::Viewport, m_shading), type<mud::Shading>(), "shading", &shading_default, Member::Value, nullptr },
			{ t, offsetof(mud::Viewport, m_lighting), type<mud::Lighting>(), "lighting", &lighting_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// mud::BlockCopy
	{
		Type& t = type<mud::BlockCopy>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockCopy", sizeof(mud::BlockCopy), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::GfxBlock>() };
		static size_t bases_offsets[] = { base_offset<mud::BlockCopy, mud::GfxBlock>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::DrawBlock
	{
		Type& t = type<mud::DrawBlock>();
		static Meta meta = { t, &namspc({ "mud" }), "DrawBlock", sizeof(mud::DrawBlock), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::GfxBlock>() };
		static size_t bases_offsets[] = { base_offset<mud::DrawBlock, mud::GfxBlock>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::BlockDepth
	{
		Type& t = type<mud::BlockDepth>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockDepth", sizeof(mud::BlockDepth), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::DrawBlock>() };
		static size_t bases_offsets[] = { base_offset<mud::BlockDepth, mud::DrawBlock>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::BlockFilter
	{
		Type& t = type<mud::BlockFilter>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockFilter", sizeof(mud::BlockFilter), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::GfxBlock>() };
		static size_t bases_offsets[] = { base_offset<mud::BlockFilter, mud::GfxBlock>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::BlockParticles
	{
		Type& t = type<mud::BlockParticles>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockParticles", sizeof(mud::BlockParticles), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::GfxBlock>() };
		static size_t bases_offsets[] = { base_offset<mud::BlockParticles, mud::GfxBlock>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::BlockResolve
	{
		Type& t = type<mud::BlockResolve>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockResolve", sizeof(mud::BlockResolve), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::GfxBlock>() };
		static size_t bases_offsets[] = { base_offset<mud::BlockResolve, mud::GfxBlock>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::BlockSky
	{
		Type& t = type<mud::BlockSky>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockSky", sizeof(mud::BlockSky), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::GfxBlock>() };
		static size_t bases_offsets[] = { base_offset<mud::BlockSky, mud::GfxBlock>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::ClusteredFrustum
	{
		Type& t = type<mud::ClusteredFrustum>();
		static Meta meta = { t, &namspc({ "mud" }), "ClusteredFrustum", sizeof(mud::ClusteredFrustum), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Frustum>() };
		static size_t bases_offsets[] = { base_offset<mud::ClusteredFrustum, mud::Frustum>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ClusteredFrustum__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_ClusteredFrustum__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, {}, {}, {}, };
	}
	// mud::Particles
	{
		Type& t = type<mud::Particles>();
		static Meta meta = { t, &namspc({ "mud" }), "Particles", sizeof(mud::Particles), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::ParticleFlow>() };
		static size_t bases_offsets[] = { base_offset<mud::Particles, mud::ParticleFlow>() };
		// defaults
		static mud::Node3* node_default = nullptr;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Particles__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Particles__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Particles, m_node), type<mud::Node3>(), "node", node_default, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::RenderTarget
	{
		Type& t = type<mud::RenderTarget>();
		static Meta meta = { t, &namspc({ "mud" }), "RenderTarget", sizeof(mud::RenderTarget), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::FrameBuffer>() };
		static size_t bases_offsets[] = { base_offset<mud::RenderTarget, mud::FrameBuffer>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
		m.m_types.push_back(&type<mud::Animated>());
		m.m_types.push_back(&type<mud::AnimatedTrack>());
		m.m_types.push_back(&type<mud::Animation>());
		m.m_types.push_back(&type<mud::AnimationPlay>());
		m.m_types.push_back(&type<mud::AnimationTarget>());
		m.m_types.push_back(&type<mud::AnimationTrack>());
		m.m_types.push_back(&type<mud::AssetStore<mud::Material>>());
		m.m_types.push_back(&type<mud::AssetStore<mud::Model>>());
		m.m_types.push_back(&type<mud::AssetStore<mud::ParticleFlow>>());
		m.m_types.push_back(&type<mud::AssetStore<mud::Prefab>>());
		m.m_types.push_back(&type<mud::AssetStore<mud::Program>>());
		m.m_types.push_back(&type<mud::AssetStore<mud::Texture>>());
		m.m_types.push_back(&type<mud::Background>());
		m.m_types.push_back(&type<mud::BackgroundMode>());
		m.m_types.push_back(&type<mud::BaseMaterialBlock>());
		m.m_types.push_back(&type<mud::BlendMode>());
		m.m_types.push_back(&type<mud::Bone>());
		m.m_types.push_back(&type<mud::Camera>());
		m.m_types.push_back(&type<mud::CullMode>());
		m.m_types.push_back(&type<mud::Culler>());
		m.m_types.push_back(&type<mud::DepthDraw>());
		m.m_types.push_back(&type<mud::DepthParams>());
		m.m_types.push_back(&type<mud::DepthTest>());
		m.m_types.push_back(&type<mud::EmitterFlow>());
		m.m_types.push_back(&type<mud::Environment>());
		m.m_types.push_back(&type<mud::Filter>());
		m.m_types.push_back(&type<mud::Fog>());
		m.m_types.push_back(&type<mud::FrameBuffer>());
		m.m_types.push_back(&type<mud::FresnelMaterialBlock>());
		m.m_types.push_back(&type<mud::Frustum>());
		m.m_types.push_back(&type<mud::FrustumSlice>());
		m.m_types.push_back(&type<mud::GfxBlock>());
		m.m_types.push_back(&type<mud::GfxContext>());
		m.m_types.push_back(&type<mud::GfxSystem>());
		m.m_types.push_back(&type<mud::Gnode>());
		m.m_types.push_back(&type<mud::ImmediateDraw>());
		m.m_types.push_back(&type<mud::ImportConfig>());
		m.m_types.push_back(&type<mud::Interpolation>());
		m.m_types.push_back(&type<mud::IsometricAngle>());
		m.m_types.push_back(&type<mud::Item>());
		m.m_types.push_back(&type<mud::ItemShadow>());
		m.m_types.push_back(&type<mud::Joint>());
		m.m_types.push_back(&type<mud::Light>());
		m.m_types.push_back(&type<mud::LightType>());
		m.m_types.push_back(&type<mud::Lighting>());
		m.m_types.push_back(&type<mud::MSAA>());
		m.m_types.push_back(&type<mud::Material>());
		m.m_types.push_back(&type<mud::MaterialFlag>());
		m.m_types.push_back(&type<mud::MaterialParam<float>>());
		m.m_types.push_back(&type<mud::MaterialParam<mud::Colour>>());
		m.m_types.push_back(&type<mud::Mesh>());
		m.m_types.push_back(&type<mud::Model>());
		m.m_types.push_back(&type<mud::ModelFormat>());
		m.m_types.push_back(&type<mud::ModelItem>());
		m.m_types.push_back(&type<mud::Month>());
		m.m_types.push_back(&type<mud::Node3>());
		m.m_types.push_back(&type<mud::ParticleFlow>());
		m.m_types.push_back(&type<mud::PbrDiffuseMode>());
		m.m_types.push_back(&type<mud::PbrMaterialBlock>());
		m.m_types.push_back(&type<mud::PbrSpecularMode>());
		m.m_types.push_back(&type<mud::Prefab>());
		m.m_types.push_back(&type<mud::Program>());
		m.m_types.push_back(&type<mud::Radiance>());
		m.m_types.push_back(&type<mud::RenderFrame>());
		m.m_types.push_back(&type<mud::RenderQuad>());
		m.m_types.push_back(&type<mud::Rig>());
		m.m_types.push_back(&type<mud::Scene>());
		m.m_types.push_back(&type<mud::ShaderType>());
		m.m_types.push_back(&type<mud::Shading>());
		m.m_types.push_back(&type<mud::ShadowFlags>());
		m.m_types.push_back(&type<mud::Shot>());
		m.m_types.push_back(&type<mud::Skeleton>());
		m.m_types.push_back(&type<mud::Skin>());
		m.m_types.push_back(&type<mud::Sun>());
		m.m_types.push_back(&type<mud::SymbolIndex>());
		m.m_types.push_back(&type<mud::Texture>());
		m.m_types.push_back(&type<mud::TextureChannel>());
		m.m_types.push_back(&type<mud::TextureHint>());
		m.m_types.push_back(&type<mud::TextureSampler>());
		m.m_types.push_back(&type<mud::UnshadedMaterialBlock>());
		m.m_types.push_back(&type<mud::Viewport>());
		m.m_types.push_back(&type<array<mud::mat4>>());
		m.m_types.push_back(&type<vector<mud::Animation*>>());
		m.m_types.push_back(&type<vector<mud::AnimationPlay>>());
		m.m_types.push_back(&type<vector<string>>());
		m.m_types.push_back(&type<vector<string>>());
		m.m_types.push_back(&type<vector<string>>());
		m.m_types.push_back(&type<vector<string>>());
		m.m_types.push_back(&type<mud::BlockCopy>());
		m.m_types.push_back(&type<mud::BlockDepth>());
		m.m_types.push_back(&type<mud::BlockFilter>());
		m.m_types.push_back(&type<mud::BlockParticles>());
		m.m_types.push_back(&type<mud::BlockResolve>());
		m.m_types.push_back(&type<mud::BlockSky>());
		m.m_types.push_back(&type<mud::ClusteredFrustum>());
		m.m_types.push_back(&type<mud::DrawBlock>());
		m.m_types.push_back(&type<mud::Particles>());
		m.m_types.push_back(&type<mud::RenderTarget>());
		{
			static Function f = { &namspc({ "mud", "gfx" }), "update_item_lights", nullptr, mud_gfx_update_item_lights_0, { { "item", type<mud::Item>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "gfx" }), "update_item_aabb", nullptr, mud_gfx_update_item_aabb_1, { { "item", type<mud::Item>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "gfx" }), "node", nullptr, mud_gfx_node_2, { { "parent", type<mud::Gnode>(),  }, { "object", type<mud::Ref>(), Param::Flags(Param::Nullable|Param::Default) }, { "position", type<mud::vec3>(), Param::Default }, { "rotation", type<mud::quat>(), Param::Default }, { "scale", type<mud::vec3>(), Param::Default } }, { &type<mud::Gnode>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "gfx" }), "shape", nullptr, mud_gfx_shape_3, { { "parent", type<mud::Gnode>(),  }, { "shape", type<mud::Shape>(),  }, { "symbol", type<mud::Symbol>(),  }, { "flags", type<uint32_t>(), Param::Default }, { "material", type<mud::Material>(), Param::Flags(Param::Nullable|Param::Default) }, { "instances", type<size_t>(), Param::Default } }, { &type<mud::Item>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "gfx" }), "draw", nullptr, mud_gfx_draw_4, { { "parent", type<mud::Gnode>(),  }, { "shape", type<mud::Shape>(),  }, { "symbol", type<mud::Symbol>(),  }, { "flags", type<uint32_t>(), Param::Default } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "gfx" }), "sprite", nullptr, mud_gfx_sprite_5, { { "parent", type<mud::Gnode>(),  }, { "image", type<mud::Image256>(),  }, { "size", type<mud::vec2>(),  }, { "flags", type<uint32_t>(), Param::Default }, { "material", type<mud::Material>(), Param::Flags(Param::Nullable|Param::Default) }, { "instances", type<size_t>(), Param::Default } }, { &type<mud::Item>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "gfx" }), "item", nullptr, mud_gfx_item_6, { { "parent", type<mud::Gnode>(),  }, { "model", type<mud::Model>(),  }, { "flags", type<uint32_t>(), Param::Default }, { "material", type<mud::Material>(), Param::Flags(Param::Nullable|Param::Default) }, { "instances", type<size_t>(), Param::Default }, { "transforms", type<array<mud::mat4>>(), Param::Default } }, { &type<mud::Item>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "gfx" }), "prefab", nullptr, mud_gfx_prefab_7, { { "parent", type<mud::Gnode>(),  }, { "prefab", type<mud::Prefab>(),  }, { "transform", type<bool>(), Param::Default }, { "flags", type<uint32_t>(), Param::Default }, { "material", type<mud::Material>(), Param::Flags(Param::Nullable|Param::Default) }, { "instances", type<size_t>(), Param::Default }, { "transforms", type<array<mud::mat4>>(), Param::Default } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "gfx" }), "model", nullptr, mud_gfx_model_8, { { "parent", type<mud::Gnode>(),  }, { "name", type<string>(),  }, { "flags", type<uint32_t>(), Param::Default }, { "material", type<mud::Material>(), Param::Flags(Param::Nullable|Param::Default) }, { "instances", type<size_t>(), Param::Default } }, { &type<mud::Item>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "gfx" }), "animated", nullptr, mud_gfx_animated_9, { { "parent", type<mud::Gnode>(),  }, { "item", type<mud::Item>(),  } }, { &type<mud::Animated>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "gfx" }), "particles", nullptr, mud_gfx_particles_10, { { "parent", type<mud::Gnode>(),  }, { "emitter", type<mud::ParticleFlow>(),  }, { "flags", type<uint32_t>(), Param::Default }, { "instances", type<size_t>(), Param::Default } }, { &type<mud::Particles>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "gfx" }), "light", nullptr, mud_gfx_light_11, { { "parent", type<mud::Gnode>(),  }, { "type", type<mud::LightType>(),  }, { "shadows", type<bool>(),  }, { "colour", type<mud::Colour>(),  }, { "range", type<float>(), Param::Default }, { "attenuation", type<float>(), Param::Default } }, { &type<mud::Light>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "gfx" }), "sun_light", nullptr, mud_gfx_sun_light_12, { { "parent", type<mud::Gnode>(),  }, { "azimuth", type<float>(),  }, { "elevation", type<float>(),  } }, { &type<mud::Light>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "gfx" }), "radiance", nullptr, mud_gfx_radiance_13, { { "parent", type<mud::Gnode>(),  }, { "texture", type<string>(),  }, { "background", type<mud::BackgroundMode>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
	}
}

namespace mud
{
	mud_gfx::mud_gfx()
		: Module("mud::gfx", { &mud_infra::m(), &mud_jobs::m(), &mud_type::m(), &mud_pool::m(), &mud_math::m(), &mud_geom::m(), &mud_ctx::m(), &mud_bgfx::m() })
	{
		// setup reflection meta data
		mud_gfx_meta(*this);
	}
}

#ifdef MUD_GFX_MODULE
extern "C"
Module& getModule()
{
		return mud_gfx::m();
}
#endif
