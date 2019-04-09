#pragma once

#include <infra/Config.h>

#include <infra/Forward.h>
#include <jobs/Forward.h>
#include <type/Forward.h>
#include <pool/Forward.h>
#include <math/Forward.h>
#include <geom/Forward.h>
#include <ctx/Forward.h>
#include <ctx-glfw/Forward.h>
#include <bgfx/Forward.h>

#ifndef MUD_GFX_EXPORT
#define MUD_GFX_EXPORT MUD_IMPORT
#endif

namespace mud
{
	enum class AnimTarget : unsigned int;
    enum class Interpolation : unsigned int;
    enum class TextureHint : unsigned int;
    enum class ShaderType : unsigned int;
	enum class ShaderColor : unsigned int;
    enum ShaderOption : unsigned int;
    enum class TextureSampler : unsigned int;
    enum class PassType : unsigned int;
    enum class BlendMode : unsigned int;
    enum class CullMode : unsigned int;
    enum class DepthDraw : unsigned int;
    enum class DepthTest : unsigned int;
	enum class DepthMethod : unsigned int;
    enum class MaterialFlag : unsigned int;
	enum class TextureFormat : unsigned int;
    enum class TextureChannel : unsigned int;
	enum class MaterialBlock : unsigned int;
	enum class Lighting : unsigned int;
    enum class PbrDiffuseMode : unsigned int;
    enum class PbrSpecularMode : unsigned int;
	enum class PhongEnvBlendMode : unsigned int;
    enum PbrShaderOption : unsigned int;
    enum class ModelFormat : unsigned int;
    enum class EmitterFlow : unsigned int;
    enum class PrefabType : unsigned int;
    enum IsometricAngle : unsigned int;
    enum ShaderOptionResolve : unsigned int;
    enum ShaderOptionFilter : unsigned int;
    enum class LightType : unsigned int;
    enum ShadowFlags : unsigned int;
    enum class ItemShadow : unsigned int;
    enum class MSAA : unsigned int;
    enum class Shading : unsigned int;
    enum class BackgroundMode : unsigned int;
    enum class Month : unsigned int;
    
    template <class T> class AssetStore;
    template <class T> struct MaterialParam;
    
    struct AnimCursor;
    class AnimTrack;
    class Animation;
    class Node3;
    class Skeleton;
    struct Joint;
    class Skin;
    class Rig;
    struct AnimatedTrack;
    struct AnimPlay;
    class Mime;
    class GfxWindow;
    struct LocatedFile;
    class GfxSystem;
    class Texture;
    struct ShaderDefine;
    struct ShaderBlock;
	struct ProgramMode;
    struct ProgramBlock;
    class Program;
    struct ProgramVersion;
    struct Pass;
    struct RenderFrame;
    struct Render;
    class GfxBlock;
    class DrawBlock;
    struct DrawElement;
	struct DrawCluster;
    class Renderer;
    struct MaterialBase;
	struct MaterialAlpha;
    struct MaterialSolid;
	struct MaterialPoint;
	struct MaterialLine;
	struct MaterialLit;
    struct MaterialFresnel;
    struct MaterialPbr;
	struct MaterialPhong;
	struct MaterialUser;
    class Material;
	class BlockMaterial;
	class Import;
    struct ImportConfig;
	class Importer;
    struct ModelElem;
    class Model;
    struct GpuMesh;
    class Mesh;
    struct Particle;
    struct ParticleSort;
    struct Flow;
    struct ParticleVertex;
    struct Flare;
    class ParticleSystem;
    class BlockParticles;
    class PassParticles;
    struct PrefabNode;
    class Prefab;
    class Camera;
	class Culler;
	class Froxelizer;
    struct DepthParams;
	struct DistanceParams;
    class PassDepth;
    class BlockDepth;
    class ImmediateDraw;
    class SymbolIndex;
    class PassEffects;
    class PassPostProcess;
    struct FilterUniform;
    class Filter;
    struct RenderQuad;
    class BlockFilter;
    class BlockCopy;
    class Frustum;
    struct FrustumSlice;
	struct ClusteredFrustum;
    class Light;
	class Lines;
    class Gnode;
	class Item;
	class Direct;
	struct Batch;
    class Viewport;
    struct PickQuery;
    class Picker;
    struct PassJobs;
    class PassClear;
    class PassSolid;
    class PassBackground;
    class PassFlip;
    struct MinimalRenderer;
    struct SolidRenderer;
    struct ClearRenderer;
    class FrameBuffer;
	class SwapBuffer;
	class Cascade;
	class SwapCascade;
    class RenderTarget;
    struct Sun;
    struct Radiance;
	struct Skylight;
    struct Background;
    struct Fog;
    struct Zone;
    class Scene;
    class Shot;
    struct Uniform;
    struct Sampler;
    struct UniformBlock;
    class BlockSky;
	class GIProbe;
	class ReflectionProbe;
	class Lightmap;
	class LightmapAtlas;
	class LightmapItem;
}

#ifdef MUD_META_GENERATOR
#include <stl/vector.h>
#include <stl/span.h>
namespace stl
{
	export_ extern template struct refl_ span_ span<mud::mat4>;

	export_ extern template class refl_ span_ span<mud::Texture*>;

	export_ extern template class refl_ seque_ vector<mud::Mesh*>;
	export_ extern template class refl_ seque_ vector<mud::Model*>;
	export_ extern template class refl_ seque_ vector<mud::Texture*>;
	export_ extern template class refl_ seque_ vector<mud::Material*>;

	export_ extern template class refl_ seque_ vector<mud::Animation*>;
	export_ extern template class refl_ seque_ vector<mud::AnimPlay>;
}
#endif
