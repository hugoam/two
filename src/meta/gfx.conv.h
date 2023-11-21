#pragma once


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/StringOps.h>
#endif

namespace two
{
	export_ template <> inline void to_value(const string& str, two::AnimTarget& val) { val = two::AnimTarget(enu<two::AnimTarget>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::AnimTarget& val, string& str) { str = enu<two::AnimTarget>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::Interpolation& val) { val = two::Interpolation(enu<two::Interpolation>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::Interpolation& val, string& str) { str = enu<two::Interpolation>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::TextureHint& val) { val = two::TextureHint(enu<two::TextureHint>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::TextureHint& val, string& str) { str = enu<two::TextureHint>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::TextureFormat& val) { val = two::TextureFormat(enu<two::TextureFormat>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::TextureFormat& val, string& str) { str = enu<two::TextureFormat>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::ShaderType& val) { val = two::ShaderType(enu<two::ShaderType>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::ShaderType& val, string& str) { str = enu<two::ShaderType>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::PassType& val) { val = two::PassType(enu<two::PassType>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::PassType& val, string& str) { str = enu<two::PassType>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::MaterialBlock& val) { val = two::MaterialBlock(enu<two::MaterialBlock>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::MaterialBlock& val, string& str) { str = enu<two::MaterialBlock>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::TextureSampler& val) { val = two::TextureSampler(enu<two::TextureSampler>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::TextureSampler& val, string& str) { str = enu<two::TextureSampler>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::Lighting& val) { val = two::Lighting(enu<two::Lighting>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::Lighting& val, string& str) { str = enu<two::Lighting>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::BlendMode& val) { val = two::BlendMode(enu<two::BlendMode>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::BlendMode& val, string& str) { str = enu<two::BlendMode>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::CullMode& val) { val = two::CullMode(enu<two::CullMode>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::CullMode& val, string& str) { str = enu<two::CullMode>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::DepthDraw& val) { val = two::DepthDraw(enu<two::DepthDraw>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::DepthDraw& val, string& str) { str = enu<two::DepthDraw>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::DepthTest& val) { val = two::DepthTest(enu<two::DepthTest>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::DepthTest& val, string& str) { str = enu<two::DepthTest>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::MaterialFlag& val) { val = two::MaterialFlag(enu<two::MaterialFlag>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::MaterialFlag& val, string& str) { str = enu<two::MaterialFlag>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::ShaderColor& val) { val = two::ShaderColor(enu<two::ShaderColor>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::ShaderColor& val, string& str) { str = enu<two::ShaderColor>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::TextureChannel& val) { val = two::TextureChannel(enu<two::TextureChannel>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::TextureChannel& val, string& str) { str = enu<two::TextureChannel>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::PbrDiffuseMode& val) { val = two::PbrDiffuseMode(enu<two::PbrDiffuseMode>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::PbrDiffuseMode& val, string& str) { str = enu<two::PbrDiffuseMode>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::PbrSpecularMode& val) { val = two::PbrSpecularMode(enu<two::PbrSpecularMode>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::PbrSpecularMode& val, string& str) { str = enu<two::PbrSpecularMode>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::PhongEnvBlendMode& val) { val = two::PhongEnvBlendMode(enu<two::PhongEnvBlendMode>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::PhongEnvBlendMode& val, string& str) { str = enu<two::PhongEnvBlendMode>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::EmitterFlow& val) { val = two::EmitterFlow(enu<two::EmitterFlow>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::EmitterFlow& val, string& str) { str = enu<two::EmitterFlow>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::ItemShadow& val) { val = two::ItemShadow(enu<two::ItemShadow>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::ItemShadow& val, string& str) { str = enu<two::ItemShadow>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::ModelFormat& val) { val = two::ModelFormat(enu<two::ModelFormat>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::ModelFormat& val, string& str) { str = enu<two::ModelFormat>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::IsometricAngle& val) { val = two::IsometricAngle(enu<two::IsometricAngle>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::IsometricAngle& val, string& str) { str = enu<two::IsometricAngle>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::DepthMethod& val) { val = two::DepthMethod(enu<two::DepthMethod>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::DepthMethod& val, string& str) { str = enu<two::DepthMethod>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::LightType& val) { val = two::LightType(enu<two::LightType>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::LightType& val, string& str) { str = enu<two::LightType>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::ShadowFlags& val) { val = two::ShadowFlags(enu<two::ShadowFlags>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::ShadowFlags& val, string& str) { str = enu<two::ShadowFlags>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::MSAA& val) { val = two::MSAA(enu<two::MSAA>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::MSAA& val, string& str) { str = enu<two::MSAA>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::Shading& val) { val = two::Shading(enu<two::Shading>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::Shading& val, string& str) { str = enu<two::Shading>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::BackgroundMode& val) { val = two::BackgroundMode(enu<two::BackgroundMode>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::BackgroundMode& val, string& str) { str = enu<two::BackgroundMode>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::Month& val) { val = two::Month(enu<two::Month>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::Month& val, string& str) { str = enu<two::Month>().name(uint32_t(val)); };
	
	
}
