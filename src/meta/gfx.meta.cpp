#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
module two.gfx.meta;
#else
#include <cstddef>
#include <stl/new.h>
#include <infra/ToString.h>
#include <infra/ToValue.h>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/infra.meta.h>
#include <meta/type.meta.h>
#include <meta/tree.meta.h>
#include <meta/jobs.meta.h>
#include <meta/pool.meta.h>
#include <meta/ecs.meta.h>
#include <meta/math.meta.h>
#include <meta/geom.meta.h>
#include <meta/ctx.meta.h>
#include <meta/bgfx.meta.h>
#include <meta/gfx.meta.h>
#include <meta/gfx.conv.h>
#include <gfx/Api.h>
#endif

using namespace two;

void two_AnimTarget__to_string(void* val, string& str) { str = g_enu[type<two::AnimTarget>().m_id]->name(uint32_t((*static_cast<two::AnimTarget*>(val)))); }
void two_AnimTarget__to_value(const string& str, void* val) { (*static_cast<two::AnimTarget*>(val)) = two::AnimTarget(g_enu[type<two::AnimTarget>().m_id]->value(str.c_str())); }
void two_Interpolation__to_string(void* val, string& str) { str = g_enu[type<two::Interpolation>().m_id]->name(uint32_t((*static_cast<two::Interpolation*>(val)))); }
void two_Interpolation__to_value(const string& str, void* val) { (*static_cast<two::Interpolation*>(val)) = two::Interpolation(g_enu[type<two::Interpolation>().m_id]->value(str.c_str())); }
void two_TextureHint__to_string(void* val, string& str) { str = g_enu[type<two::TextureHint>().m_id]->name(uint32_t((*static_cast<two::TextureHint*>(val)))); }
void two_TextureHint__to_value(const string& str, void* val) { (*static_cast<two::TextureHint*>(val)) = two::TextureHint(g_enu[type<two::TextureHint>().m_id]->value(str.c_str())); }
void two_TextureFormat__to_string(void* val, string& str) { str = g_enu[type<two::TextureFormat>().m_id]->name(uint32_t((*static_cast<two::TextureFormat*>(val)))); }
void two_TextureFormat__to_value(const string& str, void* val) { (*static_cast<two::TextureFormat*>(val)) = two::TextureFormat(g_enu[type<two::TextureFormat>().m_id]->value(str.c_str())); }
void two_ShaderType__to_string(void* val, string& str) { str = g_enu[type<two::ShaderType>().m_id]->name(uint32_t((*static_cast<two::ShaderType*>(val)))); }
void two_ShaderType__to_value(const string& str, void* val) { (*static_cast<two::ShaderType*>(val)) = two::ShaderType(g_enu[type<two::ShaderType>().m_id]->value(str.c_str())); }
void two_PassType__to_string(void* val, string& str) { str = g_enu[type<two::PassType>().m_id]->name(uint32_t((*static_cast<two::PassType*>(val)))); }
void two_PassType__to_value(const string& str, void* val) { (*static_cast<two::PassType*>(val)) = two::PassType(g_enu[type<two::PassType>().m_id]->value(str.c_str())); }
void two_MaterialBlock__to_string(void* val, string& str) { str = g_enu[type<two::MaterialBlock>().m_id]->name(uint32_t((*static_cast<two::MaterialBlock*>(val)))); }
void two_MaterialBlock__to_value(const string& str, void* val) { (*static_cast<two::MaterialBlock*>(val)) = two::MaterialBlock(g_enu[type<two::MaterialBlock>().m_id]->value(str.c_str())); }
void two_TextureSampler__to_string(void* val, string& str) { str = g_enu[type<two::TextureSampler>().m_id]->name(uint32_t((*static_cast<two::TextureSampler*>(val)))); }
void two_TextureSampler__to_value(const string& str, void* val) { (*static_cast<two::TextureSampler*>(val)) = two::TextureSampler(g_enu[type<two::TextureSampler>().m_id]->value(str.c_str())); }
void two_Lighting__to_string(void* val, string& str) { str = g_enu[type<two::Lighting>().m_id]->name(uint32_t((*static_cast<two::Lighting*>(val)))); }
void two_Lighting__to_value(const string& str, void* val) { (*static_cast<two::Lighting*>(val)) = two::Lighting(g_enu[type<two::Lighting>().m_id]->value(str.c_str())); }
void two_BlendMode__to_string(void* val, string& str) { str = g_enu[type<two::BlendMode>().m_id]->name(uint32_t((*static_cast<two::BlendMode*>(val)))); }
void two_BlendMode__to_value(const string& str, void* val) { (*static_cast<two::BlendMode*>(val)) = two::BlendMode(g_enu[type<two::BlendMode>().m_id]->value(str.c_str())); }
void two_CullMode__to_string(void* val, string& str) { str = g_enu[type<two::CullMode>().m_id]->name(uint32_t((*static_cast<two::CullMode*>(val)))); }
void two_CullMode__to_value(const string& str, void* val) { (*static_cast<two::CullMode*>(val)) = two::CullMode(g_enu[type<two::CullMode>().m_id]->value(str.c_str())); }
void two_DepthDraw__to_string(void* val, string& str) { str = g_enu[type<two::DepthDraw>().m_id]->name(uint32_t((*static_cast<two::DepthDraw*>(val)))); }
void two_DepthDraw__to_value(const string& str, void* val) { (*static_cast<two::DepthDraw*>(val)) = two::DepthDraw(g_enu[type<two::DepthDraw>().m_id]->value(str.c_str())); }
void two_DepthTest__to_string(void* val, string& str) { str = g_enu[type<two::DepthTest>().m_id]->name(uint32_t((*static_cast<two::DepthTest*>(val)))); }
void two_DepthTest__to_value(const string& str, void* val) { (*static_cast<two::DepthTest*>(val)) = two::DepthTest(g_enu[type<two::DepthTest>().m_id]->value(str.c_str())); }
void two_MaterialFlag__to_string(void* val, string& str) { str = g_enu[type<two::MaterialFlag>().m_id]->name(uint32_t((*static_cast<two::MaterialFlag*>(val)))); }
void two_MaterialFlag__to_value(const string& str, void* val) { (*static_cast<two::MaterialFlag*>(val)) = two::MaterialFlag(g_enu[type<two::MaterialFlag>().m_id]->value(str.c_str())); }
void two_ShaderColor__to_string(void* val, string& str) { str = g_enu[type<two::ShaderColor>().m_id]->name(uint32_t((*static_cast<two::ShaderColor*>(val)))); }
void two_ShaderColor__to_value(const string& str, void* val) { (*static_cast<two::ShaderColor*>(val)) = two::ShaderColor(g_enu[type<two::ShaderColor>().m_id]->value(str.c_str())); }
void two_TextureChannel__to_string(void* val, string& str) { str = g_enu[type<two::TextureChannel>().m_id]->name(uint32_t((*static_cast<two::TextureChannel*>(val)))); }
void two_TextureChannel__to_value(const string& str, void* val) { (*static_cast<two::TextureChannel*>(val)) = two::TextureChannel(g_enu[type<two::TextureChannel>().m_id]->value(str.c_str())); }
void two_PbrDiffuseMode__to_string(void* val, string& str) { str = g_enu[type<two::PbrDiffuseMode>().m_id]->name(uint32_t((*static_cast<two::PbrDiffuseMode*>(val)))); }
void two_PbrDiffuseMode__to_value(const string& str, void* val) { (*static_cast<two::PbrDiffuseMode*>(val)) = two::PbrDiffuseMode(g_enu[type<two::PbrDiffuseMode>().m_id]->value(str.c_str())); }
void two_PbrSpecularMode__to_string(void* val, string& str) { str = g_enu[type<two::PbrSpecularMode>().m_id]->name(uint32_t((*static_cast<two::PbrSpecularMode*>(val)))); }
void two_PbrSpecularMode__to_value(const string& str, void* val) { (*static_cast<two::PbrSpecularMode*>(val)) = two::PbrSpecularMode(g_enu[type<two::PbrSpecularMode>().m_id]->value(str.c_str())); }
void two_PhongEnvBlendMode__to_string(void* val, string& str) { str = g_enu[type<two::PhongEnvBlendMode>().m_id]->name(uint32_t((*static_cast<two::PhongEnvBlendMode*>(val)))); }
void two_PhongEnvBlendMode__to_value(const string& str, void* val) { (*static_cast<two::PhongEnvBlendMode*>(val)) = two::PhongEnvBlendMode(g_enu[type<two::PhongEnvBlendMode>().m_id]->value(str.c_str())); }
void two_EmitterFlow__to_string(void* val, string& str) { str = g_enu[type<two::EmitterFlow>().m_id]->name(uint32_t((*static_cast<two::EmitterFlow*>(val)))); }
void two_EmitterFlow__to_value(const string& str, void* val) { (*static_cast<two::EmitterFlow*>(val)) = two::EmitterFlow(g_enu[type<two::EmitterFlow>().m_id]->value(str.c_str())); }
void two_ItemShadow__to_string(void* val, string& str) { str = g_enu[type<two::ItemShadow>().m_id]->name(uint32_t((*static_cast<two::ItemShadow*>(val)))); }
void two_ItemShadow__to_value(const string& str, void* val) { (*static_cast<two::ItemShadow*>(val)) = two::ItemShadow(g_enu[type<two::ItemShadow>().m_id]->value(str.c_str())); }
void two_ModelFormat__to_string(void* val, string& str) { str = g_enu[type<two::ModelFormat>().m_id]->name(uint32_t((*static_cast<two::ModelFormat*>(val)))); }
void two_ModelFormat__to_value(const string& str, void* val) { (*static_cast<two::ModelFormat*>(val)) = two::ModelFormat(g_enu[type<two::ModelFormat>().m_id]->value(str.c_str())); }
void two_IsometricAngle__to_string(void* val, string& str) { str = g_enu[type<two::IsometricAngle>().m_id]->name(uint32_t((*static_cast<two::IsometricAngle*>(val)))); }
void two_IsometricAngle__to_value(const string& str, void* val) { (*static_cast<two::IsometricAngle*>(val)) = two::IsometricAngle(g_enu[type<two::IsometricAngle>().m_id]->value(str.c_str())); }
void two_DepthMethod__to_string(void* val, string& str) { str = g_enu[type<two::DepthMethod>().m_id]->name(uint32_t((*static_cast<two::DepthMethod*>(val)))); }
void two_DepthMethod__to_value(const string& str, void* val) { (*static_cast<two::DepthMethod*>(val)) = two::DepthMethod(g_enu[type<two::DepthMethod>().m_id]->value(str.c_str())); }
void two_LightType__to_string(void* val, string& str) { str = g_enu[type<two::LightType>().m_id]->name(uint32_t((*static_cast<two::LightType*>(val)))); }
void two_LightType__to_value(const string& str, void* val) { (*static_cast<two::LightType*>(val)) = two::LightType(g_enu[type<two::LightType>().m_id]->value(str.c_str())); }
void two_ShadowFlags__to_string(void* val, string& str) { str = g_enu[type<two::ShadowFlags>().m_id]->name(uint32_t((*static_cast<two::ShadowFlags*>(val)))); }
void two_ShadowFlags__to_value(const string& str, void* val) { (*static_cast<two::ShadowFlags*>(val)) = two::ShadowFlags(g_enu[type<two::ShadowFlags>().m_id]->value(str.c_str())); }
void two_MSAA__to_string(void* val, string& str) { str = g_enu[type<two::MSAA>().m_id]->name(uint32_t((*static_cast<two::MSAA*>(val)))); }
void two_MSAA__to_value(const string& str, void* val) { (*static_cast<two::MSAA*>(val)) = two::MSAA(g_enu[type<two::MSAA>().m_id]->value(str.c_str())); }
void two_Shading__to_string(void* val, string& str) { str = g_enu[type<two::Shading>().m_id]->name(uint32_t((*static_cast<two::Shading*>(val)))); }
void two_Shading__to_value(const string& str, void* val) { (*static_cast<two::Shading*>(val)) = two::Shading(g_enu[type<two::Shading>().m_id]->value(str.c_str())); }
void two_BackgroundMode__to_string(void* val, string& str) { str = g_enu[type<two::BackgroundMode>().m_id]->name(uint32_t((*static_cast<two::BackgroundMode*>(val)))); }
void two_BackgroundMode__to_value(const string& str, void* val) { (*static_cast<two::BackgroundMode*>(val)) = two::BackgroundMode(g_enu[type<two::BackgroundMode>().m_id]->value(str.c_str())); }
void two_Month__to_string(void* val, string& str) { str = g_enu[type<two::Month>().m_id]->name(uint32_t((*static_cast<two::Month*>(val)))); }
void two_Month__to_value(const string& str, void* val) { (*static_cast<two::Month*>(val)) = two::Month(g_enu[type<two::Month>().m_id]->value(str.c_str())); }
size_t stl_span_two_mat4__size(void* vec) { return (*static_cast<stl::span<two::mat4>*>(vec)).size(); }
void* stl_span_two_mat4__at(void* vec, size_t i) { return &(*static_cast<stl::span<two::mat4>*>(vec))[i]; }
size_t stl_span_two_Node3__size(void* vec) { return (*static_cast<stl::span<two::Node3>*>(vec)).size(); }
void* stl_span_two_Node3__at(void* vec, size_t i) { return &(*static_cast<stl::span<two::Node3>*>(vec))[i]; }
size_t stl_span_two_Item__size(void* vec) { return (*static_cast<stl::span<two::Item>*>(vec)).size(); }
void* stl_span_two_Item__at(void* vec, size_t i) { return &(*static_cast<stl::span<two::Item>*>(vec))[i]; }
size_t stl_span_two_Batch__size(void* vec) { return (*static_cast<stl::span<two::Batch>*>(vec)).size(); }
void* stl_span_two_Batch__at(void* vec, size_t i) { return &(*static_cast<stl::span<two::Batch>*>(vec))[i]; }
size_t stl_span_two_Direct__size(void* vec) { return (*static_cast<stl::span<two::Direct>*>(vec)).size(); }
void* stl_span_two_Direct__at(void* vec, size_t i) { return &(*static_cast<stl::span<two::Direct>*>(vec))[i]; }
size_t stl_span_two_Mime__size(void* vec) { return (*static_cast<stl::span<two::Mime>*>(vec)).size(); }
void* stl_span_two_Mime__at(void* vec, size_t i) { return &(*static_cast<stl::span<two::Mime>*>(vec))[i]; }
size_t stl_span_two_Light__size(void* vec) { return (*static_cast<stl::span<two::Light>*>(vec)).size(); }
void* stl_span_two_Light__at(void* vec, size_t i) { return &(*static_cast<stl::span<two::Light>*>(vec))[i]; }
size_t stl_span_two_Flare__size(void* vec) { return (*static_cast<stl::span<two::Flare>*>(vec)).size(); }
void* stl_span_two_Flare__at(void* vec, size_t i) { return &(*static_cast<stl::span<two::Flare>*>(vec))[i]; }
size_t stl_span_two_Texture___size(void* vec) { return (*static_cast<stl::span<two::Texture*>*>(vec)).size(); }
void* stl_span_two_Texture___at(void* vec, size_t i) { return &(*static_cast<stl::span<two::Texture*>*>(vec))[i]; }
size_t stl_vector_two_Mesh___size(void* vec) { return (*static_cast<stl::vector<two::Mesh*>*>(vec)).size(); }
void* stl_vector_two_Mesh___at(void* vec, size_t i) { return &(*static_cast<stl::vector<two::Mesh*>*>(vec))[i]; }
void stl_vector_two_Mesh___push(void* vec) { (*static_cast<stl::vector<two::Mesh*>*>(vec)).emplace_back(); }
void stl_vector_two_Mesh___add(void* vec, void* value) { (*static_cast<stl::vector<two::Mesh*>*>(vec)).push_back(static_cast<two::Mesh*>(value)); }
void stl_vector_two_Mesh___remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<two::Mesh*>*>(vec)), static_cast<two::Mesh*>(value)); }
size_t stl_vector_two_Model___size(void* vec) { return (*static_cast<stl::vector<two::Model*>*>(vec)).size(); }
void* stl_vector_two_Model___at(void* vec, size_t i) { return &(*static_cast<stl::vector<two::Model*>*>(vec))[i]; }
void stl_vector_two_Model___push(void* vec) { (*static_cast<stl::vector<two::Model*>*>(vec)).emplace_back(); }
void stl_vector_two_Model___add(void* vec, void* value) { (*static_cast<stl::vector<two::Model*>*>(vec)).push_back(static_cast<two::Model*>(value)); }
void stl_vector_two_Model___remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<two::Model*>*>(vec)), static_cast<two::Model*>(value)); }
size_t stl_vector_two_Texture___size(void* vec) { return (*static_cast<stl::vector<two::Texture*>*>(vec)).size(); }
void* stl_vector_two_Texture___at(void* vec, size_t i) { return &(*static_cast<stl::vector<two::Texture*>*>(vec))[i]; }
void stl_vector_two_Texture___push(void* vec) { (*static_cast<stl::vector<two::Texture*>*>(vec)).emplace_back(); }
void stl_vector_two_Texture___add(void* vec, void* value) { (*static_cast<stl::vector<two::Texture*>*>(vec)).push_back(static_cast<two::Texture*>(value)); }
void stl_vector_two_Texture___remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<two::Texture*>*>(vec)), static_cast<two::Texture*>(value)); }
size_t stl_vector_two_Material___size(void* vec) { return (*static_cast<stl::vector<two::Material*>*>(vec)).size(); }
void* stl_vector_two_Material___at(void* vec, size_t i) { return &(*static_cast<stl::vector<two::Material*>*>(vec))[i]; }
void stl_vector_two_Material___push(void* vec) { (*static_cast<stl::vector<two::Material*>*>(vec)).emplace_back(); }
void stl_vector_two_Material___add(void* vec, void* value) { (*static_cast<stl::vector<two::Material*>*>(vec)).push_back(static_cast<two::Material*>(value)); }
void stl_vector_two_Material___remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<two::Material*>*>(vec)), static_cast<two::Material*>(value)); }
size_t stl_vector_two_Animation___size(void* vec) { return (*static_cast<stl::vector<two::Animation*>*>(vec)).size(); }
void* stl_vector_two_Animation___at(void* vec, size_t i) { return &(*static_cast<stl::vector<two::Animation*>*>(vec))[i]; }
void stl_vector_two_Animation___push(void* vec) { (*static_cast<stl::vector<two::Animation*>*>(vec)).emplace_back(); }
void stl_vector_two_Animation___add(void* vec, void* value) { (*static_cast<stl::vector<two::Animation*>*>(vec)).push_back(static_cast<two::Animation*>(value)); }
void stl_vector_two_Animation___remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<two::Animation*>*>(vec)), static_cast<two::Animation*>(value)); }
size_t stl_vector_two_AnimPlay__size(void* vec) { return (*static_cast<stl::vector<two::AnimPlay>*>(vec)).size(); }
void* stl_vector_two_AnimPlay__at(void* vec, size_t i) { return &(*static_cast<stl::vector<two::AnimPlay>*>(vec))[i]; }
void stl_vector_two_AnimPlay__push(void* vec) { (*static_cast<stl::vector<two::AnimPlay>*>(vec)).emplace_back(); }
void stl_vector_two_AnimPlay__add(void* vec, void* value) { (*static_cast<stl::vector<two::AnimPlay>*>(vec)).push_back(*static_cast<two::AnimPlay*>(value)); }
void stl_vector_two_AnimPlay__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<two::AnimPlay>*>(vec)), *static_cast<two::AnimPlay*>(value)); }
void two_Node3__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Node3(  ); }
void two_Node3__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Node3( *static_cast<two::vec3*>(args[0]), *static_cast<two::quat*>(args[1]), *static_cast<two::vec3*>(args[2]) ); }
void two_Node3_apply(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Node3*>(object)).apply(*static_cast<two::vec3*>(args[0]), *static_cast<two::quat*>(args[1]), *static_cast<two::vec3*>(args[2])); }
void two_Node3_derive(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Node3*>(object)).derive(*static_cast<two::Node3*>(args[0]), *static_cast<two::vec3*>(args[1]), *static_cast<two::quat*>(args[2]), *static_cast<two::vec3*>(args[3])); }
void two_Node3_position(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<two::v3<float>*>(result)) = (*static_cast<two::Node3*>(object)).position(); }
void two_Node3_axis(void* object, span<void*> args, void*& result) { (*static_cast<two::v3<float>*>(result)) = (*static_cast<two::Node3*>(object)).axis(*static_cast<two::vec3*>(args[0])); }
void two_Node3_direction(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<two::v3<float>*>(result)) = (*static_cast<two::Node3*>(object)).direction(); }
void two_Texture__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Texture( *static_cast<stl::string*>(args[0]) ); }
void two_Texture__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Texture( *static_cast<two::uvec2*>(args[0]), *static_cast<bool*>(args[1]), *static_cast<two::TextureFormat*>(args[2]), *static_cast<uint64_t*>(args[3]), *static_cast<bool*>(args[4]) ); }
void two_Texture_valid(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<two::Texture*>(object)).valid(); }
void two_Texture_load(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Texture*>(object)).load(*static_cast<two::GfxSystem*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<bool*>(args[2]), *static_cast<bool*>(args[3])); }
void two_Texture_reload(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Texture*>(object)).reload(*static_cast<two::GfxSystem*>(args[0]), *static_cast<bool*>(args[1]), *static_cast<bool*>(args[2])); }
void two_Texture_load_mem(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Texture*>(object)).load_mem(*static_cast<two::GfxSystem*>(args[0]), *static_cast<stl::span<uint8_t>*>(args[1])); }
void two_Texture_load_rgba(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Texture*>(object)).load_rgba(*static_cast<two::uvec2*>(args[0]), *static_cast<stl::span<uint32_t>*>(args[1]), *static_cast<bool*>(args[2])); }
void two_Texture_load_float(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Texture*>(object)).load_float(*static_cast<two::uvec2*>(args[0]), *static_cast<stl::span<float>*>(args[1]), *static_cast<bool*>(args[2])); }
void two_Joint__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Joint(  ); }
void two_Joint__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Joint((*static_cast<two::Joint*>(other))); }
void two_AnimNode__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::AnimNode(  ); }
void two_AnimNode__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::AnimNode((*static_cast<two::AnimNode*>(other))); }
void two_AnimPlay__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::AnimPlay(  ); }
void two_AnimPlay__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::AnimPlay((*static_cast<two::AnimPlay*>(other))); }
void two_Mime__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Mime(  ); }
void two_Mime_start(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Mime*>(object)).start(*static_cast<stl::string*>(args[0]), *static_cast<bool*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3]), *static_cast<bool*>(args[4])); }
void two_Mime_play(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Mime*>(object)).play(*static_cast<two::Animation*>(args[0]), *static_cast<bool*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3]), *static_cast<bool*>(args[4])); }
void two_Mime_seek(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Mime*>(object)).seek(*static_cast<float*>(args[0])); }
void two_Mime_pause(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::Mime*>(object)).pause(); }
void two_Mime_stop(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::Mime*>(object)).stop(); }
void two_Mime_advance(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Mime*>(object)).advance(*static_cast<float*>(args[0])); }
void two_Mime_next_animation(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::Mime*>(object)).next_animation(); }
void two_Mime_add_item(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Mime*>(object)).add_item(*static_cast<two::Item*>(args[0])); }
void two_Mime_add_nodes(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Mime*>(object)).add_nodes(*static_cast<stl::span<two::Node3>*>(args[0])); }
void two_Mime_playing(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<stl::string*>(result)) = (*static_cast<two::Mime*>(object)).playing(); }
void two_FrustumSlice__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::FrustumSlice(  ); }
void two_FrustumSlice__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::FrustumSlice((*static_cast<two::FrustumSlice*>(other))); }
void two_ShaderDefine__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::ShaderDefine(  ); }
void two_ShaderDefine__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::ShaderDefine((*static_cast<two::ShaderDefine*>(other))); }
void two_ShaderBlock__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::ShaderBlock(  ); }
void two_ShaderBlock__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::ShaderBlock((*static_cast<two::ShaderBlock*>(other))); }
void two_ShaderBlock_add_option(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::ShaderBlock*>(object)).add_option(*static_cast<stl::string*>(args[0])); }
void two_ShaderBlock_add_mode(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::ShaderBlock*>(object)).add_mode(*static_cast<stl::string*>(args[0])); }
void two_ShaderBlock_add_define(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::ShaderBlock*>(object)).add_define(*static_cast<stl::string*>(args[0]), *static_cast<stl::string*>(args[1])); }
void two_ProgramMode__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::ProgramMode(  ); }
void two_ProgramMode__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::ProgramMode((*static_cast<two::ProgramMode*>(other))); }
void two_ProgramBlock__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::ProgramBlock(  ); }
void two_ProgramBlock__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::ProgramBlock((*static_cast<two::ProgramBlock*>(other))); }
void two_Program_set_block(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Program*>(object)).set_block(*static_cast<two::MaterialBlock*>(args[0]), *static_cast<bool*>(args[1])); }
void two_Program_set_pass(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Program*>(object)).set_pass(*static_cast<two::PassType*>(args[0]), *static_cast<bool*>(args[1])); }
void two_Program_set_source(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Program*>(object)).set_source(*static_cast<two::ShaderType*>(args[0]), *static_cast<stl::string*>(args[1])); }
void two_Program_register_blocks(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Program*>(object)).register_blocks(*static_cast<two::Program*>(args[0])); }
void two_Program_register_block(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Program*>(object)).register_block(*static_cast<two::ShaderBlock*>(args[0])); }
void two_ProgramVersion__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::ProgramVersion(  ); }
void two_ProgramVersion__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::ProgramVersion( *static_cast<two::Program*>(args[0]) ); }
void two_ProgramVersion__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::ProgramVersion((*static_cast<two::ProgramVersion*>(other))); }
void two_ProgramVersion_clear(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::ProgramVersion*>(object)).clear(); }
void two_ProgramVersion_set_option(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::ProgramVersion*>(object)).set_option(*static_cast<uint8_t*>(args[0]), *static_cast<uint8_t*>(args[1]), *static_cast<bool*>(args[2])); }
void two_ProgramVersion_set_mode(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::ProgramVersion*>(object)).set_mode(*static_cast<uint8_t*>(args[0]), *static_cast<uint8_t*>(args[1]), *static_cast<uint8_t*>(args[2])); }
void two_ProgramVersion_hash(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<ullong*>(result)) = (*static_cast<two::ProgramVersion*>(object)).hash(); }
void two_Pass__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Pass(  ); }
void two_Pass__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Pass((*static_cast<two::Pass*>(other))); }
void two_RenderFrame__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::RenderFrame(  ); }
void two_RenderFrame__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::RenderFrame((*static_cast<two::RenderFrame*>(other))); }
void two_Render__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Render(  ); }
void two_Render__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Render( *static_cast<two::Shading*>(args[0]), *static_cast<two::Viewport*>(args[1]), *static_cast<two::RenderTarget*>(args[2]), *static_cast<two::RenderFrame*>(args[3]) ); }
void two_Render__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Render( *static_cast<two::Shading*>(args[0]), *static_cast<two::Viewport*>(args[1]), *static_cast<two::RenderTarget*>(args[2]), *static_cast<two::FrameBuffer*>(args[3]), *static_cast<two::RenderFrame*>(args[4]) ); }
void two_Render_subrender(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Render*>(object)).subrender(*static_cast<two::Render*>(args[0])); }
void two_Render_next_pass(void* object, span<void*> args, void*& result) { (*static_cast<two::Pass*>(result)) = (*static_cast<two::Render*>(object)).next_pass(static_cast<const char*>(args[0]), *static_cast<two::PassType*>(args[1]), *static_cast<uint8_t*>(args[2])); }
void two_Render_composite_pass(void* object, span<void*> args, void*& result) { (*static_cast<two::Pass*>(result)) = (*static_cast<two::Render*>(object)).composite_pass(static_cast<const char*>(args[0]), *static_cast<two::FrameBuffer*>(args[1]), *static_cast<two::vec4*>(args[2])); }
void* two_GfxBlock__get_type(void* object) { return &(*static_cast<two::GfxBlock*>(object)).m_type; }
void two_Renderer_gather(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Renderer*>(object)).gather(*static_cast<two::Render*>(args[0])); }
void two_Renderer_begin(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Renderer*>(object)).begin(*static_cast<two::Render*>(args[0])); }
void two_Renderer_end(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Renderer*>(object)).end(*static_cast<two::Render*>(args[0])); }
void two_GfxSystem__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::GfxSystem( *static_cast<stl::string*>(args[0]) ); }
void* two_GfxSystem__get_textures(void* object) { return &(*static_cast<two::GfxSystem*>(object)).textures(); }
void* two_GfxSystem__get_programs(void* object) { return &(*static_cast<two::GfxSystem*>(object)).programs(); }
void* two_GfxSystem__get_materials(void* object) { return &(*static_cast<two::GfxSystem*>(object)).materials(); }
void* two_GfxSystem__get_models(void* object) { return &(*static_cast<two::GfxSystem*>(object)).models(); }
void* two_GfxSystem__get_flows(void* object) { return &(*static_cast<two::GfxSystem*>(object)).flows(); }
void* two_GfxSystem__get_prefabs(void* object) { return &(*static_cast<two::GfxSystem*>(object)).prefabs(); }
void two_GfxSystem_main_target(void* object, span<void*> args, void*& result) { UNUSED(args); result = &(*static_cast<two::GfxSystem*>(object)).main_target(); }
void two_GfxSystem_default_pipeline(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::GfxSystem*>(object)).default_pipeline(); }
void two_GfxSystem_add_resource_path(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::GfxSystem*>(object)).add_resource_path(*static_cast<stl::string*>(args[0]), *static_cast<bool*>(args[1])); }
void two_GfxSystem_debug_material(void* object, span<void*> args, void*& result) { UNUSED(args); result = &(*static_cast<two::GfxSystem*>(object)).debug_material(); }
void two_GfxSystem_create_model(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::GfxSystem*>(object)).create_model(*static_cast<stl::string*>(args[0])); }
void two_GfxSystem_create_model_geo(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::GfxSystem*>(object)).create_model_geo(*static_cast<stl::string*>(args[0]), *static_cast<two::MeshPacker*>(args[1]), *static_cast<bool*>(args[2]), *static_cast<bool*>(args[3])); }
void two_GfxSystem_create_model_gpu(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::GfxSystem*>(object)).create_model_gpu(*static_cast<stl::string*>(args[0]), *static_cast<two::GpuMesh*>(args[1]), *static_cast<bool*>(args[2]), *static_cast<bool*>(args[3])); }
void two_GfxSystem_fetch_material(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::GfxSystem*>(object)).fetch_material(*static_cast<stl::string*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<bool*>(args[2])); }
void two_GfxSystem_fetch_image256_material(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::GfxSystem*>(object)).fetch_image256_material(*static_cast<two::Image256*>(args[0])); }
void two_GfxSystem_shape(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::GfxSystem*>(object)).shape(*static_cast<two::Shape*>(args[0]), *static_cast<two::Symbol*>(args[1]), *static_cast<two::DrawMode*>(args[2])); }
void two_GfxSystem_symbol_material(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::GfxSystem*>(object)).symbol_material(*static_cast<two::Symbol*>(args[0]), *static_cast<two::DrawMode*>(args[1])); }
void two_MaterialParam_two_Colour__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::MaterialParam<two::Colour>(  ); }
void two_MaterialParam_two_Colour__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::MaterialParam<two::Colour>((*static_cast<two::MaterialParam<two::Colour>*>(other))); }
void two_MaterialParam_float__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::MaterialParam<float>(  ); }
void two_MaterialParam_float__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::MaterialParam<float>((*static_cast<two::MaterialParam<float>*>(other))); }
void two_MaterialParam_two_vec4__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::MaterialParam<two::vec4>(  ); }
void two_MaterialParam_two_vec4__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::MaterialParam<two::vec4>((*static_cast<two::MaterialParam<two::vec4>*>(other))); }
void two_MaterialBase__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::MaterialBase(  ); }
void two_MaterialBase__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::MaterialBase((*static_cast<two::MaterialBase*>(other))); }
void two_MaterialUser__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::MaterialUser(  ); }
void two_MaterialUser__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::MaterialUser((*static_cast<two::MaterialUser*>(other))); }
void two_MaterialAlpha__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::MaterialAlpha(  ); }
void two_MaterialAlpha__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::MaterialAlpha((*static_cast<two::MaterialAlpha*>(other))); }
void two_MaterialSolid__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::MaterialSolid(  ); }
void two_MaterialSolid__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::MaterialSolid((*static_cast<two::MaterialSolid*>(other))); }
void two_MaterialPoint__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::MaterialPoint(  ); }
void two_MaterialPoint__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::MaterialPoint((*static_cast<two::MaterialPoint*>(other))); }
void two_MaterialLine__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::MaterialLine(  ); }
void two_MaterialLine__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::MaterialLine((*static_cast<two::MaterialLine*>(other))); }
void two_MaterialFresnel__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::MaterialFresnel(  ); }
void two_MaterialFresnel__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::MaterialFresnel((*static_cast<two::MaterialFresnel*>(other))); }
void two_MaterialLit__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::MaterialLit(  ); }
void two_MaterialLit__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::MaterialLit((*static_cast<two::MaterialLit*>(other))); }
void two_MaterialPbr__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::MaterialPbr(  ); }
void two_MaterialPbr__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::MaterialPbr( *static_cast<two::Colour*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]) ); }
void two_MaterialPbr__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::MaterialPbr((*static_cast<two::MaterialPbr*>(other))); }
void two_MaterialPhong__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::MaterialPhong(  ); }
void two_MaterialPhong__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::MaterialPhong((*static_cast<two::MaterialPhong*>(other))); }
void two_ModelElem__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::ModelElem(  ); }
void two_ModelElem__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::ModelElem((*static_cast<two::ModelElem*>(other))); }
void two_Model_get_mesh(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::Model*>(object)).get_mesh(*static_cast<size_t*>(args[0])); }
void two_Model_add_mesh(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::Model*>(object)).add_mesh(*static_cast<stl::string*>(args[0]), *static_cast<bool*>(args[1])); }
void two_Model_add_rig(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::Model*>(object)).add_rig(*static_cast<stl::string*>(args[0])); }
void two_Model_add_item(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::Model*>(object)).add_item(*static_cast<two::Mesh*>(args[0]), *static_cast<two::mat4*>(args[1]), *static_cast<int*>(args[2]), *static_cast<two::Colour*>(args[3]), static_cast<two::Material*>(args[4])); }
void two_Model_prepare(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::Model*>(object)).prepare(); }
void two_Flow__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Flow(  ); }
void two_Flow__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Flow((*static_cast<two::Flow*>(other))); }
void two_Flare__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Flare(  ); }
void two_Flare__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Flare((*static_cast<two::Flare*>(other))); }
void two_Batch__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Batch(  ); }
void two_Batch__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Batch( *static_cast<two::Item*>(args[0]), *static_cast<uint16_t*>(args[1]) ); }
void two_Batch__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Batch((*static_cast<two::Batch*>(other))); }
void two_Batch_update_aabb(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Batch*>(object)).update_aabb(*static_cast<stl::span<two::mat4>*>(args[0])); }
void two_Batch_transforms(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Batch*>(object)).transforms(*static_cast<stl::span<two::mat4>*>(args[0])); }
void two_Batch_begin(void* object, span<void*> args, void*& result) { (*static_cast<stl::span<float>*>(result)) = (*static_cast<two::Batch*>(object)).begin(*static_cast<uint32_t*>(args[0])); }
void two_Batch_commit(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Batch*>(object)).commit(*static_cast<stl::span<float>*>(args[0])); }
void two_Batch_cache(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Batch*>(object)).cache(*static_cast<stl::span<float>*>(args[0])); }
void two_Batch_transform(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Batch*>(object)).transform(*static_cast<two::mat4*>(args[0])); }
void two_Item__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Item(  ); }
void two_Item__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Item( *static_cast<two::Node3*>(args[0]), *static_cast<two::Model*>(args[1]), *static_cast<uint32_t*>(args[2]), static_cast<two::Material*>(args[3]) ); }
void two_Item_update_aabb(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::Item*>(object)).update_aabb(); }
void two_ImportConfig__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::ImportConfig(  ); }
void two_ImportConfig__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::ImportConfig((*static_cast<two::ImportConfig*>(other))); }
void two_Prefab_add(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Prefab*>(object)).add(*static_cast<two::Scene*>(args[0]), static_cast<two::Mime*>(args[1])); }
void two_AssetStore_two_Texture_get(void* object, span<void*> args, void*& result) { result = (*static_cast<two::AssetStore<two::Texture>*>(object)).get(*static_cast<stl::string*>(args[0])); }
void two_AssetStore_two_Texture_create(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::AssetStore<two::Texture>*>(object)).create(*static_cast<stl::string*>(args[0])); }
void two_AssetStore_two_Texture_fetch(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::AssetStore<two::Texture>*>(object)).fetch(*static_cast<stl::string*>(args[0])); }
void two_AssetStore_two_Texture_file(void* object, span<void*> args, void*& result) { result = (*static_cast<two::AssetStore<two::Texture>*>(object)).file(*static_cast<stl::string*>(args[0])); }
void two_AssetStore_two_Texture_file_at(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::AssetStore<two::Texture>*>(object)).file_at(*static_cast<stl::string*>(args[0]), *static_cast<stl::string*>(args[1])); }
void two_AssetStore_two_Texture_load(void* object, span<void*> args, void*& result) { result = (*static_cast<two::AssetStore<two::Texture>*>(object)).load(*static_cast<stl::string*>(args[0]), *static_cast<stl::string*>(args[1])); }
void two_AssetStore_two_Texture_destroy(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::AssetStore<two::Texture>*>(object)).destroy(*static_cast<stl::string*>(args[0])); }
void two_AssetStore_two_Texture_clear(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::AssetStore<two::Texture>*>(object)).clear(); }
void two_AssetStore_two_Program_get(void* object, span<void*> args, void*& result) { result = (*static_cast<two::AssetStore<two::Program>*>(object)).get(*static_cast<stl::string*>(args[0])); }
void two_AssetStore_two_Program_create(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::AssetStore<two::Program>*>(object)).create(*static_cast<stl::string*>(args[0])); }
void two_AssetStore_two_Program_fetch(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::AssetStore<two::Program>*>(object)).fetch(*static_cast<stl::string*>(args[0])); }
void two_AssetStore_two_Program_file(void* object, span<void*> args, void*& result) { result = (*static_cast<two::AssetStore<two::Program>*>(object)).file(*static_cast<stl::string*>(args[0])); }
void two_AssetStore_two_Program_file_at(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::AssetStore<two::Program>*>(object)).file_at(*static_cast<stl::string*>(args[0]), *static_cast<stl::string*>(args[1])); }
void two_AssetStore_two_Program_load(void* object, span<void*> args, void*& result) { result = (*static_cast<two::AssetStore<two::Program>*>(object)).load(*static_cast<stl::string*>(args[0]), *static_cast<stl::string*>(args[1])); }
void two_AssetStore_two_Program_destroy(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::AssetStore<two::Program>*>(object)).destroy(*static_cast<stl::string*>(args[0])); }
void two_AssetStore_two_Program_clear(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::AssetStore<two::Program>*>(object)).clear(); }
void two_AssetStore_two_Material_get(void* object, span<void*> args, void*& result) { result = (*static_cast<two::AssetStore<two::Material>*>(object)).get(*static_cast<stl::string*>(args[0])); }
void two_AssetStore_two_Material_create(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::AssetStore<two::Material>*>(object)).create(*static_cast<stl::string*>(args[0])); }
void two_AssetStore_two_Material_fetch(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::AssetStore<two::Material>*>(object)).fetch(*static_cast<stl::string*>(args[0])); }
void two_AssetStore_two_Material_file(void* object, span<void*> args, void*& result) { result = (*static_cast<two::AssetStore<two::Material>*>(object)).file(*static_cast<stl::string*>(args[0])); }
void two_AssetStore_two_Material_file_at(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::AssetStore<two::Material>*>(object)).file_at(*static_cast<stl::string*>(args[0]), *static_cast<stl::string*>(args[1])); }
void two_AssetStore_two_Material_load(void* object, span<void*> args, void*& result) { result = (*static_cast<two::AssetStore<two::Material>*>(object)).load(*static_cast<stl::string*>(args[0]), *static_cast<stl::string*>(args[1])); }
void two_AssetStore_two_Material_destroy(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::AssetStore<two::Material>*>(object)).destroy(*static_cast<stl::string*>(args[0])); }
void two_AssetStore_two_Material_clear(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::AssetStore<two::Material>*>(object)).clear(); }
void two_AssetStore_two_Model_get(void* object, span<void*> args, void*& result) { result = (*static_cast<two::AssetStore<two::Model>*>(object)).get(*static_cast<stl::string*>(args[0])); }
void two_AssetStore_two_Model_create(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::AssetStore<two::Model>*>(object)).create(*static_cast<stl::string*>(args[0])); }
void two_AssetStore_two_Model_fetch(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::AssetStore<two::Model>*>(object)).fetch(*static_cast<stl::string*>(args[0])); }
void two_AssetStore_two_Model_file(void* object, span<void*> args, void*& result) { result = (*static_cast<two::AssetStore<two::Model>*>(object)).file(*static_cast<stl::string*>(args[0])); }
void two_AssetStore_two_Model_file_at(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::AssetStore<two::Model>*>(object)).file_at(*static_cast<stl::string*>(args[0]), *static_cast<stl::string*>(args[1])); }
void two_AssetStore_two_Model_load(void* object, span<void*> args, void*& result) { result = (*static_cast<two::AssetStore<two::Model>*>(object)).load(*static_cast<stl::string*>(args[0]), *static_cast<stl::string*>(args[1])); }
void two_AssetStore_two_Model_destroy(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::AssetStore<two::Model>*>(object)).destroy(*static_cast<stl::string*>(args[0])); }
void two_AssetStore_two_Model_clear(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::AssetStore<two::Model>*>(object)).clear(); }
void two_AssetStore_two_Flow_get(void* object, span<void*> args, void*& result) { result = (*static_cast<two::AssetStore<two::Flow>*>(object)).get(*static_cast<stl::string*>(args[0])); }
void two_AssetStore_two_Flow_create(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::AssetStore<two::Flow>*>(object)).create(*static_cast<stl::string*>(args[0])); }
void two_AssetStore_two_Flow_fetch(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::AssetStore<two::Flow>*>(object)).fetch(*static_cast<stl::string*>(args[0])); }
void two_AssetStore_two_Flow_file(void* object, span<void*> args, void*& result) { result = (*static_cast<two::AssetStore<two::Flow>*>(object)).file(*static_cast<stl::string*>(args[0])); }
void two_AssetStore_two_Flow_file_at(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::AssetStore<two::Flow>*>(object)).file_at(*static_cast<stl::string*>(args[0]), *static_cast<stl::string*>(args[1])); }
void two_AssetStore_two_Flow_load(void* object, span<void*> args, void*& result) { result = (*static_cast<two::AssetStore<two::Flow>*>(object)).load(*static_cast<stl::string*>(args[0]), *static_cast<stl::string*>(args[1])); }
void two_AssetStore_two_Flow_destroy(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::AssetStore<two::Flow>*>(object)).destroy(*static_cast<stl::string*>(args[0])); }
void two_AssetStore_two_Flow_clear(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::AssetStore<two::Flow>*>(object)).clear(); }
void two_AssetStore_two_Prefab_get(void* object, span<void*> args, void*& result) { result = (*static_cast<two::AssetStore<two::Prefab>*>(object)).get(*static_cast<stl::string*>(args[0])); }
void two_AssetStore_two_Prefab_create(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::AssetStore<two::Prefab>*>(object)).create(*static_cast<stl::string*>(args[0])); }
void two_AssetStore_two_Prefab_fetch(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::AssetStore<two::Prefab>*>(object)).fetch(*static_cast<stl::string*>(args[0])); }
void two_AssetStore_two_Prefab_file(void* object, span<void*> args, void*& result) { result = (*static_cast<two::AssetStore<two::Prefab>*>(object)).file(*static_cast<stl::string*>(args[0])); }
void two_AssetStore_two_Prefab_file_at(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::AssetStore<two::Prefab>*>(object)).file_at(*static_cast<stl::string*>(args[0]), *static_cast<stl::string*>(args[1])); }
void two_AssetStore_two_Prefab_load(void* object, span<void*> args, void*& result) { result = (*static_cast<two::AssetStore<two::Prefab>*>(object)).load(*static_cast<stl::string*>(args[0]), *static_cast<stl::string*>(args[1])); }
void two_AssetStore_two_Prefab_destroy(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::AssetStore<two::Prefab>*>(object)).destroy(*static_cast<stl::string*>(args[0])); }
void two_AssetStore_two_Prefab_clear(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::AssetStore<two::Prefab>*>(object)).clear(); }
void two_Camera_set_look_at(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Camera*>(object)).set_look_at(*static_cast<two::vec3*>(args[0]), *static_cast<two::vec3*>(args[1])); }
void two_Camera_set_isometric(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Camera*>(object)).set_isometric(*static_cast<two::IsometricAngle*>(args[0]), *static_cast<two::vec3*>(args[1])); }
void two_Camera_ray(void* object, span<void*> args, void*& result) { (*static_cast<two::Ray*>(result)) = (*static_cast<two::Camera*>(object)).ray(*static_cast<two::vec2*>(args[0])); }
void two_Camera_transform(void* object, span<void*> args, void*& result) { (*static_cast<two::v3<float>*>(result)) = (*static_cast<two::Camera*>(object)).transform(*static_cast<two::vec3*>(args[0])); }
void two_Camera_project(void* object, span<void*> args, void*& result) { (*static_cast<two::v3<float>*>(result)) = (*static_cast<two::Camera*>(object)).project(*static_cast<two::vec3*>(args[0])); }
void two_MirrorCamera__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::MirrorCamera(  ); }
void two_MirrorCamera__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::MirrorCamera((*static_cast<two::MirrorCamera*>(other))); }
void two_DepthParams__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::DepthParams(  ); }
void two_DepthParams__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::DepthParams((*static_cast<two::DepthParams*>(other))); }
void two_DistanceParams__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::DistanceParams(  ); }
void two_DistanceParams__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::DistanceParams((*static_cast<two::DistanceParams*>(other))); }
void two_GpuMesh__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::GpuMesh(  ); }
void two_GpuMesh__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::GpuMesh((*static_cast<two::GpuMesh*>(other))); }
void two_Mesh_clear(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::Mesh*>(object)).clear(); }
void two_Mesh_write(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Mesh*>(object)).write(*static_cast<two::MeshPacker*>(args[0]), *static_cast<bool*>(args[1]), *static_cast<bool*>(args[2])); }
void two_Mesh_xwrite(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Mesh*>(object)).xwrite(*static_cast<two::MeshPacker*>(args[0]), *static_cast<two::mat4*>(args[1]), *static_cast<bool*>(args[2]), *static_cast<bool*>(args[3])); }
void two_Mesh_morph(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Mesh*>(object)).morph(*static_cast<two::MeshPacker*>(args[0])); }
void two_Mesh_upload(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Mesh*>(object)).upload(*static_cast<two::GpuMesh*>(args[0]), *static_cast<bool*>(args[1])); }
void two_Mesh_cache(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Mesh*>(object)).cache(*static_cast<two::GpuMesh*>(args[0])); }
void two_Mesh_direct(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::Mesh*>(object)).direct(*static_cast<uint32_t*>(args[0]), *static_cast<uint32_t*>(args[1]), *static_cast<uint32_t*>(args[2])); }
void two_Direct__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Direct(  ); }
void two_Direct__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Direct( *static_cast<two::Item*>(args[0]) ); }
void two_Lines__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Lines(  ); }
void two_Lines__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Lines( *static_cast<stl::vector<two::vec3>*>(args[0]) ); }
void two_Lines__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Lines( *static_cast<two::Curve3*>(args[0]), *static_cast<size_t*>(args[1]) ); }
void two_Lines_add(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Lines*>(object)).add(*static_cast<two::vec3*>(args[0]), *static_cast<two::vec3*>(args[1]), *static_cast<two::Colour*>(args[2]), *static_cast<two::Colour*>(args[3])); }
void two_Lines_start(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Lines*>(object)).start(*static_cast<two::vec3*>(args[0]), *static_cast<two::Colour*>(args[1])); }
void two_Lines_next(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Lines*>(object)).next(*static_cast<two::vec3*>(args[0]), *static_cast<two::Colour*>(args[1])); }
void two_Lines_setup(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::Lines*>(object)).setup(); }
void two_Lines_write(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Lines*>(object)).write(*static_cast<two::Mesh*>(args[0])); }
void two_Lines_commit(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Lines*>(object)).commit(*static_cast<two::Batch*>(args[0])); }
void two_BlockFilter_submit(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::BlockFilter*>(object)).submit(*static_cast<two::Pass*>(args[0]), *static_cast<two::FrameBuffer*>(args[1]), *static_cast<two::ProgramVersion*>(args[2]), *static_cast<two::RenderQuad*>(args[3]), *static_cast<uint64_t*>(args[4]), *static_cast<bool*>(args[5])); }
void two_BlockFilter_quad(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::BlockFilter*>(object)).quad(*static_cast<two::Pass*>(args[0]), *static_cast<two::FrameBuffer*>(args[1]), *static_cast<two::ProgramVersion*>(args[2]), *static_cast<uint64_t*>(args[3]), *static_cast<bool*>(args[4])); }
void two_BlockFilter_multiply(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::BlockFilter*>(object)).multiply(*static_cast<float*>(args[0])); }
void two_BlockFilter_source0p(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::BlockFilter*>(object)).source0p(*static_cast<two::Texture*>(args[0]), *static_cast<two::ProgramVersion*>(args[1]), *static_cast<int*>(args[2]), *static_cast<uint32_t*>(args[3])); }
void two_BlockFilter_source0(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::BlockFilter*>(object)).source0(*static_cast<two::Texture*>(args[0]), *static_cast<uint32_t*>(args[1])); }
void two_BlockFilter_source1(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::BlockFilter*>(object)).source1(*static_cast<two::Texture*>(args[0]), *static_cast<uint32_t*>(args[1])); }
void two_BlockFilter_source2(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::BlockFilter*>(object)).source2(*static_cast<two::Texture*>(args[0]), *static_cast<uint32_t*>(args[1])); }
void two_BlockFilter_source3(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::BlockFilter*>(object)).source3(*static_cast<two::Texture*>(args[0]), *static_cast<uint32_t*>(args[1])); }
void two_BlockFilter_sourcedepth(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::BlockFilter*>(object)).sourcedepth(*static_cast<two::Texture*>(args[0]), *static_cast<uint32_t*>(args[1])); }
void two_BlockFilter_uniform(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::BlockFilter*>(object)).uniform(*static_cast<two::Pass*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<two::vec4*>(args[2])); }
void two_BlockFilter_uniforms(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::BlockFilter*>(object)).uniforms(*static_cast<two::Pass*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<stl::span<float>*>(args[2])); }
void two_BlockCopy_submit(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::BlockCopy*>(object)).submit(*static_cast<two::Pass*>(args[0]), *static_cast<two::FrameBuffer*>(args[1]), *static_cast<two::Texture*>(args[2]), *static_cast<two::RenderQuad*>(args[3]), *static_cast<uint64_t*>(args[4]), *static_cast<bool*>(args[5])); }
void two_BlockCopy_quad(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::BlockCopy*>(object)).quad(*static_cast<two::Pass*>(args[0]), *static_cast<two::FrameBuffer*>(args[1]), *static_cast<two::Texture*>(args[2]), *static_cast<uint64_t*>(args[3]), *static_cast<bool*>(args[4])); }
void two_BlockCopy_debug_show_texture(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::BlockCopy*>(object)).debug_show_texture(*static_cast<two::Render*>(args[0]), *static_cast<two::Texture*>(args[1]), *static_cast<two::vec4*>(args[2]), *static_cast<int*>(args[3])); }
void two_BlockCopy_debug_show_texturep(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::BlockCopy*>(object)).debug_show_texturep(*static_cast<two::Render*>(args[0]), static_cast<two::Texture*>(args[1]), *static_cast<two::vec4*>(args[2]), *static_cast<int*>(args[3])); }
void two_ClusteredFrustum__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::ClusteredFrustum(  ); }
void two_ClusteredFrustum__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::ClusteredFrustum((*static_cast<two::ClusteredFrustum*>(other))); }
void two_Light__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Light( *static_cast<two::Node3*>(args[0]), *static_cast<two::LightType*>(args[1]), *static_cast<bool*>(args[2]), *static_cast<two::Colour*>(args[3]), *static_cast<float*>(args[4]), *static_cast<float*>(args[5]) ); }
void two_TPool_two_Node3_add(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::TPool<two::Node3>*>(object)).add(*static_cast<two::Node3*>(args[0])); }
void two_TPool_two_Node3_addvec(void* object, span<void*> args, void*& result) { (*static_cast<stl::span<two::Node3>*>(result)) = (*static_cast<two::TPool<two::Node3>*>(object)).addvec(*static_cast<stl::span<two::Node3>*>(args[0])); }
void two_TPool_two_Node3_talloc(void* object, span<void*> args, void*& result) { UNUSED(args); result = (*static_cast<two::TPool<two::Node3>*>(object)).talloc(); }
void two_TPool_two_Node3_tdestroy(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::TPool<two::Node3>*>(object)).tdestroy(*static_cast<two::Node3*>(args[0])); }
void two_TPool_two_Node3_tfree(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::TPool<two::Node3>*>(object)).tfree(*static_cast<two::Node3*>(args[0])); }
void two_TPool_two_Item_add(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::TPool<two::Item>*>(object)).add(*static_cast<two::Item*>(args[0])); }
void two_TPool_two_Item_addvec(void* object, span<void*> args, void*& result) { (*static_cast<stl::span<two::Item>*>(result)) = (*static_cast<two::TPool<two::Item>*>(object)).addvec(*static_cast<stl::span<two::Item>*>(args[0])); }
void two_TPool_two_Item_talloc(void* object, span<void*> args, void*& result) { UNUSED(args); result = (*static_cast<two::TPool<two::Item>*>(object)).talloc(); }
void two_TPool_two_Item_tdestroy(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::TPool<two::Item>*>(object)).tdestroy(*static_cast<two::Item*>(args[0])); }
void two_TPool_two_Item_tfree(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::TPool<two::Item>*>(object)).tfree(*static_cast<two::Item*>(args[0])); }
void two_TPool_two_Batch_add(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::TPool<two::Batch>*>(object)).add(*static_cast<two::Batch*>(args[0])); }
void two_TPool_two_Batch_addvec(void* object, span<void*> args, void*& result) { (*static_cast<stl::span<two::Batch>*>(result)) = (*static_cast<two::TPool<two::Batch>*>(object)).addvec(*static_cast<stl::span<two::Batch>*>(args[0])); }
void two_TPool_two_Batch_talloc(void* object, span<void*> args, void*& result) { UNUSED(args); result = (*static_cast<two::TPool<two::Batch>*>(object)).talloc(); }
void two_TPool_two_Batch_tdestroy(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::TPool<two::Batch>*>(object)).tdestroy(*static_cast<two::Batch*>(args[0])); }
void two_TPool_two_Batch_tfree(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::TPool<two::Batch>*>(object)).tfree(*static_cast<two::Batch*>(args[0])); }
void two_TPool_two_Direct_add(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::TPool<two::Direct>*>(object)).add(*static_cast<two::Direct*>(args[0])); }
void two_TPool_two_Direct_addvec(void* object, span<void*> args, void*& result) { (*static_cast<stl::span<two::Direct>*>(result)) = (*static_cast<two::TPool<two::Direct>*>(object)).addvec(*static_cast<stl::span<two::Direct>*>(args[0])); }
void two_TPool_two_Direct_talloc(void* object, span<void*> args, void*& result) { UNUSED(args); result = (*static_cast<two::TPool<two::Direct>*>(object)).talloc(); }
void two_TPool_two_Direct_tdestroy(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::TPool<two::Direct>*>(object)).tdestroy(*static_cast<two::Direct*>(args[0])); }
void two_TPool_two_Direct_tfree(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::TPool<two::Direct>*>(object)).tfree(*static_cast<two::Direct*>(args[0])); }
void two_TPool_two_Mime_add(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::TPool<two::Mime>*>(object)).add(*static_cast<two::Mime*>(args[0])); }
void two_TPool_two_Mime_addvec(void* object, span<void*> args, void*& result) { (*static_cast<stl::span<two::Mime>*>(result)) = (*static_cast<two::TPool<two::Mime>*>(object)).addvec(*static_cast<stl::span<two::Mime>*>(args[0])); }
void two_TPool_two_Mime_talloc(void* object, span<void*> args, void*& result) { UNUSED(args); result = (*static_cast<two::TPool<two::Mime>*>(object)).talloc(); }
void two_TPool_two_Mime_tdestroy(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::TPool<two::Mime>*>(object)).tdestroy(*static_cast<two::Mime*>(args[0])); }
void two_TPool_two_Mime_tfree(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::TPool<two::Mime>*>(object)).tfree(*static_cast<two::Mime*>(args[0])); }
void two_TPool_two_Light_add(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::TPool<two::Light>*>(object)).add(*static_cast<two::Light*>(args[0])); }
void two_TPool_two_Light_addvec(void* object, span<void*> args, void*& result) { (*static_cast<stl::span<two::Light>*>(result)) = (*static_cast<two::TPool<two::Light>*>(object)).addvec(*static_cast<stl::span<two::Light>*>(args[0])); }
void two_TPool_two_Light_talloc(void* object, span<void*> args, void*& result) { UNUSED(args); result = (*static_cast<two::TPool<two::Light>*>(object)).talloc(); }
void two_TPool_two_Light_tdestroy(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::TPool<two::Light>*>(object)).tdestroy(*static_cast<two::Light*>(args[0])); }
void two_TPool_two_Light_tfree(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::TPool<two::Light>*>(object)).tfree(*static_cast<two::Light*>(args[0])); }
void two_TPool_two_Flare_add(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::TPool<two::Flare>*>(object)).add(*static_cast<two::Flare*>(args[0])); }
void two_TPool_two_Flare_addvec(void* object, span<void*> args, void*& result) { (*static_cast<stl::span<two::Flare>*>(result)) = (*static_cast<two::TPool<two::Flare>*>(object)).addvec(*static_cast<stl::span<two::Flare>*>(args[0])); }
void two_TPool_two_Flare_talloc(void* object, span<void*> args, void*& result) { UNUSED(args); result = (*static_cast<two::TPool<two::Flare>*>(object)).talloc(); }
void two_TPool_two_Flare_tdestroy(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::TPool<two::Flare>*>(object)).tdestroy(*static_cast<two::Flare*>(args[0])); }
void two_TPool_two_Flare_tfree(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::TPool<two::Flare>*>(object)).tfree(*static_cast<two::Flare*>(args[0])); }
void two_Viewport__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Viewport(  ); }
void two_Viewport__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Viewport( *static_cast<two::Camera*>(args[0]), *static_cast<two::Scene*>(args[1]), *static_cast<two::vec4*>(args[2]), *static_cast<bool*>(args[3]) ); }
void two_Viewport_cull(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Viewport*>(object)).cull(*static_cast<two::Render*>(args[0])); }
void two_Viewport_render(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Viewport*>(object)).render(*static_cast<two::Render*>(args[0])); }
void two_Viewport_set_clustered(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Viewport*>(object)).set_clustered(*static_cast<two::GfxSystem*>(args[0])); }
void two_RenderQuad__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::RenderQuad(  ); }
void two_RenderQuad__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::RenderQuad( *static_cast<two::vec4*>(args[0]), *static_cast<two::vec4*>(args[1]), *static_cast<bool*>(args[2]), *static_cast<bool*>(args[3]) ); }
void two_RenderQuad__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::RenderQuad( *static_cast<two::vec4*>(args[0]), *static_cast<bool*>(args[1]), *static_cast<bool*>(args[2]) ); }
void two_RenderQuad__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::RenderQuad((*static_cast<two::RenderQuad*>(other))); }
void two_FrameBuffer__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::FrameBuffer(  ); }
void two_FrameBuffer__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::FrameBuffer( *static_cast<two::uvec2*>(args[0]), *static_cast<two::TextureFormat*>(args[1]), *static_cast<uint64_t*>(args[2]) ); }
void two_FrameBuffer__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::FrameBuffer( *static_cast<two::uvec2*>(args[0]), *static_cast<stl::span<two::Texture*>*>(args[1]) ); }
void two_FrameBuffer_valid(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<two::FrameBuffer*>(object)).valid(); }
void two_SwapBuffer__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::SwapBuffer(  ); }
void two_SwapBuffer_create(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::SwapBuffer*>(object)).create(*static_cast<two::uvec2*>(args[0]), *static_cast<two::TextureFormat*>(args[1])); }
void two_SwapBuffer_swap(void* object, span<void*> args, void*& result) { UNUSED(args); result = &(*static_cast<two::SwapBuffer*>(object)).swap(); }
void two_SwapBuffer_current(void* object, span<void*> args, void*& result) { UNUSED(args); result = &(*static_cast<two::SwapBuffer*>(object)).current(); }
void two_SwapBuffer_last(void* object, span<void*> args, void*& result) { UNUSED(args); result = &(*static_cast<two::SwapBuffer*>(object)).last(); }
void two_Cascade__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Cascade(  ); }
void two_Cascade_create(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Cascade*>(object)).create(*static_cast<two::uvec2*>(args[0]), *static_cast<two::TextureFormat*>(args[1])); }
void two_Cascade_level(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::Cascade*>(object)).level(*static_cast<uint8_t*>(args[0])); }
void two_SwapCascade__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::SwapCascade(  ); }
void two_SwapCascade_create(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::SwapCascade*>(object)).create(*static_cast<two::uvec2*>(args[0]), *static_cast<two::TextureFormat*>(args[1])); }
void two_SwapCascade_swap(void* object, span<void*> args, void*& result) { UNUSED(args); result = &(*static_cast<two::SwapCascade*>(object)).swap(); }
void two_SwapCascade_last(void* object, span<void*> args, void*& result) { UNUSED(args); result = &(*static_cast<two::SwapCascade*>(object)).last(); }
void two_Sun__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Sun(  ); }
void two_Sun__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Sun((*static_cast<two::Sun*>(other))); }
void two_Radiance__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Radiance(  ); }
void two_Radiance__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Radiance((*static_cast<two::Radiance*>(other))); }
void two_Background__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Background(  ); }
void two_Background__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Background((*static_cast<two::Background*>(other))); }
void two_Skylight__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Skylight(  ); }
void two_Skylight__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Skylight((*static_cast<two::Skylight*>(other))); }
void two_Fog__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Fog(  ); }
void two_Fog__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Fog((*static_cast<two::Fog*>(other))); }
void two_Zone__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Zone(  ); }
void two_Zone__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Zone((*static_cast<two::Zone*>(other))); }
void two_Scene__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Scene( *static_cast<two::GfxSystem*>(args[0]) ); }
void two_Scene_begin(void* object, span<void*> args, void*& result) { UNUSED(args); result = &(*static_cast<two::Scene*>(object)).begin(); }
void two_Scene_update(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::Scene*>(object)).update(); }
void two_Scene_nodes(void* object, span<void*> args, void*& result) { UNUSED(args); result = &two::gfx::nodes((*static_cast<two::Scene*>(object))); }
void two_Scene_items(void* object, span<void*> args, void*& result) { UNUSED(args); result = &two::gfx::items((*static_cast<two::Scene*>(object))); }
void two_Scene_batches(void* object, span<void*> args, void*& result) { UNUSED(args); result = &two::gfx::batches((*static_cast<two::Scene*>(object))); }
void two_Scene_directs(void* object, span<void*> args, void*& result) { UNUSED(args); result = &two::gfx::directs((*static_cast<two::Scene*>(object))); }
void two_Scene_mimes(void* object, span<void*> args, void*& result) { UNUSED(args); result = &two::gfx::mimes((*static_cast<two::Scene*>(object))); }
void two_Scene_lights(void* object, span<void*> args, void*& result) { UNUSED(args); result = &two::gfx::lights((*static_cast<two::Scene*>(object))); }
void two_Scene_flares(void* object, span<void*> args, void*& result) { UNUSED(args); result = &two::gfx::flares((*static_cast<two::Scene*>(object))); }
void two_bxidentity_0(span<void*> args, void*& result) { UNUSED(args); (*static_cast<two::mat4*>(result)) = two::bxidentity(); }
void two_bxinverse_1(span<void*> args, void*& result) { (*static_cast<two::mat4*>(result)) = two::bxinverse(*static_cast<two::mat4*>(args[0])); }
void two_bxSRT_2(span<void*> args, void*& result) { (*static_cast<two::mat4*>(result)) = two::bxSRT(*static_cast<two::vec3*>(args[0]), *static_cast<two::vec3*>(args[1]), *static_cast<two::vec3*>(args[2])); }
void two_bxscale_3(span<void*> args, void*& result) { (*static_cast<two::mat4*>(result)) = two::bxscale(*static_cast<two::vec3*>(args[0])); }
void two_bxrotation_4(span<void*> args, void*& result) { (*static_cast<two::mat4*>(result)) = two::bxrotation(*static_cast<two::quat*>(args[0])); }
void two_bxtranslation_5(span<void*> args, void*& result) { (*static_cast<two::mat4*>(result)) = two::bxtranslation(*static_cast<two::vec3*>(args[0])); }
void two_bxmul_6(span<void*> args, void*& result) { (*static_cast<two::mat4*>(result)) = two::bxmul(*static_cast<two::mat4*>(args[0]), *static_cast<two::mat4*>(args[1])); }
void two_bxmul_7(span<void*> args, void*& result) { (*static_cast<two::v4<float>*>(result)) = two::bxmul(*static_cast<two::mat4*>(args[0]), *static_cast<two::vec4*>(args[1])); }
void two_bxmul_8(span<void*> args, void*& result) { (*static_cast<two::v3<float>*>(result)) = two::bxmul(*static_cast<two::mat4*>(args[0]), *static_cast<two::vec3*>(args[1])); }
void two_bxmulh_9(span<void*> args, void*& result) { (*static_cast<two::v3<float>*>(result)) = two::bxmulh(*static_cast<two::mat4*>(args[0]), *static_cast<two::vec3*>(args[1])); }
void two_bxlookat_10(span<void*> args, void*& result) { (*static_cast<two::mat4*>(result)) = two::bxlookat(*static_cast<two::vec3*>(args[0]), *static_cast<two::vec3*>(args[1])); }
void two_bxlookat_11(span<void*> args, void*& result) { UNUSED(result);  two::bxlookat(*static_cast<two::mat4*>(args[0]), *static_cast<two::vec3*>(args[1]), *static_cast<two::vec3*>(args[2]), *static_cast<two::vec3*>(args[3])); }
void two_bxlookat_12(span<void*> args, void*& result) { (*static_cast<two::mat4*>(result)) = two::bxlookat(*static_cast<two::vec3*>(args[0]), *static_cast<two::vec3*>(args[1]), *static_cast<two::vec3*>(args[2])); }
void two_bxproj_13(span<void*> args, void*& result) { (*static_cast<two::mat4*>(result)) = two::bxproj(*static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3]), *static_cast<bool*>(args[4])); }
void two_bxortho_14(span<void*> args, void*& result) { (*static_cast<two::mat4*>(result)) = two::bxortho(*static_cast<two::vec4*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3]), *static_cast<bool*>(args[4])); }
void two_bxortho_15(span<void*> args, void*& result) { (*static_cast<two::mat4*>(result)) = two::bxortho(*static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3]), *static_cast<float*>(args[4]), *static_cast<float*>(args[5]), *static_cast<float*>(args[6]), *static_cast<bool*>(args[7])); }
void two_bxSRT_16(span<void*> args, void*& result) { (*static_cast<two::mat4*>(result)) = two::bxSRT(*static_cast<two::vec3*>(args[0]), *static_cast<two::quat*>(args[1]), *static_cast<two::vec3*>(args[2])); }
void two_bxTRS_17(span<void*> args, void*& result) { (*static_cast<two::mat4*>(result)) = two::bxTRS(*static_cast<two::vec3*>(args[0]), *static_cast<two::quat*>(args[1]), *static_cast<two::vec3*>(args[2])); }
void two_mirror_camera_18(span<void*> args, void*& result) { (*static_cast<two::MirrorCamera*>(result)) = two::mirror_camera(*static_cast<two::Camera*>(args[0]), *static_cast<two::Node3*>(args[1]), *static_cast<float*>(args[2])); }
void two_gfx_setup_pipeline_minimal_19(span<void*> args, void*& result) { UNUSED(result);  two::gfx::setup_pipeline_minimal(*static_cast<two::GfxSystem*>(args[0])); }
void two_gfx_node_20(span<void*> args, void*& result) { result = &two::gfx::node(*static_cast<two::Gnode*>(args[0]), *static_cast<two::vec3*>(args[1]), *static_cast<two::quat*>(args[2]), *static_cast<two::vec3*>(args[3])); }
void two_gfx_shape_21(span<void*> args, void*& result) { result = &two::gfx::shape(*static_cast<two::Gnode*>(args[0]), *static_cast<two::Shape*>(args[1]), *static_cast<two::Symbol*>(args[2]), *static_cast<uint32_t*>(args[3]), static_cast<two::Material*>(args[4])); }
void two_gfx_draw_22(span<void*> args, void*& result) { UNUSED(result);  two::gfx::draw(*static_cast<two::Gnode*>(args[0]), *static_cast<two::Shape*>(args[1]), *static_cast<two::Symbol*>(args[2]), *static_cast<uint32_t*>(args[3])); }
void two_gfx_sprite_23(span<void*> args, void*& result) { result = &two::gfx::sprite(*static_cast<two::Gnode*>(args[0]), *static_cast<two::Image256*>(args[1]), *static_cast<two::vec2*>(args[2]), *static_cast<uint32_t*>(args[3]), static_cast<two::Material*>(args[4])); }
void two_gfx_item_24(span<void*> args, void*& result) { result = &two::gfx::item(*static_cast<two::Gnode*>(args[0]), *static_cast<two::Model*>(args[1]), *static_cast<uint32_t*>(args[2]), static_cast<two::Material*>(args[3])); }
void two_gfx_batch_25(span<void*> args, void*& result) { result = &two::gfx::batch(*static_cast<two::Gnode*>(args[0]), *static_cast<two::Item*>(args[1]), *static_cast<uint16_t*>(args[2])); }
void two_gfx_instances_26(span<void*> args, void*& result) { result = &two::gfx::instances(*static_cast<two::Gnode*>(args[0]), *static_cast<two::Item*>(args[1]), *static_cast<stl::span<two::mat4>*>(args[2])); }
void two_gfx_prefab_27(span<void*> args, void*& result) { UNUSED(result);  two::gfx::prefab(*static_cast<two::Gnode*>(args[0]), *static_cast<two::Prefab*>(args[1]), *static_cast<bool*>(args[2]), *static_cast<uint32_t*>(args[3]), static_cast<two::Material*>(args[4])); }
void two_gfx_model_28(span<void*> args, void*& result) { result = two::gfx::model(*static_cast<two::Gnode*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<uint32_t*>(args[2]), static_cast<two::Material*>(args[3])); }
void two_gfx_animated_29(span<void*> args, void*& result) { result = &two::gfx::animated(*static_cast<two::Gnode*>(args[0]), *static_cast<two::Item*>(args[1])); }
void two_gfx_flows_30(span<void*> args, void*& result) { result = &two::gfx::flows(*static_cast<two::Gnode*>(args[0]), *static_cast<two::Flow*>(args[1]), *static_cast<uint32_t*>(args[2])); }
void two_gfx_light_31(span<void*> args, void*& result) { result = &two::gfx::light(*static_cast<two::Gnode*>(args[0]), *static_cast<two::LightType*>(args[1]), *static_cast<bool*>(args[2]), *static_cast<two::Colour*>(args[3]), *static_cast<float*>(args[4]), *static_cast<float*>(args[5])); }
void two_gfx_sun_light_32(span<void*> args, void*& result) { result = &two::gfx::sun_light(*static_cast<two::Gnode*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2])); }
void two_gfx_radiance_33(span<void*> args, void*& result) { UNUSED(result);  two::gfx::radiance(*static_cast<two::Gnode*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<two::BackgroundMode*>(args[2])); }
void two_gfx_direct_light_node_34(span<void*> args, void*& result) { result = &two::gfx::direct_light_node(*static_cast<two::Gnode*>(args[0]), *static_cast<two::vec3*>(args[1])); }
void two_gfx_solid_material_35(span<void*> args, void*& result) { result = &two::gfx::solid_material(*static_cast<two::GfxSystem*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<two::Colour*>(args[2])); }
void two_gfx_pbr_material_36(span<void*> args, void*& result) { result = &two::gfx::pbr_material(*static_cast<two::GfxSystem*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<two::Colour*>(args[2]), *static_cast<float*>(args[3]), *static_cast<float*>(args[4])); }
void two_gfx_model_suzanne_37(span<void*> args, void*& result) { result = &two::gfx::model_suzanne(*static_cast<two::GfxSystem*>(args[0])); }
void two_pass_clear_fbo_38(span<void*> args, void*& result) { UNUSED(result);  two::pass_clear_fbo(*static_cast<two::GfxSystem*>(args[0]), *static_cast<two::Render*>(args[1]), *static_cast<two::FrameBuffer*>(args[2]), *static_cast<two::Colour*>(args[3]), *static_cast<float*>(args[4])); }
void two_pass_clear_39(span<void*> args, void*& result) { UNUSED(result);  two::pass_clear(*static_cast<two::GfxSystem*>(args[0]), *static_cast<two::Render*>(args[1])); }
void two_pass_gclear_40(span<void*> args, void*& result) { UNUSED(result);  two::pass_gclear(*static_cast<two::GfxSystem*>(args[0]), *static_cast<two::Render*>(args[1])); }
void two_pass_depth_41(span<void*> args, void*& result) { UNUSED(result);  two::pass_depth(*static_cast<two::GfxSystem*>(args[0]), *static_cast<two::Render*>(args[1])); }
void two_pass_background_42(span<void*> args, void*& result) { UNUSED(result);  two::pass_background(*static_cast<two::GfxSystem*>(args[0]), *static_cast<two::Render*>(args[1])); }
void two_pass_solid_43(span<void*> args, void*& result) { UNUSED(result);  two::pass_solid(*static_cast<two::GfxSystem*>(args[0]), *static_cast<two::Render*>(args[1])); }
void two_pass_flip_44(span<void*> args, void*& result) { UNUSED(result);  two::pass_flip(*static_cast<two::GfxSystem*>(args[0]), *static_cast<two::Render*>(args[1])); }
void two_render_minimal_45(span<void*> args, void*& result) { UNUSED(result);  two::render_minimal(*static_cast<two::GfxSystem*>(args[0]), *static_cast<two::Render*>(args[1])); }
void two_render_solid_46(span<void*> args, void*& result) { UNUSED(result);  two::render_solid(*static_cast<two::GfxSystem*>(args[0]), *static_cast<two::Render*>(args[1])); }
void two_render_clear_47(span<void*> args, void*& result) { UNUSED(result);  two::render_clear(*static_cast<two::GfxSystem*>(args[0]), *static_cast<two::Render*>(args[1])); }

