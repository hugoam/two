

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <gfx/Types.h>
#include <gfx/Api.h>
#include <obj/Vector.h>
//#include <proto/Proto.h>
#endif

namespace mud
{
    // Exported types
    template <> MUD_GFX_EXPORT Type& type<mud::BackgroundMode>() { static Type ty("mud::BackgroundMode"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BlendMode>() { static Type ty("mud::BlendMode"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::CullMode>() { static Type ty("mud::CullMode"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::DepthDraw>() { static Type ty("mud::DepthDraw"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::DepthTest>() { static Type ty("mud::DepthTest"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::EmitterFlow>() { static Type ty("mud::EmitterFlow"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Interpolation>() { static Type ty("mud::Interpolation"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::IsometricAngle>() { static Type ty("mud::IsometricAngle"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ItemFlag>() { static Type ty("mud::ItemFlag"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ItemShadow>() { static Type ty("mud::ItemShadow"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::LightType>() { static Type ty("mud::LightType"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::MSAA>() { static Type ty("mud::MSAA"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::MaterialFlag>() { static Type ty("mud::MaterialFlag"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ModelFormat>() { static Type ty("mud::ModelFormat"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Month>() { static Type ty("mud::Month"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::PassType>() { static Type ty("mud::PassType"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::PbrDiffuseMode>() { static Type ty("mud::PbrDiffuseMode"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::PbrShaderOption>() { static Type ty("mud::PbrShaderOption"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::PbrSpecularMode>() { static Type ty("mud::PbrSpecularMode"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::PrefabType>() { static Type ty("mud::PrefabType"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ShaderOption>() { static Type ty("mud::ShaderOption"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ShaderOptionFilter>() { static Type ty("mud::ShaderOptionFilter"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ShaderOptionResolve>() { static Type ty("mud::ShaderOptionResolve"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ShaderType>() { static Type ty("mud::ShaderType"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Shading>() { static Type ty("mud::Shading"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ShadowFlags>() { static Type ty("mud::ShadowFlags"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::TextureChannel>() { static Type ty("mud::TextureChannel"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::TextureHint>() { static Type ty("mud::TextureHint"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::TextureSampler>() { static Type ty("mud::TextureSampler"); return ty; }
    
    template <> MUD_GFX_EXPORT Type& type<mud::Animated>() { static Type ty("Animated"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::AnimatedTrack>() { static Type ty("AnimatedTrack"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Animation>() { static Type ty("Animation"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::AnimationPlay>() { static Type ty("AnimationPlay"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::AnimationTrack>() { static Type ty("AnimationTrack"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Background>() { static Type ty("Background"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BaseMaterialBlock>() { static Type ty("BaseMaterialBlock"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Bone>() { static Type ty("Bone"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Camera>() { static Type ty("Camera"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::DepthParams>() { static Type ty("DepthParams"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Environment>() { static Type ty("Environment"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Filter>() { static Type ty("Filter"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Fog>() { static Type ty("Fog"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::FrameBuffer>() { static Type ty("FrameBuffer"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::FresnelMaterialBlock>() { static Type ty("FresnelMaterialBlock"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Frustum>() { static Type ty("Frustum"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::FrustumSlice>() { static Type ty("FrustumSlice"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::GfxBlock>() { static Type ty("GfxBlock"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::GfxContext>() { static Type ty("GfxContext"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::GfxSystem>() { static Type ty("GfxSystem"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Gnode>() { static Type ty("Gnode"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ImmediateDraw>() { static Type ty("ImmediateDraw"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Item>() { static Type ty("Item"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Joint>() { static Type ty("Joint"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Light>() { static Type ty("Light"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Material>() { static Type ty("Material"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::MaterialParam<float>>() { static Type ty("MaterialParam<float>"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::MaterialParam<mud::Colour>>() { static Type ty("MaterialParam<mud::Colour>"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Mesh>() { static Type ty("Mesh"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Model>() { static Type ty("Model"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ModelItem>() { static Type ty("ModelItem"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Node3>() { static Type ty("Node3"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ParticleGenerator>() { static Type ty("ParticleGenerator"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::PbrMaterialBlock>() { static Type ty("PbrMaterialBlock"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Prefab>() { static Type ty("Prefab"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::PrefabNode>() { static Type ty("PrefabNode"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Program>() { static Type ty("Program"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Radiance>() { static Type ty("Radiance"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::RenderFrame>() { static Type ty("RenderFrame"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::RenderQuad>() { static Type ty("RenderQuad"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Rig>() { static Type ty("Rig"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Scene>() { static Type ty("Scene"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Shot>() { static Type ty("Shot"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Skeleton>() { static Type ty("Skeleton"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Skin>() { static Type ty("Skin"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Sun>() { static Type ty("Sun"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::SymbolIndex>() { static Type ty("SymbolIndex"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Texture>() { static Type ty("Texture"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::UnshadedMaterialBlock>() { static Type ty("UnshadedMaterialBlock"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Viewport>() { static Type ty("Viewport"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BlockCopy>() { static Type ty("BlockCopy", type<mud::GfxBlock>()); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BlockFilter>() { static Type ty("BlockFilter", type<mud::GfxBlock>()); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BlockParticles>() { static Type ty("BlockParticles", type<mud::GfxBlock>()); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BlockResolve>() { static Type ty("BlockResolve", type<mud::GfxBlock>()); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BlockSky>() { static Type ty("BlockSky", type<mud::GfxBlock>()); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::DrawBlock>() { static Type ty("DrawBlock", type<mud::GfxBlock>()); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BlockDepth>() { static Type ty("BlockDepth", type<mud::DrawBlock>()); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Particles>() { static Type ty("Particles", type<mud::ParticleGenerator>()); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::RenderTarget>() { static Type ty("RenderTarget", type<mud::FrameBuffer>()); return ty; }
}
