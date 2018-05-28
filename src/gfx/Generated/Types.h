#pragma once

#include <gfx/Generated/Forward.h>

#include <obj/Generated/Types.h>
#include <math/Generated/Types.h>
#include <geom/Generated/Types.h>

#include <obj/Type.h>
#include <obj/Proto.h>

#include <string>
#include <vector>
#include <stdint.h>


namespace mud
{
    // Exported types
    template <> MUD_GFX_EXPORT Type& type<mud::BackgroundMode>();
    template <> MUD_GFX_EXPORT Type& type<mud::BlendMode>();
    template <> MUD_GFX_EXPORT Type& type<mud::CullMode>();
    template <> MUD_GFX_EXPORT Type& type<mud::DepthDraw>();
    template <> MUD_GFX_EXPORT Type& type<mud::DepthTest>();
    template <> MUD_GFX_EXPORT Type& type<mud::EmitterDirection>();
    template <> MUD_GFX_EXPORT Type& type<mud::Interpolation>();
    template <> MUD_GFX_EXPORT Type& type<mud::IsometricAngle>();
    template <> MUD_GFX_EXPORT Type& type<mud::ItemFlag>();
    template <> MUD_GFX_EXPORT Type& type<mud::ItemShadow>();
    template <> MUD_GFX_EXPORT Type& type<mud::LightType>();
    template <> MUD_GFX_EXPORT Type& type<mud::MSAA>();
    template <> MUD_GFX_EXPORT Type& type<mud::MaterialFlag>();
    template <> MUD_GFX_EXPORT Type& type<mud::ModelFormat>();
    template <> MUD_GFX_EXPORT Type& type<mud::Month>();
    template <> MUD_GFX_EXPORT Type& type<mud::PassType>();
    template <> MUD_GFX_EXPORT Type& type<mud::PbrDiffuseMode>();
    template <> MUD_GFX_EXPORT Type& type<mud::PbrShaderOption>();
    template <> MUD_GFX_EXPORT Type& type<mud::PbrSpecularMode>();
    template <> MUD_GFX_EXPORT Type& type<mud::PrefabType>();
    template <> MUD_GFX_EXPORT Type& type<mud::ShaderOption>();
    template <> MUD_GFX_EXPORT Type& type<mud::ShaderOptionFilter>();
    template <> MUD_GFX_EXPORT Type& type<mud::ShaderOptionResolve>();
    template <> MUD_GFX_EXPORT Type& type<mud::ShaderType>();
    template <> MUD_GFX_EXPORT Type& type<mud::Shading>();
    template <> MUD_GFX_EXPORT Type& type<mud::ShadowFlags>();
    template <> MUD_GFX_EXPORT Type& type<mud::TextureChannel>();
    template <> MUD_GFX_EXPORT Type& type<mud::TextureHint>();
    template <> MUD_GFX_EXPORT Type& type<mud::TextureSampler>();
    template <> MUD_GFX_EXPORT Type& type<std::vector<mud::PrefabNode>>();
    
