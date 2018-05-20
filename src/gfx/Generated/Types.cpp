

#include <gfx/Generated/Types.h>
#include <gfx/Generated/Module.h>
#include <obj/Proto.h>

namespace mud
{
    // Exported types
    template <> MUD_GFX_EXPORT Type& type<mud::BackgroundMode>() { static Type ty("mud::BackgroundMode"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BlendMode>() { static Type ty("mud::BlendMode"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::CSMFilterMode>() { static Type ty("mud::CSMFilterMode"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::CullMode>() { static Type ty("mud::CullMode"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::DepthDraw>() { static Type ty("mud::DepthDraw"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::DepthTest>() { static Type ty("mud::DepthTest"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::EmitterDirection>() { static Type ty("mud::EmitterDirection"); return ty; }
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
    template <> MUD_GFX_EXPORT Type& type<mud::ShaderModeShadow>() { static Type ty("mud::ShaderModeShadow"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ShaderOption>() { static Type ty("mud::ShaderOption"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ShaderOptionBlur>() { static Type ty("mud::ShaderOptionBlur"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ShaderOptionDofBlur>() { static Type ty("mud::ShaderOptionDofBlur"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ShaderOptionFilter>() { static Type ty("mud::ShaderOptionFilter"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ShaderOptionGlow>() { static Type ty("mud::ShaderOptionGlow"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ShaderOptionLight>() { static Type ty("mud::ShaderOptionLight"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ShaderOptionRadiance>() { static Type ty("mud::ShaderOptionRadiance"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ShaderOptionResolve>() { static Type ty("mud::ShaderOptionResolve"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ShaderOptionShadow>() { static Type ty("mud::ShaderOptionShadow"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ShaderType>() { static Type ty("mud::ShaderType"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Shading>() { static Type ty("mud::Shading"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ShadowFlags>() { static Type ty("mud::ShadowFlags"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::TextureChannel>() { static Type ty("mud::TextureChannel"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::TextureHint>() { static Type ty("mud::TextureHint"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::TextureSampler>() { static Type ty("mud::TextureSampler"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::TonemapMode>() { static Type ty("mud::TonemapMode"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::TonemapShaderMode>() { static Type ty("mud::TonemapShaderMode"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::TonemapShaderOption>() { static Type ty("mud::TonemapShaderOption"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::TrackMode>() { static Type ty("mud::TrackMode"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<glTFAlphaMode>() { static Type ty("glTFAlphaMode"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<glTFComponentType>() { static Type ty("glTFComponentType"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<glTFInterpolation>() { static Type ty("glTFInterpolation"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<glTFPrimitiveType>() { static Type ty("glTFPrimitiveType"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<glTFType>() { static Type ty("glTFType"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<std::vector<glTFAccessor>>() { static Type ty("std::vector<glTFAccessor>"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<std::vector<glTFAnimation>>() { static Type ty("std::vector<glTFAnimation>"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<std::vector<glTFAnimationChannel>>() { static Type ty("std::vector<glTFAnimationChannel>"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<std::vector<glTFAnimationSampler>>() { static Type ty("std::vector<glTFAnimationSampler>"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<std::vector<glTFBuffer>>() { static Type ty("std::vector<glTFBuffer>"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<std::vector<glTFBufferView>>() { static Type ty("std::vector<glTFBufferView>"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<std::vector<glTFCamera>>() { static Type ty("std::vector<glTFCamera>"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<std::vector<glTFImage>>() { static Type ty("std::vector<glTFImage>"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<std::vector<glTFMaterial>>() { static Type ty("std::vector<glTFMaterial>"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<std::vector<glTFMesh>>() { static Type ty("std::vector<glTFMesh>"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<std::vector<glTFMorphTarget>>() { static Type ty("std::vector<glTFMorphTarget>"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<std::vector<glTFNode>>() { static Type ty("std::vector<glTFNode>"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<std::vector<glTFPrimitive>>() { static Type ty("std::vector<glTFPrimitive>"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<std::vector<glTFScene>>() { static Type ty("std::vector<glTFScene>"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<std::vector<glTFSkin>>() { static Type ty("std::vector<glTFSkin>"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<std::vector<glTFTexture>>() { static Type ty("std::vector<glTFTexture>"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<std::vector<int>>() { static Type ty("std::vector<int>"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<std::vector<mud::PrefabNode>>() { static Type ty("std::vector<mud::PrefabNode>"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<std::vector<mud::quat>>() { static Type ty("std::vector<mud::quat>"); return ty; }
    
    template <> MUD_GFX_EXPORT Type& type<mud::Animated>() { static Type ty("Animated"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::AnimatedTrack>() { static Type ty("AnimatedTrack"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Animation>() { static Type ty("Animation"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::AnimationPlay>() { static Type ty("AnimationPlay"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::AnimationTrack>() { static Type ty("AnimationTrack"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BCS>() { static Type ty("BCS"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Background>() { static Type ty("Background"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BaseMaterialBlock>() { static Type ty("BaseMaterialBlock"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Bone>() { static Type ty("Bone"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Camera>() { static Type ty("Camera"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::DepthParams>() { static Type ty("DepthParams"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::DofBlur>() { static Type ty("DofBlur"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Environment>() { static Type ty("Environment"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Filter>() { static Type ty("Filter"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::FrameBuffer>() { static Type ty("FrameBuffer"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Frustum>() { static Type ty("Frustum"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::FrustumSlice>() { static Type ty("FrustumSlice"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::GfxBlock>() { static Type ty("GfxBlock"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::GfxContext>() { static Type ty("GfxContext"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::GfxSystem>() { static Type ty("GfxSystem"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Glow>() { static Type ty("Glow"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Gnode>() { static Type ty("Gnode"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ImmediateDraw>() { static Type ty("ImmediateDraw"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Item>() { static Type ty("Item"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Joint>() { static Type ty("Joint"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Light>() { static Type ty("Light"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::LightShadow>() { static Type ty("LightShadow"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Material>() { static Type ty("Material"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::MaterialParam<float>>() { static Type ty("MaterialParam<float>"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::MaterialParam<mud::Colour>>() { static Type ty("MaterialParam<mud::Colour>"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Mesh>() { static Type ty("Mesh"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Model>() { static Type ty("Model"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ModelItem>() { static Type ty("ModelItem"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Node3>() { static Type ty("Node3"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ParticleGenerator>() { static Type ty("ParticleGenerator"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Particles>() { static Type ty("Particles"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::PbrMaterialBlock>() { static Type ty("PbrMaterialBlock"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::PrefabNode>() { static Type ty("PrefabNode"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Program>() { static Type ty("Program"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Radiance>() { static Type ty("Radiance"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ReflectionProbe>() { static Type ty("ReflectionProbe"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::RenderFilters>() { static Type ty("RenderFilters"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::RenderFrame>() { static Type ty("RenderFrame"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::RenderQuad>() { static Type ty("RenderQuad"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Rig>() { static Type ty("Rig"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Scene>() { static Type ty("Scene"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Shot>() { static Type ty("Shot"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Skeleton>() { static Type ty("Skeleton"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Skin>() { static Type ty("Skin"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::SpaceQuad>() { static Type ty("SpaceQuad"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Sun>() { static Type ty("Sun"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::SymbolIndex>() { static Type ty("SymbolIndex"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Texture>() { static Type ty("Texture"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Tonemap>() { static Type ty("Tonemap"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Transform>() { static Type ty("Transform"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::UnshadedMaterialBlock>() { static Type ty("UnshadedMaterialBlock"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ValueCurve<float>>() { static Type ty("ValueCurve<float>"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ValueCurve<mud::Colour>>() { static Type ty("ValueCurve<mud::Colour>"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ValueCurve<mud::quat>>() { static Type ty("ValueCurve<mud::quat>"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ValueCurve<mud::vec3>>() { static Type ty("ValueCurve<mud::vec3>"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ValueCurve<uint32_t>>() { static Type ty("ValueCurve<uint32_t>"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ValueTrack<float>>() { static Type ty("ValueTrack<float>"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ValueTrack<mud::Colour>>() { static Type ty("ValueTrack<mud::Colour>"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ValueTrack<mud::quat>>() { static Type ty("ValueTrack<mud::quat>"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ValueTrack<mud::vec3>>() { static Type ty("ValueTrack<mud::vec3>"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ValueTrack<uint32_t>>() { static Type ty("ValueTrack<uint32_t>"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ViewerController>() { static Type ty("ViewerController"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Viewport>() { static Type ty("Viewport"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<glTF>() { static Type ty("glTF"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<glTFAccessor>() { static Type ty("glTFAccessor"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<glTFAnimation>() { static Type ty("glTFAnimation"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<glTFAnimationChannel>() { static Type ty("glTFAnimationChannel"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<glTFAnimationSampler>() { static Type ty("glTFAnimationSampler"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<glTFAnimationTarget>() { static Type ty("glTFAnimationTarget"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<glTFAttributes>() { static Type ty("glTFAttributes"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<glTFBuffer>() { static Type ty("glTFBuffer"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<glTFBufferView>() { static Type ty("glTFBufferView"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<glTFCamera>() { static Type ty("glTFCamera"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<glTFImage>() { static Type ty("glTFImage"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::glTFImport>() { static Type ty("glTFImport"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<glTFMaterial>() { static Type ty("glTFMaterial"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<glTFMaterialPBR>() { static Type ty("glTFMaterialPBR"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<glTFMesh>() { static Type ty("glTFMesh"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<glTFMorphTarget>() { static Type ty("glTFMorphTarget"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<glTFNode>() { static Type ty("glTFNode"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<glTFOrthographic>() { static Type ty("glTFOrthographic"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<glTFPerspective>() { static Type ty("glTFPerspective"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<glTFPrimitive>() { static Type ty("glTFPrimitive"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<glTFSampler>() { static Type ty("glTFSampler"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<glTFScene>() { static Type ty("glTFScene"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<glTFSkin>() { static Type ty("glTFSkin"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<glTFSparse>() { static Type ty("glTFSparse"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<glTFSparseIndices>() { static Type ty("glTFSparseIndices"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<glTFSparseValues>() { static Type ty("glTFSparseValues"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<glTFTexture>() { static Type ty("glTFTexture"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<glTFTextureInfo>() { static Type ty("glTFTextureInfo"); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BlockBlur>() { static Type ty("BlockBlur", type<mud::GfxBlock>()); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BlockCopy>() { static Type ty("BlockCopy", type<mud::GfxBlock>()); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BlockDofBlur>() { static Type ty("BlockDofBlur", type<mud::GfxBlock>()); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BlockFilter>() { static Type ty("BlockFilter", type<mud::GfxBlock>()); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BlockGlow>() { static Type ty("BlockGlow", type<mud::GfxBlock>()); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BlockReflection>() { static Type ty("BlockReflection", type<mud::GfxBlock>()); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BlockResolve>() { static Type ty("BlockResolve", type<mud::GfxBlock>()); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BlockSky>() { static Type ty("BlockSky", type<mud::GfxBlock>()); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BlockTonemap>() { static Type ty("BlockTonemap", type<mud::GfxBlock>()); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::DrawBlock>() { static Type ty("DrawBlock", type<mud::GfxBlock>()); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BlockDepth>() { static Type ty("BlockDepth", type<mud::DrawBlock>()); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BlockLight>() { static Type ty("BlockLight", type<mud::DrawBlock>()); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BlockParticles>() { static Type ty("BlockParticles", type<mud::DrawBlock>()); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BlockRadiance>() { static Type ty("BlockRadiance", type<mud::DrawBlock>()); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BlockShadow>() { static Type ty("BlockShadow", type<mud::DrawBlock>()); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Viewer>() { static Type ty("Viewer", type<mud::Widget>()); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::SpaceSheet>() { static Type ty("SpaceSheet", type<mud::RootSheet>()); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::RenderTarget>() { static Type ty("RenderTarget", type<mud::FrameBuffer>()); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::SceneViewer>() { static Type ty("SceneViewer", type<mud::Scene>()); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ParticleEmitter>() { static Type ty("ParticleEmitter", type<mud::ParticleGenerator>()); return ty; }
}
