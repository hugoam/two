

#pragma once

#include <obj/Config.h>

#include <obj/Generated/Forward.h>
#include <math/Generated/Forward.h>
#include <geom/Generated/Forward.h>
#include <ui/Generated/Forward.h>

#if defined MUD_GFX_LIB
#define MUD_GFX_EXPORT MUD_EXPORT
#else
#define MUD_GFX_EXPORT MUD_IMPORT
#endif


    enum class glTFComponentType : unsigned int;
    enum class glTFType : unsigned int;
    enum class glTFPrimitiveType : unsigned int;
    enum class glTFInterpolation : unsigned int;
    enum class glTFAlphaMode : unsigned int;
    
    
    struct glTFBuffer;
    struct glTFImage;
    struct glTFBufferView;
    struct glTFSparseIndices;
    struct glTFSparseValues;
    struct glTFSparse;
    struct glTFAccessor;
    struct glTFSampler;
    struct glTFTexture;
    struct glTFSkin;
    struct glTFAttributes;
    struct glTFMorphTarget;
    struct glTFPrimitive;
    struct glTFMesh;
    struct glTFPerspective;
    struct glTFOrthographic;
    struct glTFCamera;
    struct glTFAnimationTarget;
    struct glTFAnimationChannel;
    struct glTFAnimationSampler;
    struct glTFAnimation;
    struct glTFTextureInfo;
    struct glTFMaterialPBR;
    struct glTFMaterial;
    struct glTFNode;
    struct glTFScene;
    struct glTF;

namespace std {

    
    
}

namespace mud {
namespace ui {

    
    
}
}

namespace glm {

    
    
}

namespace bgfx {

    
    
    struct UniformHandle;
    struct UniformType;
    struct TextureHandle;
    struct TextureInfo;
    struct TextureFormat;
    struct VertexBufferHandle;
    struct IndexBufferHandle;
    struct InstanceDataBuffer;
    struct ProgramHandle;
    struct FrameBufferHandle;
    struct Memory;
    struct VertexDecl;
    struct Aabb;
}

namespace mud {
namespace gfx {

    
    
}
}

namespace mud {

    enum class Interpolation : unsigned int;
    enum IsometricAngle : unsigned int;
    enum class ModelFormat : unsigned int;
    enum class ShaderType : unsigned int;
    enum ShaderOption : unsigned int;
    enum class TextureSampler : unsigned int;
    enum class PassType : unsigned int;
    enum class BlendMode : unsigned int;
    enum class CullMode : unsigned int;
    enum class DepthDraw : unsigned int;
    enum class DepthTest : unsigned int;
    enum class MaterialFlag : unsigned int;
    enum class TextureChannel : unsigned int;
    enum class PbrDiffuseMode : unsigned int;
    enum class PbrSpecularMode : unsigned int;
    enum PbrShaderOption : unsigned int;
    enum ShaderOptionFilter : unsigned int;
    enum class LightType : unsigned int;
    enum ShadowFlags : unsigned int;
    enum ItemFlag : unsigned int;
    enum class ItemShadow : unsigned int;
    enum class MSAA : unsigned int;
    enum class Shading : unsigned int;
    enum class TrackMode : unsigned int;
    enum class EmitterDirection : unsigned int;
    enum class PrefabType : unsigned int;
    enum class BackgroundMode : unsigned int;
    enum class TextureHint : unsigned int;
    enum ShaderOptionLight : unsigned int;
    enum ShaderOptionRadiance : unsigned int;
    enum ShaderOptionShadow : unsigned int;
    enum ShaderModeShadow : unsigned int;
    enum CSMFilterMode : unsigned int;
    enum class Month : unsigned int;
    enum ShaderOptionBlur : unsigned int;
    enum ShaderOptionDofBlur : unsigned int;
    enum ShaderOptionResolve : unsigned int;
    enum ShaderOptionGlow : unsigned int;
    enum TonemapShaderOption : unsigned int;
    enum TonemapShaderMode : unsigned int;
    enum class TonemapMode : unsigned int;
    
    template <class T> struct MaterialParam;
    template <class T> struct ValueCurve;
    template <class T> struct ValueTrack;
    
