#pragma once

#include <gfx/Generated/Forward.h>

#include <obj/Generated/Types.h>
#include <math/Generated/Types.h>
#include <geom/Generated/Types.h>
#include <ui/Generated/Types.h>

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
    template <> MUD_GFX_EXPORT Type& type<mud::CSMFilterMode>();
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
    template <> MUD_GFX_EXPORT Type& type<mud::ShaderModeShadow>();
    template <> MUD_GFX_EXPORT Type& type<mud::ShaderOption>();
    template <> MUD_GFX_EXPORT Type& type<mud::ShaderOptionBlur>();
    template <> MUD_GFX_EXPORT Type& type<mud::ShaderOptionDofBlur>();
    template <> MUD_GFX_EXPORT Type& type<mud::ShaderOptionFilter>();
    template <> MUD_GFX_EXPORT Type& type<mud::ShaderOptionGlow>();
    template <> MUD_GFX_EXPORT Type& type<mud::ShaderOptionLight>();
    template <> MUD_GFX_EXPORT Type& type<mud::ShaderOptionRadiance>();
    template <> MUD_GFX_EXPORT Type& type<mud::ShaderOptionResolve>();
    template <> MUD_GFX_EXPORT Type& type<mud::ShaderOptionShadow>();
    template <> MUD_GFX_EXPORT Type& type<mud::ShaderType>();
    template <> MUD_GFX_EXPORT Type& type<mud::Shading>();
    template <> MUD_GFX_EXPORT Type& type<mud::ShadowFlags>();
    template <> MUD_GFX_EXPORT Type& type<mud::TextureChannel>();
    template <> MUD_GFX_EXPORT Type& type<mud::TextureHint>();
    template <> MUD_GFX_EXPORT Type& type<mud::TextureSampler>();
    template <> MUD_GFX_EXPORT Type& type<mud::TonemapMode>();
    template <> MUD_GFX_EXPORT Type& type<mud::TonemapShaderMode>();
    template <> MUD_GFX_EXPORT Type& type<mud::TonemapShaderOption>();
    template <> MUD_GFX_EXPORT Type& type<mud::TrackMode>();
    template <> MUD_GFX_EXPORT Type& type<glTFAlphaMode>();
    template <> MUD_GFX_EXPORT Type& type<glTFComponentType>();
    template <> MUD_GFX_EXPORT Type& type<glTFInterpolation>();
    template <> MUD_GFX_EXPORT Type& type<glTFPrimitiveType>();
    template <> MUD_GFX_EXPORT Type& type<glTFType>();
    template <> MUD_GFX_EXPORT Type& type<std::vector<glTFAccessor>>();
    template <> MUD_GFX_EXPORT Type& type<std::vector<glTFAnimation>>();
    template <> MUD_GFX_EXPORT Type& type<std::vector<glTFAnimationChannel>>();
    template <> MUD_GFX_EXPORT Type& type<std::vector<glTFAnimationSampler>>();
    template <> MUD_GFX_EXPORT Type& type<std::vector<glTFBuffer>>();
    template <> MUD_GFX_EXPORT Type& type<std::vector<glTFBufferView>>();
    template <> MUD_GFX_EXPORT Type& type<std::vector<glTFCamera>>();
    template <> MUD_GFX_EXPORT Type& type<std::vector<glTFImage>>();
    template <> MUD_GFX_EXPORT Type& type<std::vector<glTFMaterial>>();
    template <> MUD_GFX_EXPORT Type& type<std::vector<glTFMesh>>();
    template <> MUD_GFX_EXPORT Type& type<std::vector<glTFMorphTarget>>();
    template <> MUD_GFX_EXPORT Type& type<std::vector<glTFNode>>();
    template <> MUD_GFX_EXPORT Type& type<std::vector<glTFPrimitive>>();
    template <> MUD_GFX_EXPORT Type& type<std::vector<glTFScene>>();
    template <> MUD_GFX_EXPORT Type& type<std::vector<glTFSkin>>();
    template <> MUD_GFX_EXPORT Type& type<std::vector<glTFTexture>>();
    template <> MUD_GFX_EXPORT Type& type<std::vector<int>>();
    template <> MUD_GFX_EXPORT Type& type<std::vector<mud::PrefabNode>>();
    template <> MUD_GFX_EXPORT Type& type<std::vector<mud::quat>>();
    
    template <> MUD_GFX_EXPORT Type& type<mud::Animated>();
    template <> MUD_GFX_EXPORT Type& type<mud::AnimatedTrack>();
    template <> MUD_GFX_EXPORT Type& type<mud::Animation>();
    template <> MUD_GFX_EXPORT Type& type<mud::AnimationPlay>();
    template <> MUD_GFX_EXPORT Type& type<mud::AnimationTrack>();
    template <> MUD_GFX_EXPORT Type& type<mud::BCS>();
    template <> MUD_GFX_EXPORT Type& type<mud::Background>();
    template <> MUD_GFX_EXPORT Type& type<mud::BaseMaterialBlock>();
    template <> MUD_GFX_EXPORT Type& type<mud::Bone>();
    template <> MUD_GFX_EXPORT Type& type<mud::Camera>();
    template <> MUD_GFX_EXPORT Type& type<mud::DepthParams>();
    template <> MUD_GFX_EXPORT Type& type<mud::DofBlur>();
    template <> MUD_GFX_EXPORT Type& type<mud::Environment>();
    template <> MUD_GFX_EXPORT Type& type<mud::Filter>();
    template <> MUD_GFX_EXPORT Type& type<mud::FrameBuffer>();
    template <> MUD_GFX_EXPORT Type& type<mud::Frustum>();
    template <> MUD_GFX_EXPORT Type& type<mud::FrustumSlice>();
    template <> MUD_GFX_EXPORT Type& type<mud::GfxBlock>();
    template <> MUD_GFX_EXPORT Type& type<mud::GfxContext>();
    template <> MUD_GFX_EXPORT Type& type<mud::GfxSystem>();
    template <> MUD_GFX_EXPORT Type& type<mud::Glow>();
    template <> MUD_GFX_EXPORT Type& type<mud::Gnode>();
    template <> MUD_GFX_EXPORT Type& type<mud::ImmediateDraw>();
    template <> MUD_GFX_EXPORT Type& type<mud::Item>();
    template <> MUD_GFX_EXPORT Type& type<mud::Joint>();
    template <> MUD_GFX_EXPORT Type& type<mud::Light>();
    template <> MUD_GFX_EXPORT Type& type<mud::LightShadow>();
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
    template <> MUD_GFX_EXPORT Type& type<mud::PrefabNode>();
    template <> MUD_GFX_EXPORT Type& type<mud::Program>();
    template <> MUD_GFX_EXPORT Type& type<mud::Radiance>();
    template <> MUD_GFX_EXPORT Type& type<mud::ReflectionProbe>();
    template <> MUD_GFX_EXPORT Type& type<mud::RenderFilters>();
    template <> MUD_GFX_EXPORT Type& type<mud::RenderFrame>();
    template <> MUD_GFX_EXPORT Type& type<mud::RenderQuad>();
    template <> MUD_GFX_EXPORT Type& type<mud::Rig>();
    template <> MUD_GFX_EXPORT Type& type<mud::Scene>();
    template <> MUD_GFX_EXPORT Type& type<mud::Shot>();
    template <> MUD_GFX_EXPORT Type& type<mud::Skeleton>();
    template <> MUD_GFX_EXPORT Type& type<mud::Skin>();
    template <> MUD_GFX_EXPORT Type& type<mud::SpaceQuad>();
    template <> MUD_GFX_EXPORT Type& type<mud::Sun>();
    template <> MUD_GFX_EXPORT Type& type<mud::SymbolIndex>();
    template <> MUD_GFX_EXPORT Type& type<mud::Texture>();
    template <> MUD_GFX_EXPORT Type& type<mud::Tonemap>();
    template <> MUD_GFX_EXPORT Type& type<mud::Transform>();
    template <> MUD_GFX_EXPORT Type& type<mud::UnshadedMaterialBlock>();
    template <> MUD_GFX_EXPORT Type& type<mud::ValueCurve<float>>();
    template <> MUD_GFX_EXPORT Type& type<mud::ValueCurve<mud::Colour>>();
    template <> MUD_GFX_EXPORT Type& type<mud::ValueCurve<mud::quat>>();
    template <> MUD_GFX_EXPORT Type& type<mud::ValueCurve<mud::vec3>>();
    template <> MUD_GFX_EXPORT Type& type<mud::ValueCurve<uint32_t>>();
    template <> MUD_GFX_EXPORT Type& type<mud::ValueTrack<float>>();
    template <> MUD_GFX_EXPORT Type& type<mud::ValueTrack<mud::Colour>>();
    template <> MUD_GFX_EXPORT Type& type<mud::ValueTrack<mud::quat>>();
    template <> MUD_GFX_EXPORT Type& type<mud::ValueTrack<mud::vec3>>();
    template <> MUD_GFX_EXPORT Type& type<mud::ValueTrack<uint32_t>>();
    template <> MUD_GFX_EXPORT Type& type<mud::ViewerController>();
    template <> MUD_GFX_EXPORT Type& type<mud::Viewport>();
    template <> MUD_GFX_EXPORT Type& type<glTF>();
    template <> MUD_GFX_EXPORT Type& type<glTFAccessor>();
    template <> MUD_GFX_EXPORT Type& type<glTFAnimation>();
    template <> MUD_GFX_EXPORT Type& type<glTFAnimationChannel>();
    template <> MUD_GFX_EXPORT Type& type<glTFAnimationSampler>();
    template <> MUD_GFX_EXPORT Type& type<glTFAnimationTarget>();
    template <> MUD_GFX_EXPORT Type& type<glTFAttributes>();
    template <> MUD_GFX_EXPORT Type& type<glTFBuffer>();
    template <> MUD_GFX_EXPORT Type& type<glTFBufferView>();
    template <> MUD_GFX_EXPORT Type& type<glTFCamera>();
    template <> MUD_GFX_EXPORT Type& type<glTFImage>();
    template <> MUD_GFX_EXPORT Type& type<mud::glTFImport>();
    template <> MUD_GFX_EXPORT Type& type<glTFMaterial>();
    template <> MUD_GFX_EXPORT Type& type<glTFMaterialPBR>();
    template <> MUD_GFX_EXPORT Type& type<glTFMesh>();
    template <> MUD_GFX_EXPORT Type& type<glTFMorphTarget>();
    template <> MUD_GFX_EXPORT Type& type<glTFNode>();
    template <> MUD_GFX_EXPORT Type& type<glTFOrthographic>();
    template <> MUD_GFX_EXPORT Type& type<glTFPerspective>();
    template <> MUD_GFX_EXPORT Type& type<glTFPrimitive>();
    template <> MUD_GFX_EXPORT Type& type<glTFSampler>();
    template <> MUD_GFX_EXPORT Type& type<glTFScene>();
    template <> MUD_GFX_EXPORT Type& type<glTFSkin>();
    template <> MUD_GFX_EXPORT Type& type<glTFSparse>();
    template <> MUD_GFX_EXPORT Type& type<glTFSparseIndices>();
    template <> MUD_GFX_EXPORT Type& type<glTFSparseValues>();
    template <> MUD_GFX_EXPORT Type& type<glTFTexture>();
    template <> MUD_GFX_EXPORT Type& type<glTFTextureInfo>();
    template <> MUD_GFX_EXPORT Type& type<mud::BlockBlur>();
    template <> MUD_GFX_EXPORT Type& type<mud::BlockCopy>();
    template <> MUD_GFX_EXPORT Type& type<mud::BlockDofBlur>();
    template <> MUD_GFX_EXPORT Type& type<mud::BlockFilter>();
    template <> MUD_GFX_EXPORT Type& type<mud::BlockGlow>();
    template <> MUD_GFX_EXPORT Type& type<mud::BlockReflection>();
    template <> MUD_GFX_EXPORT Type& type<mud::BlockResolve>();
    template <> MUD_GFX_EXPORT Type& type<mud::BlockSky>();
    template <> MUD_GFX_EXPORT Type& type<mud::BlockTonemap>();
    template <> MUD_GFX_EXPORT Type& type<mud::DrawBlock>();
    template <> MUD_GFX_EXPORT Type& type<mud::BlockDepth>();
    template <> MUD_GFX_EXPORT Type& type<mud::BlockLight>();
    template <> MUD_GFX_EXPORT Type& type<mud::BlockParticles>();
    template <> MUD_GFX_EXPORT Type& type<mud::BlockRadiance>();
    template <> MUD_GFX_EXPORT Type& type<mud::BlockShadow>();
    template <> MUD_GFX_EXPORT Type& type<mud::Viewer>();
    template <> MUD_GFX_EXPORT Type& type<mud::SpaceSheet>();
    template <> MUD_GFX_EXPORT Type& type<mud::RenderTarget>();
    template <> MUD_GFX_EXPORT Type& type<mud::SceneViewer>();
    template <> MUD_GFX_EXPORT Type& type<mud::ParticleEmitter>();
}
