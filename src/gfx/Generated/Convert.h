
#pragma once

#ifndef MUD_MODULES
#include <gfx/Generated/Types.h>

#include <obj/Reflect/Meta.h>
#include <obj/Reflect/Enum.h>
#include <obj/String/StringConvert.h>
#endif

namespace mud
{
    template <> inline void from_string(const string& str, mud::BackgroundMode& val) { val = static_cast<mud::BackgroundMode>(enu<mud::BackgroundMode>().value(str.c_str())); };
    template <> inline void to_string(const mud::BackgroundMode& val, string& str) { str = enu<mud::BackgroundMode>().m_map[size_t(val)]; };
    
    template <> inline void from_string(const string& str, mud::BlendMode& val) { val = static_cast<mud::BlendMode>(enu<mud::BlendMode>().value(str.c_str())); };
    template <> inline void to_string(const mud::BlendMode& val, string& str) { str = enu<mud::BlendMode>().m_map[size_t(val)]; };
    
    template <> inline void from_string(const string& str, mud::CullMode& val) { val = static_cast<mud::CullMode>(enu<mud::CullMode>().value(str.c_str())); };
    template <> inline void to_string(const mud::CullMode& val, string& str) { str = enu<mud::CullMode>().m_map[size_t(val)]; };
    
    template <> inline void from_string(const string& str, mud::DepthDraw& val) { val = static_cast<mud::DepthDraw>(enu<mud::DepthDraw>().value(str.c_str())); };
    template <> inline void to_string(const mud::DepthDraw& val, string& str) { str = enu<mud::DepthDraw>().m_map[size_t(val)]; };
    
    template <> inline void from_string(const string& str, mud::DepthTest& val) { val = static_cast<mud::DepthTest>(enu<mud::DepthTest>().value(str.c_str())); };
    template <> inline void to_string(const mud::DepthTest& val, string& str) { str = enu<mud::DepthTest>().m_map[size_t(val)]; };
    
    template <> inline void from_string(const string& str, mud::EmitterDirection& val) { val = static_cast<mud::EmitterDirection>(enu<mud::EmitterDirection>().value(str.c_str())); };
    template <> inline void to_string(const mud::EmitterDirection& val, string& str) { str = enu<mud::EmitterDirection>().m_map[size_t(val)]; };
    
    template <> inline void from_string(const string& str, mud::Interpolation& val) { val = static_cast<mud::Interpolation>(enu<mud::Interpolation>().value(str.c_str())); };
    template <> inline void to_string(const mud::Interpolation& val, string& str) { str = enu<mud::Interpolation>().m_map[size_t(val)]; };
    
    template <> inline void from_string(const string& str, mud::IsometricAngle& val) { val = static_cast<mud::IsometricAngle>(enu<mud::IsometricAngle>().value(str.c_str())); };
    template <> inline void to_string(const mud::IsometricAngle& val, string& str) { str = enu<mud::IsometricAngle>().m_map[size_t(val)]; };
    
    template <> inline void from_string(const string& str, mud::ItemFlag& val) { val = static_cast<mud::ItemFlag>(enu<mud::ItemFlag>().value(str.c_str())); };
    template <> inline void to_string(const mud::ItemFlag& val, string& str) { str = enu<mud::ItemFlag>().m_map[size_t(val)]; };
    
    template <> inline void from_string(const string& str, mud::ItemShadow& val) { val = static_cast<mud::ItemShadow>(enu<mud::ItemShadow>().value(str.c_str())); };
    template <> inline void to_string(const mud::ItemShadow& val, string& str) { str = enu<mud::ItemShadow>().m_map[size_t(val)]; };
    
    template <> inline void from_string(const string& str, mud::LightType& val) { val = static_cast<mud::LightType>(enu<mud::LightType>().value(str.c_str())); };
    template <> inline void to_string(const mud::LightType& val, string& str) { str = enu<mud::LightType>().m_map[size_t(val)]; };
    
