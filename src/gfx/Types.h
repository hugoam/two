#pragma once

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>
#include <gfx/Forward.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <type/Type.h>
#endif

#ifndef TWO_MODULES
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


namespace two
{
    // Exported types
    export_ template <> TWO_GFX_EXPORT Type& type<two::AnimTarget>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Interpolation>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::TextureHint>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::TextureFormat>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::ShaderType>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::PassType>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::MaterialBlock>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::TextureSampler>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Lighting>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::BlendMode>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::CullMode>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::DepthDraw>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::DepthTest>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::MaterialFlag>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::ShaderColor>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::TextureChannel>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::PbrDiffuseMode>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::PbrSpecularMode>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::PhongEnvBlendMode>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::EmitterFlow>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::ItemShadow>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::ModelFormat>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::IsometricAngle>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::DepthMethod>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::LightType>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::ShadowFlags>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::MSAA>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Shading>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::BackgroundMode>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Month>();
    
    export_ template <> TWO_GFX_EXPORT Type& type<stl::span<two::mat4>>();
    export_ template <> TWO_GFX_EXPORT Type& type<stl::span<two::Node3>>();
    export_ template <> TWO_GFX_EXPORT Type& type<stl::span<two::Item>>();
    export_ template <> TWO_GFX_EXPORT Type& type<stl::span<two::Batch>>();
    export_ template <> TWO_GFX_EXPORT Type& type<stl::span<two::Direct>>();
    export_ template <> TWO_GFX_EXPORT Type& type<stl::span<two::Mime>>();
    export_ template <> TWO_GFX_EXPORT Type& type<stl::span<two::Light>>();
    export_ template <> TWO_GFX_EXPORT Type& type<stl::span<two::Flare>>();
    export_ template <> TWO_GFX_EXPORT Type& type<stl::span<two::Texture*>>();
    export_ template <> TWO_GFX_EXPORT Type& type<stl::vector<two::Mesh*>>();
    export_ template <> TWO_GFX_EXPORT Type& type<stl::vector<two::Model*>>();
    export_ template <> TWO_GFX_EXPORT Type& type<stl::vector<two::Texture*>>();
    export_ template <> TWO_GFX_EXPORT Type& type<stl::vector<two::Material*>>();
    export_ template <> TWO_GFX_EXPORT Type& type<stl::vector<two::Animation*>>();
    export_ template <> TWO_GFX_EXPORT Type& type<stl::vector<two::AnimPlay>>();
    
    export_ template <> TWO_GFX_EXPORT Type& type<two::Node3>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::AnimTrack>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Animation>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Texture>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Skeleton>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Joint>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Skin>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Rig>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::AnimNode>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::AnimPlay>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Mime>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::ShaderDefine>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::ShaderBlock>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::ProgramMode>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::ProgramBlock>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Program>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Frustum>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::FrustumSlice>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::ProgramVersion>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Shot>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Pass>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::RenderFrame>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Render>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::GfxBlock>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::DrawBlock>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Renderer>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::MaterialParam<two::Colour>>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::MaterialParam<float>>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::MaterialParam<two::vec4>>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::MaterialBase>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::MaterialUser>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::MaterialAlpha>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::MaterialSolid>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::MaterialPoint>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::MaterialLine>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::MaterialFresnel>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::MaterialLit>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::MaterialPbr>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::MaterialPhong>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::BlockMaterial>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Material>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::ModelElem>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Model>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Flow>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Flare>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::BlockParticles>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Batch>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Item>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::ImportConfig>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Import>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Prefab>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::AssetStore<two::Texture>>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::AssetStore<two::Program>>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::AssetStore<two::Material>>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::AssetStore<two::Model>>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::AssetStore<two::Flow>>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::AssetStore<two::Prefab>>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Camera>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::MirrorCamera>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::DepthParams>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::DistanceParams>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::BlockDepth>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::GpuMesh>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Mesh>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Direct>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::ImmediateDraw>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::SymbolIndex>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Lines>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::BlockFilter>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::BlockCopy>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::ClusteredFrustum>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Light>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::GfxWindow>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::GfxSystem>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Gnode>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::TPool<two::Node3>>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::TPool<two::Item>>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::TPool<two::Batch>>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::TPool<two::Direct>>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::TPool<two::Mime>>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::TPool<two::Light>>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::TPool<two::Flare>>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Culler>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Viewport>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::RenderQuad>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::FrameBuffer>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::SwapBuffer>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Cascade>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::SwapCascade>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::RenderTarget>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Sun>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Radiance>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Background>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Skylight>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Fog>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Zone>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Scene>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::BlockSky>();
}