    struct AnimationCursor;
    class AnimationTrack;
    class Animation;
    struct Transform;
    class Node3;
    struct Bone;
    class Skeleton;
    struct Joint;
    class Skin;
    class Rig;
    struct AnimatedTrack;
    struct AnimationPlay;
    class Animated;
    class Camera;
    struct GpuMesh;
    class Mesh;
    struct ModelConfig;
    struct ModelItem;
    class Model;
    struct ShaderDefine;
    struct ShaderBlock;
    struct ProgramBlock;
    struct ProgramBlockArray;
    class Program;
    struct ShaderVersion;
    struct Pass;
    struct RenderFrame;
    struct Render;
    class GfxBlock;
    class DrawBlock;
    class RenderPass;
    struct DrawElement;
    class DrawPass;
    class Renderer;
    struct BaseMaterialBlock;
    struct UnshadedMaterialBlock;
    struct PbrMaterialBlock;
    struct PbrBlock;
    class Material;
    class ImmediateDraw;
    class SymbolIndex;
    struct FilterUniform;
    class Filter;
    struct RenderQuad;
    class BlockFilter;
    class BlockCopy;
    class Frustum;
    struct FrustumSlice;
    class Light;
    class GfxContext;
    class GfxSystem;
    class Gnode;
    class Item;
    class Viewport;
    struct ManualRender;
    struct Particle;
    struct ParticleSort;
    struct ParticleGenerator;
    struct ParticleVertex;
    struct ParticleEmitter;
    struct ParticleSystem;
    class Particles;
    struct PickQuery;
    class Picker;
    struct PassJobs;
    class Pipeline;
    class PassClear;
    class PassUnshaded;
    class PassOpaque;
    class PassBackground;
    class PassAlpha;
    class PassFlip;
    struct ReflectionRenderer;
    struct MinimalRenderer;
    struct MainRenderer;
    struct UnshadedRenderer;
    class PipelinePbr;
    struct PrefabNode;
    class FrameBuffer;
    struct SwapBuffer;
    struct Cascade;
    class RenderTarget;
    struct Sun;
    struct Radiance;
    struct Background;
    struct Environment;
    class Scene;
    class Shot;
    class Texture;
    struct Uniform;
    struct Sampler;
    struct UniformBlock;
    struct DepthParams;
    class PassDepth;
    class BlockDepth;
    class BlockLight;
    class BlockParticles;
    class PassParticles;
    class BlockRadiance;
    struct ReflectionCubemap;
    class ReflectionAtlas;
    class ReflectionProbe;
    class PassProbes;
    class BlockReflection;
    struct ShadowCubemap;
    class ShadowAtlas;
    struct CSMShadow;
    class PassShadow;
    class PassShadowmap;
    struct ShadowRenderer;
    struct LightBounds;
    struct LightShadow;
    class BlockShadow;
    class DynamicValueController;
    class SunController;
    struct ProceduralSky;
    struct PerezSky;
    class BlockSky;
    struct EffectBlurUniform;
    struct BlurKernel;
    class BlockBlur;
    struct DofBlur;
    struct DofBlurUniform;
    class BlockDofBlur;
    class BlockResolve;
    class PassEffects;
    class PassPostProcess;
    struct Glow;
    struct GlowUniform;
    class BlockGlow;
    struct BCS;
    struct Tonemap;
    struct RenderFilters;
    struct TonemapUniform;
    class BlockTonemap;
    class glTFImport;
    class ImporterGltf;
    class ImporterOBJ;
    class SpaceQuad;
    class SpaceSheet;
    struct ViewerStyles;
    class ViewerController;
    class Viewer;
    class SceneViewer;
    class OrbitController;
    class FreeOrbitController;
    class SpaceViewport;
}

namespace mud {
namespace detail {

    
    
}
}

namespace bimg {

    
    
    struct ImageContainer;
    struct Orientation;
}

namespace bx {

    
    
    struct FileReaderI;
    class FileReader;
    class FileWriter;
    struct AllocatorI;
    class DefaultAllocator;
    struct RngMwc;
}