    template <> inline void from_string(const string& str, mud::MSAA& val) { val = static_cast<mud::MSAA>(enu<mud::MSAA>().value(str.c_str())); };
    template <> inline void to_string(const mud::MSAA& val, string& str) { str = enu<mud::MSAA>().m_map[size_t(val)]; };
    
    template <> inline void from_string(const string& str, mud::MaterialFlag& val) { val = static_cast<mud::MaterialFlag>(enu<mud::MaterialFlag>().value(str.c_str())); };
    template <> inline void to_string(const mud::MaterialFlag& val, string& str) { str = enu<mud::MaterialFlag>().m_map[size_t(val)]; };
    
    template <> inline void from_string(const string& str, mud::Month& val) { val = static_cast<mud::Month>(enu<mud::Month>().value(str.c_str())); };
    template <> inline void to_string(const mud::Month& val, string& str) { str = enu<mud::Month>().m_map[size_t(val)]; };
    
    template <> inline void from_string(const string& str, mud::PbrDiffuseMode& val) { val = static_cast<mud::PbrDiffuseMode>(enu<mud::PbrDiffuseMode>().value(str.c_str())); };
    template <> inline void to_string(const mud::PbrDiffuseMode& val, string& str) { str = enu<mud::PbrDiffuseMode>().m_map[size_t(val)]; };
    
    template <> inline void from_string(const string& str, mud::PbrSpecularMode& val) { val = static_cast<mud::PbrSpecularMode>(enu<mud::PbrSpecularMode>().value(str.c_str())); };
    template <> inline void to_string(const mud::PbrSpecularMode& val, string& str) { str = enu<mud::PbrSpecularMode>().m_map[size_t(val)]; };
    
    template <> inline void from_string(const string& str, mud::PrefabType& val) { val = static_cast<mud::PrefabType>(enu<mud::PrefabType>().value(str.c_str())); };
    template <> inline void to_string(const mud::PrefabType& val, string& str) { str = enu<mud::PrefabType>().m_map[size_t(val)]; };
    
    template <> inline void from_string(const string& str, mud::ShaderType& val) { val = static_cast<mud::ShaderType>(enu<mud::ShaderType>().value(str.c_str())); };
    template <> inline void to_string(const mud::ShaderType& val, string& str) { str = enu<mud::ShaderType>().m_map[size_t(val)]; };
    
    template <> inline void from_string(const string& str, mud::Shading& val) { val = static_cast<mud::Shading>(enu<mud::Shading>().value(str.c_str())); };
    template <> inline void to_string(const mud::Shading& val, string& str) { str = enu<mud::Shading>().m_map[size_t(val)]; };
    
    template <> inline void from_string(const string& str, mud::ShadowFlags& val) { val = static_cast<mud::ShadowFlags>(enu<mud::ShadowFlags>().value(str.c_str())); };
    template <> inline void to_string(const mud::ShadowFlags& val, string& str) { str = enu<mud::ShadowFlags>().m_map[size_t(val)]; };
    
    template <> inline void from_string(const string& str, mud::TextureChannel& val) { val = static_cast<mud::TextureChannel>(enu<mud::TextureChannel>().value(str.c_str())); };
    template <> inline void to_string(const mud::TextureChannel& val, string& str) { str = enu<mud::TextureChannel>().m_map[size_t(val)]; };
    
    template <> inline void from_string(const string& str, mud::TextureHint& val) { val = static_cast<mud::TextureHint>(enu<mud::TextureHint>().value(str.c_str())); };
    template <> inline void to_string(const mud::TextureHint& val, string& str) { str = enu<mud::TextureHint>().m_map[size_t(val)]; };
    
    template <> inline void from_string(const string& str, mud::TextureSampler& val) { val = static_cast<mud::TextureSampler>(enu<mud::TextureSampler>().value(str.c_str())); };
    template <> inline void to_string(const mud::TextureSampler& val, string& str) { str = enu<mud::TextureSampler>().m_map[size_t(val)]; };
    
    
}
