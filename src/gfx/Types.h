#pragma once

#include <gfx/Forward.h>

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <obj/Type.h>
#include <obj/Vector.h>
#endif

#ifndef MUD_MODULES
#include <infra/Types.h>
#include <obj/Types.h>
#include <pool/Types.h>
#include <refl/Types.h>
#include <srlz/Types.h>
#include <math/Types.h>
#include <geom/Types.h>
#include <ctx/Types.h>
#include <ctx-glfw/Types.h>
#include <bgfx/Types.h>
#endif

#ifndef MUD_CPP_20
#include <string>
#include <cstdint>
#include <vector>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_GFX_EXPORT Type& type<mud::BackgroundMode>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::BlendMode>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::CullMode>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::DepthDraw>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::DepthTest>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::EmitterFlow>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Interpolation>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::IsometricAngle>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::ItemFlag>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::ItemShadow>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::LightType>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::MSAA>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::MaterialFlag>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::ModelFormat>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Month>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::PassType>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::PbrDiffuseMode>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::PbrShaderOption>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::PbrSpecularMode>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::PrefabType>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::ShaderOption>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::ShaderOptionFilter>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::ShaderOptionResolve>();
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
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Background>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::BaseMaterialBlock>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Bone>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Camera>();
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
    export_ template <> MUD_GFX_EXPORT Type& type<mud::ParticleGenerator>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::PbrMaterialBlock>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Prefab>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::PrefabNode>();
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
    export_ template <> MUD_GFX_EXPORT Type& type<mud::BlockFilter>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::BlockParticles>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::BlockResolve>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::BlockSky>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::DrawBlock>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::BlockDepth>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Particles>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::RenderTarget>();
    
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::Animated*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::AnimatedTrack*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::Animation*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::AnimationPlay*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::AnimationTrack*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::Background*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::BaseMaterialBlock*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::Bone*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::Camera*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::DepthParams*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::Environment*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::Filter*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::Fog*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::FrameBuffer*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::FresnelMaterialBlock*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::Frustum*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::FrustumSlice*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::GfxBlock*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::GfxContext*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::GfxSystem*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::Gnode*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::ImmediateDraw*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::Item*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::Joint*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::Light*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::Material*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::MaterialParam<float>*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::MaterialParam<mud::Colour>*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::Mesh*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::Model*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::ModelItem*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::Node3*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::ParticleGenerator*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::PbrMaterialBlock*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::Prefab*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::PrefabNode*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::Program*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::Radiance*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::RenderFrame*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::RenderQuad*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::Rig*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::Scene*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::Shot*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::Skeleton*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::Skin*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::Sun*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::SymbolIndex*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::Texture*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::UnshadedMaterialBlock*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::Viewport*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::BlockCopy*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::BlockFilter*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::BlockParticles*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::BlockResolve*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::BlockSky*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::DrawBlock*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::BlockDepth*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::Particles*>>;
	export_ template struct MUD_GFX_EXPORT Typed<std::vector<mud::RenderTarget*>>;
}
