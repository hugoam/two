module;
#include <infra/Cpp20.h>
module two.gfx;

namespace two
{
    // Exported types
    template <> TWO_GFX_EXPORT Type& type<two::AnimTarget>() { static Type ty("AnimTarget", sizeof(two::AnimTarget)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Interpolation>() { static Type ty("Interpolation", sizeof(two::Interpolation)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::TextureHint>() { static Type ty("TextureHint", sizeof(two::TextureHint)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::TextureFormat>() { static Type ty("TextureFormat", sizeof(two::TextureFormat)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::ShaderType>() { static Type ty("ShaderType", sizeof(two::ShaderType)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::PassType>() { static Type ty("PassType", sizeof(two::PassType)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::MaterialBlock>() { static Type ty("MaterialBlock", sizeof(two::MaterialBlock)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::TextureSampler>() { static Type ty("TextureSampler", sizeof(two::TextureSampler)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Lighting>() { static Type ty("Lighting", sizeof(two::Lighting)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::BlendMode>() { static Type ty("BlendMode", sizeof(two::BlendMode)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::CullMode>() { static Type ty("CullMode", sizeof(two::CullMode)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::DepthDraw>() { static Type ty("DepthDraw", sizeof(two::DepthDraw)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::DepthTest>() { static Type ty("DepthTest", sizeof(two::DepthTest)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::MaterialFlag>() { static Type ty("MaterialFlag", sizeof(two::MaterialFlag)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::ShaderColor>() { static Type ty("ShaderColor", sizeof(two::ShaderColor)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::TextureChannel>() { static Type ty("TextureChannel", sizeof(two::TextureChannel)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::PbrDiffuseMode>() { static Type ty("PbrDiffuseMode", sizeof(two::PbrDiffuseMode)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::PbrSpecularMode>() { static Type ty("PbrSpecularMode", sizeof(two::PbrSpecularMode)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::PhongEnvBlendMode>() { static Type ty("PhongEnvBlendMode", sizeof(two::PhongEnvBlendMode)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::EmitterFlow>() { static Type ty("EmitterFlow", sizeof(two::EmitterFlow)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::ItemShadow>() { static Type ty("ItemShadow", sizeof(two::ItemShadow)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::ModelFormat>() { static Type ty("ModelFormat", sizeof(two::ModelFormat)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::IsometricAngle>() { static Type ty("IsometricAngle", sizeof(two::IsometricAngle)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::DepthMethod>() { static Type ty("DepthMethod", sizeof(two::DepthMethod)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::LightType>() { static Type ty("LightType", sizeof(two::LightType)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::ShadowFlags>() { static Type ty("ShadowFlags", sizeof(two::ShadowFlags)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::MSAA>() { static Type ty("MSAA", sizeof(two::MSAA)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Shading>() { static Type ty("Shading", sizeof(two::Shading)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::BackgroundMode>() { static Type ty("BackgroundMode", sizeof(two::BackgroundMode)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Month>() { static Type ty("Month", sizeof(two::Month)); return ty; }
    
    template <> TWO_GFX_EXPORT Type& type<stl::span<two::mat4>>() { static Type ty("span<two::mat4>", sizeof(stl::span<two::mat4>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<stl::span<two::Node3>>() { static Type ty("span<two::Node3>", sizeof(stl::span<two::Node3>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<stl::span<two::Item>>() { static Type ty("span<two::Item>", sizeof(stl::span<two::Item>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<stl::span<two::Batch>>() { static Type ty("span<two::Batch>", sizeof(stl::span<two::Batch>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<stl::span<two::Direct>>() { static Type ty("span<two::Direct>", sizeof(stl::span<two::Direct>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<stl::span<two::Mime>>() { static Type ty("span<two::Mime>", sizeof(stl::span<two::Mime>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<stl::span<two::Light>>() { static Type ty("span<two::Light>", sizeof(stl::span<two::Light>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<stl::span<two::Flare>>() { static Type ty("span<two::Flare>", sizeof(stl::span<two::Flare>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<stl::span<two::Texture*>>() { static Type ty("span<two::Texture*>", sizeof(stl::span<two::Texture*>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<stl::vector<two::Mesh*>>() { static Type ty("vector<two::Mesh*>", sizeof(stl::vector<two::Mesh*>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<stl::vector<two::Model*>>() { static Type ty("vector<two::Model*>", sizeof(stl::vector<two::Model*>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<stl::vector<two::Texture*>>() { static Type ty("vector<two::Texture*>", sizeof(stl::vector<two::Texture*>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<stl::vector<two::Material*>>() { static Type ty("vector<two::Material*>", sizeof(stl::vector<two::Material*>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<stl::vector<two::Animation*>>() { static Type ty("vector<two::Animation*>", sizeof(stl::vector<two::Animation*>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<stl::vector<two::AnimPlay>>() { static Type ty("vector<two::AnimPlay>", sizeof(stl::vector<two::AnimPlay>)); return ty; }
    
    template <> TWO_GFX_EXPORT Type& type<two::Node3>() { static Type ty("Node3", sizeof(two::Node3)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::AnimTrack>() { static Type ty("AnimTrack", sizeof(two::AnimTrack)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Animation>() { static Type ty("Animation", sizeof(two::Animation)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Texture>() { static Type ty("Texture", sizeof(two::Texture)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Skeleton>() { static Type ty("Skeleton", sizeof(two::Skeleton)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Joint>() { static Type ty("Joint", sizeof(two::Joint)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Skin>() { static Type ty("Skin", sizeof(two::Skin)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Rig>() { static Type ty("Rig", sizeof(two::Rig)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::AnimNode>() { static Type ty("AnimNode", sizeof(two::AnimNode)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::AnimPlay>() { static Type ty("AnimPlay", sizeof(two::AnimPlay)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Mime>() { static Type ty("Mime", sizeof(two::Mime)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Frustum>() { static Type ty("Frustum", sizeof(two::Frustum)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::FrustumSlice>() { static Type ty("FrustumSlice", sizeof(two::FrustumSlice)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::ShaderDefine>() { static Type ty("ShaderDefine", sizeof(two::ShaderDefine)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::ShaderBlock>() { static Type ty("ShaderBlock", sizeof(two::ShaderBlock)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::ProgramMode>() { static Type ty("ProgramMode", sizeof(two::ProgramMode)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::ProgramBlock>() { static Type ty("ProgramBlock", sizeof(two::ProgramBlock)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Program>() { static Type ty("Program", sizeof(two::Program)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::ProgramVersion>() { static Type ty("ProgramVersion", sizeof(two::ProgramVersion)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Shot>() { static Type ty("Shot", sizeof(two::Shot)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Pass>() { static Type ty("Pass", sizeof(two::Pass)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::RenderFrame>() { static Type ty("RenderFrame", sizeof(two::RenderFrame)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Render>() { static Type ty("Render", sizeof(two::Render)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::GfxBlock>() { static Type ty("GfxBlock", type<two::ShaderBlock>(), sizeof(two::GfxBlock)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::DrawBlock>() { static Type ty("DrawBlock", type<two::GfxBlock>(), sizeof(two::DrawBlock)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Renderer>() { static Type ty("Renderer", sizeof(two::Renderer)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::GfxWindow>() { static Type ty("GfxWindow", sizeof(two::GfxWindow)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::GfxSystem>() { static Type ty("GfxSystem", type<two::BgfxSystem>(), sizeof(two::GfxSystem)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::MaterialParam<two::Colour>>() { static Type ty("MaterialParam<two::Colour>", sizeof(two::MaterialParam<two::Colour>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::MaterialParam<float>>() { static Type ty("MaterialParam<float>", sizeof(two::MaterialParam<float>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::MaterialParam<two::vec4>>() { static Type ty("MaterialParam<two::vec4>", sizeof(two::MaterialParam<two::vec4>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::MaterialBase>() { static Type ty("MaterialBase", sizeof(two::MaterialBase)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::MaterialUser>() { static Type ty("MaterialUser", sizeof(two::MaterialUser)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::MaterialAlpha>() { static Type ty("MaterialAlpha", sizeof(two::MaterialAlpha)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::MaterialSolid>() { static Type ty("MaterialSolid", sizeof(two::MaterialSolid)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::MaterialPoint>() { static Type ty("MaterialPoint", sizeof(two::MaterialPoint)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::MaterialLine>() { static Type ty("MaterialLine", sizeof(two::MaterialLine)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::MaterialFresnel>() { static Type ty("MaterialFresnel", sizeof(two::MaterialFresnel)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::MaterialLit>() { static Type ty("MaterialLit", sizeof(two::MaterialLit)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::MaterialPbr>() { static Type ty("MaterialPbr", sizeof(two::MaterialPbr)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::MaterialPhong>() { static Type ty("MaterialPhong", sizeof(two::MaterialPhong)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::BlockMaterial>() { static Type ty("BlockMaterial", type<two::GfxBlock>(), sizeof(two::BlockMaterial)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Material>() { static Type ty("Material", sizeof(two::Material)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::ModelElem>() { static Type ty("ModelElem", sizeof(two::ModelElem)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Model>() { static Type ty("Model", sizeof(two::Model)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Flow>() { static Type ty("Flow", sizeof(two::Flow)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Flare>() { static Type ty("Flare", type<two::Flow>(), sizeof(two::Flare)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::BlockParticles>() { static Type ty("BlockParticles", type<two::GfxBlock>(), sizeof(two::BlockParticles)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Batch>() { static Type ty("Batch", sizeof(two::Batch)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Item>() { static Type ty("Item", sizeof(two::Item)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::ImportConfig>() { static Type ty("ImportConfig", sizeof(two::ImportConfig)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Import>() { static Type ty("Import", sizeof(two::Import)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Prefab>() { static Type ty("Prefab", sizeof(two::Prefab)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::AssetStore<two::Texture>>() { static Type ty("AssetStore<two::Texture>", sizeof(two::AssetStore<two::Texture>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::AssetStore<two::Program>>() { static Type ty("AssetStore<two::Program>", sizeof(two::AssetStore<two::Program>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::AssetStore<two::Material>>() { static Type ty("AssetStore<two::Material>", sizeof(two::AssetStore<two::Material>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::AssetStore<two::Model>>() { static Type ty("AssetStore<two::Model>", sizeof(two::AssetStore<two::Model>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::AssetStore<two::Flow>>() { static Type ty("AssetStore<two::Flow>", sizeof(two::AssetStore<two::Flow>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::AssetStore<two::Prefab>>() { static Type ty("AssetStore<two::Prefab>", sizeof(two::AssetStore<two::Prefab>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Camera>() { static Type ty("Camera", sizeof(two::Camera)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::MirrorCamera>() { static Type ty("MirrorCamera", sizeof(two::MirrorCamera)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::DepthParams>() { static Type ty("DepthParams", sizeof(two::DepthParams)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::DistanceParams>() { static Type ty("DistanceParams", sizeof(two::DistanceParams)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::BlockDepth>() { static Type ty("BlockDepth", type<two::DrawBlock>(), sizeof(two::BlockDepth)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::GpuMesh>() { static Type ty("GpuMesh", sizeof(two::GpuMesh)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Mesh>() { static Type ty("Mesh", sizeof(two::Mesh)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Direct>() { static Type ty("Direct", sizeof(two::Direct)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::ImmediateDraw>() { static Type ty("ImmediateDraw", sizeof(two::ImmediateDraw)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::SymbolIndex>() { static Type ty("SymbolIndex", sizeof(two::SymbolIndex)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Lines>() { static Type ty("Lines", sizeof(two::Lines)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::BlockFilter>() { static Type ty("BlockFilter", type<two::GfxBlock>(), sizeof(two::BlockFilter)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::BlockCopy>() { static Type ty("BlockCopy", type<two::GfxBlock>(), sizeof(two::BlockCopy)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::ClusteredFrustum>() { static Type ty("ClusteredFrustum", type<two::Frustum>(), sizeof(two::ClusteredFrustum)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Light>() { static Type ty("Light", sizeof(two::Light)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Gnode>() { static Type ty("Gnode", sizeof(two::Gnode)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::TPool<two::Node3>>() { static Type ty("TPool<two::Node3>", sizeof(two::TPool<two::Node3>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::TPool<two::Item>>() { static Type ty("TPool<two::Item>", sizeof(two::TPool<two::Item>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::TPool<two::Batch>>() { static Type ty("TPool<two::Batch>", sizeof(two::TPool<two::Batch>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::TPool<two::Direct>>() { static Type ty("TPool<two::Direct>", sizeof(two::TPool<two::Direct>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::TPool<two::Mime>>() { static Type ty("TPool<two::Mime>", sizeof(two::TPool<two::Mime>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::TPool<two::Light>>() { static Type ty("TPool<two::Light>", sizeof(two::TPool<two::Light>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::TPool<two::Flare>>() { static Type ty("TPool<two::Flare>", sizeof(two::TPool<two::Flare>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Culler>() { static Type ty("Culler", sizeof(two::Culler)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Viewport>() { static Type ty("Viewport", type<two::OEntt>(), sizeof(two::Viewport)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::RenderQuad>() { static Type ty("RenderQuad", sizeof(two::RenderQuad)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::FrameBuffer>() { static Type ty("FrameBuffer", sizeof(two::FrameBuffer)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::SwapBuffer>() { static Type ty("SwapBuffer", sizeof(two::SwapBuffer)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Cascade>() { static Type ty("Cascade", sizeof(two::Cascade)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::SwapCascade>() { static Type ty("SwapCascade", sizeof(two::SwapCascade)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::RenderTarget>() { static Type ty("RenderTarget", type<two::FrameBuffer>(), sizeof(two::RenderTarget)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Sun>() { static Type ty("Sun", sizeof(two::Sun)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Radiance>() { static Type ty("Radiance", sizeof(two::Radiance)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Background>() { static Type ty("Background", sizeof(two::Background)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Skylight>() { static Type ty("Skylight", sizeof(two::Skylight)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Fog>() { static Type ty("Fog", sizeof(two::Fog)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Zone>() { static Type ty("Zone", sizeof(two::Zone)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Scene>() { static Type ty("Scene", sizeof(two::Scene)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::BlockSky>() { static Type ty("BlockSky", type<two::GfxBlock>(), sizeof(two::BlockSky)); return ty; }
}
