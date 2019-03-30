#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <cstddef>
#include <stl/new.h>
#include <infra/ToString.h>
#include <infra/ToValue.h>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/infra.meta.h>
#include <meta/jobs.meta.h>
#include <meta/type.meta.h>
#include <meta/pool.meta.h>
#include <meta/ecs.meta.h>
#include <meta/math.meta.h>
#include <meta/geom.meta.h>
#include <meta/ctx.meta.h>
#include <meta/bgfx.meta.h>
#include <meta/gfx.meta.h>
#include <meta/gfx.conv.h>
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
void mud_DepthMethod__to_string(void* val, string& str) { str = g_enu[type<mud::DepthMethod>().m_id]->name(uint32_t((*static_cast<mud::DepthMethod*>(val)))); }
void mud_DepthMethod__to_value(const string& str, void* val) { (*static_cast<mud::DepthMethod*>(val)) = mud::DepthMethod(g_enu[type<mud::DepthMethod>().m_id]->value(str.c_str())); }
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
void mud_MaterialBlock__to_string(void* val, string& str) { str = g_enu[type<mud::MaterialBlock>().m_id]->name(uint32_t((*static_cast<mud::MaterialBlock*>(val)))); }
void mud_MaterialBlock__to_value(const string& str, void* val) { (*static_cast<mud::MaterialBlock*>(val)) = mud::MaterialBlock(g_enu[type<mud::MaterialBlock>().m_id]->value(str.c_str())); }
void mud_MaterialFlag__to_string(void* val, string& str) { str = g_enu[type<mud::MaterialFlag>().m_id]->name(uint32_t((*static_cast<mud::MaterialFlag*>(val)))); }
void mud_MaterialFlag__to_value(const string& str, void* val) { (*static_cast<mud::MaterialFlag*>(val)) = mud::MaterialFlag(g_enu[type<mud::MaterialFlag>().m_id]->value(str.c_str())); }
void mud_ModelFormat__to_string(void* val, string& str) { str = g_enu[type<mud::ModelFormat>().m_id]->name(uint32_t((*static_cast<mud::ModelFormat*>(val)))); }
void mud_ModelFormat__to_value(const string& str, void* val) { (*static_cast<mud::ModelFormat*>(val)) = mud::ModelFormat(g_enu[type<mud::ModelFormat>().m_id]->value(str.c_str())); }
void mud_Month__to_string(void* val, string& str) { str = g_enu[type<mud::Month>().m_id]->name(uint32_t((*static_cast<mud::Month*>(val)))); }
void mud_Month__to_value(const string& str, void* val) { (*static_cast<mud::Month*>(val)) = mud::Month(g_enu[type<mud::Month>().m_id]->value(str.c_str())); }
void mud_PassType__to_string(void* val, string& str) { str = g_enu[type<mud::PassType>().m_id]->name(uint32_t((*static_cast<mud::PassType*>(val)))); }
void mud_PassType__to_value(const string& str, void* val) { (*static_cast<mud::PassType*>(val)) = mud::PassType(g_enu[type<mud::PassType>().m_id]->value(str.c_str())); }
void mud_PbrDiffuseMode__to_string(void* val, string& str) { str = g_enu[type<mud::PbrDiffuseMode>().m_id]->name(uint32_t((*static_cast<mud::PbrDiffuseMode*>(val)))); }
void mud_PbrDiffuseMode__to_value(const string& str, void* val) { (*static_cast<mud::PbrDiffuseMode*>(val)) = mud::PbrDiffuseMode(g_enu[type<mud::PbrDiffuseMode>().m_id]->value(str.c_str())); }
void mud_PbrSpecularMode__to_string(void* val, string& str) { str = g_enu[type<mud::PbrSpecularMode>().m_id]->name(uint32_t((*static_cast<mud::PbrSpecularMode*>(val)))); }
void mud_PbrSpecularMode__to_value(const string& str, void* val) { (*static_cast<mud::PbrSpecularMode*>(val)) = mud::PbrSpecularMode(g_enu[type<mud::PbrSpecularMode>().m_id]->value(str.c_str())); }
void mud_ShaderColor__to_string(void* val, string& str) { str = g_enu[type<mud::ShaderColor>().m_id]->name(uint32_t((*static_cast<mud::ShaderColor*>(val)))); }
void mud_ShaderColor__to_value(const string& str, void* val) { (*static_cast<mud::ShaderColor*>(val)) = mud::ShaderColor(g_enu[type<mud::ShaderColor>().m_id]->value(str.c_str())); }
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
size_t stl_span_mud_mat4__size(void* vec) { return (*static_cast<stl::span<mud::mat4>*>(vec)).size(); }
void* stl_span_mud_mat4__at(void* vec, size_t i) { return &(*static_cast<stl::span<mud::mat4>*>(vec))[i]; }
size_t stl_vector_mud_Animation___size(void* vec) { return (*static_cast<stl::vector<mud::Animation*>*>(vec)).size(); }
void* stl_vector_mud_Animation___at(void* vec, size_t i) { return &(*static_cast<stl::vector<mud::Animation*>*>(vec))[i]; }
void stl_vector_mud_Animation___push(void* vec) { (*static_cast<stl::vector<mud::Animation*>*>(vec)).emplace_back(); }
void stl_vector_mud_Animation___add(void* vec, void* value) { (*static_cast<stl::vector<mud::Animation*>*>(vec)).push_back(static_cast<mud::Animation*>(value)); }
void stl_vector_mud_Animation___remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<mud::Animation*>*>(vec)), static_cast<mud::Animation*>(value)); }
size_t stl_vector_mud_AnimationPlay__size(void* vec) { return (*static_cast<stl::vector<mud::AnimationPlay>*>(vec)).size(); }
void* stl_vector_mud_AnimationPlay__at(void* vec, size_t i) { return &(*static_cast<stl::vector<mud::AnimationPlay>*>(vec))[i]; }
void stl_vector_mud_AnimationPlay__push(void* vec) { (*static_cast<stl::vector<mud::AnimationPlay>*>(vec)).emplace_back(); }
void stl_vector_mud_AnimationPlay__add(void* vec, void* value) { (*static_cast<stl::vector<mud::AnimationPlay>*>(vec)).push_back(*static_cast<mud::AnimationPlay*>(value)); }
void stl_vector_mud_AnimationPlay__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<mud::AnimationPlay>*>(vec)), *static_cast<mud::AnimationPlay*>(value)); }
size_t stl_vector_mud_Material___size(void* vec) { return (*static_cast<stl::vector<mud::Material*>*>(vec)).size(); }
void* stl_vector_mud_Material___at(void* vec, size_t i) { return &(*static_cast<stl::vector<mud::Material*>*>(vec))[i]; }
void stl_vector_mud_Material___push(void* vec) { (*static_cast<stl::vector<mud::Material*>*>(vec)).emplace_back(); }
void stl_vector_mud_Material___add(void* vec, void* value) { (*static_cast<stl::vector<mud::Material*>*>(vec)).push_back(static_cast<mud::Material*>(value)); }
void stl_vector_mud_Material___remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<mud::Material*>*>(vec)), static_cast<mud::Material*>(value)); }
size_t stl_vector_mud_Mesh___size(void* vec) { return (*static_cast<stl::vector<mud::Mesh*>*>(vec)).size(); }
void* stl_vector_mud_Mesh___at(void* vec, size_t i) { return &(*static_cast<stl::vector<mud::Mesh*>*>(vec))[i]; }
void stl_vector_mud_Mesh___push(void* vec) { (*static_cast<stl::vector<mud::Mesh*>*>(vec)).emplace_back(); }
void stl_vector_mud_Mesh___add(void* vec, void* value) { (*static_cast<stl::vector<mud::Mesh*>*>(vec)).push_back(static_cast<mud::Mesh*>(value)); }
void stl_vector_mud_Mesh___remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<mud::Mesh*>*>(vec)), static_cast<mud::Mesh*>(value)); }
size_t stl_vector_mud_Model___size(void* vec) { return (*static_cast<stl::vector<mud::Model*>*>(vec)).size(); }
void* stl_vector_mud_Model___at(void* vec, size_t i) { return &(*static_cast<stl::vector<mud::Model*>*>(vec))[i]; }
void stl_vector_mud_Model___push(void* vec) { (*static_cast<stl::vector<mud::Model*>*>(vec)).emplace_back(); }
void stl_vector_mud_Model___add(void* vec, void* value) { (*static_cast<stl::vector<mud::Model*>*>(vec)).push_back(static_cast<mud::Model*>(value)); }
void stl_vector_mud_Model___remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<mud::Model*>*>(vec)), static_cast<mud::Model*>(value)); }
size_t stl_vector_mud_Texture___size(void* vec) { return (*static_cast<stl::vector<mud::Texture*>*>(vec)).size(); }
void* stl_vector_mud_Texture___at(void* vec, size_t i) { return &(*static_cast<stl::vector<mud::Texture*>*>(vec))[i]; }
void stl_vector_mud_Texture___push(void* vec) { (*static_cast<stl::vector<mud::Texture*>*>(vec)).emplace_back(); }
void stl_vector_mud_Texture___add(void* vec, void* value) { (*static_cast<stl::vector<mud::Texture*>*>(vec)).push_back(static_cast<mud::Texture*>(value)); }
void stl_vector_mud_Texture___remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<mud::Texture*>*>(vec)), static_cast<mud::Texture*>(value)); }
void mud_AnimatedTrack__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::AnimatedTrack(  ); }
void mud_AnimatedTrack__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::AnimatedTrack((*static_cast<mud::AnimatedTrack*>(other))); }
void mud_AnimationPlay__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::AnimationPlay(  ); }
void mud_AnimationPlay__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::AnimationPlay((*static_cast<mud::AnimationPlay*>(other))); }
void mud_AssetStore_mud_Flow_get(void* object, span<void*> args, void*& result) { result = (*static_cast<mud::AssetStore<mud::Flow>*>(object)).get(*static_cast<stl::string*>(args[0])); }
void mud_AssetStore_mud_Flow_create(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::AssetStore<mud::Flow>*>(object)).create(*static_cast<stl::string*>(args[0])); }
void mud_AssetStore_mud_Flow_fetch(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::AssetStore<mud::Flow>*>(object)).fetch(*static_cast<stl::string*>(args[0])); }
void mud_AssetStore_mud_Flow_file(void* object, span<void*> args, void*& result) { result = (*static_cast<mud::AssetStore<mud::Flow>*>(object)).file(*static_cast<stl::string*>(args[0])); }
void mud_AssetStore_mud_Flow_file_at(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::AssetStore<mud::Flow>*>(object)).file_at(*static_cast<stl::string*>(args[0]), *static_cast<stl::string*>(args[1])); }
void mud_AssetStore_mud_Flow_destroy(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::AssetStore<mud::Flow>*>(object)).destroy(*static_cast<stl::string*>(args[0])); }
void mud_AssetStore_mud_Flow_clear(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::AssetStore<mud::Flow>*>(object)).clear(); }
void mud_AssetStore_mud_Material_get(void* object, span<void*> args, void*& result) { result = (*static_cast<mud::AssetStore<mud::Material>*>(object)).get(*static_cast<stl::string*>(args[0])); }
void mud_AssetStore_mud_Material_create(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::AssetStore<mud::Material>*>(object)).create(*static_cast<stl::string*>(args[0])); }
void mud_AssetStore_mud_Material_fetch(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::AssetStore<mud::Material>*>(object)).fetch(*static_cast<stl::string*>(args[0])); }
void mud_AssetStore_mud_Material_file(void* object, span<void*> args, void*& result) { result = (*static_cast<mud::AssetStore<mud::Material>*>(object)).file(*static_cast<stl::string*>(args[0])); }
void mud_AssetStore_mud_Material_file_at(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::AssetStore<mud::Material>*>(object)).file_at(*static_cast<stl::string*>(args[0]), *static_cast<stl::string*>(args[1])); }
void mud_AssetStore_mud_Material_destroy(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::AssetStore<mud::Material>*>(object)).destroy(*static_cast<stl::string*>(args[0])); }
void mud_AssetStore_mud_Material_clear(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::AssetStore<mud::Material>*>(object)).clear(); }
void mud_AssetStore_mud_Model_get(void* object, span<void*> args, void*& result) { result = (*static_cast<mud::AssetStore<mud::Model>*>(object)).get(*static_cast<stl::string*>(args[0])); }
void mud_AssetStore_mud_Model_create(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::AssetStore<mud::Model>*>(object)).create(*static_cast<stl::string*>(args[0])); }
void mud_AssetStore_mud_Model_fetch(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::AssetStore<mud::Model>*>(object)).fetch(*static_cast<stl::string*>(args[0])); }
void mud_AssetStore_mud_Model_file(void* object, span<void*> args, void*& result) { result = (*static_cast<mud::AssetStore<mud::Model>*>(object)).file(*static_cast<stl::string*>(args[0])); }
void mud_AssetStore_mud_Model_file_at(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::AssetStore<mud::Model>*>(object)).file_at(*static_cast<stl::string*>(args[0]), *static_cast<stl::string*>(args[1])); }
void mud_AssetStore_mud_Model_destroy(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::AssetStore<mud::Model>*>(object)).destroy(*static_cast<stl::string*>(args[0])); }
void mud_AssetStore_mud_Model_clear(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::AssetStore<mud::Model>*>(object)).clear(); }
void mud_AssetStore_mud_Prefab_get(void* object, span<void*> args, void*& result) { result = (*static_cast<mud::AssetStore<mud::Prefab>*>(object)).get(*static_cast<stl::string*>(args[0])); }
void mud_AssetStore_mud_Prefab_create(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::AssetStore<mud::Prefab>*>(object)).create(*static_cast<stl::string*>(args[0])); }
void mud_AssetStore_mud_Prefab_fetch(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::AssetStore<mud::Prefab>*>(object)).fetch(*static_cast<stl::string*>(args[0])); }
void mud_AssetStore_mud_Prefab_file(void* object, span<void*> args, void*& result) { result = (*static_cast<mud::AssetStore<mud::Prefab>*>(object)).file(*static_cast<stl::string*>(args[0])); }
void mud_AssetStore_mud_Prefab_file_at(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::AssetStore<mud::Prefab>*>(object)).file_at(*static_cast<stl::string*>(args[0]), *static_cast<stl::string*>(args[1])); }
void mud_AssetStore_mud_Prefab_destroy(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::AssetStore<mud::Prefab>*>(object)).destroy(*static_cast<stl::string*>(args[0])); }
void mud_AssetStore_mud_Prefab_clear(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::AssetStore<mud::Prefab>*>(object)).clear(); }
void mud_AssetStore_mud_Program_get(void* object, span<void*> args, void*& result) { result = (*static_cast<mud::AssetStore<mud::Program>*>(object)).get(*static_cast<stl::string*>(args[0])); }
void mud_AssetStore_mud_Program_create(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::AssetStore<mud::Program>*>(object)).create(*static_cast<stl::string*>(args[0])); }
void mud_AssetStore_mud_Program_fetch(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::AssetStore<mud::Program>*>(object)).fetch(*static_cast<stl::string*>(args[0])); }
void mud_AssetStore_mud_Program_file(void* object, span<void*> args, void*& result) { result = (*static_cast<mud::AssetStore<mud::Program>*>(object)).file(*static_cast<stl::string*>(args[0])); }
void mud_AssetStore_mud_Program_file_at(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::AssetStore<mud::Program>*>(object)).file_at(*static_cast<stl::string*>(args[0]), *static_cast<stl::string*>(args[1])); }
void mud_AssetStore_mud_Program_destroy(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::AssetStore<mud::Program>*>(object)).destroy(*static_cast<stl::string*>(args[0])); }
void mud_AssetStore_mud_Program_clear(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::AssetStore<mud::Program>*>(object)).clear(); }
void mud_AssetStore_mud_Texture_get(void* object, span<void*> args, void*& result) { result = (*static_cast<mud::AssetStore<mud::Texture>*>(object)).get(*static_cast<stl::string*>(args[0])); }
void mud_AssetStore_mud_Texture_create(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::AssetStore<mud::Texture>*>(object)).create(*static_cast<stl::string*>(args[0])); }
void mud_AssetStore_mud_Texture_fetch(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::AssetStore<mud::Texture>*>(object)).fetch(*static_cast<stl::string*>(args[0])); }
void mud_AssetStore_mud_Texture_file(void* object, span<void*> args, void*& result) { result = (*static_cast<mud::AssetStore<mud::Texture>*>(object)).file(*static_cast<stl::string*>(args[0])); }
void mud_AssetStore_mud_Texture_file_at(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::AssetStore<mud::Texture>*>(object)).file_at(*static_cast<stl::string*>(args[0]), *static_cast<stl::string*>(args[1])); }
void mud_AssetStore_mud_Texture_destroy(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::AssetStore<mud::Texture>*>(object)).destroy(*static_cast<stl::string*>(args[0])); }
void mud_AssetStore_mud_Texture_clear(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::AssetStore<mud::Texture>*>(object)).clear(); }
void mud_Background__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Background(  ); }
void mud_Background__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Background((*static_cast<mud::Background*>(other))); }
void mud_Batch__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Batch(  ); }
void mud_Batch__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Batch( *static_cast<mud::Item*>(args[0]), *static_cast<uint16_t*>(args[1]) ); }
void mud_Batch__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Batch((*static_cast<mud::Batch*>(other))); }
void mud_Batch_update_aabb(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Batch*>(object)).update_aabb(*static_cast<stl::span<mud::mat4>*>(args[0])); }
void mud_Batch_transforms(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Batch*>(object)).transforms(*static_cast<stl::span<mud::mat4>*>(args[0])); }
void mud_Batch_begin(void* object, span<void*> args, void*& result) { (*static_cast<stl::span<float>*>(result)) = (*static_cast<mud::Batch*>(object)).begin(*static_cast<uint32_t*>(args[0])); }
void mud_Batch_commit(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Batch*>(object)).commit(*static_cast<stl::span<float>*>(args[0])); }
void mud_Batch_cache(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Batch*>(object)).cache(*static_cast<stl::span<float>*>(args[0])); }
void mud_Bone__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Bone(  ); }
void mud_Bone__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Bone((*static_cast<mud::Bone*>(other))); }
void mud_Camera_set_look_at(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Camera*>(object)).set_look_at(*static_cast<mud::vec3*>(args[0]), *static_cast<mud::vec3*>(args[1])); }
void mud_Camera_set_isometric(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Camera*>(object)).set_isometric(*static_cast<mud::IsometricAngle*>(args[0]), *static_cast<mud::vec3*>(args[1])); }
void mud_DepthParams__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::DepthParams(  ); }
void mud_DepthParams__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::DepthParams((*static_cast<mud::DepthParams*>(other))); }
void mud_Direct__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Direct(  ); }
void mud_Direct__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Direct( *static_cast<mud::Item*>(args[0]) ); }
void mud_DistanceParams__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::DistanceParams(  ); }
void mud_DistanceParams__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::DistanceParams((*static_cast<mud::DistanceParams*>(other))); }
void mud_Flow__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Flow(  ); }
void mud_Flow__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Flow((*static_cast<mud::Flow*>(other))); }
void mud_Fog__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Fog(  ); }
void mud_Fog__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Fog((*static_cast<mud::Fog*>(other))); }
void mud_FrustumSlice__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::FrustumSlice(  ); }
void mud_FrustumSlice__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::FrustumSlice((*static_cast<mud::FrustumSlice*>(other))); }
void* mud_GfxBlock__get_type(void* object) { return &(*static_cast<mud::GfxBlock*>(object)).m_type; }
void mud_GpuMesh__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::GpuMesh(  ); }
void mud_GpuMesh__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::GpuMesh((*static_cast<mud::GpuMesh*>(other))); }
void mud_ImportConfig__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::ImportConfig(  ); }
void mud_ImportConfig__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::ImportConfig((*static_cast<mud::ImportConfig*>(other))); }
void mud_Item__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Item(  ); }
void mud_Item__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Item( *static_cast<mud::Node3*>(args[0]), *static_cast<mud::Model*>(args[1]), *static_cast<uint32_t*>(args[2]), static_cast<mud::Material*>(args[3]) ); }
void mud_Item_update_aabb(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::Item*>(object)).update_aabb(); }
void mud_Joint__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Joint(  ); }
void mud_Joint__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Joint((*static_cast<mud::Joint*>(other))); }
void mud_Light__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Light( *static_cast<mud::Node3*>(args[0]), *static_cast<mud::LightType*>(args[1]), *static_cast<bool*>(args[2]), *static_cast<mud::Colour*>(args[3]), *static_cast<float*>(args[4]), *static_cast<float*>(args[5]) ); }
void mud_Lines__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Lines(  ); }
void mud_Lines__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Lines( *static_cast<stl::vector<mud::vec3>*>(args[0]) ); }
void mud_Lines__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Lines( *static_cast<mud::Curve3*>(args[0]), *static_cast<size_t*>(args[1]) ); }
void mud_Lines_add(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Lines*>(object)).add(*static_cast<mud::vec3*>(args[0]), *static_cast<mud::vec3*>(args[1]), *static_cast<mud::Colour*>(args[2]), *static_cast<mud::Colour*>(args[3])); }
void mud_Lines_start(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Lines*>(object)).start(*static_cast<mud::vec3*>(args[0]), *static_cast<mud::Colour*>(args[1])); }
void mud_Lines_next(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Lines*>(object)).next(*static_cast<mud::vec3*>(args[0]), *static_cast<mud::Colour*>(args[1])); }
void mud_Lines_setup(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::Lines*>(object)).setup(); }
void mud_Lines_write(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Lines*>(object)).write(*static_cast<mud::Mesh*>(args[0])); }
void mud_Lines_commit(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Lines*>(object)).commit(*static_cast<mud::Batch*>(args[0])); }
void mud_MaterialAlpha__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::MaterialAlpha(  ); }
void mud_MaterialAlpha__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::MaterialAlpha((*static_cast<mud::MaterialAlpha*>(other))); }
void mud_MaterialBase__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::MaterialBase(  ); }
void mud_MaterialBase__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::MaterialBase((*static_cast<mud::MaterialBase*>(other))); }
void mud_MaterialFresnel__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::MaterialFresnel(  ); }
void mud_MaterialFresnel__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::MaterialFresnel((*static_cast<mud::MaterialFresnel*>(other))); }
void mud_MaterialLine__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::MaterialLine(  ); }
void mud_MaterialLine__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::MaterialLine((*static_cast<mud::MaterialLine*>(other))); }
void mud_MaterialLit__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::MaterialLit(  ); }
void mud_MaterialLit__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::MaterialLit((*static_cast<mud::MaterialLit*>(other))); }
void mud_MaterialParam_float__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::MaterialParam<float>(  ); }
void mud_MaterialParam_float__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::MaterialParam<float>((*static_cast<mud::MaterialParam<float>*>(other))); }
void mud_MaterialParam_mud_Colour__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::MaterialParam<mud::Colour>(  ); }
void mud_MaterialParam_mud_Colour__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::MaterialParam<mud::Colour>((*static_cast<mud::MaterialParam<mud::Colour>*>(other))); }
void mud_MaterialParam_mud_vec4__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::MaterialParam<mud::vec4>(  ); }
void mud_MaterialParam_mud_vec4__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::MaterialParam<mud::vec4>((*static_cast<mud::MaterialParam<mud::vec4>*>(other))); }
void mud_MaterialPbr__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::MaterialPbr(  ); }
void mud_MaterialPbr__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::MaterialPbr( *static_cast<mud::Colour*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]) ); }
void mud_MaterialPbr__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::MaterialPbr((*static_cast<mud::MaterialPbr*>(other))); }
void mud_MaterialPhong__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::MaterialPhong(  ); }
void mud_MaterialPhong__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::MaterialPhong((*static_cast<mud::MaterialPhong*>(other))); }
void mud_MaterialPoint__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::MaterialPoint(  ); }
void mud_MaterialPoint__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::MaterialPoint((*static_cast<mud::MaterialPoint*>(other))); }
void mud_MaterialSolid__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::MaterialSolid(  ); }
void mud_MaterialSolid__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::MaterialSolid((*static_cast<mud::MaterialSolid*>(other))); }
void mud_MaterialUser__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::MaterialUser(  ); }
void mud_MaterialUser__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::MaterialUser((*static_cast<mud::MaterialUser*>(other))); }
void mud_Mesh_clear(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::Mesh*>(object)).clear(); }
void mud_Mesh_write(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Mesh*>(object)).write(*static_cast<mud::MeshPacker*>(args[0]), *static_cast<bool*>(args[1]), *static_cast<bool*>(args[2])); }
void mud_Mesh_upload(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Mesh*>(object)).upload(*static_cast<mud::GpuMesh*>(args[0]), *static_cast<bool*>(args[1])); }
void mud_Mesh_cache(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Mesh*>(object)).cache(*static_cast<mud::GpuMesh*>(args[0])); }
void mud_Mesh_direct(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::Mesh*>(object)).direct(*static_cast<uint32_t*>(args[0]), *static_cast<uint32_t*>(args[1]), *static_cast<uint32_t*>(args[2])); }
void mud_Mime_start(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Mime*>(object)).start(static_cast<const char*>(args[0]), *static_cast<bool*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3]), *static_cast<bool*>(args[4])); }
void mud_Mime_play(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Mime*>(object)).play(*static_cast<mud::Animation*>(args[0]), *static_cast<bool*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3]), *static_cast<bool*>(args[4])); }
void mud_Mime_seek(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Mime*>(object)).seek(*static_cast<float*>(args[0])); }
void mud_Mime_pause(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::Mime*>(object)).pause(); }
void mud_Mime_stop(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::Mime*>(object)).stop(); }
void mud_Mime_advance(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Mime*>(object)).advance(*static_cast<float*>(args[0])); }
void mud_Mime_next_animation(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::Mime*>(object)).next_animation(); }
void mud_Mime_playing(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<stl::string*>(result)) = (*static_cast<mud::Mime*>(object)).playing(); }
void mud_Model_get_mesh(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::Model*>(object)).get_mesh(*static_cast<size_t*>(args[0])); }
void mud_Model_add_mesh(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::Model*>(object)).add_mesh(*static_cast<stl::string*>(args[0]), *static_cast<bool*>(args[1])); }
void mud_Model_add_rig(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::Model*>(object)).add_rig(*static_cast<stl::string*>(args[0])); }
void mud_Model_add_item(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::Model*>(object)).add_item(*static_cast<mud::Mesh*>(args[0]), *static_cast<mud::mat4*>(args[1]), *static_cast<int*>(args[2]), *static_cast<mud::Colour*>(args[3]), static_cast<mud::Material*>(args[4])); }
void mud_Model_prepare(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::Model*>(object)).prepare(); }
void mud_ModelItem__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::ModelItem(  ); }
void mud_ModelItem__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::ModelItem((*static_cast<mud::ModelItem*>(other))); }
void mud_Node3__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Node3(  ); }
void mud_Node3__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Node3( *static_cast<mud::mat4*>(args[0]) ); }
void mud_Node3__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Node3( *static_cast<mud::vec3*>(args[0]), *static_cast<mud::quat*>(args[1]), *static_cast<mud::vec3*>(args[2]) ); }
void mud_Node3_apply(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Node3*>(object)).apply(*static_cast<mud::vec3*>(args[0]), *static_cast<mud::quat*>(args[1]), *static_cast<mud::vec3*>(args[2])); }
void mud_Node3_derive(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Node3*>(object)).derive(*static_cast<mud::Node3*>(args[0]), *static_cast<mud::vec3*>(args[1]), *static_cast<mud::quat*>(args[2]), *static_cast<mud::vec3*>(args[3])); }
void mud_Node3_position(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<mud::v3<float>*>(result)) = (*static_cast<mud::Node3*>(object)).position(); }
void mud_Node3_axis(void* object, span<void*> args, void*& result) { (*static_cast<mud::v3<float>*>(result)) = (*static_cast<mud::Node3*>(object)).axis(*static_cast<mud::vec3*>(args[0])); }
void mud_Node3_direction(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<mud::v3<float>*>(result)) = (*static_cast<mud::Node3*>(object)).direction(); }
void mud_Pass__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Pass(  ); }
void mud_Pass__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Pass((*static_cast<mud::Pass*>(other))); }
void mud_Program_set_block(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Program*>(object)).set_block(*static_cast<mud::MaterialBlock*>(args[0]), *static_cast<bool*>(args[1])); }
void mud_Program_set_pass(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Program*>(object)).set_pass(*static_cast<mud::PassType*>(args[0]), *static_cast<bool*>(args[1])); }
void mud_Program_set_source(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Program*>(object)).set_source(*static_cast<mud::ShaderType*>(args[0]), *static_cast<stl::string*>(args[1])); }
void mud_Program_register_blocks(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Program*>(object)).register_blocks(*static_cast<mud::Program*>(args[0])); }
void mud_Radiance__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Radiance(  ); }
void mud_Radiance__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Radiance((*static_cast<mud::Radiance*>(other))); }
void mud_Render__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Render(  ); }
void mud_Render__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Render( *static_cast<mud::Shading*>(args[0]), *static_cast<mud::Viewport*>(args[1]), *static_cast<mud::RenderTarget*>(args[2]), *static_cast<mud::RenderFrame*>(args[3]) ); }
void mud_Render__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Render( *static_cast<mud::Shading*>(args[0]), *static_cast<mud::Viewport*>(args[1]), *static_cast<mud::RenderTarget*>(args[2]), *static_cast<mud::FrameBuffer*>(args[3]), *static_cast<mud::RenderFrame*>(args[4]) ); }
void mud_Render__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Render((*static_cast<mud::Render*>(other))); }
void mud_Render_next_pass(void* object, span<void*> args, void*& result) { (*static_cast<mud::Pass*>(result)) = (*static_cast<mud::Render*>(object)).next_pass(static_cast<const char*>(args[0]), *static_cast<mud::PassType*>(args[1])); }
void mud_Render_composite_pass(void* object, span<void*> args, void*& result) { (*static_cast<mud::Pass*>(result)) = (*static_cast<mud::Render*>(object)).composite_pass(static_cast<const char*>(args[0]), *static_cast<mud::FrameBuffer*>(args[1]), *static_cast<mud::uvec4*>(args[2])); }
void mud_RenderFrame__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::RenderFrame(  ); }
void mud_RenderFrame__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::RenderFrame((*static_cast<mud::RenderFrame*>(other))); }
void mud_RenderQuad__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::RenderQuad( *static_cast<mud::vec4*>(args[0]), *static_cast<mud::vec4*>(args[1]), *static_cast<bool*>(args[2]) ); }
void mud_RenderQuad__construct_1(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::RenderQuad(  ); }
void mud_RenderQuad__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::RenderQuad((*static_cast<mud::RenderQuad*>(other))); }
void mud_Renderer_gather(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Renderer*>(object)).gather(*static_cast<mud::Render*>(args[0])); }
void mud_Renderer_begin(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Renderer*>(object)).begin(*static_cast<mud::Render*>(args[0])); }
void mud_Renderer_end(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Renderer*>(object)).end(*static_cast<mud::Render*>(args[0])); }
void mud_Scene__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Scene( *static_cast<mud::GfxSystem*>(args[0]) ); }
void mud_Scene_begin(void* object, span<void*> args, void*& result) { UNUSED(args); result = &(*static_cast<mud::Scene*>(object)).begin(); }
void mud_Scene_nodes(void* object, span<void*> args, void*& result) { UNUSED(args); result = &mud::gfx::nodes((*static_cast<mud::Scene*>(object))); }
void mud_Scene_items(void* object, span<void*> args, void*& result) { UNUSED(args); result = &mud::gfx::items((*static_cast<mud::Scene*>(object))); }
void mud_Scene_batches(void* object, span<void*> args, void*& result) { UNUSED(args); result = &mud::gfx::batches((*static_cast<mud::Scene*>(object))); }
void mud_Scene_directs(void* object, span<void*> args, void*& result) { UNUSED(args); result = &mud::gfx::directs((*static_cast<mud::Scene*>(object))); }
void mud_Scene_mimes(void* object, span<void*> args, void*& result) { UNUSED(args); result = &mud::gfx::mimes((*static_cast<mud::Scene*>(object))); }
void mud_Scene_lights(void* object, span<void*> args, void*& result) { UNUSED(args); result = &mud::gfx::lights((*static_cast<mud::Scene*>(object))); }
void mud_Scene_flares(void* object, span<void*> args, void*& result) { UNUSED(args); result = &mud::gfx::flares((*static_cast<mud::Scene*>(object))); }
void mud_Sun__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Sun(  ); }
void mud_Sun__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Sun((*static_cast<mud::Sun*>(other))); }
void mud_SwapBuffer_swap(void* object, span<void*> args, void*& result) { UNUSED(args); result = &(*static_cast<mud::SwapBuffer*>(object)).swap(); }
void mud_SwapBuffer_last(void* object, span<void*> args, void*& result) { UNUSED(args); result = &(*static_cast<mud::SwapBuffer*>(object)).last(); }
void mud_SwapCascade_swap(void* object, span<void*> args, void*& result) { UNUSED(args); result = &(*static_cast<mud::SwapCascade*>(object)).swap(); }
void mud_SwapCascade_last(void* object, span<void*> args, void*& result) { UNUSED(args); result = &(*static_cast<mud::SwapCascade*>(object)).last(); }
void mud_TPool_mud_Batch_add(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::TPool<mud::Batch>*>(object)).add(*static_cast<mud::Batch*>(args[0])); }
void mud_TPool_mud_Batch_talloc(void* object, span<void*> args, void*& result) { UNUSED(args); result = (*static_cast<mud::TPool<mud::Batch>*>(object)).talloc(); }
void mud_TPool_mud_Batch_tdestroy(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::TPool<mud::Batch>*>(object)).tdestroy(*static_cast<mud::Batch*>(args[0])); }
void mud_TPool_mud_Batch_tfree(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::TPool<mud::Batch>*>(object)).tfree(*static_cast<mud::Batch*>(args[0])); }
void mud_TPool_mud_Direct_add(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::TPool<mud::Direct>*>(object)).add(*static_cast<mud::Direct*>(args[0])); }
void mud_TPool_mud_Direct_talloc(void* object, span<void*> args, void*& result) { UNUSED(args); result = (*static_cast<mud::TPool<mud::Direct>*>(object)).talloc(); }
void mud_TPool_mud_Direct_tdestroy(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::TPool<mud::Direct>*>(object)).tdestroy(*static_cast<mud::Direct*>(args[0])); }
void mud_TPool_mud_Direct_tfree(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::TPool<mud::Direct>*>(object)).tfree(*static_cast<mud::Direct*>(args[0])); }
void mud_TPool_mud_Flare_add(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::TPool<mud::Flare>*>(object)).add(*static_cast<mud::Flare*>(args[0])); }
void mud_TPool_mud_Flare_talloc(void* object, span<void*> args, void*& result) { UNUSED(args); result = (*static_cast<mud::TPool<mud::Flare>*>(object)).talloc(); }
void mud_TPool_mud_Flare_tdestroy(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::TPool<mud::Flare>*>(object)).tdestroy(*static_cast<mud::Flare*>(args[0])); }
void mud_TPool_mud_Flare_tfree(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::TPool<mud::Flare>*>(object)).tfree(*static_cast<mud::Flare*>(args[0])); }
void mud_TPool_mud_Item_add(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::TPool<mud::Item>*>(object)).add(*static_cast<mud::Item*>(args[0])); }
void mud_TPool_mud_Item_talloc(void* object, span<void*> args, void*& result) { UNUSED(args); result = (*static_cast<mud::TPool<mud::Item>*>(object)).talloc(); }
void mud_TPool_mud_Item_tdestroy(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::TPool<mud::Item>*>(object)).tdestroy(*static_cast<mud::Item*>(args[0])); }
void mud_TPool_mud_Item_tfree(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::TPool<mud::Item>*>(object)).tfree(*static_cast<mud::Item*>(args[0])); }
void mud_TPool_mud_Light_add(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::TPool<mud::Light>*>(object)).add(*static_cast<mud::Light*>(args[0])); }
void mud_TPool_mud_Light_talloc(void* object, span<void*> args, void*& result) { UNUSED(args); result = (*static_cast<mud::TPool<mud::Light>*>(object)).talloc(); }
void mud_TPool_mud_Light_tdestroy(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::TPool<mud::Light>*>(object)).tdestroy(*static_cast<mud::Light*>(args[0])); }
void mud_TPool_mud_Light_tfree(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::TPool<mud::Light>*>(object)).tfree(*static_cast<mud::Light*>(args[0])); }
void mud_TPool_mud_Mime_add(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::TPool<mud::Mime>*>(object)).add(*static_cast<mud::Mime*>(args[0])); }
void mud_TPool_mud_Mime_talloc(void* object, span<void*> args, void*& result) { UNUSED(args); result = (*static_cast<mud::TPool<mud::Mime>*>(object)).talloc(); }
void mud_TPool_mud_Mime_tdestroy(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::TPool<mud::Mime>*>(object)).tdestroy(*static_cast<mud::Mime*>(args[0])); }
void mud_TPool_mud_Mime_tfree(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::TPool<mud::Mime>*>(object)).tfree(*static_cast<mud::Mime*>(args[0])); }
void mud_TPool_mud_Node3_add(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::TPool<mud::Node3>*>(object)).add(*static_cast<mud::Node3*>(args[0])); }
void mud_TPool_mud_Node3_talloc(void* object, span<void*> args, void*& result) { UNUSED(args); result = (*static_cast<mud::TPool<mud::Node3>*>(object)).talloc(); }
void mud_TPool_mud_Node3_tdestroy(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::TPool<mud::Node3>*>(object)).tdestroy(*static_cast<mud::Node3*>(args[0])); }
void mud_TPool_mud_Node3_tfree(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::TPool<mud::Node3>*>(object)).tfree(*static_cast<mud::Node3*>(args[0])); }
void mud_Texture_valid(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<mud::Texture*>(object)).valid(); }
void mud_Zone__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Zone(  ); }
void mud_Zone__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Zone((*static_cast<mud::Zone*>(other))); }
void mud_BlockCopy_quad(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::BlockCopy*>(object)).quad(*static_cast<mud::Pass*>(args[0]), *static_cast<mud::FrameBuffer*>(args[1]), *static_cast<mud::Texture*>(args[2]), *static_cast<mud::uvec4*>(args[3]), *static_cast<uint64_t*>(args[4])); }
void mud_BlockFilter_quad(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::BlockFilter*>(object)).quad(*static_cast<mud::Pass*>(args[0]), *static_cast<mud::FrameBuffer*>(args[1]), *static_cast<mud::Program*>(args[2]), *static_cast<mud::uvec4*>(args[3]), *static_cast<uint64_t*>(args[4]), *static_cast<bool*>(args[5])); }
void mud_BlockFilter_source0(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::BlockFilter*>(object)).source0(*static_cast<mud::Texture*>(args[0]), *static_cast<uint32_t*>(args[1])); }
void mud_BlockFilter_source1(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::BlockFilter*>(object)).source1(*static_cast<mud::Texture*>(args[0]), *static_cast<uint32_t*>(args[1])); }
void mud_BlockFilter_source2(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::BlockFilter*>(object)).source2(*static_cast<mud::Texture*>(args[0]), *static_cast<uint32_t*>(args[1])); }
void mud_BlockFilter_source3(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::BlockFilter*>(object)).source3(*static_cast<mud::Texture*>(args[0]), *static_cast<uint32_t*>(args[1])); }
void mud_BlockFilter_sourcedepth(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::BlockFilter*>(object)).sourcedepth(*static_cast<mud::Texture*>(args[0]), *static_cast<uint32_t*>(args[1])); }
void mud_BlockFilter_uniform(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::BlockFilter*>(object)).uniform(*static_cast<mud::Pass*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<mud::vec4*>(args[2])); }
void mud_BlockFilter_uniforms(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::BlockFilter*>(object)).uniforms(*static_cast<mud::Pass*>(args[0]), *static_cast<stl::string*>(args[1]), static_cast<mud::vec4*>(args[2]), *static_cast<uint16_t*>(args[3])); }
void mud_ClusteredFrustum__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::ClusteredFrustum(  ); }
void mud_ClusteredFrustum__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::ClusteredFrustum((*static_cast<mud::ClusteredFrustum*>(other))); }
void mud_Flare__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Flare(  ); }
void mud_Flare__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Flare((*static_cast<mud::Flare*>(other))); }
void mud_GfxSystem__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::GfxSystem( *static_cast<stl::string*>(args[0]) ); }
void* mud_GfxSystem__get_textures(void* object) { return &(*static_cast<mud::GfxSystem*>(object)).textures(); }
void* mud_GfxSystem__get_programs(void* object) { return &(*static_cast<mud::GfxSystem*>(object)).programs(); }
void* mud_GfxSystem__get_materials(void* object) { return &(*static_cast<mud::GfxSystem*>(object)).materials(); }
void* mud_GfxSystem__get_models(void* object) { return &(*static_cast<mud::GfxSystem*>(object)).models(); }
void* mud_GfxSystem__get_flows(void* object) { return &(*static_cast<mud::GfxSystem*>(object)).flows(); }
void* mud_GfxSystem__get_prefabs(void* object) { return &(*static_cast<mud::GfxSystem*>(object)).prefabs(); }
void mud_GfxSystem_main_target(void* object, span<void*> args, void*& result) { UNUSED(args); result = &(*static_cast<mud::GfxSystem*>(object)).main_target(); }
void mud_GfxSystem_default_pipeline(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::GfxSystem*>(object)).default_pipeline(); }
void mud_GfxSystem_add_resource_path(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::GfxSystem*>(object)).add_resource_path(*static_cast<stl::string*>(args[0]), *static_cast<bool*>(args[1])); }
void mud_GfxSystem_debug_material(void* object, span<void*> args, void*& result) { UNUSED(args); result = &(*static_cast<mud::GfxSystem*>(object)).debug_material(); }
void mud_GfxSystem_create_model(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::GfxSystem*>(object)).create_model(*static_cast<stl::string*>(args[0])); }
void mud_GfxSystem_create_model_geo(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::GfxSystem*>(object)).create_model_geo(*static_cast<stl::string*>(args[0]), *static_cast<mud::MeshPacker*>(args[1]), *static_cast<bool*>(args[2]), *static_cast<bool*>(args[3])); }
void mud_GfxSystem_create_model_gpu(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::GfxSystem*>(object)).create_model_gpu(*static_cast<stl::string*>(args[0]), *static_cast<mud::GpuMesh*>(args[1]), *static_cast<bool*>(args[2]), *static_cast<bool*>(args[3])); }
void mud_GfxSystem_fetch_material(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::GfxSystem*>(object)).fetch_material(*static_cast<stl::string*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<bool*>(args[2])); }
void mud_GfxSystem_fetch_image256_material(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::GfxSystem*>(object)).fetch_image256_material(*static_cast<mud::Image256*>(args[0])); }
void mud_GfxSystem_shape(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::GfxSystem*>(object)).shape(*static_cast<mud::Shape*>(args[0]), *static_cast<mud::Symbol*>(args[1]), *static_cast<mud::DrawMode*>(args[2])); }
void mud_GfxSystem_symbol_material(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::GfxSystem*>(object)).symbol_material(*static_cast<mud::Symbol*>(args[0]), *static_cast<mud::DrawMode*>(args[1])); }
void mud_Viewport_cull(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Viewport*>(object)).cull(*static_cast<mud::Render*>(args[0])); }
void mud_Viewport_render(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Viewport*>(object)).render(*static_cast<mud::Render*>(args[0])); }
void mud_Viewport_set_clustered(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Viewport*>(object)).set_clustered(*static_cast<mud::GfxSystem*>(args[0])); }
void mud_bxidentity_0(span<void*> args, void*& result) { UNUSED(args); (*static_cast<mud::mat4*>(result)) = mud::bxidentity(); }
void mud_bxinverse_1(span<void*> args, void*& result) { (*static_cast<mud::mat4*>(result)) = mud::bxinverse(*static_cast<mud::mat4*>(args[0])); }
void mud_bxSRT_2(span<void*> args, void*& result) { (*static_cast<mud::mat4*>(result)) = mud::bxSRT(*static_cast<mud::vec3*>(args[0]), *static_cast<mud::vec3*>(args[1]), *static_cast<mud::vec3*>(args[2])); }
void mud_bxscale_3(span<void*> args, void*& result) { (*static_cast<mud::mat4*>(result)) = mud::bxscale(*static_cast<mud::vec3*>(args[0])); }
void mud_bxrotation_4(span<void*> args, void*& result) { (*static_cast<mud::mat4*>(result)) = mud::bxrotation(*static_cast<mud::quat*>(args[0])); }
void mud_bxtranslation_5(span<void*> args, void*& result) { (*static_cast<mud::mat4*>(result)) = mud::bxtranslation(*static_cast<mud::vec3*>(args[0])); }
void mud_bxmul_6(span<void*> args, void*& result) { (*static_cast<mud::mat4*>(result)) = mud::bxmul(*static_cast<mud::mat4*>(args[0]), *static_cast<mud::mat4*>(args[1])); }
void mud_bxmul_7(span<void*> args, void*& result) { (*static_cast<mud::v4<float>*>(result)) = mud::bxmul(*static_cast<mud::mat4*>(args[0]), *static_cast<mud::vec4*>(args[1])); }
void mud_bxmul_8(span<void*> args, void*& result) { (*static_cast<mud::v3<float>*>(result)) = mud::bxmul(*static_cast<mud::mat4*>(args[0]), *static_cast<mud::vec3*>(args[1])); }
void mud_bxmulh_9(span<void*> args, void*& result) { (*static_cast<mud::v3<float>*>(result)) = mud::bxmulh(*static_cast<mud::mat4*>(args[0]), *static_cast<mud::vec3*>(args[1])); }
void mud_bxlookat_10(span<void*> args, void*& result) { (*static_cast<mud::mat4*>(result)) = mud::bxlookat(*static_cast<mud::vec3*>(args[0]), *static_cast<mud::vec3*>(args[1])); }
void mud_bxlookat_11(span<void*> args, void*& result) { UNUSED(result);  mud::bxlookat(*static_cast<mud::mat4*>(args[0]), *static_cast<mud::vec3*>(args[1]), *static_cast<mud::vec3*>(args[2]), *static_cast<mud::vec3*>(args[3])); }
void mud_bxlookat_12(span<void*> args, void*& result) { (*static_cast<mud::mat4*>(result)) = mud::bxlookat(*static_cast<mud::vec3*>(args[0]), *static_cast<mud::vec3*>(args[1]), *static_cast<mud::vec3*>(args[2])); }
void mud_bxproj_13(span<void*> args, void*& result) { (*static_cast<mud::mat4*>(result)) = mud::bxproj(*static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3]), *static_cast<bool*>(args[4])); }
void mud_bxortho_14(span<void*> args, void*& result) { (*static_cast<mud::mat4*>(result)) = mud::bxortho(*static_cast<mud::vec4*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3]), *static_cast<bool*>(args[4])); }
void mud_bxortho_15(span<void*> args, void*& result) { (*static_cast<mud::mat4*>(result)) = mud::bxortho(*static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3]), *static_cast<float*>(args[4]), *static_cast<float*>(args[5]), *static_cast<float*>(args[6]), *static_cast<bool*>(args[7])); }
void mud_bxSRT_16(span<void*> args, void*& result) { (*static_cast<mud::mat4*>(result)) = mud::bxSRT(*static_cast<mud::vec3*>(args[0]), *static_cast<mud::quat*>(args[1]), *static_cast<mud::vec3*>(args[2])); }
void mud_bxTRS_17(span<void*> args, void*& result) { (*static_cast<mud::mat4*>(result)) = mud::bxTRS(*static_cast<mud::vec3*>(args[0]), *static_cast<mud::quat*>(args[1]), *static_cast<mud::vec3*>(args[2])); }
void mud_load_texture_rgba_18(span<void*> args, void*& result) { UNUSED(result);  mud::load_texture_rgba(*static_cast<mud::Texture*>(args[0]), *static_cast<mud::uvec2*>(args[1]), *static_cast<stl::span<uint32_t>*>(args[2])); }
void mud_gfx_setup_pipeline_minimal_19(span<void*> args, void*& result) { UNUSED(result);  mud::gfx::setup_pipeline_minimal(*static_cast<mud::GfxSystem*>(args[0])); }
void mud_gfx_node_20(span<void*> args, void*& result) { result = &mud::gfx::node(*static_cast<mud::Gnode*>(args[0]), *static_cast<mud::Ref*>(args[1]), *static_cast<mud::vec3*>(args[2]), *static_cast<mud::quat*>(args[3]), *static_cast<mud::vec3*>(args[4])); }
void mud_gfx_shape_21(span<void*> args, void*& result) { result = &mud::gfx::shape(*static_cast<mud::Gnode*>(args[0]), *static_cast<mud::Shape*>(args[1]), *static_cast<mud::Symbol*>(args[2]), *static_cast<uint32_t*>(args[3]), static_cast<mud::Material*>(args[4])); }
void mud_gfx_draw_22(span<void*> args, void*& result) { UNUSED(result);  mud::gfx::draw(*static_cast<mud::Gnode*>(args[0]), *static_cast<mud::Shape*>(args[1]), *static_cast<mud::Symbol*>(args[2]), *static_cast<uint32_t*>(args[3])); }
void mud_gfx_sprite_23(span<void*> args, void*& result) { result = &mud::gfx::sprite(*static_cast<mud::Gnode*>(args[0]), *static_cast<mud::Image256*>(args[1]), *static_cast<mud::vec2*>(args[2]), *static_cast<uint32_t*>(args[3]), static_cast<mud::Material*>(args[4])); }
void mud_gfx_item_24(span<void*> args, void*& result) { result = &mud::gfx::item(*static_cast<mud::Gnode*>(args[0]), *static_cast<mud::Model*>(args[1]), *static_cast<uint32_t*>(args[2]), static_cast<mud::Material*>(args[3])); }
void mud_gfx_batch_25(span<void*> args, void*& result) { result = &mud::gfx::batch(*static_cast<mud::Gnode*>(args[0]), *static_cast<mud::Item*>(args[1]), *static_cast<uint16_t*>(args[2])); }
void mud_gfx_instances_26(span<void*> args, void*& result) { result = &mud::gfx::instances(*static_cast<mud::Gnode*>(args[0]), *static_cast<mud::Item*>(args[1]), *static_cast<stl::span<mud::mat4>*>(args[2])); }
void mud_gfx_prefab_27(span<void*> args, void*& result) { UNUSED(result);  mud::gfx::prefab(*static_cast<mud::Gnode*>(args[0]), *static_cast<mud::Prefab*>(args[1]), *static_cast<bool*>(args[2]), *static_cast<uint32_t*>(args[3]), static_cast<mud::Material*>(args[4])); }
void mud_gfx_model_28(span<void*> args, void*& result) { result = mud::gfx::model(*static_cast<mud::Gnode*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<uint32_t*>(args[2]), static_cast<mud::Material*>(args[3])); }
void mud_gfx_animated_29(span<void*> args, void*& result) { result = &mud::gfx::animated(*static_cast<mud::Gnode*>(args[0]), *static_cast<mud::Item*>(args[1])); }
void mud_gfx_flows_30(span<void*> args, void*& result) { result = &mud::gfx::flows(*static_cast<mud::Gnode*>(args[0]), *static_cast<mud::Flow*>(args[1]), *static_cast<uint32_t*>(args[2])); }
void mud_gfx_light_31(span<void*> args, void*& result) { result = &mud::gfx::light(*static_cast<mud::Gnode*>(args[0]), *static_cast<mud::LightType*>(args[1]), *static_cast<bool*>(args[2]), *static_cast<mud::Colour*>(args[3]), *static_cast<float*>(args[4]), *static_cast<float*>(args[5])); }
void mud_gfx_sun_light_32(span<void*> args, void*& result) { result = &mud::gfx::sun_light(*static_cast<mud::Gnode*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2])); }
void mud_gfx_radiance_33(span<void*> args, void*& result) { UNUSED(result);  mud::gfx::radiance(*static_cast<mud::Gnode*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<mud::BackgroundMode*>(args[2])); }
void mud_gfx_direct_light_node_34(span<void*> args, void*& result) { result = &mud::gfx::direct_light_node(*static_cast<mud::Gnode*>(args[0]), *static_cast<mud::vec3*>(args[1])); }
void mud_gfx_solid_material_35(span<void*> args, void*& result) { result = &mud::gfx::solid_material(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<mud::Colour*>(args[2])); }
void mud_gfx_pbr_material_36(span<void*> args, void*& result) { result = &mud::gfx::pbr_material(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<mud::Colour*>(args[2]), *static_cast<float*>(args[3]), *static_cast<float*>(args[4])); }
void mud_gfx_model_suzanne_37(span<void*> args, void*& result) { result = &mud::gfx::model_suzanne(*static_cast<mud::GfxSystem*>(args[0])); }
void mud_pass_clear_fbo_38(span<void*> args, void*& result) { UNUSED(result);  mud::pass_clear_fbo(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<mud::Render*>(args[1]), *static_cast<mud::FrameBuffer*>(args[2]), *static_cast<mud::Colour*>(args[3])); }
void mud_pass_clear_39(span<void*> args, void*& result) { UNUSED(result);  mud::pass_clear(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<mud::Render*>(args[1])); }
void mud_pass_gclear_40(span<void*> args, void*& result) { UNUSED(result);  mud::pass_gclear(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<mud::Render*>(args[1])); }
void mud_pass_depth_41(span<void*> args, void*& result) { UNUSED(result);  mud::pass_depth(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<mud::Render*>(args[1])); }
void mud_pass_background_42(span<void*> args, void*& result) { UNUSED(result);  mud::pass_background(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<mud::Render*>(args[1])); }
void mud_pass_solid_43(span<void*> args, void*& result) { UNUSED(result);  mud::pass_solid(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<mud::Render*>(args[1])); }
void mud_pass_flip_44(span<void*> args, void*& result) { UNUSED(result);  mud::pass_flip(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<mud::Render*>(args[1])); }
void mud_render_minimal_45(span<void*> args, void*& result) { UNUSED(result);  mud::render_minimal(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<mud::Render*>(args[1])); }
void mud_render_solid_46(span<void*> args, void*& result) { UNUSED(result);  mud::render_solid(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<mud::Render*>(args[1])); }
void mud_render_clear_47(span<void*> args, void*& result) { UNUSED(result);  mud::render_clear(*static_cast<mud::GfxSystem*>(args[0]), *static_cast<mud::Render*>(args[1])); }

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
		static cstring ids[] = { "Position", "Rotation", "Scale", "Count" };
		static uint32_t values[] = { 0, 1, 2, 3 };
		static mud::AnimationTarget vars[] = { mud::AnimationTarget::Position, mud::AnimationTarget::Rotation, mud::AnimationTarget::Scale, mud::AnimationTarget::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
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
		static cstring ids[] = { "None", "Mix", "Add", "Sub", "Mul", "Normal", "Alpha" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6 };
		static mud::BlendMode vars[] = { mud::BlendMode::None, mud::BlendMode::Mix, mud::BlendMode::Add, mud::BlendMode::Sub, mud::BlendMode::Mul, mud::BlendMode::Normal, mud::BlendMode::Alpha};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_BlendMode__to_string,
		                           mud_BlendMode__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::CullMode>();
		static Meta meta = { t, &namspc({ "mud" }), "CullMode", sizeof(mud::CullMode), TypeClass::Enum };
		static cstring ids[] = { "None", "Front", "Back", "Count" };
		static uint32_t values[] = { 0, 1, 2, 3 };
		static mud::CullMode vars[] = { mud::CullMode::None, mud::CullMode::Front, mud::CullMode::Back, mud::CullMode::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
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
		Type& t = type<mud::DepthMethod>();
		static Meta meta = { t, &namspc({ "mud" }), "DepthMethod", sizeof(mud::DepthMethod), TypeClass::Enum };
		static cstring ids[] = { "Depth", "DepthPacked", "Distance", "Count" };
		static uint32_t values[] = { 0, 1, 2, 3 };
		static mud::DepthMethod vars[] = { mud::DepthMethod::Depth, mud::DepthMethod::DepthPacked, mud::DepthMethod::Distance, mud::DepthMethod::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_DepthMethod__to_string,
		                           mud_DepthMethod__to_value };
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
		static cstring ids[] = { "Disabled", "X2", "X4", "X8", "X16", "Count" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5 };
		static mud::MSAA vars[] = { mud::MSAA::Disabled, mud::MSAA::X2, mud::MSAA::X4, mud::MSAA::X8, mud::MSAA::X16, mud::MSAA::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_MSAA__to_string,
		                           mud_MSAA__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::MaterialBlock>();
		static Meta meta = { t, &namspc({ "mud" }), "MaterialBlock", sizeof(mud::MaterialBlock), TypeClass::Enum };
		static cstring ids[] = { "Base", "Alpha", "Solid", "Point", "Line", "Lit", "Pbr", "Phong", "Fresnel", "User", "Count" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		static mud::MaterialBlock vars[] = { mud::MaterialBlock::Base, mud::MaterialBlock::Alpha, mud::MaterialBlock::Solid, mud::MaterialBlock::Point, mud::MaterialBlock::Line, mud::MaterialBlock::Lit, mud::MaterialBlock::Pbr, mud::MaterialBlock::Phong, mud::MaterialBlock::Fresnel, mud::MaterialBlock::User, mud::MaterialBlock::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7], &vars[8], &vars[9], &vars[10]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_MaterialBlock__to_string,
		                           mud_MaterialBlock__to_value };
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
		static cstring ids[] = { "obj", "ply", "gltf", "Count" };
		static uint32_t values[] = { 0, 1, 2, 3 };
		static mud::ModelFormat vars[] = { mud::ModelFormat::obj, mud::ModelFormat::ply, mud::ModelFormat::gltf, mud::ModelFormat::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
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
		Type& t = type<mud::PassType>();
		static Meta meta = { t, &namspc({ "mud" }), "PassType", sizeof(mud::PassType), TypeClass::Enum };
		static cstring ids[] = { "VoxelGI", "Lightmap", "Shadowmap", "Probes", "Clear", "Depth", "Normals", "Shadow", "Geometry", "Lights", "Opaque", "Background", "Particles", "Alpha", "Solid", "Effects", "PostProcess", "Flip", "Count" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18 };
		static mud::PassType vars[] = { mud::PassType::VoxelGI, mud::PassType::Lightmap, mud::PassType::Shadowmap, mud::PassType::Probes, mud::PassType::Clear, mud::PassType::Depth, mud::PassType::Normals, mud::PassType::Shadow, mud::PassType::Geometry, mud::PassType::Lights, mud::PassType::Opaque, mud::PassType::Background, mud::PassType::Particles, mud::PassType::Alpha, mud::PassType::Solid, mud::PassType::Effects, mud::PassType::PostProcess, mud::PassType::Flip, mud::PassType::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7], &vars[8], &vars[9], &vars[10], &vars[11], &vars[12], &vars[13], &vars[14], &vars[15], &vars[16], &vars[17], &vars[18]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_PassType__to_string,
		                           mud_PassType__to_value };
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
		Type& t = type<mud::ShaderColor>();
		static Meta meta = { t, &namspc({ "mud" }), "ShaderColor", sizeof(mud::ShaderColor), TypeClass::Enum };
		static cstring ids[] = { "Shader", "Vertex", "Face" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::ShaderColor vars[] = { mud::ShaderColor::Shader, mud::ShaderColor::Vertex, mud::ShaderColor::Face};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_ShaderColor__to_string,
		                           mud_ShaderColor__to_value };
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
		static cstring ids[] = { "Wireframe", "Solid", "Shaded", "Volume", "Voxels", "Lightmap", "Clear", "Count" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
		static mud::Shading vars[] = { mud::Shading::Wireframe, mud::Shading::Solid, mud::Shading::Shaded, mud::Shading::Volume, mud::Shading::Voxels, mud::Shading::Lightmap, mud::Shading::Clear, mud::Shading::Count};
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
		static cstring ids[] = { "Source0", "Source1", "Source2", "Source3", "SourceDepth", "Color", "Albedo", "Diffuse", "Alpha", "Metallic", "Specular", "Roughness", "Shininess", "Emissive", "Normal", "AO", "Depth", "User0", "User1", "User2", "User3", "User4", "User5", "Radiance", "Shadow", "Lightmap", "ReflectionProbe", "GIProbe", "Skeleton", "Zones", "Materials", "Lights", "Clusters", "LightRecords" };
		static uint32_t values[] = { 0, 1, 2, 3, 3, 0, 0, 0, 1, 2, 2, 3, 3, 4, 5, 6, 7, 12, 13, 14, 15, 6, 7, 10, 11, 12, 13, 14, 15, 0, 8, 9, 13, 14 };
		static mud::TextureSampler vars[] = { mud::TextureSampler::Source0, mud::TextureSampler::Source1, mud::TextureSampler::Source2, mud::TextureSampler::Source3, mud::TextureSampler::SourceDepth, mud::TextureSampler::Color, mud::TextureSampler::Albedo, mud::TextureSampler::Diffuse, mud::TextureSampler::Alpha, mud::TextureSampler::Metallic, mud::TextureSampler::Specular, mud::TextureSampler::Roughness, mud::TextureSampler::Shininess, mud::TextureSampler::Emissive, mud::TextureSampler::Normal, mud::TextureSampler::AO, mud::TextureSampler::Depth, mud::TextureSampler::User0, mud::TextureSampler::User1, mud::TextureSampler::User2, mud::TextureSampler::User3, mud::TextureSampler::User4, mud::TextureSampler::User5, mud::TextureSampler::Radiance, mud::TextureSampler::Shadow, mud::TextureSampler::Lightmap, mud::TextureSampler::ReflectionProbe, mud::TextureSampler::GIProbe, mud::TextureSampler::Skeleton, mud::TextureSampler::Zones, mud::TextureSampler::Materials, mud::TextureSampler::Lights, mud::TextureSampler::Clusters, mud::TextureSampler::LightRecords};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7], &vars[8], &vars[9], &vars[10], &vars[11], &vars[12], &vars[13], &vars[14], &vars[15], &vars[16], &vars[17], &vars[18], &vars[19], &vars[20], &vars[21], &vars[22], &vars[23], &vars[24], &vars[25], &vars[26], &vars[27], &vars[28], &vars[29], &vars[30], &vars[31], &vars[32], &vars[33]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_TextureSampler__to_string,
		                           mud_TextureSampler__to_value };
		g_convert[t.m_id] = &convert;
	}
	
	// Sequences
	{
		Type& t = type<stl::span<mud::mat4>>();
		static Meta meta = { t, &namspc({ "stl" }), "span<mud::mat4>", sizeof(stl::span<mud::mat4>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::mat4>(),
		                             stl_span_mud_mat4__size,
		                             stl_span_mud_mat4__at};
		g_iterable[t.m_id] = &iterable;
	}
	{
		Type& t = type<stl::vector<mud::Animation*>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<mud::Animation*>", sizeof(stl::vector<mud::Animation*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::Animation>(),
		                             stl_vector_mud_Animation___size,
		                             stl_vector_mud_Animation___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_mud_Animation___push,
		                             stl_vector_mud_Animation___add,
		                             stl_vector_mud_Animation___remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<mud::AnimationPlay>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<mud::AnimationPlay>", sizeof(stl::vector<mud::AnimationPlay>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::AnimationPlay>(),
		                             stl_vector_mud_AnimationPlay__size,
		                             stl_vector_mud_AnimationPlay__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_mud_AnimationPlay__push,
		                             stl_vector_mud_AnimationPlay__add,
		                             stl_vector_mud_AnimationPlay__remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<mud::Material*>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<mud::Material*>", sizeof(stl::vector<mud::Material*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::Material>(),
		                             stl_vector_mud_Material___size,
		                             stl_vector_mud_Material___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_mud_Material___push,
		                             stl_vector_mud_Material___add,
		                             stl_vector_mud_Material___remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<mud::Mesh*>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<mud::Mesh*>", sizeof(stl::vector<mud::Mesh*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::Mesh>(),
		                             stl_vector_mud_Mesh___size,
		                             stl_vector_mud_Mesh___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_mud_Mesh___push,
		                             stl_vector_mud_Mesh___add,
		                             stl_vector_mud_Mesh___remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<mud::Model*>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<mud::Model*>", sizeof(stl::vector<mud::Model*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::Model>(),
		                             stl_vector_mud_Model___size,
		                             stl_vector_mud_Model___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_mud_Model___push,
		                             stl_vector_mud_Model___add,
		                             stl_vector_mud_Model___remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<mud::Texture*>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<mud::Texture*>", sizeof(stl::vector<mud::Texture*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::Texture>(),
		                             stl_vector_mud_Texture___size,
		                             stl_vector_mud_Texture___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_mud_Texture___push,
		                             stl_vector_mud_Texture___add,
		                             stl_vector_mud_Texture___remove };
		g_sequence[t.m_id] = &sequence;
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
			{ t, offsetof(mud::Animation, m_name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
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
			{ t, offsetof(mud::AnimationTrack, m_node_name), type<stl::string>(), "node_name", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::AnimationTrack, m_target), type<mud::AnimationTarget>(), "target", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::AnimationTrack, m_value_type), type<mud::Type>(), "value_type", value_type_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::AnimationTrack, m_length), type<float>(), "length", &length_default, Member::Value, nullptr },
			{ t, offsetof(mud::AnimationTrack, m_interpolation), type<mud::Interpolation>(), "interpolation", &interpolation_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// mud::AssetStore<mud::Flow>
	{
		Type& t = type<mud::AssetStore<mud::Flow>>();
		static Meta meta = { t, &namspc({ "mud" }), "AssetStore<mud::Flow>", sizeof(mud::AssetStore<mud::Flow>), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "get", Address(), mud_AssetStore_mud_Flow_get, { { "name", type<stl::string>(),  } }, { &type<mud::Flow>(), QualType::None } },
			{ t, "create", Address(), mud_AssetStore_mud_Flow_create, { { "name", type<stl::string>(),  } }, { &type<mud::Flow>(), QualType::None } },
			{ t, "fetch", Address(), mud_AssetStore_mud_Flow_fetch, { { "name", type<stl::string>(),  } }, { &type<mud::Flow>(), QualType::None } },
			{ t, "file", Address(), mud_AssetStore_mud_Flow_file, { { "name", type<stl::string>(),  } }, { &type<mud::Flow>(), QualType::None } },
			{ t, "file_at", Address(), mud_AssetStore_mud_Flow_file_at, { { "path", type<stl::string>(),  }, { "name", type<stl::string>(),  } }, { &type<mud::Flow>(), QualType::None } },
			{ t, "destroy", Address(), mud_AssetStore_mud_Flow_destroy, { { "name", type<stl::string>(),  } }, g_qvoid },
			{ t, "clear", Address(), mud_AssetStore_mud_Flow_clear, {}, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, methods, {}, };
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
			{ t, "get", Address(), mud_AssetStore_mud_Material_get, { { "name", type<stl::string>(),  } }, { &type<mud::Material>(), QualType::None } },
			{ t, "create", Address(), mud_AssetStore_mud_Material_create, { { "name", type<stl::string>(),  } }, { &type<mud::Material>(), QualType::None } },
			{ t, "fetch", Address(), mud_AssetStore_mud_Material_fetch, { { "name", type<stl::string>(),  } }, { &type<mud::Material>(), QualType::None } },
			{ t, "file", Address(), mud_AssetStore_mud_Material_file, { { "name", type<stl::string>(),  } }, { &type<mud::Material>(), QualType::None } },
			{ t, "file_at", Address(), mud_AssetStore_mud_Material_file_at, { { "path", type<stl::string>(),  }, { "name", type<stl::string>(),  } }, { &type<mud::Material>(), QualType::None } },
			{ t, "destroy", Address(), mud_AssetStore_mud_Material_destroy, { { "name", type<stl::string>(),  } }, g_qvoid },
			{ t, "clear", Address(), mud_AssetStore_mud_Material_clear, {}, g_qvoid }
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
			{ t, "get", Address(), mud_AssetStore_mud_Model_get, { { "name", type<stl::string>(),  } }, { &type<mud::Model>(), QualType::None } },
			{ t, "create", Address(), mud_AssetStore_mud_Model_create, { { "name", type<stl::string>(),  } }, { &type<mud::Model>(), QualType::None } },
			{ t, "fetch", Address(), mud_AssetStore_mud_Model_fetch, { { "name", type<stl::string>(),  } }, { &type<mud::Model>(), QualType::None } },
			{ t, "file", Address(), mud_AssetStore_mud_Model_file, { { "name", type<stl::string>(),  } }, { &type<mud::Model>(), QualType::None } },
			{ t, "file_at", Address(), mud_AssetStore_mud_Model_file_at, { { "path", type<stl::string>(),  }, { "name", type<stl::string>(),  } }, { &type<mud::Model>(), QualType::None } },
			{ t, "destroy", Address(), mud_AssetStore_mud_Model_destroy, { { "name", type<stl::string>(),  } }, g_qvoid },
			{ t, "clear", Address(), mud_AssetStore_mud_Model_clear, {}, g_qvoid }
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
			{ t, "get", Address(), mud_AssetStore_mud_Prefab_get, { { "name", type<stl::string>(),  } }, { &type<mud::Prefab>(), QualType::None } },
			{ t, "create", Address(), mud_AssetStore_mud_Prefab_create, { { "name", type<stl::string>(),  } }, { &type<mud::Prefab>(), QualType::None } },
			{ t, "fetch", Address(), mud_AssetStore_mud_Prefab_fetch, { { "name", type<stl::string>(),  } }, { &type<mud::Prefab>(), QualType::None } },
			{ t, "file", Address(), mud_AssetStore_mud_Prefab_file, { { "name", type<stl::string>(),  } }, { &type<mud::Prefab>(), QualType::None } },
			{ t, "file_at", Address(), mud_AssetStore_mud_Prefab_file_at, { { "path", type<stl::string>(),  }, { "name", type<stl::string>(),  } }, { &type<mud::Prefab>(), QualType::None } },
			{ t, "destroy", Address(), mud_AssetStore_mud_Prefab_destroy, { { "name", type<stl::string>(),  } }, g_qvoid },
			{ t, "clear", Address(), mud_AssetStore_mud_Prefab_clear, {}, g_qvoid }
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
			{ t, "get", Address(), mud_AssetStore_mud_Program_get, { { "name", type<stl::string>(),  } }, { &type<mud::Program>(), QualType::None } },
			{ t, "create", Address(), mud_AssetStore_mud_Program_create, { { "name", type<stl::string>(),  } }, { &type<mud::Program>(), QualType::None } },
			{ t, "fetch", Address(), mud_AssetStore_mud_Program_fetch, { { "name", type<stl::string>(),  } }, { &type<mud::Program>(), QualType::None } },
			{ t, "file", Address(), mud_AssetStore_mud_Program_file, { { "name", type<stl::string>(),  } }, { &type<mud::Program>(), QualType::None } },
			{ t, "file_at", Address(), mud_AssetStore_mud_Program_file_at, { { "path", type<stl::string>(),  }, { "name", type<stl::string>(),  } }, { &type<mud::Program>(), QualType::None } },
			{ t, "destroy", Address(), mud_AssetStore_mud_Program_destroy, { { "name", type<stl::string>(),  } }, g_qvoid },
			{ t, "clear", Address(), mud_AssetStore_mud_Program_clear, {}, g_qvoid }
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
			{ t, "get", Address(), mud_AssetStore_mud_Texture_get, { { "name", type<stl::string>(),  } }, { &type<mud::Texture>(), QualType::None } },
			{ t, "create", Address(), mud_AssetStore_mud_Texture_create, { { "name", type<stl::string>(),  } }, { &type<mud::Texture>(), QualType::None } },
			{ t, "fetch", Address(), mud_AssetStore_mud_Texture_fetch, { { "name", type<stl::string>(),  } }, { &type<mud::Texture>(), QualType::None } },
			{ t, "file", Address(), mud_AssetStore_mud_Texture_file, { { "name", type<stl::string>(),  } }, { &type<mud::Texture>(), QualType::None } },
			{ t, "file_at", Address(), mud_AssetStore_mud_Texture_file_at, { { "path", type<stl::string>(),  }, { "name", type<stl::string>(),  } }, { &type<mud::Texture>(), QualType::None } },
			{ t, "destroy", Address(), mud_AssetStore_mud_Texture_destroy, { { "name", type<stl::string>(),  } }, g_qvoid },
			{ t, "clear", Address(), mud_AssetStore_mud_Texture_clear, {}, g_qvoid }
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
		static mud::Texture* texture_default = nullptr;
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
			{ t, offsetof(mud::Background, m_custom_program), type<mud::Program>(), "custoprogram", custoprogram_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::Background, m_texture), type<mud::Texture>(), "texture", texture_default, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Batch
	{
		Type& t = type<mud::Batch>();
		static Meta meta = { t, &namspc({ "mud" }), "Batch", sizeof(mud::Batch), TypeClass::Struct };
		// bases
		// defaults
		static mud::Item* item_default = nullptr;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Batch__construct_0, {} },
			{ t, mud_Batch__construct_1, { { "item", type<mud::Item>(),  }, { "stride", type<uint16_t>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Batch__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Batch, m_item), type<mud::Item>(), "item", item_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::Batch, m_stride), type<uint16_t>(), "stride", nullptr, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "update_aabb", Address(), mud_Batch_update_aabb, { { "instances", type<stl::span<mud::mat4>>(),  } }, g_qvoid },
			{ t, "transforms", Address(), mud_Batch_transforms, { { "instances", type<stl::span<mud::mat4>>(),  } }, g_qvoid },
			{ t, "begin", Address(), mud_Batch_begin, { { "count", type<uint32_t>(),  } }, { &type<stl::span<float>>(), QualType::None } },
			{ t, "commit", Address(), mud_Batch_commit, { { "data", type<stl::span<float>>(),  } }, g_qvoid },
			{ t, "cache", Address(), mud_Batch_cache, { { "data", type<stl::span<float>>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, methods, {}, };
	}
	// mud::Bone
	{
		Type& t = type<mud::Bone>();
		static Meta meta = { t, &namspc({ "mud" }), "Bone", sizeof(mud::Bone), TypeClass::Struct };
		// bases
		// defaults
		static mud::quat rotation_default = ZeroQuat;
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
			{ t, offsetof(mud::Bone, m_position), type<mud::vec3>(), "position", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Bone, m_rotation), type<mud::quat>(), "rotation", &rotation_default, Member::Value, nullptr },
			{ t, offsetof(mud::Bone, m_scale), type<mud::vec3>(), "scale", nullptr, Member::Value, nullptr }
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
		static mud::vec3 eye_default = Z3;
		static mud::vec3 up_default = Y3;
		static float fov_default = 60.f;
		static float aspect_default = 1.f;
		static float near_default = 0.1f;
		static float far_default = 100.f;
		static bool orthographic_default = false;
		static float height_default = 1.f;
		static bool optimize_ends_default = true;
		static mud::vec4 lod_offsets_default = {0.1f,0.3f,0.6f,0.8f};
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Camera, m_eye), type<mud::vec3>(), "eye", &eye_default, Member::Value, nullptr },
			{ t, offsetof(mud::Camera, m_target), type<mud::vec3>(), "target", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Camera, m_up), type<mud::vec3>(), "up", &up_default, Member::Value, nullptr },
			{ t, offsetof(mud::Camera, m_transform), type<mud::mat4>(), "transform", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Camera, m_projection), type<mud::mat4>(), "projection", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Camera, m_fov), type<float>(), "fov", &fov_default, Member::Value, nullptr },
			{ t, offsetof(mud::Camera, m_aspect), type<float>(), "aspect", &aspect_default, Member::Value, nullptr },
			{ t, offsetof(mud::Camera, m_near), type<float>(), "near", &near_default, Member::Value, nullptr },
			{ t, offsetof(mud::Camera, m_far), type<float>(), "far", &far_default, Member::Value, nullptr },
			{ t, offsetof(mud::Camera, m_orthographic), type<bool>(), "orthographic", &orthographic_default, Member::Value, nullptr },
			{ t, offsetof(mud::Camera, m_height), type<float>(), "height", &height_default, Member::Value, nullptr },
			{ t, offsetof(mud::Camera, m_optimize_ends), type<bool>(), "optimize_ends", &optimize_ends_default, Member::Value, nullptr },
			{ t, offsetof(mud::Camera, m_lod_offsets), type<mud::vec4>(), "lod_offsets", &lod_offsets_default, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "set_look_at", Address(), mud_Camera_set_look_at, { { "eye", type<mud::vec3>(),  }, { "target", type<mud::vec3>(),  } }, g_qvoid },
			{ t, "set_isometric", Address(), mud_Camera_set_isometric, { { "angle", type<mud::IsometricAngle>(),  }, { "position", type<mud::vec3>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, methods, {}, };
	}
	// mud::Cascade
	{
		Type& t = type<mud::Cascade>();
		static Meta meta = { t, &namspc({ "mud" }), "Cascade", sizeof(mud::Cascade), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Cascade, m_texture), type<mud::Texture>(), "texture", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::Cascade, m_num_mips), type<size_t>(), "numips", nullptr, Member::Value, nullptr }
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
		static float depth_bias_default = 0.f;
		static float depth_normal_bias_default = 0.f;
		static float depth_z_far_default = 0.f;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_DepthParams__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_DepthParams__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::DepthParams, m_depth_bias), type<float>(), "depth_bias", &depth_bias_default, Member::Value, nullptr },
			{ t, offsetof(mud::DepthParams, m_depth_normal_bias), type<float>(), "depth_normal_bias", &depth_normal_bias_default, Member::Value, nullptr },
			{ t, offsetof(mud::DepthParams, m_depth_z_far), type<float>(), "depth_z_far", &depth_z_far_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Direct
	{
		Type& t = type<mud::Direct>();
		static Meta meta = { t, &namspc({ "mud" }), "Direct", sizeof(mud::Direct), TypeClass::Object };
		// bases
		// defaults
		static mud::Item* item_default = nullptr;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Direct__construct_0, {} },
			{ t, mud_Direct__construct_1, { { "item", type<mud::Item>(),  } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Direct, m_item), type<mud::Item>(), "item", item_default, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, {}, members, {}, {}, };
	}
	// mud::DistanceParams
	{
		Type& t = type<mud::DistanceParams>();
		static Meta meta = { t, &namspc({ "mud" }), "DistanceParams", sizeof(mud::DistanceParams), TypeClass::Struct };
		// bases
		// defaults
		static float near_default = 0.f;
		static float far_default = 1.f;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_DistanceParams__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_DistanceParams__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::DistanceParams, m_eye), type<mud::vec3>(), "eye", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::DistanceParams, m_near), type<float>(), "near", &near_default, Member::Value, nullptr },
			{ t, offsetof(mud::DistanceParams, m_far), type<float>(), "far", &far_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Flow
	{
		Type& t = type<mud::Flow>();
		static Meta meta = { t, &namspc({ "mud" }), "Flow", sizeof(mud::Flow), TypeClass::Struct };
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
			{ t, mud_Flow__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Flow__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Flow, m_name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Flow, m_duration), type<float>(), "duration", &duration_default, Member::Value, nullptr },
			{ t, offsetof(mud::Flow, m_start_time), type<float>(), "start_time", &start_time_default, Member::Value, nullptr },
			{ t, offsetof(mud::Flow, m_loop), type<bool>(), "loop", &loop_default, Member::Value, nullptr },
			{ t, offsetof(mud::Flow, m_shape), type<mud::ShapeVar>(), "shape", &shape_default, Member::NonMutable, nullptr },
			{ t, offsetof(mud::Flow, m_flow), type<mud::EmitterFlow>(), "flow", &flow_default, Member::Value, nullptr },
			{ t, offsetof(mud::Flow, m_billboard), type<bool>(), "billboard", &billboard_default, Member::Value, nullptr },
			{ t, offsetof(mud::Flow, m_direction), type<mud::vec3>(), "direction", &direction_default, Member::Value, nullptr },
			{ t, offsetof(mud::Flow, m_rotation), type<mud::quat>(), "rotation", &rotation_default, Member::Value, nullptr },
			{ t, offsetof(mud::Flow, m_blend_mode), type<mud::BlendMode>(), "blend_mode", &blend_mode_default, Member::Value, nullptr },
			{ t, offsetof(mud::Flow, m_volume), type<mud::ValueTrack<float>>(), "volume", &volume_default, Member::Value, nullptr },
			{ t, offsetof(mud::Flow, m_rate), type<mud::ValueTrack<uint32_t>>(), "rate", &rate_default, Member::Value, nullptr },
			{ t, offsetof(mud::Flow, m_lifetime), type<mud::ValueTrack<float>>(), "lifetime", &lifetime_default, Member::Value, nullptr },
			{ t, offsetof(mud::Flow, m_gravity), type<mud::ValueTrack<float>>(), "gravity", &gravity_default, Member::Value, nullptr },
			{ t, offsetof(mud::Flow, m_speed), type<mud::ValueTrack<float>>(), "speed", &speed_default, Member::Value, nullptr },
			{ t, offsetof(mud::Flow, m_angle), type<mud::ValueTrack<float>>(), "angle", &angle_default, Member::Value, nullptr },
			{ t, offsetof(mud::Flow, m_blend), type<mud::ValueTrack<float>>(), "blend", &blend_default, Member::Value, nullptr },
			{ t, offsetof(mud::Flow, m_colour), type<mud::ValueTrack<mud::Colour>>(), "colour", &colour_default, Member::Value, nullptr },
			{ t, offsetof(mud::Flow, m_scale), type<mud::ValueTrack<float>>(), "scale", &scale_default, Member::Value, nullptr },
			{ t, offsetof(mud::Flow, m_sprite_frame), type<mud::ValueTrack<float>>(), "sprite_frame", &sprite_frame_default, Member::Value, nullptr },
			{ t, offsetof(mud::Flow, m_sprite_name), type<stl::string>(), "sprite_name", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
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
		static Member members[] = {
			{ t, offsetof(mud::FrameBuffer, m_size), type<mud::uvec2>(), "size", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::FrameBuffer, m_tex), type<mud::Texture>(), "tex", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
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
	// mud::GfxWindow
	{
		Type& t = type<mud::GfxWindow>();
		static Meta meta = { t, &namspc({ "mud" }), "GfxWindow", sizeof(mud::GfxWindow), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
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
	// mud::GpuMesh
	{
		Type& t = type<mud::GpuMesh>();
		static Meta meta = { t, &namspc({ "mud" }), "GpuMesh", sizeof(mud::GpuMesh), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_GpuMesh__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_GpuMesh__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
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
	// mud::Import
	{
		Type& t = type<mud::Import>();
		static Meta meta = { t, &namspc({ "mud" }), "Import", sizeof(mud::Import), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Import, m_name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Import, m_file), type<stl::string>(), "file", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Import, m_path), type<stl::string>(), "path", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Import, m_config), type<mud::ImportConfig>(), "config", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Import, m_meshes), type<stl::vector<mud::Mesh*>>(), "meshes", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::Import, m_models), type<stl::vector<mud::Model*>>(), "models", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::Import, m_images), type<stl::vector<mud::Texture*>>(), "images", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::Import, m_materials), type<stl::vector<mud::Material*>>(), "materials", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// mud::ImportConfig
	{
		Type& t = type<mud::ImportConfig>();
		static Meta meta = { t, &namspc({ "mud" }), "ImportConfig", sizeof(mud::ImportConfig), TypeClass::Struct };
		// bases
		// defaults
		static mud::ModelFormat format_default = mud::ModelFormat::obj;
		static mud::quat rotation_default = ZeroQuat;
		static mud::mat4 transform_default = bxidentity();
		static bool force_reimport_default = false;
		static bool cache_geometry_default = false;
		static bool optimize_geometry_default = false;
		static bool need_normals_default = true;
		static bool need_uvs_default = true;
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
			{ t, offsetof(mud::ImportConfig, m_position), type<mud::vec3>(), "position", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::ImportConfig, m_rotation), type<mud::quat>(), "rotation", &rotation_default, Member::Value, nullptr },
			{ t, offsetof(mud::ImportConfig, m_scale), type<mud::vec3>(), "scale", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::ImportConfig, m_transform), type<mud::mat4>(), "transform", &transform_default, Member::Value, nullptr },
			{ t, offsetof(mud::ImportConfig, m_exclude_elements), type<stl::vector<stl::string>>(), "exclude_elements", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::ImportConfig, m_exclude_materials), type<stl::vector<stl::string>>(), "exclude_materials", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::ImportConfig, m_include_elements), type<stl::vector<stl::string>>(), "include_elements", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::ImportConfig, m_include_materials), type<stl::vector<stl::string>>(), "include_materials", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::ImportConfig, m_suffix), type<stl::string>(), "suffix", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::ImportConfig, m_force_reimport), type<bool>(), "force_reimport", &force_reimport_default, Member::Value, nullptr },
			{ t, offsetof(mud::ImportConfig, m_cache_geometry), type<bool>(), "cache_geometry", &cache_geometry_default, Member::Value, nullptr },
			{ t, offsetof(mud::ImportConfig, m_optimize_geometry), type<bool>(), "optimize_geometry", &optimize_geometry_default, Member::Value, nullptr },
			{ t, offsetof(mud::ImportConfig, m_need_normals), type<bool>(), "need_normals", &need_normals_default, Member::Value, nullptr },
			{ t, offsetof(mud::ImportConfig, m_need_uvs), type<bool>(), "need_uvs", &need_uvs_default, Member::Value, nullptr },
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
		static mud::Node3* node_default = nullptr;
		static mud::Model* model_default = nullptr;
		static uint32_t flags_default = 0;
		static mud::Colour colour_default = mud::Colour::White;
		static mud::Material* material_default = nullptr;
		static bool visible_default = true;
		static mud::ItemShadow shadow_default = mud::ItemShadow::Default;
		static mud::Rig* rig_default = nullptr;
		static mud::Batch* batch_default = nullptr;
		static uint32_t construct_1_flags_default = 0;
		static mud::Material* construct_1_material_default = nullptr;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Item__construct_0, {} },
			{ t, mud_Item__construct_1, { { "node", type<mud::Node3>(),  }, { "model", type<mud::Model>(),  }, { "flags", type<uint32_t>(), Param::Default, &construct_1_flags_default }, { "material", type<mud::Material>(), Param::Flags(Param::Nullable|Param::Default), &construct_1_material_default } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Item, m_node), type<mud::Node3>(), "node", node_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::Item, m_model), type<mud::Model>(), "model", model_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::Item, m_flags), type<uint32_t>(), "flags", &flags_default, Member::Value, nullptr },
			{ t, offsetof(mud::Item, m_colour), type<mud::Colour>(), "colour", &colour_default, Member::Value, nullptr },
			{ t, offsetof(mud::Item, m_material), type<mud::Material>(), "material", material_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::Item, m_visible), type<bool>(), "visible", &visible_default, Member::Value, nullptr },
			{ t, offsetof(mud::Item, m_shadow), type<mud::ItemShadow>(), "shadow", &shadow_default, Member::Value, nullptr },
			{ t, offsetof(mud::Item, m_rig), type<mud::Rig>(), "rig", rig_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::Item, m_aabb), type<mud::Aabb>(), "aabb", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Item, m_batch), type<mud::Batch>(), "batch", batch_default, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "update_aabb", Address(), mud_Item_update_aabb, {}, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, members, methods, {}, };
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
		static mud::Node3* node_default = nullptr;
		static mud::LightType type_default = mud::LightType::Point;
		static bool visible_default = true;
		static mud::Colour colour_default = mud::Colour::White;
		static float range_default = 1.f;
		static float energy_default = 1.f;
		static float specular_default = 1.f;
		static float attenuation_default = 0.5f;
		static bool shadows_default = false;
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
		static mud::LightType construct_0_type_default = mud::LightType::Point;
		static bool construct_0_shadows_default = false;
		static mud::Colour construct_0_colour_default = mud::Colour::White;
		static float construct_0_energy_default = 1.f;
		static float construct_0_range_default = 1.f;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Light__construct_0, { { "node", type<mud::Node3>(),  }, { "type", type<mud::LightType>(), Param::Default, &construct_0_type_default }, { "shadows", type<bool>(), Param::Default, &construct_0_shadows_default }, { "colour", type<mud::Colour>(), Param::Default, &construct_0_colour_default }, { "energy", type<float>(), Param::Default, &construct_0_energy_default }, { "range", type<float>(), Param::Default, &construct_0_range_default } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Light, m_node), type<mud::Node3>(), "node", node_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::Light, m_type), type<mud::LightType>(), "type", &type_default, Member::Value, nullptr },
			{ t, offsetof(mud::Light, m_visible), type<bool>(), "visible", &visible_default, Member::Value, nullptr },
			{ t, offsetof(mud::Light, m_colour), type<mud::Colour>(), "colour", &colour_default, Member::Value, nullptr },
			{ t, offsetof(mud::Light, m_range), type<float>(), "range", &range_default, Member::Value, nullptr },
			{ t, offsetof(mud::Light, m_energy), type<float>(), "energy", &energy_default, Member::Value, nullptr },
			{ t, offsetof(mud::Light, m_specular), type<float>(), "specular", &specular_default, Member::Value, nullptr },
			{ t, offsetof(mud::Light, m_attenuation), type<float>(), "attenuation", &attenuation_default, Member::Value, nullptr },
			{ t, offsetof(mud::Light, m_shadows), type<bool>(), "shadows", &shadows_default, Member::Value, nullptr },
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
		static Class cls = { t, {}, {}, constructors, {}, members, {}, {}, };
	}
	// mud::Lines
	{
		Type& t = type<mud::Lines>();
		static Meta meta = { t, &namspc({ "mud" }), "Lines", sizeof(mud::Lines), TypeClass::Object };
		// bases
		// defaults
		static mud::Colour add_0_start_colour_default = mud::Colour(1.f);
		static mud::Colour add_0_end_colour_default = mud::Colour(1.f);
		static mud::Colour start_0_colour_default = mud::Colour(1.f);
		static mud::Colour next_0_colour_default = mud::Colour(1.f);
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Lines__construct_0, {} },
			{ t, mud_Lines__construct_1, { { "points", type<stl::vector<mud::vec3>>(),  } } },
			{ t, mud_Lines__construct_2, { { "curve", type<mud::Curve3>(),  }, { "subdiv", type<size_t>(),  } } }
		};
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "add", Address(), mud_Lines_add, { { "start", type<mud::vec3>(),  }, { "end", type<mud::vec3>(),  }, { "start_colour", type<mud::Colour>(), Param::Default, &add_0_start_colour_default }, { "end_colour", type<mud::Colour>(), Param::Default, &add_0_end_colour_default } }, g_qvoid },
			{ t, "start", Address(), mud_Lines_start, { { "position", type<mud::vec3>(),  }, { "colour", type<mud::Colour>(), Param::Default, &start_0_colour_default } }, g_qvoid },
			{ t, "next", Address(), mud_Lines_next, { { "position", type<mud::vec3>(),  }, { "colour", type<mud::Colour>(), Param::Default, &next_0_colour_default } }, g_qvoid },
			{ t, "setup", Address(), mud_Lines_setup, {}, g_qvoid },
			{ t, "write", Address(), mud_Lines_write, { { "mesh", type<mud::Mesh>(),  } }, g_qvoid },
			{ t, "commit", Address(), mud_Lines_commit, { { "batch", type<mud::Batch>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, {}, methods, {}, };
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
			{ t, offsetof(mud::Material, m_name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Material, m_builtin), type<bool>(), "builtin", &builtin_default, Member::Value, nullptr },
			{ t, offsetof(mud::Material, m_program), type<mud::Program>(), "program", program_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::Material, m_base), type<mud::MaterialBase>(), "base", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Material, m_alpha), type<mud::MaterialAlpha>(), "alpha", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Material, m_solid), type<mud::MaterialSolid>(), "solid", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Material, m_point), type<mud::MaterialPoint>(), "point", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Material, m_line), type<mud::MaterialLine>(), "line", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Material, m_lit), type<mud::MaterialLit>(), "lit", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Material, m_pbr), type<mud::MaterialPbr>(), "pbr", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Material, m_phong), type<mud::MaterialPhong>(), "phong", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Material, m_fresnel), type<mud::MaterialFresnel>(), "fresnel", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Material, m_user), type<mud::MaterialUser>(), "user", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// mud::MaterialAlpha
	{
		Type& t = type<mud::MaterialAlpha>();
		static Meta meta = { t, &namspc({ "mud" }), "MaterialAlpha", sizeof(mud::MaterialAlpha), TypeClass::Struct };
		// bases
		// defaults
		static mud::MaterialParam<float> alpha_default = {1.f,nullptr};
		static float alpha_scissor_default = 0.5f;
		static bool alpha_test_default = false;
		static bool is_alpha_default = false;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_MaterialAlpha__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_MaterialAlpha__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::MaterialAlpha, m_alpha), type<mud::MaterialParam<float>>(), "alpha", &alpha_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialAlpha, m_alpha_scissor), type<float>(), "alpha_scissor", &alpha_scissor_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialAlpha, m_alpha_test), type<bool>(), "alpha_test", &alpha_test_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialAlpha, m_is_alpha), type<bool>(), "is_alpha", &is_alpha_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::MaterialBase
	{
		Type& t = type<mud::MaterialBase>();
		static Meta meta = { t, &namspc({ "mud" }), "MaterialBase", sizeof(mud::MaterialBase), TypeClass::Struct };
		// bases
		// defaults
		static mud::BlendMode blend_mode_default = mud::BlendMode::None;
		static mud::CullMode cull_mode_default = mud::CullMode::Back;
		static mud::DepthDraw depth_draw_default = mud::DepthDraw::Enabled;
		static mud::DepthTest depth_test_default = mud::DepthTest::Enabled;
		static mud::vec2 uv0_scale_default = {1.f,1.f};
		static mud::vec2 uv0_offset_default = {0.f,0.f};
		static mud::vec2 uv1_scale_default = {1.f,1.f};
		static mud::vec2 uv1_offset_default = {0.f,0.f};
		static mud::ShaderColor shader_color_default = mud::ShaderColor::Shader;
		static bool flat_shaded_default = false;
		static bool screen_filter_default = false;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_MaterialBase__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_MaterialBase__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::MaterialBase, m_blend_mode), type<mud::BlendMode>(), "blend_mode", &blend_mode_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialBase, m_cull_mode), type<mud::CullMode>(), "cull_mode", &cull_mode_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialBase, m_depth_draw), type<mud::DepthDraw>(), "depth_draw", &depth_draw_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialBase, m_depth_test), type<mud::DepthTest>(), "depth_test", &depth_test_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialBase, m_uv0_scale), type<mud::vec2>(), "uv0_scale", &uv0_scale_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialBase, m_uv0_offset), type<mud::vec2>(), "uv0_offset", &uv0_offset_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialBase, m_uv1_scale), type<mud::vec2>(), "uv1_scale", &uv1_scale_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialBase, m_uv1_offset), type<mud::vec2>(), "uv1_offset", &uv1_offset_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialBase, m_shader_color), type<mud::ShaderColor>(), "shader_color", &shader_color_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialBase, m_flat_shaded), type<bool>(), "flat_shaded", &flat_shaded_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialBase, m_screen_filter), type<bool>(), "screen_filter", &screen_filter_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialBase, m_anisotropy), type<float>(), "anisotropy", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::MaterialFresnel
	{
		Type& t = type<mud::MaterialFresnel>();
		static Meta meta = { t, &namspc({ "mud" }), "MaterialFresnel", sizeof(mud::MaterialFresnel), TypeClass::Struct };
		// bases
		// defaults
		static mud::MaterialParam<mud::Colour> value_default = {Colour::White,nullptr};
		static float fresnel_scale_default = 1.f;
		static float fresnel_bias_default = 0.01f;
		static float fresnel_power_default = 5.f;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_MaterialFresnel__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_MaterialFresnel__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::MaterialFresnel, m_value), type<mud::MaterialParam<mud::Colour>>(), "value", &value_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialFresnel, m_fresnel_scale), type<float>(), "fresnel_scale", &fresnel_scale_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialFresnel, m_fresnel_bias), type<float>(), "fresnel_bias", &fresnel_bias_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialFresnel, m_fresnel_power), type<float>(), "fresnel_power", &fresnel_power_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::MaterialLine
	{
		Type& t = type<mud::MaterialLine>();
		static Meta meta = { t, &namspc({ "mud" }), "MaterialLine", sizeof(mud::MaterialLine), TypeClass::Struct };
		// bases
		// defaults
		static float line_width_default = 1.f;
		static bool dashed_default = false;
		static float dash_scale_default = 1.f;
		static float dash_size_default = 1.f;
		static float dash_gap_default = 1.f;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_MaterialLine__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_MaterialLine__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::MaterialLine, m_line_width), type<float>(), "line_width", &line_width_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialLine, m_dashed), type<bool>(), "dashed", &dashed_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialLine, m_dash_scale), type<float>(), "dash_scale", &dash_scale_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialLine, m_dash_size), type<float>(), "dash_size", &dash_size_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialLine, m_dash_gap), type<float>(), "dash_gap", &dash_gap_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::MaterialLit
	{
		Type& t = type<mud::MaterialLit>();
		static Meta meta = { t, &namspc({ "mud" }), "MaterialLit", sizeof(mud::MaterialLit), TypeClass::Struct };
		// bases
		// defaults
		static mud::MaterialParam<mud::Colour> emissive_default = {rgba(0x00000000),nullptr};
		static float emissive_energy_default = 0.f;
		static mud::MaterialParam<float> normal_default = {1.f,nullptr};
		static mud::MaterialParam<float> bump_default = {1.f,nullptr};
		static mud::MaterialParam<float> displace_default = {1.f,nullptr};
		static float displace_bias_default = 0.f;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_MaterialLit__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_MaterialLit__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::MaterialLit, m_emissive), type<mud::MaterialParam<mud::Colour>>(), "emissive", &emissive_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialLit, m_emissive_energy), type<float>(), "emissive_energy", &emissive_energy_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialLit, m_normal), type<mud::MaterialParam<float>>(), "normal", &normal_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialLit, m_bump), type<mud::MaterialParam<float>>(), "bump", &bump_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialLit, m_displace), type<mud::MaterialParam<float>>(), "displace", &displace_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialLit, m_displace_bias), type<float>(), "displace_bias", &displace_bias_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialLit, m_occlusion), type<mud::MaterialParam<float>>(), "occlusion", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialLit, m_lightmap), type<mud::MaterialParam<float>>(), "lightmap", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
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
			{ t, mud_MaterialParam_float__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_MaterialParam_float__copy_construct }
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
			{ t, mud_MaterialParam_mud_Colour__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_MaterialParam_mud_Colour__copy_construct }
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
	// mud::MaterialParam<mud::vec4>
	{
		Type& t = type<mud::MaterialParam<mud::vec4>>();
		static Meta meta = { t, &namspc({ "mud" }), "MaterialParam<mud::vec4>", sizeof(mud::MaterialParam<mud::vec4>), TypeClass::Struct };
		// bases
		// defaults
		static mud::Texture* texture_default = nullptr;
		static mud::TextureChannel channel_default = mud::TextureChannel::All;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_MaterialParam_mud_vec4__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_MaterialParam_mud_vec4__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::MaterialParam<mud::vec4>, m_value), type<mud::vec4>(), "value", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialParam<mud::vec4>, m_texture), type<mud::Texture>(), "texture", texture_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::MaterialParam<mud::vec4>, m_channel), type<mud::TextureChannel>(), "channel", &channel_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::MaterialPbr
	{
		Type& t = type<mud::MaterialPbr>();
		static Meta meta = { t, &namspc({ "mud" }), "MaterialPbr", sizeof(mud::MaterialPbr), TypeClass::Struct };
		// bases
		// defaults
		static mud::MaterialParam<mud::Colour> albedo_default = {Colour::White,nullptr};
		static float specular_default = 0.5f;
		static mud::MaterialParam<float> metallic_default = {0.f,nullptr,TextureChannel::Red};
		static mud::MaterialParam<float> roughness_default = {1.f,nullptr,TextureChannel::Red};
		static mud::MaterialParam<float> depth_default = {-0.02f,nullptr};
		static bool deep_parallax_default = false;
		static bool scene_environment_default = true;
		static mud::PbrDiffuseMode diffuse_mode_default = mud::PbrDiffuseMode::Burley;
		static mud::PbrSpecularMode specular_mode_default = mud::PbrSpecularMode::SchlickGGX;
		static float construct_1_metallic_default = 0.f;
		static float construct_1_roughness_default = 1.f;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_MaterialPbr__construct_0, {} },
			{ t, mud_MaterialPbr__construct_1, { { "albedo", type<mud::Colour>(),  }, { "metallic", type<float>(), Param::Default, &construct_1_metallic_default }, { "roughness", type<float>(), Param::Default, &construct_1_roughness_default } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_MaterialPbr__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::MaterialPbr, m_albedo), type<mud::MaterialParam<mud::Colour>>(), "albedo", &albedo_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialPbr, m_specular), type<float>(), "specular", &specular_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialPbr, m_metallic), type<mud::MaterialParam<float>>(), "metallic", &metallic_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialPbr, m_roughness), type<mud::MaterialParam<float>>(), "roughness", &roughness_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialPbr, m_rim), type<mud::MaterialParam<float>>(), "rim", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialPbr, m_rim_tint), type<float>(), "ritint", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialPbr, m_clearcoat), type<mud::MaterialParam<float>>(), "clearcoat", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialPbr, m_clearcoat_gloss), type<float>(), "clearcoat_gloss", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialPbr, m_anisotropy), type<mud::MaterialParam<float>>(), "anisotropy", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialPbr, m_subsurface), type<mud::MaterialParam<float>>(), "subsurface", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialPbr, m_refraction), type<mud::MaterialParam<float>>(), "refraction", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialPbr, m_depth), type<mud::MaterialParam<float>>(), "depth", &depth_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialPbr, m_transmission), type<mud::MaterialParam<mud::Colour>>(), "transmission", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialPbr, m_deep_parallax), type<bool>(), "deep_parallax", &deep_parallax_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialPbr, m_scene_environment), type<bool>(), "scene_environment", &scene_environment_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialPbr, m_diffuse_mode), type<mud::PbrDiffuseMode>(), "diffuse_mode", &diffuse_mode_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialPbr, m_specular_mode), type<mud::PbrSpecularMode>(), "specular_mode", &specular_mode_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::MaterialPhong
	{
		Type& t = type<mud::MaterialPhong>();
		static Meta meta = { t, &namspc({ "mud" }), "MaterialPhong", sizeof(mud::MaterialPhong), TypeClass::Struct };
		// bases
		// defaults
		static mud::MaterialParam<mud::Colour> diffuse_default = {rgb(0xffffff),nullptr};
		static mud::MaterialParam<mud::Colour> specular_default = {rgb(0x111111),nullptr};
		static mud::MaterialParam<float> shininess_default = {1.f,nullptr};
		static mud::MaterialParam<float> reflectivity_default = {1.f,nullptr};
		static mud::MaterialParam<float> refraction_default = {0.98f,nullptr};
		static bool toon_default = false;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_MaterialPhong__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_MaterialPhong__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::MaterialPhong, m_diffuse), type<mud::MaterialParam<mud::Colour>>(), "diffuse", &diffuse_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialPhong, m_specular), type<mud::MaterialParam<mud::Colour>>(), "specular", &specular_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialPhong, m_shininess), type<mud::MaterialParam<float>>(), "shininess", &shininess_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialPhong, m_reflectivity), type<mud::MaterialParam<float>>(), "reflectivity", &reflectivity_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialPhong, m_refraction), type<mud::MaterialParam<float>>(), "refraction", &refraction_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialPhong, m_toon), type<bool>(), "toon", &toon_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::MaterialPoint
	{
		Type& t = type<mud::MaterialPoint>();
		static Meta meta = { t, &namspc({ "mud" }), "MaterialPoint", sizeof(mud::MaterialPoint), TypeClass::Struct };
		// bases
		// defaults
		static float point_size_default = 1.f;
		static bool project_default = false;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_MaterialPoint__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_MaterialPoint__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::MaterialPoint, m_point_size), type<float>(), "point_size", &point_size_default, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialPoint, m_project), type<bool>(), "project", &project_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::MaterialSolid
	{
		Type& t = type<mud::MaterialSolid>();
		static Meta meta = { t, &namspc({ "mud" }), "MaterialSolid", sizeof(mud::MaterialSolid), TypeClass::Struct };
		// bases
		// defaults
		static mud::MaterialParam<mud::Colour> colour_default = {Colour::White,nullptr};
		// constructors
		static Constructor constructors[] = {
			{ t, mud_MaterialSolid__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_MaterialSolid__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::MaterialSolid, m_colour), type<mud::MaterialParam<mud::Colour>>(), "colour", &colour_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::MaterialUser
	{
		Type& t = type<mud::MaterialUser>();
		static Meta meta = { t, &namspc({ "mud" }), "MaterialUser", sizeof(mud::MaterialUser), TypeClass::Struct };
		// bases
		// defaults
		static mud::Texture* tex0_default = nullptr;
		static mud::Texture* tex1_default = nullptr;
		static mud::Texture* tex2_default = nullptr;
		static mud::Texture* tex3_default = nullptr;
		static mud::Texture* tex4_default = nullptr;
		static mud::Texture* tex5_default = nullptr;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_MaterialUser__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_MaterialUser__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::MaterialUser, m_tex0), type<mud::Texture>(), "tex0", tex0_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::MaterialUser, m_tex1), type<mud::Texture>(), "tex1", tex1_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::MaterialUser, m_tex2), type<mud::Texture>(), "tex2", tex2_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::MaterialUser, m_tex3), type<mud::Texture>(), "tex3", tex3_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::MaterialUser, m_tex4), type<mud::Texture>(), "tex4", tex4_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::MaterialUser, m_tex5), type<mud::Texture>(), "tex5", tex5_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::MaterialUser, m_attr0), type<mud::vec4>(), "attr0", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialUser, m_attr1), type<mud::vec4>(), "attr1", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialUser, m_attr2), type<mud::vec4>(), "attr2", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialUser, m_attr3), type<mud::vec4>(), "attr3", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialUser, m_attr4), type<mud::vec4>(), "attr4", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::MaterialUser, m_attr5), type<mud::vec4>(), "attr5", nullptr, Member::Value, nullptr }
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
		static mud::PrimitiveType primitive_default = mud::PrimitiveType::Triangles;
		static mud::Aabb aabb_default = {};
		static float radius_default = 0.f;
		static bool readback_default = false;
		static uint32_t vertex_format_default = 0;
		static bool qnormals_default = false;
		static uint32_t vertex_count_default = 0;
		static uint32_t index_count_default = 0;
		static bool index32_default = false;
		static mud::Material* material_default = nullptr;
		static bool is_dynamic_default = false;
		static bool is_direct_default = false;
		static bool write_0_optimize_default = false;
		static bool write_0_dynamic_default = false;
		static bool upload_0_optimize_default = false;
		static uint32_t direct_0_index_count_default = 0;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Mesh, m_name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Mesh, m_index), type<uint16_t>(), "index", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Mesh, m_primitive), type<mud::PrimitiveType>(), "primitive", &primitive_default, Member::Value, nullptr },
			{ t, offsetof(mud::Mesh, m_aabb), type<mud::Aabb>(), "aabb", &aabb_default, Member::Value, nullptr },
			{ t, offsetof(mud::Mesh, m_radius), type<float>(), "radius", &radius_default, Member::Value, nullptr },
			{ t, offsetof(mud::Mesh, m_origin), type<mud::vec3>(), "origin", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Mesh, m_readback), type<bool>(), "readback", &readback_default, Member::Value, nullptr },
			{ t, offsetof(mud::Mesh, m_vertex_format), type<uint32_t>(), "vertex_format", &vertex_format_default, Member::Value, nullptr },
			{ t, offsetof(mud::Mesh, m_qnormals), type<bool>(), "qnormals", &qnormals_default, Member::Value, nullptr },
			{ t, offsetof(mud::Mesh, m_vertex_count), type<uint32_t>(), "vertex_count", &vertex_count_default, Member::Value, nullptr },
			{ t, offsetof(mud::Mesh, m_index_count), type<uint32_t>(), "index_count", &index_count_default, Member::Value, nullptr },
			{ t, offsetof(mud::Mesh, m_index32), type<bool>(), "index32", &index32_default, Member::Value, nullptr },
			{ t, offsetof(mud::Mesh, m_material), type<mud::Material>(), "material", material_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::Mesh, m_is_dynamic), type<bool>(), "is_dynamic", &is_dynamic_default, Member::Value, nullptr },
			{ t, offsetof(mud::Mesh, m_is_direct), type<bool>(), "is_direct", &is_direct_default, Member::Value, nullptr },
			{ t, offsetof(mud::Mesh, m_cache), type<mud::MeshAdapter>(), "cache", nullptr, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "clear", Address(), mud_Mesh_clear, {}, g_qvoid },
			{ t, "write", Address(), mud_Mesh_write, { { "packer", type<mud::MeshPacker>(),  }, { "optimize", type<bool>(), Param::Default, &write_0_optimize_default }, { "dynamic", type<bool>(), Param::Default, &write_0_dynamic_default } }, g_qvoid },
			{ t, "upload", Address(), mud_Mesh_upload, { { "gpu_mesh", type<mud::GpuMesh>(),  }, { "optimize", type<bool>(), Param::Default, &upload_0_optimize_default } }, g_qvoid },
			{ t, "cache", Address(), mud_Mesh_cache, { { "gpu_mesh", type<mud::GpuMesh>(),  } }, g_qvoid },
			{ t, "direct", Address(), mud_Mesh_direct, { { "vertex_format", type<uint32_t>(),  }, { "vertex_count", type<uint32_t>(),  }, { "index_count", type<uint32_t>(), Param::Default, &direct_0_index_count_default } }, { &type<mud::MeshAdapter>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, methods, {}, };
	}
	// mud::Mime
	{
		Type& t = type<mud::Mime>();
		static Meta meta = { t, &namspc({ "mud" }), "Mime", sizeof(mud::Mime), TypeClass::Object };
		// bases
		// defaults
		static bool active_default = true;
		static float speed_scale_default = 1.f;
		static float default_blend_time_default = 1.f;
		static float start_0_blend_default = 0.f;
		static float start_0_speed_default = 1.f;
		static bool start_0_transient_default = false;
		static float play_0_blend_default = 0.f;
		static float play_0_speed_default = 1.f;
		static bool play_0_transient_default = false;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Mime, m_playing), type<stl::vector<mud::AnimationPlay>>(), "playing", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::Mime, m_queue), type<stl::vector<mud::Animation*>>(), "queue", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::Mime, m_active), type<bool>(), "active", &active_default, Member::Value, nullptr },
			{ t, offsetof(mud::Mime, m_speed_scale), type<float>(), "speed_scale", &speed_scale_default, Member::Value, nullptr },
			{ t, offsetof(mud::Mime, m_default_blend_time), type<float>(), "default_blend_time", &default_blend_time_default, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "start", Address(), mud_Mime_start, { { "animation", type<const char*>(), Param::Nullable }, { "loop", type<bool>(),  }, { "blend", type<float>(), Param::Default, &start_0_blend_default }, { "speed", type<float>(), Param::Default, &start_0_speed_default }, { "transient", type<bool>(), Param::Default, &start_0_transient_default } }, g_qvoid },
			{ t, "play", Address(), mud_Mime_play, { { "animation", type<mud::Animation>(),  }, { "loop", type<bool>(),  }, { "blend", type<float>(), Param::Default, &play_0_blend_default }, { "speed", type<float>(), Param::Default, &play_0_speed_default }, { "transient", type<bool>(), Param::Default, &play_0_transient_default } }, g_qvoid },
			{ t, "seek", Address(), mud_Mime_seek, { { "time", type<float>(),  } }, g_qvoid },
			{ t, "pause", Address(), mud_Mime_pause, {}, g_qvoid },
			{ t, "stop", Address(), mud_Mime_stop, {}, g_qvoid },
			{ t, "advance", Address(), mud_Mime_advance, { { "time", type<float>(),  } }, g_qvoid },
			{ t, "next_animation", Address(), mud_Mime_next_animation, {}, g_qvoid },
			{ t, "playing", Address(), mud_Mime_playing, {}, { &type<stl::string>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, methods, {}, };
	}
	// mud::Model
	{
		Type& t = type<mud::Model>();
		static Meta meta = { t, &namspc({ "mud" }), "Model", sizeof(mud::Model), TypeClass::Object };
		// bases
		// defaults
		static mud::Aabb aabb_default = {vec3(0.f),vec3(0.f)};
		static float radius_default = 0.f;
		static bool add_mesh_0_readback_default = false;
		static int add_item_0_skin_default = -1;
		static mud::Colour add_item_0_colour_default = mud::Colour::White;
		static mud::Material* add_item_0_material_default = nullptr;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Model, m_name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Model, m_index), type<uint16_t>(), "index", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Model, m_aabb), type<mud::Aabb>(), "aabb", &aabb_default, Member::Value, nullptr },
			{ t, offsetof(mud::Model, m_radius), type<float>(), "radius", &radius_default, Member::Value, nullptr },
			{ t, offsetof(mud::Model, m_origin), type<mud::vec3>(), "origin", nullptr, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "get_mesh", Address(), mud_Model_get_mesh, { { "index", type<size_t>(),  } }, { &type<mud::Mesh>(), QualType::None } },
			{ t, "add_mesh", Address(), mud_Model_add_mesh, { { "name", type<stl::string>(),  }, { "readback", type<bool>(), Param::Default, &add_mesh_0_readback_default } }, { &type<mud::Mesh>(), QualType::None } },
			{ t, "add_rig", Address(), mud_Model_add_rig, { { "name", type<stl::string>(),  } }, { &type<mud::Rig>(), QualType::None } },
			{ t, "add_item", Address(), mud_Model_add_item, { { "mesh", type<mud::Mesh>(),  }, { "transform", type<mud::mat4>(),  }, { "skin", type<int>(), Param::Default, &add_item_0_skin_default }, { "colour", type<mud::Colour>(), Param::Default, &add_item_0_colour_default }, { "material", type<mud::Material>(), Param::Flags(Param::Nullable|Param::Default), &add_item_0_material_default } }, { &type<mud::ModelItem>(), QualType::None } },
			{ t, "prepare", Address(), mud_Model_prepare, {}, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, methods, {}, };
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
		static mud::mat4 transform_default = bxidentity();
		static mud::quat construct_2_rotation_default = ZeroQuat;
		static mud::vec3 construct_2_scale_default = vec3(1.f);
		static mud::quat apply_0_rotation_default = ZeroQuat;
		static mud::vec3 apply_0_scale_default = vec3(1.f);
		static mud::quat derive_0_rotation_default = ZeroQuat;
		static mud::vec3 derive_0_scale_default = vec3(1.f);
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Node3__construct_0, {} },
			{ t, mud_Node3__construct_1, { { "transform", type<mud::mat4>(),  } } },
			{ t, mud_Node3__construct_2, { { "position", type<mud::vec3>(),  }, { "rotation", type<mud::quat>(), Param::Default, &construct_2_rotation_default }, { "scale", type<mud::vec3>(), Param::Default, &construct_2_scale_default } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Node3, m_transform), type<mud::mat4>(), "transform", &transform_default, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "apply", Address(), mud_Node3_apply, { { "position", type<mud::vec3>(),  }, { "rotation", type<mud::quat>(), Param::Default, &apply_0_rotation_default }, { "scale", type<mud::vec3>(), Param::Default, &apply_0_scale_default } }, g_qvoid },
			{ t, "derive", Address(), mud_Node3_derive, { { "parent", type<mud::Node3>(),  }, { "position", type<mud::vec3>(),  }, { "rotation", type<mud::quat>(), Param::Default, &derive_0_rotation_default }, { "scale", type<mud::vec3>(), Param::Default, &derive_0_scale_default } }, g_qvoid },
			{ t, "position", Address(), mud_Node3_position, {}, { &type<mud::vec3>(), QualType::None } },
			{ t, "axis", Address(), mud_Node3_axis, { { "dir", type<mud::vec3>(),  } }, { &type<mud::vec3>(), QualType::None } },
			{ t, "direction", Address(), mud_Node3_direction, {}, { &type<mud::vec3>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, members, methods, {}, };
	}
	// mud::Pass
	{
		Type& t = type<mud::Pass>();
		static Meta meta = { t, &namspc({ "mud" }), "Pass", sizeof(mud::Pass), TypeClass::Struct };
		// bases
		// defaults
		static mud::RenderTarget* target_default = nullptr;
		static mud::FrameBuffer* fbo_default = nullptr;
		static mud::Viewport* viewport_default = nullptr;
		static mud::uvec4 rect_default = {};
		static uint64_t bgfx_state_default = 0;
		static bool use_mrt_default = false;
		static uint8_t index_default = 0;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Pass__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Pass__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Pass, m_name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Pass, m_target), type<mud::RenderTarget>(), "target", target_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::Pass, m_fbo), type<mud::FrameBuffer>(), "fbo", fbo_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::Pass, m_viewport), type<mud::Viewport>(), "viewport", viewport_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::Pass, m_rect), type<mud::uvec4>(), "rect", &rect_default, Member::Value, nullptr },
			{ t, offsetof(mud::Pass, m_bgfx_state), type<uint64_t>(), "bgfx_state", &bgfx_state_default, Member::Value, nullptr },
			{ t, offsetof(mud::Pass, m_pass_type), type<mud::PassType>(), "pass_type", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Pass, m_use_mrt), type<bool>(), "use_mrt", &use_mrt_default, Member::Value, nullptr },
			{ t, offsetof(mud::Pass, m_index), type<uint8_t>(), "index", &index_default, Member::Value, nullptr }
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
			{ t, offsetof(mud::Prefab, m_name), type<stl::string>(), "name", nullptr, Member::Value, nullptr }
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
		static bool set_block_0_enabled_default = true;
		static bool set_pass_0_enabled_default = true;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Program, m_name), type<stl::string>(), "name", nullptr, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "set_block", Address(), mud_Program_set_block, { { "block", type<mud::MaterialBlock>(),  }, { "enabled", type<bool>(), Param::Default, &set_block_0_enabled_default } }, g_qvoid },
			{ t, "set_pass", Address(), mud_Program_set_pass, { { "type", type<mud::PassType>(),  }, { "enabled", type<bool>(), Param::Default, &set_pass_0_enabled_default } }, g_qvoid },
			{ t, "set_source", Address(), mud_Program_set_source, { { "type", type<mud::ShaderType>(),  }, { "source", type<stl::string>(),  } }, g_qvoid },
			{ t, "register_blocks", Address(), mud_Program_register_blocks, { { "program", type<mud::Program>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, methods, {}, };
	}
	// mud::Radiance
	{
		Type& t = type<mud::Radiance>();
		static Meta meta = { t, &namspc({ "mud" }), "Radiance", sizeof(mud::Radiance), TypeClass::Struct };
		// bases
		// defaults
		static mud::Colour colour_default = mud::Colour::Black;
		static float energy_default = 1.0f;
		static float ambient_default = 1.0f;
		static mud::Texture* texture_default = nullptr;
		static mud::Texture* filtered_default = nullptr;
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
			{ t, offsetof(mud::Radiance, m_colour), type<mud::Colour>(), "colour", &colour_default, Member::Value, nullptr },
			{ t, offsetof(mud::Radiance, m_energy), type<float>(), "energy", &energy_default, Member::Value, nullptr },
			{ t, offsetof(mud::Radiance, m_ambient), type<float>(), "ambient", &ambient_default, Member::Value, nullptr },
			{ t, offsetof(mud::Radiance, m_texture), type<mud::Texture>(), "texture", texture_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::Radiance, m_filtered), type<mud::Texture>(), "filtered", filtered_default, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Render
	{
		Type& t = type<mud::Render>();
		static Meta meta = { t, &namspc({ "mud" }), "Render", sizeof(mud::Render), TypeClass::Struct };
		// bases
		// defaults
		static uint8_t pass_index_default = s_render_pass_id;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Render__construct_0, {} },
			{ t, mud_Render__construct_1, { { "shading", type<mud::Shading>(),  }, { "viewport", type<mud::Viewport>(),  }, { "target", type<mud::RenderTarget>(),  }, { "frame", type<mud::RenderFrame>(),  } } },
			{ t, mud_Render__construct_2, { { "shading", type<mud::Shading>(),  }, { "viewport", type<mud::Viewport>(),  }, { "target", type<mud::RenderTarget>(),  }, { "target_fbo", type<mud::FrameBuffer>(),  }, { "frame", type<mud::RenderFrame>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Render__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Render, m_shading), type<mud::Shading>(), "shading", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Render, m_scene), type<mud::Scene>(), "scene", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::Render, m_target), type<mud::RenderTarget>(), "target", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::Render, m_target_fbo), type<mud::FrameBuffer>(), "target_fbo", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::Render, m_viewport), type<mud::Viewport>(), "viewport", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::Render, m_rect), type<mud::uvec4>(), "rect", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Render, m_camera), type<mud::Camera>(), "camera", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::Render, m_frame), type<mud::RenderFrame>(), "frame", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::Render, m_pass_index), type<uint8_t>(), "pass_index", &pass_index_default, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "next_pass", Address(), mud_Render_next_pass, { { "name", type<const char*>(), Param::Nullable }, { "type", type<mud::PassType>(),  } }, { &type<mud::Pass>(), QualType::None } },
			{ t, "composite_pass", Address(), mud_Render_composite_pass, { { "name", type<const char*>(), Param::Nullable }, { "fbo", type<mud::FrameBuffer>(),  }, { "rect", type<mud::uvec4>(),  } }, { &type<mud::Pass>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, methods, {}, };
	}
	// mud::RenderFrame
	{
		Type& t = type<mud::RenderFrame>();
		static Meta meta = { t, &namspc({ "mud" }), "RenderFrame", sizeof(mud::RenderFrame), TypeClass::Struct };
		// bases
		// defaults
		static uint32_t nudraw_calls_default = 0;
		static uint32_t nuvertices_default = 0;
		static uint32_t nutriangles_default = 0;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_RenderFrame__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_RenderFrame__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::RenderFrame, m_frame), type<uint32_t>(), "frame", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::RenderFrame, m_time), type<float>(), "time", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::RenderFrame, m_delta_time), type<float>(), "delta_time", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::RenderFrame, m_render_pass), type<uint8_t>(), "render_pass", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::RenderFrame, m_num_draw_calls), type<uint32_t>(), "nudraw_calls", &nudraw_calls_default, Member::Value, nullptr },
			{ t, offsetof(mud::RenderFrame, m_num_vertices), type<uint32_t>(), "nuvertices", &nuvertices_default, Member::Value, nullptr },
			{ t, offsetof(mud::RenderFrame, m_num_triangles), type<uint32_t>(), "nutriangles", &nutriangles_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::RenderQuad
	{
		Type& t = type<mud::RenderQuad>();
		static Meta meta = { t, &namspc({ "mud" }), "RenderQuad", sizeof(mud::RenderQuad), TypeClass::Struct };
		// bases
		// defaults
		static bool fbo_flip_default = false;
		static bool construct_0_fbo_flip_default = false;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_RenderQuad__construct_0, { { "crop", type<mud::vec4>(),  }, { "dest", type<mud::vec4>(),  }, { "fbo_flip", type<bool>(), Param::Default, &construct_0_fbo_flip_default } } },
			{ t, mud_RenderQuad__construct_1, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_RenderQuad__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::RenderQuad, m_source), type<mud::vec4>(), "source", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::RenderQuad, m_dest), type<mud::vec4>(), "dest", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::RenderQuad, m_fbo_flip), type<bool>(), "fbo_flip", &fbo_flip_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Renderer
	{
		Type& t = type<mud::Renderer>();
		static Meta meta = { t, &namspc({ "mud" }), "Renderer", sizeof(mud::Renderer), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "gather", Address(), mud_Renderer_gather, { { "render", type<mud::Render>(),  } }, g_qvoid },
			{ t, "begin", Address(), mud_Renderer_begin, { { "render", type<mud::Render>(),  } }, g_qvoid },
			{ t, "end", Address(), mud_Renderer_end, { { "render", type<mud::Render>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, methods, {}, };
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
		static Constructor constructors[] = {
			{ t, mud_Scene__construct_0, { { "gfx", type<mud::GfxSystem>(),  } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Scene, m_index), type<uint32_t>(), "index", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Scene, m_graph), type<mud::Gnode>(), "graph", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::Scene, m_root_node), type<mud::Node3>(), "root_node", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::Scene, m_env), type<mud::Zone>(), "env", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Scene, m_user), type<mud::Ref>(), "user", nullptr, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "begin", Address(), mud_Scene_begin, {}, { &type<mud::Gnode>(), QualType::None } },
			{ t, "nodes", Address(), mud_Scene_nodes, {}, { &type<mud::TPool<mud::Node3>>(), QualType::None } },
			{ t, "items", Address(), mud_Scene_items, {}, { &type<mud::TPool<mud::Item>>(), QualType::None } },
			{ t, "batches", Address(), mud_Scene_batches, {}, { &type<mud::TPool<mud::Batch>>(), QualType::None } },
			{ t, "directs", Address(), mud_Scene_directs, {}, { &type<mud::TPool<mud::Direct>>(), QualType::None } },
			{ t, "mimes", Address(), mud_Scene_mimes, {}, { &type<mud::TPool<mud::Mime>>(), QualType::None } },
			{ t, "lights", Address(), mud_Scene_lights, {}, { &type<mud::TPool<mud::Light>>(), QualType::None } },
			{ t, "flares", Address(), mud_Scene_flares, {}, { &type<mud::TPool<mud::Flare>>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, members, methods, {}, };
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
	// mud::SwapBuffer
	{
		Type& t = type<mud::SwapBuffer>();
		static Meta meta = { t, &namspc({ "mud" }), "SwapBuffer", sizeof(mud::SwapBuffer), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::SwapBuffer, m_one), type<mud::FrameBuffer>(), "one", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::SwapBuffer, m_two), type<mud::FrameBuffer>(), "two", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "swap", Address(), mud_SwapBuffer_swap, {}, { &type<mud::FrameBuffer>(), QualType::None } },
			{ t, "last", Address(), mud_SwapBuffer_last, {}, { &type<mud::Texture>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, methods, {}, };
	}
	// mud::SwapCascade
	{
		Type& t = type<mud::SwapCascade>();
		static Meta meta = { t, &namspc({ "mud" }), "SwapCascade", sizeof(mud::SwapCascade), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::SwapCascade, m_one), type<mud::Cascade>(), "one", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::SwapCascade, m_two), type<mud::Cascade>(), "two", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "swap", Address(), mud_SwapCascade_swap, {}, { &type<mud::Cascade>(), QualType::None } },
			{ t, "last", Address(), mud_SwapCascade_last, {}, { &type<mud::Cascade>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, methods, {}, };
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
	// mud::TPool<mud::Batch>
	{
		Type& t = type<mud::TPool<mud::Batch>>();
		static Meta meta = { t, &namspc({ "mud" }), "TPool<mud::Batch>", sizeof(mud::TPool<mud::Batch>), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "add", Address(), mud_TPool_mud_Batch_add, { { "value", type<mud::Batch>(),  } }, { &type<mud::Batch>(), QualType::None } },
			{ t, "talloc", Address(), mud_TPool_mud_Batch_talloc, {}, { &type<mud::Batch>(), QualType::None } },
			{ t, "tdestroy", Address(), mud_TPool_mud_Batch_tdestroy, { { "object", type<mud::Batch>(),  } }, g_qvoid },
			{ t, "tfree", Address(), mud_TPool_mud_Batch_tfree, { { "object", type<mud::Batch>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, methods, {}, };
	}
	// mud::TPool<mud::Direct>
	{
		Type& t = type<mud::TPool<mud::Direct>>();
		static Meta meta = { t, &namspc({ "mud" }), "TPool<mud::Direct>", sizeof(mud::TPool<mud::Direct>), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "add", Address(), mud_TPool_mud_Direct_add, { { "value", type<mud::Direct>(),  } }, { &type<mud::Direct>(), QualType::None } },
			{ t, "talloc", Address(), mud_TPool_mud_Direct_talloc, {}, { &type<mud::Direct>(), QualType::None } },
			{ t, "tdestroy", Address(), mud_TPool_mud_Direct_tdestroy, { { "object", type<mud::Direct>(),  } }, g_qvoid },
			{ t, "tfree", Address(), mud_TPool_mud_Direct_tfree, { { "object", type<mud::Direct>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, methods, {}, };
	}
	// mud::TPool<mud::Flare>
	{
		Type& t = type<mud::TPool<mud::Flare>>();
		static Meta meta = { t, &namspc({ "mud" }), "TPool<mud::Flare>", sizeof(mud::TPool<mud::Flare>), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "add", Address(), mud_TPool_mud_Flare_add, { { "value", type<mud::Flare>(),  } }, { &type<mud::Flare>(), QualType::None } },
			{ t, "talloc", Address(), mud_TPool_mud_Flare_talloc, {}, { &type<mud::Flare>(), QualType::None } },
			{ t, "tdestroy", Address(), mud_TPool_mud_Flare_tdestroy, { { "object", type<mud::Flare>(),  } }, g_qvoid },
			{ t, "tfree", Address(), mud_TPool_mud_Flare_tfree, { { "object", type<mud::Flare>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, methods, {}, };
	}
	// mud::TPool<mud::Item>
	{
		Type& t = type<mud::TPool<mud::Item>>();
		static Meta meta = { t, &namspc({ "mud" }), "TPool<mud::Item>", sizeof(mud::TPool<mud::Item>), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "add", Address(), mud_TPool_mud_Item_add, { { "value", type<mud::Item>(),  } }, { &type<mud::Item>(), QualType::None } },
			{ t, "talloc", Address(), mud_TPool_mud_Item_talloc, {}, { &type<mud::Item>(), QualType::None } },
			{ t, "tdestroy", Address(), mud_TPool_mud_Item_tdestroy, { { "object", type<mud::Item>(),  } }, g_qvoid },
			{ t, "tfree", Address(), mud_TPool_mud_Item_tfree, { { "object", type<mud::Item>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, methods, {}, };
	}
	// mud::TPool<mud::Light>
	{
		Type& t = type<mud::TPool<mud::Light>>();
		static Meta meta = { t, &namspc({ "mud" }), "TPool<mud::Light>", sizeof(mud::TPool<mud::Light>), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "add", Address(), mud_TPool_mud_Light_add, { { "value", type<mud::Light>(),  } }, { &type<mud::Light>(), QualType::None } },
			{ t, "talloc", Address(), mud_TPool_mud_Light_talloc, {}, { &type<mud::Light>(), QualType::None } },
			{ t, "tdestroy", Address(), mud_TPool_mud_Light_tdestroy, { { "object", type<mud::Light>(),  } }, g_qvoid },
			{ t, "tfree", Address(), mud_TPool_mud_Light_tfree, { { "object", type<mud::Light>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, methods, {}, };
	}
	// mud::TPool<mud::Mime>
	{
		Type& t = type<mud::TPool<mud::Mime>>();
		static Meta meta = { t, &namspc({ "mud" }), "TPool<mud::Mime>", sizeof(mud::TPool<mud::Mime>), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "add", Address(), mud_TPool_mud_Mime_add, { { "value", type<mud::Mime>(),  } }, { &type<mud::Mime>(), QualType::None } },
			{ t, "talloc", Address(), mud_TPool_mud_Mime_talloc, {}, { &type<mud::Mime>(), QualType::None } },
			{ t, "tdestroy", Address(), mud_TPool_mud_Mime_tdestroy, { { "object", type<mud::Mime>(),  } }, g_qvoid },
			{ t, "tfree", Address(), mud_TPool_mud_Mime_tfree, { { "object", type<mud::Mime>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, methods, {}, };
	}
	// mud::TPool<mud::Node3>
	{
		Type& t = type<mud::TPool<mud::Node3>>();
		static Meta meta = { t, &namspc({ "mud" }), "TPool<mud::Node3>", sizeof(mud::TPool<mud::Node3>), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "add", Address(), mud_TPool_mud_Node3_add, { { "value", type<mud::Node3>(),  } }, { &type<mud::Node3>(), QualType::None } },
			{ t, "talloc", Address(), mud_TPool_mud_Node3_talloc, {}, { &type<mud::Node3>(), QualType::None } },
			{ t, "tdestroy", Address(), mud_TPool_mud_Node3_tdestroy, { { "object", type<mud::Node3>(),  } }, g_qvoid },
			{ t, "tfree", Address(), mud_TPool_mud_Node3_tfree, { { "object", type<mud::Node3>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, methods, {}, };
	}
	// mud::Texture
	{
		Type& t = type<mud::Texture>();
		static Meta meta = { t, &namspc({ "mud" }), "Texture", sizeof(mud::Texture), TypeClass::Object };
		// bases
		// defaults
		static uint16_t depth_default = 0;
		static uint32_t memsize_default = 0;
		static uint32_t bits_per_pixel_default = 0;
		static bool is_depth_default = false;
		static bool is_depth_packed_default = false;
		static bool is_array_default = false;
		static bool is_cube_default = false;
		static bool is_fbo_default = false;
		static bool mips_default = false;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Texture, m_name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Texture, m_size), type<mud::uvec2>(), "size", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Texture, m_depth), type<uint16_t>(), "depth", &depth_default, Member::Value, nullptr },
			{ t, offsetof(mud::Texture, m_memsize), type<uint32_t>(), "memsize", &memsize_default, Member::Value, nullptr },
			{ t, offsetof(mud::Texture, m_bits_per_pixel), type<uint32_t>(), "bits_per_pixel", &bits_per_pixel_default, Member::Value, nullptr },
			{ t, offsetof(mud::Texture, m_is_depth), type<bool>(), "is_depth", &is_depth_default, Member::Value, nullptr },
			{ t, offsetof(mud::Texture, m_is_depth_packed), type<bool>(), "is_depth_packed", &is_depth_packed_default, Member::Value, nullptr },
			{ t, offsetof(mud::Texture, m_is_array), type<bool>(), "is_array", &is_array_default, Member::Value, nullptr },
			{ t, offsetof(mud::Texture, m_is_cube), type<bool>(), "is_cube", &is_cube_default, Member::Value, nullptr },
			{ t, offsetof(mud::Texture, m_is_fbo), type<bool>(), "is_fbo", &is_fbo_default, Member::Value, nullptr },
			{ t, offsetof(mud::Texture, m_mips), type<bool>(), "mips", &mips_default, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "valid", Address(), mud_Texture_valid, {}, { &type<bool>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, methods, {}, };
	}
	// mud::Zone
	{
		Type& t = type<mud::Zone>();
		static Meta meta = { t, &namspc({ "mud" }), "Zone", sizeof(mud::Zone), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Zone__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Zone__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Zone, m_background), type<mud::Background>(), "background", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Zone, m_radiance), type<mud::Radiance>(), "radiance", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Zone, m_sun), type<mud::Sun>(), "sun", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Zone, m_fog), type<mud::Fog>(), "fog", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::BlockCopy
	{
		Type& t = type<mud::BlockCopy>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockCopy", sizeof(mud::BlockCopy), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::GfxBlock>() };
		static size_t bases_offsets[] = { base_offset<mud::BlockCopy, mud::GfxBlock>() };
		// defaults
		static uint64_t quad_0_flags_default = 0U;
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "quad", Address(), mud_BlockCopy_quad, { { "pass", type<mud::Pass>(),  }, { "fbo", type<mud::FrameBuffer>(),  }, { "texture", type<mud::Texture>(),  }, { "rect", type<mud::uvec4>(),  }, { "flags", type<uint64_t>(), Param::Default, &quad_0_flags_default } }, g_qvoid }
		};
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, methods, {}, };
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
		static uint64_t quad_0_flags_default = 0U;
		static bool quad_0_render_default = false;
		static uint32_t source0_0_flags_default = UINT32_MAX;
		static uint32_t source1_0_flags_default = UINT32_MAX;
		static uint32_t source2_0_flags_default = UINT32_MAX;
		static uint32_t source3_0_flags_default = UINT32_MAX;
		static uint32_t sourcedepth_0_flags_default = UINT32_MAX;
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "quad", Address(), mud_BlockFilter_quad, { { "pass", type<mud::Pass>(),  }, { "fbo", type<mud::FrameBuffer>(),  }, { "program", type<mud::Program>(),  }, { "rect", type<mud::uvec4>(),  }, { "flags", type<uint64_t>(), Param::Default, &quad_0_flags_default }, { "render", type<bool>(), Param::Default, &quad_0_render_default } }, g_qvoid },
			{ t, "source0", Address(), mud_BlockFilter_source0, { { "texture", type<mud::Texture>(),  }, { "flags", type<uint32_t>(), Param::Default, &source0_0_flags_default } }, g_qvoid },
			{ t, "source1", Address(), mud_BlockFilter_source1, { { "texture", type<mud::Texture>(),  }, { "flags", type<uint32_t>(), Param::Default, &source1_0_flags_default } }, g_qvoid },
			{ t, "source2", Address(), mud_BlockFilter_source2, { { "texture", type<mud::Texture>(),  }, { "flags", type<uint32_t>(), Param::Default, &source2_0_flags_default } }, g_qvoid },
			{ t, "source3", Address(), mud_BlockFilter_source3, { { "texture", type<mud::Texture>(),  }, { "flags", type<uint32_t>(), Param::Default, &source3_0_flags_default } }, g_qvoid },
			{ t, "sourcedepth", Address(), mud_BlockFilter_sourcedepth, { { "texture", type<mud::Texture>(),  }, { "flags", type<uint32_t>(), Param::Default, &sourcedepth_0_flags_default } }, g_qvoid },
			{ t, "uniform", Address(), mud_BlockFilter_uniform, { { "pass", type<mud::Pass>(),  }, { "name", type<stl::string>(),  }, { "value", type<mud::vec4>(),  } }, g_qvoid },
			{ t, "uniforms", Address(), mud_BlockFilter_uniforms, { { "pass", type<mud::Pass>(),  }, { "name", type<stl::string>(),  }, { "value", type<mud::vec4>(), Param::Nullable }, { "num", type<uint16_t>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, methods, {}, };
	}
	// mud::BlockMaterial
	{
		Type& t = type<mud::BlockMaterial>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockMaterial", sizeof(mud::BlockMaterial), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::GfxBlock>() };
		static size_t bases_offsets[] = { base_offset<mud::BlockMaterial, mud::GfxBlock>() };
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
	// mud::BlockPbr
	{
		Type& t = type<mud::BlockPbr>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockPbr", sizeof(mud::BlockPbr), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::GfxBlock>() };
		static size_t bases_offsets[] = { base_offset<mud::BlockPbr, mud::GfxBlock>() };
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
	// mud::Flare
	{
		Type& t = type<mud::Flare>();
		static Meta meta = { t, &namspc({ "mud" }), "Flare", sizeof(mud::Flare), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Flow>() };
		static size_t bases_offsets[] = { base_offset<mud::Flare, mud::Flow>() };
		// defaults
		static mud::Node3* node_default = nullptr;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Flare__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Flare__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Flare, m_node), type<mud::Node3>(), "node", node_default, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::GfxSystem
	{
		Type& t = type<mud::GfxSystem>();
		static Meta meta = { t, &namspc({ "mud" }), "GfxSystem", sizeof(mud::GfxSystem), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::BgfxSystem>() };
		static size_t bases_offsets[] = { base_offset<mud::GfxSystem, mud::BgfxSystem>() };
		// defaults
		static mud::BlockCopy* copy_default = nullptr;
		static mud::BlockFilter* filter_default = nullptr;
		static bool flip_y_default = false;
		static bool add_resource_path_0_relative_default = true;
		static bool create_model_geo_0_readback_default = false;
		static bool create_model_geo_0_optimize_default = false;
		static bool create_model_gpu_0_readback_default = false;
		static bool create_model_gpu_0_optimize_default = false;
		static bool fetch_material_0_builtin_default = true;
		static mud::Symbol shape_0_symbol_default = {};
		static mud::DrawMode shape_0_draw_mode_default = PLAIN;
		static mud::DrawMode symbol_material_0_draw_mode_default = PLAIN;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_GfxSystem__construct_0, { { "resource_path", type<stl::string>(),  } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::GfxSystem, m_renderer), type<mud::Renderer>(), "renderer", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::GfxSystem, m_copy), type<mud::BlockCopy>(), "copy", copy_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::GfxSystem, m_filter), type<mud::BlockFilter>(), "filter", filter_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::GfxSystem, m_flip_y), type<bool>(), "flip_y", &flip_y_default, Member::Value, nullptr },
			{ t, offsetof(mud::GfxSystem, m_render_frame), type<mud::RenderFrame>(), "render_frame", nullptr, Member::Value, nullptr },
			{ t, SIZE_MAX, type<mud::AssetStore<mud::Texture>>(), "textures", nullptr, Member::Flags(Member::NonMutable|Member::Link), mud_GfxSystem__get_textures },
			{ t, SIZE_MAX, type<mud::AssetStore<mud::Program>>(), "programs", nullptr, Member::Flags(Member::NonMutable|Member::Link), mud_GfxSystem__get_programs },
			{ t, SIZE_MAX, type<mud::AssetStore<mud::Material>>(), "materials", nullptr, Member::Flags(Member::NonMutable|Member::Link), mud_GfxSystem__get_materials },
			{ t, SIZE_MAX, type<mud::AssetStore<mud::Model>>(), "models", nullptr, Member::Flags(Member::NonMutable|Member::Link), mud_GfxSystem__get_models },
			{ t, SIZE_MAX, type<mud::AssetStore<mud::Flow>>(), "flows", nullptr, Member::Flags(Member::NonMutable|Member::Link), mud_GfxSystem__get_flows },
			{ t, SIZE_MAX, type<mud::AssetStore<mud::Prefab>>(), "prefabs", nullptr, Member::Flags(Member::NonMutable|Member::Link), mud_GfxSystem__get_prefabs }
		};
		// methods
		static Method methods[] = {
			{ t, "main_target", Address(), mud_GfxSystem_main_target, {}, { &type<mud::RenderTarget>(), QualType::None } },
			{ t, "default_pipeline", Address(), mud_GfxSystem_default_pipeline, {}, g_qvoid },
			{ t, "add_resource_path", Address(), mud_GfxSystem_add_resource_path, { { "path", type<stl::string>(),  }, { "relative", type<bool>(), Param::Default, &add_resource_path_0_relative_default } }, g_qvoid },
			{ t, "debug_material", Address(), mud_GfxSystem_debug_material, {}, { &type<mud::Material>(), QualType::None } },
			{ t, "create_model", Address(), mud_GfxSystem_create_model, { { "name", type<stl::string>(),  } }, { &type<mud::Model>(), QualType::None } },
			{ t, "create_model_geo", Address(), mud_GfxSystem_create_model_geo, { { "name", type<stl::string>(),  }, { "geometry", type<mud::MeshPacker>(),  }, { "readback", type<bool>(), Param::Default, &create_model_geo_0_readback_default }, { "optimize", type<bool>(), Param::Default, &create_model_geo_0_optimize_default } }, { &type<mud::Model>(), QualType::None } },
			{ t, "create_model_gpu", Address(), mud_GfxSystem_create_model_gpu, { { "name", type<stl::string>(),  }, { "gpu_mesh", type<mud::GpuMesh>(),  }, { "readback", type<bool>(), Param::Default, &create_model_gpu_0_readback_default }, { "optimize", type<bool>(), Param::Default, &create_model_gpu_0_optimize_default } }, { &type<mud::Model>(), QualType::None } },
			{ t, "fetch_material", Address(), mud_GfxSystem_fetch_material, { { "name", type<stl::string>(),  }, { "shader", type<stl::string>(),  }, { "builtin", type<bool>(), Param::Default, &fetch_material_0_builtin_default } }, { &type<mud::Material>(), QualType::None } },
			{ t, "fetch_image256_material", Address(), mud_GfxSystem_fetch_image256_material, { { "image", type<mud::Image256>(),  } }, { &type<mud::Material>(), QualType::None } },
			{ t, "shape", Address(), mud_GfxSystem_shape, { { "shape", type<mud::Shape>(),  }, { "symbol", type<mud::Symbol>(), Param::Default, &shape_0_symbol_default }, { "draw_mode", type<mud::DrawMode>(), Param::Default, &shape_0_draw_mode_default } }, { &type<mud::Model>(), QualType::None } },
			{ t, "symbol_material", Address(), mud_GfxSystem_symbol_material, { { "symbol", type<mud::Symbol>(),  }, { "draw_mode", type<mud::DrawMode>(), Param::Default, &symbol_material_0_draw_mode_default } }, { &type<mud::Material>(), QualType::None } }
		};
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, {}, members, methods, {}, };
	}
	// mud::RenderTarget
	{
		Type& t = type<mud::RenderTarget>();
		static Meta meta = { t, &namspc({ "mud" }), "RenderTarget", sizeof(mud::RenderTarget), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::FrameBuffer>() };
		static size_t bases_offsets[] = { base_offset<mud::RenderTarget, mud::FrameBuffer>() };
		// defaults
		static mud::MSAA msaa_default = mud::MSAA::Disabled;
		static bool mrt_default = true;
		static bool deferred_default = false;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::RenderTarget, m_backbuffer), type<mud::FrameBuffer>(), "backbuffer", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::RenderTarget, m_msaa), type<mud::MSAA>(), "msaa", &msaa_default, Member::Value, nullptr },
			{ t, offsetof(mud::RenderTarget, m_mrt), type<bool>(), "mrt", &mrt_default, Member::Value, nullptr },
			{ t, offsetof(mud::RenderTarget, m_depth), type<mud::Texture>(), "depth", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::RenderTarget, m_diffuse), type<mud::Texture>(), "diffuse", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::RenderTarget, m_specular), type<mud::Texture>(), "specular", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::RenderTarget, m_normal_rough), type<mud::Texture>(), "normal_rough", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::RenderTarget, m_sss), type<mud::Texture>(), "sss", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::RenderTarget, m_ping_pong), type<mud::SwapBuffer>(), "ping_pong", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::RenderTarget, m_post_process), type<mud::SwapBuffer>(), "post_process", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::RenderTarget, m_cascade), type<mud::Cascade>(), "cascade", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::RenderTarget, m_swap_cascade), type<mud::SwapCascade>(), "swap_cascade", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::RenderTarget, m_deferred), type<bool>(), "deferred", &deferred_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, members, {}, {}, };
	}
	// mud::Viewport
	{
		Type& t = type<mud::Viewport>();
		static Meta meta = { t, &namspc({ "mud" }), "Viewport", sizeof(mud::Viewport), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::OEntt>() };
		static size_t bases_offsets[] = { base_offset<mud::Viewport, mud::OEntt>() };
		// defaults
		static uint16_t index_default = 0;
		static bool active_default = true;
		static bool scissor_default = false;
		static mud::Colour clear_colour_default = mud::Colour::Black;
		static mud::Shading shading_default = mud::Shading::Shaded;
		static mud::Lighting lighting_default = mud::Lighting::Clustered;
		static bool clustered_default = false;
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
			{ t, offsetof(mud::Viewport, m_lighting), type<mud::Lighting>(), "lighting", &lighting_default, Member::Value, nullptr },
			{ t, offsetof(mud::Viewport, m_clustered), type<bool>(), "clustered", &clustered_default, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "cull", Address(), mud_Viewport_cull, { { "render", type<mud::Render>(),  } }, g_qvoid },
			{ t, "render", Address(), mud_Viewport_render, { { "render", type<mud::Render>(),  } }, g_qvoid },
			{ t, "set_clustered", Address(), mud_Viewport_set_clustered, { { "gfx", type<mud::GfxSystem>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, members, methods, {}, };
	}
	
	
		m.m_types.push_back(&type<mud::AnimatedTrack>());
		m.m_types.push_back(&type<mud::Animation>());
		m.m_types.push_back(&type<mud::AnimationPlay>());
		m.m_types.push_back(&type<mud::AnimationTarget>());
		m.m_types.push_back(&type<mud::AnimationTrack>());
		m.m_types.push_back(&type<mud::AssetStore<mud::Flow>>());
		m.m_types.push_back(&type<mud::AssetStore<mud::Material>>());
		m.m_types.push_back(&type<mud::AssetStore<mud::Model>>());
		m.m_types.push_back(&type<mud::AssetStore<mud::Prefab>>());
		m.m_types.push_back(&type<mud::AssetStore<mud::Program>>());
		m.m_types.push_back(&type<mud::AssetStore<mud::Texture>>());
		m.m_types.push_back(&type<mud::Background>());
		m.m_types.push_back(&type<mud::BackgroundMode>());
		m.m_types.push_back(&type<mud::Batch>());
		m.m_types.push_back(&type<mud::BlendMode>());
		m.m_types.push_back(&type<mud::Bone>());
		m.m_types.push_back(&type<mud::Camera>());
		m.m_types.push_back(&type<mud::Cascade>());
		m.m_types.push_back(&type<mud::CullMode>());
		m.m_types.push_back(&type<mud::Culler>());
		m.m_types.push_back(&type<mud::DepthDraw>());
		m.m_types.push_back(&type<mud::DepthMethod>());
		m.m_types.push_back(&type<mud::DepthParams>());
		m.m_types.push_back(&type<mud::DepthTest>());
		m.m_types.push_back(&type<mud::Direct>());
		m.m_types.push_back(&type<mud::DistanceParams>());
		m.m_types.push_back(&type<mud::EmitterFlow>());
		m.m_types.push_back(&type<mud::Flow>());
		m.m_types.push_back(&type<mud::Fog>());
		m.m_types.push_back(&type<mud::FrameBuffer>());
		m.m_types.push_back(&type<mud::Frustum>());
		m.m_types.push_back(&type<mud::FrustumSlice>());
		m.m_types.push_back(&type<mud::GfxBlock>());
		m.m_types.push_back(&type<mud::GfxWindow>());
		m.m_types.push_back(&type<mud::Gnode>());
		m.m_types.push_back(&type<mud::GpuMesh>());
		m.m_types.push_back(&type<mud::ImmediateDraw>());
		m.m_types.push_back(&type<mud::Import>());
		m.m_types.push_back(&type<mud::ImportConfig>());
		m.m_types.push_back(&type<mud::Interpolation>());
		m.m_types.push_back(&type<mud::IsometricAngle>());
		m.m_types.push_back(&type<mud::Item>());
		m.m_types.push_back(&type<mud::ItemShadow>());
		m.m_types.push_back(&type<mud::Joint>());
		m.m_types.push_back(&type<mud::Light>());
		m.m_types.push_back(&type<mud::LightType>());
		m.m_types.push_back(&type<mud::Lighting>());
		m.m_types.push_back(&type<mud::Lines>());
		m.m_types.push_back(&type<mud::MSAA>());
		m.m_types.push_back(&type<mud::Material>());
		m.m_types.push_back(&type<mud::MaterialAlpha>());
		m.m_types.push_back(&type<mud::MaterialBase>());
		m.m_types.push_back(&type<mud::MaterialBlock>());
		m.m_types.push_back(&type<mud::MaterialFlag>());
		m.m_types.push_back(&type<mud::MaterialFresnel>());
		m.m_types.push_back(&type<mud::MaterialLine>());
		m.m_types.push_back(&type<mud::MaterialLit>());
		m.m_types.push_back(&type<mud::MaterialParam<float>>());
		m.m_types.push_back(&type<mud::MaterialParam<mud::Colour>>());
		m.m_types.push_back(&type<mud::MaterialParam<mud::vec4>>());
		m.m_types.push_back(&type<mud::MaterialPbr>());
		m.m_types.push_back(&type<mud::MaterialPhong>());
		m.m_types.push_back(&type<mud::MaterialPoint>());
		m.m_types.push_back(&type<mud::MaterialSolid>());
		m.m_types.push_back(&type<mud::MaterialUser>());
		m.m_types.push_back(&type<mud::Mesh>());
		m.m_types.push_back(&type<mud::Mime>());
		m.m_types.push_back(&type<mud::Model>());
		m.m_types.push_back(&type<mud::ModelFormat>());
		m.m_types.push_back(&type<mud::ModelItem>());
		m.m_types.push_back(&type<mud::Month>());
		m.m_types.push_back(&type<mud::Node3>());
		m.m_types.push_back(&type<mud::Pass>());
		m.m_types.push_back(&type<mud::PassType>());
		m.m_types.push_back(&type<mud::PbrDiffuseMode>());
		m.m_types.push_back(&type<mud::PbrSpecularMode>());
		m.m_types.push_back(&type<mud::Prefab>());
		m.m_types.push_back(&type<mud::Program>());
		m.m_types.push_back(&type<mud::Radiance>());
		m.m_types.push_back(&type<mud::Render>());
		m.m_types.push_back(&type<mud::RenderFrame>());
		m.m_types.push_back(&type<mud::RenderQuad>());
		m.m_types.push_back(&type<mud::Renderer>());
		m.m_types.push_back(&type<mud::Rig>());
		m.m_types.push_back(&type<mud::Scene>());
		m.m_types.push_back(&type<mud::ShaderColor>());
		m.m_types.push_back(&type<mud::ShaderType>());
		m.m_types.push_back(&type<mud::Shading>());
		m.m_types.push_back(&type<mud::ShadowFlags>());
		m.m_types.push_back(&type<mud::Shot>());
		m.m_types.push_back(&type<mud::Skeleton>());
		m.m_types.push_back(&type<mud::Skin>());
		m.m_types.push_back(&type<mud::Sun>());
		m.m_types.push_back(&type<mud::SwapBuffer>());
		m.m_types.push_back(&type<mud::SwapCascade>());
		m.m_types.push_back(&type<mud::SymbolIndex>());
		m.m_types.push_back(&type<mud::TPool<mud::Batch>>());
		m.m_types.push_back(&type<mud::TPool<mud::Direct>>());
		m.m_types.push_back(&type<mud::TPool<mud::Flare>>());
		m.m_types.push_back(&type<mud::TPool<mud::Item>>());
		m.m_types.push_back(&type<mud::TPool<mud::Light>>());
		m.m_types.push_back(&type<mud::TPool<mud::Mime>>());
		m.m_types.push_back(&type<mud::TPool<mud::Node3>>());
		m.m_types.push_back(&type<mud::Texture>());
		m.m_types.push_back(&type<mud::TextureChannel>());
		m.m_types.push_back(&type<mud::TextureHint>());
		m.m_types.push_back(&type<mud::TextureSampler>());
		m.m_types.push_back(&type<mud::Zone>());
		m.m_types.push_back(&type<stl::span<mud::mat4>>());
		m.m_types.push_back(&type<stl::vector<mud::Animation*>>());
		m.m_types.push_back(&type<stl::vector<mud::AnimationPlay>>());
		m.m_types.push_back(&type<stl::vector<mud::Material*>>());
		m.m_types.push_back(&type<stl::vector<mud::Mesh*>>());
		m.m_types.push_back(&type<stl::vector<mud::Model*>>());
		m.m_types.push_back(&type<stl::vector<mud::Texture*>>());
		m.m_types.push_back(&type<mud::BlockCopy>());
		m.m_types.push_back(&type<mud::BlockDepth>());
		m.m_types.push_back(&type<mud::BlockFilter>());
		m.m_types.push_back(&type<mud::BlockMaterial>());
		m.m_types.push_back(&type<mud::BlockParticles>());
		m.m_types.push_back(&type<mud::BlockPbr>());
		m.m_types.push_back(&type<mud::BlockSky>());
		m.m_types.push_back(&type<mud::ClusteredFrustum>());
		m.m_types.push_back(&type<mud::DrawBlock>());
		m.m_types.push_back(&type<mud::Flare>());
		m.m_types.push_back(&type<mud::GfxSystem>());
		m.m_types.push_back(&type<mud::RenderTarget>());
		m.m_types.push_back(&type<mud::Viewport>());
		{
			static Function f = { &namspc({ "mud" }), "bxidentity", nullptr, mud_bxidentity_0, {}, { &type<mud::mat4>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "bxinverse", nullptr, mud_bxinverse_1, { { "mat", type<mud::mat4>(),  } }, { &type<mud::mat4>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "bxSRT", nullptr, mud_bxSRT_2, { { "scale", type<mud::vec3>(),  }, { "rot", type<mud::vec3>(),  }, { "trans", type<mud::vec3>(),  } }, { &type<mud::mat4>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "bxscale", nullptr, mud_bxscale_3, { { "scale", type<mud::vec3>(),  } }, { &type<mud::mat4>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "bxrotation", nullptr, mud_bxrotation_4, { { "rot", type<mud::quat>(),  } }, { &type<mud::mat4>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "bxtranslation", nullptr, mud_bxtranslation_5, { { "vec", type<mud::vec3>(),  } }, { &type<mud::mat4>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "bxmul", nullptr, mud_bxmul_6, { { "lhs", type<mud::mat4>(),  }, { "rhs", type<mud::mat4>(),  } }, { &type<mud::mat4>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "bxmul", nullptr, mud_bxmul_7, { { "mat", type<mud::mat4>(),  }, { "vec", type<mud::vec4>(),  } }, { &type<mud::vec4>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "bxmul", nullptr, mud_bxmul_8, { { "mat", type<mud::mat4>(),  }, { "vec", type<mud::vec3>(),  } }, { &type<mud::vec3>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "bxmulh", nullptr, mud_bxmulh_9, { { "mat", type<mud::mat4>(),  }, { "vec", type<mud::vec3>(),  } }, { &type<mud::vec3>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "bxlookat", nullptr, mud_bxlookat_10, { { "eye", type<mud::vec3>(),  }, { "at", type<mud::vec3>(),  } }, { &type<mud::mat4>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "bxlookat", nullptr, mud_bxlookat_11, { { "result", type<mud::mat4>(),  }, { "eye", type<mud::vec3>(),  }, { "at", type<mud::vec3>(),  }, { "up", type<mud::vec3>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "bxlookat", nullptr, mud_bxlookat_12, { { "eye", type<mud::vec3>(),  }, { "at", type<mud::vec3>(),  }, { "up", type<mud::vec3>(),  } }, { &type<mud::mat4>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "bxproj", nullptr, mud_bxproj_13, { { "fov", type<float>(),  }, { "aspect", type<float>(),  }, { "near", type<float>(),  }, { "far", type<float>(),  }, { "oglNdc", type<bool>(),  } }, { &type<mud::mat4>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "bxortho", nullptr, mud_bxortho_14, { { "rect", type<mud::vec4>(),  }, { "near", type<float>(),  }, { "far", type<float>(),  }, { "offset", type<float>(),  }, { "oglNdc", type<bool>(),  } }, { &type<mud::mat4>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "bxortho", nullptr, mud_bxortho_15, { { "left", type<float>(),  }, { "right", type<float>(),  }, { "bottom", type<float>(),  }, { "top", type<float>(),  }, { "near", type<float>(),  }, { "far", type<float>(),  }, { "offset", type<float>(),  }, { "oglNdc", type<bool>(),  } }, { &type<mud::mat4>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "bxSRT", nullptr, mud_bxSRT_16, { { "scale", type<mud::vec3>(),  }, { "rot", type<mud::quat>(),  }, { "trans", type<mud::vec3>(),  } }, { &type<mud::mat4>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "bxTRS", nullptr, mud_bxTRS_17, { { "scale", type<mud::vec3>(),  }, { "rot", type<mud::quat>(),  }, { "trans", type<mud::vec3>(),  } }, { &type<mud::mat4>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "load_texture_rgba", nullptr, mud_load_texture_rgba_18, { { "texture", type<mud::Texture>(),  }, { "size", type<mud::uvec2>(),  }, { "data", type<stl::span<uint32_t>>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "gfx" }), "setup_pipeline_minimal", nullptr, mud_gfx_setup_pipeline_minimal_19, { { "gfx", type<mud::GfxSystem>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static mud::Ref object_default = {};
			static mud::vec3 position_default = vec3(0.f);
			static mud::quat rotation_default = ZeroQuat;
			static mud::vec3 scale_default = vec3(1.f);
			static Function f = { &namspc({ "mud", "gfx" }), "node", nullptr, mud_gfx_node_20, { { "parent", type<mud::Gnode>(),  }, { "object", type<mud::Ref>(), Param::Flags(Param::Nullable|Param::Default), &object_default }, { "position", type<mud::vec3>(), Param::Default, &position_default }, { "rotation", type<mud::quat>(), Param::Default, &rotation_default }, { "scale", type<mud::vec3>(), Param::Default, &scale_default } }, { &type<mud::Gnode>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static uint32_t flags_default = 0;
			static mud::Material* material_default = nullptr;
			static Function f = { &namspc({ "mud", "gfx" }), "shape", nullptr, mud_gfx_shape_21, { { "parent", type<mud::Gnode>(),  }, { "shape", type<mud::Shape>(),  }, { "symbol", type<mud::Symbol>(),  }, { "flags", type<uint32_t>(), Param::Default, &flags_default }, { "material", type<mud::Material>(), Param::Flags(Param::Nullable|Param::Default), &material_default } }, { &type<mud::Item>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static uint32_t flags_default = 0;
			static Function f = { &namspc({ "mud", "gfx" }), "draw", nullptr, mud_gfx_draw_22, { { "parent", type<mud::Gnode>(),  }, { "shape", type<mud::Shape>(),  }, { "symbol", type<mud::Symbol>(),  }, { "flags", type<uint32_t>(), Param::Default, &flags_default } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static uint32_t flags_default = 0;
			static mud::Material* material_default = nullptr;
			static Function f = { &namspc({ "mud", "gfx" }), "sprite", nullptr, mud_gfx_sprite_23, { { "parent", type<mud::Gnode>(),  }, { "image", type<mud::Image256>(),  }, { "size", type<mud::vec2>(),  }, { "flags", type<uint32_t>(), Param::Default, &flags_default }, { "material", type<mud::Material>(), Param::Flags(Param::Nullable|Param::Default), &material_default } }, { &type<mud::Item>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static uint32_t flags_default = 0;
			static mud::Material* material_default = nullptr;
			static Function f = { &namspc({ "mud", "gfx" }), "item", nullptr, mud_gfx_item_24, { { "parent", type<mud::Gnode>(),  }, { "model", type<mud::Model>(),  }, { "flags", type<uint32_t>(), Param::Default, &flags_default }, { "material", type<mud::Material>(), Param::Flags(Param::Nullable|Param::Default), &material_default } }, { &type<mud::Item>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "gfx" }), "batch", nullptr, mud_gfx_batch_25, { { "parent", type<mud::Gnode>(),  }, { "item", type<mud::Item>(),  }, { "stride", type<uint16_t>(),  } }, { &type<mud::Batch>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static stl::span<mud::mat4> transforms_default = {};
			static Function f = { &namspc({ "mud", "gfx" }), "instances", nullptr, mud_gfx_instances_26, { { "parent", type<mud::Gnode>(),  }, { "item", type<mud::Item>(),  }, { "transforms", type<stl::span<mud::mat4>>(), Param::Default, &transforms_default } }, { &type<mud::Batch>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool transform_default = true;
			static uint32_t flags_default = 0;
			static mud::Material* material_default = nullptr;
			static Function f = { &namspc({ "mud", "gfx" }), "prefab", nullptr, mud_gfx_prefab_27, { { "parent", type<mud::Gnode>(),  }, { "prefab", type<mud::Prefab>(),  }, { "transform", type<bool>(), Param::Default, &transform_default }, { "flags", type<uint32_t>(), Param::Default, &flags_default }, { "material", type<mud::Material>(), Param::Flags(Param::Nullable|Param::Default), &material_default } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static uint32_t flags_default = 0;
			static mud::Material* material_default = nullptr;
			static Function f = { &namspc({ "mud", "gfx" }), "model", nullptr, mud_gfx_model_28, { { "parent", type<mud::Gnode>(),  }, { "name", type<stl::string>(),  }, { "flags", type<uint32_t>(), Param::Default, &flags_default }, { "material", type<mud::Material>(), Param::Flags(Param::Nullable|Param::Default), &material_default } }, { &type<mud::Item>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "gfx" }), "animated", nullptr, mud_gfx_animated_29, { { "parent", type<mud::Gnode>(),  }, { "item", type<mud::Item>(),  } }, { &type<mud::Mime>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static uint32_t flags_default = 0;
			static Function f = { &namspc({ "mud", "gfx" }), "flows", nullptr, mud_gfx_flows_30, { { "parent", type<mud::Gnode>(),  }, { "emitter", type<mud::Flow>(),  }, { "flags", type<uint32_t>(), Param::Default, &flags_default } }, { &type<mud::Flare>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static float range_default = 0.f;
			static float attenuation_default = 0.5f;
			static Function f = { &namspc({ "mud", "gfx" }), "light", nullptr, mud_gfx_light_31, { { "parent", type<mud::Gnode>(),  }, { "type", type<mud::LightType>(),  }, { "shadows", type<bool>(),  }, { "colour", type<mud::Colour>(),  }, { "range", type<float>(), Param::Default, &range_default }, { "attenuation", type<float>(), Param::Default, &attenuation_default } }, { &type<mud::Light>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "gfx" }), "sun_light", nullptr, mud_gfx_sun_light_32, { { "parent", type<mud::Gnode>(),  }, { "azimuth", type<float>(),  }, { "elevation", type<float>(),  } }, { &type<mud::Light>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "gfx" }), "radiance", nullptr, mud_gfx_radiance_33, { { "parent", type<mud::Gnode>(),  }, { "texture", type<stl::string>(),  }, { "background", type<mud::BackgroundMode>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "gfx" }), "direct_light_node", nullptr, mud_gfx_direct_light_node_34, { { "parent", type<mud::Gnode>(),  }, { "direction", type<mud::vec3>(),  } }, { &type<mud::Light>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "gfx" }), "solid_material", nullptr, mud_gfx_solid_material_35, { { "gfx", type<mud::GfxSystem>(),  }, { "name", type<stl::string>(),  }, { "colour", type<mud::Colour>(),  } }, { &type<mud::Material>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static float metallic_default = 0.f;
			static float roughness_default = 1.f;
			static Function f = { &namspc({ "mud", "gfx" }), "pbr_material", nullptr, mud_gfx_pbr_material_36, { { "gfx", type<mud::GfxSystem>(),  }, { "name", type<stl::string>(),  }, { "albedo", type<mud::Colour>(),  }, { "metallic", type<float>(), Param::Default, &metallic_default }, { "roughness", type<float>(), Param::Default, &roughness_default } }, { &type<mud::Material>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "gfx" }), "model_suzanne", nullptr, mud_gfx_model_suzanne_37, { { "gfx", type<mud::GfxSystem>(),  } }, { &type<mud::Model>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "pass_clear_fbo", nullptr, mud_pass_clear_fbo_38, { { "gfx", type<mud::GfxSystem>(),  }, { "render", type<mud::Render>(),  }, { "fbo", type<mud::FrameBuffer>(),  }, { "colour", type<mud::Colour>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "pass_clear", nullptr, mud_pass_clear_39, { { "gfx", type<mud::GfxSystem>(),  }, { "render", type<mud::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "pass_gclear", nullptr, mud_pass_gclear_40, { { "gfx", type<mud::GfxSystem>(),  }, { "render", type<mud::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "pass_depth", nullptr, mud_pass_depth_41, { { "gfx", type<mud::GfxSystem>(),  }, { "render", type<mud::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "pass_background", nullptr, mud_pass_background_42, { { "gfx", type<mud::GfxSystem>(),  }, { "render", type<mud::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "pass_solid", nullptr, mud_pass_solid_43, { { "gfx", type<mud::GfxSystem>(),  }, { "render", type<mud::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "pass_flip", nullptr, mud_pass_flip_44, { { "gfx", type<mud::GfxSystem>(),  }, { "render", type<mud::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "render_minimal", nullptr, mud_render_minimal_45, { { "gfx", type<mud::GfxSystem>(),  }, { "render", type<mud::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "render_solid", nullptr, mud_render_solid_46, { { "gfx", type<mud::GfxSystem>(),  }, { "render", type<mud::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "render_clear", nullptr, mud_render_clear_47, { { "gfx", type<mud::GfxSystem>(),  }, { "render", type<mud::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
	}
}

namespace mud
{
	mud_gfx::mud_gfx()
		: Module("mud::gfx", { &mud_infra::m(), &mud_jobs::m(), &mud_type::m(), &mud_pool::m(), &mud_ecs::m(), &mud_math::m(), &mud_geom::m(), &mud_ctx::m(), &mud_bgfx::m() })
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
