#pragma once

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>
#include <gfx/Forward.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <type/Type.h>
#endif

#ifndef MUD_MODULES
#include <infra/Types.h>
#include <jobs/Types.h>
#include <type/Types.h>
#include <pool/Types.h>
#include <ecs/Types.h>
#include <math/Types.h>
#include <geom/Types.h>
#include <ctx/Types.h>
#include <bgfx/Types.h>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_GFX_EXPORT Type& type<mud::AnimationTarget>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::BackgroundMode>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::BlendMode>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::CullMode>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::DepthDraw>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::DepthMethod>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::DepthTest>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::EmitterFlow>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Interpolation>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::IsometricAngle>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::ItemShadow>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::LightType>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Lighting>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::MSAA>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::MaterialBlock>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::MaterialFlag>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::ModelFormat>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Month>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::PbrDiffuseMode>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::PbrSpecularMode>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::ShaderColor>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::ShaderType>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Shading>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::ShadowFlags>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::TextureChannel>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::TextureHint>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::TextureSampler>();
    
    export_ template <> MUD_GFX_EXPORT Type& type<stl::span<mud::mat4>>();
    export_ template <> MUD_GFX_EXPORT Type& type<stl::vector<mud::Animation*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<stl::vector<mud::AnimationPlay>>();
    export_ template <> MUD_GFX_EXPORT Type& type<stl::vector<mud::Material*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<stl::vector<mud::Mesh*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<stl::vector<mud::Model*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<stl::vector<mud::Texture*>>();
    
    export_ template <> MUD_GFX_EXPORT Type& type<mud::AnimatedTrack>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Animation>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::AnimationPlay>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::AnimationTrack>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::AssetStore<mud::Flow>>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::AssetStore<mud::Material>>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::AssetStore<mud::Model>>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::AssetStore<mud::Prefab>>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::AssetStore<mud::Program>>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::AssetStore<mud::Texture>>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Background>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Batch>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Bone>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Camera>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Culler>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::DepthParams>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Direct>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::DistanceParams>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Filter>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Flow>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Fog>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::FrameBuffer>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Frustum>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::FrustumSlice>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::GfxBlock>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::GfxContext>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Gnode>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::GpuMesh>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::ImmediateDraw>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Import>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::ImportConfig>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Item>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Joint>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Light>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Lines>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Material>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::MaterialAlpha>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::MaterialBase>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::MaterialFresnel>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::MaterialLine>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::MaterialParam<float>>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::MaterialParam<mud::Colour>>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::MaterialParam<mud::vec4>>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::MaterialPbr>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::MaterialPoint>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::MaterialSolid>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::MaterialUser>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Mesh>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Mime>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Model>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::ModelItem>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Node3>();
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
    export_ template <> MUD_GFX_EXPORT Type& type<mud::TPool<mud::Batch>>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::TPool<mud::Direct>>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::TPool<mud::Flare>>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::TPool<mud::Item>>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::TPool<mud::Light>>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::TPool<mud::Mime>>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::TPool<mud::Node3>>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Texture>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Viewport>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Zone>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::BlockCopy>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::BlockDepth>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::BlockFilter>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::BlockMaterial>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::BlockParticles>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::BlockPbr>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::BlockSky>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::ClusteredFrustum>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::DrawBlock>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Flare>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::GfxSystem>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::RenderTarget>();
}
