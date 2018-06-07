

#pragma once

#include <obj/Config.h>

#include <obj/Generated/Forward.h>
#include <srlz/Generated/Forward.h>
#include <math/Generated/Forward.h>
#include <geom/Generated/Forward.h>
#include <gfx/Generated/Forward.h>

#ifndef MUD_GFX_PBR_EXPORT
#define MUD_GFX_PBR_EXPORT MUD_IMPORT
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

namespace mud {
namespace gfx {

    
    
}
}

namespace json11 {

    
    
}

namespace mud {

    enum ShaderOptionLight : unsigned int;
    enum ShaderOptionRadiance : unsigned int;
    enum ShaderOptionShadow : unsigned int;
    enum ShaderModeShadow : unsigned int;
    enum CSMFilterMode : unsigned int;
    enum ShaderOptionBlur : unsigned int;
    enum ShaderOptionDofBlur : unsigned int;
    enum ShaderOptionGlow : unsigned int;
    enum TonemapShaderOption : unsigned int;
    enum TonemapShaderMode : unsigned int;
    enum class TonemapMode : unsigned int;
    
    
    struct DepthParams;
    class PassDepth;
    class BlockDepth;
    class BlockLight;
    struct ReflectionRenderer;
    struct MainRenderer;
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
    struct EffectBlurUniform;
    struct BlurKernel;
    class BlockBlur;
    struct DofBlur;
    struct DofBlurUniform;
    class BlockDofBlur;
    struct Glow;
    struct GlowUniform;
    class BlockGlow;
    struct BCS;
    struct Tonemap;
    struct RenderFilters;
    struct TonemapUniform;
    class BlockTonemap;
}

namespace mud {
namespace detail {

    
    
}
}

namespace bimg {

    
    
}

namespace bx {

    
    
}