    template <> MUD_GFX_EXPORT Type& type<mud::Animated>();
    template <> MUD_GFX_EXPORT Type& type<mud::AnimatedTrack>();
    template <> MUD_GFX_EXPORT Type& type<mud::Animation>();
    template <> MUD_GFX_EXPORT Type& type<mud::AnimationPlay>();
    template <> MUD_GFX_EXPORT Type& type<mud::AnimationTrack>();
    template <> MUD_GFX_EXPORT Type& type<mud::Background>();
    template <> MUD_GFX_EXPORT Type& type<mud::BaseMaterialBlock>();
    template <> MUD_GFX_EXPORT Type& type<mud::Bone>();
    template <> MUD_GFX_EXPORT Type& type<mud::Camera>();
    template <> MUD_GFX_EXPORT Type& type<mud::Environment>();
    template <> MUD_GFX_EXPORT Type& type<mud::Filter>();
    template <> MUD_GFX_EXPORT Type& type<mud::FrameBuffer>();
    template <> MUD_GFX_EXPORT Type& type<mud::Frustum>();
    template <> MUD_GFX_EXPORT Type& type<mud::FrustumSlice>();
    template <> MUD_GFX_EXPORT Type& type<mud::GfxBlock>();
    template <> MUD_GFX_EXPORT Type& type<mud::GfxContext>();
    template <> MUD_GFX_EXPORT Type& type<mud::GfxSystem>();
    template <> MUD_GFX_EXPORT Type& type<mud::Gnode>();
    template <> MUD_GFX_EXPORT Type& type<mud::ImmediateDraw>();
    template <> MUD_GFX_EXPORT Type& type<mud::Item>();
    template <> MUD_GFX_EXPORT Type& type<mud::Joint>();
    template <> MUD_GFX_EXPORT Type& type<mud::Light>();
    template <> MUD_GFX_EXPORT Type& type<mud::Material>();
    template <> MUD_GFX_EXPORT Type& type<mud::MaterialParam<float>>();
    template <> MUD_GFX_EXPORT Type& type<mud::MaterialParam<mud::Colour>>();
    template <> MUD_GFX_EXPORT Type& type<mud::Mesh>();
    template <> MUD_GFX_EXPORT Type& type<mud::Model>();
    template <> MUD_GFX_EXPORT Type& type<mud::ModelItem>();
    template <> MUD_GFX_EXPORT Type& type<mud::Node3>();
    template <> MUD_GFX_EXPORT Type& type<mud::ParticleGenerator>();
    template <> MUD_GFX_EXPORT Type& type<mud::Particles>();
    template <> MUD_GFX_EXPORT Type& type<mud::PbrMaterialBlock>();
    template <> MUD_GFX_EXPORT Type& type<mud::Prefab>();
    template <> MUD_GFX_EXPORT Type& type<mud::PrefabNode>();
    template <> MUD_GFX_EXPORT Type& type<mud::Program>();
    template <> MUD_GFX_EXPORT Type& type<mud::Radiance>();
    template <> MUD_GFX_EXPORT Type& type<mud::RenderFrame>();
    template <> MUD_GFX_EXPORT Type& type<mud::RenderQuad>();
    template <> MUD_GFX_EXPORT Type& type<mud::Rig>();
    template <> MUD_GFX_EXPORT Type& type<mud::Scene>();
    template <> MUD_GFX_EXPORT Type& type<mud::Shot>();
    template <> MUD_GFX_EXPORT Type& type<mud::Skeleton>();
    template <> MUD_GFX_EXPORT Type& type<mud::Skin>();
    template <> MUD_GFX_EXPORT Type& type<mud::Sun>();
    template <> MUD_GFX_EXPORT Type& type<mud::SymbolIndex>();
    template <> MUD_GFX_EXPORT Type& type<mud::Texture>();
    template <> MUD_GFX_EXPORT Type& type<mud::Transform>();
    template <> MUD_GFX_EXPORT Type& type<mud::UnshadedMaterialBlock>();
    template <> MUD_GFX_EXPORT Type& type<mud::Viewport>();
    template <> MUD_GFX_EXPORT Type& type<mud::BlockCopy>();
    template <> MUD_GFX_EXPORT Type& type<mud::BlockFilter>();
    template <> MUD_GFX_EXPORT Type& type<mud::BlockParticles>();
    template <> MUD_GFX_EXPORT Type& type<mud::BlockResolve>();
    template <> MUD_GFX_EXPORT Type& type<mud::BlockSky>();
    template <> MUD_GFX_EXPORT Type& type<mud::DrawBlock>();
    template <> MUD_GFX_EXPORT Type& type<mud::ParticleEmitter>();
    template <> MUD_GFX_EXPORT Type& type<mud::RenderTarget>();
}
