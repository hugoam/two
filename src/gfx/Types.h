#pragma once

#include <gfx/Forward.h>

#if defined TWO_TYPE_LIB
#include <type/Type.h>
#endif


namespace two
{
    // Exported types
    template <> TWO_GFX_EXPORT Type& type<two::AnimTarget>();
    template <> TWO_GFX_EXPORT Type& type<two::Interpolation>();
    template <> TWO_GFX_EXPORT Type& type<two::TextureHint>();
    template <> TWO_GFX_EXPORT Type& type<two::TextureFormat>();
    template <> TWO_GFX_EXPORT Type& type<two::ShaderType>();
    template <> TWO_GFX_EXPORT Type& type<two::PassType>();
    template <> TWO_GFX_EXPORT Type& type<two::MaterialBlock>();
    template <> TWO_GFX_EXPORT Type& type<two::TextureSampler>();
    template <> TWO_GFX_EXPORT Type& type<two::Lighting>();
    template <> TWO_GFX_EXPORT Type& type<two::BlendMode>();
    template <> TWO_GFX_EXPORT Type& type<two::CullMode>();
    template <> TWO_GFX_EXPORT Type& type<two::DepthDraw>();
    template <> TWO_GFX_EXPORT Type& type<two::DepthTest>();
    template <> TWO_GFX_EXPORT Type& type<two::MaterialFlag>();
    template <> TWO_GFX_EXPORT Type& type<two::ShaderColor>();
    template <> TWO_GFX_EXPORT Type& type<two::TextureChannel>();
    template <> TWO_GFX_EXPORT Type& type<two::PbrDiffuseMode>();
    template <> TWO_GFX_EXPORT Type& type<two::PbrSpecularMode>();
    template <> TWO_GFX_EXPORT Type& type<two::PhongEnvBlendMode>();
    template <> TWO_GFX_EXPORT Type& type<two::EmitterFlow>();
    template <> TWO_GFX_EXPORT Type& type<two::ItemShadow>();
    template <> TWO_GFX_EXPORT Type& type<two::ModelFormat>();
    template <> TWO_GFX_EXPORT Type& type<two::IsometricAngle>();
    template <> TWO_GFX_EXPORT Type& type<two::DepthMethod>();
    template <> TWO_GFX_EXPORT Type& type<two::LightType>();
    template <> TWO_GFX_EXPORT Type& type<two::ShadowFlags>();
    template <> TWO_GFX_EXPORT Type& type<two::MSAA>();
    template <> TWO_GFX_EXPORT Type& type<two::Shading>();
    template <> TWO_GFX_EXPORT Type& type<two::BackgroundMode>();
    template <> TWO_GFX_EXPORT Type& type<two::Month>();
    
    template <> TWO_GFX_EXPORT Type& type<stl::span<two::mat4>>();
    template <> TWO_GFX_EXPORT Type& type<stl::span<two::Node3>>();
    template <> TWO_GFX_EXPORT Type& type<stl::span<two::Item>>();
    template <> TWO_GFX_EXPORT Type& type<stl::span<two::Batch>>();
    template <> TWO_GFX_EXPORT Type& type<stl::span<two::Direct>>();
    template <> TWO_GFX_EXPORT Type& type<stl::span<two::Mime>>();
    template <> TWO_GFX_EXPORT Type& type<stl::span<two::Light>>();
    template <> TWO_GFX_EXPORT Type& type<stl::span<two::Flare>>();
    template <> TWO_GFX_EXPORT Type& type<stl::span<two::Texture*>>();
    template <> TWO_GFX_EXPORT Type& type<stl::vector<two::Mesh*>>();
    template <> TWO_GFX_EXPORT Type& type<stl::vector<two::Model*>>();
    template <> TWO_GFX_EXPORT Type& type<stl::vector<two::Texture*>>();
    template <> TWO_GFX_EXPORT Type& type<stl::vector<two::Material*>>();
    template <> TWO_GFX_EXPORT Type& type<stl::vector<two::Animation*>>();
    template <> TWO_GFX_EXPORT Type& type<stl::vector<two::AnimPlay>>();
    