namespace two
{
	void two_gfx_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		Type& t = type<two::AnimTarget>();
		static Meta meta = { t, &namspc({ "two" }), "AnimTarget", sizeof(two::AnimTarget), TypeClass::Enum };
		static cstring ids[] = { "Position", "Rotation", "Scale", "Weights", "Count" };
		static uint32_t values[] = { 0, 1, 2, 3, 4 };
		static two::AnimTarget vars[] = { two::AnimTarget::Position, two::AnimTarget::Rotation, two::AnimTarget::Scale, two::AnimTarget::Weights, two::AnimTarget::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_AnimTarget__to_string,
		                           two_AnimTarget__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::Interpolation>();
		static Meta meta = { t, &namspc({ "two" }), "Interpolation", sizeof(two::Interpolation), TypeClass::Enum };
		static cstring ids[] = { "Nearest", "Linear", "Cubic" };
		static uint32_t values[] = { 0, 1, 2 };
		static two::Interpolation vars[] = { two::Interpolation::Nearest, two::Interpolation::Linear, two::Interpolation::Cubic};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_Interpolation__to_string,
		                           two_Interpolation__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::TextureHint>();
		static Meta meta = { t, &namspc({ "two" }), "TextureHint", sizeof(two::TextureHint), TypeClass::Enum };
		static cstring ids[] = { "Black", "White", "Normal" };
		static uint32_t values[] = { 0, 1, 2 };
		static two::TextureHint vars[] = { two::TextureHint::Black, two::TextureHint::White, two::TextureHint::Normal};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_TextureHint__to_string,
		                           two_TextureHint__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::TextureFormat>();
		static Meta meta = { t, &namspc({ "two" }), "TextureFormat", sizeof(two::TextureFormat), TypeClass::Enum };
		static cstring ids[] = { "None", "R8", "R16F", "R32U", "R32F", "RG8", "RG16F", "RG32F", "RGB8", "BGRA8", "RGBA8", "RGB10A2", "RGBA16F", "RGBA32F", "D16", "D24", "D24S8", "D32", "D32F", "Count" };
		static uint32_t values[] = { 26, 29, 36, 39, 40, 41, 48, 52, 53, 58, 59, 74, 66, 70, 77, 78, 79, 80, 83, 84 };
		static two::TextureFormat vars[] = { two::TextureFormat::None, two::TextureFormat::R8, two::TextureFormat::R16F, two::TextureFormat::R32U, two::TextureFormat::R32F, two::TextureFormat::RG8, two::TextureFormat::RG16F, two::TextureFormat::RG32F, two::TextureFormat::RGB8, two::TextureFormat::BGRA8, two::TextureFormat::RGBA8, two::TextureFormat::RGB10A2, two::TextureFormat::RGBA16F, two::TextureFormat::RGBA32F, two::TextureFormat::D16, two::TextureFormat::D24, two::TextureFormat::D24S8, two::TextureFormat::D32, two::TextureFormat::D32F, two::TextureFormat::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7], &vars[8], &vars[9], &vars[10], &vars[11], &vars[12], &vars[13], &vars[14], &vars[15], &vars[16], &vars[17], &vars[18], &vars[19]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_TextureFormat__to_string,
		                           two_TextureFormat__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::ShaderType>();
		static Meta meta = { t, &namspc({ "two" }), "ShaderType", sizeof(two::ShaderType), TypeClass::Enum };
		static cstring ids[] = { "Compute", "Fragment", "Geometry", "Vertex", "Count" };
		static uint32_t values[] = { 0, 1, 2, 3, 4 };
		static two::ShaderType vars[] = { two::ShaderType::Compute, two::ShaderType::Fragment, two::ShaderType::Geometry, two::ShaderType::Vertex, two::ShaderType::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_ShaderType__to_string,
		                           two_ShaderType__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::PassType>();
		static Meta meta = { t, &namspc({ "two" }), "PassType", sizeof(two::PassType), TypeClass::Enum };
		static cstring ids[] = { "VoxelGI", "Lightmap", "Shadowmap", "Probes", "Clear", "Depth", "Normals", "Shadow", "Geometry", "Lights", "Opaque", "Background", "Particles", "Alpha", "Solid", "Effects", "PostProcess", "Flip", "Count" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18 };
		static two::PassType vars[] = { two::PassType::VoxelGI, two::PassType::Lightmap, two::PassType::Shadowmap, two::PassType::Probes, two::PassType::Clear, two::PassType::Depth, two::PassType::Normals, two::PassType::Shadow, two::PassType::Geometry, two::PassType::Lights, two::PassType::Opaque, two::PassType::Background, two::PassType::Particles, two::PassType::Alpha, two::PassType::Solid, two::PassType::Effects, two::PassType::PostProcess, two::PassType::Flip, two::PassType::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7], &vars[8], &vars[9], &vars[10], &vars[11], &vars[12], &vars[13], &vars[14], &vars[15], &vars[16], &vars[17], &vars[18]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_PassType__to_string,
		                           two_PassType__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::MaterialBlock>();
		static Meta meta = { t, &namspc({ "two" }), "MaterialBlock", sizeof(two::MaterialBlock), TypeClass::Enum };
		static cstring ids[] = { "Base", "Alpha", "Solid", "Point", "Line", "Lit", "Pbr", "Phong", "Fresnel", "User", "Count" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		static two::MaterialBlock vars[] = { two::MaterialBlock::Base, two::MaterialBlock::Alpha, two::MaterialBlock::Solid, two::MaterialBlock::Point, two::MaterialBlock::Line, two::MaterialBlock::Lit, two::MaterialBlock::Pbr, two::MaterialBlock::Phong, two::MaterialBlock::Fresnel, two::MaterialBlock::User, two::MaterialBlock::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7], &vars[8], &vars[9], &vars[10]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_MaterialBlock__to_string,
		                           two_MaterialBlock__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::TextureSampler>();
		static Meta meta = { t, &namspc({ "two" }), "TextureSampler", sizeof(two::TextureSampler), TypeClass::Enum };
		static cstring ids[] = { "Source0", "Source1", "Source2", "Source3", "SourceDepth", "Color", "Albedo", "Diffuse", "Alpha", "Metallic", "Specular", "Roughness", "Shininess", "Emissive", "Normal", "AO", "Displace", "Depth", "User0", "User1", "User2", "User3", "User4", "User5", "Radiance", "Shadow", "Lightmap", "ReflectionProbe", "GIProbe", "Skeleton", "Zones", "Materials", "Lights", "Clusters", "LightRecords" };
		static uint32_t values[] = { 0, 1, 2, 3, 3, 0, 0, 0, 1, 2, 2, 3, 3, 4, 5, 6, 7, 7, 12, 13, 14, 15, 6, 7, 10, 11, 12, 13, 14, 15, 0, 8, 9, 13, 14 };
		static two::TextureSampler vars[] = { two::TextureSampler::Source0, two::TextureSampler::Source1, two::TextureSampler::Source2, two::TextureSampler::Source3, two::TextureSampler::SourceDepth, two::TextureSampler::Color, two::TextureSampler::Albedo, two::TextureSampler::Diffuse, two::TextureSampler::Alpha, two::TextureSampler::Metallic, two::TextureSampler::Specular, two::TextureSampler::Roughness, two::TextureSampler::Shininess, two::TextureSampler::Emissive, two::TextureSampler::Normal, two::TextureSampler::AO, two::TextureSampler::Displace, two::TextureSampler::Depth, two::TextureSampler::User0, two::TextureSampler::User1, two::TextureSampler::User2, two::TextureSampler::User3, two::TextureSampler::User4, two::TextureSampler::User5, two::TextureSampler::Radiance, two::TextureSampler::Shadow, two::TextureSampler::Lightmap, two::TextureSampler::ReflectionProbe, two::TextureSampler::GIProbe, two::TextureSampler::Skeleton, two::TextureSampler::Zones, two::TextureSampler::Materials, two::TextureSampler::Lights, two::TextureSampler::Clusters, two::TextureSampler::LightRecords};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7], &vars[8], &vars[9], &vars[10], &vars[11], &vars[12], &vars[13], &vars[14], &vars[15], &vars[16], &vars[17], &vars[18], &vars[19], &vars[20], &vars[21], &vars[22], &vars[23], &vars[24], &vars[25], &vars[26], &vars[27], &vars[28], &vars[29], &vars[30], &vars[31], &vars[32], &vars[33], &vars[34]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_TextureSampler__to_string,
		                           two_TextureSampler__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::Lighting>();
		static Meta meta = { t, &namspc({ "two" }), "Lighting", sizeof(two::Lighting), TypeClass::Enum };
		static cstring ids[] = { "None", "Clustered", "Deferred", "VoxelGI" };
		static uint32_t values[] = { 0, 1, 2, 4 };
		static two::Lighting vars[] = { two::Lighting::None, two::Lighting::Clustered, two::Lighting::Deferred, two::Lighting::VoxelGI};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_Lighting__to_string,
		                           two_Lighting__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::BlendMode>();
		static Meta meta = { t, &namspc({ "two" }), "BlendMode", sizeof(two::BlendMode), TypeClass::Enum };
		static cstring ids[] = { "None", "Mix", "Add", "Sub", "Mul", "Normal", "Alpha" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6 };
		static two::BlendMode vars[] = { two::BlendMode::None, two::BlendMode::Mix, two::BlendMode::Add, two::BlendMode::Sub, two::BlendMode::Mul, two::BlendMode::Normal, two::BlendMode::Alpha};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_BlendMode__to_string,
		                           two_BlendMode__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::CullMode>();
		static Meta meta = { t, &namspc({ "two" }), "CullMode", sizeof(two::CullMode), TypeClass::Enum };
		static cstring ids[] = { "None", "Front", "Back", "Count" };
		static uint32_t values[] = { 0, 1, 2, 3 };
		static two::CullMode vars[] = { two::CullMode::None, two::CullMode::Front, two::CullMode::Back, two::CullMode::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_CullMode__to_string,
		                           two_CullMode__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::DepthDraw>();
		static Meta meta = { t, &namspc({ "two" }), "DepthDraw", sizeof(two::DepthDraw), TypeClass::Enum };
		static cstring ids[] = { "Enabled", "Disabled" };
		static uint32_t values[] = { 0, 1 };
		static two::DepthDraw vars[] = { two::DepthDraw::Enabled, two::DepthDraw::Disabled};
		static void* refs[] = { &vars[0], &vars[1]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_DepthDraw__to_string,
		                           two_DepthDraw__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::DepthTest>();
		static Meta meta = { t, &namspc({ "two" }), "DepthTest", sizeof(two::DepthTest), TypeClass::Enum };
		static cstring ids[] = { "Enabled", "Disabled" };
		static uint32_t values[] = { 0, 1 };
		static two::DepthTest vars[] = { two::DepthTest::Enabled, two::DepthTest::Disabled};
		static void* refs[] = { &vars[0], &vars[1]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_DepthTest__to_string,
		                           two_DepthTest__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::MaterialFlag>();
		static Meta meta = { t, &namspc({ "two" }), "MaterialFlag", sizeof(two::MaterialFlag), TypeClass::Enum };
		static cstring ids[] = { "TriplanarUV1", "TriplanarUV2", "Count" };
		static uint32_t values[] = { 0, 1, 2 };
		static two::MaterialFlag vars[] = { two::MaterialFlag::TriplanarUV1, two::MaterialFlag::TriplanarUV2, two::MaterialFlag::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_MaterialFlag__to_string,
		                           two_MaterialFlag__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::ShaderColor>();
		static Meta meta = { t, &namspc({ "two" }), "ShaderColor", sizeof(two::ShaderColor), TypeClass::Enum };
		static cstring ids[] = { "Shader", "Vertex", "Face" };
		static uint32_t values[] = { 0, 1, 2 };
		static two::ShaderColor vars[] = { two::ShaderColor::Shader, two::ShaderColor::Vertex, two::ShaderColor::Face};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_ShaderColor__to_string,
		                           two_ShaderColor__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::TextureChannel>();
		static Meta meta = { t, &namspc({ "two" }), "TextureChannel", sizeof(two::TextureChannel), TypeClass::Enum };
		static cstring ids[] = { "Red", "Green", "Blue", "Alpha", "All" };
		static uint32_t values[] = { 0, 1, 2, 3, 4 };
		static two::TextureChannel vars[] = { two::TextureChannel::Red, two::TextureChannel::Green, two::TextureChannel::Blue, two::TextureChannel::Alpha, two::TextureChannel::All};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_TextureChannel__to_string,
		                           two_TextureChannel__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::PbrDiffuseMode>();
		static Meta meta = { t, &namspc({ "two" }), "PbrDiffuseMode", sizeof(two::PbrDiffuseMode), TypeClass::Enum };
		static cstring ids[] = { "Lambert", "LambertHalf", "OrenNayar", "Burley", "Toon" };
		static uint32_t values[] = { 0, 1, 2, 3, 4 };
		static two::PbrDiffuseMode vars[] = { two::PbrDiffuseMode::Lambert, two::PbrDiffuseMode::LambertHalf, two::PbrDiffuseMode::OrenNayar, two::PbrDiffuseMode::Burley, two::PbrDiffuseMode::Toon};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_PbrDiffuseMode__to_string,
		                           two_PbrDiffuseMode__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::PbrSpecularMode>();
		static Meta meta = { t, &namspc({ "two" }), "PbrSpecularMode", sizeof(two::PbrSpecularMode), TypeClass::Enum };
		static cstring ids[] = { "SchlickGGX", "Blinn", "Phong", "Toon", "Disabled" };
		static uint32_t values[] = { 0, 1, 2, 3, 4 };
		static two::PbrSpecularMode vars[] = { two::PbrSpecularMode::SchlickGGX, two::PbrSpecularMode::Blinn, two::PbrSpecularMode::Phong, two::PbrSpecularMode::Toon, two::PbrSpecularMode::Disabled};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_PbrSpecularMode__to_string,
		                           two_PbrSpecularMode__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::PhongEnvBlendMode>();
		static Meta meta = { t, &namspc({ "two" }), "PhongEnvBlendMode", sizeof(two::PhongEnvBlendMode), TypeClass::Enum };
		static cstring ids[] = { "Mul", "Mix", "Add" };
		static uint32_t values[] = { 0, 1, 2 };
		static two::PhongEnvBlendMode vars[] = { two::PhongEnvBlendMode::Mul, two::PhongEnvBlendMode::Mix, two::PhongEnvBlendMode::Add};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_PhongEnvBlendMode__to_string,
		                           two_PhongEnvBlendMode__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::EmitterFlow>();
		static Meta meta = { t, &namspc({ "two" }), "EmitterFlow", sizeof(two::EmitterFlow), TypeClass::Enum };
		static cstring ids[] = { "Outward", "Absolute" };
		static uint32_t values[] = { 0, 1 };
		static two::EmitterFlow vars[] = { two::EmitterFlow::Outward, two::EmitterFlow::Absolute};
		static void* refs[] = { &vars[0], &vars[1]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_EmitterFlow__to_string,
		                           two_EmitterFlow__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::ItemShadow>();
		static Meta meta = { t, &namspc({ "two" }), "ItemShadow", sizeof(two::ItemShadow), TypeClass::Enum };
		static cstring ids[] = { "Default", "DoubleSided" };
		static uint32_t values[] = { 0, 1 };
		static two::ItemShadow vars[] = { two::ItemShadow::Default, two::ItemShadow::DoubleSided};
		static void* refs[] = { &vars[0], &vars[1]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_ItemShadow__to_string,
		                           two_ItemShadow__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::ModelFormat>();
		static Meta meta = { t, &namspc({ "two" }), "ModelFormat", sizeof(two::ModelFormat), TypeClass::Enum };
		static cstring ids[] = { "obj", "ply", "gltf", "Count" };
		static uint32_t values[] = { 0, 1, 2, 3 };
		static two::ModelFormat vars[] = { two::ModelFormat::obj, two::ModelFormat::ply, two::ModelFormat::gltf, two::ModelFormat::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_ModelFormat__to_string,
		                           two_ModelFormat__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::IsometricAngle>();
		static Meta meta = { t, &namspc({ "two" }), "IsometricAngle", sizeof(two::IsometricAngle), TypeClass::Enum };
		static cstring ids[] = { "NORTH", "SOUTH", "EAST", "WEST" };
		static uint32_t values[] = { 1, 2, 256, 512 };
		static two::IsometricAngle vars[] = { two::NORTH, two::SOUTH, two::EAST, two::WEST};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, false, ids, values, refs };
		static Convert convert = { two_IsometricAngle__to_string,
		                           two_IsometricAngle__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::DepthMethod>();
		static Meta meta = { t, &namspc({ "two" }), "DepthMethod", sizeof(two::DepthMethod), TypeClass::Enum };
		static cstring ids[] = { "Depth", "DepthPacked", "Distance", "Count" };
		static uint32_t values[] = { 0, 1, 2, 3 };
		static two::DepthMethod vars[] = { two::DepthMethod::Depth, two::DepthMethod::DepthPacked, two::DepthMethod::Distance, two::DepthMethod::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_DepthMethod__to_string,
		                           two_DepthMethod__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::LightType>();
		static Meta meta = { t, &namspc({ "two" }), "LightType", sizeof(two::LightType), TypeClass::Enum };
		static cstring ids[] = { "Direct", "Point", "Spot", "Count" };
		static uint32_t values[] = { 0, 1, 2, 3 };
		static two::LightType vars[] = { two::LightType::Direct, two::LightType::Point, two::LightType::Spot, two::LightType::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_LightType__to_string,
		                           two_LightType__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::ShadowFlags>();
		static Meta meta = { t, &namspc({ "two" }), "ShadowFlags", sizeof(two::ShadowFlags), TypeClass::Enum };
		static cstring ids[] = { "CSM_Stabilize", "CSM_Optimize", "CSM_BlendSplits" };
		static uint32_t values[] = { 1, 2, 4 };
		static two::ShadowFlags vars[] = { two::CSM_Stabilize, two::CSM_Optimize, two::CSM_BlendSplits};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, false, ids, values, refs };
		static Convert convert = { two_ShadowFlags__to_string,
		                           two_ShadowFlags__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::MSAA>();
		static Meta meta = { t, &namspc({ "two" }), "MSAA", sizeof(two::MSAA), TypeClass::Enum };
		static cstring ids[] = { "Disabled", "X2", "X4", "X8", "X16", "Count" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5 };
		static two::MSAA vars[] = { two::MSAA::Disabled, two::MSAA::X2, two::MSAA::X4, two::MSAA::X8, two::MSAA::X16, two::MSAA::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_MSAA__to_string,
		                           two_MSAA__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::Shading>();
		static Meta meta = { t, &namspc({ "two" }), "Shading", sizeof(two::Shading), TypeClass::Enum };
		static cstring ids[] = { "Wireframe", "Solid", "Shaded", "Volume", "Voxels", "Lightmap", "Clear", "Count" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
		static two::Shading vars[] = { two::Shading::Wireframe, two::Shading::Solid, two::Shading::Shaded, two::Shading::Volume, two::Shading::Voxels, two::Shading::Lightmap, two::Shading::Clear, two::Shading::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_Shading__to_string,
		                           two_Shading__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::BackgroundMode>();
		static Meta meta = { t, &namspc({ "two" }), "BackgroundMode", sizeof(two::BackgroundMode), TypeClass::Enum };
		static cstring ids[] = { "None", "Panorama", "Radiance", "Custom" };
		static uint32_t values[] = { 0, 1, 2, 3 };
		static two::BackgroundMode vars[] = { two::BackgroundMode::None, two::BackgroundMode::Panorama, two::BackgroundMode::Radiance, two::BackgroundMode::Custom};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_BackgroundMode__to_string,
		                           two_BackgroundMode__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::Month>();
		static Meta meta = { t, &namspc({ "two" }), "Month", sizeof(two::Month), TypeClass::Enum };
		static cstring ids[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
		static two::Month vars[] = { two::Month::January, two::Month::February, two::Month::March, two::Month::April, two::Month::May, two::Month::June, two::Month::July, two::Month::August, two::Month::September, two::Month::October, two::Month::November, two::Month::December};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7], &vars[8], &vars[9], &vars[10], &vars[11]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_Month__to_string,
		                           two_Month__to_value };
		g_convert[t.m_id] = &convert;
	}
	
	// Sequences
	{
		Type& t = type<stl::span<two::mat4>>();
		static Meta meta = { t, &namspc({ "stl" }), "span<two::mat4>", sizeof(stl::span<two::mat4>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<two::mat4>(),
		                             stl_span_two_mat4__size,
		                             stl_span_two_mat4__at};
		g_iterable[t.m_id] = &iterable;
	}
	{
		Type& t = type<stl::span<two::Node3>>();
		static Meta meta = { t, &namspc({ "stl" }), "span<two::Node3>", sizeof(stl::span<two::Node3>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<two::Node3>(),
		                             stl_span_two_Node3__size,
		                             stl_span_two_Node3__at};
		g_iterable[t.m_id] = &iterable;
	}
	{
		Type& t = type<stl::span<two::Item>>();
		static Meta meta = { t, &namspc({ "stl" }), "span<two::Item>", sizeof(stl::span<two::Item>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<two::Item>(),
		                             stl_span_two_Item__size,
		                             stl_span_two_Item__at};
		g_iterable[t.m_id] = &iterable;
	}
	{
		Type& t = type<stl::span<two::Batch>>();
		static Meta meta = { t, &namspc({ "stl" }), "span<two::Batch>", sizeof(stl::span<two::Batch>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<two::Batch>(),
		                             stl_span_two_Batch__size,
		                             stl_span_two_Batch__at};
		g_iterable[t.m_id] = &iterable;
	}
	{
		Type& t = type<stl::span<two::Direct>>();
		static Meta meta = { t, &namspc({ "stl" }), "span<two::Direct>", sizeof(stl::span<two::Direct>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<two::Direct>(),
		                             stl_span_two_Direct__size,
		                             stl_span_two_Direct__at};
		g_iterable[t.m_id] = &iterable;
	}
	{
		Type& t = type<stl::span<two::Mime>>();
		static Meta meta = { t, &namspc({ "stl" }), "span<two::Mime>", sizeof(stl::span<two::Mime>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<two::Mime>(),
		                             stl_span_two_Mime__size,
		                             stl_span_two_Mime__at};
		g_iterable[t.m_id] = &iterable;
	}
	{
		Type& t = type<stl::span<two::Light>>();
		static Meta meta = { t, &namspc({ "stl" }), "span<two::Light>", sizeof(stl::span<two::Light>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<two::Light>(),
		                             stl_span_two_Light__size,
		                             stl_span_two_Light__at};
		g_iterable[t.m_id] = &iterable;
	}
	{
		Type& t = type<stl::span<two::Flare>>();
		static Meta meta = { t, &namspc({ "stl" }), "span<two::Flare>", sizeof(stl::span<two::Flare>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<two::Flare>(),
		                             stl_span_two_Flare__size,
		                             stl_span_two_Flare__at};
		g_iterable[t.m_id] = &iterable;
	}
	{
		Type& t = type<stl::span<two::Texture*>>();
		static Meta meta = { t, &namspc({ "stl" }), "span<two::Texture*>", sizeof(stl::span<two::Texture*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<two::Texture>(),
		                             stl_span_two_Texture___size,
		                             stl_span_two_Texture___at};
		g_iterable[t.m_id] = &iterable;
	}
	{
		Type& t = type<stl::vector<two::Mesh*>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<two::Mesh*>", sizeof(stl::vector<two::Mesh*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<two::Mesh>(),
		                             stl_vector_two_Mesh___size,
		                             stl_vector_two_Mesh___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_two_Mesh___push,
		                             stl_vector_two_Mesh___add,
		                             stl_vector_two_Mesh___remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<two::Model*>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<two::Model*>", sizeof(stl::vector<two::Model*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<two::Model>(),
		                             stl_vector_two_Model___size,
		                             stl_vector_two_Model___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_two_Model___push,
		                             stl_vector_two_Model___add,
		                             stl_vector_two_Model___remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<two::Texture*>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<two::Texture*>", sizeof(stl::vector<two::Texture*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<two::Texture>(),
		                             stl_vector_two_Texture___size,
		                             stl_vector_two_Texture___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_two_Texture___push,
		                             stl_vector_two_Texture___add,
		                             stl_vector_two_Texture___remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<two::Material*>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<two::Material*>", sizeof(stl::vector<two::Material*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<two::Material>(),
		                             stl_vector_two_Material___size,
		                             stl_vector_two_Material___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_two_Material___push,
		                             stl_vector_two_Material___add,
		                             stl_vector_two_Material___remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<two::Animation*>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<two::Animation*>", sizeof(stl::vector<two::Animation*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<two::Animation>(),
		                             stl_vector_two_Animation___size,
		                             stl_vector_two_Animation___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_two_Animation___push,
		                             stl_vector_two_Animation___add,
		                             stl_vector_two_Animation___remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<two::AnimPlay>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<two::AnimPlay>", sizeof(stl::vector<two::AnimPlay>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<two::AnimPlay>(),
		                             stl_vector_two_AnimPlay__size,
		                             stl_vector_two_AnimPlay__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_two_AnimPlay__push,
		                             stl_vector_two_AnimPlay__add,
		                             stl_vector_two_AnimPlay__remove };
		g_sequence[t.m_id] = &sequence;
	}
	
	// two::Node3
	{
		Type& t = type<two::Node3>();
		static Meta meta = { t, &namspc({ "two" }), "Node3", sizeof(two::Node3), TypeClass::Object };
		// bases
		// defaults
		static two::mat4 transform_default = bxidentity();
		static two::quat construct_1_rotation_default = ZeroQuat;
		static two::vec3 construct_1_scale_default = vec3(1.f);
		static two::quat apply_0_rotation_default = ZeroQuat;
		static two::vec3 apply_0_scale_default = vec3(1.f);
		static two::quat derive_0_rotation_default = ZeroQuat;
		static two::vec3 derive_0_scale_default = vec3(1.f);
		// constructors
		static Constructor constructors[] = {
			{ t, two_Node3__construct_0, {} },
			{ t, two_Node3__construct_1, { { "position", type<two::vec3>(),  }, { "rotation", type<two::quat>(), Param::Default, &construct_1_rotation_default }, { "scale", type<two::vec3>(), Param::Default, &construct_1_scale_default } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::Node3, m_parent), type<uint32_t>(), "parent", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Node3, m_transform), type<two::mat4>(), "transform", &transform_default, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "apply", Address(), two_Node3_apply, { { "position", type<two::vec3>(),  }, { "rotation", type<two::quat>(), Param::Default, &apply_0_rotation_default }, { "scale", type<two::vec3>(), Param::Default, &apply_0_scale_default } }, g_qvoid },
			{ t, "derive", Address(), two_Node3_derive, { { "parent", type<two::Node3>(),  }, { "position", type<two::vec3>(),  }, { "rotation", type<two::quat>(), Param::Default, &derive_0_rotation_default }, { "scale", type<two::vec3>(), Param::Default, &derive_0_scale_default } }, g_qvoid },
			{ t, "position", Address(), two_Node3_position, {}, { &type<two::vec3>(), QualType::None } },
			{ t, "axis", Address(), two_Node3_axis, { { "dir", type<two::vec3>(),  } }, { &type<two::vec3>(), QualType::None } },
			{ t, "direction", Address(), two_Node3_direction, {}, { &type<two::vec3>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, members, methods, {}, };
	}
	// two::AnimTrack
	{
		Type& t = type<two::AnimTrack>();
		static Meta meta = { t, &namspc({ "two" }), "AnimTrack", sizeof(two::AnimTrack), TypeClass::Object };
		// bases
		// defaults
		static two::Type* value_type_default = nullptr;
		static float length_default = 0.f;
		static two::Interpolation interpolation_default = two::Interpolation::Linear;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::AnimTrack, m_animation), type<two::Animation>(), "animation", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::AnimTrack, m_node), type<size_t>(), "node", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::AnimTrack, m_node_name), type<stl::string>(), "node_name", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::AnimTrack, m_target), type<two::AnimTarget>(), "target", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::AnimTrack, m_value_type), type<two::Type>(), "value_type", value_type_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::AnimTrack, m_length), type<float>(), "length", &length_default, Member::Value, nullptr },
			{ t, offsetof(two::AnimTrack, m_interpolation), type<two::Interpolation>(), "interpolation", &interpolation_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// two::Animation
	{
		Type& t = type<two::Animation>();
		static Meta meta = { t, &namspc({ "two" }), "Animation", sizeof(two::Animation), TypeClass::Object };
		// bases
		// defaults
		static float length_default = 1.f;
		static float step_default = 0.1f;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::Animation, m_name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Animation, m_length), type<float>(), "length", &length_default, Member::Value, nullptr },
			{ t, offsetof(two::Animation, m_step), type<float>(), "step", &step_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// two::Texture
	{
		Type& t = type<two::Texture>();
		static Meta meta = { t, &namspc({ "two" }), "Texture", sizeof(two::Texture), TypeClass::Object };
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
		static stl::string construct_0_name_default = "";
		static uint64_t construct_1_flags_default = 0U;
		static bool construct_1_cube_default = false;
		static bool load_0_srgb_default = false;
		static bool load_0_mips_default = false;
		static bool reload_0_srgb_default = false;
		static bool reload_0_mips_default = false;
		static bool load_rgba_0_ref_default = false;
		static bool load_float_0_ref_default = false;
		// constructors
		static Constructor constructors[] = {
			{ t, two_Texture__construct_0, { { "name", type<stl::string>(), Param::Default, &construct_0_name_default } } },
			{ t, two_Texture__construct_1, { { "size", type<two::uvec2>(),  }, { "mips", type<bool>(),  }, { "format", type<two::TextureFormat>(),  }, { "flags", type<uint64_t>(), Param::Default, &construct_1_flags_default }, { "cube", type<bool>(), Param::Default, &construct_1_cube_default } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::Texture, m_name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Texture, m_location), type<stl::string>(), "location", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Texture, m_format), type<two::TextureFormat>(), "format", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Texture, m_size), type<two::uvec2>(), "size", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Texture, m_depth), type<uint16_t>(), "depth", &depth_default, Member::Value, nullptr },
			{ t, offsetof(two::Texture, m_memsize), type<uint32_t>(), "memsize", &memsize_default, Member::Value, nullptr },
			{ t, offsetof(two::Texture, m_bits_per_pixel), type<uint32_t>(), "bits_per_pixel", &bits_per_pixel_default, Member::Value, nullptr },
			{ t, offsetof(two::Texture, m_is_depth), type<bool>(), "is_depth", &is_depth_default, Member::Value, nullptr },
			{ t, offsetof(two::Texture, m_is_depth_packed), type<bool>(), "is_depth_packed", &is_depth_packed_default, Member::Value, nullptr },
			{ t, offsetof(two::Texture, m_is_array), type<bool>(), "is_array", &is_array_default, Member::Value, nullptr },
			{ t, offsetof(two::Texture, m_is_cube), type<bool>(), "is_cube", &is_cube_default, Member::Value, nullptr },
			{ t, offsetof(two::Texture, m_is_fbo), type<bool>(), "is_fbo", &is_fbo_default, Member::Value, nullptr },
			{ t, offsetof(two::Texture, m_mips), type<bool>(), "mips", &mips_default, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "valid", Address(), two_Texture_valid, {}, { &type<bool>(), QualType::None } },
			{ t, "load", Address(), two_Texture_load, { { "gfx", type<two::GfxSystem>(),  }, { "path", type<stl::string>(),  }, { "srgb", type<bool>(), Param::Default, &load_0_srgb_default }, { "mips", type<bool>(), Param::Default, &load_0_mips_default } }, g_qvoid },
			{ t, "reload", Address(), two_Texture_reload, { { "gfx", type<two::GfxSystem>(),  }, { "srgb", type<bool>(), Param::Default, &reload_0_srgb_default }, { "mips", type<bool>(), Param::Default, &reload_0_mips_default } }, g_qvoid },
			{ t, "load_mem", Address(), two_Texture_load_mem, { { "gfx", type<two::GfxSystem>(),  }, { "data", type<stl::span<uint8_t>>(),  } }, g_qvoid },
			{ t, "load_rgba", Address(), two_Texture_load_rgba, { { "size", type<two::uvec2>(),  }, { "data", type<stl::span<uint32_t>>(),  }, { "ref", type<bool>(), Param::Default, &load_rgba_0_ref_default } }, g_qvoid },
			{ t, "load_float", Address(), two_Texture_load_float, { { "size", type<two::uvec2>(),  }, { "data", type<stl::span<float>>(),  }, { "ref", type<bool>(), Param::Default, &load_float_0_ref_default } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, members, methods, {}, };
	}
	// two::Skeleton
	{
		Type& t = type<two::Skeleton>();
		static Meta meta = { t, &namspc({ "two" }), "Skeleton", sizeof(two::Skeleton), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::Joint
	{
		Type& t = type<two::Joint>();
		static Meta meta = { t, &namspc({ "two" }), "Joint", sizeof(two::Joint), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Joint__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Joint__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// two::Skin
	{
		Type& t = type<two::Skin>();
		static Meta meta = { t, &namspc({ "two" }), "Skin", sizeof(two::Skin), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::Rig
	{
		Type& t = type<two::Rig>();
		static Meta meta = { t, &namspc({ "two" }), "Rig", sizeof(two::Rig), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::AnimNode
	{
		Type& t = type<two::AnimNode>();
		static Meta meta = { t, &namspc({ "two" }), "AnimNode", sizeof(two::AnimNode), TypeClass::Struct };
		// bases
		// defaults
		static two::quat rotation_default = ZeroQuat;
		// constructors
		static Constructor constructors[] = {
			{ t, two_AnimNode__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_AnimNode__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::AnimNode, m_position), type<two::vec3>(), "position", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::AnimNode, m_rotation), type<two::quat>(), "rotation", &rotation_default, Member::Value, nullptr },
			{ t, offsetof(two::AnimNode, m_scale), type<two::vec3>(), "scale", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::AnimNode, m_transform), type<two::mat4>(), "transform", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::AnimPlay
	{
		Type& t = type<two::AnimPlay>();
		static Meta meta = { t, &namspc({ "two" }), "AnimPlay", sizeof(two::AnimPlay), TypeClass::Struct };
		// bases
		// defaults
		static const two::Animation* animation_default = nullptr;
		static bool loop_default = true;
		static float speed_default = 1.f;
		static bool transient_default = false;
		static float fadeout_default = 0.f;
		static float fadeout_left_default = 0.f;
		static float cursor_default = 0.f;
		static bool ended_default = false;
		// constructors
		static Constructor constructors[] = {
			{ t, two_AnimPlay__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_AnimPlay__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::AnimPlay, m_animation), type<two::Animation>(), "animation", animation_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::AnimPlay, m_loop), type<bool>(), "loop", &loop_default, Member::Value, nullptr },
			{ t, offsetof(two::AnimPlay, m_speed), type<float>(), "speed", &speed_default, Member::Value, nullptr },
			{ t, offsetof(two::AnimPlay, m_transient), type<bool>(), "transient", &transient_default, Member::Value, nullptr },
			{ t, offsetof(two::AnimPlay, m_fadeout), type<float>(), "fadeout", &fadeout_default, Member::Value, nullptr },
			{ t, offsetof(two::AnimPlay, m_fadeout_left), type<float>(), "fadeout_left", &fadeout_left_default, Member::Value, nullptr },
			{ t, offsetof(two::AnimPlay, m_cursor), type<float>(), "cursor", &cursor_default, Member::Value, nullptr },
			{ t, offsetof(two::AnimPlay, m_ended), type<bool>(), "ended", &ended_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Mime
	{
		Type& t = type<two::Mime>();
		static Meta meta = { t, &namspc({ "two" }), "Mime", sizeof(two::Mime), TypeClass::Object };
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
		static Constructor constructors[] = {
			{ t, two_Mime__construct_0, {} }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::Mime, m_playing), type<stl::vector<two::AnimPlay>>(), "playing", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::Mime, m_queue), type<stl::vector<two::Animation*>>(), "queue", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::Mime, m_active), type<bool>(), "active", &active_default, Member::Value, nullptr },
			{ t, offsetof(two::Mime, m_speed_scale), type<float>(), "speed_scale", &speed_scale_default, Member::Value, nullptr },
			{ t, offsetof(two::Mime, m_default_blend_time), type<float>(), "default_blend_time", &default_blend_time_default, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "start", Address(), two_Mime_start, { { "animation", type<stl::string>(),  }, { "loop", type<bool>(),  }, { "blend", type<float>(), Param::Default, &start_0_blend_default }, { "speed", type<float>(), Param::Default, &start_0_speed_default }, { "transient", type<bool>(), Param::Default, &start_0_transient_default } }, g_qvoid },
			{ t, "play", Address(), two_Mime_play, { { "animation", type<two::Animation>(),  }, { "loop", type<bool>(),  }, { "blend", type<float>(), Param::Default, &play_0_blend_default }, { "speed", type<float>(), Param::Default, &play_0_speed_default }, { "transient", type<bool>(), Param::Default, &play_0_transient_default } }, g_qvoid },
			{ t, "seek", Address(), two_Mime_seek, { { "time", type<float>(),  } }, g_qvoid },
			{ t, "pause", Address(), two_Mime_pause, {}, g_qvoid },
			{ t, "stop", Address(), two_Mime_stop, {}, g_qvoid },
			{ t, "advance", Address(), two_Mime_advance, { { "time", type<float>(),  } }, g_qvoid },
			{ t, "next_animation", Address(), two_Mime_next_animation, {}, g_qvoid },
			{ t, "add_item", Address(), two_Mime_add_item, { { "item", type<two::Item>(),  } }, g_qvoid },
			{ t, "add_nodes", Address(), two_Mime_add_nodes, { { "nodes", type<stl::span<two::Node3>>(),  } }, g_qvoid },
			{ t, "playing", Address(), two_Mime_playing, {}, { &type<stl::string>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, members, methods, {}, };
	}
	// two::Frustum
	{
		Type& t = type<two::Frustum>();
		static Meta meta = { t, &namspc({ "two" }), "Frustum", sizeof(two::Frustum), TypeClass::Object };
		// bases
		// defaults
		static float fov_default = 60.f;
		static float aspect_default = 1.f;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::Frustum, m_fov), type<float>(), "fov", &fov_default, Member::Value, nullptr },
			{ t, offsetof(two::Frustum, m_aspect), type<float>(), "aspect", &aspect_default, Member::Value, nullptr },
			{ t, offsetof(two::Frustum, m_near), type<float>(), "near", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Frustum, m_far), type<float>(), "far", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Frustum, m_center), type<two::vec3>(), "center", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Frustum, m_radius), type<float>(), "radius", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// two::FrustumSlice
	{
		Type& t = type<two::FrustumSlice>();
		static Meta meta = { t, &namspc({ "two" }), "FrustumSlice", sizeof(two::FrustumSlice), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_FrustumSlice__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_FrustumSlice__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// two::ShaderDefine
	{
		Type& t = type<two::ShaderDefine>();
		static Meta meta = { t, &namspc({ "two" }), "ShaderDefine", sizeof(two::ShaderDefine), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_ShaderDefine__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_ShaderDefine__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::ShaderDefine, m_name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::ShaderDefine, m_value), type<stl::string>(), "value", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::ShaderBlock
	{
		Type& t = type<two::ShaderBlock>();
		static Meta meta = { t, &namspc({ "two" }), "ShaderBlock", sizeof(two::ShaderBlock), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_ShaderBlock__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_ShaderBlock__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::ShaderBlock, m_index), type<uint8_t>(), "index", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::ShaderBlock, m_options), type<stl::vector<stl::string>>(), "options", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::ShaderBlock, m_modes), type<stl::vector<stl::string>>(), "modes", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "add_option", Address(), two_ShaderBlock_add_option, { { "name", type<stl::string>(),  } }, g_qvoid },
			{ t, "add_mode", Address(), two_ShaderBlock_add_mode, { { "name", type<stl::string>(),  } }, g_qvoid },
			{ t, "add_define", Address(), two_ShaderBlock_add_define, { { "name", type<stl::string>(),  }, { "value", type<stl::string>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, methods, {}, };
	}
	// two::ProgramMode
	{
		Type& t = type<two::ProgramMode>();
		static Meta meta = { t, &namspc({ "two" }), "ProgramMode", sizeof(two::ProgramMode), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_ProgramMode__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_ProgramMode__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::ProgramMode, name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::ProgramMode, size), type<uint32_t>(), "size", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::ProgramMode, shift), type<uint32_t>(), "shift", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::ProgramMode, mask), type<uint32_t>(), "mask", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::ProgramBlock
	{
		Type& t = type<two::ProgramBlock>();
		static Meta meta = { t, &namspc({ "two" }), "ProgramBlock", sizeof(two::ProgramBlock), TypeClass::Struct };
		// bases
		// defaults
		static bool enabled_default = false;
		static uint8_t option_shift_default = 0;
		static uint8_t mode_shift_default = 0;
		// constructors
		static Constructor constructors[] = {
			{ t, two_ProgramBlock__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_ProgramBlock__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::ProgramBlock, m_enabled), type<bool>(), "enabled", &enabled_default, Member::Value, nullptr },
			{ t, offsetof(two::ProgramBlock, m_option_shift), type<uint8_t>(), "option_shift", &option_shift_default, Member::Value, nullptr },
			{ t, offsetof(two::ProgramBlock, m_mode_shift), type<uint8_t>(), "mode_shift", &mode_shift_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Program
	{
		Type& t = type<two::Program>();
		static Meta meta = { t, &namspc({ "two" }), "Program", sizeof(two::Program), TypeClass::Object };
		// bases
		// defaults
		static bool set_block_0_enabled_default = true;
		static bool set_pass_0_enabled_default = true;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::Program, m_name), type<stl::string>(), "name", nullptr, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "set_block", Address(), two_Program_set_block, { { "block", type<two::MaterialBlock>(),  }, { "enabled", type<bool>(), Param::Default, &set_block_0_enabled_default } }, g_qvoid },
			{ t, "set_pass", Address(), two_Program_set_pass, { { "type", type<two::PassType>(),  }, { "enabled", type<bool>(), Param::Default, &set_pass_0_enabled_default } }, g_qvoid },
			{ t, "set_source", Address(), two_Program_set_source, { { "type", type<two::ShaderType>(),  }, { "source", type<stl::string>(),  } }, g_qvoid },
			{ t, "register_blocks", Address(), two_Program_register_blocks, { { "program", type<two::Program>(),  } }, g_qvoid },
			{ t, "register_block", Address(), two_Program_register_block, { { "block", type<two::ShaderBlock>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, methods, {}, };
	}
	// two::ProgramVersion
	{
		Type& t = type<two::ProgramVersion>();
		static Meta meta = { t, &namspc({ "two" }), "ProgramVersion", sizeof(two::ProgramVersion), TypeClass::Struct };
		// bases
		// defaults
		static bool set_option_0_active_default = true;
		// constructors
		static Constructor constructors[] = {
			{ t, two_ProgramVersion__construct_0, {} },
			{ t, two_ProgramVersion__construct_1, { { "program", type<two::Program>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_ProgramVersion__copy_construct }
		};
		// members
		// methods
		static Method methods[] = {
			{ t, "clear", Address(), two_ProgramVersion_clear, {}, g_qvoid },
			{ t, "set_option", Address(), two_ProgramVersion_set_option, { { "block", type<uint8_t>(),  }, { "option", type<uint8_t>(),  }, { "active", type<bool>(), Param::Default, &set_option_0_active_default } }, g_qvoid },
			{ t, "set_mode", Address(), two_ProgramVersion_set_mode, { { "block", type<uint8_t>(),  }, { "mode", type<uint8_t>(),  }, { "value", type<uint8_t>(),  } }, g_qvoid },
			{ t, "hash", Address(), two_ProgramVersion_hash, {}, { &type<uint64_t>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, methods, {}, };
	}
	// two::Shot
	{
		Type& t = type<two::Shot>();
		static Meta meta = { t, &namspc({ "two" }), "Shot", sizeof(two::Shot), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::Pass
	{
		Type& t = type<two::Pass>();
		static Meta meta = { t, &namspc({ "two" }), "Pass", sizeof(two::Pass), TypeClass::Struct };
		// bases
		// defaults
		static two::RenderTarget* target_default = nullptr;
		static two::FrameBuffer* fbo_default = nullptr;
		static two::Viewport* viewport_default = nullptr;
		static uint64_t bgfx_state_default = 0;
		static bool use_mrt_default = false;
		static uint8_t index_default = 0;
		// constructors
		static Constructor constructors[] = {
			{ t, two_Pass__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Pass__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Pass, m_name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Pass, m_target), type<two::RenderTarget>(), "target", target_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::Pass, m_fbo), type<two::FrameBuffer>(), "fbo", fbo_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::Pass, m_viewport), type<two::Viewport>(), "viewport", viewport_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::Pass, m_rect), type<two::vec4>(), "rect", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Pass, m_bgfx_state), type<uint64_t>(), "bgfx_state", &bgfx_state_default, Member::Value, nullptr },
			{ t, offsetof(two::Pass, m_pass_type), type<two::PassType>(), "pass_type", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Pass, m_use_mrt), type<bool>(), "use_mrt", &use_mrt_default, Member::Value, nullptr },
			{ t, offsetof(two::Pass, m_index), type<uint8_t>(), "index", &index_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::RenderFrame
	{
		Type& t = type<two::RenderFrame>();
		static Meta meta = { t, &namspc({ "two" }), "RenderFrame", sizeof(two::RenderFrame), TypeClass::Struct };
		// bases
		// defaults
		static uint32_t nudraw_calls_default = 0;
		static uint32_t nuvertices_default = 0;
		static uint32_t nutriangles_default = 0;
		// constructors
		static Constructor constructors[] = {
			{ t, two_RenderFrame__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_RenderFrame__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::RenderFrame, m_frame), type<uint32_t>(), "frame", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::RenderFrame, m_time), type<float>(), "time", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::RenderFrame, m_delta_time), type<float>(), "delta_time", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::RenderFrame, m_render_pass), type<uint8_t>(), "render_pass", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::RenderFrame, m_num_draw_calls), type<uint32_t>(), "nudraw_calls", &nudraw_calls_default, Member::Value, nullptr },
			{ t, offsetof(two::RenderFrame, m_num_vertices), type<uint32_t>(), "nuvertices", &nuvertices_default, Member::Value, nullptr },
			{ t, offsetof(two::RenderFrame, m_num_triangles), type<uint32_t>(), "nutriangles", &nutriangles_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Render
	{
		Type& t = type<two::Render>();
		static Meta meta = { t, &namspc({ "two" }), "Render", sizeof(two::Render), TypeClass::Struct };
		// bases
		// defaults
		static two::Zone* env_default = nullptr;
		static two::Lighting lighting_default = two::Lighting::None;
		static bool vflip_default = false;
		static bool needs_mrt_default = false;
		static bool is_mrt_default = false;
		static uint8_t pass_index_default = two::Render::s_render_pass_id;
		static uint8_t next_pass_0_index_default = UINT8_MAX;
		// constructors
		static Constructor constructors[] = {
			{ t, two_Render__construct_0, {} },
			{ t, two_Render__construct_1, { { "shading", type<two::Shading>(),  }, { "viewport", type<two::Viewport>(),  }, { "target", type<two::RenderTarget>(),  }, { "frame", type<two::RenderFrame>(),  } } },
			{ t, two_Render__construct_2, { { "shading", type<two::Shading>(),  }, { "viewport", type<two::Viewport>(),  }, { "target", type<two::RenderTarget>(),  }, { "target_fbo", type<two::FrameBuffer>(),  }, { "frame", type<two::RenderFrame>(),  } } }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Render, m_shading), type<two::Shading>(), "shading", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Render, m_scene), type<two::Scene>(), "scene", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::Render, m_target), type<two::RenderTarget>(), "target", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::Render, m_fbo), type<two::FrameBuffer>(), "fbo", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::Render, m_viewport), type<two::Viewport>(), "viewport", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::Render, m_rect), type<two::vec4>(), "rect", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Render, m_camera), type<two::Camera>(), "camera", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::Render, m_frame), type<two::RenderFrame>(), "frame", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::Render, m_frustum), type<two::Frustum>(), "frustum", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::Render, m_env), type<two::Zone>(), "env", env_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::Render, m_lighting), type<two::Lighting>(), "lighting", &lighting_default, Member::Value, nullptr },
			{ t, offsetof(two::Render, m_vflip), type<bool>(), "vflip", &vflip_default, Member::Value, nullptr },
			{ t, offsetof(two::Render, m_needs_mrt), type<bool>(), "needs_mrt", &needs_mrt_default, Member::Value, nullptr },
			{ t, offsetof(two::Render, m_is_mrt), type<bool>(), "is_mrt", &is_mrt_default, Member::Value, nullptr },
			{ t, offsetof(two::Render, m_pass_index), type<uint8_t>(), "pass_index", &pass_index_default, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "subrender", Address(), two_Render_subrender, { { "render", type<two::Render>(),  } }, g_qvoid },
			{ t, "next_pass", Address(), two_Render_next_pass, { { "name", type<const char*>(), Param::Nullable }, { "type", type<two::PassType>(),  }, { "index", type<uint8_t>(), Param::Default, &next_pass_0_index_default } }, { &type<two::Pass>(), QualType::None } },
			{ t, "composite_pass", Address(), two_Render_composite_pass, { { "name", type<const char*>(), Param::Nullable }, { "fbo", type<two::FrameBuffer>(),  }, { "rect", type<two::vec4>(),  } }, { &type<two::Pass>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, members, methods, {}, };
	}
	// two::GfxBlock
	{
		Type& t = type<two::GfxBlock>();
		static Meta meta = { t, &namspc({ "two" }), "GfxBlock", sizeof(two::GfxBlock), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::ShaderBlock>() };
		static size_t bases_offsets[] = { base_offset<two::GfxBlock, two::ShaderBlock>() };
		// defaults
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, SIZE_MAX, type<two::Type>(), "type", nullptr, Member::Flags(Member::NonMutable|Member::Link), two_GfxBlock__get_type }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, members, {}, {}, };
	}
	// two::DrawBlock
	{
		Type& t = type<two::DrawBlock>();
		static Meta meta = { t, &namspc({ "two" }), "DrawBlock", sizeof(two::DrawBlock), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::GfxBlock>() };
		static size_t bases_offsets[] = { base_offset<two::DrawBlock, two::GfxBlock>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::Renderer
	{
		Type& t = type<two::Renderer>();
		static Meta meta = { t, &namspc({ "two" }), "Renderer", sizeof(two::Renderer), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "gather", Address(), two_Renderer_gather, { { "render", type<two::Render>(),  } }, g_qvoid },
			{ t, "begin", Address(), two_Renderer_begin, { { "render", type<two::Render>(),  } }, g_qvoid },
			{ t, "end", Address(), two_Renderer_end, { { "render", type<two::Render>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, methods, {}, };
	}
	// two::GfxWindow
	{
		Type& t = type<two::GfxWindow>();
		static Meta meta = { t, &namspc({ "two" }), "GfxWindow", sizeof(two::GfxWindow), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::GfxSystem
	{
		Type& t = type<two::GfxSystem>();
		static Meta meta = { t, &namspc({ "two" }), "GfxSystem", sizeof(two::GfxSystem), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::BgfxSystem>() };
		static size_t bases_offsets[] = { base_offset<two::GfxSystem, two::BgfxSystem>() };
		// defaults
		static two::BlockCopy* copy_default = nullptr;
		static two::BlockFilter* filter_default = nullptr;
		static bool flip_y_default = false;
		static bool add_resource_path_0_relative_default = true;
		static bool create_model_geo_0_readback_default = false;
		static bool create_model_geo_0_optimize_default = false;
		static bool create_model_gpu_0_readback_default = false;
		static bool create_model_gpu_0_optimize_default = false;
		static bool fetch_material_0_builtin_default = true;
		static two::Symbol shape_0_symbol_default = {};
		static two::DrawMode shape_0_draw_mode_default = PLAIN;
		static two::DrawMode symbol_material_0_draw_mode_default = PLAIN;
		// constructors
		static Constructor constructors[] = {
			{ t, two_GfxSystem__construct_0, { { "resource_path", type<stl::string>(),  } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::GfxSystem, m_renderer), type<two::Renderer>(), "renderer", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::GfxSystem, m_copy), type<two::BlockCopy>(), "copy", copy_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::GfxSystem, m_filter), type<two::BlockFilter>(), "filter", filter_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::GfxSystem, m_flip_y), type<bool>(), "flip_y", &flip_y_default, Member::Value, nullptr },
			{ t, offsetof(two::GfxSystem, m_render_frame), type<two::RenderFrame>(), "render_frame", nullptr, Member::Value, nullptr },
			{ t, SIZE_MAX, type<two::AssetStore<two::Texture>>(), "textures", nullptr, Member::Flags(Member::NonMutable|Member::Link), two_GfxSystem__get_textures },
			{ t, SIZE_MAX, type<two::AssetStore<two::Program>>(), "programs", nullptr, Member::Flags(Member::NonMutable|Member::Link), two_GfxSystem__get_programs },
			{ t, SIZE_MAX, type<two::AssetStore<two::Material>>(), "materials", nullptr, Member::Flags(Member::NonMutable|Member::Link), two_GfxSystem__get_materials },
			{ t, SIZE_MAX, type<two::AssetStore<two::Model>>(), "models", nullptr, Member::Flags(Member::NonMutable|Member::Link), two_GfxSystem__get_models },
			{ t, SIZE_MAX, type<two::AssetStore<two::Flow>>(), "flows", nullptr, Member::Flags(Member::NonMutable|Member::Link), two_GfxSystem__get_flows },
			{ t, SIZE_MAX, type<two::AssetStore<two::Prefab>>(), "prefabs", nullptr, Member::Flags(Member::NonMutable|Member::Link), two_GfxSystem__get_prefabs }
		};
		// methods
		static Method methods[] = {
			{ t, "main_target", Address(), two_GfxSystem_main_target, {}, { &type<two::RenderTarget>(), QualType::None } },
			{ t, "default_pipeline", Address(), two_GfxSystem_default_pipeline, {}, g_qvoid },
			{ t, "add_resource_path", Address(), two_GfxSystem_add_resource_path, { { "path", type<stl::string>(),  }, { "relative", type<bool>(), Param::Default, &add_resource_path_0_relative_default } }, g_qvoid },
			{ t, "debug_material", Address(), two_GfxSystem_debug_material, {}, { &type<two::Material>(), QualType::None } },
			{ t, "create_model", Address(), two_GfxSystem_create_model, { { "name", type<stl::string>(),  } }, { &type<two::Model>(), QualType::None } },
			{ t, "create_model_geo", Address(), two_GfxSystem_create_model_geo, { { "name", type<stl::string>(),  }, { "geometry", type<two::MeshPacker>(),  }, { "readback", type<bool>(), Param::Default, &create_model_geo_0_readback_default }, { "optimize", type<bool>(), Param::Default, &create_model_geo_0_optimize_default } }, { &type<two::Model>(), QualType::None } },
			{ t, "create_model_gpu", Address(), two_GfxSystem_create_model_gpu, { { "name", type<stl::string>(),  }, { "gpu_mesh", type<two::GpuMesh>(),  }, { "readback", type<bool>(), Param::Default, &create_model_gpu_0_readback_default }, { "optimize", type<bool>(), Param::Default, &create_model_gpu_0_optimize_default } }, { &type<two::Model>(), QualType::None } },
			{ t, "fetch_material", Address(), two_GfxSystem_fetch_material, { { "name", type<stl::string>(),  }, { "shader", type<stl::string>(),  }, { "builtin", type<bool>(), Param::Default, &fetch_material_0_builtin_default } }, { &type<two::Material>(), QualType::None } },
			{ t, "fetch_image256_material", Address(), two_GfxSystem_fetch_image256_material, { { "image", type<two::Image256>(),  } }, { &type<two::Material>(), QualType::None } },
			{ t, "shape", Address(), two_GfxSystem_shape, { { "shape", type<two::Shape>(),  }, { "symbol", type<two::Symbol>(), Param::Default, &shape_0_symbol_default }, { "draw_mode", type<two::DrawMode>(), Param::Default, &shape_0_draw_mode_default } }, { &type<two::Model>(), QualType::None } },
			{ t, "symbol_material", Address(), two_GfxSystem_symbol_material, { { "symbol", type<two::Symbol>(),  }, { "draw_mode", type<two::DrawMode>(), Param::Default, &symbol_material_0_draw_mode_default } }, { &type<two::Material>(), QualType::None } }
		};
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, {}, members, methods, {}, };
	}
	// two::MaterialParam<two::Colour>
	{
		Type& t = type<two::MaterialParam<two::Colour>>();
		static Meta meta = { t, &namspc({ "two" }), "MaterialParam<two::Colour>", sizeof(two::MaterialParam<two::Colour>), TypeClass::Struct };
		// bases
		// defaults
		static two::Texture* texture_default = nullptr;
		static two::TextureChannel channel_default = two::TextureChannel::All;
		// constructors
		static Constructor constructors[] = {
			{ t, two_MaterialParam_two_Colour__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_MaterialParam_two_Colour__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::MaterialParam<two::Colour>, m_value), type<two::Colour>(), "value", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::MaterialParam<two::Colour>, m_texture), type<two::Texture>(), "texture", texture_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::MaterialParam<two::Colour>, m_channel), type<two::TextureChannel>(), "channel", &channel_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::MaterialParam<float>
	{
		Type& t = type<two::MaterialParam<float>>();
		static Meta meta = { t, &namspc({ "two" }), "MaterialParam<float>", sizeof(two::MaterialParam<float>), TypeClass::Struct };
		// bases
		// defaults
		static two::Texture* texture_default = nullptr;
		static two::TextureChannel channel_default = two::TextureChannel::All;
		// constructors
		static Constructor constructors[] = {
			{ t, two_MaterialParam_float__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_MaterialParam_float__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::MaterialParam<float>, m_value), type<float>(), "value", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::MaterialParam<float>, m_texture), type<two::Texture>(), "texture", texture_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::MaterialParam<float>, m_channel), type<two::TextureChannel>(), "channel", &channel_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::MaterialParam<two::vec4>
	{
		Type& t = type<two::MaterialParam<two::vec4>>();
		static Meta meta = { t, &namspc({ "two" }), "MaterialParam<two::vec4>", sizeof(two::MaterialParam<two::vec4>), TypeClass::Struct };
		// bases
		// defaults
		static two::Texture* texture_default = nullptr;
		static two::TextureChannel channel_default = two::TextureChannel::All;
		// constructors
		static Constructor constructors[] = {
			{ t, two_MaterialParam_two_vec4__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_MaterialParam_two_vec4__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::MaterialParam<two::vec4>, m_value), type<two::vec4>(), "value", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::MaterialParam<two::vec4>, m_texture), type<two::Texture>(), "texture", texture_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::MaterialParam<two::vec4>, m_channel), type<two::TextureChannel>(), "channel", &channel_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::MaterialBase
	{
		Type& t = type<two::MaterialBase>();
		static Meta meta = { t, &namspc({ "two" }), "MaterialBase", sizeof(two::MaterialBase), TypeClass::Struct };
		// bases
		// defaults
		static two::BlendMode blend_mode_default = two::BlendMode::None;
		static two::CullMode cull_mode_default = two::CullMode::Back;
		static two::DepthDraw depth_draw_default = two::DepthDraw::Enabled;
		static two::DepthTest depth_test_default = two::DepthTest::Enabled;
		static two::vec2 uv0_scale_default = {1.f,1.f};
		static two::vec2 uv0_offset_default = {0.f,0.f};
		static two::vec2 uv1_scale_default = {1.f,1.f};
		static two::vec2 uv1_offset_default = {0.f,0.f};
		static two::ShaderColor shader_color_default = two::ShaderColor::Shader;
		static bool flat_shaded_default = false;
		static bool screen_filter_default = false;
		// constructors
		static Constructor constructors[] = {
			{ t, two_MaterialBase__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_MaterialBase__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::MaterialBase, m_blend_mode), type<two::BlendMode>(), "blend_mode", &blend_mode_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialBase, m_cull_mode), type<two::CullMode>(), "cull_mode", &cull_mode_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialBase, m_depth_draw), type<two::DepthDraw>(), "depth_draw", &depth_draw_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialBase, m_depth_test), type<two::DepthTest>(), "depth_test", &depth_test_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialBase, m_uv0_scale), type<two::vec2>(), "uv0_scale", &uv0_scale_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialBase, m_uv0_offset), type<two::vec2>(), "uv0_offset", &uv0_offset_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialBase, m_uv1_scale), type<two::vec2>(), "uv1_scale", &uv1_scale_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialBase, m_uv1_offset), type<two::vec2>(), "uv1_offset", &uv1_offset_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialBase, m_shader_color), type<two::ShaderColor>(), "shader_color", &shader_color_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialBase, m_flat_shaded), type<bool>(), "flat_shaded", &flat_shaded_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialBase, m_screen_filter), type<bool>(), "screen_filter", &screen_filter_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialBase, m_anisotropy), type<float>(), "anisotropy", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::MaterialUser
	{
		Type& t = type<two::MaterialUser>();
		static Meta meta = { t, &namspc({ "two" }), "MaterialUser", sizeof(two::MaterialUser), TypeClass::Struct };
		// bases
		// defaults
		static two::Texture* tex0_default = nullptr;
		static two::Texture* tex1_default = nullptr;
		static two::Texture* tex2_default = nullptr;
		static two::Texture* tex3_default = nullptr;
		static two::Texture* tex4_default = nullptr;
		static two::Texture* tex5_default = nullptr;
		// constructors
		static Constructor constructors[] = {
			{ t, two_MaterialUser__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_MaterialUser__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::MaterialUser, m_tex0), type<two::Texture>(), "tex0", tex0_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::MaterialUser, m_tex1), type<two::Texture>(), "tex1", tex1_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::MaterialUser, m_tex2), type<two::Texture>(), "tex2", tex2_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::MaterialUser, m_tex3), type<two::Texture>(), "tex3", tex3_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::MaterialUser, m_tex4), type<two::Texture>(), "tex4", tex4_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::MaterialUser, m_tex5), type<two::Texture>(), "tex5", tex5_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::MaterialUser, m_attr0), type<two::vec4>(), "attr0", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::MaterialUser, m_attr1), type<two::vec4>(), "attr1", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::MaterialUser, m_attr2), type<two::vec4>(), "attr2", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::MaterialUser, m_attr3), type<two::vec4>(), "attr3", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::MaterialUser, m_attr4), type<two::vec4>(), "attr4", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::MaterialUser, m_attr5), type<two::vec4>(), "attr5", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::MaterialAlpha
	{
		Type& t = type<two::MaterialAlpha>();
		static Meta meta = { t, &namspc({ "two" }), "MaterialAlpha", sizeof(two::MaterialAlpha), TypeClass::Struct };
		// bases
		// defaults
		static two::MaterialParam<float> alpha_default = {1.f,nullptr};
		static float alpha_scissor_default = 0.5f;
		static bool alpha_test_default = false;
		static bool is_alpha_default = false;
		// constructors
		static Constructor constructors[] = {
			{ t, two_MaterialAlpha__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_MaterialAlpha__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::MaterialAlpha, m_alpha), type<two::MaterialParam<float>>(), "alpha", &alpha_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialAlpha, m_alpha_scissor), type<float>(), "alpha_scissor", &alpha_scissor_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialAlpha, m_alpha_test), type<bool>(), "alpha_test", &alpha_test_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialAlpha, m_is_alpha), type<bool>(), "is_alpha", &is_alpha_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::MaterialSolid
	{
		Type& t = type<two::MaterialSolid>();
		static Meta meta = { t, &namspc({ "two" }), "MaterialSolid", sizeof(two::MaterialSolid), TypeClass::Struct };
		// bases
		// defaults
		static two::MaterialParam<two::Colour> colour_default = {Colour::White,nullptr};
		// constructors
		static Constructor constructors[] = {
			{ t, two_MaterialSolid__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_MaterialSolid__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::MaterialSolid, m_colour), type<two::MaterialParam<two::Colour>>(), "colour", &colour_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::MaterialPoint
	{
		Type& t = type<two::MaterialPoint>();
		static Meta meta = { t, &namspc({ "two" }), "MaterialPoint", sizeof(two::MaterialPoint), TypeClass::Struct };
		// bases
		// defaults
		static float point_size_default = 1.f;
		static bool project_default = false;
		// constructors
		static Constructor constructors[] = {
			{ t, two_MaterialPoint__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_MaterialPoint__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::MaterialPoint, m_point_size), type<float>(), "point_size", &point_size_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialPoint, m_project), type<bool>(), "project", &project_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::MaterialLine
	{
		Type& t = type<two::MaterialLine>();
		static Meta meta = { t, &namspc({ "two" }), "MaterialLine", sizeof(two::MaterialLine), TypeClass::Struct };
		// bases
		// defaults
		static float line_width_default = 1.f;
		static bool dashed_default = false;
		static float dash_scale_default = 1.f;
		static float dash_size_default = 1.f;
		static float dash_gap_default = 1.f;
		// constructors
		static Constructor constructors[] = {
			{ t, two_MaterialLine__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_MaterialLine__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::MaterialLine, m_line_width), type<float>(), "line_width", &line_width_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialLine, m_dashed), type<bool>(), "dashed", &dashed_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialLine, m_dash_scale), type<float>(), "dash_scale", &dash_scale_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialLine, m_dash_size), type<float>(), "dash_size", &dash_size_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialLine, m_dash_gap), type<float>(), "dash_gap", &dash_gap_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::MaterialFresnel
	{
		Type& t = type<two::MaterialFresnel>();
		static Meta meta = { t, &namspc({ "two" }), "MaterialFresnel", sizeof(two::MaterialFresnel), TypeClass::Struct };
		// bases
		// defaults
		static two::MaterialParam<two::Colour> value_default = {Colour::White,nullptr};
		static float fresnel_scale_default = 1.f;
		static float fresnel_bias_default = 0.01f;
		static float fresnel_power_default = 5.f;
		// constructors
		static Constructor constructors[] = {
			{ t, two_MaterialFresnel__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_MaterialFresnel__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::MaterialFresnel, m_value), type<two::MaterialParam<two::Colour>>(), "value", &value_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialFresnel, m_fresnel_scale), type<float>(), "fresnel_scale", &fresnel_scale_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialFresnel, m_fresnel_bias), type<float>(), "fresnel_bias", &fresnel_bias_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialFresnel, m_fresnel_power), type<float>(), "fresnel_power", &fresnel_power_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::MaterialLit
	{
		Type& t = type<two::MaterialLit>();
		static Meta meta = { t, &namspc({ "two" }), "MaterialLit", sizeof(two::MaterialLit), TypeClass::Struct };
		// bases
		// defaults
		static two::MaterialParam<two::Colour> emissive_default = {rgba(0x00000000),nullptr};
		static float emissive_energy_default = 0.f;
		static two::MaterialParam<float> normal_default = {1.f,nullptr};
		static two::MaterialParam<float> bump_default = {1.f,nullptr};
		static two::MaterialParam<float> displace_default = {1.f,nullptr};
		static float displace_bias_default = 0.f;
		static bool no_envmap_default = false;
		// constructors
		static Constructor constructors[] = {
			{ t, two_MaterialLit__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_MaterialLit__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::MaterialLit, m_emissive), type<two::MaterialParam<two::Colour>>(), "emissive", &emissive_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialLit, m_emissive_energy), type<float>(), "emissive_energy", &emissive_energy_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialLit, m_normal), type<two::MaterialParam<float>>(), "normal", &normal_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialLit, m_bump), type<two::MaterialParam<float>>(), "bump", &bump_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialLit, m_displace), type<two::MaterialParam<float>>(), "displace", &displace_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialLit, m_displace_bias), type<float>(), "displace_bias", &displace_bias_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialLit, m_occlusion), type<two::MaterialParam<float>>(), "occlusion", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::MaterialLit, m_lightmap), type<two::MaterialParam<float>>(), "lightmap", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::MaterialLit, m_no_envmap), type<bool>(), "no_envmap", &no_envmap_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::MaterialPbr
	{
		Type& t = type<two::MaterialPbr>();
		static Meta meta = { t, &namspc({ "two" }), "MaterialPbr", sizeof(two::MaterialPbr), TypeClass::Struct };
		// bases
		// defaults
		static two::MaterialParam<two::Colour> albedo_default = {Colour::White,nullptr};
		static float specular_default = 0.5f;
		static two::MaterialParam<float> metallic_default = {0.f,nullptr,TextureChannel::Red};
		static two::MaterialParam<float> roughness_default = {1.f,nullptr,TextureChannel::Red};
		static two::MaterialParam<float> depth_default = {-0.02f,nullptr};
		static bool deep_parallax_default = false;
		static two::PbrDiffuseMode diffuse_mode_default = two::PbrDiffuseMode::Burley;
		static two::PbrSpecularMode specular_mode_default = two::PbrSpecularMode::SchlickGGX;
		static float construct_1_metallic_default = 0.f;
		static float construct_1_roughness_default = 1.f;
		// constructors
		static Constructor constructors[] = {
			{ t, two_MaterialPbr__construct_0, {} },
			{ t, two_MaterialPbr__construct_1, { { "albedo", type<two::Colour>(),  }, { "metallic", type<float>(), Param::Default, &construct_1_metallic_default }, { "roughness", type<float>(), Param::Default, &construct_1_roughness_default } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_MaterialPbr__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::MaterialPbr, m_albedo), type<two::MaterialParam<two::Colour>>(), "albedo", &albedo_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialPbr, m_specular), type<float>(), "specular", &specular_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialPbr, m_metallic), type<two::MaterialParam<float>>(), "metallic", &metallic_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialPbr, m_roughness), type<two::MaterialParam<float>>(), "roughness", &roughness_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialPbr, m_rim), type<two::MaterialParam<float>>(), "rim", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::MaterialPbr, m_rim_tint), type<float>(), "ritint", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::MaterialPbr, m_clearcoat), type<two::MaterialParam<float>>(), "clearcoat", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::MaterialPbr, m_clearcoat_gloss), type<float>(), "clearcoat_gloss", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::MaterialPbr, m_anisotropy), type<two::MaterialParam<float>>(), "anisotropy", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::MaterialPbr, m_subsurface), type<two::MaterialParam<float>>(), "subsurface", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::MaterialPbr, m_refraction), type<two::MaterialParam<float>>(), "refraction", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::MaterialPbr, m_depth), type<two::MaterialParam<float>>(), "depth", &depth_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialPbr, m_transmission), type<two::MaterialParam<two::Colour>>(), "transmission", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::MaterialPbr, m_deep_parallax), type<bool>(), "deep_parallax", &deep_parallax_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialPbr, m_diffuse_mode), type<two::PbrDiffuseMode>(), "diffuse_mode", &diffuse_mode_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialPbr, m_specular_mode), type<two::PbrSpecularMode>(), "specular_mode", &specular_mode_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::MaterialPhong
	{
		Type& t = type<two::MaterialPhong>();
		static Meta meta = { t, &namspc({ "two" }), "MaterialPhong", sizeof(two::MaterialPhong), TypeClass::Struct };
		// bases
		// defaults
		static two::MaterialParam<two::Colour> diffuse_default = {rgb(0xffffff),nullptr};
		static two::MaterialParam<two::Colour> specular_default = {rgb(0x111111),nullptr};
		static two::MaterialParam<float> shininess_default = {30.f,nullptr};
		static two::MaterialParam<float> reflectivity_default = {1.f,nullptr};
		static two::MaterialParam<float> refraction_default = {0.f,nullptr};
		static two::PhongEnvBlendMode env_blend_default = two::PhongEnvBlendMode::Mul;
		static bool toon_default = false;
		// constructors
		static Constructor constructors[] = {
			{ t, two_MaterialPhong__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_MaterialPhong__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::MaterialPhong, m_diffuse), type<two::MaterialParam<two::Colour>>(), "diffuse", &diffuse_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialPhong, m_specular), type<two::MaterialParam<two::Colour>>(), "specular", &specular_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialPhong, m_shininess), type<two::MaterialParam<float>>(), "shininess", &shininess_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialPhong, m_reflectivity), type<two::MaterialParam<float>>(), "reflectivity", &reflectivity_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialPhong, m_refraction), type<two::MaterialParam<float>>(), "refraction", &refraction_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialPhong, m_env_blend), type<two::PhongEnvBlendMode>(), "env_blend", &env_blend_default, Member::Value, nullptr },
			{ t, offsetof(two::MaterialPhong, m_toon), type<bool>(), "toon", &toon_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::BlockMaterial
	{
		Type& t = type<two::BlockMaterial>();
		static Meta meta = { t, &namspc({ "two" }), "BlockMaterial", sizeof(two::BlockMaterial), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::GfxBlock>() };
		static size_t bases_offsets[] = { base_offset<two::BlockMaterial, two::GfxBlock>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::Material
	{
		Type& t = type<two::Material>();
		static Meta meta = { t, &namspc({ "two" }), "Material", sizeof(two::Material), TypeClass::Object };
		// bases
		// defaults
		static uint16_t index_default = 0;
		static bool builtin_default = false;
		static two::Program* program_default = nullptr;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::Material, m_index), type<uint16_t>(), "index", &index_default, Member::Value, nullptr },
			{ t, offsetof(two::Material, m_name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Material, m_builtin), type<bool>(), "builtin", &builtin_default, Member::Value, nullptr },
			{ t, offsetof(two::Material, m_program), type<two::Program>(), "program", program_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::Material, m_base), type<two::MaterialBase>(), "base", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Material, m_alpha), type<two::MaterialAlpha>(), "alpha", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Material, m_solid), type<two::MaterialSolid>(), "solid", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Material, m_point), type<two::MaterialPoint>(), "point", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Material, m_line), type<two::MaterialLine>(), "line", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Material, m_lit), type<two::MaterialLit>(), "lit", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Material, m_pbr), type<two::MaterialPbr>(), "pbr", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Material, m_phong), type<two::MaterialPhong>(), "phong", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Material, m_fresnel), type<two::MaterialFresnel>(), "fresnel", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Material, m_user), type<two::MaterialUser>(), "user", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// two::ModelElem
	{
		Type& t = type<two::ModelElem>();
		static Meta meta = { t, &namspc({ "two" }), "ModelElem", sizeof(two::ModelElem), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_ModelElem__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_ModelElem__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::ModelElem, m_index), type<size_t>(), "index", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::ModelElem, m_mesh), type<two::Mesh>(), "mesh", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::ModelElem, m_has_transform), type<bool>(), "has_transform", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::ModelElem, m_transform), type<two::mat4>(), "transform", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::ModelElem, m_skin), type<int>(), "skin", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::ModelElem, m_colour), type<two::Colour>(), "colour", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::ModelElem, m_material), type<two::Material>(), "material", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Model
	{
		Type& t = type<two::Model>();
		static Meta meta = { t, &namspc({ "two" }), "Model", sizeof(two::Model), TypeClass::Object };
		// bases
		// defaults
		static two::Aabb aabb_default = {vec3(0.f),vec3(0.f)};
		static float radius_default = 0.f;
		static bool add_mesh_0_readback_default = false;
		static int add_item_0_skin_default = -1;
		static two::Colour add_item_0_colour_default = two::Colour::White;
		static two::Material* add_item_0_material_default = nullptr;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::Model, m_name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Model, m_index), type<uint16_t>(), "index", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Model, m_aabb), type<two::Aabb>(), "aabb", &aabb_default, Member::Value, nullptr },
			{ t, offsetof(two::Model, m_radius), type<float>(), "radius", &radius_default, Member::Value, nullptr },
			{ t, offsetof(two::Model, m_origin), type<two::vec3>(), "origin", nullptr, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "get_mesh", Address(), two_Model_get_mesh, { { "index", type<size_t>(),  } }, { &type<two::Mesh>(), QualType::None } },
			{ t, "add_mesh", Address(), two_Model_add_mesh, { { "name", type<stl::string>(),  }, { "readback", type<bool>(), Param::Default, &add_mesh_0_readback_default } }, { &type<two::Mesh>(), QualType::None } },
			{ t, "add_rig", Address(), two_Model_add_rig, { { "name", type<stl::string>(),  } }, { &type<two::Rig>(), QualType::None } },
			{ t, "add_item", Address(), two_Model_add_item, { { "mesh", type<two::Mesh>(),  }, { "transform", type<two::mat4>(),  }, { "skin", type<int>(), Param::Default, &add_item_0_skin_default }, { "colour", type<two::Colour>(), Param::Default, &add_item_0_colour_default }, { "material", type<two::Material>(), Param::Flags(Param::Nullable|Param::Default), &add_item_0_material_default } }, { &type<two::ModelElem>(), QualType::None } },
			{ t, "prepare", Address(), two_Model_prepare, {}, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, methods, {}, };
	}
	// two::Flow
	{
		Type& t = type<two::Flow>();
		static Meta meta = { t, &namspc({ "two" }), "Flow", sizeof(two::Flow), TypeClass::Struct };
		// bases
		// defaults
		static float duration_default = 1.f;
		static float start_time_default = 0.f;
		static bool loop_default = false;
		static two::ShapeVar shape_default = {};
		static two::EmitterFlow flow_default = two::EmitterFlow::Outward;
		static bool billboard_default = true;
		static two::vec3 direction_default = {0.f,0.f,-1.f};
		static two::quat rotation_default = ZeroQuat;
		static two::BlendMode blend_mode_default = two::BlendMode::Normal;
		static two::ValueTrack<float> volume_default = {1.f};
		static two::ValueTrack<uint32_t> rate_default = {0};
		static two::ValueTrack<float> lifetime_default = {1.f};
		static two::ValueTrack<float> gravity_default = {0.f};
		static two::ValueTrack<float> speed_default = {1.f};
		static two::ValueTrack<float> angle_default = {0.f};
		static two::ValueTrack<float> blend_default = {{0.8f,0.0f}};
		static two::ValueTrack<two::Colour> colour_default = {Colour::White};
		static two::ValueTrack<float> scale_default = {0.1f};
		static two::ValueTrack<float> sprite_frame_default = {0.f};
		// constructors
		static Constructor constructors[] = {
			{ t, two_Flow__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Flow__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Flow, m_name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Flow, m_duration), type<float>(), "duration", &duration_default, Member::Value, nullptr },
			{ t, offsetof(two::Flow, m_start_time), type<float>(), "start_time", &start_time_default, Member::Value, nullptr },
			{ t, offsetof(two::Flow, m_loop), type<bool>(), "loop", &loop_default, Member::Value, nullptr },
			{ t, offsetof(two::Flow, m_shape), type<two::ShapeVar>(), "shape", &shape_default, Member::NonMutable, nullptr },
			{ t, offsetof(two::Flow, m_flow), type<two::EmitterFlow>(), "flow", &flow_default, Member::Value, nullptr },
			{ t, offsetof(two::Flow, m_billboard), type<bool>(), "billboard", &billboard_default, Member::Value, nullptr },
			{ t, offsetof(two::Flow, m_direction), type<two::vec3>(), "direction", &direction_default, Member::Value, nullptr },
			{ t, offsetof(two::Flow, m_rotation), type<two::quat>(), "rotation", &rotation_default, Member::Value, nullptr },
			{ t, offsetof(two::Flow, m_blend_mode), type<two::BlendMode>(), "blend_mode", &blend_mode_default, Member::Value, nullptr },
			{ t, offsetof(two::Flow, m_volume), type<two::ValueTrack<float>>(), "volume", &volume_default, Member::Value, nullptr },
			{ t, offsetof(two::Flow, m_rate), type<two::ValueTrack<uint32_t>>(), "rate", &rate_default, Member::Value, nullptr },
			{ t, offsetof(two::Flow, m_lifetime), type<two::ValueTrack<float>>(), "lifetime", &lifetime_default, Member::Value, nullptr },
			{ t, offsetof(two::Flow, m_gravity), type<two::ValueTrack<float>>(), "gravity", &gravity_default, Member::Value, nullptr },
			{ t, offsetof(two::Flow, m_speed), type<two::ValueTrack<float>>(), "speed", &speed_default, Member::Value, nullptr },
			{ t, offsetof(two::Flow, m_angle), type<two::ValueTrack<float>>(), "angle", &angle_default, Member::Value, nullptr },
			{ t, offsetof(two::Flow, m_blend), type<two::ValueTrack<float>>(), "blend", &blend_default, Member::Value, nullptr },
			{ t, offsetof(two::Flow, m_colour), type<two::ValueTrack<two::Colour>>(), "colour", &colour_default, Member::Value, nullptr },
			{ t, offsetof(two::Flow, m_scale), type<two::ValueTrack<float>>(), "scale", &scale_default, Member::Value, nullptr },
			{ t, offsetof(two::Flow, m_sprite_frame), type<two::ValueTrack<float>>(), "sprite_frame", &sprite_frame_default, Member::Value, nullptr },
			{ t, offsetof(two::Flow, m_sprite_name), type<stl::string>(), "sprite_name", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Flare
	{
		Type& t = type<two::Flare>();
		static Meta meta = { t, &namspc({ "two" }), "Flare", sizeof(two::Flare), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Flow>() };
		static size_t bases_offsets[] = { base_offset<two::Flare, two::Flow>() };
		// defaults
		static two::Node3* node_default = nullptr;
		// constructors
		static Constructor constructors[] = {
			{ t, two_Flare__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Flare__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Flare, m_node), type<two::Node3>(), "node", node_default, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// two::BlockParticles
	{
		Type& t = type<two::BlockParticles>();
		static Meta meta = { t, &namspc({ "two" }), "BlockParticles", sizeof(two::BlockParticles), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::GfxBlock>() };
		static size_t bases_offsets[] = { base_offset<two::BlockParticles, two::GfxBlock>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::Batch
	{
		Type& t = type<two::Batch>();
		static Meta meta = { t, &namspc({ "two" }), "Batch", sizeof(two::Batch), TypeClass::Struct };
		// bases
		// defaults
		static two::Item* item_default = nullptr;
		// constructors
		static Constructor constructors[] = {
			{ t, two_Batch__construct_0, {} },
			{ t, two_Batch__construct_1, { { "item", type<two::Item>(),  }, { "stride", type<uint16_t>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Batch__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Batch, m_item), type<two::Item>(), "item", item_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::Batch, m_stride), type<uint16_t>(), "stride", nullptr, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "update_aabb", Address(), two_Batch_update_aabb, { { "instances", type<stl::span<two::mat4>>(),  } }, g_qvoid },
			{ t, "transforms", Address(), two_Batch_transforms, { { "instances", type<stl::span<two::mat4>>(),  } }, g_qvoid },
			{ t, "begin", Address(), two_Batch_begin, { { "count", type<uint32_t>(),  } }, { &type<stl::span<float>>(), QualType::None } },
			{ t, "commit", Address(), two_Batch_commit, { { "data", type<stl::span<float>>(),  } }, g_qvoid },
			{ t, "cache", Address(), two_Batch_cache, { { "data", type<stl::span<float>>(),  } }, g_qvoid },
			{ t, "transform", Address(), two_Batch_transform, { { "m", type<two::mat4>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, methods, {}, };
	}
	// two::Item
	{
		Type& t = type<two::Item>();
		static Meta meta = { t, &namspc({ "two" }), "Item", sizeof(two::Item), TypeClass::Object };
		// bases
		// defaults
		static two::Node3* node_default = nullptr;
		static two::Model* model_default = nullptr;
		static uint32_t flags_default = 0;
		static two::Colour colour_default = two::Colour::White;
		static two::Material* material_default = nullptr;
		static bool visible_default = true;
		static two::ItemShadow shadow_default = two::ItemShadow::Default;
		static two::Rig* rig_default = nullptr;
		static two::Batch* batch_default = nullptr;
		static uint32_t construct_1_flags_default = 0;
		static two::Material* construct_1_material_default = nullptr;
		// constructors
		static Constructor constructors[] = {
			{ t, two_Item__construct_0, {} },
			{ t, two_Item__construct_1, { { "node", type<two::Node3>(),  }, { "model", type<two::Model>(),  }, { "flags", type<uint32_t>(), Param::Default, &construct_1_flags_default }, { "material", type<two::Material>(), Param::Flags(Param::Nullable|Param::Default), &construct_1_material_default } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::Item, m_node), type<two::Node3>(), "node", node_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::Item, m_model), type<two::Model>(), "model", model_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::Item, m_flags), type<uint32_t>(), "flags", &flags_default, Member::Value, nullptr },
			{ t, offsetof(two::Item, m_colour), type<two::Colour>(), "colour", &colour_default, Member::Value, nullptr },
			{ t, offsetof(two::Item, m_material), type<two::Material>(), "material", material_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::Item, m_visible), type<bool>(), "visible", &visible_default, Member::Value, nullptr },
			{ t, offsetof(two::Item, m_shadow), type<two::ItemShadow>(), "shadow", &shadow_default, Member::Value, nullptr },
			{ t, offsetof(two::Item, m_rig), type<two::Rig>(), "rig", rig_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::Item, m_aabb), type<two::Aabb>(), "aabb", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Item, m_batch), type<two::Batch>(), "batch", batch_default, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "update_aabb", Address(), two_Item_update_aabb, {}, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, members, methods, {}, };
	}
	// two::ImportConfig
	{
		Type& t = type<two::ImportConfig>();
		static Meta meta = { t, &namspc({ "two" }), "ImportConfig", sizeof(two::ImportConfig), TypeClass::Struct };
		// bases
		// defaults
		static two::ModelFormat format_default = two::ModelFormat::obj;
		static two::quat rotation_default = ZeroQuat;
		static two::mat4 transform_default = bxidentity();
		static bool force_reimport_default = false;
		static bool cache_geometry_default = false;
		static bool optimize_geometry_default = false;
		static bool need_normals_default = true;
		static bool need_uvs_default = true;
		static bool no_transforms_default = false;
		static uint32_t flags_default = ItemFlag::None;
		// constructors
		static Constructor constructors[] = {
			{ t, two_ImportConfig__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_ImportConfig__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::ImportConfig, m_format), type<two::ModelFormat>(), "format", &format_default, Member::Value, nullptr },
			{ t, offsetof(two::ImportConfig, m_position), type<two::vec3>(), "position", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::ImportConfig, m_rotation), type<two::quat>(), "rotation", &rotation_default, Member::Value, nullptr },
			{ t, offsetof(two::ImportConfig, m_scale), type<two::vec3>(), "scale", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::ImportConfig, m_transform), type<two::mat4>(), "transform", &transform_default, Member::Value, nullptr },
			{ t, offsetof(two::ImportConfig, m_exclude_elements), type<stl::vector<stl::string>>(), "exclude_elements", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::ImportConfig, m_exclude_materials), type<stl::vector<stl::string>>(), "exclude_materials", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::ImportConfig, m_include_elements), type<stl::vector<stl::string>>(), "include_elements", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::ImportConfig, m_include_materials), type<stl::vector<stl::string>>(), "include_materials", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::ImportConfig, m_suffix), type<stl::string>(), "suffix", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::ImportConfig, m_force_reimport), type<bool>(), "force_reimport", &force_reimport_default, Member::Value, nullptr },
			{ t, offsetof(two::ImportConfig, m_cache_geometry), type<bool>(), "cache_geometry", &cache_geometry_default, Member::Value, nullptr },
			{ t, offsetof(two::ImportConfig, m_optimize_geometry), type<bool>(), "optimize_geometry", &optimize_geometry_default, Member::Value, nullptr },
			{ t, offsetof(two::ImportConfig, m_need_normals), type<bool>(), "need_normals", &need_normals_default, Member::Value, nullptr },
			{ t, offsetof(two::ImportConfig, m_need_uvs), type<bool>(), "need_uvs", &need_uvs_default, Member::Value, nullptr },
			{ t, offsetof(two::ImportConfig, m_no_transforms), type<bool>(), "no_transforms", &no_transforms_default, Member::Value, nullptr },
			{ t, offsetof(two::ImportConfig, m_flags), type<uint32_t>(), "flags", &flags_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Import
	{
		Type& t = type<two::Import>();
		static Meta meta = { t, &namspc({ "two" }), "Import", sizeof(two::Import), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::Import, m_name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Import, m_file), type<stl::string>(), "file", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Import, m_path), type<stl::string>(), "path", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Import, m_config), type<two::ImportConfig>(), "config", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Import, m_meshes), type<stl::vector<two::Mesh*>>(), "meshes", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::Import, m_models), type<stl::vector<two::Model*>>(), "models", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::Import, m_images), type<stl::vector<two::Texture*>>(), "images", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::Import, m_materials), type<stl::vector<two::Material*>>(), "materials", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::Import, m_animations), type<stl::vector<two::Animation*>>(), "animations", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// two::Prefab
	{
		Type& t = type<two::Prefab>();
		static Meta meta = { t, &namspc({ "two" }), "Prefab", sizeof(two::Prefab), TypeClass::Object };
		// bases
		// defaults
		static two::Mime* add_0_mime_default = nullptr;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::Prefab, m_name), type<stl::string>(), "name", nullptr, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "add", Address(), two_Prefab_add, { { "scene", type<two::Scene>(),  }, { "mime", type<two::Mime>(), Param::Flags(Param::Nullable|Param::Default), &add_0_mime_default } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, methods, {}, };
	}
	// two::AssetStore<two::Texture>
	{
		Type& t = type<two::AssetStore<two::Texture>>();
		static Meta meta = { t, &namspc({ "two" }), "AssetStore<two::Texture>", sizeof(two::AssetStore<two::Texture>), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "get", Address(), two_AssetStore_two_Texture_get, { { "name", type<stl::string>(),  } }, { &type<two::Texture>(), QualType::None } },
			{ t, "create", Address(), two_AssetStore_two_Texture_create, { { "name", type<stl::string>(),  } }, { &type<two::Texture>(), QualType::None } },
			{ t, "fetch", Address(), two_AssetStore_two_Texture_fetch, { { "name", type<stl::string>(),  } }, { &type<two::Texture>(), QualType::None } },
			{ t, "file", Address(), two_AssetStore_two_Texture_file, { { "name", type<stl::string>(),  } }, { &type<two::Texture>(), QualType::None } },
			{ t, "file_at", Address(), two_AssetStore_two_Texture_file_at, { { "path", type<stl::string>(),  }, { "name", type<stl::string>(),  } }, { &type<two::Texture>(), QualType::None } },
			{ t, "load", Address(), two_AssetStore_two_Texture_load, { { "path", type<stl::string>(),  }, { "name", type<stl::string>(),  } }, { &type<two::Texture>(), QualType::None } },
			{ t, "destroy", Address(), two_AssetStore_two_Texture_destroy, { { "name", type<stl::string>(),  } }, g_qvoid },
			{ t, "clear", Address(), two_AssetStore_two_Texture_clear, {}, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, methods, {}, };
	}
	// two::AssetStore<two::Program>
	{
		Type& t = type<two::AssetStore<two::Program>>();
		static Meta meta = { t, &namspc({ "two" }), "AssetStore<two::Program>", sizeof(two::AssetStore<two::Program>), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "get", Address(), two_AssetStore_two_Program_get, { { "name", type<stl::string>(),  } }, { &type<two::Program>(), QualType::None } },
			{ t, "create", Address(), two_AssetStore_two_Program_create, { { "name", type<stl::string>(),  } }, { &type<two::Program>(), QualType::None } },
			{ t, "fetch", Address(), two_AssetStore_two_Program_fetch, { { "name", type<stl::string>(),  } }, { &type<two::Program>(), QualType::None } },
			{ t, "file", Address(), two_AssetStore_two_Program_file, { { "name", type<stl::string>(),  } }, { &type<two::Program>(), QualType::None } },
			{ t, "file_at", Address(), two_AssetStore_two_Program_file_at, { { "path", type<stl::string>(),  }, { "name", type<stl::string>(),  } }, { &type<two::Program>(), QualType::None } },
			{ t, "load", Address(), two_AssetStore_two_Program_load, { { "path", type<stl::string>(),  }, { "name", type<stl::string>(),  } }, { &type<two::Program>(), QualType::None } },
			{ t, "destroy", Address(), two_AssetStore_two_Program_destroy, { { "name", type<stl::string>(),  } }, g_qvoid },
			{ t, "clear", Address(), two_AssetStore_two_Program_clear, {}, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, methods, {}, };
	}
	// two::AssetStore<two::Material>
	{
		Type& t = type<two::AssetStore<two::Material>>();
		static Meta meta = { t, &namspc({ "two" }), "AssetStore<two::Material>", sizeof(two::AssetStore<two::Material>), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "get", Address(), two_AssetStore_two_Material_get, { { "name", type<stl::string>(),  } }, { &type<two::Material>(), QualType::None } },
			{ t, "create", Address(), two_AssetStore_two_Material_create, { { "name", type<stl::string>(),  } }, { &type<two::Material>(), QualType::None } },
			{ t, "fetch", Address(), two_AssetStore_two_Material_fetch, { { "name", type<stl::string>(),  } }, { &type<two::Material>(), QualType::None } },
			{ t, "file", Address(), two_AssetStore_two_Material_file, { { "name", type<stl::string>(),  } }, { &type<two::Material>(), QualType::None } },
			{ t, "file_at", Address(), two_AssetStore_two_Material_file_at, { { "path", type<stl::string>(),  }, { "name", type<stl::string>(),  } }, { &type<two::Material>(), QualType::None } },
			{ t, "load", Address(), two_AssetStore_two_Material_load, { { "path", type<stl::string>(),  }, { "name", type<stl::string>(),  } }, { &type<two::Material>(), QualType::None } },
			{ t, "destroy", Address(), two_AssetStore_two_Material_destroy, { { "name", type<stl::string>(),  } }, g_qvoid },
			{ t, "clear", Address(), two_AssetStore_two_Material_clear, {}, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, methods, {}, };
	}
	// two::AssetStore<two::Model>
	{
		Type& t = type<two::AssetStore<two::Model>>();
		static Meta meta = { t, &namspc({ "two" }), "AssetStore<two::Model>", sizeof(two::AssetStore<two::Model>), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "get", Address(), two_AssetStore_two_Model_get, { { "name", type<stl::string>(),  } }, { &type<two::Model>(), QualType::None } },
			{ t, "create", Address(), two_AssetStore_two_Model_create, { { "name", type<stl::string>(),  } }, { &type<two::Model>(), QualType::None } },
			{ t, "fetch", Address(), two_AssetStore_two_Model_fetch, { { "name", type<stl::string>(),  } }, { &type<two::Model>(), QualType::None } },
			{ t, "file", Address(), two_AssetStore_two_Model_file, { { "name", type<stl::string>(),  } }, { &type<two::Model>(), QualType::None } },
			{ t, "file_at", Address(), two_AssetStore_two_Model_file_at, { { "path", type<stl::string>(),  }, { "name", type<stl::string>(),  } }, { &type<two::Model>(), QualType::None } },
			{ t, "load", Address(), two_AssetStore_two_Model_load, { { "path", type<stl::string>(),  }, { "name", type<stl::string>(),  } }, { &type<two::Model>(), QualType::None } },
			{ t, "destroy", Address(), two_AssetStore_two_Model_destroy, { { "name", type<stl::string>(),  } }, g_qvoid },
			{ t, "clear", Address(), two_AssetStore_two_Model_clear, {}, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, methods, {}, };
	}
	// two::AssetStore<two::Flow>
	{
		Type& t = type<two::AssetStore<two::Flow>>();
		static Meta meta = { t, &namspc({ "two" }), "AssetStore<two::Flow>", sizeof(two::AssetStore<two::Flow>), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "get", Address(), two_AssetStore_two_Flow_get, { { "name", type<stl::string>(),  } }, { &type<two::Flow>(), QualType::None } },
			{ t, "create", Address(), two_AssetStore_two_Flow_create, { { "name", type<stl::string>(),  } }, { &type<two::Flow>(), QualType::None } },
			{ t, "fetch", Address(), two_AssetStore_two_Flow_fetch, { { "name", type<stl::string>(),  } }, { &type<two::Flow>(), QualType::None } },
			{ t, "file", Address(), two_AssetStore_two_Flow_file, { { "name", type<stl::string>(),  } }, { &type<two::Flow>(), QualType::None } },
			{ t, "file_at", Address(), two_AssetStore_two_Flow_file_at, { { "path", type<stl::string>(),  }, { "name", type<stl::string>(),  } }, { &type<two::Flow>(), QualType::None } },
			{ t, "load", Address(), two_AssetStore_two_Flow_load, { { "path", type<stl::string>(),  }, { "name", type<stl::string>(),  } }, { &type<two::Flow>(), QualType::None } },
			{ t, "destroy", Address(), two_AssetStore_two_Flow_destroy, { { "name", type<stl::string>(),  } }, g_qvoid },
			{ t, "clear", Address(), two_AssetStore_two_Flow_clear, {}, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, methods, {}, };
	}
	// two::AssetStore<two::Prefab>
	{
		Type& t = type<two::AssetStore<two::Prefab>>();
		static Meta meta = { t, &namspc({ "two" }), "AssetStore<two::Prefab>", sizeof(two::AssetStore<two::Prefab>), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "get", Address(), two_AssetStore_two_Prefab_get, { { "name", type<stl::string>(),  } }, { &type<two::Prefab>(), QualType::None } },
			{ t, "create", Address(), two_AssetStore_two_Prefab_create, { { "name", type<stl::string>(),  } }, { &type<two::Prefab>(), QualType::None } },
			{ t, "fetch", Address(), two_AssetStore_two_Prefab_fetch, { { "name", type<stl::string>(),  } }, { &type<two::Prefab>(), QualType::None } },
			{ t, "file", Address(), two_AssetStore_two_Prefab_file, { { "name", type<stl::string>(),  } }, { &type<two::Prefab>(), QualType::None } },
			{ t, "file_at", Address(), two_AssetStore_two_Prefab_file_at, { { "path", type<stl::string>(),  }, { "name", type<stl::string>(),  } }, { &type<two::Prefab>(), QualType::None } },
			{ t, "load", Address(), two_AssetStore_two_Prefab_load, { { "path", type<stl::string>(),  }, { "name", type<stl::string>(),  } }, { &type<two::Prefab>(), QualType::None } },
			{ t, "destroy", Address(), two_AssetStore_two_Prefab_destroy, { { "name", type<stl::string>(),  } }, g_qvoid },
			{ t, "clear", Address(), two_AssetStore_two_Prefab_clear, {}, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, methods, {}, };
	}
	// two::Camera
	{
		Type& t = type<two::Camera>();
		static Meta meta = { t, &namspc({ "two" }), "Camera", sizeof(two::Camera), TypeClass::Object };
		// bases
		// defaults
		static two::vec3 eye_default = z3;
		static two::vec3 up_default = y3;
		static float fov_default = 60.f;
		static float aspect_default = 1.f;
		static float near_default = 0.1f;
		static float far_default = 100.f;
		static bool orthographic_default = false;
		static float height_default = 1.f;
		static bool no_update_default = false;
		static bool optimize_ends_default = true;
		static two::vec4 lod_offsets_default = {0.1f,0.3f,0.6f,0.8f};
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::Camera, m_eye), type<two::vec3>(), "eye", &eye_default, Member::Value, nullptr },
			{ t, offsetof(two::Camera, m_target), type<two::vec3>(), "target", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Camera, m_up), type<two::vec3>(), "up", &up_default, Member::Value, nullptr },
			{ t, offsetof(two::Camera, m_view), type<two::mat4>(), "view", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Camera, m_proj), type<two::mat4>(), "proj", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Camera, m_fov), type<float>(), "fov", &fov_default, Member::Value, nullptr },
			{ t, offsetof(two::Camera, m_aspect), type<float>(), "aspect", &aspect_default, Member::Value, nullptr },
			{ t, offsetof(two::Camera, m_near), type<float>(), "near", &near_default, Member::Value, nullptr },
			{ t, offsetof(two::Camera, m_far), type<float>(), "far", &far_default, Member::Value, nullptr },
			{ t, offsetof(two::Camera, m_orthographic), type<bool>(), "orthographic", &orthographic_default, Member::Value, nullptr },
			{ t, offsetof(two::Camera, m_height), type<float>(), "height", &height_default, Member::Value, nullptr },
			{ t, offsetof(two::Camera, m_no_update), type<bool>(), "no_update", &no_update_default, Member::Value, nullptr },
			{ t, offsetof(two::Camera, m_optimize_ends), type<bool>(), "optimize_ends", &optimize_ends_default, Member::Value, nullptr },
			{ t, offsetof(two::Camera, m_lod_offsets), type<two::vec4>(), "lod_offsets", &lod_offsets_default, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "set_look_at", Address(), two_Camera_set_look_at, { { "eye", type<two::vec3>(),  }, { "target", type<two::vec3>(),  } }, g_qvoid },
			{ t, "set_isometric", Address(), two_Camera_set_isometric, { { "angle", type<two::IsometricAngle>(),  }, { "position", type<two::vec3>(),  } }, g_qvoid },
			{ t, "ray", Address(), two_Camera_ray, { { "offset", type<two::vec2>(),  } }, { &type<two::Ray>(), QualType::None } },
			{ t, "transform", Address(), two_Camera_transform, { { "point", type<two::vec3>(),  } }, { &type<two::vec3>(), QualType::None } },
			{ t, "project", Address(), two_Camera_project, { { "point", type<two::vec3>(),  } }, { &type<two::vec3>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, methods, {}, };
	}
	// two::MirrorCamera
	{
		Type& t = type<two::MirrorCamera>();
		static Meta meta = { t, &namspc({ "two" }), "MirrorCamera", sizeof(two::MirrorCamera), TypeClass::Struct };
		// bases
		// defaults
		static bool visible_default = false;
		// constructors
		static Constructor constructors[] = {
			{ t, two_MirrorCamera__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_MirrorCamera__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::MirrorCamera, m_visible), type<bool>(), "visible", &visible_default, Member::Value, nullptr },
			{ t, offsetof(two::MirrorCamera, m_camera), type<two::Camera>(), "camera", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::MirrorCamera, m_mirror), type<two::mat4>(), "mirror", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::DepthParams
	{
		Type& t = type<two::DepthParams>();
		static Meta meta = { t, &namspc({ "two" }), "DepthParams", sizeof(two::DepthParams), TypeClass::Struct };
		// bases
		// defaults
		static float depth_bias_default = 0.f;
		static float depth_normal_bias_default = 0.f;
		static float depth_z_far_default = 0.f;
		// constructors
		static Constructor constructors[] = {
			{ t, two_DepthParams__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_DepthParams__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::DepthParams, m_depth_bias), type<float>(), "depth_bias", &depth_bias_default, Member::Value, nullptr },
			{ t, offsetof(two::DepthParams, m_depth_normal_bias), type<float>(), "depth_normal_bias", &depth_normal_bias_default, Member::Value, nullptr },
			{ t, offsetof(two::DepthParams, m_depth_z_far), type<float>(), "depth_z_far", &depth_z_far_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::DistanceParams
	{
		Type& t = type<two::DistanceParams>();
		static Meta meta = { t, &namspc({ "two" }), "DistanceParams", sizeof(two::DistanceParams), TypeClass::Struct };
		// bases
		// defaults
		static float near_default = 0.f;
		static float far_default = 1.f;
		// constructors
		static Constructor constructors[] = {
			{ t, two_DistanceParams__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_DistanceParams__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::DistanceParams, m_eye), type<two::vec3>(), "eye", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::DistanceParams, m_near), type<float>(), "near", &near_default, Member::Value, nullptr },
			{ t, offsetof(two::DistanceParams, m_far), type<float>(), "far", &far_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::BlockDepth
	{
		Type& t = type<two::BlockDepth>();
		static Meta meta = { t, &namspc({ "two" }), "BlockDepth", sizeof(two::BlockDepth), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::DrawBlock>() };
		static size_t bases_offsets[] = { base_offset<two::BlockDepth, two::DrawBlock>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::GpuMesh
	{
		Type& t = type<two::GpuMesh>();
		static Meta meta = { t, &namspc({ "two" }), "GpuMesh", sizeof(two::GpuMesh), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_GpuMesh__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_GpuMesh__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// two::Mesh
	{
		Type& t = type<two::Mesh>();
		static Meta meta = { t, &namspc({ "two" }), "Mesh", sizeof(two::Mesh), TypeClass::Object };
		// bases
		// defaults
		static two::PrimitiveType primitive_default = two::PrimitiveType::Triangles;
		static two::Aabb aabb_default = {};
		static float radius_default = 0.f;
		static bool readback_default = false;
		static uint32_t vertex_format_default = 0;
		static bool qnormals_default = false;
		static uint32_t vertex_count_default = 0;
		static uint32_t index_count_default = 0;
		static bool index32_default = false;
		static two::Material* material_default = nullptr;
		static bool is_dynamic_default = false;
		static bool is_direct_default = false;
		static bool write_0_optimize_default = false;
		static bool write_0_dynamic_default = false;
		static bool xwrite_0_optimize_default = false;
		static bool xwrite_0_dynamic_default = false;
		static bool upload_0_optimize_default = false;
		static uint32_t direct_0_index_count_default = 0;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::Mesh, m_name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Mesh, m_index), type<uint16_t>(), "index", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Mesh, m_primitive), type<two::PrimitiveType>(), "primitive", &primitive_default, Member::Value, nullptr },
			{ t, offsetof(two::Mesh, m_aabb), type<two::Aabb>(), "aabb", &aabb_default, Member::Value, nullptr },
			{ t, offsetof(two::Mesh, m_radius), type<float>(), "radius", &radius_default, Member::Value, nullptr },
			{ t, offsetof(two::Mesh, m_origin), type<two::vec3>(), "origin", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Mesh, m_readback), type<bool>(), "readback", &readback_default, Member::Value, nullptr },
			{ t, offsetof(two::Mesh, m_vertex_format), type<uint32_t>(), "vertex_format", &vertex_format_default, Member::Value, nullptr },
			{ t, offsetof(two::Mesh, m_qnormals), type<bool>(), "qnormals", &qnormals_default, Member::Value, nullptr },
			{ t, offsetof(two::Mesh, m_vertex_count), type<uint32_t>(), "vertex_count", &vertex_count_default, Member::Value, nullptr },
			{ t, offsetof(two::Mesh, m_index_count), type<uint32_t>(), "index_count", &index_count_default, Member::Value, nullptr },
			{ t, offsetof(two::Mesh, m_index32), type<bool>(), "index32", &index32_default, Member::Value, nullptr },
			{ t, offsetof(two::Mesh, m_material), type<two::Material>(), "material", material_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::Mesh, m_is_dynamic), type<bool>(), "is_dynamic", &is_dynamic_default, Member::Value, nullptr },
			{ t, offsetof(two::Mesh, m_is_direct), type<bool>(), "is_direct", &is_direct_default, Member::Value, nullptr },
			{ t, offsetof(two::Mesh, m_cache), type<two::MeshAdapter>(), "cache", nullptr, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "clear", Address(), two_Mesh_clear, {}, g_qvoid },
			{ t, "write", Address(), two_Mesh_write, { { "packer", type<two::MeshPacker>(),  }, { "optimize", type<bool>(), Param::Default, &write_0_optimize_default }, { "dynamic", type<bool>(), Param::Default, &write_0_dynamic_default } }, g_qvoid },
			{ t, "xwrite", Address(), two_Mesh_xwrite, { { "packer", type<two::MeshPacker>(),  }, { "transform", type<two::mat4>(),  }, { "optimize", type<bool>(), Param::Default, &xwrite_0_optimize_default }, { "dynamic", type<bool>(), Param::Default, &xwrite_0_dynamic_default } }, g_qvoid },
			{ t, "morph", Address(), two_Mesh_morph, { { "packer", type<two::MeshPacker>(),  } }, g_qvoid },
			{ t, "upload", Address(), two_Mesh_upload, { { "gpu_mesh", type<two::GpuMesh>(),  }, { "optimize", type<bool>(), Param::Default, &upload_0_optimize_default } }, g_qvoid },
			{ t, "cache", Address(), two_Mesh_cache, { { "gpu_mesh", type<two::GpuMesh>(),  } }, g_qvoid },
			{ t, "direct", Address(), two_Mesh_direct, { { "vertex_format", type<uint32_t>(),  }, { "vertex_count", type<uint32_t>(),  }, { "index_count", type<uint32_t>(), Param::Default, &direct_0_index_count_default } }, { &type<two::MeshAdapter>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, methods, {}, };
	}
	// two::Direct
	{
		Type& t = type<two::Direct>();
		static Meta meta = { t, &namspc({ "two" }), "Direct", sizeof(two::Direct), TypeClass::Object };
		// bases
		// defaults
		static two::Item* item_default = nullptr;
		// constructors
		static Constructor constructors[] = {
			{ t, two_Direct__construct_0, {} },
			{ t, two_Direct__construct_1, { { "item", type<two::Item>(),  } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::Direct, m_item), type<two::Item>(), "item", item_default, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, {}, members, {}, {}, };
	}
	// two::ImmediateDraw
	{
		Type& t = type<two::ImmediateDraw>();
		static Meta meta = { t, &namspc({ "two" }), "ImmediateDraw", sizeof(two::ImmediateDraw), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::SymbolIndex
	{
		Type& t = type<two::SymbolIndex>();
		static Meta meta = { t, &namspc({ "two" }), "SymbolIndex", sizeof(two::SymbolIndex), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::Lines
	{
		Type& t = type<two::Lines>();
		static Meta meta = { t, &namspc({ "two" }), "Lines", sizeof(two::Lines), TypeClass::Object };
		// bases
		// defaults
		static two::Colour add_0_start_colour_default = two::Colour(1.f);
		static two::Colour add_0_end_colour_default = two::Colour(1.f);
		static two::Colour start_0_colour_default = two::Colour(1.f);
		static two::Colour next_0_colour_default = two::Colour(1.f);
		// constructors
		static Constructor constructors[] = {
			{ t, two_Lines__construct_0, {} },
			{ t, two_Lines__construct_1, { { "points", type<stl::vector<two::vec3>>(),  } } },
			{ t, two_Lines__construct_2, { { "curve", type<two::Curve3>(),  }, { "subdiv", type<size_t>(),  } } }
		};
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "add", Address(), two_Lines_add, { { "start", type<two::vec3>(),  }, { "end", type<two::vec3>(),  }, { "start_colour", type<two::Colour>(), Param::Default, &add_0_start_colour_default }, { "end_colour", type<two::Colour>(), Param::Default, &add_0_end_colour_default } }, g_qvoid },
			{ t, "start", Address(), two_Lines_start, { { "position", type<two::vec3>(),  }, { "colour", type<two::Colour>(), Param::Default, &start_0_colour_default } }, g_qvoid },
			{ t, "next", Address(), two_Lines_next, { { "position", type<two::vec3>(),  }, { "colour", type<two::Colour>(), Param::Default, &next_0_colour_default } }, g_qvoid },
			{ t, "setup", Address(), two_Lines_setup, {}, g_qvoid },
			{ t, "write", Address(), two_Lines_write, { { "mesh", type<two::Mesh>(),  } }, g_qvoid },
			{ t, "commit", Address(), two_Lines_commit, { { "batch", type<two::Batch>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, {}, methods, {}, };
	}
	// two::BlockFilter
	{
		Type& t = type<two::BlockFilter>();
		static Meta meta = { t, &namspc({ "two" }), "BlockFilter", sizeof(two::BlockFilter), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::GfxBlock>() };
		static size_t bases_offsets[] = { base_offset<two::BlockFilter, two::GfxBlock>() };
		// defaults
		static uint64_t submit_0_flags_default = 0U;
		static bool submit_0_render_default = false;
		static uint64_t quad_0_flags_default = 0U;
		static bool quad_0_render_default = false;
		static int source0p_0_level_default = 0;
		static uint32_t source0p_0_flags_default = UINT32_MAX;
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
			{ t, "submit", Address(), two_BlockFilter_submit, { { "pass", type<two::Pass>(),  }, { "fbo", type<two::FrameBuffer>(),  }, { "program", type<two::ProgramVersion>(),  }, { "quad", type<two::RenderQuad>(),  }, { "flags", type<uint64_t>(), Param::Default, &submit_0_flags_default }, { "render", type<bool>(), Param::Default, &submit_0_render_default } }, g_qvoid },
			{ t, "quad", Address(), two_BlockFilter_quad, { { "pass", type<two::Pass>(),  }, { "fbo", type<two::FrameBuffer>(),  }, { "program", type<two::ProgramVersion>(),  }, { "flags", type<uint64_t>(), Param::Default, &quad_0_flags_default }, { "render", type<bool>(), Param::Default, &quad_0_render_default } }, g_qvoid },
			{ t, "multiply", Address(), two_BlockFilter_multiply, { { "mul", type<float>(),  } }, g_qvoid },
			{ t, "source0p", Address(), two_BlockFilter_source0p, { { "texture", type<two::Texture>(),  }, { "program", type<two::ProgramVersion>(),  }, { "level", type<int>(), Param::Default, &source0p_0_level_default }, { "flags", type<uint32_t>(), Param::Default, &source0p_0_flags_default } }, g_qvoid },
			{ t, "source0", Address(), two_BlockFilter_source0, { { "texture", type<two::Texture>(),  }, { "flags", type<uint32_t>(), Param::Default, &source0_0_flags_default } }, g_qvoid },
			{ t, "source1", Address(), two_BlockFilter_source1, { { "texture", type<two::Texture>(),  }, { "flags", type<uint32_t>(), Param::Default, &source1_0_flags_default } }, g_qvoid },
			{ t, "source2", Address(), two_BlockFilter_source2, { { "texture", type<two::Texture>(),  }, { "flags", type<uint32_t>(), Param::Default, &source2_0_flags_default } }, g_qvoid },
			{ t, "source3", Address(), two_BlockFilter_source3, { { "texture", type<two::Texture>(),  }, { "flags", type<uint32_t>(), Param::Default, &source3_0_flags_default } }, g_qvoid },
			{ t, "sourcedepth", Address(), two_BlockFilter_sourcedepth, { { "texture", type<two::Texture>(),  }, { "flags", type<uint32_t>(), Param::Default, &sourcedepth_0_flags_default } }, g_qvoid },
			{ t, "uniform", Address(), two_BlockFilter_uniform, { { "pass", type<two::Pass>(),  }, { "name", type<stl::string>(),  }, { "value", type<two::vec4>(),  } }, g_qvoid },
			{ t, "uniforms", Address(), two_BlockFilter_uniforms, { { "pass", type<two::Pass>(),  }, { "name", type<stl::string>(),  }, { "values", type<stl::span<float>>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, methods, {}, };
	}
	// two::BlockCopy
	{
		Type& t = type<two::BlockCopy>();
		static Meta meta = { t, &namspc({ "two" }), "BlockCopy", sizeof(two::BlockCopy), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::GfxBlock>() };
		static size_t bases_offsets[] = { base_offset<two::BlockCopy, two::GfxBlock>() };
		// defaults
		static uint64_t submit_0_flags_default = 0U;
		static bool submit_0_render_default = false;
		static uint64_t quad_0_flags_default = 0U;
		static bool quad_0_render_default = false;
		static int debug_show_texture_0_level_default = 0;
		static int debug_show_texturep_0_level_default = 0;
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "submit", Address(), two_BlockCopy_submit, { { "pass", type<two::Pass>(),  }, { "fbo", type<two::FrameBuffer>(),  }, { "texture", type<two::Texture>(),  }, { "quad", type<two::RenderQuad>(),  }, { "flags", type<uint64_t>(), Param::Default, &submit_0_flags_default }, { "render", type<bool>(), Param::Default, &submit_0_render_default } }, g_qvoid },
			{ t, "quad", Address(), two_BlockCopy_quad, { { "pass", type<two::Pass>(),  }, { "fbo", type<two::FrameBuffer>(),  }, { "texture", type<two::Texture>(),  }, { "flags", type<uint64_t>(), Param::Default, &quad_0_flags_default }, { "render", type<bool>(), Param::Default, &quad_0_render_default } }, g_qvoid },
			{ t, "debug_show_texture", Address(), two_BlockCopy_debug_show_texture, { { "render", type<two::Render>(),  }, { "texture", type<two::Texture>(),  }, { "rect", type<two::vec4>(),  }, { "level", type<int>(), Param::Default, &debug_show_texture_0_level_default } }, g_qvoid },
			{ t, "debug_show_texturep", Address(), two_BlockCopy_debug_show_texturep, { { "render", type<two::Render>(),  }, { "texture", type<two::Texture>(), Param::Nullable }, { "rect", type<two::vec4>(),  }, { "level", type<int>(), Param::Default, &debug_show_texturep_0_level_default } }, g_qvoid }
		};
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, methods, {}, };
	}
	// two::ClusteredFrustum
	{
		Type& t = type<two::ClusteredFrustum>();
		static Meta meta = { t, &namspc({ "two" }), "ClusteredFrustum", sizeof(two::ClusteredFrustum), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Frustum>() };
		static size_t bases_offsets[] = { base_offset<two::ClusteredFrustum, two::Frustum>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_ClusteredFrustum__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_ClusteredFrustum__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, {}, {}, {}, };
	}
	// two::Light
	{
		Type& t = type<two::Light>();
		static Meta meta = { t, &namspc({ "two" }), "Light", sizeof(two::Light), TypeClass::Object };
		// bases
		// defaults
		static two::Node3* node_default = nullptr;
		static two::LightType type_default = two::LightType::Point;
		static bool visible_default = true;
		static two::Colour colour_default = two::Colour::White;
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
		static two::LightType construct_0_type_default = two::LightType::Point;
		static bool construct_0_shadows_default = false;
		static two::Colour construct_0_colour_default = two::Colour::White;
		static float construct_0_energy_default = 1.f;
		static float construct_0_range_default = 1.f;
		// constructors
		static Constructor constructors[] = {
			{ t, two_Light__construct_0, { { "node", type<two::Node3>(),  }, { "type", type<two::LightType>(), Param::Default, &construct_0_type_default }, { "shadows", type<bool>(), Param::Default, &construct_0_shadows_default }, { "colour", type<two::Colour>(), Param::Default, &construct_0_colour_default }, { "energy", type<float>(), Param::Default, &construct_0_energy_default }, { "range", type<float>(), Param::Default, &construct_0_range_default } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::Light, m_node), type<two::Node3>(), "node", node_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::Light, m_type), type<two::LightType>(), "type", &type_default, Member::Value, nullptr },
			{ t, offsetof(two::Light, m_visible), type<bool>(), "visible", &visible_default, Member::Value, nullptr },
			{ t, offsetof(two::Light, m_colour), type<two::Colour>(), "colour", &colour_default, Member::Value, nullptr },
			{ t, offsetof(two::Light, m_range), type<float>(), "range", &range_default, Member::Value, nullptr },
			{ t, offsetof(two::Light, m_energy), type<float>(), "energy", &energy_default, Member::Value, nullptr },
			{ t, offsetof(two::Light, m_specular), type<float>(), "specular", &specular_default, Member::Value, nullptr },
			{ t, offsetof(two::Light, m_attenuation), type<float>(), "attenuation", &attenuation_default, Member::Value, nullptr },
			{ t, offsetof(two::Light, m_shadows), type<bool>(), "shadows", &shadows_default, Member::Value, nullptr },
			{ t, offsetof(two::Light, m_shadow_range), type<float>(), "shadow_range", &shadow_range_default, Member::Value, nullptr },
			{ t, offsetof(two::Light, m_layers), type<uint32_t>(), "layers", &layers_default, Member::Value, nullptr },
			{ t, offsetof(two::Light, m_last_render), type<uint32_t>(), "last_render", &last_render_default, Member::Value, nullptr },
			{ t, offsetof(two::Light, m_last_update), type<uint32_t>(), "last_update", &last_update_default, Member::Value, nullptr },
			{ t, offsetof(two::Light, m_spot_angle), type<float>(), "spot_angle", &spot_angle_default, Member::Value, nullptr },
			{ t, offsetof(two::Light, m_spot_attenuation), type<float>(), "spot_attenuation", &spot_attenuation_default, Member::Value, nullptr },
			{ t, offsetof(two::Light, m_shadow_flags), type<two::ShadowFlags>(), "shadow_flags", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Light, m_shadow_num_splits), type<uint8_t>(), "shadow_nusplits", &shadow_nusplits_default, Member::Value, nullptr },
			{ t, offsetof(two::Light, m_shadow_split_distribution), type<float>(), "shadow_split_distribution", &shadow_split_distribution_default, Member::Value, nullptr },
			{ t, offsetof(two::Light, m_shadow_normal_bias), type<float>(), "shadow_normal_bias", &shadow_normal_bias_default, Member::Value, nullptr },
			{ t, offsetof(two::Light, m_shadow_bias), type<float>(), "shadow_bias", &shadow_bias_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, {}, members, {}, {}, };
	}
	// two::Gnode
	{
		Type& t = type<two::Gnode>();
		static Meta meta = { t, &namspc({ "two" }), "Gnode", sizeof(two::Gnode), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::TPool<two::Node3>
	{
		Type& t = type<two::TPool<two::Node3>>();
		static Meta meta = { t, &namspc({ "two" }), "TPool<two::Node3>", sizeof(two::TPool<two::Node3>), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "add", Address(), two_TPool_two_Node3_add, { { "value", type<two::Node3>(),  } }, { &type<two::Node3>(), QualType::None } },
			{ t, "addvec", Address(), two_TPool_two_Node3_addvec, { { "values", type<stl::span<two::Node3>>(),  } }, { &type<stl::span<two::Node3>>(), QualType::None } },
			{ t, "talloc", Address(), two_TPool_two_Node3_talloc, {}, { &type<two::Node3>(), QualType::None } },
			{ t, "tdestroy", Address(), two_TPool_two_Node3_tdestroy, { { "object", type<two::Node3>(),  } }, g_qvoid },
			{ t, "tfree", Address(), two_TPool_two_Node3_tfree, { { "object", type<two::Node3>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, methods, {}, };
	}
	// two::TPool<two::Item>
	{
		Type& t = type<two::TPool<two::Item>>();
		static Meta meta = { t, &namspc({ "two" }), "TPool<two::Item>", sizeof(two::TPool<two::Item>), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "add", Address(), two_TPool_two_Item_add, { { "value", type<two::Item>(),  } }, { &type<two::Item>(), QualType::None } },
			{ t, "addvec", Address(), two_TPool_two_Item_addvec, { { "values", type<stl::span<two::Item>>(),  } }, { &type<stl::span<two::Item>>(), QualType::None } },
			{ t, "talloc", Address(), two_TPool_two_Item_talloc, {}, { &type<two::Item>(), QualType::None } },
			{ t, "tdestroy", Address(), two_TPool_two_Item_tdestroy, { { "object", type<two::Item>(),  } }, g_qvoid },
			{ t, "tfree", Address(), two_TPool_two_Item_tfree, { { "object", type<two::Item>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, methods, {}, };
	}
	// two::TPool<two::Batch>
	{
		Type& t = type<two::TPool<two::Batch>>();
		static Meta meta = { t, &namspc({ "two" }), "TPool<two::Batch>", sizeof(two::TPool<two::Batch>), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "add", Address(), two_TPool_two_Batch_add, { { "value", type<two::Batch>(),  } }, { &type<two::Batch>(), QualType::None } },
			{ t, "addvec", Address(), two_TPool_two_Batch_addvec, { { "values", type<stl::span<two::Batch>>(),  } }, { &type<stl::span<two::Batch>>(), QualType::None } },
			{ t, "talloc", Address(), two_TPool_two_Batch_talloc, {}, { &type<two::Batch>(), QualType::None } },
			{ t, "tdestroy", Address(), two_TPool_two_Batch_tdestroy, { { "object", type<two::Batch>(),  } }, g_qvoid },
			{ t, "tfree", Address(), two_TPool_two_Batch_tfree, { { "object", type<two::Batch>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, methods, {}, };
	}
	// two::TPool<two::Direct>
	{
		Type& t = type<two::TPool<two::Direct>>();
		static Meta meta = { t, &namspc({ "two" }), "TPool<two::Direct>", sizeof(two::TPool<two::Direct>), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "add", Address(), two_TPool_two_Direct_add, { { "value", type<two::Direct>(),  } }, { &type<two::Direct>(), QualType::None } },
			{ t, "addvec", Address(), two_TPool_two_Direct_addvec, { { "values", type<stl::span<two::Direct>>(),  } }, { &type<stl::span<two::Direct>>(), QualType::None } },
			{ t, "talloc", Address(), two_TPool_two_Direct_talloc, {}, { &type<two::Direct>(), QualType::None } },
			{ t, "tdestroy", Address(), two_TPool_two_Direct_tdestroy, { { "object", type<two::Direct>(),  } }, g_qvoid },
			{ t, "tfree", Address(), two_TPool_two_Direct_tfree, { { "object", type<two::Direct>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, methods, {}, };
	}
	// two::TPool<two::Mime>
	{
		Type& t = type<two::TPool<two::Mime>>();
		static Meta meta = { t, &namspc({ "two" }), "TPool<two::Mime>", sizeof(two::TPool<two::Mime>), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "add", Address(), two_TPool_two_Mime_add, { { "value", type<two::Mime>(),  } }, { &type<two::Mime>(), QualType::None } },
			{ t, "addvec", Address(), two_TPool_two_Mime_addvec, { { "values", type<stl::span<two::Mime>>(),  } }, { &type<stl::span<two::Mime>>(), QualType::None } },
			{ t, "talloc", Address(), two_TPool_two_Mime_talloc, {}, { &type<two::Mime>(), QualType::None } },
			{ t, "tdestroy", Address(), two_TPool_two_Mime_tdestroy, { { "object", type<two::Mime>(),  } }, g_qvoid },
			{ t, "tfree", Address(), two_TPool_two_Mime_tfree, { { "object", type<two::Mime>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, methods, {}, };
	}
	// two::TPool<two::Light>
	{
		Type& t = type<two::TPool<two::Light>>();
		static Meta meta = { t, &namspc({ "two" }), "TPool<two::Light>", sizeof(two::TPool<two::Light>), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "add", Address(), two_TPool_two_Light_add, { { "value", type<two::Light>(),  } }, { &type<two::Light>(), QualType::None } },
			{ t, "addvec", Address(), two_TPool_two_Light_addvec, { { "values", type<stl::span<two::Light>>(),  } }, { &type<stl::span<two::Light>>(), QualType::None } },
			{ t, "talloc", Address(), two_TPool_two_Light_talloc, {}, { &type<two::Light>(), QualType::None } },
			{ t, "tdestroy", Address(), two_TPool_two_Light_tdestroy, { { "object", type<two::Light>(),  } }, g_qvoid },
			{ t, "tfree", Address(), two_TPool_two_Light_tfree, { { "object", type<two::Light>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, methods, {}, };
	}
	// two::TPool<two::Flare>
	{
		Type& t = type<two::TPool<two::Flare>>();
		static Meta meta = { t, &namspc({ "two" }), "TPool<two::Flare>", sizeof(two::TPool<two::Flare>), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "add", Address(), two_TPool_two_Flare_add, { { "value", type<two::Flare>(),  } }, { &type<two::Flare>(), QualType::None } },
			{ t, "addvec", Address(), two_TPool_two_Flare_addvec, { { "values", type<stl::span<two::Flare>>(),  } }, { &type<stl::span<two::Flare>>(), QualType::None } },
			{ t, "talloc", Address(), two_TPool_two_Flare_talloc, {}, { &type<two::Flare>(), QualType::None } },
			{ t, "tdestroy", Address(), two_TPool_two_Flare_tdestroy, { { "object", type<two::Flare>(),  } }, g_qvoid },
			{ t, "tfree", Address(), two_TPool_two_Flare_tfree, { { "object", type<two::Flare>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, methods, {}, };
	}
	// two::Culler
	{
		Type& t = type<two::Culler>();
		static Meta meta = { t, &namspc({ "two" }), "Culler", sizeof(two::Culler), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::Culler, m_viewport), type<two::Viewport>(), "viewport", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// two::Viewport
	{
		Type& t = type<two::Viewport>();
		static Meta meta = { t, &namspc({ "two" }), "Viewport", sizeof(two::Viewport), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::OEntt>() };
		static size_t bases_offsets[] = { base_offset<two::Viewport, two::OEntt>() };
		// defaults
		static uint16_t index_default = 0;
		static bool autorender_default = true;
		static bool autoflip_default = false;
		static bool scissor_default = false;
		static two::Colour clear_colour_default = two::Colour::Black;
		static two::Shading shading_default = two::Shading::Shaded;
		static two::Lighting lighting_default = two::Lighting::Clustered;
		static bool clustered_default = false;
		static bool to_gamma_default = false;
		static two::vec4 construct_1_rect_default = vec4(0.f);
		static bool construct_1_scissor_default = false;
		// constructors
		static Constructor constructors[] = {
			{ t, two_Viewport__construct_0, {} },
			{ t, two_Viewport__construct_1, { { "camera", type<two::Camera>(),  }, { "scene", type<two::Scene>(),  }, { "rect", type<two::vec4>(), Param::Default, &construct_1_rect_default }, { "scissor", type<bool>(), Param::Default, &construct_1_scissor_default } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::Viewport, m_camera), type<two::Camera>(), "camera", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::Viewport, m_scene), type<two::Scene>(), "scene", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::Viewport, m_index), type<uint16_t>(), "index", &index_default, Member::Value, nullptr },
			{ t, offsetof(two::Viewport, m_autorender), type<bool>(), "autorender", &autorender_default, Member::Value, nullptr },
			{ t, offsetof(two::Viewport, m_autoflip), type<bool>(), "autoflip", &autoflip_default, Member::Value, nullptr },
			{ t, offsetof(two::Viewport, m_rect), type<two::vec4>(), "rect", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Viewport, m_scissor), type<bool>(), "scissor", &scissor_default, Member::Value, nullptr },
			{ t, offsetof(two::Viewport, m_clear_colour), type<two::Colour>(), "clear_colour", &clear_colour_default, Member::Value, nullptr },
			{ t, offsetof(two::Viewport, m_shading), type<two::Shading>(), "shading", &shading_default, Member::Value, nullptr },
			{ t, offsetof(two::Viewport, m_lighting), type<two::Lighting>(), "lighting", &lighting_default, Member::Value, nullptr },
			{ t, offsetof(two::Viewport, m_clustered), type<bool>(), "clustered", &clustered_default, Member::Value, nullptr },
			{ t, offsetof(two::Viewport, m_to_gamma), type<bool>(), "to_gamma", &to_gamma_default, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "cull", Address(), two_Viewport_cull, { { "render", type<two::Render>(),  } }, g_qvoid },
			{ t, "render", Address(), two_Viewport_render, { { "render", type<two::Render>(),  } }, g_qvoid },
			{ t, "set_clustered", Address(), two_Viewport_set_clustered, { { "gfx", type<two::GfxSystem>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, {}, members, methods, {}, };
	}
	// two::RenderQuad
	{
		Type& t = type<two::RenderQuad>();
		static Meta meta = { t, &namspc({ "two" }), "RenderQuad", sizeof(two::RenderQuad), TypeClass::Struct };
		// bases
		// defaults
		static two::vec4 source_default = vec4(vec2(0.f),vec2(1.f));
		static two::vec4 dest_default = vec4(vec2(0.f),vec2(1.f));
		static bool fbo_flip_default = false;
		static bool relative_default = false;
		static bool construct_1_fbo_flip_default = false;
		static bool construct_1_relative_default = false;
		static bool construct_2_fbo_flip_default = false;
		static bool construct_2_relative_default = false;
		// constructors
		static Constructor constructors[] = {
			{ t, two_RenderQuad__construct_0, {} },
			{ t, two_RenderQuad__construct_1, { { "crop", type<two::vec4>(),  }, { "dest", type<two::vec4>(),  }, { "fbo_flip", type<bool>(), Param::Default, &construct_1_fbo_flip_default }, { "relative", type<bool>(), Param::Default, &construct_1_relative_default } } },
			{ t, two_RenderQuad__construct_2, { { "rect", type<two::vec4>(),  }, { "fbo_flip", type<bool>(), Param::Default, &construct_2_fbo_flip_default }, { "relative", type<bool>(), Param::Default, &construct_2_relative_default } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_RenderQuad__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::RenderQuad, m_source), type<two::vec4>(), "source", &source_default, Member::Value, nullptr },
			{ t, offsetof(two::RenderQuad, m_dest), type<two::vec4>(), "dest", &dest_default, Member::Value, nullptr },
			{ t, offsetof(two::RenderQuad, m_fbo_flip), type<bool>(), "fbo_flip", &fbo_flip_default, Member::Value, nullptr },
			{ t, offsetof(two::RenderQuad, m_relative), type<bool>(), "relative", &relative_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::FrameBuffer
	{
		Type& t = type<two::FrameBuffer>();
		static Meta meta = { t, &namspc({ "two" }), "FrameBuffer", sizeof(two::FrameBuffer), TypeClass::Object };
		// bases
		// defaults
		static uint64_t construct_1_flags_default = 0U;
		// constructors
		static Constructor constructors[] = {
			{ t, two_FrameBuffer__construct_0, {} },
			{ t, two_FrameBuffer__construct_1, { { "size", type<two::uvec2>(),  }, { "format", type<two::TextureFormat>(),  }, { "flags", type<uint64_t>(), Param::Default, &construct_1_flags_default } } },
			{ t, two_FrameBuffer__construct_2, { { "size", type<two::uvec2>(),  }, { "textures", type<stl::span<two::Texture*>>(),  } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::FrameBuffer, m_size), type<two::uvec2>(), "size", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::FrameBuffer, m_tex), type<two::Texture>(), "tex", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "valid", Address(), two_FrameBuffer_valid, {}, { &type<bool>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, members, methods, {}, };
	}
	// two::SwapBuffer
	{
		Type& t = type<two::SwapBuffer>();
		static Meta meta = { t, &namspc({ "two" }), "SwapBuffer", sizeof(two::SwapBuffer), TypeClass::Object };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_SwapBuffer__construct_0, {} }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::SwapBuffer, m_one), type<two::FrameBuffer>(), "one", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::SwapBuffer, m_two), type<two::FrameBuffer>(), "two", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "create", Address(), two_SwapBuffer_create, { { "size", type<two::uvec2>(),  }, { "color_format", type<two::TextureFormat>(),  } }, g_qvoid },
			{ t, "swap", Address(), two_SwapBuffer_swap, {}, { &type<two::FrameBuffer>(), QualType::None } },
			{ t, "current", Address(), two_SwapBuffer_current, {}, { &type<two::FrameBuffer>(), QualType::None } },
			{ t, "last", Address(), two_SwapBuffer_last, {}, { &type<two::Texture>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, members, methods, {}, };
	}
	// two::Cascade
	{
		Type& t = type<two::Cascade>();
		static Meta meta = { t, &namspc({ "two" }), "Cascade", sizeof(two::Cascade), TypeClass::Object };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Cascade__construct_0, {} }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::Cascade, m_texture), type<two::Texture>(), "texture", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::Cascade, m_num_mips), type<size_t>(), "numips", nullptr, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "create", Address(), two_Cascade_create, { { "size", type<two::uvec2>(),  }, { "color_format", type<two::TextureFormat>(),  } }, g_qvoid },
			{ t, "level", Address(), two_Cascade_level, { { "index", type<uint8_t>(),  } }, { &type<two::FrameBuffer>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, members, methods, {}, };
	}
	// two::SwapCascade
	{
		Type& t = type<two::SwapCascade>();
		static Meta meta = { t, &namspc({ "two" }), "SwapCascade", sizeof(two::SwapCascade), TypeClass::Object };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_SwapCascade__construct_0, {} }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::SwapCascade, m_one), type<two::Cascade>(), "one", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::SwapCascade, m_two), type<two::Cascade>(), "two", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "create", Address(), two_SwapCascade_create, { { "size", type<two::uvec2>(),  }, { "color_format", type<two::TextureFormat>(),  } }, g_qvoid },
			{ t, "swap", Address(), two_SwapCascade_swap, {}, { &type<two::Cascade>(), QualType::None } },
			{ t, "last", Address(), two_SwapCascade_last, {}, { &type<two::Cascade>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, members, methods, {}, };
	}
	// two::RenderTarget
	{
		Type& t = type<two::RenderTarget>();
		static Meta meta = { t, &namspc({ "two" }), "RenderTarget", sizeof(two::RenderTarget), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::FrameBuffer>() };
		static size_t bases_offsets[] = { base_offset<two::RenderTarget, two::FrameBuffer>() };
		// defaults
		static two::MSAA msaa_default = two::MSAA::Disabled;
		static bool mrt_default = true;
		static bool deferred_default = false;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::RenderTarget, m_backbuffer), type<two::FrameBuffer>(), "backbuffer", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::RenderTarget, m_msaa), type<two::MSAA>(), "msaa", &msaa_default, Member::Value, nullptr },
			{ t, offsetof(two::RenderTarget, m_mrt), type<bool>(), "mrt", &mrt_default, Member::Value, nullptr },
			{ t, offsetof(two::RenderTarget, m_depth), type<two::Texture>(), "depth", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::RenderTarget, m_diffuse), type<two::Texture>(), "diffuse", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::RenderTarget, m_specular), type<two::Texture>(), "specular", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::RenderTarget, m_normal_rough), type<two::Texture>(), "normal_rough", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::RenderTarget, m_sss), type<two::Texture>(), "sss", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::RenderTarget, m_ping_pong), type<two::SwapBuffer>(), "ping_pong", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::RenderTarget, m_post), type<two::SwapBuffer>(), "post", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::RenderTarget, m_cascade), type<two::Cascade>(), "cascade", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::RenderTarget, m_swap_cascade), type<two::SwapCascade>(), "swap_cascade", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::RenderTarget, m_deferred), type<bool>(), "deferred", &deferred_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, members, {}, {}, };
	}
	// two::Sun
	{
		Type& t = type<two::Sun>();
		static Meta meta = { t, &namspc({ "two" }), "Sun", sizeof(two::Sun), TypeClass::Struct };
		// bases
		// defaults
		static two::Colour colour_default = {0.8f,0.8f,0.0f};
		static float intensity_default = 0.f;
		// constructors
		static Constructor constructors[] = {
			{ t, two_Sun__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Sun__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Sun, azimuth), type<float>(), "azimuth", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Sun, elevation), type<float>(), "elevation", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Sun, m_colour), type<two::Colour>(), "colour", &colour_default, Member::Value, nullptr },
			{ t, offsetof(two::Sun, m_intensity), type<float>(), "intensity", &intensity_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Radiance
	{
		Type& t = type<two::Radiance>();
		static Meta meta = { t, &namspc({ "two" }), "Radiance", sizeof(two::Radiance), TypeClass::Struct };
		// bases
		// defaults
		static two::Colour colour_default = two::Colour::White;
		static float energy_default = 1.0f;
		static two::Colour ambient_default = two::Colour::Black;
		static two::Texture* texture_default = nullptr;
		static two::Texture* filtered_default = nullptr;
		static bool filter_default = true;
		// constructors
		static Constructor constructors[] = {
			{ t, two_Radiance__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Radiance__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Radiance, m_colour), type<two::Colour>(), "colour", &colour_default, Member::Value, nullptr },
			{ t, offsetof(two::Radiance, m_energy), type<float>(), "energy", &energy_default, Member::Value, nullptr },
			{ t, offsetof(two::Radiance, m_ambient), type<two::Colour>(), "ambient", &ambient_default, Member::Value, nullptr },
			{ t, offsetof(two::Radiance, m_texture), type<two::Texture>(), "texture", texture_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::Radiance, m_filtered), type<two::Texture>(), "filtered", filtered_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::Radiance, m_filter), type<bool>(), "filter", &filter_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Background
	{
		Type& t = type<two::Background>();
		static Meta meta = { t, &namspc({ "two" }), "Background", sizeof(two::Background), TypeClass::Struct };
		// bases
		// defaults
		static two::BackgroundMode mode_default = two::BackgroundMode::None;
		static two::Colour colour_default = two::Colour::Black;
		static two::Program* custoprogram_default = nullptr;
		static two::Texture* texture_default = nullptr;
		// constructors
		static Constructor constructors[] = {
			{ t, two_Background__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Background__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Background, m_mode), type<two::BackgroundMode>(), "mode", &mode_default, Member::Value, nullptr },
			{ t, offsetof(two::Background, m_colour), type<two::Colour>(), "colour", &colour_default, Member::Value, nullptr },
			{ t, offsetof(two::Background, m_custom_program), type<two::Program>(), "custoprogram", custoprogram_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::Background, m_texture), type<two::Texture>(), "texture", texture_default, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Skylight
	{
		Type& t = type<two::Skylight>();
		static Meta meta = { t, &namspc({ "two" }), "Skylight", sizeof(two::Skylight), TypeClass::Struct };
		// bases
		// defaults
		static bool enabled_default = false;
		static float intensity_default = 1.f;
		static two::vec3 position_default = vec3(0.f,1.f,0.f);
		// constructors
		static Constructor constructors[] = {
			{ t, two_Skylight__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Skylight__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Skylight, m_enabled), type<bool>(), "enabled", &enabled_default, Member::Value, nullptr },
			{ t, offsetof(two::Skylight, m_intensity), type<float>(), "intensity", &intensity_default, Member::Value, nullptr },
			{ t, offsetof(two::Skylight, m_position), type<two::vec3>(), "position", &position_default, Member::Value, nullptr },
			{ t, offsetof(two::Skylight, m_direction), type<two::vec3>(), "direction", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Skylight, m_color), type<two::Colour>(), "color", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Skylight, m_ground), type<two::Colour>(), "ground", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Fog
	{
		Type& t = type<two::Fog>();
		static Meta meta = { t, &namspc({ "two" }), "Fog", sizeof(two::Fog), TypeClass::Struct };
		// bases
		// defaults
		static bool enabled_default = false;
		static float density_default = 0.01f;
		static two::Colour colour_default = two::Colour::White;
		static bool depth_default = false;
		static float depth_begin_default = 0.f;
		static float depth_end_default = 0.f;
		static float depth_curve_default = 1.f;
		static bool height_default = false;
		static float height_min_default = 0.f;
		static float height_max_default = 1.f;
		static float height_curve_default = 0.1f;
		static bool transmit_default = false;
		static float transmit_curve_default = 1.f;
		// constructors
		static Constructor constructors[] = {
			{ t, two_Fog__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Fog__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Fog, m_enabled), type<bool>(), "enabled", &enabled_default, Member::Value, nullptr },
			{ t, offsetof(two::Fog, m_density), type<float>(), "density", &density_default, Member::Value, nullptr },
			{ t, offsetof(two::Fog, m_colour), type<two::Colour>(), "colour", &colour_default, Member::Value, nullptr },
			{ t, offsetof(two::Fog, m_depth), type<bool>(), "depth", &depth_default, Member::Value, nullptr },
			{ t, offsetof(two::Fog, m_depth_begin), type<float>(), "depth_begin", &depth_begin_default, Member::Value, nullptr },
			{ t, offsetof(two::Fog, m_depth_end), type<float>(), "depth_end", &depth_end_default, Member::Value, nullptr },
			{ t, offsetof(two::Fog, m_depth_curve), type<float>(), "depth_curve", &depth_curve_default, Member::Value, nullptr },
			{ t, offsetof(two::Fog, m_height), type<bool>(), "height", &height_default, Member::Value, nullptr },
			{ t, offsetof(two::Fog, m_height_min), type<float>(), "height_min", &height_min_default, Member::Value, nullptr },
			{ t, offsetof(two::Fog, m_height_max), type<float>(), "height_max", &height_max_default, Member::Value, nullptr },
			{ t, offsetof(two::Fog, m_height_curve), type<float>(), "height_curve", &height_curve_default, Member::Value, nullptr },
			{ t, offsetof(two::Fog, m_transmit), type<bool>(), "transmit", &transmit_default, Member::Value, nullptr },
			{ t, offsetof(two::Fog, m_transmit_curve), type<float>(), "transmit_curve", &transmit_curve_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Zone
	{
		Type& t = type<two::Zone>();
		static Meta meta = { t, &namspc({ "two" }), "Zone", sizeof(two::Zone), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Zone__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Zone__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Zone, m_background), type<two::Background>(), "background", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Zone, m_radiance), type<two::Radiance>(), "radiance", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Zone, m_sun), type<two::Sun>(), "sun", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Zone, m_skylight), type<two::Skylight>(), "skylight", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Zone, m_fog), type<two::Fog>(), "fog", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Scene
	{
		Type& t = type<two::Scene>();
		static Meta meta = { t, &namspc({ "two" }), "Scene", sizeof(two::Scene), TypeClass::Object };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Scene__construct_0, { { "gfx", type<two::GfxSystem>(),  } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::Scene, m_index), type<uint32_t>(), "index", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Scene, m_graph), type<two::Gnode>(), "graph", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::Scene, m_root_node), type<two::Node3>(), "root_node", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::Scene, m_env), type<two::Zone>(), "env", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Scene, m_user), type<two::Ref>(), "user", nullptr, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "begin", Address(), two_Scene_begin, {}, { &type<two::Gnode>(), QualType::None } },
			{ t, "update", Address(), two_Scene_update, {}, g_qvoid },
			{ t, "nodes", Address(), two_Scene_nodes, {}, { &type<two::TPool<two::Node3>>(), QualType::None } },
			{ t, "items", Address(), two_Scene_items, {}, { &type<two::TPool<two::Item>>(), QualType::None } },
			{ t, "batches", Address(), two_Scene_batches, {}, { &type<two::TPool<two::Batch>>(), QualType::None } },
			{ t, "directs", Address(), two_Scene_directs, {}, { &type<two::TPool<two::Direct>>(), QualType::None } },
			{ t, "mimes", Address(), two_Scene_mimes, {}, { &type<two::TPool<two::Mime>>(), QualType::None } },
			{ t, "lights", Address(), two_Scene_lights, {}, { &type<two::TPool<two::Light>>(), QualType::None } },
			{ t, "flares", Address(), two_Scene_flares, {}, { &type<two::TPool<two::Flare>>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, members, methods, {}, };
	}
	// two::BlockSky
	{
		Type& t = type<two::BlockSky>();
		static Meta meta = { t, &namspc({ "two" }), "BlockSky", sizeof(two::BlockSky), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::GfxBlock>() };
		static size_t bases_offsets[] = { base_offset<two::BlockSky, two::GfxBlock>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	
	
		m.m_types.push_back(&type<stl::span<two::mat4>>());
		m.m_types.push_back(&type<stl::span<two::Node3>>());
		m.m_types.push_back(&type<stl::span<two::Item>>());
		m.m_types.push_back(&type<stl::span<two::Batch>>());
		m.m_types.push_back(&type<stl::span<two::Direct>>());
		m.m_types.push_back(&type<stl::span<two::Mime>>());
		m.m_types.push_back(&type<stl::span<two::Light>>());
		m.m_types.push_back(&type<stl::span<two::Flare>>());
		m.m_types.push_back(&type<stl::span<two::Texture*>>());
		m.m_types.push_back(&type<stl::vector<two::Mesh*>>());
		m.m_types.push_back(&type<stl::vector<two::Model*>>());
		m.m_types.push_back(&type<stl::vector<two::Texture*>>());
		m.m_types.push_back(&type<stl::vector<two::Material*>>());
		m.m_types.push_back(&type<stl::vector<two::Animation*>>());
		m.m_types.push_back(&type<stl::vector<two::AnimPlay>>());
		m.m_types.push_back(&type<two::Node3>());
		m.m_types.push_back(&type<two::AnimTarget>());
		m.m_types.push_back(&type<two::Interpolation>());
		m.m_types.push_back(&type<two::AnimTrack>());
		m.m_types.push_back(&type<two::Animation>());
		m.m_types.push_back(&type<two::TextureHint>());
		m.m_types.push_back(&type<two::TextureFormat>());
		m.m_types.push_back(&type<two::Texture>());
		m.m_types.push_back(&type<two::Skeleton>());
		m.m_types.push_back(&type<two::Joint>());
		m.m_types.push_back(&type<two::Skin>());
		m.m_types.push_back(&type<two::Rig>());
		m.m_types.push_back(&type<two::AnimNode>());
		m.m_types.push_back(&type<two::AnimPlay>());
		m.m_types.push_back(&type<two::Mime>());
		m.m_types.push_back(&type<two::Frustum>());
		m.m_types.push_back(&type<two::FrustumSlice>());
		m.m_types.push_back(&type<two::ShaderType>());
		m.m_types.push_back(&type<two::PassType>());
		m.m_types.push_back(&type<two::ShaderDefine>());
		m.m_types.push_back(&type<two::ShaderBlock>());
		m.m_types.push_back(&type<two::ProgramMode>());
		m.m_types.push_back(&type<two::ProgramBlock>());
		m.m_types.push_back(&type<two::MaterialBlock>());
		m.m_types.push_back(&type<two::Program>());
		m.m_types.push_back(&type<two::ProgramVersion>());
		m.m_types.push_back(&type<two::Shot>());
		m.m_types.push_back(&type<two::TextureSampler>());
		m.m_types.push_back(&type<two::Lighting>());
		m.m_types.push_back(&type<two::Pass>());
		m.m_types.push_back(&type<two::RenderFrame>());
		m.m_types.push_back(&type<two::Render>());
		m.m_types.push_back(&type<two::GfxBlock>());
		m.m_types.push_back(&type<two::DrawBlock>());
		m.m_types.push_back(&type<two::Renderer>());
		m.m_types.push_back(&type<two::GfxWindow>());
		m.m_types.push_back(&type<two::GfxSystem>());
		m.m_types.push_back(&type<two::BlendMode>());
		m.m_types.push_back(&type<two::CullMode>());
		m.m_types.push_back(&type<two::DepthDraw>());
		m.m_types.push_back(&type<two::DepthTest>());
		m.m_types.push_back(&type<two::MaterialFlag>());
		m.m_types.push_back(&type<two::ShaderColor>());
		m.m_types.push_back(&type<two::TextureChannel>());
		m.m_types.push_back(&type<two::MaterialParam<two::Colour>>());
		m.m_types.push_back(&type<two::MaterialParam<float>>());
		m.m_types.push_back(&type<two::MaterialParam<two::vec4>>());
		m.m_types.push_back(&type<two::MaterialBase>());
		m.m_types.push_back(&type<two::MaterialUser>());
		m.m_types.push_back(&type<two::MaterialAlpha>());
		m.m_types.push_back(&type<two::MaterialSolid>());
		m.m_types.push_back(&type<two::MaterialPoint>());
		m.m_types.push_back(&type<two::MaterialLine>());
		m.m_types.push_back(&type<two::MaterialFresnel>());
		m.m_types.push_back(&type<two::PbrDiffuseMode>());
		m.m_types.push_back(&type<two::PbrSpecularMode>());
		m.m_types.push_back(&type<two::MaterialLit>());
		m.m_types.push_back(&type<two::MaterialPbr>());
		m.m_types.push_back(&type<two::PhongEnvBlendMode>());
		m.m_types.push_back(&type<two::MaterialPhong>());
		m.m_types.push_back(&type<two::BlockMaterial>());
		m.m_types.push_back(&type<two::Material>());
		m.m_types.push_back(&type<two::ModelElem>());
		m.m_types.push_back(&type<two::Model>());
		m.m_types.push_back(&type<two::EmitterFlow>());
		m.m_types.push_back(&type<two::Flow>());
		m.m_types.push_back(&type<two::Flare>());
		m.m_types.push_back(&type<two::BlockParticles>());
		m.m_types.push_back(&type<two::ItemShadow>());
		m.m_types.push_back(&type<two::Batch>());
		m.m_types.push_back(&type<two::Item>());
		m.m_types.push_back(&type<two::ModelFormat>());
		m.m_types.push_back(&type<two::ImportConfig>());
		m.m_types.push_back(&type<two::Import>());
		m.m_types.push_back(&type<two::Prefab>());
		m.m_types.push_back(&type<two::AssetStore<two::Texture>>());
		m.m_types.push_back(&type<two::AssetStore<two::Program>>());
		m.m_types.push_back(&type<two::AssetStore<two::Material>>());
		m.m_types.push_back(&type<two::AssetStore<two::Model>>());
		m.m_types.push_back(&type<two::AssetStore<two::Flow>>());
		m.m_types.push_back(&type<two::AssetStore<two::Prefab>>());
		m.m_types.push_back(&type<two::IsometricAngle>());
		m.m_types.push_back(&type<two::Camera>());
		m.m_types.push_back(&type<two::MirrorCamera>());
		m.m_types.push_back(&type<two::DepthMethod>());
		m.m_types.push_back(&type<two::DepthParams>());
		m.m_types.push_back(&type<two::DistanceParams>());
		m.m_types.push_back(&type<two::BlockDepth>());
		m.m_types.push_back(&type<two::GpuMesh>());
		m.m_types.push_back(&type<two::Mesh>());
		m.m_types.push_back(&type<two::Direct>());
		m.m_types.push_back(&type<two::ImmediateDraw>());
		m.m_types.push_back(&type<two::SymbolIndex>());
		m.m_types.push_back(&type<two::Lines>());
		m.m_types.push_back(&type<two::BlockFilter>());
		m.m_types.push_back(&type<two::BlockCopy>());
		m.m_types.push_back(&type<two::ClusteredFrustum>());
		m.m_types.push_back(&type<two::LightType>());
		m.m_types.push_back(&type<two::ShadowFlags>());
		m.m_types.push_back(&type<two::Light>());
		m.m_types.push_back(&type<two::Gnode>());
		m.m_types.push_back(&type<two::TPool<two::Node3>>());
		m.m_types.push_back(&type<two::TPool<two::Item>>());
		m.m_types.push_back(&type<two::TPool<two::Batch>>());
		m.m_types.push_back(&type<two::TPool<two::Direct>>());
		m.m_types.push_back(&type<two::TPool<two::Mime>>());
		m.m_types.push_back(&type<two::TPool<two::Light>>());
		m.m_types.push_back(&type<two::TPool<two::Flare>>());
		m.m_types.push_back(&type<two::Culler>());
		m.m_types.push_back(&type<two::MSAA>());
		m.m_types.push_back(&type<two::Shading>());
		m.m_types.push_back(&type<two::Viewport>());
		m.m_types.push_back(&type<two::RenderQuad>());
		m.m_types.push_back(&type<two::FrameBuffer>());
		m.m_types.push_back(&type<two::SwapBuffer>());
		m.m_types.push_back(&type<two::Cascade>());
		m.m_types.push_back(&type<two::SwapCascade>());
		m.m_types.push_back(&type<two::RenderTarget>());
		m.m_types.push_back(&type<two::Sun>());
		m.m_types.push_back(&type<two::Radiance>());
		m.m_types.push_back(&type<two::BackgroundMode>());
		m.m_types.push_back(&type<two::Background>());
		m.m_types.push_back(&type<two::Skylight>());
		m.m_types.push_back(&type<two::Fog>());
		m.m_types.push_back(&type<two::Zone>());
		m.m_types.push_back(&type<two::Scene>());
		m.m_types.push_back(&type<two::Month>());
		m.m_types.push_back(&type<two::BlockSky>());
		{
			static Function f = { &namspc({ "two" }), "bxidentity", funcptr<two::mat4(*)()>(two::bxidentity), two_bxidentity_0, {}, { &type<two::mat4>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "bxinverse", funcptr<two::mat4(*)(const two::mat4&)>(two::bxinverse), two_bxinverse_1, { { "mat", type<two::mat4>(),  } }, { &type<two::mat4>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "bxSRT", funcptr<two::mat4(*)(const two::vec3&, const two::vec3&, const two::vec3&)>(two::bxSRT), two_bxSRT_2, { { "scale", type<two::vec3>(),  }, { "rot", type<two::vec3>(),  }, { "trans", type<two::vec3>(),  } }, { &type<two::mat4>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "bxscale", funcptr<two::mat4(*)(const two::vec3&)>(two::bxscale), two_bxscale_3, { { "scale", type<two::vec3>(),  } }, { &type<two::mat4>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "bxrotation", funcptr<two::mat4(*)(const two::quat&)>(two::bxrotation), two_bxrotation_4, { { "rot", type<two::quat>(),  } }, { &type<two::mat4>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "bxtranslation", funcptr<two::mat4(*)(const two::vec3&)>(two::bxtranslation), two_bxtranslation_5, { { "vec", type<two::vec3>(),  } }, { &type<two::mat4>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "bxmul", funcptr<two::mat4(*)(const two::mat4&, const two::mat4&)>(two::bxmul), two_bxmul_6, { { "lhs", type<two::mat4>(),  }, { "rhs", type<two::mat4>(),  } }, { &type<two::mat4>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "bxmul", funcptr<two::vec4(*)(const two::mat4&, const two::vec4&)>(two::bxmul), two_bxmul_7, { { "mat", type<two::mat4>(),  }, { "vec", type<two::vec4>(),  } }, { &type<two::vec4>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "bxmul", funcptr<two::vec3(*)(const two::mat4&, const two::vec3&)>(two::bxmul), two_bxmul_8, { { "mat", type<two::mat4>(),  }, { "vec", type<two::vec3>(),  } }, { &type<two::vec3>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "bxmulh", funcptr<two::vec3(*)(const two::mat4&, const two::vec3&)>(two::bxmulh), two_bxmulh_9, { { "mat", type<two::mat4>(),  }, { "vec", type<two::vec3>(),  } }, { &type<two::vec3>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "bxlookat", funcptr<two::mat4(*)(const two::vec3&, const two::vec3&)>(two::bxlookat), two_bxlookat_10, { { "eye", type<two::vec3>(),  }, { "at", type<two::vec3>(),  } }, { &type<two::mat4>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "bxlookat", funcptr<void(*)(two::mat4&, const two::vec3&, const two::vec3&, const two::vec3&)>(two::bxlookat), two_bxlookat_11, { { "result", type<two::mat4>(),  }, { "eye", type<two::vec3>(),  }, { "at", type<two::vec3>(),  }, { "up", type<two::vec3>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "bxlookat", funcptr<two::mat4(*)(const two::vec3&, const two::vec3&, const two::vec3&)>(two::bxlookat), two_bxlookat_12, { { "eye", type<two::vec3>(),  }, { "at", type<two::vec3>(),  }, { "up", type<two::vec3>(),  } }, { &type<two::mat4>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "bxproj", funcptr<two::mat4(*)(float, float, float, float, bool)>(two::bxproj), two_bxproj_13, { { "fov", type<float>(),  }, { "aspect", type<float>(),  }, { "near", type<float>(),  }, { "far", type<float>(),  }, { "oglNdc", type<bool>(),  } }, { &type<two::mat4>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "bxortho", funcptr<two::mat4(*)(const two::vec4&, float, float, float, bool)>(two::bxortho), two_bxortho_14, { { "rect", type<two::vec4>(),  }, { "near", type<float>(),  }, { "far", type<float>(),  }, { "offset", type<float>(),  }, { "oglNdc", type<bool>(),  } }, { &type<two::mat4>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "bxortho", funcptr<two::mat4(*)(float, float, float, float, float, float, float, bool)>(two::bxortho), two_bxortho_15, { { "left", type<float>(),  }, { "right", type<float>(),  }, { "bottom", type<float>(),  }, { "top", type<float>(),  }, { "near", type<float>(),  }, { "far", type<float>(),  }, { "offset", type<float>(),  }, { "oglNdc", type<bool>(),  } }, { &type<two::mat4>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "bxSRT", funcptr<two::mat4(*)(const two::vec3&, const two::quat&, const two::vec3&)>(two::bxSRT), two_bxSRT_16, { { "scale", type<two::vec3>(),  }, { "rot", type<two::quat>(),  }, { "trans", type<two::vec3>(),  } }, { &type<two::mat4>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "bxTRS", funcptr<two::mat4(*)(const two::vec3&, const two::quat&, const two::vec3&)>(two::bxTRS), two_bxTRS_17, { { "scale", type<two::vec3>(),  }, { "rot", type<two::quat>(),  }, { "trans", type<two::vec3>(),  } }, { &type<two::mat4>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static float clipBias_default = 0.f;
			static Function f = { &namspc({ "two" }), "mirror_camera", funcptr<two::MirrorCamera(*)(const two::Camera&, two::Node3&, float)>(two::mirror_camera), two_mirror_camera_18, { { "sourcecam", type<two::Camera>(),  }, { "node", type<two::Node3>(),  }, { "clipBias", type<float>(), Param::Default, &clipBias_default } }, { &type<two::MirrorCamera>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "gfx" }), "setup_pipeline_minimal", funcptr<void(*)(two::GfxSystem&)>(two::gfx::setup_pipeline_minimal), two_gfx_setup_pipeline_minimal_19, { { "gfx", type<two::GfxSystem>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static two::vec3 position_default = vec3(0.f);
			static two::quat rotation_default = ZeroQuat;
			static two::vec3 scale_default = vec3(1.f);
			static Function f = { &namspc({ "two", "gfx" }), "node", funcptr<two::Gnode&(*)(two::Gnode&, const two::vec3&, const two::quat&, const two::vec3&)>(two::gfx::node), two_gfx_node_20, { { "parent", type<two::Gnode>(),  }, { "position", type<two::vec3>(), Param::Default, &position_default }, { "rotation", type<two::quat>(), Param::Default, &rotation_default }, { "scale", type<two::vec3>(), Param::Default, &scale_default } }, { &type<two::Gnode>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static uint32_t flags_default = 0;
			static two::Material* material_default = nullptr;
			static Function f = { &namspc({ "two", "gfx" }), "shape", funcptr<two::Item&(*)(two::Gnode&, const two::Shape&, const two::Symbol&, uint32_t, two::Material*)>(two::gfx::shape), two_gfx_shape_21, { { "parent", type<two::Gnode>(),  }, { "shape", type<two::Shape>(),  }, { "symbol", type<two::Symbol>(),  }, { "flags", type<uint32_t>(), Param::Default, &flags_default }, { "material", type<two::Material>(), Param::Flags(Param::Nullable|Param::Default), &material_default } }, { &type<two::Item>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static uint32_t flags_default = 0;
			static Function f = { &namspc({ "two", "gfx" }), "draw", funcptr<void(*)(two::Gnode&, const two::Shape&, const two::Symbol&, uint32_t)>(two::gfx::draw), two_gfx_draw_22, { { "parent", type<two::Gnode>(),  }, { "shape", type<two::Shape>(),  }, { "symbol", type<two::Symbol>(),  }, { "flags", type<uint32_t>(), Param::Default, &flags_default } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static uint32_t flags_default = 0;
			static two::Material* material_default = nullptr;
			static Function f = { &namspc({ "two", "gfx" }), "sprite", funcptr<two::Item&(*)(two::Gnode&, const two::Image256&, const two::vec2&, uint32_t, two::Material*)>(two::gfx::sprite), two_gfx_sprite_23, { { "parent", type<two::Gnode>(),  }, { "image", type<two::Image256>(),  }, { "size", type<two::vec2>(),  }, { "flags", type<uint32_t>(), Param::Default, &flags_default }, { "material", type<two::Material>(), Param::Flags(Param::Nullable|Param::Default), &material_default } }, { &type<two::Item>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static uint32_t flags_default = 0;
			static two::Material* material_default = nullptr;
			static Function f = { &namspc({ "two", "gfx" }), "item", funcptr<two::Item&(*)(two::Gnode&, const two::Model&, uint32_t, two::Material*)>(two::gfx::item), two_gfx_item_24, { { "parent", type<two::Gnode>(),  }, { "model", type<two::Model>(),  }, { "flags", type<uint32_t>(), Param::Default, &flags_default }, { "material", type<two::Material>(), Param::Flags(Param::Nullable|Param::Default), &material_default } }, { &type<two::Item>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "gfx" }), "batch", funcptr<two::Batch&(*)(two::Gnode&, two::Item&, uint16_t)>(two::gfx::batch), two_gfx_batch_25, { { "parent", type<two::Gnode>(),  }, { "item", type<two::Item>(),  }, { "stride", type<uint16_t>(),  } }, { &type<two::Batch>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static stl::span<two::mat4> transforms_default = {};
			static Function f = { &namspc({ "two", "gfx" }), "instances", funcptr<two::Batch&(*)(two::Gnode&, two::Item&, stl::span<two::mat4>)>(two::gfx::instances), two_gfx_instances_26, { { "parent", type<two::Gnode>(),  }, { "item", type<two::Item>(),  }, { "transforms", type<stl::span<two::mat4>>(), Param::Default, &transforms_default } }, { &type<two::Batch>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool transform_default = true;
			static uint32_t flags_default = 0;
			static two::Material* material_default = nullptr;
			static Function f = { &namspc({ "two", "gfx" }), "prefab", funcptr<void(*)(two::Gnode&, const two::Prefab&, bool, uint32_t, two::Material*)>(two::gfx::prefab), two_gfx_prefab_27, { { "parent", type<two::Gnode>(),  }, { "prefab", type<two::Prefab>(),  }, { "transform", type<bool>(), Param::Default, &transform_default }, { "flags", type<uint32_t>(), Param::Default, &flags_default }, { "material", type<two::Material>(), Param::Flags(Param::Nullable|Param::Default), &material_default } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static uint32_t flags_default = 0;
			static two::Material* material_default = nullptr;
			static Function f = { &namspc({ "two", "gfx" }), "model", funcptr<two::Item*(*)(two::Gnode&, const stl::string&, uint32_t, two::Material*)>(two::gfx::model), two_gfx_model_28, { { "parent", type<two::Gnode>(),  }, { "name", type<stl::string>(),  }, { "flags", type<uint32_t>(), Param::Default, &flags_default }, { "material", type<two::Material>(), Param::Flags(Param::Nullable|Param::Default), &material_default } }, { &type<two::Item>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "gfx" }), "animated", funcptr<two::Mime&(*)(two::Gnode&, two::Item&)>(two::gfx::animated), two_gfx_animated_29, { { "parent", type<two::Gnode>(),  }, { "item", type<two::Item>(),  } }, { &type<two::Mime>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static uint32_t flags_default = 0;
			static Function f = { &namspc({ "two", "gfx" }), "flows", funcptr<two::Flare&(*)(two::Gnode&, const two::Flow&, uint32_t)>(two::gfx::flows), two_gfx_flows_30, { { "parent", type<two::Gnode>(),  }, { "emitter", type<two::Flow>(),  }, { "flags", type<uint32_t>(), Param::Default, &flags_default } }, { &type<two::Flare>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static float range_default = 0.f;
			static float attenuation_default = 0.5f;
			static Function f = { &namspc({ "two", "gfx" }), "light", funcptr<two::Light&(*)(two::Gnode&, two::LightType, bool, two::Colour, float, float)>(two::gfx::light), two_gfx_light_31, { { "parent", type<two::Gnode>(),  }, { "type", type<two::LightType>(),  }, { "shadows", type<bool>(),  }, { "colour", type<two::Colour>(),  }, { "range", type<float>(), Param::Default, &range_default }, { "attenuation", type<float>(), Param::Default, &attenuation_default } }, { &type<two::Light>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "gfx" }), "sun_light", funcptr<two::Light&(*)(two::Gnode&, float, float)>(two::gfx::sun_light), two_gfx_sun_light_32, { { "parent", type<two::Gnode>(),  }, { "azimuth", type<float>(),  }, { "elevation", type<float>(),  } }, { &type<two::Light>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "gfx" }), "radiance", funcptr<void(*)(two::Gnode&, const stl::string&, two::BackgroundMode)>(two::gfx::radiance), two_gfx_radiance_33, { { "parent", type<two::Gnode>(),  }, { "texture", type<stl::string>(),  }, { "background", type<two::BackgroundMode>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "gfx" }), "direct_light_node", funcptr<two::Light&(*)(two::Gnode&, const two::vec3&)>(two::gfx::direct_light_node), two_gfx_direct_light_node_34, { { "parent", type<two::Gnode>(),  }, { "direction", type<two::vec3>(),  } }, { &type<two::Light>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "gfx" }), "solid_material", funcptr<two::Material&(*)(two::GfxSystem&, const stl::string&, const two::Colour&)>(two::gfx::solid_material), two_gfx_solid_material_35, { { "gfx", type<two::GfxSystem>(),  }, { "name", type<stl::string>(),  }, { "colour", type<two::Colour>(),  } }, { &type<two::Material>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static float metallic_default = 0.f;
			static float roughness_default = 1.f;
			static Function f = { &namspc({ "two", "gfx" }), "pbr_material", funcptr<two::Material&(*)(two::GfxSystem&, const stl::string&, const two::Colour&, float, float)>(two::gfx::pbr_material), two_gfx_pbr_material_36, { { "gfx", type<two::GfxSystem>(),  }, { "name", type<stl::string>(),  }, { "albedo", type<two::Colour>(),  }, { "metallic", type<float>(), Param::Default, &metallic_default }, { "roughness", type<float>(), Param::Default, &roughness_default } }, { &type<two::Material>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "gfx" }), "model_suzanne", funcptr<two::Model&(*)(two::GfxSystem&)>(two::gfx::model_suzanne), two_gfx_model_suzanne_37, { { "gfx", type<two::GfxSystem>(),  } }, { &type<two::Model>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static float depth_default = 1.f;
			static Function f = { &namspc({ "two" }), "pass_clear_fbo", funcptr<void(*)(two::GfxSystem&, two::Render&, two::FrameBuffer&, const two::Colour&, float)>(two::pass_clear_fbo), two_pass_clear_fbo_38, { { "gfx", type<two::GfxSystem>(),  }, { "render", type<two::Render>(),  }, { "fbo", type<two::FrameBuffer>(),  }, { "colour", type<two::Colour>(),  }, { "depth", type<float>(), Param::Default, &depth_default } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "pass_clear", funcptr<void(*)(two::GfxSystem&, two::Render&)>(two::pass_clear), two_pass_clear_39, { { "gfx", type<two::GfxSystem>(),  }, { "render", type<two::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "pass_gclear", funcptr<void(*)(two::GfxSystem&, two::Render&)>(two::pass_gclear), two_pass_gclear_40, { { "gfx", type<two::GfxSystem>(),  }, { "render", type<two::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "pass_depth", funcptr<void(*)(two::GfxSystem&, two::Render&)>(two::pass_depth), two_pass_depth_41, { { "gfx", type<two::GfxSystem>(),  }, { "render", type<two::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "pass_background", funcptr<void(*)(two::GfxSystem&, two::Render&)>(two::pass_background), two_pass_background_42, { { "gfx", type<two::GfxSystem>(),  }, { "render", type<two::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "pass_solid", funcptr<void(*)(two::GfxSystem&, two::Render&)>(two::pass_solid), two_pass_solid_43, { { "gfx", type<two::GfxSystem>(),  }, { "render", type<two::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "pass_flip", funcptr<void(*)(two::GfxSystem&, two::Render&)>(two::pass_flip), two_pass_flip_44, { { "gfx", type<two::GfxSystem>(),  }, { "render", type<two::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "render_minimal", funcptr<void(*)(two::GfxSystem&, two::Render&)>(two::render_minimal), two_render_minimal_45, { { "gfx", type<two::GfxSystem>(),  }, { "render", type<two::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "render_solid", funcptr<void(*)(two::GfxSystem&, two::Render&)>(two::render_solid), two_render_solid_46, { { "gfx", type<two::GfxSystem>(),  }, { "render", type<two::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "render_clear", funcptr<void(*)(two::GfxSystem&, two::Render&)>(two::render_clear), two_render_clear_47, { { "gfx", type<two::GfxSystem>(),  }, { "render", type<two::Render>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
	}
}

namespace two
{
	two_gfx::two_gfx()
		: Module("two::gfx", { &two_infra::m(), &two_type::m(), &two_tree::m(), &two_jobs::m(), &two_pool::m(), &two_ecs::m(), &two_math::m(), &two_geom::m(), &two_ctx::m(), &two_bgfx::m() })
	{
		// setup reflection meta data
		two_gfx_meta(*this);
	}
}

#ifdef TWO_GFX_MODULE
extern "C"
Module& getModule()
{
	return two_gfx::m();
}
#endif
