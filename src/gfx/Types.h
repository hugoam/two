#pragma once

#include <gfx/Forward.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <type/Type.h>
#include <type/Vector.h>
#endif

#ifndef MUD_MODULES
#include <infra/Types.h>
#include <jobs/Types.h>
#include <type/Types.h>
#include <pool/Types.h>
#include <math/Types.h>
#include <geom/Types.h>
#include <ctx/Types.h>
#include <bgfx/Types.h>
#endif

#ifndef MUD_CPP_20
#include <stl/string.h>
#include <stl/vector.h>
#include <stdint.h>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_GFX_EXPORT Type& type<mud::AnimationTarget>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::BackgroundMode>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::BlendMode>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::CullMode>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::DepthDraw>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::DepthTest>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::EmitterFlow>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Interpolation>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::IsometricAngle>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::ItemShadow>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::LightType>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Lighting>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::MSAA>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::MaterialFlag>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::ModelFormat>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Month>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::PbrDiffuseMode>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::PbrSpecularMode>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::ShaderType>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Shading>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::ShadowFlags>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::TextureChannel>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::TextureHint>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::TextureSampler>();
    
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Animated>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::AnimatedTrack>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Animation>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::AnimationPlay>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::AnimationTrack>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::AssetStore<mud::Material>>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::AssetStore<mud::Model>>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::AssetStore<mud::ParticleFlow>>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::AssetStore<mud::Prefab>>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::AssetStore<mud::Program>>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::AssetStore<mud::Texture>>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Background>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::BaseMaterialBlock>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Bone>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Camera>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Culler>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::DepthParams>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Environment>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Filter>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Fog>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::FrameBuffer>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::FresnelMaterialBlock>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Frustum>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::FrustumSlice>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::GfxBlock>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::GfxContext>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::GfxSystem>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Gnode>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::ImmediateDraw>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::ImportConfig>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Item>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Joint>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Light>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Material>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::MaterialParam<float>>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::MaterialParam<mud::Colour>>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Mesh>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Model>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::ModelItem>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Node3>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::ParticleFlow>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::PbrMaterialBlock>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Prefab>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Program>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Radiance>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::RenderFrame>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::RenderQuad>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Rig>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Scene>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Shot>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Skeleton>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Skin>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Sun>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::SymbolIndex>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Texture>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::UnshadedMaterialBlock>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Viewport>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::BlockCopy>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::DrawBlock>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::BlockDepth>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::BlockFilter>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::BlockParticles>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::BlockResolve>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::BlockSky>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::ClusteredFrustum>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Particles>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::RenderTarget>();
    
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Animated*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::AnimatedTrack*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Animation*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::AnimationPlay*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::AnimationTrack*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::AssetStore<mud::Material>*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::AssetStore<mud::Model>*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::AssetStore<mud::ParticleFlow>*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::AssetStore<mud::Prefab>*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::AssetStore<mud::Program>*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::AssetStore<mud::Texture>*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Background*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::BaseMaterialBlock*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Bone*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Camera*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Culler*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::DepthParams*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Environment*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Filter*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Fog*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::FrameBuffer*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::FresnelMaterialBlock*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Frustum*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::FrustumSlice*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::GfxBlock*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::GfxContext*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::GfxSystem*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Gnode*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::ImmediateDraw*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::ImportConfig*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Item*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Joint*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Light*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Material*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::MaterialParam<float>*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::MaterialParam<mud::Colour>*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Mesh*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Model*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::ModelItem*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Node3*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::ParticleFlow*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::PbrMaterialBlock*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Prefab*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Program*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Radiance*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::RenderFrame*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::RenderQuad*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Rig*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Scene*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Shot*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Skeleton*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Skin*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Sun*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::SymbolIndex*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Texture*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::UnshadedMaterialBlock*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Viewport*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::BlockCopy*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::DrawBlock*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::BlockDepth*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::BlockFilter*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::BlockParticles*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::BlockResolve*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::BlockSky*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::ClusteredFrustum*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Particles*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::RenderTarget*>>();
}
