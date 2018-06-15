

#pragma once

#include <infra/Config.h>

#include <infra/Forward.h>
#include <obj/Forward.h>
#include <pool/Forward.h>
#include <refl/Forward.h>
#include <srlz/Forward.h>
#include <math/Forward.h>
#include <geom/Forward.h>
#include <ctx/Forward.h>

#ifndef MUD_GFX_EXPORT
#define MUD_GFX_EXPORT MUD_IMPORT
#endif


    
    

namespace std {

    
    
}

namespace mud {
namespace ui {

    
    
}
}

namespace glm {

    
    
}

namespace bgfx {

    
    
}

namespace json11 {

    
    
}

namespace mud {

    enum class Interpolation : unsigned int;
    enum class TextureHint : unsigned int;
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
    enum class ModelFormat : unsigned int;
    enum class EmitterDirection : unsigned int;
    enum class PrefabType : unsigned int;
    enum IsometricAngle : unsigned int;
    enum ShaderOptionResolve : unsigned int;
    enum ShaderOptionFilter : unsigned int;
    enum class LightType : unsigned int;
    enum ShadowFlags : unsigned int;
    enum ItemFlag : unsigned int;
    enum class ItemShadow : unsigned int;
    enum class MSAA : unsigned int;
    enum class Shading : unsigned int;
    enum class BackgroundMode : unsigned int;
    enum class Month : unsigned int;
    
    template <class T> struct MaterialParam;
    
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
    class GfxContext;
    struct LocatedFile;
    class GfxSystem;
    class Texture;
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
    struct ModelConfig;
    struct ModelItem;
    class Model;
    struct GpuMesh;
    class Mesh;
    struct Particle;
    struct ParticleSort;
    struct ParticleGenerator;
    struct ParticleVertex;
    struct ParticleEmitter;
    struct ParticleSystem;
    class Particles;
    class BlockParticles;
    class PassParticles;
    struct PrefabNode;
    class Prefab;
    class Camera;
    struct DepthParams;
    class PassDepth;
    class BlockDepth;
    class ImmediateDraw;
    class SymbolIndex;
    class BlockResolve;
    class PassEffects;
    class PassPostProcess;
    struct FilterUniform;
    class Filter;
    struct RenderQuad;
    class BlockFilter;
    class BlockCopy;
    class Frustum;
    struct FrustumSlice;
    class Light;
    class Gnode;
    class Item;
    class Viewport;
    struct ManualRender;
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
    struct MinimalRenderer;
    struct UnshadedRenderer;
    struct ClearRenderer;
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
    struct Uniform;
    struct Sampler;
    struct UniformBlock;
    class DynamicValueController;
    class SunController;
    struct ProceduralSky;
    struct PerezSky;
    class BlockSky;
}

namespace mud {
namespace detail {

    
    
}
}

namespace mud {
namespace gfx {

    
    
}
}

namespace bimg {

    
    
}

namespace bx {

    
    
}

