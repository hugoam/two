#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <gfx/Types.h>
#include <gfx/Api.h>
#include <type/Vector.h>
#endif

namespace mud
{
    // Exported types
    template <> MUD_GFX_EXPORT Type& type<mud::AnimationTarget>() { static Type ty("AnimationTarget", sizeof(mud::AnimationTarget)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BackgroundMode>() { static Type ty("BackgroundMode", sizeof(mud::BackgroundMode)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BlendMode>() { static Type ty("BlendMode", sizeof(mud::BlendMode)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::CullMode>() { static Type ty("CullMode", sizeof(mud::CullMode)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::DepthDraw>() { static Type ty("DepthDraw", sizeof(mud::DepthDraw)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::DepthTest>() { static Type ty("DepthTest", sizeof(mud::DepthTest)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::EmitterFlow>() { static Type ty("EmitterFlow", sizeof(mud::EmitterFlow)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Interpolation>() { static Type ty("Interpolation", sizeof(mud::Interpolation)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::IsometricAngle>() { static Type ty("IsometricAngle", sizeof(mud::IsometricAngle)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ItemShadow>() { static Type ty("ItemShadow", sizeof(mud::ItemShadow)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::LightType>() { static Type ty("LightType", sizeof(mud::LightType)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Lighting>() { static Type ty("Lighting", sizeof(mud::Lighting)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::MSAA>() { static Type ty("MSAA", sizeof(mud::MSAA)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::MaterialFlag>() { static Type ty("MaterialFlag", sizeof(mud::MaterialFlag)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ModelFormat>() { static Type ty("ModelFormat", sizeof(mud::ModelFormat)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Month>() { static Type ty("Month", sizeof(mud::Month)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::PbrDiffuseMode>() { static Type ty("PbrDiffuseMode", sizeof(mud::PbrDiffuseMode)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::PbrSpecularMode>() { static Type ty("PbrSpecularMode", sizeof(mud::PbrSpecularMode)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ShaderType>() { static Type ty("ShaderType", sizeof(mud::ShaderType)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Shading>() { static Type ty("Shading", sizeof(mud::Shading)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ShadowFlags>() { static Type ty("ShadowFlags", sizeof(mud::ShadowFlags)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::TextureChannel>() { static Type ty("TextureChannel", sizeof(mud::TextureChannel)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::TextureHint>() { static Type ty("TextureHint", sizeof(mud::TextureHint)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::TextureSampler>() { static Type ty("TextureSampler", sizeof(mud::TextureSampler)); return ty; }
    
    template <> MUD_GFX_EXPORT Type& type<stl::span<mud::mat4>>() { static Type ty("span<mud::mat4>", sizeof(stl::span<mud::mat4>)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<stl::vector<mud::Animation*>>() { static Type ty("vector<mud::Animation*>", sizeof(stl::vector<mud::Animation*>)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<stl::vector<mud::AnimationPlay>>() { static Type ty("vector<mud::AnimationPlay>", sizeof(stl::vector<mud::AnimationPlay>)); return ty; }
    
    template <> MUD_GFX_EXPORT Type& type<mud::AnimatedTrack>() { static Type ty("AnimatedTrack", sizeof(mud::AnimatedTrack)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Animation>() { static Type ty("Animation", sizeof(mud::Animation)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::AnimationPlay>() { static Type ty("AnimationPlay", sizeof(mud::AnimationPlay)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::AnimationTrack>() { static Type ty("AnimationTrack", sizeof(mud::AnimationTrack)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::AssetStore<mud::Flow>>() { static Type ty("AssetStore<mud::Flow>", sizeof(mud::AssetStore<mud::Flow>)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::AssetStore<mud::Material>>() { static Type ty("AssetStore<mud::Material>", sizeof(mud::AssetStore<mud::Material>)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::AssetStore<mud::Model>>() { static Type ty("AssetStore<mud::Model>", sizeof(mud::AssetStore<mud::Model>)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::AssetStore<mud::Prefab>>() { static Type ty("AssetStore<mud::Prefab>", sizeof(mud::AssetStore<mud::Prefab>)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::AssetStore<mud::Program>>() { static Type ty("AssetStore<mud::Program>", sizeof(mud::AssetStore<mud::Program>)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::AssetStore<mud::Texture>>() { static Type ty("AssetStore<mud::Texture>", sizeof(mud::AssetStore<mud::Texture>)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Background>() { static Type ty("Background", sizeof(mud::Background)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Bone>() { static Type ty("Bone", sizeof(mud::Bone)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Camera>() { static Type ty("Camera", sizeof(mud::Camera)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Culler>() { static Type ty("Culler", sizeof(mud::Culler)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::DepthParams>() { static Type ty("DepthParams", sizeof(mud::DepthParams)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Filter>() { static Type ty("Filter", sizeof(mud::Filter)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Flow>() { static Type ty("Flow", sizeof(mud::Flow)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Fog>() { static Type ty("Fog", sizeof(mud::Fog)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::FrameBuffer>() { static Type ty("FrameBuffer", sizeof(mud::FrameBuffer)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Frustum>() { static Type ty("Frustum", sizeof(mud::Frustum)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::FrustumSlice>() { static Type ty("FrustumSlice", sizeof(mud::FrustumSlice)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::GfxBlock>() { static Type ty("GfxBlock", sizeof(mud::GfxBlock)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::GfxContext>() { static Type ty("GfxContext", sizeof(mud::GfxContext)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::GfxSystem>() { static Type ty("GfxSystem", sizeof(mud::GfxSystem)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Gnode>() { static Type ty("Gnode", sizeof(mud::Gnode)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ImmediateDraw>() { static Type ty("ImmediateDraw", sizeof(mud::ImmediateDraw)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ImportConfig>() { static Type ty("ImportConfig", sizeof(mud::ImportConfig)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Item>() { static Type ty("Item", sizeof(mud::Item)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Joint>() { static Type ty("Joint", sizeof(mud::Joint)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Light>() { static Type ty("Light", sizeof(mud::Light)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Material>() { static Type ty("Material", sizeof(mud::Material)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::MaterialBase>() { static Type ty("MaterialBase", sizeof(mud::MaterialBase)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::MaterialFresnel>() { static Type ty("MaterialFresnel", sizeof(mud::MaterialFresnel)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::MaterialParam<float>>() { static Type ty("MaterialParam<float>", sizeof(mud::MaterialParam<float>)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::MaterialParam<mud::Colour>>() { static Type ty("MaterialParam<mud::Colour>", sizeof(mud::MaterialParam<mud::Colour>)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::MaterialPbr>() { static Type ty("MaterialPbr", sizeof(mud::MaterialPbr)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::MaterialUnshaded>() { static Type ty("MaterialUnshaded", sizeof(mud::MaterialUnshaded)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Mesh>() { static Type ty("Mesh", sizeof(mud::Mesh)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Mime>() { static Type ty("Mime", sizeof(mud::Mime)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Model>() { static Type ty("Model", sizeof(mud::Model)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ModelItem>() { static Type ty("ModelItem", sizeof(mud::ModelItem)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Node3>() { static Type ty("Node3", sizeof(mud::Node3)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Prefab>() { static Type ty("Prefab", sizeof(mud::Prefab)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Program>() { static Type ty("Program", sizeof(mud::Program)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Radiance>() { static Type ty("Radiance", sizeof(mud::Radiance)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::RenderFrame>() { static Type ty("RenderFrame", sizeof(mud::RenderFrame)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::RenderQuad>() { static Type ty("RenderQuad", sizeof(mud::RenderQuad)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Rig>() { static Type ty("Rig", sizeof(mud::Rig)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Scene>() { static Type ty("Scene", sizeof(mud::Scene)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Shot>() { static Type ty("Shot", sizeof(mud::Shot)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Skeleton>() { static Type ty("Skeleton", sizeof(mud::Skeleton)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Skin>() { static Type ty("Skin", sizeof(mud::Skin)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Sun>() { static Type ty("Sun", sizeof(mud::Sun)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::SymbolIndex>() { static Type ty("SymbolIndex", sizeof(mud::SymbolIndex)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::TPool<mud::Flare>>() { static Type ty("TPool<mud::Flare>", sizeof(mud::TPool<mud::Flare>)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::TPool<mud::Item>>() { static Type ty("TPool<mud::Item>", sizeof(mud::TPool<mud::Item>)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::TPool<mud::Light>>() { static Type ty("TPool<mud::Light>", sizeof(mud::TPool<mud::Light>)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::TPool<mud::Mime>>() { static Type ty("TPool<mud::Mime>", sizeof(mud::TPool<mud::Mime>)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::TPool<mud::Node3>>() { static Type ty("TPool<mud::Node3>", sizeof(mud::TPool<mud::Node3>)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Texture>() { static Type ty("Texture", sizeof(mud::Texture)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Viewport>() { static Type ty("Viewport", sizeof(mud::Viewport)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Zone>() { static Type ty("Zone", sizeof(mud::Zone)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BlockCopy>() { static Type ty("BlockCopy", type<mud::GfxBlock>(), sizeof(mud::BlockCopy)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::DrawBlock>() { static Type ty("DrawBlock", type<mud::GfxBlock>(), sizeof(mud::DrawBlock)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BlockDepth>() { static Type ty("BlockDepth", type<mud::DrawBlock>(), sizeof(mud::BlockDepth)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BlockFilter>() { static Type ty("BlockFilter", type<mud::GfxBlock>(), sizeof(mud::BlockFilter)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BlockParticles>() { static Type ty("BlockParticles", type<mud::GfxBlock>(), sizeof(mud::BlockParticles)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BlockResolve>() { static Type ty("BlockResolve", type<mud::GfxBlock>(), sizeof(mud::BlockResolve)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BlockSky>() { static Type ty("BlockSky", type<mud::GfxBlock>(), sizeof(mud::BlockSky)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ClusteredFrustum>() { static Type ty("ClusteredFrustum", type<mud::Frustum>(), sizeof(mud::ClusteredFrustum)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Flare>() { static Type ty("Flare", type<mud::Flow>(), sizeof(mud::Flare)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::MaterialBlock>() { static Type ty("MaterialBlock", type<mud::GfxBlock>(), sizeof(mud::MaterialBlock)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::RenderTarget>() { static Type ty("RenderTarget", type<mud::FrameBuffer>(), sizeof(mud::RenderTarget)); return ty; }
}