    template <> TWO_GFX_EXPORT Type& type<two::Node3>();
    template <> TWO_GFX_EXPORT Type& type<two::AnimTrack>();
    template <> TWO_GFX_EXPORT Type& type<two::Animation>();
    template <> TWO_GFX_EXPORT Type& type<two::Texture>();
    template <> TWO_GFX_EXPORT Type& type<two::Skeleton>();
    template <> TWO_GFX_EXPORT Type& type<two::Joint>();
    template <> TWO_GFX_EXPORT Type& type<two::Skin>();
    template <> TWO_GFX_EXPORT Type& type<two::Rig>();
    template <> TWO_GFX_EXPORT Type& type<two::AnimNode>();
    template <> TWO_GFX_EXPORT Type& type<two::AnimPlay>();
    template <> TWO_GFX_EXPORT Type& type<two::Mime>();
    template <> TWO_GFX_EXPORT Type& type<two::Frustum>();
    template <> TWO_GFX_EXPORT Type& type<two::FrustumSlice>();
    template <> TWO_GFX_EXPORT Type& type<two::ShaderDefine>();
    template <> TWO_GFX_EXPORT Type& type<two::ShaderBlock>();
    template <> TWO_GFX_EXPORT Type& type<two::ProgramMode>();
    template <> TWO_GFX_EXPORT Type& type<two::ProgramBlock>();
    template <> TWO_GFX_EXPORT Type& type<two::Program>();
    template <> TWO_GFX_EXPORT Type& type<two::ProgramVersion>();
    template <> TWO_GFX_EXPORT Type& type<two::Shot>();
    template <> TWO_GFX_EXPORT Type& type<two::Pass>();
    template <> TWO_GFX_EXPORT Type& type<two::RenderFrame>();
    template <> TWO_GFX_EXPORT Type& type<two::Render>();
    template <> TWO_GFX_EXPORT Type& type<two::GfxBlock>();
    template <> TWO_GFX_EXPORT Type& type<two::DrawBlock>();
    template <> TWO_GFX_EXPORT Type& type<two::Renderer>();
    template <> TWO_GFX_EXPORT Type& type<two::GfxWindow>();
    template <> TWO_GFX_EXPORT Type& type<two::GfxSystem>();
    template <> TWO_GFX_EXPORT Type& type<two::MaterialParam<two::Colour>>();
    template <> TWO_GFX_EXPORT Type& type<two::MaterialParam<float>>();
    template <> TWO_GFX_EXPORT Type& type<two::MaterialParam<two::vec4>>();
    template <> TWO_GFX_EXPORT Type& type<two::MaterialBase>();
    template <> TWO_GFX_EXPORT Type& type<two::MaterialUser>();
    template <> TWO_GFX_EXPORT Type& type<two::MaterialAlpha>();
    template <> TWO_GFX_EXPORT Type& type<two::MaterialSolid>();
    template <> TWO_GFX_EXPORT Type& type<two::MaterialPoint>();
    template <> TWO_GFX_EXPORT Type& type<two::MaterialLine>();
    template <> TWO_GFX_EXPORT Type& type<two::MaterialFresnel>();
    template <> TWO_GFX_EXPORT Type& type<two::MaterialLit>();
    template <> TWO_GFX_EXPORT Type& type<two::MaterialPbr>();
    template <> TWO_GFX_EXPORT Type& type<two::MaterialPhong>();
    template <> TWO_GFX_EXPORT Type& type<two::BlockMaterial>();
    template <> TWO_GFX_EXPORT Type& type<two::Material>();
    template <> TWO_GFX_EXPORT Type& type<two::ModelElem>();
    template <> TWO_GFX_EXPORT Type& type<two::Model>();
    template <> TWO_GFX_EXPORT Type& type<two::Flow>();
    template <> TWO_GFX_EXPORT Type& type<two::Flare>();
    template <> TWO_GFX_EXPORT Type& type<two::BlockParticles>();
    template <> TWO_GFX_EXPORT Type& type<two::Batch>();
    template <> TWO_GFX_EXPORT Type& type<two::Item>();
    template <> TWO_GFX_EXPORT Type& type<two::ImportConfig>();
    template <> TWO_GFX_EXPORT Type& type<two::Import>();
    template <> TWO_GFX_EXPORT Type& type<two::Prefab>();
    template <> TWO_GFX_EXPORT Type& type<two::AssetStore<two::Texture>>();
    template <> TWO_GFX_EXPORT Type& type<two::AssetStore<two::Program>>();
    template <> TWO_GFX_EXPORT Type& type<two::AssetStore<two::Material>>();
    template <> TWO_GFX_EXPORT Type& type<two::AssetStore<two::Model>>();
    template <> TWO_GFX_EXPORT Type& type<two::AssetStore<two::Flow>>();
    template <> TWO_GFX_EXPORT Type& type<two::AssetStore<two::Prefab>>();
    template <> TWO_GFX_EXPORT Type& type<two::Camera>();
    template <> TWO_GFX_EXPORT Type& type<two::MirrorCamera>();
    template <> TWO_GFX_EXPORT Type& type<two::DepthParams>();
    template <> TWO_GFX_EXPORT Type& type<two::DistanceParams>();
    template <> TWO_GFX_EXPORT Type& type<two::BlockDepth>();
    template <> TWO_GFX_EXPORT Type& type<two::GpuMesh>();
    template <> TWO_GFX_EXPORT Type& type<two::Mesh>();
    template <> TWO_GFX_EXPORT Type& type<two::Direct>();
    template <> TWO_GFX_EXPORT Type& type<two::ImmediateDraw>();
    template <> TWO_GFX_EXPORT Type& type<two::SymbolIndex>();
    template <> TWO_GFX_EXPORT Type& type<two::Lines>();
    template <> TWO_GFX_EXPORT Type& type<two::BlockFilter>();
    template <> TWO_GFX_EXPORT Type& type<two::BlockCopy>();
    template <> TWO_GFX_EXPORT Type& type<two::ClusteredFrustum>();
    template <> TWO_GFX_EXPORT Type& type<two::Light>();
    template <> TWO_GFX_EXPORT Type& type<two::Gnode>();
    template <> TWO_GFX_EXPORT Type& type<two::TPool<two::Node3>>();
    template <> TWO_GFX_EXPORT Type& type<two::TPool<two::Item>>();
    template <> TWO_GFX_EXPORT Type& type<two::TPool<two::Batch>>();
    template <> TWO_GFX_EXPORT Type& type<two::TPool<two::Direct>>();
    template <> TWO_GFX_EXPORT Type& type<two::TPool<two::Mime>>();
    template <> TWO_GFX_EXPORT Type& type<two::TPool<two::Light>>();
    template <> TWO_GFX_EXPORT Type& type<two::TPool<two::Flare>>();
    template <> TWO_GFX_EXPORT Type& type<two::Culler>();
    template <> TWO_GFX_EXPORT Type& type<two::Viewport>();
    template <> TWO_GFX_EXPORT Type& type<two::RenderQuad>();
    template <> TWO_GFX_EXPORT Type& type<two::FrameBuffer>();
    template <> TWO_GFX_EXPORT Type& type<two::SwapBuffer>();
    template <> TWO_GFX_EXPORT Type& type<two::Cascade>();
    template <> TWO_GFX_EXPORT Type& type<two::SwapCascade>();
    template <> TWO_GFX_EXPORT Type& type<two::RenderTarget>();
    template <> TWO_GFX_EXPORT Type& type<two::Sun>();
    template <> TWO_GFX_EXPORT Type& type<two::Radiance>();
    template <> TWO_GFX_EXPORT Type& type<two::Background>();
    template <> TWO_GFX_EXPORT Type& type<two::Skylight>();
    template <> TWO_GFX_EXPORT Type& type<two::Fog>();
    template <> TWO_GFX_EXPORT Type& type<two::Zone>();
    template <> TWO_GFX_EXPORT Type& type<two::Scene>();
    template <> TWO_GFX_EXPORT Type& type<two::BlockSky>();
}
