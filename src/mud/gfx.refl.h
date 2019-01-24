#pragma once

#include <mud/gfx.h>
#include <mud/refl.h>
#include <mud/infra.h>


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

namespace mud
{
	export_ template <> inline void to_value(const string& str, mud::AnimationTarget& val) { val = mud::AnimationTarget(enu<mud::AnimationTarget>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::AnimationTarget& val, string& str) { str = enu<mud::AnimationTarget>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::BackgroundMode& val) { val = mud::BackgroundMode(enu<mud::BackgroundMode>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::BackgroundMode& val, string& str) { str = enu<mud::BackgroundMode>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::BlendMode& val) { val = mud::BlendMode(enu<mud::BlendMode>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::BlendMode& val, string& str) { str = enu<mud::BlendMode>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::CullMode& val) { val = mud::CullMode(enu<mud::CullMode>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::CullMode& val, string& str) { str = enu<mud::CullMode>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::DepthDraw& val) { val = mud::DepthDraw(enu<mud::DepthDraw>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::DepthDraw& val, string& str) { str = enu<mud::DepthDraw>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::DepthTest& val) { val = mud::DepthTest(enu<mud::DepthTest>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::DepthTest& val, string& str) { str = enu<mud::DepthTest>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::EmitterFlow& val) { val = mud::EmitterFlow(enu<mud::EmitterFlow>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::EmitterFlow& val, string& str) { str = enu<mud::EmitterFlow>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::Interpolation& val) { val = mud::Interpolation(enu<mud::Interpolation>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Interpolation& val, string& str) { str = enu<mud::Interpolation>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::IsometricAngle& val) { val = mud::IsometricAngle(enu<mud::IsometricAngle>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::IsometricAngle& val, string& str) { str = enu<mud::IsometricAngle>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::ItemShadow& val) { val = mud::ItemShadow(enu<mud::ItemShadow>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::ItemShadow& val, string& str) { str = enu<mud::ItemShadow>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::LightType& val) { val = mud::LightType(enu<mud::LightType>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::LightType& val, string& str) { str = enu<mud::LightType>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::Lighting& val) { val = mud::Lighting(enu<mud::Lighting>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Lighting& val, string& str) { str = enu<mud::Lighting>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::MSAA& val) { val = mud::MSAA(enu<mud::MSAA>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::MSAA& val, string& str) { str = enu<mud::MSAA>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::MaterialFlag& val) { val = mud::MaterialFlag(enu<mud::MaterialFlag>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::MaterialFlag& val, string& str) { str = enu<mud::MaterialFlag>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::ModelFormat& val) { val = mud::ModelFormat(enu<mud::ModelFormat>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::ModelFormat& val, string& str) { str = enu<mud::ModelFormat>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::Month& val) { val = mud::Month(enu<mud::Month>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Month& val, string& str) { str = enu<mud::Month>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::PbrDiffuseMode& val) { val = mud::PbrDiffuseMode(enu<mud::PbrDiffuseMode>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::PbrDiffuseMode& val, string& str) { str = enu<mud::PbrDiffuseMode>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::PbrSpecularMode& val) { val = mud::PbrSpecularMode(enu<mud::PbrSpecularMode>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::PbrSpecularMode& val, string& str) { str = enu<mud::PbrSpecularMode>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::ShaderType& val) { val = mud::ShaderType(enu<mud::ShaderType>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::ShaderType& val, string& str) { str = enu<mud::ShaderType>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::Shading& val) { val = mud::Shading(enu<mud::Shading>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Shading& val, string& str) { str = enu<mud::Shading>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::ShadowFlags& val) { val = mud::ShadowFlags(enu<mud::ShadowFlags>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::ShadowFlags& val, string& str) { str = enu<mud::ShadowFlags>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::TextureChannel& val) { val = mud::TextureChannel(enu<mud::TextureChannel>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::TextureChannel& val, string& str) { str = enu<mud::TextureChannel>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::TextureHint& val) { val = mud::TextureHint(enu<mud::TextureHint>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::TextureHint& val, string& str) { str = enu<mud::TextureHint>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::TextureSampler& val) { val = mud::TextureSampler(enu<mud::TextureSampler>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::TextureSampler& val, string& str) { str = enu<mud::TextureSampler>().name(uint32_t(val)); };
	
	
}

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif


#ifndef MUD_GFX_REFL_EXPORT
#define MUD_GFX_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_GFX_REFL_EXPORT mud_gfx : public Module
	{
	private:
		mud_gfx();
		
	public:
		static mud_gfx& m() { static mud_gfx instance; return instance; }
	};
}

#ifdef MUD_GFX_MODULE
extern "C"
MUD_GFX_REFL_EXPORT Module& getModule();
#endif

