#pragma once

#include <infra/Config.h>

#ifndef TWO_GFX_EXPORT
#define TWO_GFX_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ enum class AnimTarget : unsigned int;
    export_ enum class Interpolation : unsigned int;
    export_ enum class TextureHint : unsigned int;
    export_ enum class ShaderType : unsigned int;
	export_ enum class ShaderColor : unsigned int;
    export_ enum ShaderOption : unsigned int;
    export_ enum class TextureSampler : unsigned int;
    export_ enum class PassType : unsigned int;
    export_ enum class BlendMode : unsigned int;
    export_ enum class CullMode : unsigned int;
    export_ enum class DepthDraw : unsigned int;
    export_ enum class DepthTest : unsigned int;
	export_ enum class DepthMethod : unsigned int;
    export_ enum class MaterialFlag : unsigned int;
	export_ enum class TextureFormat : unsigned int;
    export_ enum class TextureChannel : unsigned int;
	export_ enum class MaterialBlock : unsigned int;
	export_ enum class Lighting : unsigned int;
    export_ enum class PbrDiffuseMode : unsigned int;
    export_ enum class PbrSpecularMode : unsigned int;
	export_ enum class PhongEnvBlendMode : unsigned int;
    export_ enum PbrShaderOption : unsigned int;
    export_ enum class ModelFormat : unsigned int;
    export_ enum class EmitterFlow : unsigned int;
    export_ enum class PrefabType : unsigned int;
    export_ enum IsometricAngle : unsigned int;
    export_ enum ShaderOptionResolve : unsigned int;
    export_ enum ShaderOptionFilter : unsigned int;
    export_ enum class LightType : unsigned int;
    export_ enum ShadowFlags : unsigned int;
    export_ enum class ItemShadow : unsigned int;
    export_ enum class MSAA : unsigned int;
    export_ enum class Shading : unsigned int;
    export_ enum class BackgroundMode : unsigned int;
    export_ enum class Month : unsigned int;
    
    export_ template <class T> class AssetStore;
    export_ template <class T> struct MaterialParam;

	export_ struct AnimNode;
	export_ struct AnimCursor;
	export_ struct AnimPlay;
    export_ class AnimTrack;
    export_ class Animation;
    export_ class Node3;
    export_ class Skeleton;
    export_ struct Joint;
    export_ class Skin;
    export_ class Rig;
    export_ class Mime;
	export_ struct MirrorCamera;
    export_ class GfxWindow;
    export_ struct LocatedFile;
    export_ class GfxSystem;
    export_ class Texture;
    export_ struct ShaderDefine;
    export_ struct ShaderBlock;
	export_ struct ProgramMode;
    export_ struct ProgramBlock;
    export_ class Program;
    export_ struct ProgramVersion;
    export_ struct Pass;
    export_ struct RenderFrame;
    export_ struct Render;
    export_ class GfxBlock;
    export_ class DrawBlock;
    export_ struct DrawElement;
	export_ struct DrawCluster;
    export_ class Renderer;
    export_ struct MaterialBase;
	export_ struct MaterialAlpha;
    export_ struct MaterialSolid;
	export_ struct MaterialPoint;
	export_ struct MaterialLine;
	export_ struct MaterialLit;
    export_ struct MaterialFresnel;
    export_ struct MaterialPbr;
	export_ struct MaterialPhong;
	export_ struct MaterialUser;
    export_ class Material;
	export_ class BlockMaterial;
	export_ class Import;
    export_ struct ImportConfig;
	export_ class Importer;
    export_ struct ModelElem;
    export_ class Model;
    export_ struct GpuMesh;
    export_ class Mesh;
    export_ struct Particle;
    export_ struct ParticleSort;
    export_ struct Flow;
    export_ struct ParticleVertex;
    export_ struct Flare;
    export_ class ParticleSystem;
    export_ class BlockParticles;
    export_ class PassParticles;
    export_ struct PrefabNode;
    export_ class Prefab;
    export_ class Camera;
	export_ class Culler;
	export_ class Froxelizer;
    export_ struct DepthParams;
	export_ struct DistanceParams;
    export_ class PassDepth;
    export_ class BlockDepth;
    export_ class ImmediateDraw;
    export_ class SymbolIndex;
    export_ class PassEffects;
    export_ class PassPostProcess;
    export_ struct FilterUniform;
    export_ class Filter;
    export_ struct RenderQuad;
    export_ class BlockFilter;
    export_ class BlockCopy;
    export_ class Frustum;
    export_ struct FrustumSlice;
	export_ struct ClusteredFrustum;
    export_ class Light;
	export_ class Lines;
    export_ class Gnode;
	export_ class Item;
	export_ class Direct;
	export_ struct Batch;
    export_ class Viewport;
    export_ struct PickQuery;
    export_ class Picker;
    export_ struct PassJobs;
    export_ class PassClear;
    export_ class PassSolid;
    export_ class PassBackground;
    export_ class PassFlip;
    export_ struct MinimalRenderer;
    export_ struct SolidRenderer;
    export_ struct ClearRenderer;
    export_ class FrameBuffer;
	export_ class SwapBuffer;
	export_ class Cascade;
	export_ class SwapCascade;
    export_ class RenderTarget;
    export_ struct Sun;
    export_ struct Radiance;
	export_ struct Skylight;
    export_ struct Background;
    export_ struct Fog;
    export_ struct Zone;
    export_ class Scene;
    export_ class Shot;
    export_ struct Uniform;
    export_ struct Sampler;
    export_ struct UniformBlock;
    export_ class BlockSky;
}

#ifdef TWO_META_GENERATOR
#include <stl/vector.h>
#include <stl/span.h>
namespace stl
{
	extern template struct refl_ span_ span<two::mat4>;

	extern template struct refl_ span_ span<two::Node3>;
	extern template struct refl_ span_ span<two::Item>;
	extern template struct refl_ span_ span<two::Batch>;
	extern template struct refl_ span_ span<two::Direct>;
	extern template struct refl_ span_ span<two::Mime>;
	extern template struct refl_ span_ span<two::Light>;
	extern template struct refl_ span_ span<two::Flare>;

	extern template struct refl_ span_ span<two::Texture*>;

	extern template class refl_ seque_ vector<two::Mesh*>;
	extern template class refl_ seque_ vector<two::Model*>;
	extern template class refl_ seque_ vector<two::Texture*>;
	extern template class refl_ seque_ vector<two::Material*>;

	extern template class refl_ seque_ vector<two::Animation*>;
	extern template class refl_ seque_ vector<two::AnimPlay>;
}
#endif
